//
// Created by Paweł Świątek on 08/06/2022.
//

#ifndef GLOWNYPROJEKT_FRANCUSKI_H
#define GLOWNYPROJEKT_FRANCUSKI_H

#endif //GLOWNYPROJEKT_FRANCUSKI_H
#include <string>
#include <sstream>
//#include <map>
#include <cstring>
//#include <locale.h>
std::vector<tlumaczenie>wczytaj_dane_csv_fr;

void przeklad_francuski()
{
    std::ifstream data("/Users/swtq/CLionProjects/glownyprojekt/jezyki_excel/Fra_slowa.csv");
    if (!data.is_open()) {
        exit(EXIT_FAILURE);
    }
    std::string str;
    while (getline(data, str)) {
        tlumaczenie tlum;
        std::istringstream iss(str);
        std::string token;
        getline(iss, tlum.jezyk1, ';');
        getline(iss, tlum.jezyk2, ';');
        getline(iss, token, ';');
        int conversion = atoi(token.c_str());
        tlum.set_lvl(conversion);
        wczytaj_dane_csv_fr.push_back(tlum);
    }
}