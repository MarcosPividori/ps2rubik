#ifndef __BEGINNER_SOLVER__
#define __BEGINNER_SOLVER__

#include "cubo.h"

move_t* reducir(move_t* lista,int* var_out);

cubo* armar_cruz(cubo *cubo_in);

cubo* orientar_cruz1(cubo *cubo_in);

cubo* orientar_cruz2(cubo *cubo_in);

cubo* beginner(cubo *cubo_in);

cubo *beginner_solver(cubo *cubo_in,int paso);

#endif //__BEGINNER_SOLVER__
