#include "Camera.h"
#include <iostream>

int Camera::totalCamere = 0;
//Constructori si destructor
Camera::Camera(): numar(0), status(0), pret_noapte(0), tip_camera("Nedefinit") { totalCamere++; }; //Constructor implicit

//Constructor parametrizat
Camera::Camera(int numar, bool status, int pret_noapte, std::string tip_camera): numar(numar), status(status), pret_noapte(pret_noapte), tip_camera(tip_camera) { totalCamere++; };

Camera::~Camera() {};

//Getteri si setteri
int Camera::getNumar() { return numar; };
int Camera::getPret() { return pret_noapte; };
std::string Camera::getTip() { return tip_camera; };
int Camera::getTotalCamere() { return totalCamere; }

void Camera::setNumar(int numar) { this->numar=numar; };
void Camera::setPret(int pret_noapte) { this->pret_noapte=pret_noapte; };
void Camera::setDisponibilitate(bool status) { this->status=status; };
void Camera::setTip(std::string tip_camera) { this->tip_camera=tip_camera; };

//Metode suplimentare
bool Camera::verificaDisponibilitate() { return status; };
void Camera::afisareDetaliiCamera() 
{
    std::cout<<"Numar camera: "<<numar<<"\n";
    std::cout<<"Status: "<<status<<"\n";
    std::cout<<"Pret: "<<pret_noapte<<"\n";
    std::cout<<"Tip: "<<tip_camera<<"\n";
};

//Operator overload
//Overload pe operatorul de citire --- urmeaza --- pentru Administrator (adaugare camera)