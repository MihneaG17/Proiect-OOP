#include "Review.h"
#include <iostream>

namespace HotelManagement {

Review::Review(): m_nota(0.0), m_comentariu("-") {}; //Constructor implicit
Review::Review(double nota, std::string comentariu): m_nota(nota), m_comentariu(comentariu) {}; // Constructor parametrizat (foloseste referinta constanta pentru eficienta)
Review::Review(const Review& rw): m_nota(rw.m_nota), m_comentariu(rw.m_comentariu) {}; //Copy constructor
Review::~Review() {}; //Destructor

//Cand introduc inapoi atributul client trebuie sa am grija sa-l introduc si in constructori

//Getteri si setteri
double Review::GetNota() const { return m_nota; }
std::string Review::GetComentariu() const { return m_comentariu; }

//void Review::setClient(const Client& client) { this->client=client; }
void Review::SetNota(double nota) { m_nota=nota; }
void Review::SetComentariu(std::string comentariu) { m_comentariu=comentariu; }

//Metode suplimentare
void Review::AfisareReview()
{
    std::cout<<"Nota: "<<m_nota<<"\n";
    std::cout<<"Comentariu: "<<m_comentariu<<"\n";
}
}