//
// Created by Paweł Świątek on 08/06/2022.
//

#ifndef GLOWNYPROJEKT_ANGIELSKI_H
#define GLOWNYPROJEKT_ANGIELSKI_H

#endif //GLOWNYPROJEKT_ANGIELSKI_H

#include <string>
#include <sstream>

#include <cstring>

std::vector<tlumaczenie>wczytaj_dane_csv;

void przeklad_angielski()
{
    std::ifstream data("/Users/swtq/CLionProjects/glownyprojekt/jezyki_excel/Ang_slowa.csv");
    if (!data.is_open())
    {
        exit(EXIT_FAILURE);
    }
    std::string str;
    while (getline(data, str))
    {
        tlumaczenie tlum;
        std::istringstream iss(str);
        std::string token;
        getline(iss, tlum.jezyk1, ';');
        getline(iss, tlum.jezyk2, ';');
        getline(iss, token, ';');
        int conversion;
        conversion = atoi(token.c_str());
        tlum.set_lvl(conversion);
        wczytaj_dane_csv.push_back(tlum);
    }
}