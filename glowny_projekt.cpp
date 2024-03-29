#include <iostream> // Standardowa biblioteka C++
#include <vector> //W programie wykorszystywane są wektory i ich funkcjonalności
#include <fstream> // biblioteka udostępniająca działania na plikach
#include "tlumaczenie.h" // Nagłówek do klasy
#include <limits> // Przy używaniu getline od użytkownika pomaga ustalić rozsądny limit inputu
#include <ctime> // biblioteka udostępniająca funkcjonalność zegara w c++
#include "angielski.h" //nagłówki zawierające wektory i funkcje poszególnych języków
#include "francuski.h" //każdy pojedynczy z nich znajduję sie w innym pliku (czyli ma inną ścieżkę)
#include "norweski.h" // więc każdy z nich musi być osobno wywołany
#include "wietnamski.h" // -||-
#include "chinski_uproszczony.h" // -||-
#include "koreanski.h" // -||-
#include "rosyjski.h" // -||-
#include "arabski.h" // -||-
#include "hebrajski.h" // -||-
#include "gruzinski.h" // -||-
#include "wegierski.h" // -||-
#include "hindi.h" // -||- ____

// Tworzymy nieskończoną maszynę, potrzebujemy do tego
// zmienną globalną kontrolującą stan naszej maszyny
int state = 0;
// Wektor przyjmujący klasę tłumaczenie jako typ, oraz
// przyjmujący ścieżkę naszego pliku jako argument
// Dochodzi do rozczytania naszego pliku wejściowego
// zapisany w formie csv, oraz strukturze
// słowo_docelowe,tłumaczenie,poziom trudności.
//
// Na końcu (rozczytanie ostatniej linijki)
// rozczytany plik jest zwracany w formie wektora
// do którego przesyłaliśmy (push.back) dane
std::vector<tlumaczenie>wczytaj_dane(std::string sciezka)
{
    std::vector<tlumaczenie> wynik;
    std::ifstream plik_z_danymi;
    plik_z_danymi.open(sciezka);
    if (plik_z_danymi.good())
    {
        std::string j1, j2;
        int lvl;
        while (true)
        {
            plik_z_danymi >> j1 >> j2 >> lvl;
            tlumaczenie t;
            t.jezyk1 = j1;
            t.jezyk2 = j2;
            t.set_lvl(lvl);
            if(!plik_z_danymi.fail())
            {
                wynik.push_back(t);
            }
            else break;
        }
    }
    else
    {
        std::cout<<"nie otwarto pliku";
    }
    return wynik;
}

