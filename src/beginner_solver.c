// Algoritmo beginner.

#include <stdio.h>
#include "cubo.h"
#include "beginner_solver.h"
#include "cubo.h"
#include "cola.h"

#define LOOP_LIMIT 50

int cantidad(cubo *cubo_in)
{
    int cant=0,k,**matriz;
    matriz= cubo_in->num;
    
    k=matriz[5][5];    
    if(matriz[5][4]==k)
        cant++;
    if(matriz[5][6]==k)
        cant++;
    if(matriz[4][5]==k)
        cant++;
    if(matriz[6][5]==k)
        cant++;
    return cant;
}

cubo* armar_cruz(cubo *cubo_in)
{
    int cant1,i,flag;
    cubo *punt1,*punt2;
    int loop_c=0;
    
    cant1=cantidad(cubo_in);
    punt1=cubo_in;
    vaciar_cola();
    
    while(cant1<4) 
    {
        flag=0;
        for(i=1;i<19;i++)
        {
            punt2= new_cubo();
            copiar(punt2,punt1);
            switch(i)
            {
                case 1  : F(punt2);break;
                case 2  : B(punt2);break;
                case 3  : U(punt2);break;
                case 4  : D(punt2);break;
                case 5  : R(punt2);break;
                case 6  : L(punt2);break;
                case 7  : f(punt2);break;
                case 8  : b(punt2);break;
                case 9  : u(punt2);break;
                case 10 : d(punt2);break;
                case 11 : r(punt2);break;
                case 12 : l(punt2);break;
                case 13 : F(punt2);F(punt2);break;
                case 14 : B(punt2);B(punt2);break;
                case 15 : U(punt2);U(punt2);break;
                case 16 : D(punt2);D(punt2);break;
                case 17 : R(punt2);R(punt2);break;
                case 18 : L(punt2);L(punt2);break; 
            }
            if(cantidad(punt2) >= cant1)    
            {	
                add_cola(punt2);
                if(cantidad(punt2) > cant1)
                {   
                    liberar_cubo(punt1);
                    punt1= new_cubo();
                    copiar(punt1,punt2);
                    cant1=cantidad(punt1); 
                    vaciar_cola();
                    flag=1;
                    break;
                }
            }
            else
                liberar_cubo(punt2);
        }
        if(flag==1) continue;
        for(i=1;i<9;i++)
        {
            punt2= new_cubo();
            copiar(punt2,punt1);
            switch(i)
            {
                case 1 : U(punt2);F(punt2);r(punt2);break;
                case 2 : u(punt2);f(punt2);L(punt2);break;
                case 3 : L(punt2);F(punt2);u(punt2);break;
                case 4 : l(punt2);f(punt2);D(punt2);break;
                case 5 : D(punt2);F(punt2);l(punt2);break;
                case 6 : d(punt2);f(punt2);R(punt2);break;
                case 7 : R(punt2);F(punt2);d(punt2);break;
                case 8 : r(punt2);f(punt2);U(punt2);break; 
            }
            if(cantidad(punt2) > cant1)    
            {	
                liberar_cubo(punt1);
                punt1=punt2;
                cant1=cantidad(punt1); 
                vaciar_cola();
                flag=1;
                break;
            }
            else
                liberar_cubo(punt2);
        }
        
        if(flag==0)
        {       
            liberar_cubo(punt1);
            punt1=quitar_cola();
        }

        loop_c++;
        //Esto es por si surge algun imprevisto.
        if(loop_c>LOOP_LIMIT) {
            printf("ERROR: EL ALGORITMO NO PUDO ENCONTRAR SOLUCION.\n");
            vaciar_cola();
            return punt1;
        }
    }
    
    return punt1;   
}

int cantidad_cruz_correcta(cubo *cubo_in)
{
    int cant=0,**matriz;
    matriz=cubo_in->num;
    if(matriz[5][2]==matriz[5][3])
        cant++;
    if(matriz[5][7]==matriz[5][8])
        cant++;
    if(matriz[3][5]==matriz[2][5])
        cant++;
    if(matriz[7][5]==matriz[8][5])
        cant++;
    return cant;       
}

