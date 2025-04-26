#include "Rezervare.h"
#include "Client.h"
#include "Camera.h"
#include "Review.h"
#include "utils.h"
#include <iostream>
#include <string>

Rezervare::Rezervare(): m_id_rezervare(-1), m_data_check_in("-"), m_data_check_out("-"), m_pret_total(0.0), m_numar_nopti(0), m_discount(0.0), m_metoda_plata("-"), m_observatii("-") {}; //Constructor implicit

//Constructor parametrizat
Rezervare::Rezervare(int id_rezervare, std::string data_check_in, std::string data_check_out, double pret_total, 
    const Client& client, const Camera& camera, std::string metoda_plata, std::string observatii, double discount, int numar_nopti):
m_id_rezervare(id_rezervare), m_data_check_in(data_check_in), m_data_check_out(data_check_out), m_pret_total(pret_total), m_client(client), m_camera(camera),
m_metoda_plata(metoda_plata), m_observatii(observatii), m_discount(discount), m_numar_nopti(numar_nopti) {}; 

//Copy Constructor
Rezervare::Rezervare(const Rezervare& r): m_id_rezervare(r.m_id_rezervare), m_data_check_in(r.m_data_check_in), m_data_check_out(r.m_data_check_out), m_pret_total(r.m_pret_total),
m_client(r.m_client), m_camera(r.m_camera), m_discount(r.m_discount), m_numar_nopti(r.m_numar_nopti), m_observatii(r.m_observatii), m_metoda_plata(r.m_metoda_plata) {}; 

//Destructor
Rezervare::~Rezervare() {};

//Getteri si setteri
int Rezervare::GetId() const { return m_id_rezervare; };
std::string Rezervare::GetDataCheckIn() const { return m_data_check_in; };
std::string Rezervare::GetDataCheckOut() const { return m_data_check_out; };
int Rezervare::GetNumarNopti() const { return m_numar_nopti; };
double Rezervare::GetPretTotal() const { return m_pret_total; };
double Rezervare::GetDiscount() const { return m_discount; };
std::string Rezervare::GetMetodaPlata() const { return m_metoda_plata; };
std::string Rezervare::GetObservatii() const { return m_observatii; };
const Client& Rezervare::GetClient() const { return m_client; };
const Camera& Rezervare::GetCamera() const { return m_camera; };
const Review& Rezervare::GetReview() const { return m_review; };

void Rezervare::SetId(int id_rezervare) { m_id_rezervare=id_rezervare; };
void Rezervare::SetDataCheckIn(std::string data_check_in) { m_data_check_in=data_check_in; };
void Rezervare::SetDataCheckOut(std::string data_check_out) { m_data_check_out=data_check_out; };
void Rezervare::SetNumarNopti(int numar_nopti) { m_numar_nopti=numar_nopti; };
void Rezervare::SetDiscount(double discount) { m_discount=discount;  };
void Rezervare::SetMetodaPlata(std::string metoda_plata) { m_metoda_plata=metoda_plata; };
void Rezervare::SetObservatii(std::string observatii) { m_observatii=observatii; };
void Rezervare::SetReview(const Review& review) { m_review=review; };

//Metode suplimentare
void Rezervare::CalcularePretDupaDiscount()
{
    m_pret_total-=(m_pret_total*m_discount/100);
};

void Rezervare::AfisareDetalii()
{
    std::cout<<"ID rezervare: "<<m_id_rezervare<<"\n";
    std::cout<<"Data Check-in: "<<m_data_check_in<<"\n";
    std::cout<<"Data Check-out: "<<m_data_check_out<<"\n";
    std::cout<<"Pret total: "<<m_pret_total<<"\n";
    std::cout<<"Numar nopti: "<<m_numar_nopti<<"\n";
    std::cout<<"Discount aplicat: "<<m_discount<< "%\n";
    std::cout<<"Metoda de plata: "<<m_metoda_plata<< "\n";
    std::cout<<"Observatii: "<<m_observatii<< "\n";
    std::cout<<"\n";
    std::cout<<"Detaliile clientului: \n";
    m_client.AfisareDetalii();
    std::cout<<"Detaliile camerei: \n";
    m_camera.AfisareDetaliiCamera();
};

void Rezervare::CalcularePretTotal() {
    int zile=CalculeazaDiferentaZile(m_data_check_in,m_data_check_out);

    if(zile>0)
    {
        m_pret_total=zile*m_camera.GetPret();
        m_numar_nopti=zile;
    }
    else
        std::cout<<"Datele introduse nu sunt valide.\n";
    };

bool Rezervare::AreReview()
{
    return m_review.GetNota()>0 || m_review.GetComentariu()!="-";
}