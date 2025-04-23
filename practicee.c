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
	struct Nod* prev;
};
typedef struct Nod Nod;

struct Lista {
	Nod* first;
	Nod* last;
};
typedef struct Lista Lista;

void afisareMasina(Masina m) {
	printf("Id: %d\nModel:%s\nPret:%.2f\n\n", m.id, m.model, m.pret);
}

Masina citireMasinaFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m;

	m.id = atoi(strtok(buffer, sep));

	aux = strtok(NULL, sep);
	m.model = (char*)malloc(strlen(aux) + 1);
	strcpy_s(m.model, strlen(aux) + 1, aux);

	m.pret = atof(strtok(NULL, sep));

	return m;
}

void adaugaMasinaInListaFinal(Lista* lista, Masina m) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = m;
	nou->next = NULL;
	nou->prev = lista->last;
	if (lista->last != NULL) {
		lista->last->next = nou;
	}
	else {
		lista->first = nou;
	}
	lista->last = nou;
}

Lista citesteMasiniFisier(const char* numefisier) {
	FILE* file = fopen(numefisier, "r");
	Lista lista;
	lista.first = NULL;
	lista.last = NULL;

	while (!feof(file)) {
		adaugaMasinaInListaFinal(&lista, citireMasinaFisier(file));
	}
	fclose(file);
	return lista;
}

void afisareListaMasini(Lista lista) {
	Nod* p = lista.first;
	while (p) {
		afisareMasina(p->info);
		p = p->next;
	}
}

int main() {

	Lista lista = citesteMasiniFisier("masini3.txt");

	afisareListaMasini(lista);

}