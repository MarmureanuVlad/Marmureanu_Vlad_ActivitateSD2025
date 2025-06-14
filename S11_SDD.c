#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

struct Nod {
	Masina info;
	struct Nod* next;
};
typedef struct Nod Nod;

struct NodDublu {
	Masina info;
	struct NodDublu* next;
	struct NodDublu* prev;
};
typedef struct NodDublu NodDublu;

struct Coada {
	NodDublu* front;
	NodDublu* rear;
};
typedef struct Coada Coada;


Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	if (fgets(buffer, 100, file) == NULL) {
		Masina empty = { -1, 0, 0, NULL, NULL, '-' };
		return empty;
	}
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy(m1.model, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy(m1.numeSofer, aux);

	aux = strtok(NULL, sep);
	m1.serie = aux[0];
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

void pushStack(Nod** stiva, Masina masina) {
	Nod* nou = malloc(sizeof(Nod));
	nou->info = masina;
	nou->next = (*stiva);
	(*stiva) = nou;
}

Masina popStack(Nod** stiva) {
	if (!(*stiva))
		return (Masina) { -1, 0, 0, NULL, NULL, '-' };
	Nod* temp = (*stiva);
	Masina m = temp->info;
	(*stiva) = temp->next;
	free(temp);
	return m;
}

int IsEmptyStack(Nod* stiva) {
	return stiva == NULL;
}

Nod* citireStackMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	if (!f) return NULL;
	Nod* stiva = NULL;
	while (!feof(f))
	{
		Masina m = citireMasinaDinFisier(f);
		if (m.id != -1)
			pushStack(&stiva, m);
	}
	fclose(f);
	return stiva;
}

void dezalocareStivaDeMasini(Nod** stiva) {
	while ((*stiva))
	{
		Masina m = popStack(stiva);
		free(m.model);
		free(m.numeSofer);
	}
}

int size(Nod* stiva) {
	int count = 0;
	while (stiva)
	{
		count++;
		stiva = stiva->next;
	}
	return count;
}

void enqueue(Coada* coada, Masina masina) {
	NodDublu* nou = (NodDublu*)malloc(sizeof(NodDublu));
	nou->info = masina;
	nou->next = NULL;
	nou->prev = coada->rear;
	if (coada->rear)
		coada->rear->next = nou;
	else
		coada->front = nou;
	coada->rear = nou;
}

Masina dequeue(Coada* coada) {
	if (coada->front)
	{
		Masina m = coada->front->info;
		NodDublu* temp = coada->front;
		coada->front = coada->front->next;
		if (coada->front == NULL)
			coada->rear = NULL;
		else
			coada->front->prev = NULL;
		free(temp);
		return m;
	}
	else
	{
		Masina m;
		m.id = -1;
		return m;
	}
}

Coada citireCoadaDeMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Coada coada = { NULL, NULL };
	if (!f) return coada;

	while (!feof(f))
	{
		Masina m = citireMasinaDinFisier(f);
		if (m.id != -1)
			enqueue(&coada, m);
	}
	fclose(f);
	return coada;
}

void dezalocareCoadaDeMasini(Coada* coada) {
	while (coada->front)
	{
		Masina m = dequeue(coada);
		free(m.model);
		free(m.numeSofer);
	}
}

float calculeazaPretTotal(Nod** stiva)
{
	Nod* temp = NULL;
	float suma = 0;
	while (!IsEmptyStack((*stiva)))
	{
		Masina m = popStack(stiva);
		suma += m.pret;
		pushStack(&temp, m);
	}
	while (!IsEmptyStack(temp))
	{
		pushStack(stiva, popStack(&temp));
	}
	return suma;
}

float calculeazaPretTotalCoada(Coada coada) {
	float suma = 0;
	NodDublu* curent = coada.front;
	while (curent) {
		suma += curent->info.pret;
		curent = curent->next;
	}
	return suma;
}

Masina getMasinaByIDStack(Nod* stiva, int id) {
	while (stiva) {
		if (stiva->info.id == id)
			return stiva->info;
		stiva = stiva->next;
	}
	return (Masina) { -1, 0, 0, NULL, NULL, '-' };
}

Masina getMasinaByIDQueue(Coada coada, int id) {
	NodDublu* curent = coada.front;
	while (curent) {
		if (curent->info.id == id)
			return curent->info;
		curent = curent->next;
	}
	return (Masina) { -1, 0, 0, NULL, NULL, '-' };
}

int main() {
	Nod* stiva = citireStackMasiniDinFisier("masini2.txt");
	Coada coada = citireCoadaDeMasiniDinFisier("masini2.txt");

	printf("Masina din stiva:\n");
	Masina m = popStack(&stiva);
	afisareMasina(m);

	printf("Masina din coada:\n");
	Masina m1 = dequeue(&coada);
	afisareMasina(m1);

	printf("Pret total in stiva: %.2f\n", calculeazaPretTotal(&stiva));
	printf("Pret total in coada: %.2f\n", calculeazaPretTotalCoada(coada));

	printf("Cautare masina cu ID 2 in stiva:\n");
	Masina cautata = getMasinaByIDStack(stiva, 2);
	if (cautata.id != -1)
		afisareMasina(cautata);

	printf("Cautare masina cu ID 3 in coada:\n");
	Masina cautata2 = getMasinaByIDQueue(coada, 3);
	if (cautata2.id != -1)
		afisareMasina(cautata2);

	dezalocareStivaDeMasini(&stiva);
	dezalocareCoadaDeMasini(&coada);

	return 0;
}