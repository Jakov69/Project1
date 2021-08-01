#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cvor;
typedef struct cvor* Pozicija;
typedef struct cvor {
	char ime[64];
	char podime[64];
	int kolicina;
	Pozicija next;

}cvor;

void UcitajDat(Pozicija);
void unos(Pozicija, char*, char*, int);
void Ispis(Pozicija);
void filter(Pozicija);
void trazi(Pozicija, char*, int);

int main() {
	cvor head;
	head.next = NULL;
	Pozicija p = &head;

	UcitajDat(p);

	filter(p);

	Ispis(p);



	return 0;
}

void UcitajDat(Pozicija p) {
	

	FILE* dat = fopen("artikli.txt", "r");
	if (dat == NULL) {
		printf("Neuspjesno otvaranje dat");
		
	}
	char imee[64];
	char podimee[64];
	int kolicinaa = 0;
	while (fscanf(dat, "%s %s %d ", imee, podimee, &kolicinaa) > 0) {

		unos(p, imee, podimee, kolicinaa);

	}
	fclose(dat);
}

void unos(Pozicija p, char* imee, char* podimee, int kolicinaa) {
	Pozicija w = NULL;
	while (p->next != NULL && strcmp(p->next->ime, imee) < 0) {
		p = p->next;
	}
	w = (Pozicija)malloc(sizeof(cvor));
	if (!w) {
		printf("Neuspjesno otvaranje dat");
	}
	strcpy(w->ime, imee);
	strcpy(w->podime, podimee);
	w->kolicina = kolicinaa;

	w->next = p->next;
	p->next = w;
}

void Ispis(Pozicija p) {
	p = p->next;
	while (p != 0) {
		printf("%s %s %d ", p->ime, p->podime, p->kolicina);
		puts("\n");
		p = p->next;
	}
}

void filter(Pozicija p) {
	

	FILE* fp = fopen("racun.txt", "r");
	if (fp == NULL) {
		printf("Neuspjesno otvaranje dat");
		
	}
	char ppodime[64];
	int kkolicina = 0;
	while (fscanf(fp, "%s %d ", ppodime, &kkolicina) > 0) {

		trazi(p, ppodime, kkolicina);

	}

	fclose(fp);
}

void trazi(Pozicija p, char* ppodimee, int kkolicinaa) {
	while (p->next != 0) {
		if (strcmp(p->next->podime, ppodimee) == 0) {
			p->next->kolicina = p->next->kolicina - kkolicinaa;
		}
		p = p->next;
	}
}