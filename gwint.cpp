#include "gwint.h"
#include <algorithm>
#include <random>
#include <bits/stdc++.h>

namespace gwint
{

std::vector<char> pola = {'.', '.', '.', '.', '.', '.', '.', '.', '.'};
std::array<char, 2> symbole = {'X', 'O'};

int nr_gracza_aktywnego = 0;
class zmienneKarty {
    //1=PIK 2=KARO 3=TREFL 4=SERCE
public:
    int id;
    int wartosc;
    int znak;
    zmienneKarty(int przyjeteId, int przyjetaWartosc, int przyjetyZnak) {
        id=przyjeteId;
        wartosc= przyjetaWartosc;
        znak=przyjetyZnak;
    }
};
class pojedynczePole {
public:
    bool czyJestAs;
    int karta;
    std::vector<int> dwojki;
};
std::vector<zmienneKarty> daneKart;
std::vector<int> kupkaDobierania;
std::vector<int> zuzyte;
std::vector<int> wypadniete;
bool czyGraWystartowala=0;
class daneGracza {
public:
    std::vector<int> talia;
    std::vector<pojedynczePole> pole;


    int liczba_pol_na_karty;
    int liczba_polozonych_kart;
    daneGracza(){
        pole.reserve(12);
        pojedynczePole puste;
        puste.karta=0;
        puste.dwojki=std::vector<int>(0, 0);
        puste.czyJestAs=0;
        for(int d=1;d<=10;d++) {
            pole[d]=puste;
        }
    }
};
std::vector<daneGracza> daneGraczy;
void stworzDaneKart() {
    std::cout<<"sdk1";
    daneKart.reserve(57);
    daneKart[0]=zmienneKarty(0, 1, 44);
    daneKart[ 1]=zmienneKarty( 1, 2, 1);
    daneKart[ 2]=zmienneKarty( 2, 2, 2);
    daneKart[ 3]=zmienneKarty( 3, 2, 3);
    daneKart[ 4]=zmienneKarty( 4, 2, 4);
    daneKart[ 5]=zmienneKarty( 5, 3, 1);
    daneKart[ 6]=zmienneKarty( 6, 3, 2);
    daneKart[ 7]=zmienneKarty( 7, 3, 3);
    daneKart[ 8]=zmienneKarty( 8, 3, 4);
    daneKart[ 9]=zmienneKarty( 9, 4, 1);
    daneKart[10]=zmienneKarty(10, 4, 2);
    daneKart[11]=zmienneKarty(11, 4, 3);
    daneKart[12]=zmienneKarty(12, 4, 4);
    daneKart[13]=zmienneKarty(13, 5, 1);
    daneKart[14]=zmienneKarty(14, 5, 2);
    daneKart[15]=zmienneKarty(15, 5, 3);
    daneKart[16]=zmienneKarty(16, 5, 4);
    daneKart[17]=zmienneKarty(17, 6, 1);
    daneKart[18]=zmienneKarty(18, 6, 2);
    daneKart[19]=zmienneKarty(19, 6, 3);
    daneKart[20]=zmienneKarty(20, 6, 4);
    daneKart[21]=zmienneKarty(21, 7, 1);
    daneKart[22]=zmienneKarty(22, 7, 2);
    daneKart[23]=zmienneKarty(23, 7, 3);
    daneKart[24]=zmienneKarty(24, 7, 4);
    daneKart[25]=zmienneKarty(25, 8, 1);
    daneKart[26]=zmienneKarty(26, 8, 2);
    daneKart[27]=zmienneKarty(27, 8, 3);
    daneKart[28]=zmienneKarty(28, 8, 4);
    daneKart[29]=zmienneKarty(29, 9, 1);
    daneKart[30]=zmienneKarty(30, 9, 2);
    daneKart[31]=zmienneKarty(31, 9, 3);
    daneKart[32]=zmienneKarty(32, 9, 4);
    daneKart[33]=zmienneKarty(33, 10, 1);
    daneKart[34]=zmienneKarty(34, 10, 2);
    daneKart[35]=zmienneKarty(35, 10, 3);
    daneKart[36]=zmienneKarty(36, 10, 4);
    daneKart[37]=zmienneKarty(37, 12, 1);
    daneKart[38]=zmienneKarty(38, 12, 2);
    daneKart[39]=zmienneKarty(39, 12, 3);
    daneKart[40]=zmienneKarty(40, 12, 4);
    daneKart[41]=zmienneKarty(41, 14, 1);
    daneKart[42]=zmienneKarty(42, 14, 2);
    daneKart[43]=zmienneKarty(43, 14, 3);
    daneKart[44]=zmienneKarty(44, 14, 4);
    daneKart[45]=zmienneKarty(45, 16, 1);
    daneKart[46]=zmienneKarty(46, 16, 2);
    daneKart[47]=zmienneKarty(47, 16, 3);
    daneKart[48]=zmienneKarty(48, 16, 4);
    daneKart[49]=zmienneKarty(49, 18, 1);
    daneKart[50]=zmienneKarty(50, 18, 2);
    daneKart[51]=zmienneKarty(51, 18, 3);
    daneKart[52]=zmienneKarty(52, 18, 4);
    daneKart[53]=zmienneKarty(53, 20, 5);
    daneKart[54]=zmienneKarty(54, 20, 5);
    daneKart[55]=zmienneKarty(55, 20, 5);
    std::cout <<"sdk2";
}
void stworzDaneGraczy() {
    std::cout<<"sdg1";
    daneGraczy = std::vector<daneGracza>(2); //[0]=daneGracza();
    //daneGraczy[1]=daneGracza();
    daneGraczy[0].liczba_pol_na_karty=4;
    daneGraczy[1].liczba_pol_na_karty=4;
    daneGraczy[0].liczba_polozonych_kart=0;
    daneGraczy[1].liczba_polozonych_kart=0;
    std::cout<<"sdg2";
}
void przetasujKupkeDobierania() {
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(kupkaDobierania), std::end(kupkaDobierania), rng);
}

