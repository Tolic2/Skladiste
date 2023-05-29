#define _CRT_SECURE_NO_WARNINGS

#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int izbornik(const char* const ime) {

	printf("\t\t***************************************\n\n");
	printf("\t\tOdaberite jednu od ponudenih opcija: \n\n");
	printf("\t\t***************************************\n\n");
	printf("\t\tOpcija 1: Dodavanje artikla:\n\n");
	printf("\t\tOpcija 2: Sortiranje artikala po cijeni od najvece\n\n");
	printf("\t\tOpcija 3: Sortiranje artikala po cijeni od najmanje\n\n");
	printf("\t\tOpcija 4: Ispis svih artikala\n\n");
	printf("\t\tOpcija 5: Pretrazivanje artikla po ID-u\n\n");
	printf("\t\tOpcija 6: Brisanje artikla\n\n");
	printf("\t\tOpcija 7: Brisanje datoteke\n\n");
	printf("\t\tOpcija 8: Zavrsetak programa\n\n");
	printf("\t\t***************************************\n\n");

	int opcija = 0;
	static ARTIKL* poljeArtikala = NULL;
	static ARTIKL* pronadeniArtikl = NULL;

	scanf("%d", &opcija);
	system("cls");

	switch (opcija) {

	case 1:

		dodajArtikl(ime);
		break;

	case 2:
		if (poljeArtikala != NULL) {
			free(poljeArtikala);
			poljeArtikala = NULL;
		}

		poljeArtikala = (ARTIKL*)ucitajArtikl(ime);
		ispisiSortiranoMax(poljeArtikala);

		break;


	case 3:
		if (poljeArtikala != NULL) {
			free(poljeArtikala);
			poljeArtikala = NULL;
		}

		poljeArtikala = (ARTIKL*)ucitajArtikl(ime);
		ispisiSortiranoMin(poljeArtikala);

		break;

	case 4:
		if (poljeArtikala != NULL) {
			free(poljeArtikala);
		}

		poljeArtikala = (ARTIKL*)ucitajArtikl(ime);

		ispisiArtikl(poljeArtikala);
		break;

	case 5:
		if (poljeArtikala != NULL) {
			free(poljeArtikala);
		}

		poljeArtikala = (ARTIKL*)ucitajArtikl(ime);

		pronadeniArtikl = (ARTIKL*)pretrazivanje(poljeArtikala);

		if (pronadeniArtikl != NULL) {
			printf("ID: %d\n", pronadeniArtikl->id);
			printf("Ime: %s\n", pronadeniArtikl->ime);
			printf("Proizvodac: %s\n", pronadeniArtikl->proizvodac);
			printf("Vrsta: %s\n", pronadeniArtikl->vrsta);
			printf("Cijena: %d\n", pronadeniArtikl->cijena);
			printf("Kolicina: %d\n", pronadeniArtikl->kolicina);
		}
		else {
			printf("Ne postoji artikl s tim ID-om");
		}
		break;

	case 6:
		if (poljeArtikala != NULL) {
			free(poljeArtikala);
			poljeArtikala = NULL;
		}

		poljeArtikala = (ARTIKL*)ucitajArtikl(ime);

		brisanjeArtikala(poljeArtikala, ime);
		break;
			
	case 7:
		brisanjeDatoteke("skladiste.bin");

		break;

	case 8:
		opcija = izlaz(poljeArtikala);

		break;
	default:
		opcija = 0;
		
	}

	return opcija;

}
