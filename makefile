anagrafe_autoveicoli: 
	gcc -ansi -Wall -O anagrafe_autoveicoli.c -o anagrafe_autoveicoli
	gcc -ansi -Wall -O file_auto.c -o file_auto
	gcc -ansi -Wall -O v_sperimentale.c -o v_sperimentale
	
pulisci: 
	rm -f anagrafe_autoveicoli.o
	rm -f file_auto.o
	rm -f v_sperimentale.o

pulisci_tutto:
	rm -f anagrafe_autoveicoli anagrafe_autoveicoli.o
	rm -f file_auto file_auto.o
	rm -f v_sperimentale v_sperimentale.o
