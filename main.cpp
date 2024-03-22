#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/algorithm/string/classification.hpp> // Include boost::for is_any_of
#include <boost/algorithm/string/split.hpp> // Include for boost::split

// https://www.boost.org/doc/libs/1_81_0/doc/html/boost_asio/tutorial/tutdaytime3.html

using boost::asio::ip::tcp;

// gracze maja nr 0 i 1
std::vector<char> pola = {'.', '.', '.', '.', '.', '.', '.', '.', '.'};
std::array<char, 2> symbole = {'X', 'O'};

int nr_gracza_aktywnego = 0;

enum class Odp { REMIS, OK_GRAMY_DALEJ, OK_WYGRALES, OK_PRZEGRALES, ZAJETE_POLE, ZLY_RUCH};

Odp ruch(int nr_gracza, int nr_pola) {
    if (nr_gracza != nr_gracza_aktywnego) return Odp::ZLY_RUCH;
    if (pola[nr_pola] != '.') return Odp::ZAJETE_POLE;
    pola[nr_pola] = symbole[nr_gracza];
    // sprawdzanie czy remis, wygrana
    nr_gracza_aktywnego = 1 - nr_gracza_aktywnego;
    return Odp::OK_GRAMY_DALEJ;
}

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
    }

    void zapytanie(const boost::system::error_code& error)
    {
        if (error) {
            std::cout << "blad, " << error << "\n";
            return;
        }

        std::cout << "dostalem wiadomosc\n";
        std::string s( (std::istreambuf_iterator<char>(&buffer)), std::istreambuf_iterator<char>() );
        boost::algorithm::trim(s);

        // na string s jest to co wyslal klient
        std::vector<std::string> words;
        boost::split(words, s, boost::is_any_of(" "), boost::token_compress_on);
        auto komenda = words[0];

        std::ostringstream ss;

        if (komenda == "status") {
            ss << nr_gracza_aktywnego;
            for (auto ch : pola) ss << " " << ch;
            ss << "\n";
        }
        else if (komenda == "ruch")
        {
            std::cout << "dostalem nr gracza:" << words[1] << ", nr pola:" << words[2] << "\n";
            int nr_gracza = boost::lexical_cast<int>(words[1]);
            int nr_pola = boost::lexical_cast<int>(words[2]);
            auto odp = ruch(nr_gracza, nr_pola);
            switch (odp) {
                case Odp::ZLY_RUCH:
                    ss << "zlyruch";
                    break;
                case Odp::ZAJETE_POLE:
                    ss << "zajete";
                    break;
                case Odp::OK_GRAMY_DALEJ:
                    ss << "ok";
                    break;
                default:
                    ss << "nie-zakodowane";
                    break;
            }
        }
        //std::cout << "tresc:" << words[0] << "\n";

        std::string odpowiedz = ss.str();
        // do tego miejsca przyszykuj odpowiedz

        boost::asio::async_write(socket_, boost::asio::buffer(odpowiedz),
                                 boost::bind(&tcp_connection::odpowiedz_wyslana, shared_from_this(),
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));

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

  void start()
  {
       //message_ = "                                      ";
       // message_ = make_daytime_string();

       std::cout << "mam polaczenie, bede czytac...\n";

      auto handler = boost::bind(&tcp_connection::zapytanie, shared_from_this(),
                  boost::asio::placeholders::error);

// https://github.com/ygpark/hanb-boost-asio-sample/blob/master/async_read_until/async_read_until.cpp
      boost::asio::async_read_until(socket_, buffer, '\n', handler);
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
