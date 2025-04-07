#include "utils.h"

int numarZileInLuna(int luna, int an)
{
    switch(luna)
    {
        case 4: case 6: case 9: case 11: return 30;
        case 2: return (an % 4 == 0 && (an % 100 != 0 || an % 400 == 0)) ? 29 : 28;
        default: return 31;
    }
}

int calculeazaDiferentaZile(const std::string& check_in, const std::string& check_out)
{
    int zi1, luna1, an1;
    int zi2, luna2, an2;

    an1 = std::stoi(check_in.substr(0, 4));
    luna1 = std::stoi(check_in.substr(5, 2));
    zi1 = std::stoi(check_in.substr(8, 2));

    an2 = std::stoi(check_out.substr(0, 4));
    luna2 = std::stoi(check_out.substr(5, 2));
    zi2 = std::stoi(check_out.substr(8, 2));

    int zile = 0;

    while (an1 < an2 || luna1 < luna2 || zi1 < zi2)
    {
        zi1++;
        zile++;
        if (zi1 > numarZileInLuna(luna1, an1))
        {
            zi1 = 1;
            luna1++;
            if (luna1 > 12)
            {
                luna1 = 1;
                an1++;
            }
        }
    }

    return zile;
}