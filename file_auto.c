#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void)
{
	char alfa[] = {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
	/*25 modelli di macchine da utilizzare casualemente*/
	char modello[25][22] = {
			  "Fiat Ottimo		",
		          "Fiat Punto		",
			  "Fiat Doblo'		",
			  "Fiat Ducato		",
			  "Fiat Bravo		",
			  "Toyota Subaru	",
			  "Toyota Crown 	",
			  "Toyota Celica	",
			  "Toyota Fortuner	",
			  "Jeep Renegade	",
			  "Jeep Compass 	",
			  "Jeep Cherokee	",
			  "Ford Fiesta		",
			  "Ford Focus		",
			  "Ford Ecosport	",
			  "Ford Laser		",
			  "Ford Mondeo		",
			  "Suzuki Across	",
			  "Suzuki Baleno	",
			  "Suzuki Celerio	",
			  "Opel Crossland	",
			  "Opel Corsa		",
			  "Opel Commodore	",
			  "Opel Diplomat	",
			  "Opel Frontera	"};
	
	int i, 		/*Lavoro: contatore per il numero di autoveicoli da stampare*/
	    j, 		/*Lavoro: contatore per il numero di caratteri alfanumerici da stampare*/
	    car,	/*Input: numero autoveicoli in elenco*/
	    esito_lettura = 0; /*Lavoro: assegnamento scanf*/
	FILE *file_auto;/*Inizializzazione del file .txt*/
	file_auto = fopen("file_auto.txt", "w");

	srand(time(0));

	do
	{
		printf("Digitare il numero di codici veicolo in elenco: ");
		esito_lettura = scanf("%d", &car);
		while(getchar() != '\n');
		if (esito_lettura != 1 || car < 0)
			printf("\nValore non accettabile. Inserire di nuovo\n");
	} while (esito_lettura != 1 || car < 0);

	for(i = 0;
	   (i <= car);
	    i++)
	{	/*Stampa dell'intestazione*/
		if( i == 0)
			fprintf(file_auto, "Veicolo\t\tProprietario\tModello\t\t\tAnno\n\n");
		else
		{/*Stampa delle 4 lettere del codice veicolo*/
		for(j = 0;
		   (j < 4);
		    j++)
		{
			fprintf(file_auto, "%c", alfa[26 + rand()%26]);
		}
		/*Stampa dei 2 numeri del codice veicolo*/
		for(j = 0;
		   (j < 2);
		    j++)
		{
			fprintf(file_auto, "%d", rand()%9);
		}
		fprintf(file_auto, "\t\t");
		/*Stampa delle 3 lettere del codice proprietario*/
		for(j = 0;
		   (j < 3);
		    j++)
		{
			fprintf(file_auto, "%c", alfa[26 + rand()%26]);
		}
		/*Stampa dei 3 numeri del codice proprietario*/
		for(j = 0;
		   (j < 3);
		    j++)
		{
			fprintf(file_auto, "%d", rand()%9);
		}
		/*Stampa casuale del modello del veicolo*/
		fprintf(file_auto, "\t\t%s\t", modello[rand()%25]);
		/*Stampa casuale dell'anno di immatricolazione*/
		fprintf(file_auto, "%d\n", 1990 + rand()%30);
		}
		
	}
	return(0);
}	
		    

