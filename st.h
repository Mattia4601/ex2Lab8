#ifndef ASDLAB8_ST_H
#define ASDLAB8_ST_H
#include <stdio.h>

//file header per la symbol table come ADT di 1 classe
typedef struct sym_table *ST;

ST STinit(int maxN);//inizializza la symtable
void STfree(ST st);//distrugge la symtable
int STsize(ST st);//ritorna la dimensione effettiva della symtable
void STinsert(ST st, char *elab, char *sottorete);//inserisce un dato nella symboltable, dove i rappresenterà l'indice di quel dato nella symtable
int STsearch(ST st, char *str);//cerca l'indice della symtable relativo all'emento con nome dato
char *STsearchByIndex(ST st, int index);
char** STgetSortVertexs(ST st);
char* STgetSubnetByIndex(ST st, int index);

#endif //ASDLAB8_ST_H
