# Fsminishell
This Program contains the similiar useful commands from Linux Shell

-Programul conceput are la baza implementarea utilitarelor din Linux. Implementarea acestora a durat 7 zile, alocand un numar de 6 ore pe zi. Acest program este realizat cu ajutorul unor functii care ajutata realizarea utilitarelor cerute din enunt.

-Programul are 19 functii(impreuna cu main-ul) si contine un fisier header. O parte din ele sunt recursive care realizeaza comenzile: tree, find, pwd.

-In fisierul header au fost definite structurile necesare care arata directoarele si fisierele care apartin unui director anume. Implementarea acestora a fost realizata cu liste dublu inlantuite.

-Functiile "create_fs" si "delete_fs" creeaza sistemul de fisiere si implicit il distruge. In prima functie se aloca dinamic si se precizeaza legaturile "root-ul", urmand in ultima parte a programului sa fie distrus prin "delete_fs".

-Functia "touch" adauga un fisier nou in lista de fisiere a unui director anume, pentru adaugarea acestuia se verifica daca mai exista si alte fisiere in lista, urmand tratarea cazurilor.

-Functia "ls" este realizata cu ajutorul a doua functii, una pentru afisarea fisierelor si alta pentru afisarea directoarelor.

-Functia "mkdir" creeaza un un director in directorul curent, mai intai se aloca dinamic un director, specificandu-i legaturile. Se verifica ca la "touch" cele doua cazuri, urmand tratarea fiecaruia separat(daca cumva este primul director sau nu).

-Functia "pwd" este realizat recursiv, afiseaza calea curenta a directorului curent. Prima conditie trateaza cazul in care s-a ajuns la directorul "root", altfel se apeleaza recursiv functia pana se ajunge la el. Afisarea se face in ordinea din Linux.

-Functia "tree" afiseaza intr-o forma asemanatoare cu cea a utilitarului, toate directoarele si fisierele dintr-un director ales, functia utilizeaza ca parametrii: directorul curent si o variabila de tip int cu scopul de a da o forma de afisare ca in Linux. Prima conditie trateaza cazul in care directorul nu are nimic in el, efectuand iesirea din functie. Acest subprogram este realizat recursiv.

-Functia "cd" schimba directorul curent "rad_curent" cu un alt director ce se afla in interiorul acestuia. Aceasta functie s-a realizat recursiv.

-Functia "rm" sterge un fisier dat ca parametru prin numele sau dintr-un director anume. Se parcurge lista de fisiere si se incearca cautarea lui. In caz in care a fost gasit, se incearca obtinerea unui caz in care se afla( daca este un singur fisier, daca se afla la inceput, daca se afla la final, daca nu se regaseste in primele trei cazuri). In caz in care nu exista niciun fisier cu numele dat se afiseaza un mesaj corespunzator

-Functia "rmdir" este construita ca si "rm", iar dupa ce se obtine directorul, va fi apelata functia "rmdir_all" care sterge toate directoarele si fisiere intr-o forma recursiva. Stergerea fisierelor se realizeaza cu functia "rmfile"

-Functia "find" este intr-o forma recursiva, apeland functia "parce_all_files" cu scopul de a gasi fisierele cerute in enunt pentru fiecare director in parte.

-Functia "main" contine apelurile functiilor din enunt, prin citirea unor comenzi si tratarea acestora. (s-au folosit siruri de caractere)
