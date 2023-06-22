#include <stdio.h>	/*Inclusione delle librerie standard*/
#include <stdlib.h>
#include <string.h>

typedef struct dati_veicolo	/*Definizione di un tipo struttura contenente i dati veicoli*/
{ 
	char veicolo[7],
	     proprietario[7],
	     marca[20],
	     modello[20];
	int  immatricolazione;
} dati_veicolo_t;

typedef struct albero_veicolo	/*Definzione struttura ad albero binario*/
{
	dati_veicolo_t dati;
	struct albero_veicolo *sx,
			      *dx;
} albero_veicolo_t;

/*Dichiarazione delle funzioni*/

void acquisire_file(FILE *, albero_veicolo_t **); /*Funzione per acquisire il file di partenza con i dati dei veicoli*/

void verifica_nuovo_inserimento(albero_veicolo_t **);	/*Funzione per la validazione dei nuovi dati da inserire*/

void inserire_veicolo(albero_veicolo_t **, dati_veicolo_t, int); /*Funzione per l'inserimento di un nuovo veicolo*/

void rimuovere_veicolo(albero_veicolo_t **, char *); /*Funzione per la rimozione di un veicolo*/

void cercare_veicolo(albero_veicolo_t *, char *); /*Funzione per la ricerca di un veicolo*/

void veicolo_maggiore(albero_veicolo_t *); /*Funzione ricorsiva per calcolo e stampa del codice veicolo maggiore*/

void veicolo_minore(albero_veicolo_t *); /*Funzione ricorsiva per calcolo e stampa del codice veicolo minore*/

void stampare_dati(albero_veicolo_t *, FILE *, int); /*Funzione ricorsiva di visita dell'albero binario*/

