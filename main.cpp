#include <iostream>
#include <vector>

#include "Clase/Hotel.h"

using namespace HotelManagement; //tot codul actual este pus in namespace-ul HotelManagement - momentan nu schimba functionalitatea, insa in cazul in care voi adauga si alte componente, acesta va fi util pentru a nu exista conflicte de nume in cadrul functiilor si claselor

int main()
{   
    Hotel hotel;
    hotel.Ruleaza();
    
    return 0;
}