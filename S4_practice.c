#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Masina {
	int id;
	char* model;
	float pret;
};

typedef struct Masina Masina;

struct Nod {
	Masina info;
	struct Nod* next;
};

typedef struct Nod Nod;

Masina initializare(int id, char* model, float pret) {
	Masina m;
	m.id = id;
	m.pret = pret;
	m.model = (char*)malloc(strlen(model) + 1);
	strcpy_s(m.model, strlen(model) + 1, model);
	return m;
}

//Masina citireMasinaFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m;
//
//	//strtok(buffer, sep) la primul
//
//	// atoi pt int, atof pt float
//	// la char* fac aux = strtok() si dupa aloc memorie
//	// la char fac *strtok()
//
//}
//
//Nod* citireListaMasini(const char* numefisier) {
//	FILE* file = fopen(numefisier, "r");
//	Nod* cap = NULL;
//
//	while (!feof(file)) {
//		adaugaMasinaInLista(citireMasinaFisier(file), &cap);
//	}
//
//	fclose(file);
//	return cap;
//}

void afisareMasina(Masina m) {
	printf("Id: %d\nModel: %s\nPret: %.2f\n\n", m.id, m.model, m.pret);
}

void adaugaMasinaInLista(Masina m, Nod** cap) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = m;
	nou->next = NULL;
	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		Nod* p = *cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}
}

void adaugaMasinaLaInceput(Masina m, Nod** cap) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = m;
	nou->next = *cap;
	*cap = nou;
}

void afisareListaMasini(Nod* cap) {
	while (cap) {
		afisareMasina(cap->info);
		cap = cap->next;
	}
}


int main() {

	Masina m1 = initializare(1, "Supra", 45000);
	Masina m2 = initializare(2, "350Z", 30000);
	Masina m3 = initializare(3, "S", 140000);
	Masina m4 = initializare(4, "M4", 90000);
	Masina m5 = initializare(5, "GLE", 120000);


	Nod* cap = NULL;

	adaugaMasinaInLista(m1, &cap);
	adaugaMasinaInLista(m2, &cap);
	adaugaMasinaInLista(m3, &cap);
	adaugaMasinaInLista(m4, &cap);

	adaugaMasinaLaInceput(m5, &cap);

	afisareListaMasini(cap);
}