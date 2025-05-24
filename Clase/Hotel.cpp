#include "Hotel.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

namespace HotelManagement {

Hotel::Hotel() {
    IncarcaCamereDinFisier();
    IncarcaAngajatiDinFisier();
    IncarcaRezervariDinFisier();
    IncarcaClientiDinFisier();
}; //Cand se creaza un obiect de tip Hotel (in main, unic) se incarca automat in vectori datele despre camere, rezervari, angajati si clienti preluate din fisierele text

Hotel::~Hotel() {
    for(auto& angajat : m_angajati)
    {
        delete angajat;
    }
    m_angajati.clear();
}; //Destructor - sunt sterse obiectele de tip Angajat alocate pe heap

void Hotel::Ruleaza() //Meniul principal - metoda Ruleaza() se apeleaza in main
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
                MeniuClient();
                break;
            case 2:
                MeniuAdministrator();
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

void Hotel::MeniuClient() //Meniul clientului
{
    int choice;
    do {
        std::cout<<"Ce doriti sa faceti?\n";
        std::cout<<"1. Vezi camerele disponibile.\n";
        std::cout<<"2. Efectueaza o rezervare.\n";
        std::cout<<"3. Vezi rezervari efectuate.\n";
        std::cout<<"4. Anuleaza o rezervare.\n";
        std::cout<<"5. Ofera review unei rezervari.\n";
        std::cout<<"6. Inapoi\n";
        std::cout<<"Alegeti:\n";
        std::cin>>choice;
        switch (choice)
        {
        case 1:
            VeziCamereDisponibile();
            break;
        case 2:
            EfectueazaRezervare();
            break;
        case 3:
            VizualizareRezervari();
            break;
        case 4:
            AnuleazaRezervare();
            break;
        case 5:
            OferaReview();
            break;
        case 6:
            std::cout<<"Revenim la meniul principal\n";
        default:
            break;
    }
   }while(choice!=6);
}
void Hotel::MeniuAdministrator() //Meniu administrator - necesita log-in cu date unice (mail si parola)
{
    bool ok=false;
    LogareAdmin(ok);
    if(ok==true)
    {
        int choice;
        do
        {
            std::cout<<"Ce doriti sa faceti?: \n";
            std::cout<<"1. Adaugati camere. \n";
            std::cout<<"2. Gestionati angajati. \n";
            std::cout<<"3. Vizualizati clienti.\n";
            std::cout<<"4. Vizualizati toate rezervarile. \n";
            std::cout<<"5. Inapoi \n";
            std::cout<<"Alegeti:\n";
            std::cin>>choice;
            switch (choice)
            {
            case 1:
                AdaugaCamere();
                break;
            case 2:
                GestionareAngajati();
                break;
            case 3:
                VizualizareClienti();
                break;
            case 4:
                VizualizareToateRezervarile();
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

void Hotel::VeziCamereDisponibile()
{  
    std::cout<<"In hotel exista "<<Camera::GetTotalCamere()<<" camere, urmatoarele fiind disponibile pentru rezervare: "<<"\n";
    for(auto& camera : m_camere) //referinta - pentru a nu copia fiecare element din vector - este accesat obiectul in sine
    {
        if(camera.VerificaDisponibilitate()==true)
        {
            std::cout<<camera<<"\n"; //operator overloading << - afisam detaliile camerei
            //std::cout<<"Camera "<<camera.getNumar()<<" - "<<camera.getTip()<<" - "<<camera.getPret()<<" RON/noapte"<<"\n";
        }
    }
    std::cout<<"\n";
}

void Hotel::SalvareRezervareFisier(const Rezervare& r)
{
    std::ofstream f("Fisiere_txt/rezervari.txt",std::ios::app); //deschide fisierul in modul append pentru a adauga date la finalul acestuia

    if(f.is_open()) 
    {   
        //Se adauga datele rezervarii in fisier
        f<<"ID rezervare: "<<r.GetId()<<"\n";
        f<<"Nume client: "<<r.GetClient().GetNume()<<"\n";
        f<<"Email: "<<r.GetClient().GetEmail()<<"\n";

        const Camera cam = r.GetCamera();

        f<<"Camera: "<<cam.GetNumar()<<" - "<<cam.GetTip()<<" - "<<cam.GetPret()<<"RON/noapte\n";

        f<<"Check-in: "<<r.GetDataCheckIn()<<"\n";
        f<<"Check-out: "<<r.GetDataCheckOut()<<"\n";
        f<<"Nopti: "<<r.GetNumarNopti()<<"\n";
        f<<"Pret total: "<<r.GetPretTotal()<<"\n";
        f<<"Discount: "<<r.GetDiscount()<<"\n";
        f<<"Metoda plata: "<<r.GetMetodaPlata()<<"\n";
        f<<"Observatii: "<<r.GetObservatii()<<"\n";
        f<<"Rating: "<<r.GetReview().GetNota()<<"\n";
        f<<"Comentariu: "<<r.GetReview().GetComentariu()<<"\n";
        f<<"------------------------------\n";

        f.close();
    }
    else
    {
        std::cerr<<"Eroare la deschiderea fisierului\n"; //standard error stream used to output the errors
    }
}

void Hotel::IncarcaCamereDinFisier()
{
    std::ifstream in("Fisiere_txt/camere.txt");

    if(!in)
    {
        std::cerr<<"Eroare la deschiderea fisierului\n"; //standard error stream used to output the errors
        return;
    }

    int nr_camera,pret;
    std::string tip;
    bool disponibilitate;

    //cat timp citim linii valide
    while(in >> nr_camera >> tip >> pret >> disponibilitate)
    {
        Camera camera;
        camera.SetNumar(nr_camera);
        camera.SetTip(tip);
        camera.SetPret(pret);
        camera.SetDisponibilitate(disponibilitate);

        m_camere.push_back(camera); //Pentru fiecare camera din fisier, se creeaza un obiect de tip Camera, ii sunt setate atributele si este incarcat in vector
        //Din acest motiv variabila statica m_total_camere este incrementata in constructorul default, deoarece mai intai sunt create obiectele si apoi populate cu date
    }
    in.close();
}
void Hotel::IncarcaRezervariDinFisier()
{
    std::ifstream fin("Fisiere_txt/rezervari.txt");
    if (!fin.is_open()) {
        std::cerr << "Eroare la deschiderea fisierului de rezervari.\n"; //standard error stream used to output the errors
        return;
    }
    std::string linie;
    while(std::getline(fin,linie)) //cat timp citim linii
    {
        if(linie.empty()) continue; //ignoram liniile goale

        int id=std::stoi(linie.substr(14)); //substring-ul de la pozitia 14 - id-ul care se afla dupa ":" !!!!!

        std::getline(fin,linie);
        std::string nume=linie.substr(13); //nume client:

        std::getline(fin, linie);
        std::string email = linie.substr(7); //email:

        std::getline(fin, linie); // Camera: 2 - Double - 200RON/noapte
        int nr_camera, pret_camera;
        std::string tipCamera;

        size_t start = linie.find(':') + 2; // începe după "Camera: "
        size_t dash1 = linie.find('-', start); //prima "-" dupa pozitia start
        nr_camera = std::stoi(linie.substr(start, dash1 - start));

        size_t dash2 = linie.find('-', dash1 + 2); //a doua "-" dupa prima
        tipCamera = linie.substr(dash1 + 2, dash2 - dash1 - 3);

        size_t ron_pos = linie.find("RON"); //cauta pozitia unde scrie "RON" in fisier
        pret_camera = std::stoi(linie.substr(dash2 + 2, ron_pos - dash2 - 2)); //ia valoarea dintre dash2 si RON si o transforma in int (reprezinta pretul camerei)

        Camera cam(nr_camera, true, pret_camera, tipCamera); //Aici se creeaza un obiect de tip camera cu constructorul parametrizat - m_total_camere nu se incrementeaza !! nu se creeaza camere noi, doar se asociaza una deja existenta unei rezervari

        std::getline(fin, linie);
        std::string check_in = linie.substr(10); //check-in:

        std::getline(fin, linie);
        std::string check_out = linie.substr(11); //check-out:

        std::getline(fin, linie);
        int nopti = std::stoi(linie.substr(7)); //nopti:

        std::getline(fin, linie);
        double pret_total = std::stod(linie.substr(12)); //pret total:

        std::getline(fin, linie);
        double discount = std::stod(linie.substr(9)); //discount:

        std::getline(fin, linie);
        std::string metoda = linie.substr(14); //metoda plata:

        std::getline(fin, linie);
        std::string observatii = linie.substr(12); //observatii:

        std::getline(fin,linie);
        double rating = std::stod(linie.substr(7)); //rating:

        std::getline(fin,linie);
        std::string comentariu=linie.substr(12); //comentariu:

        Client client;
        client.SetNume(nume);
        client.SetEmail(email);

        Review rv;
        rv.SetNota(rating);
        rv.SetComentariu(comentariu);

        Rezervare r(id, check_in, check_out, pret_total, client, cam, metoda, observatii, discount, nopti);
        r.SetReview(rv);
        m_rezervari.push_back(r); //se adauga rezervarea in vector

        std::getline(fin,linie); //dam skip la separatorul ------------------------
    }
    fin.close();
}
void Hotel::IncarcaClientiDinFisier()
{
    std::ifstream fin("Fisiere_txt/clienti.txt");
    if (!fin.is_open()) {
        std::cerr << "Eroare la deschiderea fisierului clienti.txt.\n"; //standard error stream used to output the errors
        return;
    }

    std::string linie;
    while(std::getline(fin, linie))
    {
        std::istringstream iss(linie);
        std::string id_str, nume, mail, varsta_str;

        std::getline(iss,id_str,';');
        std::getline(iss,nume,';');
        std::getline(iss,mail,';');
        std::getline(iss,varsta_str,';');

        int id_client=std::stoi(id_str);
        int varsta=std::stoi(varsta_str);

        Client c(nume,mail,varsta,id_client);

        m_clienti.push_back(c);
    }
    fin.close();
}
bool Hotel::ExistaClientInFisier(const Client& client) //functie care verifica daca un client este deja inregistrat in fisier
{
    std::ifstream fin("Fisiere_txt/clienti.txt");
    if (!fin.is_open()) {
        std::cerr << "Eroare la deschiderea fisierului clienti.txt.\n"; //standard error stream used to output the errors
        return false;
    }
    std::string linie;
    while(std::getline(fin,linie)) {
        std::istringstream iss(linie);
        std::string nume,mail,varsta,id_client;
        std::getline(iss,id_client,';');
        std::getline(iss,nume,';');
        std::getline(iss,mail,';');
        std::getline(iss,varsta,';');

        if(mail==client.GetEmail()) { //verificare la nivel de mail deoarece mail-ul unui client ar trebui sa fie unic
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}

void Hotel::SalveazaClientInFisier(const Client& client)
{
    std::ofstream fout("Fisiere_txt/clienti.txt", std::ios::app); //append-mode
    if (!fout.is_open()) {
        std::cerr << "Eroare la deschiderea fisierului clienti.txt.\n"; //standard error stream used to output the errors
        return;
    }
    fout<<client.GetIdC()<<";"<<client.GetNume()<<";"<<client.GetEmail()<<";"<<client.GetVarsta()<<"\n";
    fout.close();
}

void Hotel::AdaugaRezervare(Camera &camera, std::string& data_check_in, std::string& data_check_out)
{
    Client client;
    std::string nume, email;
    int varsta;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Curata buffer-ul pentru a nu sari peste getline (elimina \n-ul citit cu cin)
    
    std::cout<<"Introduceti numele si prenumele pe care doriti sa efectuati rezervarea: "<<"\n";
    std::getline(std::cin, nume);
    client.SetNume(nume);

    std::cout<<"Introduceti email-ul: "<<"\n";
    std::cin>>email;
    client.SetEmail(email);

    std::cout<<"Introduceti varsta: "<<"\n";
    std::cin>>varsta;
    client.SetVarsta(varsta);

    int id_client;
    id_client=m_clienti.size()+1;
    client.SetIdC(id_client);

    std::string metoda_plata, observatii;

    std::cout<<"Selectati metoda de plata (Numerar/Card/Transfer bancar): "<<"\n";
    std::cin>>metoda_plata;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Curata buffer-ul pentru a nu sari peste getline (elimina \n-ul citit cu cin)


    std::cout << "Observatii (optional): ";
    std::getline(std::cin, observatii);

    std::cout<<"\n";

    //Calculeaza pretul total al rezervarii
    int nopti=CalculeazaDiferentaZile(data_check_in,data_check_out); //functie helper din utils.h

    double pret_total;
    pret_total=nopti*camera.GetPret();

    double discount=0.0;

    int id_rezervare=m_rezervari.size()+1;

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
        r.CalcularePretDupaDiscount();
        r.SetDiscount(discount);
    }
    
    m_rezervari.push_back(r);
    SalvareRezervareFisier(r);

    if(!ExistaClientInFisier(client))
    {
        SalveazaClientInFisier(client);
        m_clienti.push_back(client);
    }

    camera.SetDisponibilitate(false); //Camera rezervata devine ocupata
    ActualizeazaCamereDupaRezervare();

    std::cout << "Rezervarea a fost efectuata cu succes! Detalii:\n";
    r.AfisareDetalii();

}
void Hotel::EfectueazaRezervare()
{
    bool ok=0;
    for(auto& camera : m_camere)
    {
        if(camera.VerificaDisponibilitate()==true)
            ok=1;
    }
    if (ok==0)
    {
        std::cout<<"Momentan nu mai este nicio camera libera."<<"\n"; //Daca nicio camera nu mai e disponibila atunci nu se mai pot efectua rezervari
        std::cout<<"\n";
        return;
    }
    int nr_camera;
    std::cout<<"Selectati camera pe care doriti sa o rezervati: ";
    std::cin>>nr_camera;
    bool gasita=false;
    for(auto& camera : m_camere)
    {
        if (camera.GetNumar()==nr_camera)
        {
            if(camera.VerificaDisponibilitate()==false)
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

                if (CalculeazaDiferentaZile(data_check_in,data_check_out) <= 0)
                {
                    std::cout<<"Datele introduse nu sunt valide"<<"\n";
                    return;
                }

                AdaugaRezervare(camera, data_check_in, data_check_out); //Daca datele de mai sus sunt valide, se apeleaza functia AdaugaRezervare() care continua cu crearea rezervarii

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

void Hotel::VizualizareRezervari()
{
    std::cout<<"Cautati rezervarea dupa: \n";
    std::cout<<"1. ID rezervare\n";
    std::cout<<"2. Nume client\n";
    int opt;
    std::cin>>opt;

    if(opt==1)
    {
        int id;
        std::cout<<"Introduceti ID-ul rezervarii: \n";
        std::cin>>id;

        Rezervare* r=CautaRezervare(id); //CautaRezervare() intoarce un pointer pentru o rezervare existenta
        if(r) //Daca a fost gasita rezervarea, sunt afisate detaliile
            r->AfisareDetalii();
        else
            std::cout<<"Rezervarea nu a fost gasita\n";
    }
    else if(opt==2)
    {
        std::string nume;
        std::cout<<"Introduceti numele pentru care doriti sa vedeti rezervarile efectuate: \n";
        std::cin.ignore();
        std::getline(std::cin,nume);

        std::vector<Rezervare*> rezervari_gasite=CautaRezervare(nume); //CautaRezervare() intoarce un vector de pointeri catre obiecte de tip Rezervare

        if(rezervari_gasite.empty())
        {
            std::cout<<"Nu au fost gasite rezervari pentru acest nume\n";
        }
        else
        {
            for(auto& rezervare : rezervari_gasite)
            {
                rezervare->AfisareDetalii();
                std::cout<<"-------------------------\n";
            }
        }
    }
    else
    {
        std::cout<<"Optiune invalida\n";
    }
}
Rezervare* Hotel::CautaRezervare(int id)
{
    for(auto& rezervare : m_rezervari)
    {
        if(rezervare.GetId()==id)
            return &rezervare; //intoarce referinta catre rezervarea gasita
    }
    return nullptr; //pointer null - rezervarea nu a fost gasita
}

std::vector<Rezervare*> Hotel::CautaRezervare(std::string nume)
{
    std::vector<Rezervare*> rezultate;
    for(auto& rezervare : m_rezervari)
    {
        if(rezervare.GetClient().GetNume()==nume)
            rezultate.push_back(&rezervare); //e adaugata referinta catre rezervarea cautata in vector
    }
    return rezultate;
}
void Hotel::AnuleazaRezervare()
{
    if(m_rezervari.empty())
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

    for(auto& rezervare : m_rezervari)
    {
        if(rezervare.GetId()==id_rezervare)
        {
            gasit=true;

            Camera cam=rezervare.GetCamera();
            int nr_camera=cam.GetNumar(); //Setez statusul camerei ca fiind true (libera)
            
            for(auto& camera : m_camere)
            {
                if(camera.GetNumar()==nr_camera)
                {
                    camera.SetDisponibilitate(true);
                    break;
                }
            }
            m_rezervari.erase(m_rezervari.begin()+pozitie);
            ActualizareRezervariDupaAnulare();
            ActualizeazaCamereDupaRezervare();
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

void Hotel::ActualizareRezervariDupaAnulare() //Rescrie fisierul cu continutul actual al vectorului de rezervari
{
    std::ofstream fout("Fisiere_txt/rezervari.txt", std::ios::out); //std::ios::out este folosit pentru a rescrie fisierul (overwrite) folosind continutul actual din vector
    if(!fout.is_open())
    {
        std::cerr<<"Eroare la deschiderea fisierului"; //standard error stream used to output the errors
        return;
    }

    for(auto& rezervare : m_rezervari)
    {
            fout<<"ID rezervare: "<<rezervare.GetId()<<"\n";
            fout<<"Nume client: "<<rezervare.GetClient().GetNume()<<"\n";
            fout<<"Email: "<<rezervare.GetClient().GetEmail()<<"\n";
            
            const Camera cam = rezervare.GetCamera();

            fout<<"Camera: "<<cam.GetNumar()<<" - "<<cam.GetTip()<<" - "<<cam.GetPret()<<"RON/noapte\n";
            fout<<"Check-in: "<<rezervare.GetDataCheckIn()<<"\n";
            fout<<"Check-out: "<<rezervare.GetDataCheckOut()<<"\n";
            fout<<"Nopti: "<<rezervare.GetNumarNopti()<<"\n";
            fout<<"Pret total: "<<rezervare.GetPretTotal()<<"\n";
            fout<<"Discount: "<<rezervare.GetDiscount()<<"%\n";
            fout<<"Metoda plata: "<<rezervare.GetMetodaPlata()<<"\n";
            fout<<"Observatii: "<<rezervare.GetObservatii()<<"\n";
            
            Review r=rezervare.GetReview();
            fout<<"Rating: "<<r.GetNota()<<"\n";
            fout<<"Comentariu: "<<r.GetComentariu()<<"\n";
            
            fout<<"-------------------------------"<<"\n";
    }
    fout.close();
}
void Hotel::ActualizeazaCamereDupaRezervare() //Rescrie fisierul cu continutul actual al vectorului de camere
{
    std::ofstream fout("Fisiere_txt/camere.txt", std::ios::out); //overwrite
    if(!fout.is_open())
    {
        std::cerr<<"Eroare la deschiderea fisierului"; //standard error stream used to output the errors
        return;
    }

    for(auto& camera : m_camere)
    {
        fout<<camera.GetNumar()<<" ";
        fout<<camera.GetTip()<<" ";
        fout<<camera.GetPret()<<" ";
        fout<<camera.GetStatus()<<"\n";
    }
    fout.close();
}

void Hotel::OferaReview() 
{
    if(m_rezervari.empty())
    {
        std::cout<<"Nu ati efectuat nicio rezervare. Un review poate fi oferit doar daca exista cel putin o rezervare.\n";
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
    for(auto& rezervare : m_rezervari)
    {
        if(rezervare.GetId()==id_rezervare)
        {
            gasit=true;

            std::cout<<"Introduceti rating-ul pe care doriti sa il acordati rezervarii (un numar de la 1 la 5, poate avea si zecimale):\n";
            std::cin>>rating;
            if (rating < 1 || rating > 5) {
                std::cout << "Rating-ul trebuie să fie între 1 și 5.\n";
                return;
            }            
            review.SetNota(rating);
            std::cout<<"Lasati un comentariu in care descrieti experienta dvs: \n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //curata buffer-ul 
            std::getline(std::cin, comentariu);
            review.SetComentariu(comentariu);

            rezervare.SetReview(review);
            ActualizareRezervariDupaAnulare(); //folosesc aceeasi functie care ~rescrie fisierul dupa anulare~ pentru a adauga un review (se actualizeaza continutul fisierului cu cel modificat din vector)
        }
    }
    if(!gasit)
    {
        std::cout<<"Rezervarea cautata nu a fost gasita\n";
    }
}

//Actiuni administrator

void Hotel::LogareAdmin(bool &ok)
{   
    std::string email, parola;
    std::cout<<"Introduceti email-ul: \n";
    std::cin>>email;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //curata buffer-ul

    std::cout<<"Introduceti parola: \n";
    std::cin>>parola;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //curata buffer-ul

    //obiect creat dinamic, tratat ca Autentificabil, dar care va apela metoda suprascrisa din clasa Administrator
    Autentificabil* utilizator=new Administrator("admin@gmail.com","admin123");
    
    if(utilizator->Autentificare(email,parola))
    {
        std::cout<<"V-ati autentificat cu succes!\n";
        ok=true;
    }
    else
    {
        std::cout<<"Mail-ul sau parola introduse sunt incorecte!\n";
    }
    delete utilizator;
}

void Hotel::ScrieCameraInFisier(const Camera& camera)
{
    std::ofstream out("Fisiere_txt/camere.txt", std::ios::app); //deschide in modul append - adauga camera la finalul fisierului
    if(out)
    {
        out<<camera.GetNumar()<<" "<<camera.GetTip()<<" "<<camera.GetPret()<<" "<<camera.GetStatus()<<"\n";
        out.close();
    }
    else
    {
        std::cerr<<"Eroare la deschiderea fisierului.\n"; //standard error stream used to output the errors
    }
}

void Hotel::AdaugaCamere()
{
    int nr_camera;
    std::cout<<"Introduceti numarul camerei: \n";
    std::cin>>nr_camera;
    
    for(auto& camera : m_camere)
    {
        if(camera.GetNumar()==nr_camera)
        {
            std::cout<<"Camera cu ID-ul "<<nr_camera<<" deja exista.\n";
            std::cout<<'\n';
            return;
        }
    }

    std::string tip_camera;
    std::cout<<"Introduceti tipul camerei: \n";
    std::cin>>tip_camera;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //curata buffer-ul

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
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //curata buffer-ul

    std::string confirmare;
    std::cout<<"Sunteti sigur ca doriti sa adaugati o noua camera? Va reamintim detaliile introduse: \n";
    std::cout<<"Numar camera: "<<nr_camera<<"\nTipul camerei: "<<tip_camera<<"\nPretul camerei: "<<pret<<"\nDisponibilitate: "<<status<<"\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    do
    { 
        std::cout<<"Scrieti 'DA' pentru a confirma si a crea noua camera sau 'NU' altfel: \n";
        std::getline(std::cin, confirmare);

        for (auto& c : confirmare) c = toupper(c); // input-ul sa fie case-insensitive

        if(confirmare=="DA")
        {
            Camera newCam(nr_camera, status, pret, tip_camera);
            m_camere.push_back(newCam);
            ScrieCameraInFisier(newCam);
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

void Hotel::GestionareAngajati() //meniu cu optiuni pentru gestionarea angajatilor
{
    int choice;
    std::cout<<"Alegeti: \n";
    do
    {   std::cout<<"1. Vizualizare angajati\n";
        std::cout<<"2. Marire salariala\n";
        std::cout<<"3. Minorare salariala\n";
        std::cout<<"4. Concediere\n";
        std::cout<<"5. Angajare\n";
        std::cout<<"6. Afiseaza statistici despre angajati\n";
        std::cout<<"7. Inapoi\n";
        std::cout<<"Alegeti optiunea: ";
        std::cin>>choice;

        switch (choice)
        {
        case 1:
            VizualizareAngajati();
            break;
        case 2:
            MaresteSalariuAdmin();
            break;
        case 3:
            MicsoreazaSalariuAdmin();
            break;
        case 4:
            ConcediereAngajat();
            break;
        case 5:
            Angajare();
            break;
        case 6:
            AfiseazaStatisticiAngajati();
            break;
        case 7:
            std::cout<<"Inapoi\n";
            break;
        default:
            break;
        }
        
    } while (choice!=7);
}
void Hotel::VizualizareClienti()
{
    if(m_clienti.empty())
    {
        std::cout<<"Momentan nu exista niciun client inregistrat.\n";
        std::cout<<"\n";
    }
    else
    {   std::cout<<"Lista clientilor inregistrati:\n";
        std::cout<<"-----------------------------------\n";
        for(auto& client : m_clienti) {
            client.AfisareDetalii();
            std::cout<<"-----------------------------------\n";
        }
        std::cout<<"\n";
    }
}
void Hotel::VizualizareToateRezervarile() //afiseaza intreg continutul fisierului cu rezervari
{
    std::ifstream fin("Fisiere_txt/rezervari.txt");
    if(!fin.is_open())
    {
        std::cerr<<"Eroare la deschiderea fisierului.\n"; //standard error stream used to output the errors
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
void Hotel::VizualizareAngajati()
{
    for(auto& angajat : m_angajati)
    {
        angajat->AfisareDetalii();
        std::cout<<"\n";
    }
}

void Hotel::MaresteSalariuAdmin()
{
    int id, pozitie=0;
    bool ok=0;

    std::cout<<"Introduceti ID-ul angajatului caruia doriti sa-i mariti salariul:\n";
    std::cin>>id;

    for(auto& angajat : m_angajati)
    {
        if(angajat->GetId()==id)
        {
            ok=1;
            break;
        }
        pozitie++;
    }
    if(ok)
    {
        int suma;
        std::cout<<"Introduceti suma cu care doriti sa mariti salariul angajatului: \n";
        std::cin>>suma;

        //Folosesc operatorul overloaded +
        Angajat* angajat_nou = *(m_angajati[pozitie])+suma; //creez o copie dupa angajatul vechi dar care are salariul modificat

        //Actualizez struct-ul cu statistici pentru angajati
        StatisticiAngajat::EliminaSalariu(m_angajati[pozitie]->GetSalariu(),m_angajati);
        StatisticiAngajat::AdaugaSalariu(angajat_nou->GetSalariu());

        delete m_angajati[pozitie]; //Eliberez vechiul obiect
        m_angajati[pozitie]=angajat_nou; //Inlocuiesc cu noul obiect

        SalveazaAngajatiInFisier();

        std::cout<<"Salariul a fost modificat\n";
    }
    else
    {
        std::cout<<"Angajatul nu a fost gasit.\n\n";
    }
}

void Hotel::MicsoreazaSalariuAdmin()
{
    int id, pozitie=0;
    bool ok=0;
    std::cout<<"Introduceti ID-ul angajatului caruia doriti sa-i micsorati salariul:\n";
    std::cin>>id;
    for(auto& angajat : m_angajati)
    {
        if(angajat->GetId()==id)
        {
            ok=1;
            break;
        }
        pozitie++;
    }
    if(ok)
    {
        int procent;
        std::cout<<"Introduceti procentul cu care doriti sa micsorati salariul angajatului: \n";
        std::cin>>procent;

        m_angajati[pozitie]->MinorareSalariala(procent); //este folosita metoda din clasa Angajat
        SalveazaAngajatiInFisier();

        std::cout<<"Salariul a fost modificat\n";
    }
    else
    {
        std::cout<<"Angajatul nu a fost gasit.\n\n";
    }
    SalveazaAngajatiInFisier();
}

void Hotel::ConcediereAngajat()
{
    int id, pozitie=0;
    bool ok=0;
    std::cout<<"Introduceti ID-ul angajatului pe care doriti sa-l concediati: \n";
    std::cin>>id;

    for(auto& angajat : m_angajati)
    {
        if(angajat->GetId()==id)
        {
            ok=1;
            break;
        }
        pozitie++;
    }
    if(ok)
    {   
        int salariu=m_angajati[pozitie]->GetSalariu();
        delete m_angajati[pozitie]; //sterg de tot obiectul si eliberez memoria
        m_angajati.erase(m_angajati.begin()+pozitie); //sterg pointerul din vector

        StatisticiAngajat::EliminaSalariu(salariu,m_angajati);

        SalveazaAngajatiInFisier();
        std::cout<<"Angajatul cu ID-ul "<<id<<" a fost concediat\n\n";
    }
    else
    {
        std::cout<<"Angajatul nu a fost gasit.\n\n";
    }
    SalveazaAngajatiInFisier();
}

void Hotel::Angajare()
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

    id=m_angajati.size()+1;

    for(auto& c : functie)
    {
        c=tolower(c); //transform string-ul in lowercase pentru a nu fi case-sensitive raspunsul
    }
    if(functie=="ingrijitor")
    {
        AdaugaIngrijitor(nume,email,varsta,id,salariu,functie);
    }
    else if(functie=="receptioner")
    {
        AdaugaReceptioner(nume,email,varsta,id,salariu,functie);
    }
    else if(functie=="bucatar")
    {
        AdaugaBucatar(nume,email,varsta,id,salariu,functie);
    }
    else if(functie=="manager")
    {
        AdaugaManager(nume,email,varsta,id,salariu,functie);
    }
    else
    {
        std::cout<<"Functia introdusa nu exista\n";
    }
}

void Hotel::AfiseazaStatisticiAngajati() //Se afiseaza datele "statice" din struct
{
    std::cout<<"Total angajati: "<<StatisticiAngajat::total_angajati<<"\n";
    std::cout<<"Salariu total: "<<StatisticiAngajat::salariu_total<<"\n";
    std::cout<<"Salariu mediu: "<<StatisticiAngajat::SalariuMediu()<<"\n";
    std::cout<<"Salariu minim: "<<StatisticiAngajat::salariu_minim<<"\n";
    std::cout<<"Salariu maxim: "<<StatisticiAngajat::salariu_maxim<<"\n";
    std::cout<<"\n";
}

//Functiile din optiunea(metoda) angajare()

void Hotel::AdaugaIngrijitor(std::string nume, std::string email, int varsta, int id, int salariu, std::string functie)
{
    int etaj_curatenie;
    std::cout<<"Asociati angajatului etajul la care sa faca curatenie: ";
    std::cin>>etaj_curatenie;

    m_angajati.push_back(new Ingrijitor(nume,email,varsta,id,salariu,functie,etaj_curatenie)); //se creaza pe heap un obiect de tip Ingrijitor si e adaugat in vectorul de angajati
    AdaugaAngajatInFisier(m_angajati.back());
    std::cout<<"Angajatul a fost adaugat cu succes!\n";
}

void Hotel::AdaugaReceptioner(std::string nume, std::string email, int varsta, int id, int salariu, std::string functie)
{
    int nr_limbi;
    std::string schimb, limba;
    std::vector<std::string> limbi_vorbite;

    std::cout<<"Introduceti schimbul angajatului (zi/noapte): ";
    std::cin>>schimb;

    std::cout<<"Introduceti numarul de limbi ce urmeaza sa fie adaugat: ";
    std::cin>>nr_limbi;

    std::cout<<"Introduceti limbile vorbite: \n";
    for(int i=0;i<nr_limbi;i++)
    {
        std::cin>>limba;
        limbi_vorbite.push_back(limba);
    }

    m_angajati.push_back(new Receptioner(nume,email,varsta,id,salariu,functie,schimb,limbi_vorbite)); //se creaza pe heap un obiect de tip Receptioner si e adaugat in vectorul de angajati
    AdaugaAngajatInFisier(m_angajati.back());
    std::cout<<"Angajatul a fost adaugat cu succes!\n";
}

void Hotel::AdaugaBucatar(std::string nume, std::string email, int varsta, int id, int salariu, std::string functie)
{
    std::string specializare,certificare;
    std::vector<std::string> certificari;
    int nr_certificari;

    std::cout<<"Introduceti specializare: ";
    std::cin>>specializare;

    std::cout<<"Introduceti numarul de certificari: ";
    std::cin>>nr_certificari;

    std::cout<<"Introduceti certificarile detinute: ";
    for(int i=0;i<nr_certificari;i++)
    {
        std::cin>>certificare;
        certificari.push_back(certificare);
    }

    m_angajati.push_back(new Bucatar(nume,email,varsta,id,salariu,functie,specializare,certificari)); //se creaza pe heap un obiect de tip Bucatar si e adaugat in vectorul de angajati
    AdaugaAngajatInFisier(m_angajati.back());
    std::cout<<"Angajatul a fost adaugat cu succes!\n";
}

void Hotel::AdaugaManager(std::string nume, std::string email, int varsta, int id, int salariu, std::string functie)
{
    int ani_exp,nr_dept;
    std::vector<std::string> departamente;
    std::string dept;

    std::cout<<"Introduceti anii de experienta: ";
    std::cin>>ani_exp;

    std::cout<<"Introduceti numarul de departamente: ";
    std::cin>>nr_dept;

    std::cout<<"Introduceti departamentele: ";
    for(int i=0;i<nr_dept;i++)
    {
        std::cin>>dept;
        departamente.push_back(dept);
    }

    m_angajati.push_back(new Manager(nume,email,varsta,id,salariu,functie,departamente,ani_exp)); //se creaza pe heap un obiect de tip Manager si e adaugat in vectorul de angajati
    AdaugaAngajatInFisier(m_angajati.back());
    std::cout<<"Angajatul a fost adaugat cu succes!\n";
}

void Hotel::IncarcaAngajatiDinFisier()
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
            IncarcaIngrijitor(nume,email,varsta,id,salariu,functie,atribut1);
        }
        else if(functie=="receptioner")
        {
            IncarcaReceptioner(nume,email,varsta,id,salariu,functie,atribut1,atribut2);
        }
        else if(functie=="bucatar")
        {
            IncarcaBucatar(nume,email,varsta,id,salariu,functie,atribut1,atribut2);
        }
        else if(functie=="manager")
        {
            IncarcaManager(nume,email,varsta,id,salariu,functie,atribut1,atribut2);
        }
    }
    fin.close();
}

//pentru fiecare angajat incarcat din fisier se creeaza pe heap un obiect specific functiei sale
void Hotel::IncarcaIngrijitor(std::string nume, std::string email, int varsta, int id, int salariu, std::string functie, std::string atribut1)
{
    int etaj=std::stoi(atribut1);
    m_angajati.push_back(new Ingrijitor(nume,email,varsta,id,salariu,functie,etaj));
}

void Hotel::IncarcaReceptioner(std::string nume, std::string email, int varsta, int id, int salariu, std::string functie, std::string atribut1, std::string atribut2)
{
    std::string schimb=atribut1;
    std::vector<std::string> limbi;
    std::istringstream limbi_stream(atribut2);
    std::string limba;

    //al doilea atribut contine mai multe limbi: extrag fiecare limba si o adaug in vector
    while(std::getline(limbi_stream, limba, ','))
    {
        limbi.push_back(limba);
    }
    m_angajati.push_back(new Receptioner(nume,email,varsta,id,salariu,functie,schimb,limbi));
}

void Hotel::IncarcaBucatar(std::string nume, std::string email, int varsta, int id, int salariu, std::string functie, std::string atribut1, std::string atribut2)
{
    std::string specializare=atribut1;
    std::vector<std::string> certificari;
    std::istringstream cert_stream(atribut2);
    std::string certificare;

    //la fel ca la receptioner - citim fiecare certificare si o adaugam in vector
    while(std::getline(cert_stream, certificare, ','))
    {
        certificari.push_back(certificare);
    }
    m_angajati.push_back(new Bucatar(nume,email,varsta,id,salariu,functie,specializare,certificari));
}

void Hotel::IncarcaManager(std::string nume, std::string email, int varsta, int id, int salariu, std::string functie, std::string atribut1, std::string atribut2)
{
    int aniExp=std::stoi(atribut2);
    std::vector<std::string> departamente;
    std::istringstream dept_stream(atribut1);
    std::string dept;

    //la fel ca la receptioner - citim fiecare departament si il adaugam in vector
    while(std::getline(dept_stream, dept, ','))
    {
        departamente.push_back(dept);
    }
    m_angajati.push_back(new Manager(nume,email,varsta,id,salariu,functie,departamente,aniExp));
}

void Hotel::SalveazaAngajatiInFisier()
{
    std::ofstream fout("Fisiere_txt/angajati.txt", std::ios::out); //std::ios::out este folosit pentru a rescrie fisierul (overwrite) folosind continutul actual din vector (util pentru functiile de marire/micsorare salariala si concediere)
    if(!fout.is_open())
    {
        std::cerr<<"Eroare la deschiderea fisierului";
        return;
    }
    for(auto& angajat : m_angajati) //parcurgem fiecare angajat din vector
    {
        fout<<angajat->GetFunctie()<<";"<<angajat->GetNume()<<";"<<angajat->GetEmail()<<";"<<angajat->GetVarsta()<<";"
        <<angajat->GetId()<<";"<<angajat->GetSalariu()<<";";

        //Downcast pentru fiecare subtip de angajat (facem acest lucru pentru a scrie atributele specifice fiecarui tip angajat)
        //verificam la runtime daca un pointer/referinta la clasa de baza poate fi convertit in pointer/referinta la o clasa derivata
        //<Angajati*> e un vector de pointeri - fiecare elem pointeaza la un obiect de tipul Angajat - care poate fi Ingrijitor, Bucatar etc
        if(auto ingrijitor=dynamic_cast<Ingrijitor*>(angajat)) //se verifica daca se poate face cast-ul la obiectul derivat - daca nu, se returneaza nullptr si se trece la else
        {
            fout<<ingrijitor->GetEtaj();
        }
        else if(auto receptioner=dynamic_cast<Receptioner*>(angajat))
        {
            fout<<receptioner->GetSchimb()<<";";
            const auto& limbi=receptioner->GetLimbi();
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
            fout<<bucatar->GetSpecializare()<<";";
            const auto& certificari=bucatar->GetCertificari();
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
            const auto& departamente=manager->GetDepartamente();
            for(int i=0;i<departamente.size();i++)
            {
                fout<<departamente[i];
                if(i<departamente.size()-1)
                    fout<<",";
            }
            fout<<";"<<manager->GetExperienta();
        }
        fout<<"\n";
    }
    fout.close();
}

void Hotel::AdaugaAngajatInFisier(Angajat* angajat)
{
    std::ofstream fout("Fisiere_txt/angajati.txt", std::ios::app); //append
    if (!fout.is_open()) {
        std::cerr << "Eroare la deschiderea fisierului.\n";
        return;
    }

    //Aici se intampla acelasi lucru ca la functia anterioara, insa aici primesc ca argument un singur pointer la un angajat si ii verific tipul real, spre deosebire de functia anterioara unde iau toti pointerii de angajati din vector si ii verific
    if (Ingrijitor* i = dynamic_cast<Ingrijitor*>(angajat)) {
        fout << "ingrijitor;"<< i->GetNume() << ";"<< i->GetEmail() << ";"<< i->GetVarsta() << ";"<< i->GetId() << ";"<< i->GetSalariu() << ";"<< i->GetEtaj() << "\n";
    }
    else if (Receptioner* r = dynamic_cast<Receptioner*>(angajat)) {
        fout << "receptioner;"<< r->GetNume() << ";"<< r->GetEmail() << ";"<< r->GetVarsta() << ";"<< r->GetId() << ";"<< r->GetSalariu() << ";"<< r->GetSchimb() << ";";

        const auto& limbi = r->GetLimbi();
        for (int i = 0; i < limbi.size(); ++i) {
            fout << limbi[i];
            if (i < limbi.size() - 1) fout << ",";
        }
        fout << "\n";
    }
    else if (Bucatar* b = dynamic_cast<Bucatar*>(angajat)) {
        fout << "bucatar;"<< b->GetNume() << ";"<< b->GetEmail() << ";"<< b->GetVarsta() << ";"<< b->GetId() << ";"<< b->GetSalariu() << ";"<< b->GetSpecializare() << ";";

        const auto& certif = b->GetCertificari();
        for (int i = 0; i < certif.size(); ++i) {
            fout << certif[i];
            if (i < certif.size() - 1) fout << ",";
        }
        fout << "\n";
    }
    else if (Manager* m = dynamic_cast<Manager*>(angajat)) {
        fout << "manager;"<< m->GetNume() << ";"<< m->GetEmail() << ";"<< m->GetVarsta() << ";"<< m->GetId() << ";"<< m->GetSalariu() << ";";

        const auto& dept = m->GetDepartamente();
        for (int i = 0; i < dept.size(); ++i) {
            fout << dept[i];
            if (i < dept.size() - 1) fout << ",";
        }
        fout<<";"<<m->GetExperienta();
        fout << "\n";
    }
    fout.close();
}

} //namespace
