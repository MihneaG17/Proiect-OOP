#ifndef REVIEW_H
#define REVIEW_H

#include <iostream>
#include "Client.h"

class Review {
    double m_nota;
    std::string m_comentariu;
public:
    Review(); //Constructor implicit
    Review(double nota, std::string comentariu); //Constructor parametrizat
    Review(const Review& rw); //Copy Constructor

    ~Review(); //Destructor

    //Getteri si setteri
    double GetNota() const;
    std::string GetComentariu() const;

    //void setClient(const Client& client);
    void SetNota(double nota);
    void SetComentariu(std::string comentariu);

    //Metode suplimentare
    void AfisareReview();

};
#endif