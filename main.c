#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lueKokonaisluku(void);
int lueReaaliluku(void);
void lueRoskat(void);
int menuValinta (void);
double nostoLaskin (double);
void nostoMuu (int , double);
void saldoTarkistus (double);
void lueMerkkijono(char merkkijono[], int pituus);


int main (void){

FILE * tili;
int virheLaskuri = 0 , valinta;
double saldo;

char tilinumero[256] , pin[256] , pintarkistus[256] , syote[256];


printf("Syota tilinumero >");
    lueMerkkijono(tilinumero, 256);
    strcat(tilinumero, ".tili");

if ((tili = fopen(tilinumero, "r"))==NULL)
    {
    printf("Tilinumero vaarin! Poistutaan...");
    exit(0);
    }
printf("\n*********************\n");
printf("\n  Tilinumero oikein!  \n");
printf("\n*********************\n");

printf("\nSyota PIN-koodi >");
fgets(pin , 256 , tili);
do{
    lueMerkkijono(syote , 256);
    if(pin[strlen(pin)-1] =='\n')
       pin[strlen(pin)-1] ='\0';

if(strcmp(syote , pin) != 0){
        virheLaskuri++;
 if (virheLaskuri == 3){
            printf("\nPIN-koodi syotetty liian monesti vaarin! Poistutaan...");
            exit(0);
    }
printf("\nPIN-koodi vaarin!\n\nYrita uudelleen >");
}

if (strcmp(syote , pin) == 0);

}while (strcmp( syote , pin ) != 0 && virheLaskuri < 3);

printf("\n*********************\n");
printf("\n  PIN-koodi oikein!  \n");
printf("\n*********************\n");

do{
valinta = menuValinta();
switch (valinta){

case 1:
    fscanf(tili , "%lf" , &saldo);
    saldo = nostoLaskin(saldo);
    tili = fopen(tilinumero , "w");
    fprintf(tili , "%s\n%2lf" , pin , saldo);
    fclose(tili);
    break;

case 2:
    fscanf(tili , "%lf" , &saldo);
    saldoTarkistus(saldo);
    break;

case 0:
    printf("\n*********************\n");
    printf("\n     Lopetetaan!     \n");
    printf("\n*********************\n");
    exit(0);
    break;


}


}while(valinta !=0);

return 0;}


int lueKokonaisluku(void){

   int luku;
   char mki;
   int status;

   while((status = scanf("%d%c", &luku, &mki))==0  || (2 == status && mki != '\n') ){
      lueRoskat();
      printf("Et syottanyt kokonaislukua > ");
   }

   return luku;
}

int lueReaaliluku(void){

   double luku;
   char mki;
   int status;

   while((status = scanf("%lf%c", &luku, &mki))==0  || (2 == status && mki != '\n') ){
      lueRoskat();
      printf("Et syottanyt reaalilukua > ");
   }

   return luku;
}

void lueRoskat(void){

   while( fgetc(stdin) != '\n');

}

void lueMerkkijono( char merkkijono[], int pituus ){

   fgets( merkkijono, pituus, stdin );

   if( merkkijono[ strlen(merkkijono) -1 ] == '\n')
      merkkijono[ strlen(merkkijono) -1 ] = '\0';
   else
      lueRoskat();

}

/*
 *
 * menuValinta - funktio tulostaa pankkiautomaatin päävalikon ja palauttaa käyttäjän tekemän valinnan main funktioon.
 *
 * paluuarvo - käyttäjän tekemä valinta  (int).
 *
 */
int menuValinta (void){

int valinta;

printf("\nTervetuloa! Valitse toiminto kirjoittamalla toiminnon numero:\n"
       "  1. Otto\n "
       " 2. Saldo\n"
       "  0. Lopeta\n"
       "  > ");

valinta = lueKokonaisluku();

while (valinta < 0 || valinta > 3){
        printf("\nVirheellinen valinta, yrita uudelleen >");
        valinta = lueKokonaisluku();
        }

return (valinta);
}

