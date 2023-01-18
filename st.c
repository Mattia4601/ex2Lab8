#include "st.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30
struct sym_table{
    char **vNomiElab;//vettore di stringhe che contiene i nomi degli elaboratori
    char **vSottoreti;//vettore di stringhe che contiene i nomi delle sottoreti
    int n;//dimensione effettiva della symtable
    int maxN;//dimensione massima
};

static void mergeArray(char* a[MAX], int p, int q, int r) {
    int i, j, k=0;
    char *b[MAX];
    i = p;
    j = q+1;

    while (i<=q && j<=r) {
        if (strcmp(a[i],a[j])<0) {
            (b[k])=(a[i]);
            i++;
        } else {
            (b[k])=(a[j]);
            j++;
        }
        k++;
    }
    while (i <= q) {
       (b[k])= (a[i]);
        i++;
        k++;
    }
    while (j <= r) {
        (b[k])= (a[j]);
        j++;
        k++;
    }
    for (k=p; k<=r; k++)
        (a[k])= (b[k-p]);
    return;
}


static void mergeSortArray(char** array,int p, int r){
    int q;
    if (p < r) {
        q = (p+r)/2;
        mergeSortArray(array, p, q);
        mergeSortArray(array, q+1, r);
        mergeArray(array, p, q, r);
    }

}

char** STgetSortVertexs(ST st){
    char **v_tmp;
    int i,size;
    size = st->n;
    v_tmp = malloc(size*sizeof(char*));
    if (v_tmp==NULL)
        return NULL;
    for (i=0; i<size; i++){
        v_tmp[i] = malloc(31 * sizeof(char));
    }
    for(i=0;i<size;i++){
        strcpy(v_tmp[i],st->vNomiElab[i]);
    }

    return v_tmp;
}

char* STgetSubnetByIndex(ST st, int index){
    if(index < 0 || index > st->n){
        return NULL;
    }
    return st->vSottoreti[index];
}

ST STinit (int maxN){
    ST st;
    st = malloc(sizeof(*st));
    if(st == NULL){
        printf("Errore allocazione in init symtable\n");
        return NULL;
    }
    st->n=0;st->maxN = maxN;
    st->vNomiElab = calloc(maxN, sizeof(char*));//vettori di stringhe
    st->vSottoreti = calloc(maxN, sizeof(char *));
    if (st->vNomiElab == NULL || st->vSottoreti == NULL){
        printf("Errore allocazione dei vettori contenuti nella symtable\n");
        return NULL;
    }
    return st;
}

void STfree(ST st){
    int i;
    if (st == NULL)
        return;
    for (i=0; i < st->n; i++){
        if (st->vNomiElab[i]!=NULL)
            free(st->vNomiElab[i]);
        if (st->vSottoreti[i]!=NULL)
            free(st->vSottoreti[i]);
    }
    free(st->vSottoreti);
    free(st->vNomiElab);
    free(st);
}

int STsize(ST st){
    return st->n;
}

void STinsert(ST st,char *elab, char *sottorete){
    int j, k;
    if (STsearch(st,elab) == -1) {
        if (st->n == st->maxN) {//ho finito lo spazio devo reallocare
            st->maxN *= 2;//realloco del doppio della dimensione precedente
            st->vNomiElab = realloc(st->vNomiElab, st->maxN * sizeof(char *));
            st->vSottoreti = realloc(st->vSottoreti, st->maxN * sizeof(char *));
        }
        //for che serve per trovare la posizione (j) corretta in cui inserire il nuovo elab
        for (j=0; j<st->n && strcmp(st->vNomiElab[j],elab)<0; j++);
        st->n++;
        //for che serve per scalare tutti gli elab che verranno dopo di quello che sto per inserire in posizione j
        for (k=st->n-1; k>j; k--){
            st->vNomiElab[k] = st->vNomiElab[k-1];
            st->vSottoreti[k] = st->vSottoreti[k-1];
        }
        //inserisco elab e subnet
        st->vNomiElab[j] = strdup(elab);
        st->vSottoreti[j] = strdup(sottorete);
    }
}

int STsearch(ST st, char *str){
    int i;
    for (i=0; i<st->n; i++){
        if (st->vNomiElab[i]!=NULL && strcmp(st->vNomiElab[i],str)==0){
            return i;//ritorno l'indice nella symtable relativo all' elaboratore dato
        }
    }
    return -1;//non trovato
}

char *STsearchByIndex(ST st, int index){
    if (index<0 || index >= st->n){
        return NULL;
    }
    return st->vNomiElab[index];
}