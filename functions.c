#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "dataType.h"

static int brojArtikala = 0;

void inicijalizacija(const char* const ime) {

	FILE* fp = fopen(ime, "rb");

	if (fp == NULL) {
		fp = fopen(ime, "wb");

		fwrite(&brojArtikala, sizeof(int), 1, fp);
		fclose(fp);
		printf("Kreirana datoteka artikli.bin\n\n");
	}
	else {
		fclose(fp);
	}
}

void dodajArtikl(const char* const ime) {

	FILE* fp = fopen(ime, "rb+");

	if (fp == NULL) {
		perror("Dodavanje artikala u datoteku artikli.bin");
		exit(EXIT_FAILURE);
	}

	fread(&brojArtikala, sizeof(int), 1, fp);
	printf("Broj artikla: %d \n\n", brojArtikala);

	ARTIKL temp = { 0 };
	temp.id = brojArtikala + 1;
	getchar();

	printf("Unesite ime artikla: ");
	scanf("%24[^\n]", temp.ime);
	getchar();

	printf("Unesite vrstu artikla: ");
	scanf("%24[^\n]", temp.vrsta);
	getchar();

	printf("Unesite ime proizvodaca: ");
	scanf("%24[^\n]", temp.proizvodac);

	printf("Unesite cijenu artikla: ");
	scanf("%f", &temp.cijena);
	getchar();

	printf("Unesite kolicinu artikla: ");
	scanf("%d", &temp.kolicina);
	getchar();

	fseek(fp, sizeof(ARTIKL) * brojArtikala, SEEK_CUR);
	fwrite(&temp, sizeof(ARTIKL), 1, fp);
	printf("Novi artikl dodan\n\n");

	rewind(fp);
	brojArtikala++;

	fwrite(&brojArtikala, sizeof(int), 1, fp);
	fclose(fp);
}
void* ucitajArtikl(const char* const ime) {

	FILE* fp = fopen(ime, "rb");

	if (fp == NULL) {
		perror("Ucitavanje artikala iz artikli.bin");
		exit(EXIT_FAILURE);
	}

	fread(&brojArtikala, sizeof(int), 1, fp);
	printf("Broj artikala: %d\n", brojArtikala);

	ARTIKL* poljeArtikala = (ARTIKL*)calloc(brojArtikala, sizeof(ARTIKL));

	if (poljeArtikala == NULL) {
		perror("Zauzimanje memorije za polje artikala");
		return NULL;
	}

	fread(poljeArtikala, sizeof(ARTIKL), brojArtikala, fp);

	printf("Svi artikli su uspjesno ucitani\n\n");

	return poljeArtikala;
}

void zamjena(ARTIKL* const veci, ARTIKL* const manji) {
	ARTIKL temp = { 0 };
	temp = *manji;
	*manji = *veci;
	*veci = temp;
}

void brisanjeArtikala(ARTIKL* const polje, const char* const dat) {

	if (brojArtikala == 0) {
		printf("Polje artikala je prazno\n");
		return;
	}

	FILE* fp = fopen(dat, "rb+");

	if (fp == NULL) {
		perror("Brisanje artikala");
		exit(EXIT_FAILURE);
	}

	fseek(fp, sizeof(int), SEEK_CUR);

	int i, trazeniID;

	printf("Unesite ID artikla kojeg zelite obrisati: ");

	do {
		scanf("%d", &trazeniID);
		if (trazeniID < 1 || trazeniID > brojArtikala) {
			printf("Artikl s tim ID-om ne postoji, unesite valjani ID");
		}
	} while (trazeniID < 1 || trazeniID > brojArtikala);

	ARTIKL* poljeArtikala = (ARTIKL*)calloc(brojArtikala - 1, sizeof(ARTIKL));

	int brojac = 0;

	for (i = 0; i < brojArtikala; i++) {

		if (trazeniID != (polje + i)->id) {
			*(poljeArtikala + brojac) = *(polje + i);

			if ((poljeArtikala + brojac)->id > trazeniID) {
				(poljeArtikala + brojac)->id -= 1;
			}

			fwrite((poljeArtikala + brojac), sizeof(ARTIKL), 1, fp);
			brojac++;
		}

	}

	free(poljeArtikala);
	poljeArtikala = NULL;

	rewind(fp);

	fwrite(&brojac, sizeof(int), 1, fp);
	fclose(fp);

	printf("Artikl je uspjesno obrisan\n");

}

