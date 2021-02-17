/*****************************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet 
 * Tekijä: Kalle Liljeström
 * Opiskelijanumero: 
 * Päivämäärä: 4.3.2019
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto: Lähteenä C-ohjelmoinnin 
 * perusteet luentodiat sekä C-kieli ohjelmointiopas, Kasurinen & Nikula 2012
 */
/*****************************************************************************/
/*	ali1 aliohjelmakirjasto sisältää aliohjelmat nimitiedoston lukuun, 
	nimi- ja tuloslistan uusien alkioiden lisäämiseen ja nimilistan 
	nimien analysointiin. Suunniteltu toimimaan pääohjelman kanssa ja 
	vaatii ali2 aliohjelmakirjaston toimiakseen.
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "ali1.h"
#include "ali2.h"

/*	Aliohjelma lukee annetusta tiedostosta nimet ja lisää ne linkitettyyn 
	listaan. Palauttaa pointterin nimilistan alkuun.
*/
NIMI *lueTiedosto(NIMI *pA)
{
	char tiedostoNimi[MAX], nimi[MAX];
	int i = 0;
	FILE *tiedosto;

	printf("Anna luettavan tiedoston nimi: ");
	scanf("%s", tiedostoNimi);

	/* tyhjennetään lista, jos se ei ole tyhjä kutsumalla toista aliohjelmaa */
	if (pA != NULL)
	{
		printf("Poistetaan aiemmat tiedot ja luetaan uudet.\n");
		pA = tyhjennaLista(pA);
	}

	printf("Luetaan tiedosto '%s'.\n", tiedostoNimi);
	/* yritetään avata tiedosto, lopetetaan, jos ei onnistu */
	if ((tiedosto = fopen(tiedostoNimi, "r")) == NULL)
	{
		printf("Tiedoston avaus epäonnistui.\n");
		exit(1);
	}

	while (fgets(nimi, MAX, tiedosto) != NULL)
	{
		/* poistetaan rivinvaihtomerkki lopusta */
		nimi[strcspn(nimi, "\n")] = '\0';

		/* lopetetaan, jos löytyy tyhjä rivi  */
		if (strlen(nimi) == 0)
		{
			printf("Tyhjä rivi, lopetetaan lukeminen.\n");
			break;
		}
		/* kutsutaan aliohjelmaa, joka lisää nimen listaan */
		pA = lisaaNimi(pA, nimi);
		i++;
	}
	printf("Tiedosto '%s' luettu, %d nimiriviä.\n", tiedostoNimi, i);

	/* suljetaan tiedosto */
	fclose(tiedosto);

	return pA;
}
/*	Aliohjelma ottaa parametreina pointterin linkitetyn nimilistan alkuun 
	ja nimen. Nimi asetetaan listan alkioon, joka lisätään listan loppuun.
	Palauttaa pointterin nimilistan alkuun. 
*/
NIMI *lisaaNimi(NIMI *pA, char *s)
{
	/* pointteri listan läpikäymiseen ja uusi alkio */
	NIMI *ptr, *ptrUusi;

	/* varataan alkiolle muistia, lopetetaan, jos epäonnistuu */
	if ((ptrUusi = (NIMI *)malloc(sizeof(NIMI))) == NULL)
	{
		perror("Muistin varaus epäonnistui");
		exit(1);
	}
	strncpy(ptrUusi->nimi, s, MAX - 1);
	ptrUusi->pNext = NULL;

	/* lisätään alkio listan perään */
	if (pA == NULL)
	{
		pA = ptrUusi;
	}
	else
	{
		ptr = pA;
		while (ptr->pNext != NULL)
		{
			ptr = ptr->pNext;
		}
		ptr->pNext = ptrUusi;
	}
	return pA;
}
/*	Aliohjelma analysoi nimilistan nimien pituuksia ja tulostaa näytölle 
	sekä tallettaa linkitettyyn tuloslistaan nimien määrän, lyhimmän ja 
	pisimmän nimen pituuden sekä nimien pituuksien keskiarvon. Saa 
	parametreina pointterit tulos- ja nimilistan alkuihin. Palauttaa
	pointterin tuloslistan alkuun.
*/
TULOS *analysoi(TULOS *pATulos, NIMI *pANimi)
{
	/* uusi tuloslistan alkio ja pointteri nimilistan läpikäymiseen */
	TULOS *ptrTulos;
	NIMI *ptrNimi;
	int pituus, kokooja = 0;

	/* virheilmoitus, jos lista on tyhjä */
	if (pANimi == NULL)
	{
		printf("Ei analysoitavaa, lue ensin nimitiedosto.\n");
		return pATulos;
	}
	/* varataan muistia tuloslistan alkiolle, lopetetaan, jos epäonnistuu */
	if ((ptrTulos = (TULOS *)malloc(sizeof(TULOS))) == NULL)
	{
		perror("Muistin varaus epäonnistui");
		exit(1);
	}

	printf("Anna analysoitavalle datasetille nimi: ");
	scanf("%s", ptrTulos->nimi);
	ptrTulos->pNext = NULL;

	printf("Analysoidaan listassa olevat tiedot.\n");

	ptrNimi = pANimi;
	pituus = strlen(ptrNimi->nimi);
	ptrTulos->maara = 1;
	/* asetetaan tuloslistan alkuarvoiksi ensimmäisen nimen pituus */
	ptrTulos->pitMin = ptrTulos->pitMax = kokooja = pituus;
	ptrNimi = ptrNimi->pNext;

	/* käydään nimilista läpi ja muutetaan tuloslistan alkion arvoja 
	tarvittaessa
	*/
	while (ptrNimi != NULL)
	{
		pituus = strlen(ptrNimi->nimi);
		if (pituus > ptrTulos->pitMax)
		{
			ptrTulos->pitMax = pituus;
		}
		else if (pituus < ptrTulos->pitMin)
		{
			ptrTulos->pitMin = pituus;
		}

		kokooja += pituus;
		ptrTulos->maara++;
		ptrNimi = ptrNimi->pNext;
	}
	/* nimien pituuksien keskiarvon laskeminen */
	ptrTulos->pitKA = (float)kokooja / ptrTulos->maara;
	
	/* kutsutaan aliohjelmaa, joka lisää alkion tuloslistaan */
	pATulos = lisaaTulos(pATulos, ptrTulos);

	return pATulos;
}
/*	Aliohjelma lisää parametrina annetun tuloslistan alkion listan perään ja
	tulostaa näytölle sen tiedot. Saa toisena parametrinaan pointterin 
	tuloslistan alkuun ja palauttaa sen lopuksi kutsuvaan ohjelmaan.
*/
TULOS *lisaaTulos(TULOS *pA, TULOS *ptrUusi)
{	
	/* pointteri listan läpikäymiseen */
	TULOS *ptr;

	/* lisätään alkio listan perään */
	if (pA == NULL)
	{
		pA = ptrUusi;
	}
	else
	{
		ptr = pA;
		while (ptr->pNext != NULL)
		{
			ptr = ptr->pNext;
		}
		ptr->pNext = ptrUusi;
	}
	/* tulostetaan alkion tiedot näytölle */
	printf("Datasetti Nimiä PitMin PitMax PitKA\n");
	printf("%-9s %5d %6d %6d %5.1f\n", ptrUusi->nimi, ptrUusi->maara,
		   ptrUusi->pitMin, ptrUusi->pitMax, ptrUusi->pitKA);

	return pA;
}
/*****************************************************************************/
/* eof */
