#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"
#define MAXC 30
#define maxWT INT_MAX

struct graph {
    int V;
    int E;
    int **madj;
    ST tab;
};

//funzioni che possono essere viste solo da questo file
static Edge EDGEcreate(int v, int w, int wt);
static int **MATRIXinit(int r, int c, int val);
static void insertE(Graph G, Edge e);




int GRAPHverificaSottografo(Graph g,char *vrt1,char *vrt2, char* vrt3){
    int id1,id2,id3;
    id1 = STsearch(g->tab,vrt1);
    id2 = STsearch(g->tab,vrt2);
    id3 = STsearch(g->tab,vrt3);
    //verifico se il primo è collegato con gli altri due
    if (g->madj[id1][id2] == maxWT || g->madj[id1][id3] == maxWT ){
        return -1;//-1 sta per 'non è un sottografo completo'
    }
    //verifico se il secondo è collegato con gli altri due
    if (g->madj[id2][id1] == maxWT || g->madj[id2][id3] == maxWT ){
        return -1;//-1 sta per 'non è un sottografo completo'
    }
    //verifico se il terzo è collegato con gli altri due
    if (g->madj[id3][id1] == maxWT || g->madj[id3][id2] == maxWT ){
        return -1;//-1 sta per 'non è un sottografo completo'
    }
    return 1;//1 sta per 'è un sottografo completo'
}



void GRAPHelencaVertici(Graph g){
    char **verticiOrdinati,*str;//str e' dove salvo il nome della sottorete
    int nLinkedVertex,index,j,i,nVertici,peso;

    verticiOrdinati = STgetSortVertexs(g->tab); //salvo su un vettore temporaneo i vertici in ordine alfabetico
    nVertici = STsize(g->tab);
    str = malloc(MAXC * sizeof(char ));
    for (i=0; i<nVertici; i++) {//per ogni vertice del grafo
        str = STgetSubnetByIndex(g->tab, i);
        printf("Verice-->   Nome elab: %s   Nome sottorete: %s\n",verticiOrdinati[i],str);
        printf("Archi:\n");
        for (j=0; j<nVertici; j++){
            if (g->madj[i][j] != maxWT){//significa che il j esimo vertice forma un arco con i
                printf("Nome elab: %s  Nome sottorete: %s  Peso arco: %d\n", STsearchByIndex(g->tab,j),
                       STgetSubnetByIndex(g->tab,j),g->madj[i][j]);
            }
        }
    }
}

static Edge EDGEcreate(int v, int w, int wt){
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}

int **MATRIXinit(int r, int c, int val){
    int i,j;
    int **t = malloc(r* sizeof(int *));
    if (t == NULL){
        return NULL;
    }

    for (i=0;i<r;i++){
        t[i] = malloc(c * sizeof(int *));
        if (t[i]==NULL){
            return NULL;
        }
    }
    for (i=0; i<r; i++){
        for (j=0; j<c; j++){
            t[i][j]=val;//inizializzo tutte le celle della matrice di adiacenza
        }
    }
    return t;
}
//V è il numero di vertici del grafo ricorda!
Graph GRAPHinit(){
    Graph g=malloc(sizeof(*g));
    if (g==NULL)
        return NULL;
    g->V = 0;
    g->E = 0;
    g->madj = NULL;
    g->tab = STinit(1);//inizializza la tabella di simboli
    if(g->tab == NULL){
        return NULL;
    }
    return g;
}

void GRAPHfree(Graph g){
    int i;

    for (i=0; i<g->V;i++){
        free(g->madj[i]);
    }
    free(g->madj);
    STfree(g->tab);
    free(g);
}
//da cambiare
Graph GRAPHload(char* filename){
    int V,c=0,id1,id2,wt;
    char vert1[MAXC], vert2[MAXC],subnet1[MAXC],subnet2[MAXC];
    Graph g;
    FILE *fin;
    char buff[400];
    //prima cosa alloco la struct di tipo graph g è il puntatore alla struct
    g = GRAPHinit();//nota la mat di adj la alloco dopo che ho salvato i vertici ordinatamente nella symbol table
    //1a lettura del file per capire quanti sono i vertici e salvarli in ordine alfabetico nella symbol table
    fin = fopen(filename,"r");
    if (fin == NULL)
        return NULL;
    while (fscanf(fin,"%s%s%s%s",vert1,subnet1,vert2,subnet2)==4){
        if (STsearch(g->tab,vert1) == -1) {
    //se il vert1 non e' presente già allora lo aggiungo alla symmbol table
            STinsert(g->tab, vert1, subnet1);
            g->V++;
        }
        if (STsearch(g->tab,vert2) == -1) {
        //stessa cosa per vert2
            STinsert(g->tab, vert2, subnet2);
            g->V++;
        }
        //ignoro la lettura del peso
        fscanf(fin,"%*d");
    }
    //faccio puntare fin di nuovo all'inizio del file
    rewind(fin);
    //ora rileggo il file solo per inserire gli archi nella matrice di adj
    //perciò creo la matrice di adj
    g->madj = MATRIXinit(g->V,g->V,maxWT);
    while ( fscanf(fin,"%s%*s%s%*s%d",vert1,vert2,&wt) == 3 ){
        //trovo gli id numerici dei miei due vertici letti
        id1 = STsearch(g->tab,vert1); id2 = STsearch(g->tab, vert2);
        if (id1 != -1 && id2 != -1) {
            g->E++;//aggiorno il num di archi
            //aggiungo l'arco nella mat di adj
            GRAPHinsertE(g, id1, id2, wt);
        }

    }
    //chiudo il file
    fclose(fin);
    return g;
}

void GRAPHinsertE(Graph g, int id1, int id2, int wt) {
    insertE(g, EDGEcreate(id1, id2, wt));
}

static void  insertE(Graph g, Edge e) {
    int v = e.v, w = e.w, wt = e.wt;
    if (g->madj[v][w] == maxWT)
        g->E++;
    g->madj[v][w] = wt;
    g->madj[w][v] = wt;
}
//salva su un vettore di archi a, tutti gli archi presenti nel grafo
void  GRAPHedges(Graph g, Edge *a) {
    int v, w, E = 0;
    for (v=0; v < g->V; v++)
        for (w=v+1; w < g->V; w++)
            if (g->madj[v][w] != maxWT)
                a[E++] = EDGEcreate(v, w, g->madj[v][w]);

}
//stampa su file le info riguardanti il grafo
void GRAPHstore(Graph g, FILE *fout) {
    int i;
    Edge *a;

    a = malloc(g->E * sizeof(Edge));
    if (a == NULL)
        return;

    GRAPHedges(g, a);

    fprintf(fout, "%d\n", g->V);//numero vertici
    for (i = 0; i < g->V; i++)//stampa i nomi di tutti i vertici
        fprintf(fout, "%s\n", STsearchByIndex(g->tab, i));

    for (i = 0; i < g->E; i++)//stampa le info di tutti gli archi
        fprintf(fout, "%s  %s %d\n", STsearchByIndex(g->tab, a[i].v), STsearchByIndex(g->tab, a[i].w), a[i].wt);

}

int GRAPHgetIndex(Graph G, char *str, char *subnet) {
    int id;
    id = STsearch(G->tab, str);
    if (id == -1) {
        id = STsize(G->tab);
        STinsert(G->tab, str, subnet);
    }
    return id;
}

