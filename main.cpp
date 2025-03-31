#include <iostream>
#include <vector>

#include "Clase/Persoana.h"
#include "Clase/Angajat.h"
#include "Clase/Client.h"
#include "Clase/Camera.h"
#include "Clase/Rezervare.h"
#include "Clase/Review.h"

int main()
{   
    Client client("Mihnea","mihnea298@gmail.com",19,101,{1,2,3});
    Camera camera(1, true, 200, "Double");
    Rezervare rezervare(1, "2025-04-01", "2025-04-06", 0.0, client, camera, "Card", "N/A", 10.0, 0);
    
    rezervare.calcularePretTotal();
    rezervare.calcularePretDupaDiscount();
    rezervare.afisareDetalii();
    

    return 0;
}