cubo* orientar_cruz1(cubo *cubo_in)
{
    cubo *punt1;
    if(cantidad_cruz_correcta(cubo_in) >= 2)
        return cubo_in;
    else
    {
        punt1= new_cubo();
        copiar(punt1,cubo_in);
        F(punt1);
        if(2 <= cantidad_cruz_correcta(punt1)) {
            liberar_cubo(cubo_in);
            return punt1;
        }
        liberar_cubo(punt1);

        punt1= new_cubo();
        copiar(punt1,cubo_in);
        f(punt1);
        if(2 <= cantidad_cruz_correcta(punt1)){
            liberar_cubo(cubo_in);
            return punt1;
        }
        liberar_cubo(punt1);
        
        punt1= new_cubo();
        copiar(punt1,cubo_in);
        F(punt1);
        F(punt1);
        liberar_cubo(cubo_in);
        return punt1;        
    }         
}

char *list_orientar_cruz2[6] = {
    "RRBUUbRR"
  , "DDBRRbDD"
  , "LLBDDbLL"
  , "UUBLLbUU"
  , "RRBBLLbbRR"
  , "DDBBUUbbDD"            
  };

cubo* orientar_cruz2(cubo *cubo_in)
{
    int i;
    cubo *punt1;
    if(cantidad_cruz_correcta(cubo_in)!=4)
        for(i=0;i<6;i++)
        {
            punt1= new_cubo();
            copiar(punt1,cubo_in);
            apply_move_list(punt1,list_orientar_cruz2[i]);
            if(cantidad_cruz_correcta(punt1)==4){
                liberar_cubo(cubo_in);
                return punt1;
            }
            liberar_cubo(punt1);
        }
    return cubo_in;
}


int cantidad_esq_orientadas(cubo *cubo_in)
{
    int cant=0,**matriz;
    matriz=cubo_in->num;
  
    if(matriz[5][2]==matriz[4][3] && matriz[5][5]==matriz[4][4])
        cant++;
    if(matriz[5][5]==matriz[4][6] && matriz[5][8]==matriz[4][7])
        cant++;
    if(matriz[5][2]==matriz[6][3] && matriz[5][5]==matriz[6][4])
        cant++;
    if(matriz[5][5]==matriz[6][6] && matriz[5][8]==matriz[6][7])
        cant++;
    return cant;
}

cubo* orientar_esquina(cubo *cubo_in)
{
    cubo *punt1,*punt2;
    int i,cant,cant1;
    int loop_c=0;

    vaciar_cola();
    
    punt1=cubo_in;
    cant1=cantidad_esq_orientadas(punt1);
    
    while(cantidad_esq_orientadas(punt1) != 4) 
    {
        for(i=1;i<16;i++)
        {
            punt2= new_cubo();
            copiar(punt2,punt1);
            switch(i)
            {
                case 1  : B(punt2);break;
                case 2  : b(punt2);break;
                case 3  : B(punt2);B(punt2);break;
                case 4  : R(punt2);b(punt2);r(punt2);break;
                case 5  : D(punt2);b(punt2);d(punt2);break;
                case 6  : L(punt2);b(punt2);l(punt2);break;
                case 7  : U(punt2);b(punt2);u(punt2);break;
                case 8  : U(punt2);B(punt2);u(punt2);break;
                case 9  : R(punt2);B(punt2);r(punt2);break;
                case 10 : D(punt2);B(punt2);d(punt2);break;
                case 11 : L(punt2);B(punt2);l(punt2);break;
                case 12 : l(punt2);b(punt2);L(punt2);break;
                case 13 : u(punt2);b(punt2);U(punt2);break;
                case 14 : r(punt2);b(punt2);R(punt2);break;
                case 15 : d(punt2);b(punt2);D(punt2);break;
            }
            cant=cantidad_esq_orientadas(punt2);    
            if(cant>=cant1)
            {    
                add_cola(punt2);
                if(cant>cant1)
                {
                    cant1=cant;
                    copiar(punt1,punt2);
                    vaciar_cola();
                    break;
                }
            }
            else
                liberar_cubo(punt2);
        }
        if(cola_vacia())
            continue;
        else
        {
            liberar_cubo(punt1);
            punt1=quitar_cola();
        }
        
        loop_c++;
        //Esto es por si surge algun imprevisto.
        if(loop_c>LOOP_LIMIT) {
            printf("ERROR: EL ALGORITMO NO PUDO ENCONTRAR SOLUCION.\n");
            vaciar_cola();
            return punt1;
        }
    }
  
    return punt1;
}


