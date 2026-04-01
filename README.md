Proiect POO - Sistem Gestiune Hotelieră "All-in-one"



Proiectul meu simulează funcționarea unei agenții de turism digitale, fiind o încercare de a vedea cum se transformă o structură reală de business în cod C++. Am ales această temă deoarece industria călătoriilor este una dintre cele mai dinamice, implicând o gestiune masivă de date între cei care oferă servicii și cei care le folosesc. Aplicația nu este doar un catalog, ci un sistem interactiv unde utilizatorii pot experimenta rolul de Proprietar (care administrează hoteluri sau transporturi) sau de Client (care își gestionează bugetul și face rezervări).

Pentru a rezolva cerințele tehnice ale proiectului, am folosit 12 clase organizate riguros.De asemenea, am integrat toate conceptele învățate la curs: de la polimorfism, care îmi permite să calculez prețurile diferit pentru fiecare tip de serviciu, până la moștenirea în diamant pentru pachetele de vacanță, o problemă tehnică pe care am rezolvat-o prin moștenire virtuală. Totul este coordonat de un meniu inteligent de tip Singleton, care asigură o singură instanță de control pe parcursul rulării.

Pentru a preveni erorile sau închiderea bruscă a programului, am implementat un sistem de excepții custom. Acestea actioneaza atunci cand un client introduce date greșite sau încearcă să cumpere ceva fără să aibă destui bani în cont. În plus, am avut mare grijă la gestiunea memoriei, folosind Regula celor 3 și destructori speciali pentru a mă asigura că fiecare obiect creat este șters corect la final. 

Programul mai are multe funcții și idei de implementat, întrucât doresc să dezvolt acest sistem mai departe, însă aceasta este fundația solidă de la care plec pentru partea 1 a proiectului.

Pentru a rula programul: g++ -std=c++20 main.cpp Utilizator.cpp Client.cpp Proprietar.cpp Serviciu.cpp Cazare.cpp Transport.cpp PachetVacanta.cpp Rezervare.cpp InterfataSistem.cpp -o program && ./program