// Jako input użytkownika korzystamy z getline, który jeżeli raz przyjmie argument,
// potrafi w programie przekazać ten sam input do kolejnego polecenia.
// Funckja clear_cin czyści ten input, żeby ominąć ten problem.
void clear_cin()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    srand(time(NULL));
    // W tej sekcji przekładany jest każdy pojedynczy język
    // na odpowiadające im wektory, których typ jest klasą "tlumaczenie".
    przeklad_angielski();
    przeklad_francuski();
    przeklad_norweski();
    przeklad_wietnamski();
    przeklad_chinski_uproszczony();
    przeklad_koreanski();
    przeklad_rosyjski();
    przeklad_arabski();
    przeklad_hebrajski();
    przeklad_gruzinski();
    przeklad_wegierski();
    przeklad_hindi();

    // Wprowadzenie dla użytkownika
    std::cout << std::endl;
    std::cout << "Aplikacja tekstowa Fiszki" << std::endl << std::endl;
    std::cout << "Tłumaczenie z języka docelowego na polski." << std::endl;
    std::cout << "Znacząca większość zagranicznych słów w różnym kontekście ma wiele znaczeń." << std::endl;
    std::cout << "Aplikacja ma opcję zaliczenia odpowiedzi podczas gdy znaliśmy odpowiedź, "
                 "natomiast system tego nie uznał." << std::endl;
    std::cout << "W przypadku wpisania innego tłumaczenia, nie należy zaliczać odpowiedzi. "
                 "Celem jest zapamiętanie podanego tłumaczenia." <<std::endl;
    // W tym momencie rozpoczynamy działanie nieskończonej maszyny

    while(1)
    {
        switch(state)
        {
            // Na początku "wpadamy" w ten stan automatycznie za każdym razem
            // kiedy 1) włączamy program
            //       2) wyczerpaliśmy bazę danych jednego z języków
            // Jest on poglądem na zawartość dla użytkownika.
            // Ponownie czysto informacyjna sekcja pozwająca zrozumieć
            // w jaki sposób należy korzystać z programu.
            case 0:
            {
                std::cout << "\n";
                std::cout<<"*************"<<std::endl<<std::endl;
                std::cout << "Wybierz język:" << std::endl;
                std::cout << "1)  Francuski" << std::endl;
                std::cout << "2)  Angielski" << std::endl;
                std::cout << "3)  Norweski" << std::endl;
                std::cout << "4)  Wietnamski" << std::endl;
                std::cout << "5)  Chiński uproszczony" << std::endl;
                std::cout << "6)  Koreański" << std::endl;
                std::cout << "7)  Rosyjski" << std::endl;
                std::cout << "8)  Arabski" << std::endl;
                std::cout << "9)  Hebrajski" << std::endl;
                std::cout << "10) Gruziński" << std::endl;
                std::cout << "11) Węgierski" << std::endl;
                std::cout << "12) Hindi" << std::endl << std::endl;
                std::cin >> state;
                clear_cin();
                // Wykluczamy możliwość wprowadzenia innej wartości niż dostępne języki
                if(state!=1 && state!=2 && state!=3 && state!=4 && state!=5 && state!=6 && state!=7
                && state!=8 && state!=9 && state!=10 && state!=11 && state!=12)
                {
                    std::cout<<"Źle wprowadzona wartość."<<std::endl;
                    state = 0;
                    break;
                }
                std::cout << std::endl;
                break;
            }
            case 1:
            {
                float opanowanie = 0; //Zmienna lokalna zliczająca poprawne odpowiedzi
                std::ofstream wyniki_fr; //Plik tekstowy, w którym zamieszczony będzie
                // dokładny spis poprawnych i niepoprawnych odpowiedzi sprzed ostatniej sesji nauki.
                wyniki_fr.open("/Users/swtq/CLionProjects/glownyprojekt/wyniki_francuski.txt");
                //pętla która przechodzi przez wszystkie słowa w danym języku
                for (size_t i = 0; i < wczytaj_dane_csv_fr.size(); ++i)
                {
                    std::cout << "Słowo " << i + 1 << ": " << wczytaj_dane_csv_fr[i].jezyk1 << " " << std::endl
                              << std::endl;
                    std::cout << "_________________________"<<'\n';
                    std::cout<<"Napisz tłumaczenie słowa: ";
                    std::string wklad_uzytkownika;
                    // Przechowuje czas tuż przed otworzeniem inputu dla użytkownika
                    time_t czas_przed = time(NULL);
                    // W zmiennej wklad_uzytkownika będzie przetrzymywana odpowiedź
                    // następnie porównywana literka po literce z poprawnym tłumaczeniem
                    std::getline(std::cin, wklad_uzytkownika);

                    // Przechowuje czas tuż po inpucie użytkownika
                    time_t czas_po = time(NULL);

                    //std::cout << "CZAS WPISYWANIA: " << (czas_po - czas_przed) << std::endl;
                    std::cout <<"Poprawne tłumaczenie: " << wczytaj_dane_csv_fr[i].jezyk2 << "\n"<<"\n";
                    // Rzadko zdarza się, że słowa zawierają jakiekolwiek cyfry. To w intencji
                    // użytkownika leży żeby wpisać poprawne tłumaczenie.
                    // Jedyna sytuacja w której system mógłby nie działać mimo dobrych zamiarów
                    // ucznia, jest wpisanie wielkich liter, co standardowo jest rozróżniane przez c++
                    // od małych liter. Tłumaczenia słów w bazie danych są zmniejszone do małych liter,
                    // to samo musimy wykonać dla inputu użykownika:
                    transform(wklad_uzytkownika.begin(), wklad_uzytkownika.end(), wklad_uzytkownika.begin(), ::tolower);
                    std::cout<<"Twoja odpowiedź: ";
                    for(int k=0; k<wczytaj_dane_csv_fr[i].jezyk2.length(); k++)
                    {
                        std::cout<<wklad_uzytkownika[k];
                    }
                    std::cout<<"\n";
                    // Zmienna która kontroluje czy input jest taki sam jak tłumaczenie
                    // w przypadku gdy choć jedna pozycja się nie zgadza, nasza zmienna zwiększy się,
                    // przekraczając tym samym limit pozwalający jej na wejście do pętli IF, która
                    // z kolei zalicza nam odpowiedź. Robi to poprzez zwiększenie zmiennej opanowanie.
                    int tester = 0;
                    for(int j=0; j<wczytaj_dane_csv_fr[i].jezyk2.length(); j++)
                    {
                        if(wklad_uzytkownika[j]!=wczytaj_dane_csv_fr[i].jezyk2[j])
                        {
                            tester++;
                        }
                    }
                    if(tester==0)
                    {
                        std::cout<<"Dobra odpowiedź!"<<std::endl;
                        wyniki_fr<<wczytaj_dane_csv_fr[i].jezyk1<<" - "<<"Zapamiętane. ("
                        << (czas_po - czas_przed)<< " sekund)"<< std::endl;
                        opanowanie++;
                    }
                    // Tak jak na początku w treści informacyjnego wprowadzenia dla użytkownika było wspomniane,
                    // istnieje opcja zaliczenia odpowiedzi w przypadku niespodziewanego nie zaliczenia odpowiedzi.
                    // W fazie testowania okazało się, że najczęściej jest to albo literówka spowodowana pospiesznością,
                    // albo zwyczajne wpisanie innego tłumaczenia danego słowa. W pierwszym przypadku istnieje możliwość
                    // zaliczenia odpowiedzi, natomiast w tym drugim przypadku możliwość zapisu naszego wyniku tak,
                    // jak było w rzeczywistości.
                    else
                    {
                        std::cout<<"Zła odpowiedź."<<std::endl<<std::endl;
                        std::cout<<"Czy Twoim zdaniem to słowo powinno zostać zaliczone?"<<std::endl;
                        std::cout<<"1) Tak"<<std::endl;
                        std::cout<<"2) Nie"<<std::endl;
                        int y;
                        std::cin>>y; //(zmienic na getline to sie nie bedzie bugowalo.)
                        clear_cin();
                        if(y==1)
                        {
                            // Plik tekstowy jest w formie:
                            // Słowo które tłumaczyliśmy - Czy dobrze przetłumaczyliśmy
                            // tak, ażeby można było wrócić i wnikliwie (słowo po słowie)
                            // analizować ostatnie podejście.
                            std::cout<<"Odpowiedź zaliczona."<<std::endl;
                            wyniki_fr<<wczytaj_dane_csv_fr[i].jezyk1<<" - "<<"Zapamiętane. ["
                            << (czas_po - czas_przed)<< " sekund]"<< std::endl;
                            opanowanie++;
                        }
                        else
                        {
                            wyniki_fr<<wczytaj_dane_csv_fr[i].jezyk1<<" - "<<"Do nauczenia **. ("
                            << (czas_po - czas_przed)<< " sekund)"<< std::endl;
                        }
                    }
                    std::cout << "_________________________"<<'\n'<<"\n";
                }
                // Zrozumiała sama przez siebie operacja matematyczna, to znaczy ilość dobrych odpowiedzi
                // przez ilość wszystkich odpowiedzi razy sto. Jest to najszybsze podsumowanie które daje
                // użytkownikowi szansę mierzenia swojego progresu.
                std::cout<<"Opanowanie tej porcji fiszek: "<<(opanowanie/wczytaj_dane_csv_fr.size())*100<<"%"<<std::endl;
                state = 0;
                break;
            }
            // dla języka  angielskiego
            case 2:
            {
                float opanowanie = 0;
                std::ofstream wyniki_ang;
                wyniki_ang.open("/Users/swtq/CLionProjects/glownyprojekt/wyniki_angielski.txt");
                for (size_t i = 0; i < wczytaj_dane_csv.size(); ++i)
                {
                    std::cout << "Słowo " << i + 1 << ": " << wczytaj_dane_csv[i].jezyk1 << " " << std::endl
                              << std::endl;
                    std::cout << "_________________________"<<'\n';
                    std::cout<<"Napisz tłumaczenie słowa: ";
                    std::string wklad_uzytkownika;

                    time_t czas_przed = time(NULL);
                    std::getline(std::cin, wklad_uzytkownika);
                    time_t czas_po = time(NULL);

                    std::cout <<"Poprawne tłumaczenie: " << wczytaj_dane_csv[i].jezyk2 << "\n"<<"\n";
                    transform(wklad_uzytkownika.begin(), wklad_uzytkownika.end(), wklad_uzytkownika.begin(), ::tolower);
                    std::cout<<"Twoja odpowiedź: ";
                    for(int k=0; k<wczytaj_dane_csv[i].jezyk2.length(); k++)
                    {
                        std::cout<<wklad_uzytkownika[k];
                    }
                    std::cout<<"\n";
                    int tester = 0;
                    for(int j=0; j<wczytaj_dane_csv[i].jezyk2.length(); j++)
                    {
                        if(wklad_uzytkownika[j]!=wczytaj_dane_csv[i].jezyk2[j])
                        {
                            tester++;
                        }
                    }
                    if(tester==0)
                    {
                        std::cout<<"Dobra odpowiedź!"<<std::endl;
                        wyniki_ang<<wczytaj_dane_csv[i].jezyk1<<" - "<<
                        "Zapamiętane. ("<< (czas_po - czas_przed)<< " sekund)"<< std::endl;
                        opanowanie++;
                    }
                    else
                    {
                        std::cout<<"Zła odpowiedź."<<std::endl<<std::endl;
                        std::cout<<"Czy Twoim zdaniem to słowo powinno zostać zaliczone?"<<std::endl;
                        std::cout<<"1) Tak"<<std::endl;
                        std::cout<<"2) Nie"<<std::endl;
                        int y;
                        std::cin>>y;
                        clear_cin();
                        if(y==1)
                        {
                            std::cout<<"Odpowiedź zaliczona."<<std::endl;
                            wyniki_ang<<wczytaj_dane_csv[i].jezyk1<<" - "<<
                            "Zapamiętane. [" << (czas_po - czas_przed)<< " sekund]"<< std::endl;
                            opanowanie++;
                        }
                        else
                        {
                            wyniki_ang<<wczytaj_dane_csv[i].jezyk1<<" - "<<
                            "Do nauczenia **. (" << (czas_po - czas_przed)<< " sekund)"<< std::endl;
                        }
                    }
                    std::cout << "_________________________"<<'\n'<<"\n";
                }
                std::cout<<"Opanowanie tej porcji fiszek: "<<(opanowanie/wczytaj_dane_csv.size())*100<<"%"<<std::endl;
                state = 0;
                break;
            }
            // dla języka norweskiego
            case 3:
            {
                float opanowanie = 0;
                std::ofstream wyniki_norweski;
                wyniki_norweski.open("/Users/swtq/CLionProjects/glownyprojekt/wyniki_norweski.txt");
                for (size_t i = 0; i < wczytaj_dane_csv_nor.size(); ++i)
                {
                    std::cout << "Słowo " << i + 1 << ": " << wczytaj_dane_csv_nor[i].jezyk1 << " " << std::endl
                              << std::endl;
                    std::cout << "_________________________"<<'\n';
                    std::cout<<"Napisz tłumaczenie słowa: ";
                    std::string wklad_uzytkownika;

                    time_t czas_przed = time(NULL);
                    std::getline(std::cin, wklad_uzytkownika);
                    time_t czas_po = time(NULL);

                    std::cout <<"Poprawne tłumaczenie: " << wczytaj_dane_csv_nor[i].jezyk2 << "\n"<<"\n";
                    transform(wklad_uzytkownika.begin(), wklad_uzytkownika.end(), wklad_uzytkownika.begin(), ::tolower);
                    std::cout<<"Twoja odpowiedź: ";
                    for(int k=0; k<wczytaj_dane_csv_nor[i].jezyk2.length(); k++)
                    {
                        std::cout<<wklad_uzytkownika[k];
                    }
                    std::cout<<"\n";
                    int tester = 0;
                    for(int j=0; j<wczytaj_dane_csv_nor[i].jezyk2.length(); j++)
                    {
                        if(wklad_uzytkownika[j]!=wczytaj_dane_csv_nor[i].jezyk2[j])
                        {
                            tester++;
                        }
                    }
                    if(tester==0)
                    {
                        std::cout<<"Dobra odpowiedź!"<<std::endl;
                        wyniki_norweski<<wczytaj_dane_csv_nor[i].jezyk1<<" - "<<
                        "Zapamiętane. ("<< (czas_po - czas_przed)<< " sekund)"<< std::endl;
                        opanowanie++;
                    }
                    else
                    {
                        std::cout<<"Zła odpowiedź."<<std::endl<<std::endl;
                        std::cout<<"Czy Twoim zdaniem to słowo powinno zostać zaliczone?"<<std::endl;
                        std::cout<<"1) Tak"<<std::endl;
                        std::cout<<"2) Nie"<<std::endl;
                        int y;
                        std::cin>>y;
                        clear_cin();
                        if(y==1)
                        {
                            std::cout<<"Odpowiedź zaliczona."<<std::endl;
                            wyniki_norweski<<wczytaj_dane_csv_nor[i].jezyk1<<" - "<<
                            "Zapamiętane. [" << (czas_po - czas_przed)<< " sekund]"<< std::endl;
                            opanowanie++;
                        }
                        else
                        {
                            wyniki_norweski<<wczytaj_dane_csv_nor[i].jezyk1<<" - "<<
                            "Do nauczenia **. (" << (czas_po - czas_przed)<< " sekund)"<< std::endl;
                        }
                    }
                    std::cout << "_________________________"<<'\n'<<"\n";
                }
                std::cout<<"Opanowanie tej porcji fiszek: "<<(opanowanie/wczytaj_dane_csv_nor.size())*100<<"%"<<std::endl;
                state = 0;
                break;
            }
            //dla języka wietnamskiego
            case 4:
            {
                float opanowanie = 0;
                std::ofstream wyniki_wietnamski;
                wyniki_wietnamski.open("/Users/swtq/CLionProjects/glownyprojekt/wyniki_wietnamski.txt");
                for (size_t i = 0; i < wczytaj_dane_csv_wiet.size(); ++i)
                {
                    std::cout << "Słowo " << i + 1 << ": " << wczytaj_dane_csv_wiet[i].jezyk1 << " " << std::endl
                              << std::endl;
                    std::cout << "_________________________"<<'\n';
                    std::cout<<"Napisz tłumaczenie słowa: ";
                    std::string wklad_uzytkownika;

                    time_t czas_przed = time(NULL);
                    std::getline(std::cin, wklad_uzytkownika);
                    time_t czas_po = time(NULL);

                    std::cout <<"Poprawne tłumaczenie: " << wczytaj_dane_csv_wiet[i].jezyk2 << "\n"<<"\n";
                    transform(wklad_uzytkownika.begin(), wklad_uzytkownika.end(), wklad_uzytkownika.begin(), ::tolower);
                    std::cout<<"Twoja odpowiedź: ";
                    for(int k=0; k<wczytaj_dane_csv_wiet[i].jezyk2.length(); k++)
                    {
                        std::cout<<wklad_uzytkownika[k];
                    }
                    std::cout<<"\n";
                    int tester = 0;
                    for(int j=0; j<wczytaj_dane_csv_wiet[i].jezyk2.length(); j++)
                    {
                        if(wklad_uzytkownika[j]!=wczytaj_dane_csv_wiet[i].jezyk2[j])
                        {
                            tester++;
                        }
                    }
                    if(tester==0)
                    {
                        std::cout<<"Dobra odpowiedź!"<<std::endl;
                        wyniki_wietnamski<<wczytaj_dane_csv_wiet[i].jezyk1<<" - "<<
                        "Zapamiętane. ("<< (czas_po - czas_przed)<< " sekund)"<< std::endl;
                        opanowanie++;
                    }
                    else
                    {
                        std::cout<<"Zła odpowiedź."<<std::endl<<std::endl;
                        std::cout<<"Czy Twoim zdaniem to słowo powinno zostać zaliczone?"<<std::endl;
                        std::cout<<"1) Tak"<<std::endl;
                        std::cout<<"2) Nie"<<std::endl;
                        int y;
                        std::cin>>y;
                        clear_cin();
                        if(y==1)
                        {
                            std::cout<<"Odpowiedź zaliczona."<<std::endl;
                            wyniki_wietnamski<<wczytaj_dane_csv_wiet[i].jezyk1<<" - "<<
                            "Zapamiętane. [" << (czas_po - czas_przed)<< " sekund]"<< std::endl;
                            opanowanie++;
                        }
                        else
                        {
                            wyniki_wietnamski<<wczytaj_dane_csv_wiet[i].jezyk1<<" - "<<
                            "Do nauczenia **. (" << (czas_po - czas_przed)<< " sekund)"<< std::endl;
                        }
                    }
                    std::cout << "_________________________"<<'\n'<<"\n";
                }
                std::cout<<"Opanowanie tej porcji fiszek: "<<(opanowanie/wczytaj_dane_csv_wiet.size())*100<<"%"<<std::endl;
                state = 0;
                break;
            }
            // dla języka chińskiego uproszczonego
            case 5:
            {
                float opanowanie = 0;
                std::ofstream wyniki_chinski;
                wyniki_chinski.open("/Users/swtq/CLionProjects/glownyprojekt/wyniki_chinski.txt");
                for (size_t i = 0; i < wczytaj_dane_csv_chin.size(); ++i)
                {
                    std::cout << "Słowo " << i + 1 << ": " << wczytaj_dane_csv_chin[i].jezyk1 << " " << std::endl
                              << std::endl;
                    std::cout << "_________________________"<<'\n';
                    std::cout<<"Napisz tłumaczenie słowa: ";
                    std::string wklad_uzytkownika;

                    time_t czas_przed = time(NULL);
                    std::getline(std::cin, wklad_uzytkownika);
                    time_t czas_po = time(NULL);

                    std::cout <<"Poprawne tłumaczenie: " << wczytaj_dane_csv_chin[i].jezyk2 << "\n"<<"\n";
                    transform(wklad_uzytkownika.begin(), wklad_uzytkownika.end(), wklad_uzytkownika.begin(), ::tolower);
                    std::cout<<"Twoja odpowiedź: ";
                    for(int k=0; k<wczytaj_dane_csv_chin[i].jezyk2.length(); k++)
                    {
                        std::cout<<wklad_uzytkownika[k];
                    }
                    std::cout<<"\n";
                    int tester = 0;
                    for(int j=0; j<wczytaj_dane_csv_chin[i].jezyk2.length(); j++)
                    {
                        if(wklad_uzytkownika[j]!=wczytaj_dane_csv_chin[i].jezyk2[j])
                        {
                            tester++;
                        }
                    }
                    if(tester==0)
                    {
                        std::cout<<"Dobra odpowiedź!"<<std::endl;
                        wyniki_chinski<<wczytaj_dane_csv_chin[i].jezyk1<<" - "<<
                        "Zapamiętane. ("<< (czas_po - czas_przed)<< " sekund)"<< std::endl;
                        opanowanie++;
                    }
                    else
                    {
                        std::cout<<"Zła odpowiedź."<<std::endl<<std::endl;
                        std::cout<<"Czy Twoim zdaniem to słowo powinno zostać zaliczone?"<<std::endl;
                        std::cout<<"1) Tak"<<std::endl;
                        std::cout<<"2) Nie"<<std::endl;
                        int y;
                        std::cin>>y;
                        clear_cin();
                        if(y==1)
                        {
                            std::cout<<"Odpowiedź zaliczona."<<std::endl;
                            wyniki_chinski<<wczytaj_dane_csv_chin[i].jezyk1<<" - "<<
                            "Zapamiętane. [" << (czas_po - czas_przed)<< " sekund]"<< std::endl;
                            opanowanie++;
                        }
                        else
                        {
                            wyniki_chinski<<wczytaj_dane_csv_chin[i].jezyk1<<" - "<<
                            "Do nauczenia **. (" << (czas_po - czas_przed)<< " sekund)"<< std::endl;
                        }
                    }
                    std::cout << "_________________________"<<'\n'<<"\n";
                }
                std::cout<<"Opanowanie tej porcji fiszek: "<<(opanowanie/wczytaj_dane_csv_chin.size())*100<<"%"<<std::endl;
                state = 0;
                break;
            }
            // dla języka koreańskiego
            case 6:
            {
                float opanowanie = 0;
                std::ofstream wyniki_koreanski;
                wyniki_koreanski.open("/Users/swtq/CLionProjects/glownyprojekt/wyniki_koreanski.txt");
                for (size_t i = 0; i < wczytaj_dane_csv_kor.size(); ++i)
                {
                    std::cout << "Słowo " << i + 1 << ": " << wczytaj_dane_csv_kor[i].jezyk1 << " " << std::endl
                              << std::endl;
                    std::cout << "_________________________"<<'\n';
                    std::cout<<"Napisz tłumaczenie słowa: ";
                    std::string wklad_uzytkownika;

                    time_t czas_przed = time(NULL);
                    std::getline(std::cin, wklad_uzytkownika);
                    time_t czas_po = time(NULL);

                    std::cout <<"Poprawne tłumaczenie: " << wczytaj_dane_csv_kor[i].jezyk2 << "\n"<<"\n";
                    transform(wklad_uzytkownika.begin(), wklad_uzytkownika.end(), wklad_uzytkownika.begin(), ::tolower);
                    std::cout<<"Twoja odpowiedź: ";
                    for(int k=0; k<wczytaj_dane_csv_kor[i].jezyk2.length(); k++)
                    {
                        std::cout<<wklad_uzytkownika[k];
                    }
                    std::cout<<"\n";
                    int tester = 0;
                    for(int j=0; j<wczytaj_dane_csv_kor[i].jezyk2.length(); j++)
                    {
                        if(wklad_uzytkownika[j]!=wczytaj_dane_csv_kor[i].jezyk2[j])
                        {
                            tester++;
                        }
                    }
                    if(tester==0)
                    {
                        std::cout<<"Dobra odpowiedź!"<<std::endl;
                        wyniki_koreanski<<wczytaj_dane_csv_kor[i].jezyk1<<" - "<<
                        "Zapamiętane. ("<< (czas_po - czas_przed)<< " sekund)"<< std::endl;
                        opanowanie++;
                    }
                    else
                    {
                        std::cout<<"Zła odpowiedź."<<std::endl<<std::endl;
                        std::cout<<"Czy Twoim zdaniem to słowo powinno zostać zaliczone?"<<std::endl;
                        std::cout<<"1) Tak"<<std::endl;
                        std::cout<<"2) Nie"<<std::endl;
                        int y;
                        std::cin>>y;
                        clear_cin();
                        if(y==1)
                        {
                            std::cout<<"Odpowiedź zaliczona."<<std::endl;
                            wyniki_koreanski<<wczytaj_dane_csv_kor[i].jezyk1<<" - "<<
                            "Zapamiętane. [" << (czas_po - czas_przed)<< " sekund]"<< std::endl;
                            opanowanie++;
                        }
                        else
                        {
                            wyniki_koreanski<<wczytaj_dane_csv_kor[i].jezyk1<<" - "<<
                            "Do nauczenia **. (" << (czas_po - czas_przed)<< " sekund)"<< std::endl;
                        }
                    }
                    std::cout << "_________________________"<<'\n'<<"\n";
                }
                std::cout<<"Opanowanie tej porcji fiszek: "<<(opanowanie/wczytaj_dane_csv_kor.size())*100<<"%"<<std::endl;
                state = 0;
                break;
            }
            // dla języka rosyjskiego
            case 7:
            {
                float opanowanie = 0;
                std::ofstream wyniki_rosyjski;
                wyniki_rosyjski.open("/Users/swtq/CLionProjects/glownyprojekt/wyniki_rosyjski.txt");
                for (size_t i = 0; i < wczytaj_dane_csv_ros.size(); ++i)
                {
                    std::cout << "Słowo " << i + 1 << ": " << wczytaj_dane_csv_ros[i].jezyk1 << " " << std::endl
                              << std::endl;
                    std::cout << "_________________________"<<'\n';
                    std::cout<<"Napisz tłumaczenie słowa: ";
                    std::string wklad_uzytkownika;

                    time_t czas_przed = time(NULL);
                    std::getline(std::cin, wklad_uzytkownika);
                    time_t czas_po = time(NULL);

                    std::cout <<"Poprawne tłumaczenie: " << wczytaj_dane_csv_ros[i].jezyk2 << "\n"<<"\n";
                    transform(wklad_uzytkownika.begin(), wklad_uzytkownika.end(), wklad_uzytkownika.begin(), ::tolower);
                    std::cout<<"Twoja odpowiedź: ";
                    for(int k=0; k<wczytaj_dane_csv_ros[i].jezyk2.length(); k++)
                    {
                        std::cout<<wklad_uzytkownika[k];
                    }
                    std::cout<<"\n";
                    int tester = 0;
                    for(int j=0; j<wczytaj_dane_csv_ros[i].jezyk2.length(); j++)
                    {
                        if(wklad_uzytkownika[j]!=wczytaj_dane_csv_ros[i].jezyk2[j])
                        {
                            tester++;
                        }
                    }
                    if(tester==0)
                    {
                        std::cout<<"Dobra odpowiedź!"<<std::endl;
                        wyniki_rosyjski<<wczytaj_dane_csv_ros[i].jezyk1<<" - "<<
                        "Zapamiętane. ("<< (czas_po - czas_przed)<< " sekund)"<< std::endl;
                        opanowanie++;
                    }
                    else
                    {
                        std::cout<<"Zła odpowiedź."<<std::endl<<std::endl;
                        std::cout<<"Czy Twoim zdaniem to słowo powinno zostać zaliczone?"<<std::endl;
                        std::cout<<"1) Tak"<<std::endl;
                        std::cout<<"2) Nie"<<std::endl;
                        int y;
                        std::cin>>y;
                        clear_cin();
                        if(y==1)
                        {
                            std::cout<<"Odpowiedź zaliczona."<<std::endl;
                            wyniki_rosyjski<<wczytaj_dane_csv_ros[i].jezyk1<<" - "<<
                            "Zapamiętane. [" << (czas_po - czas_przed)<< " sekund]"<< std::endl;
                            opanowanie++;
                        }
                        else
                        {
                            wyniki_rosyjski<<wczytaj_dane_csv_ros[i].jezyk1<<" - "<<
                            "Do nauczenia **. (" << (czas_po - czas_przed)<< " sekund)"<< std::endl;
                        }
                    }
                    std::cout << "_________________________"<<'\n'<<"\n";
                }
                std::cout<<"Opanowanie tej porcji fiszek: "<<(opanowanie/wczytaj_dane_csv_ros.size())*100<<"%"<<std::endl;
                state = 0;
                break;
            }
            // dla języka arabskiego
            case 8:
            {
                float opanowanie = 0;
                std::ofstream wyniki_arabski;
                wyniki_arabski.open("/Users/swtq/CLionProjects/glownyprojekt/wyniki_arabski.txt");
                for (size_t i = 0; i < wczytaj_dane_csv_ara.size(); ++i)
                {
                    std::cout << "Słowo " << i + 1 << ": " << wczytaj_dane_csv_ara[i].jezyk1 << " " << std::endl
                              << std::endl;
                    std::cout << "_________________________"<<'\n';
                    std::cout<<"Napisz tłumaczenie słowa: ";
                    std::string wklad_uzytkownika;

                    time_t czas_przed = time(NULL);
                    std::getline(std::cin, wklad_uzytkownika);
                    time_t czas_po = time(NULL);

                    std::cout <<"Poprawne tłumaczenie: " << wczytaj_dane_csv_ara[i].jezyk2 << "\n"<<"\n";
                    transform(wklad_uzytkownika.begin(), wklad_uzytkownika.end(), wklad_uzytkownika.begin(), ::tolower);
                    std::cout<<"Twoja odpowiedź: ";
                    for(int k=0; k<wczytaj_dane_csv_ara[i].jezyk2.length(); k++)
                    {
                        std::cout<<wklad_uzytkownika[k];
                    }
                    std::cout<<"\n";
                    int tester = 0;
                    for(int j=0; j<wczytaj_dane_csv_ara[i].jezyk2.length(); j++)
                    {
                        if(wklad_uzytkownika[j]!=wczytaj_dane_csv_ara[i].jezyk2[j])
                        {
                            tester++;
                        }
                    }
                    if(tester==0)
                    {
                        std::cout<<"Dobra odpowiedź!"<<std::endl;
                        wyniki_arabski<<wczytaj_dane_csv_ara[i].jezyk1<<" - "<<
                        "Zapamiętane. ("<< (czas_po - czas_przed)<< " sekund)"<< std::endl;
                        opanowanie++;
                    }
                    else
                    {
                        std::cout<<"Zła odpowiedź."<<std::endl<<std::endl;
                        std::cout<<"Czy Twoim zdaniem to słowo powinno zostać zaliczone?"<<std::endl;
                        std::cout<<"1) Tak"<<std::endl;
                        std::cout<<"2) Nie"<<std::endl;
                        int y;
                        std::cin>>y;
                        clear_cin();
                        if(y==1)
                        {
                            std::cout<<"Odpowiedź zaliczona."<<std::endl;
                            wyniki_arabski<<wczytaj_dane_csv_ara[i].jezyk1<<" - "<<
                            "Zapamiętane. [" << (czas_po - czas_przed)<< " sekund]"<< std::endl;
                            opanowanie++;
                        }
                        else
                        {
                            wyniki_arabski<<wczytaj_dane_csv_ara[i].jezyk1<<" - "<<
                            "Do nauczenia **. (" << (czas_po - czas_przed)<< " sekund)"<< std::endl;
                        }
                    }
                    std::cout << "_________________________"<<'\n'<<"\n";
                }
                std::cout<<"Opanowanie tej porcji fiszek: "<<(opanowanie/wczytaj_dane_csv_ara.size())*100<<"%"<<std::endl;
                state = 0;
                break;
            }
            // dla języka hebrajskiego
            case 9:
            {
                float opanowanie = 0;
                std::ofstream wyniki_hebrajski;
                wyniki_hebrajski.open("/Users/swtq/CLionProjects/glownyprojekt/wyniki_hebrajski.txt");
                for (size_t i = 0; i < wczytaj_dane_csv_heb.size(); ++i)
                {
                    std::cout << "Słowo " << i + 1 << ": " << wczytaj_dane_csv_heb[i].jezyk1 << " " << std::endl
                              << std::endl;
                    std::cout << "_________________________"<<'\n';
                    std::cout<<"Napisz tłumaczenie słowa: ";
                    std::string wklad_uzytkownika;

                    time_t czas_przed = time(NULL);
                    std::getline(std::cin, wklad_uzytkownika);
                    time_t czas_po = time(NULL);

                    std::cout <<"Poprawne tłumaczenie: " << wczytaj_dane_csv_heb[i].jezyk2 << "\n"<<"\n";
                    transform(wklad_uzytkownika.begin(), wklad_uzytkownika.end(), wklad_uzytkownika.begin(), ::tolower);
                    std::cout<<"Twoja odpowiedź: ";
                    for(int k=0; k<wczytaj_dane_csv_heb[i].jezyk2.length(); k++)
                    {
                        std::cout<<wklad_uzytkownika[k];
                    }
                    std::cout<<"\n";
                    int tester = 0;
                    for(int j=0; j<wczytaj_dane_csv_heb[i].jezyk2.length(); j++)
                    {
                        if(wklad_uzytkownika[j]!=wczytaj_dane_csv_heb[i].jezyk2[j])
                        {
                            tester++;
                        }
                    }
                    if(tester==0)
                    {
                        std::cout<<"Dobra odpowiedź!"<<std::endl;
                        wyniki_hebrajski<<wczytaj_dane_csv_heb[i].jezyk1<<" - "<<
                        "Zapamiętane. ("<< (czas_po - czas_przed)<< " sekund)"<< std::endl;
                        opanowanie++;
                    }
                    else
                    {
                        std::cout<<"Zła odpowiedź."<<std::endl<<std::endl;
                        std::cout<<"Czy Twoim zdaniem to słowo powinno zostać zaliczone?"<<std::endl;
                        std::cout<<"1) Tak"<<std::endl;
                        std::cout<<"2) Nie"<<std::endl;
                        int y;
                        std::cin>>y;
                        clear_cin();
                        if(y==1)
                        {
                            std::cout<<"Odpowiedź zaliczona."<<std::endl;
                            wyniki_hebrajski<<wczytaj_dane_csv_heb[i].jezyk1<<" - "<<
                            "Zapamiętane. [" << (czas_po - czas_przed)<< " sekund]"<< std::endl;
                            opanowanie++;
                        }
                        else
                        {
                            wyniki_hebrajski<<wczytaj_dane_csv_heb[i].jezyk1<<" - "<<
                            "Do nauczenia **. (" << (czas_po - czas_przed)<< " sekund)"<< std::endl;
                        }
                    }
                    std::cout << "_________________________"<<'\n'<<"\n";
                }
                std::cout<<"Opanowanie tej porcji fiszek: "<<(opanowanie/wczytaj_dane_csv_heb.size())*100<<"%"<<std::endl;
                state = 0;
                break;
            }
            // dla języka gruzińskiego
            case 10:
            {
                float opanowanie = 0;
                std::ofstream wyniki_gruzinski;
                wyniki_gruzinski.open("/Users/swtq/CLionProjects/glownyprojekt/wyniki_gruzinski.txt");
                for (size_t i = 0; i < wczytaj_dane_csv_gru.size(); ++i)
                {
                    std::cout << "Słowo " << i + 1 << ": " << wczytaj_dane_csv_gru[i].jezyk1 << " " << std::endl
                              << std::endl;
                    std::cout << "_________________________"<<'\n';
                    std::cout<<"Napisz tłumaczenie słowa: ";
                    std::string wklad_uzytkownika;

                    time_t czas_przed = time(NULL);
                    std::getline(std::cin, wklad_uzytkownika);
                    time_t czas_po = time(NULL);

                    std::cout <<"Poprawne tłumaczenie: " << wczytaj_dane_csv_gru[i].jezyk2 << "\n"<<"\n";
                    transform(wklad_uzytkownika.begin(), wklad_uzytkownika.end(), wklad_uzytkownika.begin(), ::tolower);
                    std::cout<<"Twoja odpowiedź: ";
                    for(int k=0; k<wczytaj_dane_csv_gru[i].jezyk2.length(); k++)
                    {
                        std::cout<<wklad_uzytkownika[k];
                    }
                    std::cout<<"\n";
                    int tester = 0;
                    for(int j=0; j<wczytaj_dane_csv_gru[i].jezyk2.length(); j++)
                    {
                        if(wklad_uzytkownika[j]!=wczytaj_dane_csv_gru[i].jezyk2[j])
                        {
                            tester++;
                        }
                    }
                    if(tester==0)
                    {
                        std::cout<<"Dobra odpowiedź!"<<std::endl;
                        wyniki_gruzinski<<wczytaj_dane_csv_gru[i].jezyk1<<" - "<<
                        "Zapamiętane. ("<< (czas_po - czas_przed)<< " sekund)"<< std::endl;
                        opanowanie++;
                    }
                    else
                    {
                        std::cout<<"Zła odpowiedź."<<std::endl<<std::endl;
                        std::cout<<"Czy Twoim zdaniem to słowo powinno zostać zaliczone?"<<std::endl;
                        std::cout<<"1) Tak"<<std::endl;
                        std::cout<<"2) Nie"<<std::endl;
                        int y;
                        std::cin>>y;
                        clear_cin();
                        if(y==1)
                        {
                            std::cout<<"Odpowiedź zaliczona."<<std::endl;
                            wyniki_gruzinski<<wczytaj_dane_csv_gru[i].jezyk1<<" - "<<
                            "Zapamiętane. [" << (czas_po - czas_przed)<< " sekund]"<< std::endl;
                            opanowanie++;
                        }
                        else
                        {
                            wyniki_gruzinski<<wczytaj_dane_csv_gru[i].jezyk1<<" - "<<
                            "Do nauczenia **. (" << (czas_po - czas_przed)<< " sekund)"<< std::endl;
                        }
                    }
                    std::cout << "_________________________"<<'\n'<<"\n";
                }
                std::cout<<"Opanowanie tej porcji fiszek: "<<(opanowanie/wczytaj_dane_csv_gru.size())*100<<"%"<<std::endl;
                state = 0;
                break;
            }
            // dla języka węgierskiego
            case 11:
            {
                float opanowanie = 0;
                std::ofstream wyniki_wegierski;
                wyniki_wegierski.open("/Users/swtq/CLionProjects/glownyprojekt/wyniki_wegierski.txt");
                for (size_t i = 0; i < wczytaj_dane_csv_weg.size(); ++i)
                {
                    std::cout << "Słowo " << i + 1 << ": " << wczytaj_dane_csv_weg[i].jezyk1 << " " << std::endl
                              << std::endl;
                    std::cout << "_________________________"<<'\n';
                    std::cout<<"Napisz tłumaczenie słowa: ";
                    std::string wklad_uzytkownika;

                    time_t czas_przed = time(NULL);
                    std::getline(std::cin, wklad_uzytkownika);
                    time_t czas_po = time(NULL);

                    std::cout <<"Poprawne tłumaczenie: " << wczytaj_dane_csv_weg[i].jezyk2 << "\n"<<"\n";
                    transform(wklad_uzytkownika.begin(), wklad_uzytkownika.end(), wklad_uzytkownika.begin(), ::tolower);
                    std::cout<<"Twoja odpowiedź: ";
                    for(int k=0; k<wczytaj_dane_csv_weg[i].jezyk2.length(); k++)
                    {
                        std::cout<<wklad_uzytkownika[k];
                    }
                    std::cout<<"\n";
                    int tester = 0;
                    for(int j=0; j<wczytaj_dane_csv_weg[i].jezyk2.length(); j++)
                    {
                        if(wklad_uzytkownika[j]!=wczytaj_dane_csv_weg[i].jezyk2[j])
                        {
                            tester++;
                        }
                    }
                    if(tester==0)
                    {
                        std::cout<<"Dobra odpowiedź!"<<std::endl;
                        wyniki_wegierski<<wczytaj_dane_csv_weg[i].jezyk1<<" - "<<
                        "Zapamiętane. ("<< (czas_po - czas_przed)<< " sekund)"<< std::endl;
                        opanowanie++;
                    }
                    else
                    {
                        std::cout<<"Zła odpowiedź."<<std::endl<<std::endl;
                        std::cout<<"Czy Twoim zdaniem to słowo powinno zostać zaliczone?"<<std::endl;
                        std::cout<<"1) Tak"<<std::endl;
                        std::cout<<"2) Nie"<<std::endl;
                        int y;
                        std::cin>>y;
                        clear_cin();
                        if(y==1)
                        {
                            std::cout<<"Odpowiedź zaliczona."<<std::endl;
                            wyniki_wegierski<<wczytaj_dane_csv_weg[i].jezyk1<<" - "<<
                            "Zapamiętane. [" << (czas_po - czas_przed)<< " sekund]"<< std::endl;
                            opanowanie++;
                        }
                        else
                        {
                            wyniki_wegierski<<wczytaj_dane_csv_weg[i].jezyk1<<" - "<<
                            "Do nauczenia **. (" << (czas_po - czas_przed)<< " sekund)"<< std::endl;
                        }
                    }
                    std::cout << "_________________________"<<'\n'<<"\n";
                }
                std::cout<<"Opanowanie tej porcji fiszek: "<<(opanowanie/wczytaj_dane_csv_weg.size())*100<<"%"<<std::endl;
                state = 0;
                break;
            }
            // dla języka hindi
            case 12:
            {
                float opanowanie = 0;
                std::ofstream wyniki_hindi;
                wyniki_hindi.open("/Users/swtq/CLionProjects/glownyprojekt/wyniki_hindi.txt");
                for (size_t i = 0; i < wczytaj_dane_csv_hin.size(); ++i)
                {
                    std::cout << "Słowo " << i + 1 << ": " << wczytaj_dane_csv_hin[i].jezyk1 << " " << std::endl
                              << std::endl;
                    std::cout << "_________________________"<<'\n';
                    std::cout<<"Napisz tłumaczenie słowa: ";
                    std::string wklad_uzytkownika;

                    time_t czas_przed = time(NULL);
                    std::getline(std::cin, wklad_uzytkownika);
                    time_t czas_po = time(NULL);

                    std::cout <<"Poprawne tłumaczenie: " << wczytaj_dane_csv_hin[i].jezyk2 << "\n"<<"\n";
                    transform(wklad_uzytkownika.begin(), wklad_uzytkownika.end(), wklad_uzytkownika.begin(), ::tolower);
                    std::cout<<"Twoja odpowiedź: ";
                    for(int k=0; k<wczytaj_dane_csv_hin[i].jezyk2.length(); k++)
                    {
                        std::cout<<wklad_uzytkownika[k];
                    }
                    std::cout<<"\n";
                    int tester = 0;
                    for(int j=0; j<wczytaj_dane_csv_hin[i].jezyk2.length(); j++)
                    {
                        if(wklad_uzytkownika[j]!=wczytaj_dane_csv_hin[i].jezyk2[j])
                        {
                            tester++;
                        }
                    }
                    if(tester==0)
                    {
                        std::cout<<"Dobra odpowiedź!"<<std::endl;
                        wyniki_hindi<<wczytaj_dane_csv_hin[i].jezyk1<<" - "<<
                        "Zapamiętane. ("<< (czas_po - czas_przed)<< " sekund)"<< std::endl;
                        opanowanie++;
                    }
                    else
                    {
                        std::cout<<"Zła odpowiedź."<<std::endl<<std::endl;
                        std::cout<<"Czy Twoim zdaniem to słowo powinno zostać zaliczone?"<<std::endl;
                        std::cout<<"1) Tak"<<std::endl;
                        std::cout<<"2) Nie"<<std::endl;
                        int y;
                        std::cin>>y;
                        clear_cin();
                        if(y==1)
                        {
                            std::cout<<"Odpowiedź zaliczona."<<std::endl;
                            wyniki_hindi<<wczytaj_dane_csv_hin[i].jezyk1<<" - "<<
                            "Zapamiętane. [" << (czas_po - czas_przed)<< " sekund]"<< std::endl;
                            opanowanie++;
                        }
                        else
                        {
                            wyniki_hindi<<wczytaj_dane_csv_hin[i].jezyk1<<" - "<<
                            "Do nauczenia **. (" << (czas_po - czas_przed)<< " sekund)"<< std::endl;
                        }
                    }
                    std::cout << "_________________________"<<'\n'<<"\n";
                }
                std::cout<<"Opanowanie tej porcji fiszek: "<<(opanowanie/wczytaj_dane_csv_hin.size())*100<<"%"<<std::endl;
                state = 0;
                break;
            }
        }
    }
    return 0;
}