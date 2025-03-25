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
typedef struct Nod Nod;

//creare structura pentru un nod dintr-o lista simplu inlantuita
struct Nod {
	Masina info;
	Nod* urm;
};

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

void afisareMasinaa(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(Nod* cap) {
	//afiseaza toate elemente de tip masina din lista simplu inlantuita
	//prin apelarea functiei afisareMasina()

	while (cap) {
		afisareMasinaa(cap->info);
		cap = cap->urm;
	}
}

void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->urm = NULL;

	if ((*cap) == NULL) {
		*cap = nou;
	}
	else {
		Nod* p = *cap;
		while (p->urm) {
			p = p->urm;
		}
		p->urm = nou;
	}
}

void adaugaLaInceputInLista(Nod** cap, Masina masinaNoua) {
	//adauga la inceputul listei o noua masina pe care o primim ca parametru

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->urm = *cap;


}

Nod* citireListaMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul

	FILE* f = fopen(numeFisier, "r");
	Nod* lista = NULL;
	while (!feof(f)) {
		adaugaMasinaInLista(&lista, citireMasinaDinFisier(f));
	}

	fclose(f);
	return lista;
}

void dezalocareListaMasini(Nod** cap) {
	//sunt dezalocate toate masinile si lista de elemente
	while ((*cap) != NULL) {
		Nod* aux = (*cap);
		*cap = (*cap)->urm;
		free(aux->info.numeSofer);
		free(aux->info.model);
		free(aux);
	}
}

float calculeazaPretMediu(Nod* lista) {
	//calculeaza pretul mediu al masinilor din lista.
	if (!lista) return 0;
	int count = 0;
	float sum = 0;
	while (lista) {
		sum += lista->info.pret;
		count++;
		lista = lista->urm;
	}

	return (count > 0) ? sum / count : 0;
}

void stergeMasiniDinSeria(/*lista masini*/ char serieCautata) {
	//sterge toate masinile din lista care au seria primita ca parametru.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

float calculeazaPretulMasinilorUnuiSofer(Nod* lista, const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.

	float sum = 0;
	while (lista) {
		if (strcmp(numeSofer, lista->info.numeSofer) == 0) {
			sum += lista->info.pret;
		}

		lista = lista->urm;
	}

	return sum;
}

char* getCeaMaiScumpamasina(Nod* lista) {

	float pretulMax = 0;
	char* modelScump = NULL;
	while (lista) {
		if (lista->info.pret > pretulMax) {
			pretulMax = lista->info.pret;
			modelScump = lista->info.model;
		}

		lista = lista->urm;
	}
	if (pretulMax > 0) {
		char* nou = malloc(strlen(modelScump) + 1);
		strcpy_s(nou, strlen(modelScump) + 1, modelScump);
		return nou;
	}
	return NULL;
}

int main() {

	Nod* cap = NULL;

	cap = citireListaMasiniDinFisier("masini2.txt"); //daca lasam functia cu void* in loc de Nod*, aici trebuia sa facem cast
	afisareListaMasini(cap);

	printf("%.2f\n", calculeazaPretMediu(cap));

	printf("%.2f\n", calculeazaPretulMasinilorUnuiSofer(cap, "Ionescu"));

	printf("%s\n", getCeaMaiScumpamasina(&cap)); // ??

	dezalocareListaMasini(&cap);

	return 0;
}