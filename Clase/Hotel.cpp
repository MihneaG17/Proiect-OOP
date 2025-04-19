#include "Hotel.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

Hotel::Hotel() {
    incarcaCamereDinFisier();
    incarcaAngajatiDinFisier();
};

Hotel::~Hotel() {}; //Destructor

void Hotel::ruleaza()
{
    int opt;

    do {
        std::cout << "Bun venit! Alegeti contul in care doriti sa va conectati\n";
        std::cout << "1. Client\n";
        std::cout << "2. Administrator\n";
        std::cout << "3. Iesire\n";
        std::cout << "Alegere: ";
        std::cin >> opt;

        switch (opt) {
            case 1:
                meniuClient();
                break;
            case 2:
                meniuAdministrator();
                break;
            case 3:
                std::cout << "La revedere!\n";
                break;
            default:
                std::cout << "Optiune invalida. Va rugam sa alegeti din nou\n";
                break;
        }

    } while (opt != 3);
}

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
    bool ok=false;
    logareAdmin(ok);
    if(ok==true)
    {
        int choice;
        do
        {
            std::cout<<"Ce doriti sa faceti?: \n";
            std::cout<<"1. Adaugati camere. \n";
            std::cout<<"2. Gestionati angajati. \n";
            std::cout<<"3. Vizualizati clienti. \n";
            std::cout<<"4. Vizualizati toate rezervarile. \n";
            std::cout<<"5. Inapoi \n";
            std::cout<<"Alegeti:\n";
            std::cin>>choice;
            switch (choice)
            {
            case 1:
                adaugaCamere();
                break;
            case 2:
                gestionareAngajati();
                break;
            case 3:
                vizualizareClienti();
                break;
            case 4:
                vizualizareToateRezervarile();
                break;
            case 5:
                std::cout<<"Revenim la meniul principal\n";
            default:
                break;
            }
        } while (choice!=5);
    }
}

//Actiuni client

void Hotel::veziCamereDisponibile()
{  
    std::cout<<"Urmatoarele camere sunt disponibile pentru rezervare: "<<"\n";
    for(auto& camera : camere) //referinta - pentru a nu copia fiecare element din vector - este accesat obiectul in sine
    {
        if(camera.verificaDisponibilitate()==true)
        {
            std::cout<<"Camera "<<camera.getNumar()<<" - "<<camera.getTip()<<" - "<<camera.getPret()<<" RON/noapte"<<"\n";
        }
    }
    std::cout<<"\n";
}

void Hotel::salvareRezervareFisier(const Rezervare& r)
{
    std::ofstream f("Fisiere_txt/rezervari.txt",std::ios::app); //deschide fisierul in modul append pentru a adauga date la finalul sau

    if(f.is_open())
    {
        f<<"ID rezervare: "<<r.getId()<<"\n";
        f<<"Nume client: "<<r.getClient().getNume()<<"\n";
        f<<"Email: "<<r.getClient().getEmail()<<"\n";

        const Camera cam = r.getCamera();

        f<<"Camera: "<<cam.getNumar()<<" - "<<cam.getTip()<<" - "<<cam.getPret()<<"RON/noapte\n";

        f<<"Check-in: "<<r.getDataCheckIn()<<"\n";
        f<<"Check-out: "<<r.getDataCheckOut()<<"\n";
        f<<"Nopti: "<<r.getNumarNopti()<<"\n";
        f<<"Pret total: "<<r.getPretTotal()<<"\n";
        f<<"Discount: "<<r.getDiscount()<<"\n";
        f<<"Metoda plata: "<<r.getMetodaPlata()<<"\n";
        f<<"Observatii: "<<r.getObservatii()<<"\n";
        f<<"------------------------------\n";

        f.close();
    }
    else
    {
        std::cerr<<"Eroare la deschiderea fisierului\n"; //standard error stream used to output the errors
    }
}

void Hotel::incarcaCamereDinFisier()
{
    std::ifstream in("Fisiere_txt/camere.txt");

    if(!in)
    {
        std::cerr<<"Eroare la deschiderea fisierului\n"; //standard error stream used to output the errors
        return;
    }

    int nrCamera,pret;
    std::string tip;
    bool disponibilitate;

    //cat timp citim linii valide
    while(in >> nrCamera >> tip >> pret >> disponibilitate)
    {
        Camera camera;
        camera.setNumar(nrCamera);
        camera.setTip(tip);
        camera.setPret(pret);
        camera.setDisponibilitate(disponibilitate);

        camere.push_back(camera);
    }
    in.close();
}

