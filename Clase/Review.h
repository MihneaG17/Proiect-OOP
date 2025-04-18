#ifndef REVIEW_H
#define REVIEW_H

#include <iostream>
#include "Client.h"

class Review {
    //Client client;
    double nota;
    std::string comentariu;
public:
    Review(); //Constructor implicit
    Review(double nota, std::string comentariu); //Constructor parametrizat
    Review(const Review& rw); //Copy Constructor
    ~Review(); //Destructor

    //Getteri si setteri
    //const Client& getClient() const;
    double getNota() const;
    std::string getComentariu() const;

    //void setClient(const Client& client);
    void setNota(double nota);
    void setComentariu(std::string comentariu);

    //Metode suplimentare
    void afisareReview();

};
#endif