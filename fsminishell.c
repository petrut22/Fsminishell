#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#define NMAX 300
//functie cu rolul de a initia radacina root
void create_fs(Directory **radacina)
{
	//se aloca dinamic structura Direcotry
	(*radacina) = malloc(sizeof(Directory));
	//se initializeaza fiecare parametru
	//astfel pentru fisierul root setam parintele NULL
	(*radacina)->parentDir = NULL;
	(*radacina)->name = "/";
	(*radacina)->childFile = NULL;
	(*radacina)->childDir = NULL;
}
//functie cu rolul de a distruge radacina
//sistemului de fisiere prin eliberarea acestuia
void delete_fs(Directory **radacina)
{
	Directory *new_directory;

	new_directory = *radacina;

	free(new_directory);

}
//functie cu rolul de a sorta fisierele cu
//algoritmul bubble sort aplicat listelor
void sortare_files(Directory **rad_curent)
{
	File *aux;

	fisier *fisier_parc;

	int ok = 1;
	//in cazul in care sistemul de fisiere al
	//directorului curent este null atunci iesim din functie
	if ((*rad_curent)->childFile == NULL)
		return;
	fisier_parc = (*rad_curent)->childFile;
	while (ok) {
		ok = 0;
		while (fisier_parc->next != NULL) {
			if (strcmp(fisier_parc->fis->name,
			 fisier_parc->next->fis->name) > 0) {
				aux = fisier_parc->fis;
				fisier_parc->fis = fisier_parc->next->fis;
				fisier_parc->next->fis = aux;
				ok = 1;

			}
			fisier_parc = fisier_parc->next;
		}
		fisier_parc = (*rad_curent)->childFile;

		}
}
//functia are rolul de a adauga fisiere in directorul curent,
//apeland dupa functie de sortare pentru ordinea lexico-grafica
void touch(Directory **rad_curent, char *name, char *content)
{
	fisier *fisier_parc;

	fisier *new_fisier = malloc(sizeof(fisier));
	//se aloca fiecare parametru in parte a structurii
	//fisierului din director
	new_fisier->fis = malloc(sizeof(File));
	new_fisier->fis->name = (char *) malloc(sizeof(char)*100);
	new_fisier->fis->data = (char *) malloc(sizeof(char)*100);
	strcpy(new_fisier->fis->name, name);
	strcpy(new_fisier->fis->data, content);
	new_fisier->fis->size = strlen(content);
	new_fisier->fis->dir = (*rad_curent);
	new_fisier->next = NULL;
	new_fisier->prev = NULL;
	//se verifica daca cumva daca este primmul fisier de adaugat
	if ((*rad_curent)->childFile == NULL) {
		(*rad_curent)->childFile = new_fisier;
		return;
		}

	fisier_parc = (*rad_curent)->childFile;
	while (fisier_parc->next)
		fisier_parc = fisier_parc->next;

	new_fisier->prev = fisier_parc;
	fisier_parc->next = new_fisier;
	sortare_files(rad_curent);

}
//algoritmul de sortare a directoarelor similar ca cel al fisierelor
void sortare_directories(Directory **rad_curent)
{
	Directory *aux;

	director *director_parc = (*rad_curent)->childDir;

	int ok = 1;

	while (ok) {
		ok = 0;
		while (director_parc->next != NULL) {
			if (strcmp(director_parc->dir->name,
				director_parc->next->dir->name) > 0) {
				aux = director_parc->dir;
				director_parc->dir = director_parc->next->dir;
				director_parc->next->dir = aux;
				ok = 1;

			}
			director_parc = director_parc->next;
		}
	director_parc = (*rad_curent)->childDir;

	}
}
//functie cu rolul de a parcurge directoarele din radacina Dir
void parce_directories(Directory *Dir)
{

	director *parce_directories = Dir->childDir;

	while (parce_directories != NULL) {
		if (parce_directories->next == NULL)
			printf("%s", parce_directories->dir->name);
		else
			printf("%s ", parce_directories->dir->name);

	parce_directories = parce_directories->next;
	}

}
//functie cu rolul de a parcurge fisierle din radacina Dir
void parce_files(Directory *director)
{

	fisier *parce_file = director->childFile;

	while (parce_file != NULL) {
		printf("%s ", parce_file->fis->name);
		parce_file = parce_file->next;
	}

}
//ls este functia care va indeplini cerintele din enunt,
//apeland cele doua functii de mai sus
void ls(Directory *rad_curent)
{
	parce_files(rad_curent);
	parce_directories(rad_curent);
	printf("\n");
}

