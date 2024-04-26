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
class Gra {
public:
    std::vector<zmienneKarty> daneKart;
    std::vector<int> kupkaDobierania;
    std::vector<int> zuzyte;
    std::vector<int> wypadniete;
    std::vector<daneGracza> daneGraczy;
    bool czyGraWystartowala=0;
    OdsylaczOdpowiedzi odsylacz_ktory_czeka;
    std::string kod_ostatniego_ruchu; // do odesłania
};
std::map<int, Gra> gry;

//nazwaVectoraX = nazwaVectora z danej gry
void stworzDaneKart(std::vector<zmienneKarty>& daneKartX) {
    std::cout<<"sdk1";
    daneKartX.reserve(57);
    daneKartX[0]=zmienneKarty(0, 1, 44);
    daneKartX[ 1]=zmienneKarty( 1, 2, 1);
    daneKartX[ 2]=zmienneKarty( 2, 2, 2);
    daneKartX[ 3]=zmienneKarty( 3, 2, 3);
    daneKartX[ 4]=zmienneKarty( 4, 2, 4);
    daneKartX[ 5]=zmienneKarty( 5, 3, 1);
    daneKartX[ 6]=zmienneKarty( 6, 3, 2);
    daneKartX[ 7]=zmienneKarty( 7, 3, 3);
    daneKartX[ 8]=zmienneKarty( 8, 3, 4);
    daneKartX[ 9]=zmienneKarty( 9, 4, 1);
    daneKartX[10]=zmienneKarty(10, 4, 2);
    daneKartX[11]=zmienneKarty(11, 4, 3);
    daneKartX[12]=zmienneKarty(12, 4, 4);
    daneKartX[13]=zmienneKarty(13, 5, 1);
    daneKartX[14]=zmienneKarty(14, 5, 2);
    daneKartX[15]=zmienneKarty(15, 5, 3);
    daneKartX[16]=zmienneKarty(16, 5, 4);
    daneKartX[17]=zmienneKarty(17, 6, 1);
    daneKartX[18]=zmienneKarty(18, 6, 2);
    daneKartX[19]=zmienneKarty(19, 6, 3);
    daneKartX[20]=zmienneKarty(20, 6, 4);
    daneKartX[21]=zmienneKarty(21, 7, 1);
    daneKartX[22]=zmienneKarty(22, 7, 2);
    daneKartX[23]=zmienneKarty(23, 7, 3);
    daneKartX[24]=zmienneKarty(24, 7, 4);
    daneKartX[25]=zmienneKarty(25, 8, 1);
    daneKartX[26]=zmienneKarty(26, 8, 2);
    daneKartX[27]=zmienneKarty(27, 8, 3);
    daneKartX[28]=zmienneKarty(28, 8, 4);
    daneKartX[29]=zmienneKarty(29, 9, 1);
    daneKartX[30]=zmienneKarty(30, 9, 2);
    daneKartX[31]=zmienneKarty(31, 9, 3);
    daneKartX[32]=zmienneKarty(32, 9, 4);
    daneKartX[33]=zmienneKarty(33, 10, 1);
    daneKartX[34]=zmienneKarty(34, 10, 2);
    daneKartX[35]=zmienneKarty(35, 10, 3);
    daneKartX[36]=zmienneKarty(36, 10, 4);
    daneKartX[37]=zmienneKarty(37, 12, 1);
    daneKartX[38]=zmienneKarty(38, 12, 2);
    daneKartX[39]=zmienneKarty(39, 12, 3);
    daneKartX[40]=zmienneKarty(40, 12, 4);
    daneKartX[41]=zmienneKarty(41, 14, 1);
    daneKartX[42]=zmienneKarty(42, 14, 2);
    daneKartX[43]=zmienneKarty(43, 14, 3);
    daneKartX[44]=zmienneKarty(44, 14, 4);
    daneKartX[45]=zmienneKarty(45, 16, 1);
    daneKartX[46]=zmienneKarty(46, 16, 2);
    daneKartX[47]=zmienneKarty(47, 16, 3);
    daneKartX[48]=zmienneKarty(48, 16, 4);
    daneKartX[49]=zmienneKarty(49, 18, 1);
    daneKartX[50]=zmienneKarty(50, 18, 2);
    daneKartX[51]=zmienneKarty(51, 18, 3);
    daneKartX[52]=zmienneKarty(52, 18, 4);
    daneKartX[53]=zmienneKarty(53, 20, 5);
    daneKartX[54]=zmienneKarty(54, 20, 5);
    daneKartX[55]=zmienneKarty(55, 20, 5);
    //std::cout <<"sdk2";
}
void stworzDaneGraczy(std::vector<daneGracza>& daneGraczyX) {
    //std::cout<<"sdg1";
    daneGraczyX = std::vector<daneGracza>(2); //[0]=daneGracza();
    //daneGraczy[1]=daneGracza();
    daneGraczyX[0].liczba_pol_na_karty=4;
    daneGraczyX[1].liczba_pol_na_karty=4;
    daneGraczyX[0].liczba_polozonych_kart=0;
    daneGraczyX[1].liczba_polozonych_kart=0;
    //std::cout<<"sdg2";
}
void przetasujKupkeDobierania(std::vector<int>& kupkaDobieraniaX) {
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(kupkaDobieraniaX), std::end(kupkaDobieraniaX), rng);
}

