#include <stdio.h>
#include <stdlib.h>

struct produs {
	int id;
	char* denumire;
	float pret;
};

struct produs init(int id, const char* denumire, float pret) {
	struct produs p;

	p.id = id;
	p.pret = pret;

	if (denumire != NULL) {
		p.denumire = (char*)malloc(strlen(denumire) + 1);
		strcpy_s(p.denumire, strlen(denumire) + 1, denumire);
	}
	else p.denumire = NULL;

	return p;
}

void afis(struct produs p) {
	printf("Id: %d\n Denumire: %s\n Pret: %.2f\n\n", p.id, p.denumire, p.pret);
}

void afis_vector(struct produs** vector, int nrProduse) {
	for (int i = 0; i < nrProduse; i++) {
		afis(*vector[i]);
	}
}

void modifica_pret(struct produs* p, int pret_nou) {
	p->pret = pret_nou;
}

struct produs* primele_produse(struct produs** vector, int nr) {
	struct produs* vector_nou = NULL;
	vector_nou = (struct produs*)malloc(sizeof(struct produs) * nr);

	for (int i = 0; i < nr; i++) {
		vector_nou[i] = *vector[i];
		if (vector[i]->denumire != NULL) {
			vector_nou[i].denumire = (char*)malloc(strlen(vector[i]->denumire) + 1);
			strcpy_s(vector_nou[i].denumire, strlen(vector[i]->denumire) + 1, vector[i]->denumire);
		}
		else vector_nou[i].denumire = NULL;
	}

	return vector_nou;
}

int main() {

	struct produs p1 = init(1, "Ceapa", 1.2);
	struct produs p2 = init(2, "Rosii", 1.5);
	struct produs p3 = init(3, "Castraveti", 0.7);
	struct produs p4 = init(4, "Vinete", 1.4);

	/*afis(p1);
	afis(p2);*/

	struct produs** vector = NULL;
	int nrProduse = 4;
	vector = (struct produs*)malloc(sizeof(struct produs) * nrProduse);
	vector[0] = &p1;
	vector[1] = &p2;
	/*vector[2] = init(3, "Castraveti", 0.7);
	vector[3] = init(4, "Vinete", 1.4);*/
	vector[2] = &p3;
	vector[3] = &p4; // sau as putea sa fac init sa returneze un pointer la produs direct

	afis_vector(vector, nrProduse);

	modifica_pret(&p1, 1);
	//afis(p1);

	afis_vector(vector, nrProduse);

	struct produs* vector_nou = primele_produse(vector, 2);

	// am testat faptul ca daca modific in vectorul din care am copiat o denumire, aceasta nu se va modifica si in vector_nou (deep copy)
	/*vector[0]->denumire = "DACIA";
	afis_vector(vector, nrProduse);*/

	for (int i = 0; i < 2; i++) {
		afis(vector_nou[i]);
	}
	
	return 0;
}