//functie cu rolul de a adauga un director in radacina curenta
void mkdir(Directory **rad_curent, char *name)
{
	director *director_parc;
	//se initializeaza directorul pe care il vom pune in radacina curenta
	director *new_director = malloc(sizeof(director));

	new_director->dir = malloc(sizeof(Directory));
	new_director->dir->childDir = NULL;
	new_director->dir->childFile = NULL;
	new_director->dir->parentDir = (*rad_curent);
	new_director->dir->name = (char *) malloc(sizeof(char)*100);
	strcpy(new_director->dir->name, name);
	new_director->next = NULL;
	new_director->prev = NULL;

	//verificam cazul in care este primul director de adaugat
	//daca este primul director atunci iesim din functie
	if ((*rad_curent)->childDir == NULL) {
		(*rad_curent)->childDir = new_director;
		return;
	}
	//operatiile necesare de legare a "nodului" cu "lista"
	director_parc = (*rad_curent)->childDir;
	while (director_parc->next)
		director_parc = director_parc->next;

	new_director->prev = director_parc;
	director_parc->next = new_director;
	sortare_directories(rad_curent);
}

//functie cu rolul de a afisa calea de la radacina la directorului curent
// se paote observa implementarea ei intro-o forma recursiva
void pwd(Directory *rad_curent)
{
	if (rad_curent->parentDir == NULL) {
		printf("%s", rad_curent->name);
		return;
		}
	else {
		pwd(rad_curent->parentDir);
		if (rad_curent->parentDir->name == "/")
			printf("%s", rad_curent->name);
		else
			printf("/%s", rad_curent->name);
	}
}

//aceasta functie implementeaza utilitarul din linux
//nivel ajuta la afisarea in forma asemnatoare
//lista de directoare si fisiere ca in linux
void tree(Directory *rad_curent, int nivel)
{
	int i;

	fisier *parce_file;

	director *parce_dir;

	if (rad_curent->childFile == NULL && rad_curent->childDir == NULL)
		return;

		parce_file = rad_curent->childFile;

		while (parce_file != NULL) {
			for (i = 0; i < 4 * (nivel+1); i++)
				printf(" ");
			printf("%s\n", parce_file->fis->name);
			parce_file = parce_file->next;
		}

		parce_dir = rad_curent->childDir;

		while (parce_dir != NULL) {
			for (i = 0; i < 4 * (nivel+1); i++)
				printf(" ");
			printf("%s\n", parce_dir->dir->name);
			tree(parce_dir->dir, nivel+1);
			parce_dir = parce_dir->next;
		}
}
//functia schimba directorul curent cu altul care face parte din el
//acesta intai trebuie verificat daca apartine lui "rad_curent"
//apoi se face schimbarea
void cd(Directory **rad_curent, char *name)
{
	int ok = 0;

	director *director_parce;

	Directory *keep_director;

	if (strcmp(name, "..") == 0) {
		*(rad_curent) = (*rad_curent)->parentDir;
		return;
		}
	else {
		director_parce = (*rad_curent)->childDir;
		while (director_parce && ok == 0) {
			if (strcmp(director_parce->dir->name, name) == 0) {
				ok = 1;
				keep_director = director_parce->dir;
			}
			director_parce = director_parce->next;
		}

		if (ok == 1)
			(*rad_curent) = keep_director;
		else
			printf("Cannot move to '%s': No such directory!\n",
				name);

	}


}
//functia sterge un fisier din director
void rm(Directory **rad_curent, char *name)
{
	int ok = 0;

	fisier *parce_file = (*rad_curent)->childFile;

	fisier *new_file;
	//implementarea functiei a fost facuta pe 4 cazuri
	while (parce_file != NULL) {
		//se verifica daca fisierul se gaseste in lista de fisiere
		if (strcmp(parce_file->fis->name, name) == 0) {
			ok = 1;
			{
			//acesta este cazul in care fisierul este de unul singur
			if (parce_file->prev == NULL &&
				parce_file->next == NULL) {
				(*rad_curent)->childFile = NULL;
				free(parce_file->fis->name);
				free(parce_file->fis->data);
				free(parce_file->fis);
				free(parce_file);
				return;
				}
			//acesta este cazul in care se afla la final
			if (parce_file->next == NULL) {
				parce_file->prev->next = NULL;
				free(parce_file->fis->name);
				free(parce_file->fis->data);
				free(parce_file->fis);
				free(parce_file);
				return;

			}
			//acesta este cazul in care se afla la inceput
			if (parce_file->prev == NULL) {
				(*rad_curent)->childFile = parce_file->next;
				(*rad_curent)->childFile->prev = NULL;
				free(parce_file->fis->name);
				free(parce_file->fis->data);
				free(parce_file->fis);
				free(parce_file);
				return;
				}
			//in continuare urmeaza cazul in care se
			//afla intr-o pozitie diferita fata de cele de mai sus
				new_file = parce_file;
				parce_file->next->prev = parce_file->prev;
				parce_file->prev->next = parce_file->next;
				free(new_file->fis->name);
				free(new_file->fis->data);
				free(new_file->fis);
				free(new_file);


			}
			break;
		}
		parce_file = parce_file->next;
	}

	if (ok == 0)
		printf("Cannot remove '%s': No such file!\n", name);

	}

