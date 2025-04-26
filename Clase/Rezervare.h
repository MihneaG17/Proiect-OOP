#ifndef REZERVARE_H
#define REZERVARE_H

#include "Camera.h"
#include "Client.h"
#include "Review.h"
#include "utils.h"
#include <iostream>

class Rezervare
{
    int m_id_rezervare;
    std::string m_data_check_in;
    std::string m_data_check_out;
    int m_numar_nopti;
    double m_pret_total;
    double m_discount;
    std::string m_metoda_plata;
    std::string m_observatii;
    Client m_client;
    Camera m_camera;
    Review m_review;
public:
    Rezervare(); //Constructor implicit
    Rezervare(int id_rezervare, std::string data_check_in, std::string data_check_out, double pret_total, 
              const Client& client, const Camera& camera, std::string metoda_plata, std::string observatii, double discount, int numar_nopti); //Constructor parametrizat
    Rezervare(const Rezervare& r); //Copy constructor
    ~Rezervare(); //Destructor

    //Getteri si setteri
    int GetId() const;
    std::string GetDataCheckIn() const;
    std::string GetDataCheckOut() const;
    int GetNumarNopti() const;
    double GetPretTotal() const;
    double GetDiscount() const;
    std::string GetMetodaPlata() const;
    std::string GetObservatii() const;
    const Client& GetClient() const;
    const Camera& GetCamera() const;
    const Review& GetReview() const;

    void SetId(int id);
    void SetDataCheckIn(std::string data_check_in);
    void SetDataCheckOut(std::string data_check_out);
    void SetNumarNopti(int numar_nopti);
    void SetDiscount(double discount);
    void SetMetodaPlata(std::string metoda_plata);
    void SetObservatii(std::string observatii);
    void SetReview(const Review& review);
    

    //Metode suplimentare
    void CalcularePretDupaDiscount(); //Pret calculat dupa aplicarea discountului
    void AfisareDetalii();
    void CalcularePretTotal();
    bool AreReview();
};
#endif //REZERVARE_H