int cantidad_medios(cubo *cubo_in)
{
    int **matriz,cant=0;
    matriz = cubo_in->num;
    
    if(matriz[4][2]==matriz[5][2] && matriz[2][4]==matriz[2][5])
        cant++;
    if(matriz[5][2]==matriz[6][2] && matriz[8][4]==matriz[8][5])
        cant++;
    if(matriz[8][5]==matriz[8][6] && matriz[6][8]==matriz[5][8])
        cant++;
    if(matriz[5][8]==matriz[4][8] && matriz[2][6]==matriz[2][5])
        cant++;
    return cant;
}

char *list_terminar_segundalinea[9] = {
    "RbrbuBU" 
  , "UbublBL"
  , "LblbdBD"
  , "DbdbrBR"
  , "uBUBRbr"
  , "rBRBDbd"
  , "dBDBLbl"
  , "lBLBUbu"
  , "uBUBRbr"
  };

cubo* terminar_segundalinea(cubo *cubo_in)
{
    cubo *punt1,*punt2;
    int i,flag,cant,cant1;
    int loop_c=0;
    
    vaciar_cola();
    
    punt1=cubo_in;
    cant1=cantidad_medios(punt1);
    
    while(cantidad_medios(punt1) != 4) 
    {
        punt2= new_cubo();
        copiar(punt2,punt1);
        B(punt2);
        add_cola(punt2);
            
        punt2= new_cubo();
        copiar(punt2,punt1);
        B(punt2);B(punt2);
        add_cola(punt2);
        
        punt2= new_cubo();
        copiar(punt2,punt1);
        b(punt2);
        add_cola(punt2);

        flag=0;
        
        for(i=0;i<9;i++)
        {
            punt2= new_cubo();
            copiar(punt2,punt1);
            apply_move_list(punt2,list_terminar_segundalinea[i]);
            cant=cantidad_medios(punt2);
            if(cant>cant1)
            {
                cant1=cant;
                liberar_cubo(punt1);
                punt1=punt2;
                vaciar_cola();
                flag = 1;
                break;
            }        
            else
                if(cant==cant1)
                    add_cola(punt2);
                else
                    liberar_cubo(punt2);
        }

        if(flag == 0){
            liberar_cubo(punt1);
            punt1=quitar_cola();    
        }
        
        loop_c++;
        //Esto es por si surge algun imprevisto.
        if(loop_c>LOOP_LIMIT) {
            printf("ERROR: EL ALGORITMO NO PUDO ENCONTRAR SOLUCION.\n");
            vaciar_cola();
            return punt1;
        }
    }
    return punt1;
}

int cantidad_cruz2(cubo *cubo_in)
{
    int **matriz,cant=0;
    matriz = cubo_in->num;
    
    if(matriz[5][11]==matriz[5][10])
        cant++;
    if(matriz[5][11]==matriz[5][12])
        cant++;
    if(matriz[5][11]==matriz[4][11])
        cant++;
    if(matriz[5][11]==matriz[6][11])
        cant++;
    return cant;
}

char *list_armar_segundacruz[4]= {
    "rbuBUR"
  , "dbrBRD"
  , "lbdBDL"
  , "ublBLU"
  };

cubo* armar_segundacruz(cubo *cubo_in)
{
    cubo *punt1,*punt2;
    int i,cant,cant1;
    int loop_c=0;
    
    vaciar_cola();
    
    punt1=cubo_in;
    cant1=cantidad_cruz2(punt1);
    
    while(cantidad_cruz2(punt1) != 4) 
    {
        for(i=0;i<4;i++)
        {
            punt2= new_cubo();
            copiar(punt2,punt1);
            apply_move_list(punt2,list_armar_segundacruz[i]);
            cant=cantidad_cruz2(punt2);
            if(cant>=cant1)
            {
                add_cola(punt2);
                if(cant>cant1)
                {
                    cant1=cant;
                    copiar(punt1,punt2);
                    vaciar_cola();
                    break;
                } 
            }
            else
                liberar_cubo(punt2);
        }
        
        if(cola_vacia())
            continue;
        else
        {
            liberar_cubo(punt1);
            punt1=quitar_cola();
        }
        
        loop_c++;
        //Esto es por si surge algun imprevisto.
        if(loop_c>LOOP_LIMIT) {
            printf("ERROR: EL ALGORITMO NO PUDO ENCONTRAR SOLUCION.\n");
            vaciar_cola();
            return punt1;
        }
    }
    
    return punt1;
}

