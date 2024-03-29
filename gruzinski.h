//
// Created by Paweł Świątek on 10/06/2022.
//

#ifndef GLOWNYPROJEKT_GRUZINSKI_H
#define GLOWNYPROJEKT_GRUZINSKI_H

#endif //GLOWNYPROJEKT_GRUZINSKI_H

std::vector<tlumaczenie>wczytaj_dane_csv_gru;

void przeklad_gruzinski()
{
    std::ifstream data("/Users/swtq/CLionProjects/glownyprojekt/jezyki_excel/Gru_slowa.csv");
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
        wczytaj_dane_csv_gru.push_back(tlum);
    }
}
