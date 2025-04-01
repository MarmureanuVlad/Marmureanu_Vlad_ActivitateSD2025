// lucrare: functii, vectori, fisiere, LS, LD, HASH

// inserat intr o struct, de calc ceva, afisare, dezaloc SAU de luat dintr o strcut si pus in alta

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

//creare structura pentru un nod dintr-o lista dublu inlantuita
struct Nod {
	Masina info;
	struct Nod* next;
	struct Nod* prev;
};
typedef struct Nod Nod;
//creare structura pentru Lista Dubla
struct Lista {
	Nod* first;
	Nod* last;
};
typedef struct Lista Lista;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasiniInceput(Lista list) {
	//afiseaza toate elemente de tip masina din lista dublu inlantuita
	//prin apelarea functiei afisareMasina()
	Nod* p = list.first;
	while (p) {
		afisareMasina(p->info);
		p = p->next;
	}
}

void afisareListaMasiniSfarsit(Lista list) {
	Nod* p = list.last;
	while (p) {
		afisareMasina(p->info);
		p = p->prev;
	}
}

void adaugaMasinaInLista(Lista* list, Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
	Nod* p = (Nod*)malloc(sizeof(Nod));
	p->info = masinaNoua;
	p->next = NULL;
	p->prev = list->last;
	if (list->last) {
		list->last->next = p;
	}
	else {
		list->first = p;
	}
	list->last = p;
}


void adaugaLaInceputInLista(Lista* list, Masina masinaNoua) {
	//adauga la inceputul listei dublu inlantuite o noua masina pe care o primim ca parametru
	Nod* p = (Nod*)malloc(sizeof(Nod));
	p->prev = NULL;
	p->next = list->first;
	p->info = masinaNoua;

	if (list->first) {
		list->first->prev = p;
	}
	else {
		list->last = p;
	}
	list->first = p;
}

struct Lista citireLDMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");
	Lista list;
	list.first = NULL;
	list.last = NULL;

	while (!feof(f)) {
		//adaugaMasinaInLista(&list, citireMasinaDinFisier(f));
		adaugaLaInceputInLista(&list, citireMasinaDinFisier(f));
	}
	fclose(f);

	return list;
}

void dezalocareLDMasini(Lista* lista) {
	//sunt dezalocate toate masinile si lista dublu inlantuita de elemente
	Nod* p = lista->first;
	while (p->next) {
		free(p->info.numeSofer);
		free(p->info.model);
		p = p->next;
		free(p->prev);
	}
	free(p->info.numeSofer);
	free(p->info.model);
	free(p);
	lista->first = NULL;
	lista->last = NULL;
}

float calculeazaPretMediu(Lista lista) {
	//calculeaza pretul mediu al masinilor din lista.
	Nod* aux = lista.first;
	float pretmediu = 0;
	float suma = 0;
	float cnt = 0;

	while (aux) {
		suma += aux->info.pret;
		cnt++;
		aux = aux->next;
	}

	return suma/cnt;
}

void stergeMasinaDupaID(/*lista masini*/ int id) {
	//sterge masina cu id-ul primit.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

char* getNumeSoferMasinaScumpa(/*lista dublu inlantuita*/) {
	//cauta masina cea mai scumpa si 
	//returneaza numele soferului acestei maasini.
	return NULL;
}

//int main() {
//
//	Lista lista;
//
//	lista = citireLDMasiniDinFisier("masini2.txt");
//
//	//afisareListaMasiniInceput(lista);
//
//	afisareListaMasiniSfarsit(lista);
//
//	float pretmediu = calculeazaPretMediu(lista);
//	printf("Pret mediu: %.2f", pretmediu);
//
//	dezalocareLDMasini(&lista);
//
//	return 0;
//}