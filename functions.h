#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "datatype.h"
//10
int izbornik(const char* const);
void inicijalizacija(const char* const);
void dodajArtikl(const char* const);
void* ucitajArtikl(const char* const);
void ispisiArtikl(const ARTIKL* const);
void brisanjeArtikala(ARTIKL* const, const char* const);
void* pretrazivanje(ARTIKL* const);
void zamjena(ARTIKL* const, ARTIKL* const);
void* sortirajCijenaMax(char*);
void ispisiSortiranoMax(const ARTIKL* polje);
void* sortirajCijenaMin(char*);
void ispisiSortiranoMin(const ARTIKL* polje);
int brisanjeDatoteke(char* fp);
#endif