int main(void)
{	/*Dichiarazione delle variabili locali alla funzioni*/
	/*Variabili di input*/
	char veicolo_ricerca[7],		/*Variabile per l'acquisizione del codice veicolo da cercare*/		
	     veicolo_rimosso[7],		/*Variabile per l'acquisizione del codice veicolo da rimuovere*/
	     fine;				/*Variabile per selezionare la scelta dell'utente sulla stampa dei dati*/
	int to_do = 0;				/*Variabile per selezionare l'operazione*/


	/*Variabili di lavoro*/
	albero_veicolo_t *radice_p = NULL;	/*Inizializzazione della radice*/
	int esito_lettura = 0;			/*Variabile di controllo per la selezione dell'utente*/

	FILE *file_auto = fopen("file_auto.txt", "r"); 	/*File per l'importazione dei dati*/
	
	/*Programma di Susanna Peretti*/
	printf("Avvio programma.\n");
	
	/*Apertura e controllo del file in acquisizione*/
	if ((file_auto = fopen("file_auto.txt", "r")) == NULL)
		printf("\nIl file non e' stato acquisito correttamente. Il programma e' terminato.\n");
	else
	{
		while(fgetc(file_auto) != '\n'); /*Saltare la prima linea di intestazione*/
		acquisire_file(file_auto,	/*Funzione per l'acquisizione dei veicoli da file*/
			       &radice_p);
		printf("\nIl file e' stato acquisito correttamente.\n");

		do	/*Elenco delle operazioni da poter svolgere*/
		{
			printf("\nSelezionare l'operazione da svolgere:\n");
			printf("0)Chiudi programma \t\t 1)Inserire un veicolo\n");
			printf("2)Rimuovere un veicolo \t\t 3)Cercare un veicolo\n");
			printf("4)Calcolare il valore maggiore \t 5)Calcolare il valore minore\n");

			do
			{
				esito_lettura = scanf("%d", &to_do);
				while(getchar() != '\n');	/*Pulizia del buffer*/
				if (esito_lettura != 1 || to_do > 5 || to_do < 0) /*Validazione stretta della scelta dell'utente*/
					printf("\nAttenzione. Inserire un numero da 0 a 5 per selezionare l'operazione.\n");

			} while ( esito_lettura != 1 || to_do < 0 || to_do > 5);

			if (to_do == 0)		/*Chiusura del programma*/
			{
				do
				{		/*Richiesta di stampare a schermo i dati presenti nell'albero*/
					printf("\nPremere 's' per accedere ai dati relativi agli autoveicoli salvati.\n");
					esito_lettura = scanf("%c", &fine);
					while(getchar() != '\n');
				} while (esito_lettura != 1);
				if (fine == 's' || fine == 'S')
				{		/*Stampa a schermo di tutti i dati archiviati*/
					printf("Veicolo\t\tProprietario\tModello\t\tAnno\n");
					stampare_dati(radice_p, file_auto, 0);
				}

				do
				{		/*Richiesta di modificare il file .txt preso in acquisizione*/
					printf("\nPremere 's' per modificare i dati all'interno del file di testo 'file_auto.txt'.\n");
					esito_lettura = scanf("%c", &fine);
					while(getchar() != '\n');
				} while (esito_lettura != 1);
				if (fine == 's' || fine == 'S')
				{		/*Aggiornamento del file di acquisizione 'file_auto.txt'*/
					fclose(file_auto);				/*Chiusura del file in lettura*/
					file_auto = fopen("file_auto.txt", "w");	/*Apertura del file in scrittura*/
					fprintf(file_auto, "Veicolo\t\tProprietario\tModello\t\tAnno\n");
					stampare_dati(radice_p, file_auto, 1);
					printf("\nIl file e' stato modificato con successo.\n");
				}
				printf("\nTermine programma.\n");
			}

			else if (to_do == 1)	/*Inserimento di un nuovo veicolo*/
				verifica_nuovo_inserimento(&radice_p);

			else if (to_do == 2)	/*Rimozione di un veicolo*/
			{	/*Acquisizione del codice da rimuovere*/
				printf("\nInserire il codice veicolo da rimuovere: ");
				esito_lettura = scanf("%s", veicolo_rimosso);
				while(getchar() != '\n');
				if (esito_lettura == 1) 
					rimuovere_veicolo(&radice_p, veicolo_rimosso);
			}

			else if (to_do == 3)	/*Ricerca di un veicolo*/
			{	/*Acquisizione del codice veicolo da cercare*/
				printf("\nInserire il codice veicolo da cercare: ");
				esito_lettura = scanf("%s", veicolo_ricerca);
				while(getchar() != '\n');
				if (esito_lettura == 1)
					cercare_veicolo(radice_p, veicolo_ricerca);
			}
			/*Ricerca del codice veicolo con valore maggiore secondo l'ordine lessicografico*/
			else if (to_do == 4)	
			{
				printf("\nIl veicolo con il valore maggiore e':\n");
				veicolo_maggiore(radice_p);
			}
			/*Ricerca del codice veicolo con valore minore secondo l'ordine lessicografico*/
			else if (to_do == 5)	
			{
				printf("\nIl veicolo con il valore minore e':\n");
				veicolo_minore(radice_p);
			}
		} while (to_do != 0);	
	fclose(file_auto); 	/*Chiusura del file di acquisizione*/
	}
	return (0);
}
/*Definzione delle funzioni*/
/*Funzione per acquisire il file di partenza con i dati dei veicoli*/
void acquisire_file(FILE *file_auto,
		    albero_veicolo_t **radice_p)
{	/*Dichiarazione delle variabili locali alla funzione*/
	int errore = 0,		/*Variabile di controllo*/
	    i, 			/*Indice per controllo codice veicolo*/
	    esito_lettura;	/*Controllo per la fscanf*/
	dati_veicolo_t to_add;	/*Dati del veicolo da inserire*/

	do
	{	/*Acquisizione da file dei dati relativi ai veicoli*/
		esito_lettura = fscanf(file_auto, "%s%s%s%s%d",
				to_add.veicolo,
				to_add.proprietario,
				to_add.marca,
				to_add.modello,
				&to_add.immatricolazione);
		/*Controllare che sia stata raggiunta la fine del file e che siano stati acquisiti 5 valori*/
		if((feof(file_auto)) == 0 && esito_lettura == 5) 
		{

			for(i = 0;
		 	   i <= 5;
		 	   i++)
			{	
			if (i <= 3)	/*Controllo del codice veicolo in inserimento*/
				errore += (to_add.veicolo[i] >= 'A' && to_add.veicolo[i] <= 'Z')? 0: 1;

			else if (i > 3)
				errore += (to_add.veicolo[i] >= '0' && to_add.veicolo[i] <= '9')? 0: 1;

			if (i <= 2)	/*Controllo del codice propietario in inserimento*/
				errore += (to_add.proprietario[i] >= 'A' && to_add.proprietario[i] <= 'Z')? 0: 1;
			
			else if (i > 2)
				errore += (to_add.proprietario[i] >= '0' && to_add.proprietario[i] <= '9')? 0: 1;

		}
		/*Controllo lunghezza della stringa in acquisizione*/
		if(strlen(to_add.veicolo) != 6 || strlen(to_add.proprietario) != 6)
			errore++;
		/*Se non sono presenti errori, viene chiamata la funzione di inserimento*/
		if (errore == 0)
			inserire_veicolo(radice_p, to_add, 0);
		}
	
	} while (feof(file_auto) == 0);
}