void* sortirajCijenaMax(ARTIKL* polje) {
	int max = -1;

	for (int i = 0; i < brojArtikala - 1; i++) {

		max = i;

		for (int j = i + 1; j < brojArtikala; j++) {

			if ((polje + j)->cijena > (polje + max)->cijena) {
				max = j;
			}
		}
		zamjena((polje + i), (polje + max));
	}

	return polje;
}


void ispisiSortiranoMax(const ARTIKL* polje) {

	if (brojArtikala == 0) {
		printf("Polje artikala je prazno\n");
		return;
	}
		polje = sortirajCijenaMax(polje);

	for (int i = 0; i < brojArtikala; i++) {
		printf("ID: %d\tIme: %s\tProizvodac: %s\tVrsta: %s\tCijena: %.2f\tKolicina:%d\n\n",
			(polje + i)->id,
			(polje + i)->ime,
			(polje + i)->proizvodac,
			(polje + i)->vrsta,
			(polje + i)->cijena,
			(polje + i)->kolicina);
	}
}

void* sortirajCijenaMin(ARTIKL* polje) {
	int min = -1;

	for (int i = 0; i < brojArtikala - 1; i++) {

		min = i;

		for (int j = i + 1; j < brojArtikala; j++) {

			if ((polje + j)->cijena < (polje + min)->cijena) {
				min = j;
			}
		}
		zamjena((polje + i), (polje + min));
	}

	return polje;
}

void ispisiSortiranoMin(const ARTIKL* polje) {

	if (brojArtikala == 0) {
		printf("Polje artikala je prazno\n");
		return;
	}
	polje = sortirajCijenaMin(polje);

	for (int i = 0; i < brojArtikala; i++) {
		printf("ID: %d\tIme: %s\tProizvodac: %s\tVrsta: %s\tCijena: %.2f\tKolicina:%d\n\n",
			(polje + i)->id,
			(polje + i)->ime,
			(polje + i)->proizvodac,
			(polje + i)->vrsta,
			(polje + i)->cijena,
			(polje + i)->kolicina);
	}
}

void ispisiArtikl(const ARTIKL* const polje) {

	if (polje == NULL) {
		printf("Polje artikala je prazno");
		return;
	}

	for (int i = 0; i < brojArtikala; i++) {
		printf("ID: %d\tIme: %s\tProizvodac: %s\tVrsta: %s\tCijena: %.2f\tKolicina: %d\n\n",
			(polje + i)->id,
			(polje + i)->ime,
			(polje + i)->proizvodac,
			(polje + i)->vrsta,
			(polje + i)->cijena,
			(polje + i)->kolicina);
	}
}

void* pretrazivanje(ARTIKL* const polje) {

	if (polje == NULL) {
		printf("Polje artikala je prazno");
		return NULL;
	}
	int i, trazeniID;

	printf("Unesite ID artikla kojeg zelite pronaci: ");
	scanf("%d", &trazeniID);

	for (i = 0; i < brojArtikala; i++) {

		if (trazeniID == (polje + i)->id) {
			printf("Artikl pronaden\n");

			return  (polje + i);
		}
	}

	return NULL;
}

int brisanjeDatoteke(char* fp) {
	
	int status;
	
	status = remove("skladiste.bin");

	if (status == 0) {
		printf("Datoteka uspjesno obrisana\n");

	}
	else {
		printf("Nije moguce obrisati datoteku\n");
	}
	return 0;
}

int izlaz(ARTIKL* polje) {

	free(polje);
	
	return 0;
}














