# Proiect OOP - Sistem de management pentru hotel - Dobrin Mihnea-Gabriel - Grupa 143
 - Proiect realizat in C++ pentru materia Programare Orientata pe Obiecte. </br>
 - Acest proiect presupune proiectarea unui Sistem de management pentru hotel. Cand programul este rulat, utilizatorul are 2 optiuni - deschiderea meniului pentru clienti si deschiderea meniului pentru administrator. Fiecare meniu diferite optiuni, cum ar fi: vizualizarea camerelor disponibile, efectuarea unei rezervari, anularea unei rezervari (pentru clienti), optiuni legate de gestionarea angajatilor, precum si de vizualizare a statisticilor din hotel (numar de angajati, rezervari efectuate, clienti inregistrati etc).
 - Datele sunt stocate in fisiere .txt, iar la rularea programului datele deja existente in aceste fisiere sunt incarcate in vectori pentru a permite operatii asupra lor. </br>
 - Proiectul este realizat respectand cerintele si coding guideline-ul primit in cadrul laboratorului de POO.
 - Pentru a rula programul, este necesara crearea manuala a executabilului. Se ruleaza in cmd, in folderul in care sunt salvate fisierele proiectului, urmatoarea comanda:
 `g++ main.cpp Clase/Angajat.cpp Clase/Persoana.cpp Clase/Camera.cpp Clase/Client.cpp Clase/Rezervare.cpp Clase/Review.cpp Clase/Hotel.cpp Clase/Receptioner.cpp Clase/Ingrijitor.cpp Clase/Bucatar.cpp Clase/Manager.cpp Clase/Administrator.cpp Clase/utils.cpp -o program`. Se va crea un fisier .exe care poate fi rulat tot in cmd introducand comanda `[nume-fisier].exe`.
 - Pentru optiunea Administrator din meniu este necesara introducerea unui mail si a unei parole. Credentialele asteptate pentru permiterea logarii sunt `admin@gmail.com` (mail) si `admin123` (parola) ❗.
 - Proiectul a fost scris in Visual Studio Code.

