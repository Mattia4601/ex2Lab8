#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#define filename "grafo.txt"
int main(int argc, char *argv[]) {
    int cont=1,i,flag,flag2=0,command;
    Graph g=NULL;
    char vrt1[30],vrt2[30],vrt3[30];

    while(cont) {
        printf("\nOperations on weighted undirected graphs\n");
        printf("===============\n");
        printf("1.Load graph from file\n");
        printf("2.Print sorted vertexes and his edges\n");
        printf("3.Check if three vertexes are a complete subgraph\n");
        printf("4.Load infos on adjacency list\n ");
        printf("5.Free graph and exit\n");
        printf("Enter your choice : ");
        if(scanf("%d",&i)<=0) {
            printf("Integers only!\n");
            exit(0);
        }
        else {
            switch(i) {
                case 1:
                    g = GRAPHload(filename);
                    break;
                case 2:
                    if (g==NULL){
                        printf("Grafo vuoto!\n");
                        break;
                    }
                    GRAPHelencaVertici(g);
                    break;
                case 3:
                    printf("Scrivi nomi dei tre vertici separati da uno spazio\n");
                    scanf("%s%s%s",vrt1,vrt2,vrt3);
                    if(flag2 == 1) {
                        printf("Se vuoi usare lista di adiacenze digita 1 altrimenti 0 uso matrice di adiacenze\n");
                        scanf("%d",&command);
                    }
                    if (command==0) {
                        flag = GRAPHverificaSottografo(g, vrt1, vrt2, vrt3);
                    }
                    else if (command == 1){
                        int id1,id2,id3;
                        id1= GRAPHgetIndex(g,vrt1);id2=GRAPHgetIndex(g,vrt2);id3=GRAPHgetIndex(g,vrt3);
                        flag = LISTcheckSubgraph(g,id1,id2,id3);
                    }
                    else{
                        break;
                    }
                    if (flag == -1){
                        printf("I tre vertici non formano un sottografo completo\n");
                    }
                    else if (flag == 1){
                        printf("I tre vertici formano un sottografo completo\n");
                    }
                    break;
                case 4:
                    GRAPHcaricaListAdj(g);
                    flag2=1;
                    break;
                case 5:
                    cont = 0;
                    break;
                default:    printf("Invalid option\n");
            }
        }
    }
    GRAPHfree(g);
}
