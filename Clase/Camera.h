#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

class Camera
{
    int numar;
    bool status;
    int pret_noapte;
    std::string tip_camera;
    static int totalCamere;
public:
    Camera(); //Constructor implicit
    Camera(int numar, bool status, int pret_noapte, std::string tip_camera); //Constructor parametrizat

    ~Camera(); //Destructor

    //Getteri si setteri
    int getNumar();
    int getPret();
    std::string getTip();
    static int getTotalCamere();

    void setNumar(int numar);
    void setPret(int pret_noapte);
    void setDisponibilitate(bool status);
    void setTip(std::string tip_camera);

    //Metode suplimentare
    bool verificaDisponibilitate();
    void afisareDetaliiCamera();

    //Operator overload 
    //Overload pe operatorul de citire --- urmeaza --- pentru Administrator (adaugare camera)
};

#endif //CAMERA_H