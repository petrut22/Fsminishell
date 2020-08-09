# Fsminishell
This Program contains the similiar useful commands from Linux shell
Timp de implementare: 2 saptamani

Programul de fata descrie jocul battleship cu toate optiunile sale si anume
: Randomize map si Destroy in advance​

Modul de implementare:

Jocul este construit pe baza bibliotecii ncurses si cuprinde ferestre care se
deschid pe baza unor alegeri luate cu ajutorul butoanelor care sunt afisate 
in joc. Programul de deschide cu primul meniu care cuprinde 4 optiuni: 
New game, Resume, Score, Exit.  Prima optiune incepe modul de joc, 
dar mai intai intreaba jucatorul daca doreste o mapa random sau una 
deja existenta(se afla in arhiva, iar programul se executa impreuna cu acesta);
Dupa alegera optiunii jucatorul are in fata lui in stanga mapa de joc,
iar in stanga se afla mapa computerului care este completata cu nave.

In timpul jocului se pot alege unele optiuni prezente cum ar fi
Randomize map, Destroy in advance​ sau Intoarcere la meniu. In cazul
in care jucatorul se afla in meniu se poate reintoarce in joc, apasand
Resume. Scorul va fi afisat in momentul in care ori jucatorul ori 
calculatorul doboara toate navele si poate fi vizualizat chiar si din meniu.

Daca se doreste iesirea din joc se apasa PE butonul Exit.

Partea de bonus a programului consta in alegererea unei mape existente sau
una random dupa apasarea butonului New Game. Programul foloseste matrici si
vectori alocati dinamic, functii care asigura eliberarea memoriei, citirea
matricilor, configurarea navelor, implementarea jocului, asigurarea ca o nava
sa se afle in interiorului hartii etc. Inca o parte de bonus mai poate fi 
implementarea unei repozitionari, astfel cand jucatorul se afla de exemplu
la marginea mapei in dreapta, daca apasata pe sageata dreapta, cursorul se va
repozitiona la incepului hartii. 

Main-ul asigura dimensiunile anumitor ferestre cum ar fi meniu si joc,
Meniul este unul generalizat, se bazeaza pe deplasarea cursorului si alegerea 
unei optiuni(variabila highlight asigura pozitia in vectorul primului meniu).
Ca la final sa obtinem obtiunea aleasa prin variabila tasta_aleasa.

Popularea hartilor se face in functia "random_map" care apeleaza la randul
ei alte functii specifice pentru navele de o casuta, 2 casute, 3 casute, 4 
casute. Spre exemplu, functia pentru o nava de o casuta determina 2 pozitii
i si j random si se asigura ca elementul de coordonate date se afla pe harta
si nu a fost accesat anterior. Urmatoarele functii se bazeaza pe conceptul
de la prima functie, astfel dupa gasirea unei pozitii se incearca continuarea
completarii in directiile sus, jos, dreapta, stanga cu conditia de a nu depasi
mapa.

Jocul este implementat pe baza altor functii care asigura pozitia cursorului
jucatorului, determina scorului fiecaruia, indeplinirea cerintelor de la 
taskul 4.

Modelul de harta este scris pe o singura linie cu codificarea necesara si este
folosit in urma comenzii ./battleship battleship_fis1
