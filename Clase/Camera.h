#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

class Camera
{
    int m_numar;
    bool m_status;
    int m_pret_noapte;
    std::string m_tip_camera;
    static int m_total_camere;
public:
    Camera(); //Constructor implicit
    Camera(int numar, bool status, int pret_noapte, std::string tip_camera); //Constructor parametrizat

    ~Camera(); //Destructor

    //Getteri si setteri
    int GetNumar() const;
    int GetPret() const;
    std::string GetTip() const;
    bool GetStatus() const;
    static int GetTotalCamere();

    void SetNumar(int numar);
    void SetPret(int pret_noapte);
    void SetDisponibilitate(bool status);
    void SetTip(std::string tip_camera);

    //Metode suplimentare
    bool VerificaDisponibilitate();
    void AfisareDetaliiCamera();

    //Overloading operator <<
    friend std::ostream& operator<<(std::ostream& out, Camera& cam); //functie friend deoarece accesez atributele private ale clasei (fara a folosi getteri)

};

#endif //CAMERA_H