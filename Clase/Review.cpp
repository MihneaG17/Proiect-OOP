#include "Review.h"
#include <iostream>

Review::Review(): nota(0.0), comentariu("N/A") {}; //Constructor implicit
Review::Review(double nota, std::string comentariu): nota(nota), comentariu(comentariu) {}; // Constructor parametrizat (foloseste referinta constanta pentru eficienta)
Review::Review(const Review& rw): nota(rw.nota), comentariu(rw.comentariu) {}; //Copy constructor
Review::~Review() {}; //Destructor

//Cand introduc inapoi atributul client trebuie sa am grija sa-l introduc si in constructori

//Getteri si setteri
//const Client& Review::getClient() const { return client; } - Am "dezactivat" temporar aceste metode si atributul client deoarece momentan nu sunt folosite dar vor fi implementate in viitor
double Review::getNota() const { return nota; }
std::string Review::getComentariu() const { return comentariu; }

//void Review::setClient(const Client& client) { this->client=client; }
void Review::setNota(double nota) { this->nota=nota; }
void Review::setComentariu(std::string comentariu) { this->comentariu=comentariu; }

//Metode suplimentare
void Review::afisareReview()
{
    //client.afisareDetaliiClient();
    std::cout<<"Nota: "<<nota<<"\n";
    std::cout<<"Comentariu: "<<comentariu<<"\n";
}