#include <stdlib.h>
#include <stdio.h>

struct Produs {
	int id;
	char* denumire;
	float pret;
};

struct Produs initializare(int id, const char* denumire, float pret) {
	struct Produs p;
	p.id = id;
	p.pret = pret;
	p.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy_s(p.denumire, strlen(denumire) + 1, denumire);

	return p;
}

void afisareProdus(struct Produs p) {
	printf("Id: %d\nDenumire: %s\nPret: %.2f", p.id, p.denumire, p.pret);
	printf("\n\n");
}

void modificaPret(struct Produs* p, int pretNou) {
	p->pret = pretNou;
}

void afisareVectorProduse(struct Produs* vector, int nrProduse) {
	for (int i = 0; i < nrProduse; i++) {
		afisareProdus(vector[i]);
	}
}

struct Produs* returneazaPrimeleProduse(struct Produs* vector, int nrElemente, int nrElemCopiate) {
	struct Produs* vectorNou = NULL;
	vectorNou = (struct Produs*)malloc(sizeof(struct Produs) * nrElemCopiate);
	for (int i = 0; i < nrElemCopiate; i++) {
		vectorNou[i] = vector[i];
		vectorNou[i].denumire = (char*)malloc(strlen(vector[i].denumire) + 1);
		strcpy_s(vectorNou[i].denumire, strlen(vector[i].denumire) + 1, vector[i].denumire);
	}
	return vectorNou;
}

void dezalocare(struct Produs** vector, int* nrElem) {
	for (int i = 0; i < nrElem; i++) {
		free((*vector[i]).denumire);
		//free(vector[i]->denumire);
	}
	free(*vector);
	*vector = NULL;
	*nrElem = 0;
}

void copiazaProdCuPretMare(struct Produs* produse, int nrProduse, struct Produs** produseScumpe, int* dim, int prag) {
	for (int i = 0; i < nrProduse; i++) {
		if (produse[i].pret >= prag) {
			(*dim)++;
		}
	}
	*produseScumpe = (struct Produs*)malloc(sizeof(struct Produs) * (*dim));
	*dim = 0;
	for (int i = 0; i < nrProduse; i++) {
		if (produse[i].pret >= prag) {
			(*produseScumpe)[*dim] = produse[i];
			(*produseScumpe)[*dim].denumire = (char*)malloc(strlen(produse[i].denumire) + 1);
			strcpy_s((*produseScumpe)[*dim].denumire, strlen(produse[i].denumire) + 1, produse[i].denumire);
			(*dim)++;
		}
	}
}

struct Produs getPrimulProdDupaNume(struct Produs* vector, int nrElem, const char* denumire) {
	for (int i = 0; i < nrElem; i++) {
		if (strcmp(vector[i].denumire, denumire) == 0) {
			return vector[i];
		}
	}
	return initializare(1, "Nimic", 0);
}


int main() {

	struct Produs p1 = initializare(1, "Prod1", 100);
	struct Produs p2 = initializare(2, "Prod2", 20.50);
	struct Produs p3 = initializare(3, "Prod3", 350);
	struct Produs p4 = initializare(4, "Prod4", 5.556);

	afisareProdus(p1);

	modificaPret(&p1, 120);

	afisareProdus(p1);

	struct Produs* vectorProduse = NULL;
	int nrProduse = 4;

	vectorProduse = (struct Produs*)malloc(sizeof(struct Produs) * nrProduse);

	vectorProduse[0] = p1;
	vectorProduse[1] = p2;
	vectorProduse[2] = p3;
	vectorProduse[3] = p4;

	afisareVectorProduse(vectorProduse, nrProduse);

	struct Produs* vectorNou = NULL;
	vectorNou = returneazaPrimeleProduse(vectorProduse, 4, 2);


	afisareVectorProduse(vectorNou, 2);

	struct Produs* produseScumpe = NULL;
	int dim = 0;
	copiazaProdCuPretMare(vectorProduse, nrProduse, &produseScumpe, &dim, 100);

	printf("Produse cu pret mare:\n\n");
	afisareVectorProduse(produseScumpe, dim);

	struct Produs produsDupaNume = getPrimulProdDupaNume(vectorProduse, nrProduse, "IDK");
	printf("Primul prod dupa nume:\n\n");
	afisareProdus(produsDupaNume);

}