/*Funzione per la validazione dei nuovi dati da inserire*/
void verifica_nuovo_inserimento(albero_veicolo_t **radice_p)
{
	int errore = 0,
	    esito_lettura = 0,
	    i;
	dati_veicolo_t to_add;

	do 	/*Inserimento del nuovo codice veicolo*/
	{	
		errore = 0;
		printf("\nInserire il codice del nuovo veicolo: ");		
		esito_lettura = scanf("%s", to_add.veicolo);
		while(getchar() != '\n');

		for(i = 0;
		    i <= 5;
		    i++)
		{	
			if (i <= 3)	/*Controllo del codice veicolo in inserimento*/
				errore += (to_add.veicolo[i] >= 'A' && to_add.veicolo[i] <= 'Z')? 0: 1;
					
			else if (i <= 5 && i > 3)
				errore += (to_add.veicolo[i] >= '0' && to_add.veicolo[i] <= '9')? 0: 1;
		}
		if(strlen(to_add.veicolo) != 6)	/*Validazione della lunghezza della stringa*/
			errore++;

		if (errore > 0)	/*Se sono presenti errori, si chiede il reinserimento del codice*/
			printf("\nIl codice veicolo inserito non e' corretto. Riprovare.\n");
	} while (errore > 0 && esito_lettura == 1);

	do	/*Inserimento del codice proprietario*/
	{
		errore = 0;
		printf("\nInserire il codice proprietario del nuovo veicolo: ");
		esito_lettura = scanf("%s", to_add.proprietario);
		while(getchar() != '\n');

		for(i = 0;
		    i <= 5;
		    i++)
		{
			if (i <= 2)	/*Controllo del codice proprietario in inserimento*/
				errore += (to_add.proprietario[i] >= 'A' && to_add.proprietario[i] <= 'Z')? 0: 1;
			
			else if (i <= 5 && i > 2)
				errore += (to_add.proprietario[i] >= '0' && to_add.proprietario[i] <= '9')? 0: 1;
		}
		if(strlen(to_add.proprietario) != 6)	/*Validazione della lunghezza della stringa*/
				errore++;

		if (errore > 0) /*Se sono presenti errori, si chiede il reinserimento del codice*/
			printf("\nIl codice proprietario inserito non è corretto. Riprovare\n");
	} while (errore > 0 && esito_lettura == 1);

		/*Inserimento del modello del nuovo veicolo*/
	printf("\nInserire il modello del veicolo (max 20 caratteri): ");
	esito_lettura = scanf("%s%s", to_add.marca, to_add.modello);
	while(getchar() != '\n');		

	do	/*Inserimento dell'anno di immatricolazione del nuovo veicolo*/
	{	/*Validazione stretta dell'anno di immatricolazione inserito*/
		printf("\nInserire l'anno di immatricolazione del nuovo veicolo: ");
		esito_lettura = scanf("%d", &to_add.immatricolazione);
		while(getchar() != '\n');	
		if (esito_lettura != 1)			
			printf("\nL'anno non e' stato inserito correttamente. Riprovare.\n");
	} while (esito_lettura != 1);
	
	/*A seguito della validazione di tutti i dati si esegue l'inserimento*/
	inserire_veicolo(radice_p, to_add, 1);
}
/*Funzione per l'inserimento di un nuovo veicolo*/
void inserire_veicolo(albero_veicolo_t **radice_p, dati_veicolo_t to_add, int stampa)
{
	/*Dichiarazione delle variabili locali alla funzione*/
	albero_veicolo_t *nodo_p,	/*Nodi puntatore per muoversi all'interno dell'albero*/
			 *padre_p,
			 *nuovo_p;
	 /*Ricerca di un nodo libero per l'inserimento del nuovo veicolo*/
	for(nodo_p = padre_p = *radice_p;
	   ((nodo_p != NULL) && (strcmp(nodo_p->dati.veicolo, to_add.veicolo) != 0));
	   padre_p = nodo_p, nodo_p = (strcmp(to_add.veicolo, nodo_p->dati.veicolo) < 0)?
		   				nodo_p->sx: 
						nodo_p->dx);
	if(nodo_p != NULL)	/*Se il nodo puntato non e' vuoto*/
	{	/*Il codice veicolo coincide con uno gia' presente*/	
		if(strcmp(nodo_p->dati.veicolo, to_add.veicolo) == 0) 
			printf("\nIl veicolo non e' stato inserito perche' e' già presente in elenco.\n");
	}

	else		/*Inserimento del nuovo veicolo in un nodo libero*/
	{
		if (stampa == 1)/*Variabile di controllo per inserimento da tastiera*/
			printf("\nIl veicolo e' stato inserito con successo.\n");
		nuovo_p = (albero_veicolo_t *)malloc(sizeof(albero_veicolo_t));
		nuovo_p->dati = to_add; /*Inserimento autoveicolo*/
		nuovo_p->dx = nuovo_p->sx = NULL; 
		/*Caso base: inserimento in albero vuoto*/
	        if(nodo_p == *radice_p) 
			*radice_p = nuovo_p; /*Inizializzazione radice*/ 
		else
			/*Caso generale: inserimento in albero non vuoto*/
			if(strcmp(to_add.veicolo, padre_p->dati.veicolo) < 0)
		        	padre_p->sx = nuovo_p;
			else			
				padre_p->dx = nuovo_p;
	}	
}
/*Funzione per la rimozione di un veicolo presente nel sistema*/
void rimuovere_veicolo(albero_veicolo_t **radice_p, char *veicolo_rimosso)
{
	/*Dichiarazione delle variabili locali*/
	albero_veicolo_t *nodo_p,
			 *padre_p,
			 *sost_p;

	/*Ricerca del codice inserito all'interno dell'albero*/
	for(nodo_p = padre_p = *radice_p; 
	   ((nodo_p != NULL) && (strcmp(nodo_p->dati.veicolo, veicolo_rimosso) != 0));
	    padre_p = nodo_p, nodo_p = (strcmp(veicolo_rimosso, nodo_p->dati.veicolo) < 0)?
		   				nodo_p->sx:
						nodo_p->dx);
	if(nodo_p == NULL)
		printf("\nIl codice veicolo non e' stato trovato.\n");
	else
	{
		printf("\nIl veicolo e' stato rimosso con successo.\n");
		/*Caso in cui il nodo non abbia un figlio sinistro*/
		if(nodo_p->sx == NULL)
		{
			if(nodo_p == *radice_p)	/*Se il nodo coincide con la radice*/				
				*radice_p = nodo_p->dx; /*Il figlio destro è la nuova radice*/

			else /*Si assegna il padre in base alle caratteristiche del nodo*/
				if(strcmp(veicolo_rimosso, padre_p->dati.veicolo) < 0)
					padre_p->sx = nodo_p->dx;
				else
					padre_p->dx = nodo_p->dx;
		}
		else
		{	/*Caso in cui il nodo non abbia un figlio destro*/
			if(nodo_p->dx == NULL)
			{
				if(nodo_p == *radice_p) /*Se il nodo coincide con la radice*/
					*radice_p = nodo_p->sx; /*Il figlio sinistro è la nuova radice*/

				else /*Si assegna il padre in base alle caratteristiche del nodo*/
					if((strcmp(veicolo_rimosso, padre_p->dati.veicolo)) == -1)
						padre_p->sx = nodo_p->sx;
					else
						padre_p->dx = nodo_p->sx;
			}
			
			else
			{ /*Il nodo ha due figli, si cerca il suo successore e si assegna il nodo padre*/
				sost_p = nodo_p;
			
				for(padre_p = sost_p, nodo_p = sost_p->sx;
				   (nodo_p->dx != NULL);
				   padre_p = nodo_p, nodo_p = nodo_p->dx);
				
				sost_p->dati = nodo_p->dati;

				if (padre_p == sost_p)
					padre_p->sx = nodo_p->sx;
				else
					padre_p->dx = nodo_p->sx;

			}
			free(nodo_p);
		}
	}	
}
/*Funzione per la ricerca di un veicolo*/
void cercare_veicolo(albero_veicolo_t *radice_p, char *veicolo_ricerca)
{
	/*Dichiarazione delle variabili locali*/
	albero_veicolo_t *nodo_p;	/*Nodo puntatore per muoversi all'interno della struttura*/

	for(nodo_p = radice_p;		/*Ricerca del nodo contenente il codice veicolo indicato*/
	   ((nodo_p != NULL) && (strcmp(nodo_p->dati.veicolo, veicolo_ricerca) != 0));
	    nodo_p = (strcmp(veicolo_ricerca, nodo_p->dati.veicolo) < 0)?
	    					nodo_p->sx: 
						nodo_p->dx);
	if(nodo_p != NULL) /*Il codice e' presente in elenco*/							
	{
		printf("\nVeicolo richiesto:\n");
		printf("Veicolo\t\tProprietario\tModello\t\tAnno\n");
		printf("%s\t\t%s\t\t%s %s\t%d\n", 
			nodo_p->dati.veicolo, nodo_p->dati.proprietario, nodo_p->dati.marca, nodo_p->dati.modello, nodo_p->dati.immatricolazione);
	}
	
	else									
		printf("\nIl veicolo richiesto non e' stato trovato.\n");
}
/*Funzione ricorsiva per calcolo e stampa del codice veicolo maggiore*/
void veicolo_maggiore(albero_veicolo_t *nodo_p)
{
	if (nodo_p->dx == NULL)
	{
		printf("Veicolo\t\tProprietario\tModello\t\tAnno\n");
		printf("%s\t\t%s\t\t%s %s\t%d\n", 
			nodo_p->dati.veicolo, nodo_p->dati.proprietario, nodo_p->dati.marca, nodo_p->dati.modello, nodo_p->dati.immatricolazione);
	}
	else
		veicolo_maggiore(nodo_p->dx);	
}
/*Funzione ricorsiva per calcolo e stampa del codice veicolo minore*/
void veicolo_minore(albero_veicolo_t *nodo_p)
{
	if (nodo_p->sx == NULL)
	{
		printf("Veicolo\t\tProprietario\tModello\t\tAnno\n");
		printf("%s\t\t%s\t\t%s %s\t%d\n", 
			nodo_p->dati.veicolo, nodo_p->dati.proprietario, nodo_p->dati.marca, nodo_p->dati.modello, nodo_p->dati.immatricolazione);
	}
	else
		veicolo_minore(nodo_p->sx);
}
/*Funzione ricorsiva di visita dell'albero binario*/
void stampare_dati(albero_veicolo_t *radice_p, FILE *file_auto, int stampa)
{ 
	if(radice_p != NULL)
	{
		if(stampa == 0)	/*Stampa a schermo di tutti dati archiviati*/
			printf("%s\t\t%s\t\t%s %s\t%d\n",
				radice_p->dati.veicolo, radice_p->dati.proprietario,radice_p->dati.marca, radice_p->dati.modello, radice_p->dati.immatricolazione);
		else		/*Aggiornamento del file di acquisizione 'file_auto.txt'*/
			fprintf(file_auto, "%s\t\t%s\t\t%s %s\t\t%d\n",
				radice_p->dati.veicolo, radice_p->dati.proprietario,radice_p->dati.marca, radice_p->dati.modello, radice_p->dati.immatricolazione);
		
		/*Algoritmo di visita in ordine anticipato*/
		stampare_dati(radice_p->sx, file_auto, stampa);
		stampare_dati(radice_p->dx, file_auto, stampa);
	}
}
