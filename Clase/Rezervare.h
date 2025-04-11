#ifndef REZERVARE_H
#define REZERVARE_H

#include "Camera.h"
#include "Client.h"
#include "Review.h"
#include "utils.h"
#include <iostream>

class Rezervare
{
    int id_rezervare;
    std::string data_check_in;
    std::string data_check_out;
    int numar_nopti;
    double pret_total;
    double discount;
    std::string metoda_plata;
    std::string observatii;
    Client client;
    Camera camera;
    Review review;
public:
    Rezervare(); //Constructor implicit
    Rezervare(int id_rezervare, std::string data_check_in, std::string data_check_out, double pret_total, 
              const Client& client, const Camera& camera, std::string metoda_plata, std::string observatii, double discount, int numar_nopti); //Constructor parametrizat
    Rezervare(const Rezervare& r); //Copy constructor
    ~Rezervare(); //Destructor

    //Getteri si setteri
    int getId();
    std::string getDataCheckIn();
    std::string getDataCheckOut();
    int getNumarNopti();
    double getPretTotal();
    double getDiscount();
    std::string getMetodaPlata();
    std::string getObservatii();
    const Client& getClient() const;
    const Camera& getCamera() const;
    const Review& getReview() const;

    void setId(int id);
    void setDataCheckIn(std::string data_check_in);
    void setDataCheckOut(std::string data_check_out);
    void setNumarNopti(int numar_nopti);
    void setDiscount(double discount);
    void setMetodaPlata(std::string metoda_plata);
    void setObservatii(std::string observatii);
    void setReview(const Review& review);
    

    //Metode suplimentare
    void prelungireRezervare(int nopti);
    void calcularePretDupaDiscount(); //Pret calculat dupa aplicarea discountului
    void afisareDetalii();
    void calcularePretTotal();
    bool areReview();
};
#endif //REZERVARE_H
