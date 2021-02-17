/*****************************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet 
 * Tekijä: Kalle Liljeström
 * Opiskelijanumero: 
 * Päivämäärä: 4.3.2019
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto: Lähteenä C-ohjelmoinnin 
 * perusteet luentodiat sekä C-kieli ohjelmointiopas, Kasurinen & Nikula 2012
 */
/*****************************************************************************/
/* Header -tiedosto ali1 aliohjelmakirjastolle */

/* include guard */
#ifndef ali1_h
#define ali1_h

#define MAX 20

/* linkitetyn nimilistan alkio */
typedef struct Nimi
{
	char nimi[MAX];
	struct Nimi *pNext;
} NIMI;

/* linkitetyn tuloslistan alkio */
typedef struct Tulos
{
	char nimi[MAX];
	int maara, pitMin, pitMax;
	float pitKA;
	struct Tulos *pNext;
} TULOS;

/* aliohjelmien esittelyt */
NIMI *lueTiedosto(NIMI *pA);
NIMI *lisaaNimi(NIMI *pA, char *s);
TULOS *analysoi(TULOS *pATulos, NIMI *pANimi);
TULOS *lisaaTulos(TULOS *pA, TULOS *ptrUusi);

#endif
/*****************************************************************************/
/* eof */