void Hotel::adaugaRezervare(Camera &camera, std::string& data_check_in, std::string& data_check_out)
{
    Client client;
    std::string nume, email;
    int varsta;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Curata buffer-ul pentru a nu sari peste getline (elimina \n-ul citit cu cin)
    
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

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Curata buffer-ul pentru a nu sari peste getline (elimina \n-ul citit cu cin)


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

    salvareRezervareFisier(r);

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
        std::cout<<"\n";
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
        std::cout<<"\n";
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
                std::cout<<"Discount aplicat: "<<rezervare.getDiscount()<<"%\n";
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
            if (rating < 1 || rating > 5) {
                std::cout << "Rating-ul trebuie să fie între 1 și 5.\n";
                return;
            }            
            review.setNota(rating);
            std::cout<<"Lasati un comentariu in care descrieti experienta dvs: \n";
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

//Actiuni administrator

void Hotel::logareAdmin(bool &ok)
{   
    std::string email, parola;
    std::cout<<"Introduceti email-ul: \n";
    std::cin>>email;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout<<"Introduceti parola: \n";
    std::cin>>parola;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if(email!="mihnea298@gmail.com" || parola!="mihnea123")
    {
        std::cout<<"Mail-ul sau parola introduse sunt incorecte!\n";
        return;
    }
    std::cout<<"V-ati autentificat cu succes!\n";
    ok=true;
}

void Hotel::scrieCameraInFisier(const Camera& camera)
{
    std::ofstream out("Fisiere_txt/camere.txt", std::ios::app); //deschide in modul append
    if(out)
    {
        out<<camera.getNumar()<<" "<<camera.getTip()<<" "<<camera.getPret()<<" "<<camera.getStatus()<<"\n";
        out.close();
    }
    else
    {
        std::cerr<<"Eroare la deschiderea fisierului.\n";
    }
}

void Hotel::adaugaCamere()
{
    int nrCamera;
    std::cout<<"Introduceti numarul camerei: \n";
    std::cin>>nrCamera;
    
    for(auto& camera : camere)
    {
        if(camera.getNumar()==nrCamera)
        {
            std::cout<<"Camera cu ID-ul "<<nrCamera<<" deja exista.\n";
            std::cout<<'\n';
            return;
        }
    }

    std::string tipCamera;
    std::cout<<"Introduceti tipul camerei: \n";
    std::cin>>tipCamera;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int pret;
    std::cout<<"Introduceti pretul camerei (per noapte - in RON): \n";
    std::cin>>pret;
    if(pret<0)
    {
        std::cout<<"Pretul introdus trebuie sa fie un numar pozitiv.\n";
        return;
    }

    bool status;
    std::cout<<"Introduceti disponibilitatea camerei (1-libera / 0-ocupata): \n";
    std::cin>>status;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string confirmare;
    std::cout<<"Sunteti sigur ca doriti sa adaugati o noua camera? Va reamintim detaliile introduse: \n";
    std::cout<<"Numar camera: "<<nrCamera<<"\nTipul camerei: "<<tipCamera<<"\nPretul camerei: "<<pret<<"\nDisponibilitate: "<<status<<"\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    do
    { 
        std::cout<<"Scrieti 'DA' pentru a confirma si a crea noua camera sau 'NU' altfel: \n";
        std::getline(std::cin, confirmare);

        for (auto& c : confirmare) c = toupper(c); // input-ul sa fie case-insensitive

        if(confirmare=="DA")
        {
            Camera newCam(nrCamera, status, pret, tipCamera);
            camere.push_back(newCam);
            scrieCameraInFisier(newCam);
            std::cout<<"Camera a fost adaugata cu succes!\n";
            return;
        }
        else 
        {
            if(confirmare=="NU")
            {
                std::cout<<"Revenim la meniul principal \n";
                return;
            }
            else
            {
                std::cout<<"Raspuns invalid. Va rugam sa tastati DA sau NU.\n";
                
            }
        }
    }while(true);

}

void Hotel::gestionareAngajati()
{
    int choice;
    std::cout<<"Alegeti: \n";
    do
    {   std::cout<<"1. Vizualizare angajati\n";
        std::cout<<"2. Marire salariala\n";
        std::cout<<"3. Minorare salariala\n";
        std::cout<<"4. Concediere\n";
        std::cout<<"5. Angajare\n";
        std::cout<<"6. Inapoi\n";
        std::cout<<"Alegeti optiunea: ";
        std::cin>>choice;

        switch (choice)
        {
        case 1:
            vizualizareAngajati();
            break;
        case 2:
            maresteSalariuAdmin();
            break;
        case 3:
            micsoreazaSalariuAdmin();
            break;
        case 4:
            concediereAngajat();
            break;
        case 5:
            angajare();
            break;
        case 6:
            std::cout<<"Inapoi\n";
            break;
        default:
            break;
        }
        
    } while (choice!=6);
}
void Hotel::vizualizareClienti()
{

}
void Hotel::vizualizareToateRezervarile()
{
    std::ifstream fin("Fisiere_txt/rezervari.txt");
    if(!fin.is_open())
    {
        std::cerr<<"Eroare la deschiderea fisierului.\n";
        return;
    }
    std::string linie;
    std::cout<<"Rezervarile inregistrate sunt: \n";
    std::cout<<"-----------------------------------\n";

    while(std::getline(fin,linie))
    {
        std::cout<<linie<<"\n";
    }
    fin.close();                                        
}

//Metodele (optiunile) din gestionareAngajati()
void Hotel::vizualizareAngajati()
{
    for(auto& angajat : angajati)
    {
        angajat->afisareDetalii();
        std::cout<<"\n";
    }
}

void Hotel::maresteSalariuAdmin()
{
    int id, pozitie=0;
    bool ok=0;
    std::cout<<"Introduceti ID-ul angajatului caruia doriti sa-i mariti salariul:\n";
    std::cin>>id;
    for(auto& angajat : angajati)
    {
        if(angajat->getId()==id)
        {
            ok=1;
            break;
        }
        pozitie++;
    }
    if(ok==1)
    {
        int procent;
        std::cout<<"Introduceti procentul cu care doriti sa mariti salariul angajatului: \n";
        std::cin>>procent;

        angajati[pozitie]->MarireSalariala(procent);
        salveazaAngajatiInFisier();

        std::cout<<"Salariul a fost modificat\n";
    }
    else
    {
        std::cout<<"Angajatul nu a fost gasit.\n\n";
    }
}

void Hotel::micsoreazaSalariuAdmin()
{
    int id, pozitie=0;
    bool ok=0;
    std::cout<<"Introduceti ID-ul angajatului caruia doriti sa-i micsorati salariul:\n";
    std::cin>>id;
    for(auto& angajat : angajati)
    {
        if(angajat->getId()==id)
        {
            ok=1;
            break;
        }
        pozitie++;
    }
    if(ok==1)
    {
        int procent;
        std::cout<<"Introduceti procentul cu care doriti sa micsorati salariul angajatului: \n";
        std::cin>>procent;

        angajati[pozitie]->MinorareSalariala(procent);
        salveazaAngajatiInFisier();

        std::cout<<"Salariul a fost modificat\n";
    }
    else
    {
        std::cout<<"Angajatul nu a fost gasit.\n\n";
    }
    salveazaAngajatiInFisier();
}

void Hotel::concediereAngajat()
{
    int id, pozitie=0;
    bool ok=0;
    std::cout<<"Introduceti ID-ul angajatului pe care doriti sa-l concediati: \n";
    std::cin>>id;

    for(auto& angajat : angajati)
    {
        if(angajat->getId()==id)
        {
            ok=1;
            break;
        }
        pozitie++;
    }
    if(ok==1)
    {
        angajati.erase(angajati.begin()+pozitie);
        salveazaAngajatiInFisier();
        std::cout<<"Angajatul cu ID-ul "<<id<<" a fost concediat\n\n";
    }
    else
    {
        std::cout<<"Angajatul nu a fost gasit.\n\n";
    }
    salveazaAngajatiInFisier();
}

void Hotel::angajare()
{
    std::string nume,email,functie;
    int varsta,id,salariu;
    std::cout<<"Introduceti datele angajatului:\n";

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //curata buffer-ul inainte de citirea string-urilor

    std::cout<<"Nume complet: ";
    std::getline(std::cin,nume);

    std::cout<<"Email: ";
    std::getline(std::cin,email);

    std::cout<<"Varsta: ";
    std::cin>>varsta;

    std::cout<<"Salariu: ";
    std::cin>>salariu;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout<<"Functie (Ingrijitor / Receptioner / Bucatar / Manager): ";
    std::getline(std::cin,functie);

    id=angajati.size()+1;

    for(auto& c : functie)
    {
        c=tolower(c); //transform string-ul in lowercase pentru a nu fi case-sensitive raspunsul
    }
    if(functie=="ingrijitor")
    {
        adaugaIngrijitor(nume,email,varsta,id,salariu,functie);
    }
    else if(functie=="receptioner")
    {
        adaugaReceptioner(nume,email,varsta,id,salariu,functie);
    }
    else if(functie=="bucatar")
    {
        adaugaBucatar(nume,email,varsta,id,salariu,functie);
    }
    else if(functie=="manager")
    {
        adaugaManager(nume,email,varsta,id,salariu,functie);
    }
    else
    {
        std::cout<<"Functia introdusa nu exista\n";
    }
}

//Functiile din optiunea(metoda) angajare()

void Hotel::adaugaIngrijitor(std::string nume, std::string email, int varsta, int id, int salariu, std::string functie)
{
    int etaj_curatenie;
    std::cout<<"Asociati angajatului etajul la care sa faca curatenie: ";
    std::cin>>etaj_curatenie;

    angajati.push_back(new Ingrijitor(nume,email,varsta,id,salariu,functie,etaj_curatenie));
    adaugaAngajatInFisier(angajati.back());
    std::cout<<"Angajatul a fost adaugat cu succes!\n";
}

void Hotel::adaugaReceptioner(std::string nume, std::string email, int varsta, int id, int salariu, std::string functie)
{
    int nrLimbi;
    std::string schimb, limba;
    std::vector<std::string> limbi_vorbite;

    std::cout<<"Introduceti schimbul angajatului (zi/noapte): ";
    std::cin>>schimb;

    std::cout<<"Introduceti numarul de limbi ce urmeaza sa fie adaugat: ";
    std::cin>>nrLimbi;

    std::cout<<"Introduceti limbile vorbite: \n";
    for(int i=0;i<nrLimbi;i++)
    {
        std::cin>>limba;
        limbi_vorbite.push_back(limba);
    }

    angajati.push_back(new Receptioner(nume,email,varsta,id,salariu,functie,schimb,limbi_vorbite));
    adaugaAngajatInFisier(angajati.back());
    std::cout<<"Angajatul a fost adaugat cu succes!\n";
}

void Hotel::adaugaBucatar(std::string nume, std::string email, int varsta, int id, int salariu, std::string functie)
{
    std::string specializare,certificare;
    std::vector<std::string> certificari;
    int nrCertificari;

    std::cout<<"Introduceti specializare: ";
    std::cin>>specializare;

    std::cout<<"Introduceti numarul de certificari: ";
    std::cin>>nrCertificari;

    std::cout<<"Introduceti certificarile detinute: ";
    for(int i=0;i<nrCertificari;i++)
    {
        std::cin>>certificare;
        certificari.push_back(certificare);
    }

    angajati.push_back(new Bucatar(nume,email,varsta,id,salariu,functie,specializare,certificari));
    adaugaAngajatInFisier(angajati.back());
    std::cout<<"Angajatul a fost adaugat cu succes!\n";
}

void Hotel::adaugaManager(std::string nume, std::string email, int varsta, int id, int salariu, std::string functie)
{
    int aniExp,nrDept;
    std::vector<std::string> departamente;
    std::string dept;

    std::cout<<"Introduceti anii de experienta: ";
    std::cin>>aniExp;

    std::cout<<"Introduceti numarul de departamente: ";
    std::cin>>nrDept;

    std::cout<<"Introduceti departamentele: ";
    for(int i=0;i<nrDept;i++)
    {
        std::cin>>dept;
        departamente.push_back(dept);
    }

    angajati.push_back(new Manager(nume,email,varsta,id,salariu,functie,departamente,aniExp));
    adaugaAngajatInFisier(angajati.back());
    std::cout<<"Angajatul a fost adaugat cu succes!\n";
}

void Hotel::incarcaAngajatiDinFisier()
{
    std::ifstream fin("Fisiere_txt/angajati.txt");
    if(!fin.is_open())
    {
        std::cerr<<"Eroare la deschiderea fisierului\n"; //standard error stream
        return;
    }
    std::string linie;
    while(std::getline(fin,linie)) //cat timp citim linii din fisier
    {
        std::istringstream iss(linie); //object used to stream the string into different variables
        //the string can be streamed and stored using the extraction operator(>>) or using string methods such as getline

        std::string nume, email, varstaStr, idStr, salariuStr, functie, atribut1, atribut2;

        //extrag in fiecare variabila datele din fisier pana cand intalnesc ;
        std::getline(iss, functie, ';');
        std::getline(iss, nume, ';');
        std::getline(iss, email, ';');
        std::getline(iss, varstaStr, ';');
        std::getline(iss, idStr, ';');
        std::getline(iss, salariuStr, ';');
        std::getline(iss, atribut1, ';');
        std::getline(iss, atribut2, ';'); //optional - nu toti angajatii au si atribut 2 (ex: ingrijitor)

        int varsta=std::stoi(varstaStr); //string to integer
        int id=std::stoi(idStr);
        int salariu=std::stoi(salariuStr);

        if(functie=="ingrijitor")
        {
            incarcaIngrijitor(nume,email,varsta,id,salariu,functie,atribut1);
        }
        else if(functie=="receptioner")
        {
            incarcaReceptioner(nume,email,varsta,id,salariu,functie,atribut1,atribut2);
        }
        else if(functie=="bucatar")
        {
            incarcaBucatar(nume,email,varsta,id,salariu,functie,atribut1,atribut2);
        }
        else if(functie=="manager")
        {
            incarcaManager(nume,email,varsta,id,salariu,functie,atribut1,atribut2);
        }
    }
    fin.close();
}

void Hotel::incarcaIngrijitor(std::string nume, std::string email, int varsta, int id, int salariu, std::string functie, std::string atribut1)
{
    int etaj=std::stoi(atribut1);
    angajati.push_back(new Ingrijitor(nume,email,varsta,id,salariu,functie,etaj));
}

void Hotel::incarcaReceptioner(std::string nume, std::string email, int varsta, int id, int salariu, std::string functie, std::string atribut1, std::string atribut2)
{
    std::string schimb=atribut1;
    std::vector<std::string> limbi;
    std::istringstream limbiStream(atribut2);
    std::string limba;

    //al doilea atribut contine mai multe limbi: extrag fiecare limba si o adaug in vector
    while(std::getline(limbiStream, limba, ','))
    {
        limbi.push_back(limba);
    }
    angajati.push_back(new Receptioner(nume,email,varsta,id,salariu,functie,schimb,limbi));
}

void Hotel::incarcaBucatar(std::string nume, std::string email, int varsta, int id, int salariu, std::string functie, std::string atribut1, std::string atribut2)
{
    std::string specializare=atribut1;
    std::vector<std::string> certificari;
    std::istringstream certStream(atribut2);
    std::string certificare;

    //la fel ca la receptioner - citim fiecare certificare si o adaugam in vector
    while(std::getline(certStream, certificare, ','))
    {
        certificari.push_back(certificare);
    }
    angajati.push_back(new Bucatar(nume,email,varsta,id,salariu,functie,specializare,certificari));
}

void Hotel::incarcaManager(std::string nume, std::string email, int varsta, int id, int salariu, std::string functie, std::string atribut1, std::string atribut2)
{
    int aniExp=std::stoi(atribut2);
    std::vector<std::string> departamente;
    std::istringstream deptStream(atribut1);
    std::string dept;

    //la fel ca la receptioner - citim fiecare certificare si o adaugam in vector
    while(std::getline(deptStream, dept, ','))
    {
        departamente.push_back(dept);
    }
    angajati.push_back(new Manager(nume,email,varsta,id,salariu,functie,departamente,aniExp));
}

void Hotel::salveazaAngajatiInFisier()
{
    std::ofstream fout("Fisiere_txt/angajati.txt", std::ios::out); //std::ios::out este folosit pentru a rescrie fisierul (overwrite) folosind continutul actual din vector (util pentru functiile de marire/micsorare salariala si concediere)
    if(!fout.is_open())
    {
        std::cerr<<"Eroare la deschiderea fisierului";
        return;
    }
    for(auto& angajat : angajati) //parcurgem fiecare angajat din vector
    {
        fout<<angajat->getFunctie()<<";"<<angajat->getNume()<<";"<<angajat->getEmail()<<";"<<angajat->getVarsta()<<";"
        <<angajat->getId()<<";"<<angajat->getSalariu()<<";";

        //Downcast pentru fiecare subtip de angajat (facem acest lucru pentru a scrie atributele specifice fiecarui tip angajat)
        //toate obiectele sunt convertite la runtime
        if(auto ingrijitor=dynamic_cast<Ingrijitor*>(angajat))
        {
            fout<<ingrijitor->getEtaj();
        }
        else if(auto receptioner=dynamic_cast<Receptioner*>(angajat))
        {
            fout<<receptioner->getSchimb()<<";";
            const auto& limbi=receptioner->getLimbi();
            //for care scrie toate string-urile (limbile) stocate in vector
            for(int i=0;i<limbi.size();i++)
            {
                fout<<limbi[i];
                if(i<limbi.size()-1) //if pentru a nu scrie "," si dupa ultimul elem din vector
                    fout<<",";
            }
        }
        else if(auto bucatar=dynamic_cast<Bucatar*>(angajat))
        {
            fout<<bucatar->getSpecializare()<<";";
            const auto& certificari=bucatar->getCertificari();
            //for care scrie toate string-urile (certificarile) stocate in vector
            for(int i=0;i<certificari.size();i++)
            {
                fout<<certificari[i];
                if(i<certificari.size()-1)
                    fout<<",";
            }
        }
        else if(auto manager=dynamic_cast<Manager*>(angajat))
        {
            const auto& departamente=manager->getDepartamente();
            for(int i=0;i<departamente.size();i++)
            {
                fout<<departamente[i];
                if(i<departamente.size()-1)
                    fout<<",";
            }
            fout<<";"<<manager->getExperienta();
        }
        fout<<"\n";
    }
    fout.close();
}

void Hotel::adaugaAngajatInFisier(Angajat* angajat)
{
    std::ofstream fout("Fisiere_txt/angajati.txt", std::ios::app);
    if (!fout.is_open()) {
        std::cerr << "Eroare la deschiderea fisierului.\n";
        return;
    }

    if (Ingrijitor* i = dynamic_cast<Ingrijitor*>(angajat)) {
        fout << "ingrijitor;"<< i->getNume() << ";"<< i->getEmail() << ";"<< i->getVarsta() << ";"<< i->getId() << ";"<< i->getSalariu() << ";"<< i->getFunctie() << ";"<< i->getEtaj() << "\n";
    }
    else if (Receptioner* r = dynamic_cast<Receptioner*>(angajat)) {
        fout << "receptioner;"<< r->getNume() << ";"<< r->getEmail() << ";"<< r->getVarsta() << ";"<< r->getId() << ";"<< r->getSalariu() << ";"<< r->getFunctie() << ";"<< r->getSchimb() << ";";

        const auto& limbi = r->getLimbi();
        for (int i = 0; i < limbi.size(); ++i) {
            fout << limbi[i];
            if (i < limbi.size() - 1) fout << ",";
        }
        fout << "\n";
    }
    else if (Bucatar* b = dynamic_cast<Bucatar*>(angajat)) {
        fout << "bucatar;"<< b->getNume() << ";"<< b->getEmail() << ";"<< b->getVarsta() << ";"<< b->getId() << ";"<< b->getSalariu() << ";"<< b->getFunctie() << ";"<< b->getSpecializare() << ";";

        const auto& certif = b->getCertificari();
        for (int i = 0; i < certif.size(); ++i) {
            fout << certif[i];
            if (i < certif.size() - 1) fout << ",";
        }
        fout << "\n";
    }
    else if (Manager* m = dynamic_cast<Manager*>(angajat)) {
        fout << "manager;"<< m->getNume() << ";"<< m->getEmail() << ";"<< m->getVarsta() << ";"<< m->getId() << ";"<< m->getSalariu() << ";"<< m->getFunctie() << ";";

        const auto& dept = m->getDepartamente();
        for (int i = 0; i < dept.size(); ++i) {
            fout << dept[i];
            if (i < dept.size() - 1) fout << ",";
        }
        fout<<";"<<m->getExperienta();
        fout << "\n";
    }
    fout.close();
}


