#include "gwint.h"

namespace gwint
{

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




void ruch(Wiadomosc const & wd, OdsylaczOdpowiedzi const & odsylacz)
{
    std::string komenda = wd.get<std::string>("cmd");
    // na string wd jest to co dostales od klienta

    Wiadomosc odp; // odpowiedzi do odeslania

    if (komenda == "status") {

        odp.put<int>("active_player", nr_gracza_aktywnego);

        Wiadomosc tablica;
        for (auto ch: pola) {
            Wiadomosc el;
            el.put("", ch);
            tablica.push_back(std::make_pair("", el));
        }
        odp.add_child("board", tablica);

    } else if (komenda == "ruch") {
        //std::cout << "dostalem nr gracza:" << words[1] << ", nr pola:" << words[2] << "\n";
        int nr_gracza = wd.get<int>("player_num");
        int nr_pola = wd.get<int>("field_num");
        auto rodp = ruch(nr_gracza, nr_pola);
        switch (rodp) {
            case Odp::ZLY_RUCH:
                odp.put<std::string>("result", "zlyruch");
                break;
            case Odp::ZAJETE_POLE:
                odp.put<std::string>("result", "zajete");
                break;
            case Odp::OK_GRAMY_DALEJ:
                odp.put<std::string>("result", "ok_gramy_dalej");
                break;
            default:
                odp.put<std::string>("error", "not implemented");
                break;
        }
    }
    else {
        odp.put("error", "unknown command");
    }

    odsylacz(odp);
}

}



