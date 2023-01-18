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
static void sort(Edge *a, int l, int r);
static void merge(Graph g,Edge a[], int p, int q, int r);
static void mergeSort(Graph g,Edge a[], int p, int r);



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


static void merge(Graph g,Edge a[], int p, int q, int r) {
    int i, j, k=0;
    Edge b[MAXC];
    i = p;
    j = q+1;

    while (i<=q && j<=r) {
        if (strcmp(STsearchByIndex(g->tab,a[i].w), STsearchByIndex(g->tab,a[j].w) ) < 0 ) {
            b[k] = a[i];
            i++;
        } else {
            b[k] = a[j];
            j++;
        }
        k++;
    }
    while (i <= q) {
        b[k] = a[i];
        i++;
        k++;
    }
    while (j <= r) {
        b[k] = a[j];
        j++;
        k++;
    }
    for (k=p; k<=r; k++)
        a[k] = b[k-p];

}

static void mergeSort(Graph g,Edge a[], int p, int r) {
    int q;
    if (p < r) {
        q = (p+r)/2;
        mergeSort(g,a, p, q);
        mergeSort(g,a, q+1, r);
        merge(g,a, p, q, r);
    }

}


//crea un vettore di archi di un vertice ordinati per ordine alfabetico
int GRAPHcreaVettArchiOrdinato(Graph g, int indexVertex,Edge *vArchi){
    int count=0,i;//count conteggia il numero di vertici con cui forma archi
    //prima salvo tutti gli archi nel vettore
    for(i=0;i<g->V;i++){//per tutti i vertici del grafo
        if (i == indexVertex)//i è uguale all'indice del vertice preso in considerazione
            continue;
        if (g->madj[indexVertex][i] != maxWT){
            //l'i-esimo vertice ha un arco con il vertice preso in considerazione
            vArchi[count] = EDGEcreate(indexVertex,i,g->madj[indexVertex][i]);
            count++;
        }
    }
    //poi ordino il vettore
    mergeSort(g,vArchi,0,count);
    return count;
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
Graph GRAPHinit(int V){
    Graph g=malloc(sizeof(*g));
    if (g==NULL)
        return NULL;
    g->V = V;
    g->E = 0;
    g->madj = MATRIXinit(V,V, maxWT);
    if (g->madj == NULL)
        return NULL;
    g->tab = STinit(V);//inizializza la tabella di simboli
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
    fin = fopen(filename,"r");
    if (fin == NULL)
        return NULL;
    //non so il num di vertici, leggo una prima volta il file per vedere quante righe ho
    while (fgets(buff,maxWT,fin)!=NULL){
        c++;
    }
    //il numero di vertici sarà al massimo il doppio di c
    g = GRAPHinit(2*c);
    fclose(fin);
    fin = fopen(filename,"r");//riapro in lettura il file
    if (fin == NULL)
        return NULL;

    while ( fscanf(fin,"%s%s%s%s%d",vert1,subnet1,vert2,subnet2,&wt) == 5 ){
        STinsert(g->tab,vert1,subnet1);
        STinsert(g->tab,vert2,subnet2);
        g->E++;//aggiorno il num di archi
        id1 = STsearch(g->tab,vert1); id2 = STsearch(g->tab, vert2);
        if (id1 != -1 && id2 != -1) {
            GRAPHinsertE(g, id1, id2, wt);//aggiungo l'arco nella mat di adj
        }

    }

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
//ordina il vettore di archi in base al peso
static void sort(Edge *a, int l, int r ) {
    int i, j, min, temp;
    for(i = l; i < r; i++) {
        min = i;
        for (j = i+1; j <= r; j++)
            if (a[j].wt < a[min].wt)
                min = j;

        temp = a[i].v;
        a[i].v = a[min].v;
        a[min].v = temp;

        temp = a[i].w;
        a[i].w = a[min].w;
        a[min].w = temp;

        temp = a[i].wt;
        a[i].wt = a[min].wt;
        a[min].wt = temp;
    }
    return;
}

