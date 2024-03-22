#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>

// https://www.boost.org/doc/libs/1_81_0/doc/html/boost_asio/tutorial/tutdaytime3.html

using boost::asio::ip::tcp;

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

class tcp_connection
  : public boost::enable_shared_from_this<tcp_connection>
{
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

  void start()
  {
       message_ = "                                      ";
       // message_ = make_daytime_string();

       std::cout << "mam polaczenie, bede czytac...\n";

      auto handler = boost::bind(&tcp_connection::czy_nowa_czy_stara, shared_from_this(),
                  boost::asio::placeholders::error);

// https://github.com/ygpark/hanb-boost-asio-sample/blob/master/async_read_until/async_read_until.cpp
      boost::asio::async_read_until(socket_, buffer, '\n', handler);

       //boost::asio::async_write(socket_, boost::asio::buffer(message_),
       //  boost::bind(&tcp_connection::handle_write, shared_from_this(),
       //   boost::asio::placeholders::error,
       //   boost::asio::placeholders::bytes_transferred));

  }
  private:
  tcp_connection(boost::asio::io_context& io_context)
    : socket_(io_context)
  {
  }

  void handle_write(const boost::system::error_code& /*error*/,
      size_t /*bytes_transferred*/)
  {
  }

  void czy_nowa_czy_stara(const boost::system::error_code& /*error*/)
  {
      std::string s( (std::istreambuf_iterator<char>(&buffer)), std::istreambuf_iterator<char>() );

      std::cout << "dostalem \n" << s << "\n";
  }

  tcp::socket socket_;
  std::string message_;
  boost::asio::streambuf buffer;
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