//functia va fi folosita in rmdir pentru stergerea tuturor fisierelor
//dintr-un director
void rmfile(fisier *file_del)
{
	fisier *new_file = file_del;

	while (file_del != NULL) {
		free(file_del->fis->name);
		free(file_del->fis->data);
		free(file_del->fis);
		new_file = file_del;
		file_del = file_del->next;
		free(new_file);
	}
}
//functia va sterge intr-un mod recursiv fiecare director din directorul curent
//urmand stergerea implicita a fisierelor
void rmdir_all(Directory **rad_del)
{
	director *new_directory;

		if ((*rad_del)->childDir == NULL) {
			free((*rad_del)->name);
			rmfile((*rad_del)->childFile);
			free((*rad_del));
			return;
		}

			while ((*rad_del)->childDir != NULL) {
				rmdir_all(&((*rad_del)->childDir->dir));
				new_directory = (*rad_del)->childDir;
				(*rad_del)->childDir =
				(*rad_del)->childDir->next;
				free(new_directory);
			}

		free((*rad_del)->name);
		rmfile((*rad_del)->childFile);
		free((*rad_del));
}
//functia va sterge un director din directorul curent
void rmdir(Directory **rad_curent, char *name)
{
	int ok = 0;

	director *parce_dir = (*rad_curent)->childDir;

	director *new_dir;
	// vor fi 4 cazuri in vederea stergerii directorului
	while (parce_dir != NULL) {
		if (strcmp(parce_dir->dir->name, name) == 0) {
			ok = 1;
			//cazul in care exista un singur director
			if (parce_dir->prev == NULL &&
				parce_dir->next == NULL) {
				rmdir_all(&(parce_dir->dir));
				(*rad_curent)->childDir = NULL;
				free(parce_dir);
				return;
			}
			//cazul in care se afla la final
			if (parce_dir->next == NULL) {
				rmdir_all(&(parce_dir->dir));
				parce_dir->prev->next = NULL;
				free(parce_dir);
				return;
			}
			//cazul in care se afla la inceput
			if (parce_dir->prev == NULL) {
				rmdir_all(&(parce_dir->dir));
				(*rad_curent)->childDir = parce_dir->next;
				(*rad_curent)->childDir->prev = NULL;
				free(parce_dir);
				return;
				}
			//cazul in care se gaseste intr-o pozitie
				//diferita fata de cele de mai sus
				rmdir_all(&(parce_dir->dir));
				parce_dir->next->prev = parce_dir->prev;
				parce_dir->prev->next = parce_dir->next;
				free(parce_dir);
		break;
		}
		parce_dir = parce_dir->next;
}
	if (ok == 0)
		printf("Cannot remove '%s': No such directory!\n", name);

}