void stworzKupkeDobierania() {
    std::cout<<"skd1";
    for(int d=1;d<=55;d++) {
        kupkaDobierania.push_back(d);
    }
    przetasujKupkeDobierania();
    std::cout<<"skd2";
}
void przeniesKartyZeZuzytychNaKupkeDobierania() {
    for(auto d : zuzyte) {
        kupkaDobierania.push_back(d);
    }
    zuzyte.clear();
    przetasujKupkeDobierania();
}
int dobierzKarte(int nr_gracza) {
    if(kupkaDobierania.size()==0) {
        przeniesKartyZeZuzytychNaKupkeDobierania();
    }
    auto dobranaKarta = kupkaDobierania[0];
    kupkaDobierania.erase(kupkaDobierania.begin()+0);
    daneGraczy[nr_gracza].talia.push_back(dobranaKarta);
    return dobranaKarta;
}
enum class Odp { REMIS, OK_GRAMY_DALEJ, OK_WYGRALES, OK_PRZEGRALES, ZAJETE_POLE, ZLY_RUCH};
/*
Odp ruch(int nr_gracza, int nr_pola) {
    if (nr_gracza != nr_gracza_aktywnego) return Odp::ZLY_RUCH;
    if (pola[nr_pola] != '.') return Odp::ZAJETE_POLE;
    pola[nr_pola] = symbole[nr_gracza];
    // sprawdzanie czy remis, wygrana
    nr_gracza_aktywnego = 1 - nr_gracza_aktywnego;
    return Odp::OK_GRAMY_DALEJ;
}
 */
bool czygraczamakarteb(int a, int b) {
    for(auto x :daneGraczy[a].talia) {
        if(x==b) {
            return 1;
        }
    }
    return 0;
}
bool czygraczamamiejscenakarty(int a) {
    if(daneGraczy[a].liczba_pol_na_karty>daneGraczy[a].liczba_polozonych_kart) {
        return 1;
    }
    return 0;
}
bool czykartaapasujedob(int a, int b) {
    std::cout<<"sprawdzam czy " << a << "pasuje do " << b << "\n";
    if(daneKart[a].wartosc==daneKart[b].wartosc) {
        std::cout<<"zgadzaja sie wartosci\n";
        return 1;
    }
    if(daneKart[a].znak==daneKart[b].znak) {
        std::cout<<"zgadzaja sie znaki \n";
        return 1;
    }
    std::cout << "nie zgadzaja sie\n";
    return 0;
}
bool czykartaapasujedopolagraczab(int a, int b) {
    
    if(daneGraczy[b].liczba_polozonych_kart==0) {
        return 1;
    }
    for(auto x : daneGraczy[b].pole) {
        if(czykartaapasujedob(x.karta, a)) {
            return 1;
        }
    }
    return 0;
}
void usunkartez(std::vector<int> &v, int nr_karty) {
    bool cu=0;
    for(int d=0;d<v.size();d++) {
        std::cout<<"natrafilem na karte "<<v[d]<< "\n";
        if(v[d]==nr_karty) {
            std::cout<< "anlazlem szukaną "<< nr_karty << "\n";
            v.erase(v.begin()+d);
            cu=1;
            break;
        }
    }
    if(!cu)std::cout<<"NIU USUNALEM ZADNEJ KARTY :OOOOOOOOOOO\n";
}

