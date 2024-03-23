#include "gwint.h"

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/property_tree/json_parser.hpp>

// https://www.boost.org/doc/libs/1_81_0/doc/html/boost_asio/tutorial/tutdaytime3.html

using boost::asio::ip::tcp;

// gracze maja nr 0 i 1

class tcp_connection
  : public boost::enable_shared_from_this<tcp_connection>
{
    tcp::socket socket_;
    boost::asio::streambuf buffer;

    void odpowiedz_wyslana(const boost::system::error_code& error,
                           size_t bytes_transferred) {

        if (error) {
            std::cout << "blad w wysylaniu odpowiedzi, " << error << "\n";
            return;
        }

        std::cout << "wyslano odpowiedz, bajtow:" << bytes_transferred << "\n";
        czytaj_zapytanie();
    }

    void odeslij_odpowiedz(gwint::Wiadomosc const & wd)
    {
        std::ostringstream ss;
        boost::property_tree::write_json(ss, wd);
        std::string odpowiedz = ss.str();

        boost::asio::async_write(socket_, boost::asio::buffer(odpowiedz),
                                 boost::bind(&tcp_connection::odpowiedz_wyslana, shared_from_this(),
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));
    }

    void zapytanie(const boost::system::error_code& error, std::size_t bytes_transferred)
    {
        if (error) {
            std::cout << "blad, " << error << "\n";
            return;
        }

        boost::property_tree::ptree wiadomosc;

        try {
            std::cout << "dostalem wiadomosc\n";
            std::istream input_from_buffer(&buffer);
            boost::property_tree::read_json(input_from_buffer, wiadomosc);
        }
        catch (boost::property_tree::ptree_error const & exc)
        {
            boost::property_tree::ptree err_answer;
            err_answer.put("error", exc.what());
            buffer.consume(bytes_transferred);
            odeslij_odpowiedz(err_answer);
            return;
        }

        buffer.consume(bytes_transferred);

        gwint::OdsylaczOdpowiedzi odsylacz = boost::bind(
                &tcp_connection::odeslij_odpowiedz, shared_from_this(), boost::placeholders::_1);

        try {
            gwint::ruch(wiadomosc, odsylacz);
        }
        catch (boost::property_tree::ptree_error const & exc)
        {
            boost::property_tree::ptree err_answer;
            err_answer.put("error", exc.what());
            odeslij_odpowiedz(err_answer);
        }
    }

    void czytaj_zapytanie()
    {
        auto handler = boost::bind(&tcp_connection::zapytanie, shared_from_this(),
                                   boost::asio::placeholders::error, boost::placeholders::_2);

        // https://github.com/ygpark/hanb-boost-asio-sample/blob/master/async_read_until/async_read_until.cpp
        boost::asio::async_read_until(socket_, buffer, "\r\n\r\n", handler);
    }

public:
  typedef boost::shared_ptr<tcp_connection> pointer;

  static pointer create(boost::asio::io_context& io_context)
  {
    return pointer(new tcp_connection(io_context));
  }

  tcp::socket& socket()
  {
    return socket_;
  }

  void start() {
      std::cout << "mam polaczenie\n";
      czytaj_zapytanie();
  }

  private:
    tcp_connection(boost::asio::io_context& io_context)
        : socket_(io_context)
    {
    }
};


class tcp_server {
    boost::asio::io_context & io_context_;
    tcp::acceptor acceptor_;

public:
    tcp_server(boost::asio::io_context & io_context)
            : io_context_(io_context),
              acceptor_(io_context, tcp::endpoint(tcp::v4(), 33567)) {
        start_accept();
    }

private:

    void start_accept() {
        tcp_connection::pointer new_connection =
                tcp_connection::create(io_context_);

        acceptor_.async_accept(new_connection->socket(),
                               boost::bind(&tcp_server::handle_accept, this, new_connection,
                                           boost::asio::placeholders::error));
    }

    void handle_accept(tcp_connection::pointer new_connection,
                       const boost::system::error_code &error) {
        if (!error) {
            new_connection->start();
        }

        start_accept();
    }
};

int main() {

  try
  {
    boost::asio::io_context io_context;
    tcp_server server(io_context);


    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
