#include <iostream>
#define TOT 6
#include <string>
#include <cstdio>
#include <cstdlib>
#include <fstream>

using namespace std;

typedef struct Taccesspoint{
    char Bssid[18];
    char Segnale[3];
    char Canale[3];

    bool contienevuoto() {
        for (int i=0; i<3; i++){
            //printf("Elemento in posizione %d uguale a \" %c \" \n",i,Canale[i]);
            if(Canale[i]==32) //se il carattere e' uno spazio
                return true;
        }
        return false;
    }
}Taccesspoint;

int main() {

    FILE *fin, *fout;
    Taccesspoint AccessPoint[TOT];
    char trash [2];
    //aggiungo un carattere di chiusura a termine del file in modo da poter riconoscere la fine
    if((fin=fopen("MyLogFile.txt", "a"))== NULL){
        printf("Errore di apertura del file\n");
        return 1;
    }
    fprintf(fin,"F");
    fclose(fin);
    //Leggo il file ed estraggo i dati
    if((fin=fopen("MyLogFile.txt", "r"))== NULL){
        printf("Errore di apertura del file\n");
        return 1;
    }
    printf("Apertura del file\n");
    rewind(fin);
    fseek(fin,30,SEEK_SET);
    int i=0;
    while(true){
    	if((trash=="F")||(i>=TOT)) goto fuori;
    	printf("Trash: %s \n", trash);
        fgets(AccessPoint[i].Bssid, 18, fin);
        printf("BSSID: %s \n", AccessPoint[i].Bssid);
        fseek(fin,37,SEEK_CUR);
        fgets(AccessPoint[i].Segnale, 3, fin);
        fseek(fin,40,SEEK_CUR);
        fgets(AccessPoint[i].Canale, 3, fin);
        if (AccessPoint[i].contienevuoto())
            fseek(fin,31,SEEK_CUR);
        else
            fseek(fin,32,SEEK_CUR);
        printf("Letta la %d riga del file del file\n",i+1);
        i++;
        fgets(trash,2,fin);
    }
    fuori:
    printf("Trash: %s \n", trash);
    printf("Chiudo il file fin");
    fclose(fin);
    remove("MyLogFile.txt");
    remove("Risultati.js");
    remove("DataBase/Risultati.js");
    printf("Aperto il file .js");
    fout=fopen("Risultati.js", "w");
    fprintf( fout, "{ \"AccessPoint\" :[ \n");
    int j;
    for(int j=0; j<i-1; j++) {
        fprintf( fout, "{\"Bssid\":\"%s\"," , AccessPoint[j].Bssid);
        fprintf( fout, "\"Canale\":\"%s\"," , AccessPoint[j].Canale);
        fprintf( fout, "\"Segnale\":\"%s\"} ,\n" , AccessPoint[j].Segnale);
    }
    fprintf( fout, "{\"Bssid\":\"%s\"," , AccessPoint[j].Bssid);
    fprintf( fout, "\"Canale\":\"%s\"," , AccessPoint[j].Canale);
    fprintf( fout, "\"Segnale\":\"%s\"} \n] }" , AccessPoint[j].Segnale);

    fclose(fout);

    fout=fopen("DataBase/Risultati.js", "w");
    for(int j=0; j<i; j++) {
        fprintf( fout, "%s\n" , AccessPoint[j].Bssid);
        fprintf( fout, "%s\n" , AccessPoint[j].Canale);
        fprintf( fout, "%s\n\n" , AccessPoint[j].Segnale);
    }

    fclose(fout);
    //system("PAUSE");
    return 0;
}