OdsylaczOdpowiedzi odsylacz_ktory_czeka;

void ruch(Wiadomosc const & wd, OdsylaczOdpowiedzi const & odsylacz)
{
    std::cout << "ruch start\n";
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

    }
    else if(komenda=="wypisz_dane_gracza") {
        int nr_gracza=wd.get<int>("nr_gracza");
        Wiadomosc talia_gracza;
        for(auto x : daneGraczy[nr_gracza].talia) {
            talia_gracza.put<int>("", x);
        }
        odp.add_child("talia_gracza", talia_gracza);
    }
    else if(komenda == "start") {
        if(!czyGraWystartowala) {
            stworzDaneKart();
            stworzDaneGraczy();
            stworzKupkeDobierania();
            czyGraWystartowala=1;
            odp.put<std::string>("odpowiedz", "wystartowalo");
        }
        else {
            odp.put<std::string>("error", "gra_juz_wczesniej_wystartowala");
        }
    }
    else if(komenda == "pole") {
        int nr_gracza = wd.get<int>("nr_gracza");

        for(auto karta : daneGraczy[nr_gracza].pole) {
            odp.put("", karta.karta);
        }
    }
    /*
    else if (komenda == "ruch") {
        //std::cout << "dostalem nr gracza:" << words[1] << ", nr pola:" << words[2] << "\n";
        int nr_gracza = wd.get<int>("player_id");
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
     */
    else if(komenda == "dobierz_karte") {
        int nr_gracza = wd.get<int>("nr_gracza");
        auto dobrana = dobierzKarte(nr_gracza);
        odp.put<int>("dobrana_karta", dobrana);
    }
    else if(komenda == "postaw_na_polu") {
        int nr_gracza = wd.get<int>("nr_gracza");
        int nr_karty = wd.get<int>("nr_karty");
        int nr_pola = wd.get<int>("nr_pola");
        if(!czygraczamakarteb(nr_gracza, nr_karty)) {
            odp.put<std::string>("error", "gracz_nie_posiada_tej_karty");

        }
        else if(!czygraczamamiejscenakarty(nr_gracza)){
            odp.put<std::string>("error", "gracz_nie_ma_miejsca_na_polu");
        }
        else if(!czykartaapasujedopolagraczab(nr_karty, nr_gracza)) {
            odp.put<std::string>("error", "karta_nie_pasuje_do_pola");
        }
        else if(daneGraczy[nr_gracza].pole[nr_pola].karta!=0) {
            odp.put<std::string>("error", "na_polu_jest_inna_karta");
        }
        else {
            if(nr_pola>=5&&nr_pola<=8) {
                if(daneGraczy[nr_gracza].pole[nr_pola].czyJestAs==0) {
                    odp.put<std::string>("error", "nie_ma_tam_asa");
                }
                else {
                    daneGraczy[nr_gracza].pole[nr_pola].karta=nr_karty;
                }
            }
            else if(nr_pola>=1&&nr_pola<=4) {
                daneGraczy[nr_gracza].pole[nr_pola].karta=nr_karty;
            }
            else {
                odp.put<std::string>("error", "zly_numer_pola");
            }
            usunkartez(daneGraczy[nr_gracza].talia, nr_karty);
        }
    }
    else if (komenda == "czekaj") {
        if (odsylacz_ktory_czeka) {
            odp.put<std::string>("error", "juz-ktos-czeka");
        }
        else {
            odsylacz_ktory_czeka = odsylacz;
            return;
        }
    }
    else if (komenda == "zwolnij-czekacza") {
        if (odsylacz_ktory_czeka) {
            Wiadomosc odp_dla_tego_co_czeka;
            odp_dla_tego_co_czeka.put<std::string>("byl_ruch", "tutaj-opis-ruchu");
            odsylacz_ktory_czeka(odp_dla_tego_co_czeka);
            odsylacz_ktory_czeka = OdsylaczOdpowiedzi();
            odp.put("status", "sukces-ktos-czekal-i-go-obudzilismy");
        }
        else {
            odp.put("status", "nikt-nie-czekal");
        }
    }
    else {
        odp.put("error", "unknown command");
    }

    odsylacz(odp);
}

}