//functie cu rolul de a parcurge lista de fisiere
//pentru afisarea fisierului cu cerintele cerute
//aceasta functie este folosita de find
void parce_all_files(Directory *rad_curent,
	int min_size, int max_size, char *subcontent)
{
	fisier *parce_file = rad_curent->childFile;

	while (parce_file) {
		if (parce_file->fis->size >= min_size &&
			parce_file->fis->size <= max_size
			&& strstr(parce_file->fis->data, subcontent) != NULL)
			printf("%s ", parce_file->fis->name);

		parce_file = parce_file->next;
	}

}
//gasesete fisierele pana la o adancime anume
//parcurgand directoarele intr-o froma recursiva
void find(Directory *rad_curent, int max_depth,
	int min_size, int max_size, char *subcontent)
{
	director *parce_director = rad_curent->childDir;

	if (max_depth < 0)
		return;
	if (max_depth == 0 || rad_curent->childDir == NULL) {
		parce_all_files(rad_curent, min_size, max_size, subcontent);
		return;
	}

	parce_all_files(rad_curent, min_size, max_size, subcontent);
	while (parce_director) {
		find(parce_director->dir, max_depth-1,
		min_size, max_size, subcontent);
		parce_director = parce_director->next;
	}
}

int main(void)
{
	Directory *radacina = NULL;

	char s[NMAX], nume[NMAX], content[NMAX];

	int max_depth, min_size, max_size;

	int nr;

	char *p;
	//folosirea comenzilor se face cu ajutorul unor if-uri
	//urmand iesirea din while prin delete_fs
	while (fgets(s, NMAX, stdin)) {
		s[strlen(s) - 1] = 0;

		if (strcmp(s, "create fs") == 0)
			create_fs(&radacina);


		if (strcmp(s, "delete fs") == 0) {
			delete_fs(&radacina);
			break;
		}

		if (strstr(s, "touch")) {
			nr = 1;
			p = strtok(s, " ");
			while (p != NULL) {
				if (nr == 2)
					strcpy(nume, p);
				if (nr == 3)
					strcpy(content, p);
				nr++;
				p = strtok(NULL, " ");
			}
			touch(&radacina, nume, content);
	}

		if (strstr(s, "mkdir")) {
			nr = 1;
			p = strtok(s, " ");
			while (p != NULL) {
				if (nr == 2)
					strcpy(nume, p);
				nr++;
				p = strtok(NULL, " ");
			}
			mkdir(&radacina, nume);
	}
		if (strcmp(s, "ls") == 0)
			ls(radacina);

		if (strcmp(s, "pwd") == 0) {
			pwd(radacina);
			printf("\n");
		}

		if (strstr(s, "cd")) {
			nr = 1;
			p = strtok(s, " ");
			while (p != NULL) {
				if (nr == 2)
					strcpy(nume, p);
				nr++;
				p = strtok(NULL, " ");
			}
			cd(&radacina, nume);
		}

		if (strcmp(s, "tree") == 0) {
			printf("%s\n", radacina->name);
			tree(radacina, 0);
		}

		if (strstr(s, "rm") && strstr(s, "rmdir") == NULL) {
			nr = 1;
			p = strtok(s, " ");
			while (p != NULL) {
				if (nr == 2)
					strcpy(nume, p);
			nr++;
			p = strtok(NULL, " ");
		}
			rm(&radacina, nume);
		}

		if (strstr(s, "rmdir")) {
			nr = 1;
			p = strtok(s, " ");
			while (p != NULL) {
				if (nr == 2)
					strcpy(nume, p);
				nr++;
				p = strtok(NULL, " ");
		}
			rmdir(&radacina, nume);
		}

		if (strstr(s, "find")) {
			nr = 1;
			p = strtok(s, " ");
			while (p != NULL) {
				if (nr == 2)
					max_depth = atoi(p);
				if (nr == 3)
					min_size = atoi(p);
				if (nr == 4)
					max_size = atoi(p);
				if (nr == 5)
					strcpy(nume, p);
			nr++;
			p = strtok(NULL, " ");
		}

		find(radacina, max_depth, min_size, max_size, nume);
		printf("\n");
		}
	}
	return 0;

}
