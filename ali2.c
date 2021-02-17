/*****************************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet 
 * Tekijä: Kalle Liljeström
 * Opiskelijanumero: 
 * Päivämäärä: 4.3.2019
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto: Lähteenä C-ohjelmoinnin 
 * perusteet luentodiat sekä C-kieli ohjelmointiopas, Kasurinen & Nikula 2012.
 */
/*****************************************************************************/
/*	ali2 aliohjelmakirjasto sisältää aliohjelmat tulos- ja nimilistan
	tulostukseen, tyhjennykseen sekä tuloslistan tallentamiseen tiedostoon.
	Suunniteltu toimimaan pääohjelman kanssa ja vaatii ali2 
	aliohjelmakirjaston nimi ja tulos -structit sekä define käskyt toimiakseen.
*/
#include <stdio.h>
#include <stdlib.h>
#include "ali1.h"
#include "ali2.h"

/* 	Aliohjelma tulostaa nimilistan näytölle. Saa parametrina pointterin 
	nimilistan alkuun.
*/
void tulostaLista(NIMI *pA)
{
	NIMI *ptr;

	if (pA == NULL)
	{
		printf("Lista on tyhjä.\n");
	}
	else
	{	
		/* Käydään linkitetty lista yksi alkio kerrallaan läpi */
		ptr = pA;
		while (ptr != NULL)
		{
			printf("%s\n", ptr->nimi);
			ptr = ptr->pNext;
		}
	}
}
/* Aliohjelma tulostaa tuloslistan datasetit näytölle. Saa parametrina 
	pointterin tuloslistan alkuun.
*/
void tulostaTulokset(TULOS *pA)
{
	TULOS *ptr;

	if (pA == NULL)
	{
		printf("Lista on tyhjä.\n");
	}
	else
	{	
		ptr = pA;
		printf("Datasetti Nimiä PitMin PitMax PitKA\n");

		/* Käydään linkitetty lista yksi alkio kerrallaan läpi */
		while (ptr != NULL)
		{
			printf("%-9s %5d %6d %6d %5.1f\n", ptr->nimi, ptr->maara,
				   ptr->pitMin, ptr->pitMax, ptr->pitKA);

			ptr = ptr->pNext;
		}
	}
}
/* Tyhjennetään linkitetty mimilista ja vapautetaan muisti. Saa paramterina 
	pointterin tuloslistan alkuun ja palauttaa sen, jolloin se osoittaa 
	arvoon NULL. 
*/
NIMI *tyhjennaLista(NIMI *pA)
{
	NIMI *ptr;

	ptr = pA;
	/* Käydään lista läpi */
	while (ptr != NULL)
	{
		pA = ptr->pNext;
		free(ptr);
		ptr = pA;
	}
	return pA;
}
/*	Tyhjennetään linkitetty tuloslista ja vapautetaan muisti. Saa paramterina 
	pointterin tuloslistan alkuun ja palauttaa sen, jolloin se osoittaa 
	arvoon NULL.
*/
TULOS *tyhjennaTulokset(TULOS *pA)
{
	TULOS *ptr;

	ptr = pA;
	/* Käydään lista läpi */
	while (ptr != NULL)
	{
		pA = ptr->pNext;
		free(ptr);
		ptr = pA;
	}
	return pA;
}
/* Aliohjelma kysyy tiedoston nimen, luo sen, ja tallentaa siihen tuloslistan
 	tiedot. Saa parametrina pointterin tuloslistan alkuun.
*/
void tallennaTiedosto(TULOS *pA)
{
	char tiedostoNimi[MAX];
	FILE *tiedosto;
	TULOS *ptr;

	if (pA == NULL)
	{
		printf("Lista on tyhjä\n");
	}
	else
	{
		printf("Anna tallennettavan tulostiedoston nimi: ");
		scanf("%s", tiedostoNimi);

		/* Yritetään avata tiedosto, lopetetaan, jos epäonnistuu */
		if ((tiedosto = fopen(tiedostoNimi, "w")) == NULL)
		{
			printf("Tiedoston avaus epäonnistui.\n");
			exit(1);
		}
		else
		{
			ptr = pA;
			fprintf(tiedosto, "Datasetti Nimiä PitMin PitMax PitKA\n");

			/* Käydään tuloslista läpi */
			while (ptr != NULL)
			{
				fprintf(tiedosto, "%-9s %5d %6d %6d %5.1f\n", ptr->nimi,
						ptr->maara, ptr->pitMin, ptr->pitMax, ptr->pitKA);

				ptr = ptr->pNext;
			}
			printf("Tiedosto tallennettu.\n");
		}
		/* suljetaan tiedosto */
		fclose(tiedosto);
	}
}
/*****************************************************************************/
/* eof */
