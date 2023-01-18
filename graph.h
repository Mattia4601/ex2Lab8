#ifndef ASDLAB8_GRAPH_H
#define ASDLAB8_GRAPH_H
#include "st.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//file header per il grafo non orientato e pesato implementato come ADT di 1 classe
//tipo arco
typedef struct edge{
    int v;
    int w;
    int wt;
}Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);//inizializza il grafo
void GRAPHfree(Graph G);//distrugge il grafo
Graph  GRAPHload(char *filename);//carica il grafo da file
void GRAPHinsertE(Graph G, int id1, int id2, int wt);//aggiunge un arco
void GRAPHremoveE(Graph G, int id1, int id2);//rimuove un arco
//inserisci nella symtable il nuovo vertice se non presente, altrimenti ritorna direttamente l'indice
//nella symtable relativo a quel vertice
<<<<<<< HEAD
int GRAPHgetIndex(Graph G, char *str, char* subnet);
=======
int GRAPHgetIndex(Graph G, char *str, char *subnet);
>>>>>>> 9f56c93b8923c5cc331215f417ff9bd2cb563376
void GRAPHstore(Graph G, FILE *fout);//carica il grafo su file
void GRAPHedges(Graph G, Edge *a);//crea i vari archi del grafo leggendo la matrice di adiacenza
void GRAPHelencaVertici(Graph g);
int GRAPHcreaVettArchiOrdinato(Graph g, int indexVertex,Edge *vArchi);
int GRAPHverificaSottografo(Graph g,char *vrt1, char *str2, char *str3);

#endif //ASDLAB8_GRAPH_H
