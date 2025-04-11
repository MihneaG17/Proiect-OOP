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
    camere[4].setNumar(5); camere[4].setTip("Premium"); camere[4].setPret(500); camere[4].setDisponibilitate(true);
};

Hotel::~Hotel() {};

void Hotel::ruleaza()
{
    int opt;
    std::cout<<"Bun venit! Alegeti contul in care doriti sa va conectati\n";
    std::cout<<"1. Client\n";
    std::cout<<"2. Administrator\n";
    std::cout<<"3. Iesire\n";
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
                std::cout<<"La revedere!\n";
                break;
            default:
                std::cout<<"Optiune invalida. Va rugam sa alegeti din nou\n";
                ruleaza();
                break;
        }
    
};

void Hotel::meniuClient()
{
    int choice;
    do {
    std::cout<<"Ce doriti sa faceti?\n";
    std::cout<<"1. Vezi camerele disponibile.\n";
    std::cout<<"2. Efectueaza o rezervare.\n";
    std::cout<<"3. Vezi toate rezervarile efectuate.\n";
    std::cout<<"4. Anuleaza o rezervare.\n";
    std::cout<<"5. Ofera review unei rezervari.\n";
    std::cout<<"6. Inapoi\n";
    std::cout<<"Alegeti:\n";
    std::cin>>choice;
    switch (choice)
    {
    case 1:
        veziCamereDisponibile();
        break;
    case 2:
        efectueazaRezervare();
        break;
    case 3:
        vizualizareRezervari();
        break;
    case 4:
        anuleazaRezervare();
        break;
    case 5:
        oferaReview();
        break;
    case 6:
        std::cout<<"Revenim la meniul principal\n";
    default:
        break;
    }
   }while(choice!=6);
}
void Hotel::meniuAdministrator()
{
    std::cout<<"To be continued...\n";
}

//Actiuni client

void Hotel::veziCamereDisponibile()
{
    std::cout<<"Urmatoarele camere sunt disponibile pentru rezervare: "<<"\n";
    for(auto& camera : camere) //referinta - pentru a nu copia fiecare element din vector
    {
        if(camera.verificaDisponibilitate()==true)
        {
            std::cout<<"Camera "<<camera.getNumar()<<" - "<<camera.getTip()<<" - "<<camera.getPret()<<" RON/noapte"<<"\n";
        }
    }
    std::cout<<"\n";
}

void Hotel::adaugaRezervare(Camera &camera, std::string& data_check_in, std::string& data_check_out)
{
    Client client;
    std::string nume, email;
    int varsta;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Curata buffer-ul pentru a nu sari peste getline
    
    std::cout<<"Introduceti numele si prenumele pe care doriti sa efectuati rezervarea: "<<"\n";
    std::getline(std::cin, nume);
    client.setNume(nume);

    std::cout<<"Introduceti email-ul: "<<"\n";
    std::cin>>email;
    client.setEmail(email);

    std::cout<<"Introduceti varsta: "<<"\n";
    std::cin>>varsta;
    client.setVarsta(varsta);

    std::string metoda_plata, observatii;

    std::cout<<"Selectati metoda de plata (Numerar/Card/Transfer bancar): "<<"\n";
    std::cin>>metoda_plata;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Curata buffer-ul pentru a nu sari peste getline


    std::cout << "Observatii (optional): ";
    std::getline(std::cin, observatii);

    std::cout<<"\n";

    //Calculeaza pretul total al rezervarii
    int nopti=calculeazaDiferentaZile(data_check_in,data_check_out);

    double pret_total;
    pret_total=nopti*camera.getPret();

    double discount=0.0;

    int id_rezervare=rezervari.size()+1;

    Rezervare r(id_rezervare, data_check_in, data_check_out, pret_total, client, camera, metoda_plata, observatii, discount, nopti);

    if(nopti>7 && nopti<=10) //Se adauga discount in functie de numarul de nopti selectate pentru rezervare
    {
        discount+=10;
    }
    else if(nopti>10)
    {
        discount+=15;
    }
    if(discount!=0)
    {
        r.calcularePretDupaDiscount();
        r.setDiscount(discount);
    }
    
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
        std::cout<<"Momentan nu mai este nicio camera libera."<<"\n";
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
                std::cout<<"Camera selectata nu este disponibila."<<"\n";
                std::cout<<"\n";
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
                    std::cout<<"Datele introduse nu sunt valide"<<"\n";
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
            std::cout<<"Camera nu exista"<<"\n";
            std::cout<<"\n";
        }
    
}

