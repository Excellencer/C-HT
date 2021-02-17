/*****************************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet 
 * Tekijä: Kalle Liljeström
 * Opiskelijanumero: 
 * Päivämäärä: 4.3.2019
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto: Lähteenä C-ohjelmoinnin 
 * perusteet luentodiat sekä C-kieli ohjelmointiopas, Kasurinen & Nikula 2012
 */
/*****************************************************************************/
/* 	Pääohjelma toimii valikkopohjaisesti. Lukee annetusta tiedostosta nimiä 
	ja analysoi niiden pituuksia, ja voi tallettaa tulokset tiedostoon.
	Vaatii toimiakseen ali1 ja ali2 aliohjelmakirjastot. 
*/

#include <stdio.h>
#include "ali1.h"
#include "ali2.h"

int valikko(void);

int main(void)
{	
	/* pointterit nimi- ja tuloslistan alkuihin, aluksi NULL eli ei käytössä */
	NIMI *pAlkuNimi = NULL;
	TULOS *pAlkuTulos = NULL;
	int valinta;

	printf("\nTämä ohjelma tutkii nimitietoja sisältäviä tiedostoja.\n");

	/* loop, jossa kutsutaan aliohjelmia käyttäjän valinnan mukaan */
	do
	{
		switch (valinta = valikko())
		{
		case 1:
			pAlkuNimi = lueTiedosto(pAlkuNimi);
			break;
		case 2:
			tulostaLista(pAlkuNimi);
			break;
		case 3:
			pAlkuTulos = analysoi(pAlkuTulos, pAlkuNimi);
			break;
		case 4:
			tulostaTulokset(pAlkuTulos);
			break;
		case 5:
			tallennaTiedosto(pAlkuTulos);
			break;
		case 6:
			pAlkuTulos = tyhjennaTulokset(pAlkuTulos);
			printf("Tuloslista tyhjennetty.\n");
			break;
		case 0:
			printf("Kiitos ohjelman käytöstä.\n");
			break;
		default:
			printf("Tuntematon valinta, yritä uudestaan.\n");
			break;
		}
	} while (valinta != 0);

	/* tyhjennetään listat ja vapautetaan muistit */
	pAlkuNimi = tyhjennaLista(pAlkuNimi);
	pAlkuTulos = tyhjennaTulokset(pAlkuTulos);

	return 0;
}
/* 	Aliohjelma tulostaa valikon ja lukee käyttäjän valinnan, jonka se 
	palauttaa pääohjelmaan.
*/
int valikko(void)
{
	int luku;

	printf("\nValitse haluamasi toiminto alla olevasta valikosta:\n");
	printf("1) Lue nimitiedosto\n");
	printf("2) Tulosta listassa olevat tiedot\n");
	printf("3) Analysoi tiedot\n");
	printf("4) Tulosta kaikki tulostiedot\n");
	printf("5) Tallenna kaikki tulostiedot tiedostoon\n");
	printf("6) Tyhjennä tuloslista\n");
	printf("0) Lopeta\n");

	printf("Anna valintasi: ");
	scanf("%d", &luku);

	return luku;
}

/*****************************************************************************/
/* eof */