void stworzKupkeDobierania(std::vector<int>& kupkaDobieraniaX) {
    //std::cout<<"skd1";
    for(int d=1;d<=55;d++) {
        kupkaDobieraniaX.push_back(d);
    }
    przetasujKupkeDobierania(kupkaDobieraniaX);
    //std::cout<<"skd2";
}
void przeniesKartyZeZuzytychNaKupkeDobierania(std::vector<int>& zuzyteX, std::vector<int>& kupkaDobieraniaX) {
    for(auto d : zuzyteX) {
        kupkaDobieraniaX.push_back(d);
    }
    zuzyteX.clear();
    przetasujKupkeDobierania(kupkaDobieraniaX);
}
int dobierzKarte(int nr_gracza, std::vector<int>& kupkaDobieraniaX, std::vector<int>& zuzyteX, std::vector<daneGracza>& daneGraczyX) {
    if(kupkaDobieraniaX.size()==0) {
        przeniesKartyZeZuzytychNaKupkeDobierania(zuzyteX, kupkaDobieraniaX);
    }
    auto dobranaKarta = kupkaDobieraniaX[0];
    kupkaDobieraniaX.erase(kupkaDobieraniaX.begin()+0);
    daneGraczyX[nr_gracza].talia.push_back(dobranaKarta);
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
bool czygraczamakarteb(int a, int b, std::vector<daneGracza>& daneGraczyX) {
    for(auto x :daneGraczyX[a].talia) {
        if(x==b) {
            return 1;
        }
    }
    return 0;
}
bool czygraczamamiejscenakarty(int a,std::vector<daneGracza>& daneGraczyX) {
    if(daneGraczyX[a].liczba_pol_na_karty>daneGraczyX[a].liczba_polozonych_kart) {
        return 1;
    }
    return 0;
}
bool czykartaapasujedob(int a, int b, std::vector<zmienneKarty>& daneKartX) {
    //std::cout<<"sprawdzam czy " << a << "pasuje do " << b << "\n";
    if(daneKartX[a].wartosc==daneKartX[b].wartosc) {
        //std::cout<<"zgadzaja sie wartosci\n";
        return 1;
    }
    if(daneKartX[a].znak==daneKartX[b].znak) {
        //std::cout<<"zgadzaja sie znaki \n";
        return 1;
    }
    //std::cout << "nie zgadzaja sie\n";
    return 0;
}
bool czykartaapasujedopolagraczab(int a, int b, std::vector<daneGracza> daneGraczyX, std::vector<zmienneKarty>& daneKartX) {
    
    if(daneGraczyX[b].liczba_polozonych_kart==0) {
        return 1;
    }
    for(auto x : daneGraczyX[b].pole) {
        if(czykartaapasujedob(x.karta, a, daneKartX)) {
            return 1;
        }
    }
    return 0;
}
void usunkartez(std::vector<int> &v, int nr_karty) {
    bool cu=0;
    for(int d=0;d<v.size();d++) {
        //std::cout<<"natrafilem na karte "<<v[d]<< "\n";
        if(v[d]==nr_karty) {
            //std::cout<< "anlazlem szukaną "<< nr_karty << "\n";
            v.erase(v.begin()+d);
            cu=1;
            break;
        }
    }
    if(!cu)std::cout<<"NIE USUNAL KARTY!\n";
}
void zakonczWszystkieGry() {
    gry.clear();
    std::cout<<"---------zakonczono wszystkie gry\n";
}


void ruch(Wiadomosc const & wd, OdsylaczOdpowiedzi const & odsylacz)
{
    std::cout << "ruch start\n";
    std::string komenda = wd.get<std::string>("cmd");
    // na string wd jest to co dostales od klienta

    Wiadomosc odp; // odpowiedzi do odeslania

    std::string tkod_ruchu; //tymczasowy kod ruchu który chce gracz wykonać
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
        int id_gry=wd.get<int>("id_gry");
        Wiadomosc talia_gracza;
        for(auto x : gry[id_gry].daneGraczy[nr_gracza].talia) {
            talia_gracza.put<int>("", x);
        }
        odp.add_child("talia_gracza", talia_gracza);
    }
    else if(komenda == "start") {
        int id_gry=wd.get<int>("id_gry");
        std::cout << "gra " << id_gry << " ------------\n";
        if(!gry.count(id_gry)||!gry[id_gry].czyGraWystartowala) {
            std::cout << "pomyslnie wystartowala\n";
            Gra X;
            gry[id_gry]=X;
            stworzDaneKart(gry[id_gry].daneKart);
            stworzDaneGraczy(gry[id_gry].daneGraczy);
            stworzKupkeDobierania(gry[id_gry].kupkaDobierania);
            gry[id_gry].czyGraWystartowala=1;
            odp.put<std::string>("sukces", "wystartowalo");
        }
        else {
            std::cout << "juz wczesniej byla taka gra\n";
            odp.put<std::string>("error", "gra_juz_wczesniej_wystartowala");
        }
    }
    else if(komenda == "pole") {
        int nr_gracza = wd.get<int>("nr_gracza");
        int id_gry=wd.get<int>("id_gry");
        std::cout << "gra " << id_gry << " ------------\n";
        for(auto karta : gry[id_gry].daneGraczy[nr_gracza].pole) {
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
        int id_gry=wd.get<int>("id_gry");
        std::cout << "gra " << id_gry << " ------------\n";
        if(!gry.count(id_gry)) {
            odp.put<std::string>("error", "zly_kod_gry");
            std::cout << "zly kod gry\n";
        }
        else {
            auto dobrana = dobierzKarte(nr_gracza, gry[id_gry].kupkaDobierania, gry[id_gry].zuzyte,
                                        gry[id_gry].daneGraczy);
            odp.put<int>("dobrana_karta", dobrana);
        }
    }
    else if(komenda == "postaw_na_polu") {

        int nr_gracza = wd.get<int>("nr_gracza");
        int nr_karty = wd.get<int>("nr_karty");
        int nr_pola = wd.get<int>("nr_pola");
        int id_gry=wd.get<int>("id_gry");
        std::cout << "gra " << id_gry << " ------------\n";
        if(!gry.count(id_gry)) {
            odp.put<std::string>("error", "zly_kod_gry");
            std::cout << "zly kod gry\n";
        }
        else {
            tkod_ruchu+=std::to_string(nr_gracza);
            tkod_ruchu += 'a';
            if (nr_karty < 10) {
                tkod_ruchu += '0';
                tkod_ruchu += std::to_string(nr_karty);
            } else {
                tkod_ruchu += std::to_string(nr_karty);
            }
            tkod_ruchu += std::to_string(nr_pola);
            if (!czygraczamakarteb(nr_gracza, nr_karty, gry[id_gry].daneGraczy)) {
                odp.put<std::string>("error", "gracz_nie_posiada_tej_karty");

            } else if (!czygraczamamiejscenakarty(nr_gracza, gry[id_gry].daneGraczy)) {
                odp.put<std::string>("error", "gracz_nie_ma_miejsca_na_polu");
            } else if (!czykartaapasujedopolagraczab(nr_karty, nr_gracza, gry[id_gry].daneGraczy,
                                                     gry[id_gry].daneKart)) {
                odp.put<std::string>("error", "karta_nie_pasuje_do_pola");
            } else if (gry[id_gry].daneGraczy[nr_gracza].pole[nr_pola].karta != 0) {
                odp.put<std::string>("error", "na_polu_jest_inna_karta");
            } else {
                if (nr_pola >= 5 && nr_pola <= 8) {
                    if (gry[id_gry].daneGraczy[nr_gracza].pole[nr_pola].czyJestAs == 0) {
                        odp.put<std::string>("error", "nie_ma_tam_asa");
                    } else {
                        gry[id_gry].daneGraczy[nr_gracza].pole[nr_pola].karta = nr_karty;
                        gry[id_gry].kod_ostatniego_ruchu = tkod_ruchu;
                        odp.put<std::string>("sukces", "karta_polozona");
                    }
                } else if (nr_pola >= 1 && nr_pola <= 4) {
                    gry[id_gry].daneGraczy[nr_gracza].pole[nr_pola].karta = nr_karty;
                    gry[id_gry].kod_ostatniego_ruchu = tkod_ruchu;
                    odp.put<std::string>("sukces", "karta_polozona");
                } else {
                    odp.put<std::string>("error", "zly_numer_pola");
                }
                if (gry[id_gry].kod_ostatniego_ruchu == tkod_ruchu) {
                    usunkartez(gry[id_gry].daneGraczy[nr_gracza].talia, nr_karty);
                }
            }
        }
    }
    else if (komenda == "czekaj") {
        int id_gry=wd.get<int>("id_gry");
        std::cout << "gra " << id_gry << " ------------\n";
        if(!gry.count(id_gry)) {
            odp.put<std::string>("error", "zly_kod_gry");
            std::cout << "zly kod gry\n";
        }
        else {
            if (gry[id_gry].odsylacz_ktory_czeka) {
                odp.put<std::string>("error", "juz_ktos_czeka");
            } else {
                gry[id_gry].odsylacz_ktory_czeka = odsylacz;
                return;
            }
        }
    }
    else if (komenda == "zwolnij_czekacza") {
        int id_gry=wd.get<int>("id_gry");
        std::cout << "gra " << id_gry << " ------------\n";
        if(!gry.count(id_gry)) {
            odp.put<std::string>("error", "zly_kod_gry");
            std::cout << "zly kod gry\n";
        }
        else {
            if (gry[id_gry].odsylacz_ktory_czeka) {
                Wiadomosc odp_dla_tego_co_czeka;
                odp_dla_tego_co_czeka.put<std::string>("byl_ruch", gry[id_gry].kod_ostatniego_ruchu);
                gry[id_gry].odsylacz_ktory_czeka(odp_dla_tego_co_czeka);
                gry[id_gry].odsylacz_ktory_czeka = OdsylaczOdpowiedzi();
                odp.put("sukces", "ktos_czekal_i_go_obudzilismy");
            } else {
                odp.put("sukces", "nikt_nie_czekal");
            }
        }
    }
    else if(komenda=="zakoncz") {
        int id_gry=wd.get<int>("id_gry");
        std::cout << "gra " << id_gry << " ------------\n";
        if(!gry.count(id_gry)) {
            odp.put<std::string>("error", "zly_kod_gry");
            std::cout << "zly kod gry\n";
        }
        else {
            //PODLICZANIE KTO WYGRAL
            gry.erase(id_gry);

            std::cout << "pomyslnie zakonczono gre\n";
            odp.put<std::string>("sukces", "zakonczono_gre");
        }
    }
    else if(komenda=="zakoncz_wszystkie") {
        zakonczWszystkieGry();
    }
    else {
        std::cout << "!!dostalem nieznana komende\n";
        odp.put("error", "nieznana_komenda");
    }

    odsylacz(odp);
}

}



