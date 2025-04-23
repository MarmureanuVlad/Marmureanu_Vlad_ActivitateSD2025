#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void afisareMasina(Masina m) {
	printf("Id: %d\nModel: %s\nPret: %.2f\n", m.id, m.model, m.pret);
}

void adaugaMasinaInLista(Masina m, Nod** cap) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = m;
	nou->next = NULL;
	if ((*cap) != NULL) {
		Nod* aux = *cap;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		*cap = nou;
	}
}

void adaugaMasinaLaInceputInLista(Masina m, Nod** cap) {
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

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m;

	aux = strtok(buffer, sep);
	m.id = atoi(aux);

	aux = strtok(NULL, sep);
	m.model = (char*)malloc(strlen(aux) + 1);
	strcpy_s(m.model, strlen(aux) + 1, aux);

	m.pret = atof(strtok(NULL, sep));

	return m;
}

Nod* citesteLista(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	Nod* cap = NULL;

	while (!feof(file)) {
		//adaugaMasinaInLista(citireMasinaDinFisier(file), &cap);
		adaugaMasinaLaInceputInLista(citireMasinaDinFisier(file), &cap);
	}
	fclose(file);

	return cap;
}

int main() {

	Nod* cap = NULL;
	cap = citesteLista("masini3.txt");

	afisareListaMasini(cap);

}