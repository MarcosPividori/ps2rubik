
#include "generador.h"
#include <stdlib.h>
#include <time.h>

int desarmar_cubo(cubo *cubo_in)
{    
    int i,j,k;
    
    srand(clock());
    
    j=rand()%1000;
       
    for(i=1;i<j;i++)
    {
        k=rand()%12;
        switch(k)
        {
            case 0 : F(cubo_in);
            case 1 : B(cubo_in);
            case 2 : U(cubo_in);
            case 3 : D(cubo_in);
            case 4 : R(cubo_in);
            case 5 : L(cubo_in);
            case 6 : f(cubo_in);
            case 7 : b(cubo_in);
            case 8 : u(cubo_in);
            case 9 : d(cubo_in);
            case 10: r(cubo_in);
            case 11: l(cubo_in);
        }
        cubo_in->rec[0]=0;
    }
        
    return 0;
}