void Hotel::vizualizareRezervari()
{
    if(rezervari.empty()) //Metoda din libraria <vector> pentru a verifica daca vectorul este sau nu gol
    {
        std::cout<<"Momentan nu ati efectuat nicio rezervare"<<"\n";
        return;
    }
    else
    {
        for(auto& rezervare : rezervari)
        {
            std::cout<<"-------------------------------"<<"\n";
            std::cout<<"ID-ul rezervarii: "<<rezervare.getId()<<"\n";
            std::cout<<"Data de check-in: "<<rezervare.getDataCheckIn()<<"\n";
            std::cout<<"Data de check-out: "<<rezervare.getDataCheckOut()<<"\n";
            std::cout<<"Numar nopti: "<<rezervare.getNumarNopti()<<"\n";
            std::cout<<"Pret total: "<<rezervare.getPretTotal()<<"\n";
            if (rezervare.getDiscount()!=0)
            {
                std::cout<<"Discount aplicat: "<<rezervare.getDiscount()<<"\n";
            }
            std::cout<<"Metoda de plata: "<<rezervare.getMetodaPlata()<<"\n";
            std::cout<<"Observatii: "<<rezervare.getObservatii()<<"\n";

            const Camera& cam = rezervare.getCamera();

            std::cout<<"\n";
            std::cout<<"Detaliile camerei asociate rezervarii: "<<"\n";
            std::cout<<"Numar: "<<cam.getNumar()<<"\n";
            std::cout<<"Pret/noapte: "<<cam.getPret()<<"\n";
            std::cout<<"Tip: "<<cam.getTip()<<"\n";

            std::cout<<"\n";
            
            if(rezervare.areReview())
            {
                Review r=rezervare.getReview();
                std::cout<<"Rating: "<<r.getNota()<<"\n";
                std::cout<<"Comentariu: "<<r.getComentariu()<<"\n";
            }
        }
        std::cout<<"\n";
    }
}

void Hotel::anuleazaRezervare()
{
    if(rezervari.empty())
    {
        std::cout<<"Nu exista nicio rezervare activa.\n";
        std::cout<<"\n";
        return;
    }
    std::cout<<"Introduceti ID-ul rezervarii pe care doriti sa o anulati:\n";
    int id_rezervare;
    std::cin>>id_rezervare;
    int pozitie=0;
    bool gasit=false;

    for(auto& rezervare : rezervari)
    {
        if(rezervare.getId()==id_rezervare)
        {
            gasit=true;

            Camera cam=rezervare.getCamera();
            int nrCamera=cam.getNumar(); //Setez statusul camerei ca fiind true (libera)
            
            for(auto& camera : camere)
            {
                if(camera.getNumar()==nrCamera)
                {
                    camera.setDisponibilitate(true);
                    break;
                }
            }
            rezervari.erase(rezervari.begin()+pozitie);
            std::cout<<"Rezervarea a fost anulata cu succes!\n";
            std::cout<<"\n";
            break;
        }
        pozitie++;
    }
    if(!gasit)
    {
        std::cout<<"Rezervarea cautata nu a fost gasita\n";
    }
}

void Hotel::oferaReview() 
{
    if(rezervari.empty())
    {
        std::cout<<"Nu ati efectuat nicio rezervare. Un review poate fi oferit doar unei rezervari.\n";
        std::cout<<"\n";
        return;
    }
    Review review;
    std::cout<<"Introduceti ID-ul rezervarii careia doriti sa-i oferiti un review:\n";
    int id_rezervare;
    std::cin>>id_rezervare;
    bool gasit=false;
    double rating;
    std::string comentariu;
    for(auto& rezervare : rezervari)
    {
        if(rezervare.getId()==id_rezervare)
        {
            gasit=true;

            std::cout<<"Introduceti rating-ul pe care doriti sa il acordati rezervarii (un numar de la 1 la 5, poate avea si zecimale):\n";
            std::cin>>rating;
            review.setNota(rating);
            std::cout<<"Lasati un comentariu in care descrieri experienta dvs: \n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, comentariu);
            review.setComentariu(comentariu);

            rezervare.setReview(review);
        }
    }
    if(!gasit)
    {
        std::cout<<"Rezervarea cautata nu a fost gasita\n";
    }
}