/*
 *
 * nostoLaskin - funktio tulostaa nosto-menun, jossa käyttäjä voi valita summan jonka haluaa nostaa
 *
 * Parametrit: (double) saldo, käyttäjän tilin saldo, luetaan tiedostosta.
 *
 * Paluuarvo: (double) saldo, käyttäjän uusi saldo noston jälkeen, tallennetaan tiedostoon.
 *
 */
double nostoLaskin (double saldo){
int valinta , muuSumma;


do{
printf("\n****Valitse summa jonka haluat nostaa kirjoittamalla summan edessa oleva numero****\n"
           "1: 20€\n"
           "2: 40€\n"
           "3: 60€\n"
           "4: 80€\n"
           "5: 100€\n"
           "6: Muu summa\n"
           "7: Palaa valikkoon\n"
           "0: Lopeta\n"
           ">");
valinta = lueKokonaisluku();
        if(valinta > 7)
            printf("Virheellinen valinta, yrita uudelleen\n");
}while(valinta > 7);



switch(valinta){

case 1:
    saldo = saldo - 20;
    printf("20 euron seteleita: 1\n");
    break;

case 2:
    saldo = saldo - 40;
    printf("20 euron seteleita: 2\n");
    break;

case 3:
    saldo = saldo -60;
    printf("20 euron seteleita: 3\n");
    break;

case 4:
    saldo = saldo -80;
    printf("20 euron seteleita: 4\n");
    break;

case 5:
    saldo = saldo - 100;
    printf("20 euron seteleita: 5\n");
    break;

case 6:
    do
    {
    printf("\nSyota haluamasi summa >");
    muuSumma = lueKokonaisluku();
        if(muuSumma > 1000 || muuSumma < 20 || muuSumma > saldo || muuSumma % 10 != 0 || muuSumma == 30){
            printf("\n***********************************************************\n");
            printf("\n          Virheellinen luku tai tililla ei katetta!\n                     Yrita uudelleen!\n");
            printf("\n***********************************************************\n");}
    }while(muuSumma > 1000 || muuSumma < 20 || muuSumma > saldo || muuSumma % 10 != 0 || muuSumma == 30);
    nostoMuu(muuSumma , saldo);
    saldo = saldo - muuSumma;
    break;

case 7:
    break;

case 0:
    printf("\n*********************\n");
    printf("\n     Lopetetaan!     \n");
    printf("\n*********************\n");
    exit(0);
    break;

}
return (saldo);
}

/*
 * saldoTarkistus - funktio tulostaa näytölle käyttäjän saldon.
 *
 * Parametri: (double) saldo, käyttäjän sen hetkinen saldo, luetaan tiedostosta.
 *
 */
void saldoTarkistus (double saldo){
int valinta;

printf("\n**************************\n");
printf("\n  Saldosi on %.2lf\n" , saldo);
printf("\n**************************\n");
    do {printf("\nHaluatko:\n"
           "1. Valitse uusi toiminto\n"
           "2. Lopeta\n"
           "\nValitse toiminto kirjoittamalla sen edessa oleva numero >");
           valinta = lueKokonaisluku();
           if(valinta > 2 || valinta == 0){
            printf("\n*******************************\n");
            printf("\nVaara valinta, yrita uudelleen\n");
            printf("\n*******************************\n");}
                if(valinta == 2)
                    exit(0);
}while(valinta > 2 || valinta < 0 || valinta == 0);
}

/*
 *
 * nostoMuu - funktio laskee, kuinka monta 50 euron ja 20 euron seteliä käyttäjä saa automaatista.
 *
 * Parametrit: (int) muuSumma, käyttäjän nostoLaskin - funktiossa syöttämä summa.
 *             (double) saldo, käyttäjän saldo, luetaan tiedostosta.
 *
 */
void nostoMuu (int muuSumma , double saldo){


int r_20 = 0 , r_50 = 0;

while (muuSumma % 50 != 0){
        muuSumma = muuSumma - 20;
        r_20++;
        }

r_50 = muuSumma / 50;

printf("\n50 euron seteleita: %d\n20 euron seteleita: %d\n" , r_50 , r_20);
}







