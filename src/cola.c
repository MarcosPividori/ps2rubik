
#include "cola.h"
#include <stdlib.h>

struct nod
{
    cubo *pun;
    struct nod *sig;
};

typedef struct nod nodo;

nodo *IniCola=NULL,*FinCola=NULL;

void liberar_nodo(nodo *punt)
{
	if(punt != NULL)
	{
        liberar_cubo(punt->pun);
        free(punt);
	}
}

void add_cola(cubo *a)
{
    nodo *b;
    b=(nodo*) malloc(sizeof(nodo));
    b->pun=a;
    b->sig=NULL;
    if(IniCola==NULL)
        IniCola=b;
    else
        FinCola->sig=b;
    FinCola=b;    
}

cubo* quitar_cola()
{   
    cubo *a;
    nodo *b;
    a=IniCola->pun;
    b=IniCola->sig;
    free(IniCola);
    IniCola=b;
    if(IniCola==NULL)
        FinCola=NULL;
    return a;
}

void vaciar_cola()
{
	nodo *punt;
	while(IniCola!=NULL)
	{
		punt=IniCola->sig;
		liberar_cubo(IniCola->pun);
		free(IniCola);
		IniCola=punt;
	}
    FinCola=NULL;
}

int cola_vacia()
{
    return FinCola==NULL;
}
