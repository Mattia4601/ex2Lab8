#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#define filename "grafo.txt"
int main(int argc, char *argv[]) {
    int cont=1,i,flag;
    Graph g=NULL;
    char vrt1[30],vrt2[30],vrt3[30];

    while(cont) {
        printf("\nOperations on weighted undirected graphs\n");
        printf("===============\n");
        printf("1.Load graph from file\n");
        printf("2.Print sorted vertexes and his edges\n");
        printf("3.Check if three vertexes are a complete subgraph\n");
        printf("4.Free graph and exit\n");
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
                    flag = GRAPHverificaSottografo(g,vrt1,vrt2,vrt3);
                    if (flag == -1){
                        printf("I tre vertici non formano un sottografo completo\n");
                    }
                    else if (flag == 1){
                        printf("I tre vertici formano un sottografo completo\n");
                    }
                    break;
                case 4:
                    cont = 0;
                    break;
                default:    printf("Invalid option\n");
            }
        }
    }
    GRAPHfree(g);
}
