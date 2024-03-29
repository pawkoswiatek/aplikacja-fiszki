//
// Created by Paweł Świątek on 10/06/2022.
//

#ifndef GLOWNYPROJEKT_WEGIERSKI_H
#define GLOWNYPROJEKT_WEGIERSKI_H

#endif //GLOWNYPROJEKT_WEGIERSKI_H

std::vector<tlumaczenie>wczytaj_dane_csv_weg;

void przeklad_wegierski()
{
    std::ifstream data("/Users/swtq/CLionProjects/glownyprojekt/jezyki_excel/Weg_slowa.csv");
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
        //int x;
        getline(iss, tlum.jezyk1, ';');
        getline(iss, tlum.jezyk2, ';');
        getline(iss, token, ';');
        int conversion = atoi(token.c_str());
        tlum.set_lvl(conversion);
        wczytaj_dane_csv_weg.push_back(tlum);
    }
}