int cantidad_esquinasultimacara(cubo *cubo_in)
{
    int **matriz,cant=0;
    matriz = cubo_in->num;
    
    if(matriz[5][11]==matriz[4][10])
        cant++;
    if(matriz[5][11]==matriz[4][12])
        cant++;
    if(matriz[5][11]==matriz[6][10])
        cant++;
    if(matriz[5][11]==matriz[6][12])
        cant++;
    return cant;
}

char *list_armar_ultimacara2[8]=
  { "RBrBRBBr"
  , "DBdBDBBd"
  , "LBlBLBBl"
  , "UBuBUBBu"
  , "lbLblbbL"
  , "ubUbubbU"
  , "rbRbrbbR"
  , "dbDbdbbD"
  };

cubo* armar_ultimacara2(cubo *cubo_in)
{
    cubo *punt1,*punt2;
    int i,cant1;
    int loop_c=0;
    
    vaciar_cola();
    
    punt1=cubo_in;
    cant1=cantidad_esquinasultimacara(punt1);
    
    while(cantidad_esquinasultimacara(punt1) != 4) 
    {
        for(i=0;i<8;i++)
        {
            punt2= new_cubo();
            copiar(punt2,punt1);
            apply_move_list(punt2,list_armar_ultimacara2[i]);
            if(cantidad_esquinasultimacara(punt2)==4)
            {
                vaciar_cola();
                liberar_cubo(punt1);
                punt1=punt2;
                break;
            }
            else
                add_cola(punt2);
        }
        if(cantidad_esquinasultimacara(punt1)==4)
            break;
        liberar_cubo(punt1);
        punt1=quitar_cola(); 
        
        loop_c++;
        //Esto es por si surge algun imprevisto.
        if(loop_c>LOOP_LIMIT) {
            printf("ERROR: EL ALGORITMO NO PUDO ENCONTRAR SOLUCION.\n");
            vaciar_cola();
            return punt1;
        }
    }
    return punt1;    
}
       
int cantidad_esquinasfinal(cubo *cubo_in)
{
    int **matriz,cant=0;
    matriz = cubo_in->num;
    
    if(matriz[2][5]==matriz[1][6] && matriz[4][9]==matriz[5][8])
        cant++;
    if(matriz[2][5]==matriz[1][4] && matriz[4][1]==matriz[5][2])
        cant++;
    if(matriz[8][5]==matriz[9][4] && matriz[6][1]==matriz[5][2])
        cant++;
    if(matriz[8][5]==matriz[9][6] && matriz[6][9]==matriz[5][8])
        cant++;
    return cant;
}

char *list_armar_ultimasesquinas[11]=
  { "B" 
  , "b"
  , "B"
  , "rUrDDRurDDRR"
  , "dRdLLDrdLLDD"
  , "lDlUULdlUULL"
  , "uLuRRUluRRUU"
  , "UrUlluRUlluu"
  , "RdRuurDRuurr"
  , "DlDrrdLDrrdd"
  , "LuLddlULddll"
  };

cubo* armar_ultimasesquinas(cubo *cubo_in)
{
    cubo *punt1,*punt2;
    int i,cant1;
    int loop_c=0;
    
    vaciar_cola();
    
    punt1=cubo_in;
    cant1=cantidad_esquinasfinal(punt1);
    
    while(cantidad_esquinasfinal(punt1) != 4) 
    {
        for(i=0;i<11;i++)
        {
            punt2= new_cubo();
            copiar(punt2,punt1);
            apply_move_list(punt2,list_armar_ultimasesquinas[i]); 
            if(cantidad_esquinasfinal(punt2)==4)
            {
                vaciar_cola();
                liberar_cubo(punt1);
                punt1=punt2;
                break;
            }
            else
                add_cola(punt2);
        }
        if(cantidad_esquinasfinal(punt1)==4)
            break;
        liberar_cubo(punt1);
        punt1=quitar_cola(); 
        
        loop_c++;
        //Esto es por si surge algun imprevisto.
        if(loop_c>LOOP_LIMIT) {
            printf("ERROR: EL ALGORITMO NO PUDO ENCONTRAR SOLUCION.\n");
            vaciar_cola();
            return punt1;
        }
    }
    return punt1;    
}    

int cantidad_final(cubo *cubo_in)
{
    int **matriz,cant=0;
    matriz = cubo_in->num;
    
    if(matriz[1][5]==matriz[2][5])
        cant++;
    if(matriz[5][1]==matriz[5][2])
        cant++;
    if(matriz[5][8]==matriz[5][9])
        cant++;
    if(matriz[8][5]==matriz[9][5])
        cant++;
    return cant;
}

