#include "Hotel.h"
#include "utils.h"
#include <iostream>
#include <limits>

Hotel::Hotel() {
    int i, nrCamere=5; //mai multe camere vor fi adaugate in viitor!
    Camera cam1, cam2, cam3, cam4, cam5;
    camere.push_back(cam1);
    camere.push_back(cam2);
    camere.push_back(cam3);
    camere.push_back(cam4);
    camere.push_back(cam5);
    camere[0].setNumar(1); camere[0].setTip("Single"); camere[0].setPret(100); camere[0].setDisponibilitate(true); 
    camere[1].setNumar(2); camere[1].setTip("Double"); camere[1].setPret(200); camere[1].setDisponibilitate(true);
    camere[2].setNumar(3); camere[2].setTip("Triple"); camere[2].setPret(300); camere[2].setDisponibilitate(true);
    camere[3].setNumar(4); camere[3].setTip("Quadruple"); camere[3].setPret(400); camere[3].setDisponibilitate(true);
    camere[4].setNumar(5); camere[4].setTip("Suite"); camere[4].setPret(500); camere[4].setDisponibilitate(true);
};

Hotel::~Hotel() {};

void Hotel::ruleaza()
{
    int opt;
    std::cout<<"Bun venit! Alege contul in care doresti sa te conectezi"<<std::endl;
    std::cout<<"1. Client"<<std::endl;
    std::cout<<"2. Administrator"<<std::endl;
    std::cout<<"3. Renunta."<<std::endl;
    std::cin>>opt;
    switch(opt) { 
            case 1:
                meniuClient();
                ruleaza();
                break;
            case 2:
                meniuAdministrator(); //De adaugat
                ruleaza();
                break;
            case 3:
                std::cout<<"La revedere!"<<std::endl;
                break;
            default:
                std::cout<<"Optiune invalida. Te rog sa alegi din nou"<<std::endl;
                ruleaza();
                break;
        }
    
};

void Hotel::meniuClient()
{
    int choice;
    do {
    std::cout<<"Ce doriti sa faceti?"<<std::endl;
    std::cout<<"1. Efectueaza o rezervare."<<std::endl;
    std::cout<<"2. Vezi camerele disponibile"<<std::endl;
    std::cout<<"3. De adaugat."<<std::endl;
    std::cout<<"4. Inapoi."<<std::endl;
    std::cout<<"Alege:"<<std::endl;
    std::cin>>choice;
    switch (choice)
    {
    case 1:
        efectueazaRezervare();
        break;
    case 2:
        veziCamereDisponibile();
        break;
    case 3:
        //de adaugat
        break;
    case 4:
        std::cout<<"Revenim la meniul principal"<<std::endl;
    default:
        break;
    }
   }while(choice!=4);
}
void Hotel::meniuAdministrator()
{
    std::cout<<"To be continued..."<<std::endl;
}

void Hotel::adaugaRezervare(Camera &camera, std::string& data_check_in, std::string& data_check_out)
{
    Client client;
    std::string nume, email;
    int varsta;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Curata buffer-ul pentru a nu sari peste getline
    
    std::cout<<"Introduceti numele si prenumele: "<<std::endl;
    std::getline(std::cin, nume);
    client.setNume(nume);

    std::cout<<"Introduceti email-ul: "<<std::endl;
    std::cin>>email;
    client.setEmail(email);

    std::cout<<"Introduceti varsta: "<<std::endl;
    std::cin>>varsta;
    client.setVarsta(varsta);

    std::string metoda_plata, observatii;

    std::cout<<"Selectati metoda de plata (Numerar/Card/Transfer bancar): "<<std::endl;
    std::cin>>metoda_plata;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Curata buffer-ul pentru a nu sari peste getline


    std::cout << "Observatii (optional): ";
    std::getline(std::cin, observatii);

    //Calculeaza pretul total al rezervarii
    int nopti=calculeazaDiferentaZile(data_check_in,data_check_out);

    double pret_total;
    pret_total=nopti*camera.getPret();

    double discount=0.0;
    pret_total-=pret_total*discount/100; //Momentan fara discount - functionalitate viitoare

    int id_rezervare=rezervari.size()+1;

    Rezervare r(id_rezervare, data_check_in, data_check_out, pret_total, client, camera, metoda_plata, observatii, discount, nopti);
    rezervari.push_back(r);

    camera.setDisponibilitate(false);

    std::cout << "Rezervarea a fost efectuata cu succes! Detalii:\n";
    r.afisareDetalii();

}
void Hotel::efectueazaRezervare()
{
    bool ok=0;
    for(auto& camera : camere)
    {
        if(camera.verificaDisponibilitate()==true)
            ok=1;
    }
    if (ok==0)
    {
        std::cout<<"Momentan nu mai este nicio camera libera."<<std::endl;
        return;
    }
    int nrCamera;
    std::cout<<"Selectati camera pe care doriti sa o rezervati: ";
    std::cin>>nrCamera;
    bool gasita=false;
    for(auto& camera : camere)
    {
        if (camera.getNumar()==nrCamera)
        {
            if(camera.verificaDisponibilitate()==false)
            {
                std::cout<<"Camera selectata nu este disponibila."<<std::endl;
            }
            else
            {
                std::string data_check_in, data_check_out;
                std::cout<<"Data check-in (YYYY-MM-DD): ";
                std::cin>>data_check_in;
                std::cout<<"Data check-out (YYYY-MM-DD): ";
                std::cin>>data_check_out;

                if (calculeazaDiferentaZile(data_check_in,data_check_out) <= 0)
                {
                    std::cout<<"Datele introduse nu sunt valide"<<std::endl;
                    return;
                }

                adaugaRezervare(camera, data_check_in, data_check_out);

            }
            gasita=true;
            break;
        }
    }
    if(gasita==false)
        {
            std::cout<<"Camera nu exista"<<std::endl;
        }
    
}
void Hotel::veziCamereDisponibile()
{
    std::cout<<"Urmatoarele camere sunt disponibile pentru rezervare: "<<std::endl;
    for(auto& camera : camere) //referinta - pentru a nu copia fiecare element din vector
    {
        if(camera.verificaDisponibilitate()==true)
        {
            std::cout<<"Camera "<<camera.getNumar()<<" este disponibila"<<std::endl;
        }
    }
}
