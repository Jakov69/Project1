#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define D 64

typedef struct lista1* Pozicija1;
struct lista2;
typedef struct lista2* Pozicija2;
typedef struct lista2 {

	char artikl[D];
	int kolicina;
	Pozicija2 next;

}lista2;

struct lista1;

typedef struct lista1 {
	char kategorija[D];
	Pozicija1 next;
	Pozicija2 lista;

}lista1;

Pozicija1 UcitajDat(Pozicija1);
Pozicija1 Unos(Pozicija1, char*, char*, int);
Pozicija1 trazi(Pozicija1, char*);
Pozicija2 UnosL2(Pozicija2, char*, int);
void Ispis(Pozicija1);
void Ispis2(Pozicija2);
Pozicija1 filter(Pozicija1);
Pozicija1 Trazi(Pozicija1, char*, char*, int);
Pozicija2 Trazi2(Pozicija2, char*, int);
void IspisF(Pozicija1);
void IspisF2(Pozicija2);
void BrisanjeSvega(Pozicija1);
void BrisanjeSvega2(Pozicija2);

int main() {

	lista1 head;
	head.next = NULL;
	Pozicija1 h = &head;

	UcitajDat(h);

	puts("Artikli pocetak:\n");
	Ispis(h);

	filter(h);
	puts("\n--------");
	puts("Artikli umanjeni za racun:\n");
	Ispis(h);
	puts("\n--------");
	puts("Artikli s kolicinom manjom od 5:\n");
	IspisF(h);

	//BrisanjeSvega(h);

	puts("\n--------");
	//Ispis(h);

	return 0;
}

Pozicija1 UcitajDat(Pozicija1 h) {
	FILE* dat = fopen("artikli.txt", "r");
	if (dat == NULL) {
		printf("Neuspjesno otvaranje dat");
	}

	char kat[D];
	char art[D];
	int kol = 0;
	while (fscanf(dat, "%s %s %d ", kat, art, &kol) > 0) {

		Unos(h, kat, art, kol);

	}

	fclose(dat);
	return NULL;
}

Pozicija1 Unos(Pozicija1 p, char* katt, char* artt, int koll) {
	Pozicija1 q = NULL;
	Pozicija1 g = NULL;

	g = trazi(p, katt);

	if (g == NULL) {

		q = (Pozicija1)malloc(sizeof(lista1));
		strcpy(q->kategorija, katt);

		q->next = NULL;
		q->lista = NULL;
		q->lista = UnosL2(q->lista, artt, koll);
		q->next = p->next;
		p->next = q;

		return NULL;
	}

	else {
		g->lista = UnosL2(g->lista, artt, koll);
		return NULL;
	}

}

Pozicija1 trazi(Pozicija1 y, char* rijec) {
	while (y->next->kategorija != NULL && strcmp(y->next->kategorija, rijec) != 0) {
		y = y->next;
	}
	return y->next;
}

Pozicija2 UnosL2(Pozicija2 r, char* aart, int kkol) {

	if (r == NULL) {
		Pozicija2 R;
		r = (Pozicija2)malloc(sizeof(lista2));
		R = (Pozicija2)malloc(sizeof(lista2));
		R->next = NULL;
		r->next = NULL;

		strcpy(R->artikl, aart);
		R->kolicina = kkol;

		R->next = r->next;
		r->next = R;

		return r;
	}

	Pozicija2 N;
	N = (Pozicija2)malloc(sizeof(lista2));
	strcpy(N->artikl, aart);
	N->kolicina = kkol;

	N->next = r->next;
	r->next = N;

	return r;
}

void Ispis(Pozicija1 p1) {
	p1 = p1->next;
	while (p1 != NULL) {
		printf("\n %s ", p1->kategorija);
		Ispis2(p1->lista);
		p1 = p1->next;
	}
}

void Ispis2(Pozicija2 p2) {
	p2 = p2->next;
	while (p2 != NULL) {
		printf("\n %s %d\n", p2->artikl, p2->kolicina);
		p2 = p2->next;
	}
}

Pozicija1 filter(Pozicija1 w) {

	FILE* fp = fopen("racun.txt", "r");
	if (fp == NULL) {
		printf("Neuspjesno otvaranje fp");
	}

	char kat2[D];
	char art2[D];
	int kol2 = 0;
	while (fscanf(fp, "%s %s %d ", kat2, art2, &kol2) > 0) {

		Trazi(w, kat2, art2, kol2);

	}

	fclose(fp);
	return NULL;
}

Pozicija1 Trazi(Pozicija1 W, char* katt2, char* artt2, int koll2) {
	while (W->next != NULL) {
		if (strcmp(W->next->kategorija, katt2) == 0) {
			Trazi2(W->next->lista, artt2, koll2);
		}
		W = W->next;
	}
	return W;
}

Pozicija2 Trazi2(Pozicija2 W2, char* aart2, int kkol2) {
	while (W2->next != NULL) {
		if (strcmp(W2->next->artikl, aart2) == 0) {
			W2->next->kolicina = W2->next->kolicina - (kkol2);
		}

		W2 = W2->next;
	}
	return W2;
}

void IspisF(Pozicija1 F) {
	F = F->next;
	while (F != NULL) {
		printf("\n%s", F->kategorija);
		IspisF2(F->lista);
		F = F->next;
	}
}

void IspisF2(Pozicija2 F2) {
	F2 = F2->next;
	while (F2 != NULL) {

		if (F2->kolicina < 5) {
			printf("\n%s %d", F2->artikl, F2->kolicina);
		}

		F2 = F2->next;
	}
}

void BrisanjeSvega(Pozicija1 B) {
	Pozicija1 tmp;


	while (B->next != NULL) {
		tmp = B->next;
		B->next = tmp->next;

		BrisanjeSvega2(B->lista);       // ??

		free(tmp);
	}
}

void BrisanjeSvega2(Pozicija2 B2) {
	Pozicija2 tmp2;


	while (B2->next != NULL) {
		tmp2 = B2->next;
		B2->next = tmp2->next;
		free(tmp2);
	}

}