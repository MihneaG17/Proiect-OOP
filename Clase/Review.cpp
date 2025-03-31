#include "Review.h"
#include <iostream>

Review::Review(): nota(0.0), comentariu("N/A") {}; //Constructor implicit
Review::Review(const Client& client, double nota, std::string comentariu): client(client), nota(nota), comentariu(comentariu) {}; // Constructor parametrizat (foloseste referinta constanta pentru eficienta)
Review::Review(const Review& rw): client(rw.client), nota(rw.nota), comentariu(rw.comentariu) {}; //Copy constructor
Review::~Review() {}; //Destructor

//Getteri si setteri
const Client& Review::getClient() const { return client; }
double Review::getNota() { return nota; }
std::string Review::getComentariu() { return comentariu; }

void Review::setClient(const Client& client) { this->client=client; }
void Review::setNota(double nota) { this->nota=nota; }
void Review::setComentariu(std::string comentariu) { this->comentariu=comentariu; }

//Metode suplimentare
void Review::afisareReview()
{
    client.afisareDetaliiClient();
    std::cout<<"Nota: "<<nota<<"\n";
    std::cout<<"Comentariu: "<<comentariu<<"\n";
}