char *list_terminar_de_unavez[8]=
  { "RBrBRBBrubUbubbU"
  , "DBdBDBBdrbRbrbbR"
  , "LBlBLBBldbDbdbbD"
  , "UBuBUBBulbLblbbL"
  , "lbLblbbLUBuBUBBu"
  , "ubUbubbURBrBRBBr"
  , "rbRbrbbRDBdBDBBd"
  , "dbDbdbbDLBlBLBBl"
  };

cubo* terminar_de_unavez(cubo *cubo_in)
{
    cubo *punt1,*punt2;
    int i,cant,cant1;
    int loop_c=0;
    
    punt1=cubo_in;
    cant1=cantidad_final(punt1);
    
    while(cantidad_final(punt1) != 4) 
    {
        for(i=0;i<8;i++)
        {
            punt2= new_cubo();
            copiar(punt2,punt1);
            apply_move_list(punt2,list_terminar_de_unavez[i]);
            cant=cantidad_final(punt2);
            if(cant>cant1) {
                liberar_cubo(punt1);
                punt1=punt2;
                cant1=cant;
                break;
            }
            else
                liberar_cubo(punt2);
        }
        
        loop_c++;
        //Esto es por si surge algun imprevisto.
        if(loop_c>LOOP_LIMIT) {
            printf("ERROR: EL ALGORITMO NO PUDO ENCONTRAR SOLUCION.\n");
            vaciar_cola();
            return punt1;
        }
    }
    return punt1;              
}


move_t* reducir(move_t* lista,int* variacion_out)
{
    move_t *rec;
    int cant,i,j;
     
    rec= (move_t*) malloc(MAXPASOS*sizeof(move_t));   
    for(cant=0;lista[cant] != 0;cant++)
        ;
        
    if(cant==1 || cant==0) {
        free(rec);
        return lista;
    }
    
    for(i=0,j=0;i<cant;j++)
    {
		if( (i+2) < cant) {
			if(lista[i] == lista[i+1] && lista[i+1] == lista[i+2]) {
			    rec[j] = opposite_move(lista[i]);
				*variacion_out=1;
                i=i+3;
			}
            else {
			     rec[j] = lista[i];	
			     i++;
		    }
        }
		else {
		     rec[j] = lista[i];	
		     i++;
		}
	}
	cant=j;
	
	for(j=0,i=0;j<cant;)
	{
		if(rec[j] == opposite_move(rec[j+1])) {
            j=j+2;
            *variacion_out=1;
        }
		else {
            rec[i]=rec[j];
            j++;
            i++;
        }
	}
	cant=i;
	rec[cant]=0;
	free(lista);	
	return rec;
}

cubo *beginner_solver(cubo *cubo_in,int paso)
{
    int variacion;
    cubo *Solucion=cubo_in;
	move_t *recorrido;  
    
    printf("BEGINNER: Inicio etapa %d.\n",paso);
    switch(paso){
        case 0:      
            Solucion=new_cubo();
            copiar(Solucion,cubo_in);
            break;

        case 1:
            Solucion=armar_cruz(Solucion);
            break;

        case 2:
            Solucion=orientar_cruz1(Solucion);
            break;

        case 3:
            Solucion=orientar_cruz2(Solucion);
            break;

        case 4:
            Solucion=orientar_esquina(Solucion);
            break;

        case 5:
            Solucion=terminar_segundalinea(Solucion);
            break;

        case 6:
            Solucion=armar_segundacruz(Solucion);
            break;

        case 7:
            Solucion=armar_ultimacara2(Solucion);
            break;

        case 8:
            Solucion=armar_ultimasesquinas(Solucion);
            break;

        case 9:
            Solucion = terminar_de_unavez(Solucion);
			recorrido = Solucion->rec;
			do{
				variacion=0;
				recorrido=reducir(recorrido,&variacion);		
			} while(variacion==1);
			Solucion->rec=recorrido;
            break;
    }
    printf("BEGINNER: Fin etapa %d.\n",paso);
    return Solucion;
}

cubo* beginner(cubo *cubo_in)
{
    cubo *Solucion=cubo_in;
    int i;

    for(i=0;i<10;i++)
        Solucion=beginner_solver(Solucion,i);
		
    return Solucion;
}

