#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "socket.h"
#include "my_signal.h"
#include "son.h"

int main(int argc, char *argv[]){
    struct stat file_stat;
    /*repertoire racine du serveur*/
    const char *document_root="../html";
    if(stat(document_root, &file_stat)!=-1){
        if(S_ISDIR(file_stat.st_mode)){
            initialiser_signaux();
		    int serveur = creer_serveur(8080);
		    if(serveur == -1){
		        printf("erreur de creation serveur\n");
		        fflush(stdout);
		        return -1;
		    }
		    /*accepter les connexions indefiniment*/
		    while(1){
		        /*descripteur de fichier correspondant a la socket cliente*/
		        int client;
		        /*Attente d'une connexion (bloquant)*/
		        client=accept(serveur, NULL, NULL);
		        if(client==-1){
		            perror("connection to server fail");
		            return -1;
		        }else{
		            int pid=fork();
		            /*fork foire*/
		            if(pid==-1){
		                perror("fork");
		                return -1;
		            }
		            /*Dans le process fils*/
		            if(pid==0){
		                traitement_fils(client, document_root);
		            }else{
		                /*Dans le pere*/
		                close(client);
		            }
		        }
		    }
        }else{
            printf("%s n'est pas un repertoire valide! arret du serveur\n", document_root);
            return -1;
        }
    }else{
        perror("stat");
        return -1;
    }
}
