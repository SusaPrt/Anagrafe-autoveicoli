#include <stdio.h>	
#include <stdlib.h>
#include <string.h>

typedef struct dati_veicolo	
{ 
	char veicolo[7],
	     proprietario[7],
	     marca[20],
	     modello[20];
	int  immatricolazione;
} dati_veicolo_t;

typedef struct albero_veicolo	
{
	dati_veicolo_t dati;
	struct albero_veicolo *sx,
			      *dx;
} albero_veicolo_t;

void acquisire_file(FILE *, albero_veicolo_t **); 

void verifica_nuovo_inserimento(albero_veicolo_t **);	

void inserire_veicolo(albero_veicolo_t **, dati_veicolo_t, int); 

void rimuovere_veicolo(albero_veicolo_t **, char *); 

void cercare_veicolo(albero_veicolo_t *, char *); 

int veicolo_maggiore(albero_veicolo_t *); 

int veicolo_minore(albero_veicolo_t *); 

void stampare_dati(albero_veicolo_t *, FILE *, int);

int main(void)
{	
	char veicolo_ricerca[7],			
	     veicolo_rimosso[7],	
	     fine;			
	int to_do = 0,			
	    passi = 0; 	/*Lavoro: variabile contatore per i passi base*/

	albero_veicolo_t *radice_p = NULL;	
	int esito_lettura = 0;			

	FILE *file_auto = fopen("file_auto.txt", "r"); 
	
	/*Programma di Susanna Peretti*/	
	printf("Avvio programma.\n");
	
	if ((file_auto = fopen("file_auto.txt", "r")) == NULL)
		printf("\nIl file non e' stato acquisito correttamente. Il programma e' terminato.\n");
	else
	{
		while(fgetc(file_auto) != '\n'); 
		acquisire_file(file_auto,
 				&radice_p);
		printf("\nIl file e' stato acquisito correttamente.\n");

		do	
		{
			printf("\nSelezionare l'operazione da svolgere:\n");
			printf("0)Chiudi programma \t\t 1)Inserire un veicolo\n");
			printf("2)Rimuovere un veicolo \t\t 3)Cercare un veicolo\n");
			printf("4)Calcolare il valore maggiore \t 5)Calcolare il valore minore\n");

			do
			{
				esito_lettura = scanf("%d",
						&to_do);
				while(getchar() != '\n');	

				if (esito_lettura != 1 || to_do > 5 || to_do < 0) 
					printf("\nAttenzione. Inserire un numero da 0 a 5 per selezionare l'operazione.\n");

			} while ( esito_lettura != 1 || to_do < 0 || to_do > 5);

			if (to_do == 0)		
			{
				do
				{		
					printf("\nPremere 's' per accedere ai dati relativi agli autoveicoli salvati.\n");
					esito_lettura = scanf("%c", &fine);
					while(getchar() != '\n');
				} while (esito_lettura != 1);
				if (fine == 's' || fine == 'S')
				{		
					printf("Veicolo\t\tProprietario\tModello\t\tAnno\n");
					stampare_dati(radice_p, file_auto, 0);
				}

				do
				{		
					printf("\nPremere 's' per modificare i dati all'interno del file di testo 'file_auto.txt'.\n");
					esito_lettura = scanf("%c", &fine);
					while(getchar() != '\n');
				} while (esito_lettura != 1);
				if (fine == 's' || fine == 'S')
				{		
					fclose(file_auto);			
					file_auto = fopen("file_auto.txt", "w");	
					fprintf(file_auto, "Veicolo\t\tProprietario\tModello\t\tAnno\n");
					stampare_dati(radice_p, file_auto, 1);
					printf("\nIl file e' stato modificato con successo.\n");
				}
				printf("\nTermine programma.\n");
			}

			else if (to_do == 1)	
				verifica_nuovo_inserimento(&radice_p);

			else if (to_do == 2)	
			{	
				printf("\nInserire il codice veicolo da rimuovere: ");
				esito_lettura = scanf("%s", veicolo_rimosso);
				while(getchar() != '\n');
				if (esito_lettura == 1)
					rimuovere_veicolo(&radice_p, veicolo_rimosso);
			}

			else if (to_do == 3)	
			{	
				printf("\nInserire il codice veicolo da cercare: ");
				esito_lettura = scanf("%s", veicolo_ricerca);
				while(getchar() != '\n');
				if (esito_lettura == 1)
					cercare_veicolo(radice_p, veicolo_ricerca);
			}

			else if (to_do == 4)	
			{
				printf("\nIl veicolo con il valore maggiore e':\n");
				passi = veicolo_maggiore(radice_p);
				printf("\nNumero passi: %d", passi); /*Stampa del numero di passi base*/
			}
			else if (to_do == 5)	
			{
				printf("\nIl veicolo con il valore minore e':\n");
				passi = veicolo_minore(radice_p);
				printf("\nNumero passi: %d", passi); /*Stampa del numero di passi base*/
			}
		} while (to_do != 0);	
	fclose(file_auto); 	
	}
	return (0);
}
void acquisire_file(FILE *file_auto,
		    albero_veicolo_t **radice_p)
{	
	int errore = 0,		
	    i, 			
	    esito_lettura;	
	dati_veicolo_t to_add;
	do
	{	
		esito_lettura = fscanf(file_auto, "%s%s%s%s%d",
				to_add.veicolo,
				to_add.proprietario,
				to_add.marca,
				to_add.modello,
				&to_add.immatricolazione);
		
		if((feof(file_auto)) == 0 && esito_lettura == 5) 
		{

			for(i = 0;
		 	   i <= 5;
		 	   i++)
			{	
			if (i <= 3)	
				errore += (to_add.veicolo[i] >= 'A' && to_add.veicolo[i] <= 'Z')? 0: 1;

			else if (i > 3)
				errore += (to_add.veicolo[i] >= '0' && to_add.veicolo[i] <= '9')? 0: 1;

			if (i <= 2)	
				errore += (to_add.proprietario[i] >= 'A' && to_add.proprietario[i] <= 'Z')? 0: 1;
			
			else if (i > 2)
				errore += (to_add.proprietario[i] >= '0' && to_add.proprietario[i] <= '9')? 0: 1;

		}
		if(strlen(to_add.veicolo) != 6 || strlen(to_add.proprietario) != 6)
			errore++;
		if (errore == 0)
			inserire_veicolo(radice_p, to_add, 0);
		}
	
	} while (feof(file_auto) == 0);
}
void verifica_nuovo_inserimento(albero_veicolo_t **radice_p)
{
	int errore = 0,
	    esito_lettura = 0,
	    i;
	dati_veicolo_t to_add;

	do 	
	{	
		errore = 0;
		printf("\nInserire il codice del nuovo veicolo: ");		
		esito_lettura = scanf("%s", to_add.veicolo);
		while(getchar() != '\n');

		for(i = 0;
		    i <= 5;
		    i++)
		{	
			if (i <= 3)	
				errore += (to_add.veicolo[i] >= 'A' && to_add.veicolo[i] <= 'Z')? 0: 1;
					
			else if (i <= 5 && i > 3)
				errore += (to_add.veicolo[i] >= '0' && to_add.veicolo[i] <= '9')? 0: 1;
		}
		if(strlen(to_add.veicolo) != 6)
			errore++;

		if (errore > 0)	
			printf("\nIl codice veicolo inserito non e' corretto. Riprovare.\n");
	} while (errore > 0 && esito_lettura == 1);

	do	
	{
		errore = 0;
		printf("\nInserire il codice proprietario del nuovo veicolo: ");
		esito_lettura = scanf("%s", to_add.proprietario);
		while(getchar() != '\n');

		for(i = 0;
		    i <= 5;
		    i++)
		{
			if (i <= 2)	
				errore += (to_add.proprietario[i] >= 'A' && to_add.proprietario[i] <= 'Z')? 0: 1;
			
			else if (i <= 5 && i > 2)
				errore += (to_add.proprietario[i] >= '0' && to_add.proprietario[i] <= '9')? 0: 1;
		}
		if(strlen(to_add.proprietario) != 6)	
				errore++;

		if (errore > 0) 
			printf("\nIl codice proprietario inserito non è corretto. Riprovare\n");
	} while (errore > 0 && esito_lettura == 1);
	
	printf("\nInserire il modello del veicolo: (max 20 caratteri): ");
	esito_lettura = scanf("%s%s", to_add.marca, to_add.modello);
	while(getchar() != '\n');		

	do	
	{
		printf("\nInserire l'anno di immatricolazione del nuovo veicolo: ");
		esito_lettura = scanf("%d", &to_add.immatricolazione);
		while(getchar() != '\n');	
		if (esito_lettura != 1)			
			printf("\nL'anno non e' stato inserito correttamente. Riprovare.\n");
	} while (esito_lettura != 1);
	
	inserire_veicolo(radice_p, to_add, 1);
}
void inserire_veicolo(albero_veicolo_t **radice_p, dati_veicolo_t to_add, int stampa)
{
	albero_veicolo_t *nodo_p,	
			 *padre_p,
			 *nuovo_p;
	int passi = 4; 	/*Inizializzazione ciclo for + controlli di uscita*/

	for(nodo_p = padre_p = *radice_p; /*2*/
	   ((nodo_p != NULL) && (strcmp(nodo_p->dati.veicolo, to_add.veicolo) != 0)); /*2*/
	   padre_p = nodo_p, nodo_p = (strcmp(to_add.veicolo, nodo_p->dati.veicolo) < 0)? /*3*/
		   				nodo_p->sx: 
						nodo_p->dx) { passi += 5;}
		/*Condizione di continuazione + 3 istruzioni di aggiornamento*/

		if(nodo_p != NULL)
		{
					
			if(strcmp(nodo_p->dati.veicolo, to_add.veicolo) == 0)
				printf("\nIl veicolo non e' stato inserito perche' e' già presente in elenco.\n");
		}
	
		else				{
			if (stampa == 1)
			{
				passi++;
				printf("\nIl veicolo e' stato inserito con successo.\n");
			}
			nuovo_p = (albero_veicolo_t *)malloc(sizeof(albero_veicolo_t));
			nuovo_p->dati = to_add;
			nuovo_p->dx = nuovo_p->sx = NULL;
	       		if(nodo_p == *radice_p)
			{
				passi++;
				*radice_p = nuovo_p;
			}
			else
			{
				passi += 2;
				if(strcmp(to_add.veicolo, padre_p->dati.veicolo) < 0)
		        		padre_p->sx = nuovo_p;
				else			
					padre_p->dx = nuovo_p;
			}
			passi += 4; /*if + nuovo_p*/
		}
	printf("\nNumero passi: %d", passi);
		
	
}
void rimuovere_veicolo(albero_veicolo_t **radice_p, char *veicolo_rimosso)
{
	albero_veicolo_t *nodo_p,
			 *padre_p,
			 *sost_p;
	int passi = 4; /*Inizializzazione ciclo for + controlli di uscita*/

	for(nodo_p = padre_p = *radice_p; /*2*/		
	   ((nodo_p != NULL) && (strcmp(nodo_p->dati.veicolo, veicolo_rimosso) != 0)); /*2*/
	    padre_p = nodo_p, nodo_p = (strcmp(veicolo_rimosso, nodo_p->dati.veicolo) < 0)? /*3*/
		   				nodo_p->sx:
						nodo_p->dx){ passi += 5;}
		/*Condizione di continuazione + 3 istruzioni di aggiornamento*/
	if(nodo_p == NULL)
		printf("\nIl codice veicolo non e' stato trovato.\n");
	else
	{
		printf("\nIl veicolo e' stato rimosso con successo.\n");
		if(nodo_p->sx == NULL)
		{
			if(nodo_p == *radice_p)					
				*radice_p = nodo_p->dx;
			else
			{
				if(strcmp(veicolo_rimosso, padre_p->dati.veicolo) < 0)
					padre_p->sx = nodo_p->dx;
				else
					padre_p->dx = nodo_p->dx;
				passi += 3; /*If + assegnamento*/
			}
			passi += 2; /*Istruzioni if*/
		}
		else
		{
			if(nodo_p->dx == NULL)
			{
				if(nodo_p == *radice_p)
					*radice_p = nodo_p->sx;
				else
				{
					passi += 2; /*Istruzione if + assegnamento*/
					if((strcmp(veicolo_rimosso, padre_p->dati.veicolo)) == -1)
						padre_p->sx = nodo_p->sx;
					else
						padre_p->dx = nodo_p->sx;
				}
				passi += 2;/*Istruzioni if*/
			}
			
			else
			{
				sost_p = nodo_p;
			
				for(padre_p = sost_p, nodo_p = sost_p->sx;
				   (nodo_p->dx != NULL);
				   padre_p = nodo_p, nodo_p = nodo_p->dx){ passi += 3;}

				
				sost_p->dati = nodo_p->dati;

				if (padre_p == sost_p)
					padre_p->sx = nodo_p->sx;
				
				else
					padre_p->dx = nodo_p->sx;
				passi += 7;
			}
			free(nodo_p);
		} passi += 4; /*Istruzione if + printf + free(nodo_p)*/
	}
	printf("\nNumero passi: %d", passi);	
}
void cercare_veicolo(albero_veicolo_t *radice_p, char *veicolo_ricerca)
{
	albero_veicolo_t *nodo_p;		

	int passi = 3; /*Inizializzazione ciclo for + controlli di uscita*/

	for(nodo_p = radice_p;				
	   ((nodo_p != NULL) && (strcmp(nodo_p->dati.veicolo, veicolo_ricerca) != 0));
	    nodo_p = (strcmp(veicolo_ricerca, nodo_p->dati.veicolo) < 0)?
	    					nodo_p->sx: 
						nodo_p->dx){ passi += 4;}
		/*Condizione di continuazione + 3 istruzioni di aggiornamento*/
	if(nodo_p != NULL)							
	{
		printf("\nVeicolo richiesto:\n");
		printf("Veicolo\t\tProprietario\tModello\t\tAnno\n");
		printf("%s\t\t%s\t\t%s %s\t%d\n", 
			nodo_p->dati.veicolo, nodo_p->dati.proprietario, nodo_p->dati.marca, nodo_p->dati.modello, nodo_p->dati.immatricolazione);
		passi += 3; /*3 printf*/
	}
	
	else									
		printf("\nIl veicolo richiesto non e' stato trovato.\n");

	passi++; /*Istruzione if*/
	printf("\nNumero passi: %d", passi);
}
int veicolo_maggiore(albero_veicolo_t *nodo_p)
{
	int passi; 

	passi = 1;
	if (nodo_p->dx == NULL)
	{
		printf("Veicolo\t\tProprietario\tModello\t\tAnno\n");
		printf("%s\t\t%s\t\t%s %s\t%d\n", 
			nodo_p->dati.veicolo, nodo_p->dati.proprietario, nodo_p->dati.marca, nodo_p->dati.modello, nodo_p->dati.immatricolazione);
		passi += 2;
	}
	else
		passi += veicolo_maggiore(nodo_p->dx);

	return(passi);	
}
int veicolo_minore(albero_veicolo_t *nodo_p)
{
	int passi;

	passi = 1;
	if (nodo_p->sx == NULL)
	{
		printf("Veicolo\t\tProprietario\tModello\t\tAnno\n");
		printf("%s\t\t%s\t\t%s %s\t%d\n", 
			nodo_p->dati.veicolo, nodo_p->dati.proprietario, nodo_p->dati.marca, nodo_p->dati.modello, nodo_p->dati.immatricolazione);
		passi += 2;
	}
	else
		passi += veicolo_minore(nodo_p->sx);
	return(passi);
}
void stampare_dati(albero_veicolo_t *radice_p, FILE *file_auto, int stampa)
{ 
	if(radice_p != NULL)
	{
		if(stampa == 0)
			printf("%s\t\t%s\t\t%s %s\t%d\n",
					radice_p->dati.veicolo, radice_p->dati.proprietario,radice_p->dati.marca, radice_p->dati.modello, radice_p->dati.immatricolazione);
		else		
			fprintf(file_auto, "%s\t\t%s\t\t%s %s\t\t%d\n",
				radice_p->dati.veicolo, radice_p->dati.proprietario,radice_p->dati.marca, radice_p->dati.modello, radice_p->dati.immatricolazione);
		
		stampare_dati(radice_p->sx, file_auto, stampa);
		stampare_dati(radice_p->dx, file_auto, stampa);
	}
}
