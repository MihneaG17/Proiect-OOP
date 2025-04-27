#include "Camera.h"
#include <iostream>

int Camera::m_total_camere = 0;
//Constructori si destructor
Camera::Camera(): m_numar(0), m_status(0), m_pret_noapte(0), m_tip_camera("Nedefinit") { m_total_camere++; }; //Constructor implicit

//Constructor parametrizat
Camera::Camera(int numar, bool status, int pret_noapte, std::string tip_camera): m_numar(numar), m_status(status), m_pret_noapte(pret_noapte), m_tip_camera(tip_camera) {};

//Copy Constructor
Camera::Camera(const Camera& cam): m_numar(cam.m_numar), m_status(cam.m_status), m_pret_noapte(cam.m_pret_noapte), m_tip_camera(cam.m_tip_camera) {};
//Destructor
Camera::~Camera() {};

//Getteri si setteri
int Camera::GetNumar() const { return m_numar; };
int Camera::GetPret() const { return m_pret_noapte; };
std::string Camera::GetTip() const { return m_tip_camera; };
bool Camera::GetStatus() const { return m_status; };
int Camera::GetTotalCamere() { return m_total_camere; }

void Camera::SetNumar(int numar) { m_numar=numar; };
void Camera::SetPret(int pret_noapte) { m_pret_noapte=pret_noapte; };
void Camera::SetDisponibilitate(bool status) { m_status=status; };
void Camera::SetTip(std::string tip_camera) { m_tip_camera=tip_camera; };

//Metode suplimentare
bool Camera::VerificaDisponibilitate() { return m_status; };
void Camera::AfisareDetaliiCamera() 
{
    std::cout<<"Numar camera: "<<m_numar<<"\n";
    std::cout<<"Status: "<<m_status<<"\n";
    std::cout<<"Pret: "<<m_pret_noapte<<"\n";
    std::cout<<"Tip: "<<m_tip_camera<<"\n";
    std::cout<<"\n";
};

//Overloading operator <<

std::ostream& operator<<(std::ostream& out, Camera& cam) //Afiseaza detaliile camerei
{
    out<<"Camera "<<cam.m_numar<<" - "<<cam.m_tip_camera<<" - "<<cam.m_pret_noapte<<" RON/noapte";
    return out;
}

