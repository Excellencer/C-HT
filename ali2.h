/*****************************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet 
 * Tekijä: Kalle Liljeström
 * Opiskelijanumero: 
 * Päivämäärä: 4.3.2019
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto: Lähteenä C-ohjelmoinnin 
 * perusteet luentodiat sekä C-kieli ohjelmointiopas, Kasurinen & Nikula 2012
 */
/*****************************************************************************/
/* Header -tiedosto ali2 aliohjelmakirjastolle */

/* include guard */
#ifndef ali2_h
#define ali2_h

/* aliohjelmien esittelyt */
void tulostaLista(NIMI *pA);
void tulostaTulokset(TULOS *pA);
NIMI *tyhjennaLista(NIMI *pA);
TULOS *tyhjennaTulokset(TULOS *pA);
void tallennaTiedosto(TULOS *pA);

#endif
/*****************************************************************************/
/* eof */
