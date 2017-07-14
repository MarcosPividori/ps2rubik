//Marcos Pividori
//Este codigo cuenta con el algoritmo principal para resolver el cubo de rubik.
//El que se utiliza en general es el creado por Friedrich,
//En caso de error se utiliza el algoritmo clasico beginner. 

#include <stdio.h>
#include "cubo.h"
#include "rubik_solver.h"
#include "beginner_solver.h"
#include "cubo.h"
#include "cola.h"

int ERROR = 0;

// Utiles.

move_t traducir(move_t move, int giro) {
  switch (giro) {
  case 1:
    return move;
  case 2:
    switch (move) {
    case mov_F:
      return mov_R;
    case mov_f:
      return mov_r;
    case mov_R:
      return mov_B;
    case mov_r:
      return mov_b;
    case mov_B:
      return mov_L;
    case mov_b:
      return mov_l;
    case mov_L:
      return mov_F;
    case mov_l:
      return mov_f;
    default:
      return move;
    }
  case 3:
    switch (move) {
    case mov_F:
      return mov_B;
    case mov_f:
      return mov_b;
    case mov_R:
      return mov_L;
    case mov_r:
      return mov_l;
    case mov_B:
      return mov_F;
    case mov_b:
      return mov_f;
    case mov_L:
      return mov_R;
    case mov_l:
      return mov_r;
    default:
      return move;
    }
  case 4:
    switch (move) {
    case mov_F:
      return mov_L;
    case mov_f:
      return mov_l;
    case mov_R:
      return mov_F;
    case mov_r:
      return mov_f;
    case mov_B:
      return mov_R;
    case mov_b:
      return mov_r;
    case mov_L:
      return mov_B;
    case mov_l:
      return mov_b;
    default:
      return move;
    }
  case 5:
    switch (move) {
    case mov_F:
      return mov_U;
    case mov_f:
      return mov_u;
    case mov_R:
      return mov_R;
    case mov_r:
      return mov_r;
    case mov_B:
      return mov_D;
    case mov_b:
      return mov_d;
    case mov_L:
      return mov_L;
    case mov_l:
      return mov_l;
    case mov_U:
      return mov_B;
    case mov_u:
      return mov_b;
    case mov_D:
      return mov_F;
    case mov_d:
      return mov_f;
    default:
      return move;
    }
  case 6:
    switch (move) {
    case mov_F:
      return mov_D;
    case mov_f:
      return mov_d;
    case mov_R:
      return mov_R;
    case mov_r:
      return mov_r;
    case mov_B:
      return mov_U;
    case mov_b:
      return mov_u;
    case mov_L:
      return mov_L;
    case mov_l:
      return mov_l;
    case mov_U:
      return mov_F;
    case mov_u:
      return mov_f;
    case mov_D:
      return mov_B;
    case mov_d:
      return mov_b;
    default:
      return move;
    }
  }
  return move;
}

move_t traducir2(move_t move, int giro) {
  switch (giro) {
  case 2:
    switch (move) {
    case mov_U:
      return mov_L;
    case mov_u:
      return mov_l;
    case mov_R:
      return mov_U;
    case mov_r:
      return mov_u;
    case mov_D:
      return mov_R;
    case mov_d:
      return mov_r;
    case mov_L:
      return mov_D;
    case mov_l:
      return mov_d;
    default:
      return move;
    }
  case 3:
    switch (move) {
    case mov_U:
      return mov_D;
    case mov_u:
      return mov_d;
    case mov_R:
      return mov_L;
    case mov_r:
      return mov_l;
    case mov_D:
      return mov_U;
    case mov_d:
      return mov_u;
    case mov_L:
      return mov_R;
    case mov_l:
      return mov_r;
    default:
      return move;
    }
  case 4:
    switch (move) {
    case mov_U:
      return mov_R;
    case mov_u:
      return mov_r;
    case mov_R:
      return mov_D;
    case mov_r:
      return mov_d;
    case mov_D:
      return mov_L;
    case mov_d:
      return mov_l;
    case mov_L:
      return mov_U;
    case mov_l:
      return mov_u;
    default:
      return move;
    }
  }
  return move;
}

cubo *rotar(cubo * cubo_in, int i) {
  int **matrix, j, k, s, m, n, cant;
  matrix = cubo_in->num;
  cant = cantidad_pasos(cubo_in);
  if (i <= 4)
    for (j = 1; j <= (i - 1); j++) {
      U(cubo_in);
      d(cubo_in);
      k = matrix[5][1];
      s = matrix[5][2];
      m = matrix[5][3];
      for (n = 1; n < 10; n++)
        matrix[5][n] = matrix[5][n + 3];
      matrix[5][10] = k;
      matrix[5][11] = s;
      matrix[5][12] = m;
    }
  if (i == 5) {
    r(cubo_in);
    L(cubo_in);
    k = matrix[7][5];
    s = matrix[8][5];
    m = matrix[9][5];
    for (n = 9; n > 3; n--)
      matrix[n][5] = matrix[n - 3][5];
    matrix[1][5] = matrix[6][11];
    matrix[2][5] = matrix[5][11];
    matrix[3][5] = matrix[4][11];
    matrix[6][11] = k;
    matrix[5][11] = s;
    matrix[4][11] = m;
  }
  if (i == 6) {
    R(cubo_in);
    l(cubo_in);
    k = matrix[1][5];
    s = matrix[2][5];
    m = matrix[3][5];
    for (n = 1; n < 7; n++)
      matrix[n][5] = matrix[n + 3][5];
    matrix[7][5] = matrix[6][11];
    matrix[8][5] = matrix[5][11];
    matrix[9][5] = matrix[4][11];
    matrix[6][11] = k;
    matrix[5][11] = s;
    matrix[4][11] = m;
  }
  cubo_in->rec[cant] = 0;
  return cubo_in;
}

cubo *rotar2(cubo * cubo_in, int i) {
  int **matrix, j, k, s, m, cant;
  matrix = cubo_in->num;
  cant = cantidad_pasos(cubo_in);
  for (j = 1; j <= (i - 1); j++) {
    b(cubo_in);
    F(cubo_in);
    k = matrix[2][4];
    s = matrix[2][5];
    m = matrix[2][6];
    matrix[2][4] = matrix[6][2];
    matrix[2][5] = matrix[5][2];
    matrix[2][6] = matrix[4][2];
    matrix[6][2] = matrix[8][6];
    matrix[5][2] = matrix[8][5];
    matrix[4][2] = matrix[8][4];
    matrix[8][6] = matrix[4][8];
    matrix[8][5] = matrix[5][8];
    matrix[8][4] = matrix[6][8];
    matrix[4][8] = k;
    matrix[5][8] = s;
    matrix[6][8] = m;
  }
  cubo_in->rec[cant] = 0;
  return cubo_in;
}

cubo *desrotar2(cubo * cubo_in, int i) {
  if (i != 1)
    rotar2(cubo_in, 4 - (i - 2));
  return cubo_in;
}


//Inicio etapas del algoritmo.

int cantidad_primera_segunda(cubo * cubo_in) {
  int cant = 0, **matrix;
  matrix = cubo_in->num;

  if (matrix[5][2] == matrix[4][3] && matrix[5][5] == matrix[4][4])
    if (matrix[4][2] == matrix[5][2] && matrix[2][4] == matrix[2][5])
      cant++;

  if (matrix[5][5] == matrix[4][6] && matrix[5][8] == matrix[4][7])
    if (matrix[5][8] == matrix[4][8] && matrix[2][6] == matrix[2][5])
      cant++;

  if (matrix[5][2] == matrix[6][3] && matrix[5][5] == matrix[6][4])
    if (matrix[5][2] == matrix[6][2] && matrix[8][4] == matrix[8][5])
      cant++;

  if (matrix[5][5] == matrix[6][6] && matrix[5][8] == matrix[6][7])
    if (matrix[8][5] == matrix[8][6] && matrix[6][8] == matrix[5][8])
      cant++;
  return cant;
}

char *list_terminar_primera_segunda[41] = {
  "BuBBUBBuBU", "bRBBrBBRbr", "BuBUbRBr", "bRbrBubU", "RBr", "ubU", "BBRBRRURu",
  "BBubUUruR", "BubUBBuBU", "bRBrBBRbr", "buBBUUruR", "BRBBRRURu", "buBU",
  "BRbr", "RbrBBubU", "uBUBBRBr", "BuBBUbRBr", "bRBBrBubU", "BBRRBBrbRbRR",
  "BBUUBBUBuBUU", "bRbrBRBr", "BuBUbubU", "uBBUBubU", "RBBrbRBr", "uBUBRbr",
  "RbrbuBU", "uBUUruR", "RbRRURu", "RBrbRBr", "ubUBubU", "bRbrBBRbr",
  "BuBUBBuBU", "RRBRRBRRBBRR", "bRBrBubU", "BubUbRBr", "RbruBBU",
  "RRBBrbRbrBBr", "UUBBUBuBUBBU", "RRBBURRuBBrBr", "RbRBDbdRR", "uBublBLUU"
};

cubo *terminar_primera_segunda(cubo * cubo_in) {
  cubo *punt1, *punt2, *punt;
  int flag, i, j, k, cant, cantidad;

  vaciar_cola();
  punt = cubo_in;
  cantidad = cantidad_primera_segunda(punt);
  cant = cantidad_pasos(punt);

  while (cantidad_primera_segunda(punt) != 4) {
    flag = 0;
    for (j = 1; j < 5; j++) {
      punt1 = new_cubo();
      copiar(punt1, punt);
      punt1 = rotar2(punt1, j);

      for (i = 0; i < 41; i++) {
        punt2 = new_cubo();
        copiar(punt2, punt1);
        apply_move_list(punt2, list_terminar_primera_segunda[i]);

        if (cantidad_primera_segunda(punt2) > cantidad) {
          liberar_cubo(punt);
          punt = punt2;
          cantidad = cantidad_primera_segunda(punt);
          vaciar_cola();
          punt = desrotar2(punt, j);
          for (k = cant; punt->rec[k] != 0; k++)
            punt->rec[k] = traducir2(punt->rec[k], j);
          cant = k;
          flag = 1;
          printf("Aumento la cantidad: %d.\n", cantidad);
          break;
        }
        liberar_cubo(punt2);
      }
      liberar_cubo(punt1);
      if (flag == 1)
        break;
    }
    if (flag == 0) {
      for (i = 1; i < 8; i++) {
        punt2 = new_cubo();
        copiar(punt2, punt);
        switch (i) {
        case 1:
          B(punt2);
          break;
        case 2:
          b(punt2);
          break;
        case 3:
          B(punt2);
          B(punt2);
          break;
        case 4:
          R(punt2);
          B(punt2);
          r(punt2);
          break;
        case 5:
          D(punt2);
          B(punt2);
          d(punt2);
          break;
        case 6:
          L(punt2);
          B(punt2);
          l(punt2);
          break;
        case 7:
          U(punt2);
          B(punt2);
          u(punt2);
          break;
        }
        if (cantidad_primera_segunda(punt2) >= cantidad)
          add_cola(punt2);
        else
          liberar_cubo(punt2);
      }

      liberar_cubo(punt);
      punt = quitar_cola();
      cant = cantidad_pasos(punt);
    }
    ERROR++;
    //Esto es por si surge algun imprevisto.
    printf("%d ", ERROR);
    if (ERROR > 50) {
      punt = beginner(cubo_in);
      liberar_cubo(cubo_in);
      printf("ERROR: PROBAREMOS CON EL ALGORITMO BEGINNER.\n");
      return punt;
    }
  }
  return punt;
}


int cantidad_ultimacara(cubo * cubo_in) {
  int **matrix, cant = 0;
  matrix = cubo_in->num;

  if (matrix[5][11] == matrix[4][10])
    cant++;
  if (matrix[5][11] == matrix[4][12])
    cant++;
  if (matrix[5][11] == matrix[6][10])
    cant++;
  if (matrix[5][11] == matrix[6][12])
    cant++;
  if (matrix[5][11] == matrix[5][12])
    cant++;
  if (matrix[5][11] == matrix[4][11])
    cant++;
  if (matrix[5][11] == matrix[6][11])
    cant++;
  if (matrix[5][11] == matrix[5][10])
    cant++;
  return cant;
}


char *list_armar_ultimacara[57] = {
  "RBBRRURuBBrURu", "URBrbuDBLbld", "RldLBBldRdRRL", "lRRDrDLBBlDLr",
  "RBrBrURuBBrURu", "LUrURuulldRdrDDL", "RlDRDrdLrrURu", "lRDRDrdLLrrURul",
  "ldLbrBRbrBRlDL", "RbbrrbRbrbbURu", "UBRbrBRbru", "rbuBuLUlUR",
  "LUrURurURUUl", "ldRdrDRdrDDL", "lDLLulldLLUl", "LullDLLUlldL",
  "URBrbRBrbu", "rubUBubUBR", "LUrURUUl", "ldRdrDDL", "LRRuRurUURuRl",
  "lRRDrDRDDrDrL", "ubULulBLUl", "UBurURbruR", "lDDRDrDL", "LUUruRul",
  "LulbLUluBU", "rURBruRUbu", "LUlRBrbLul", "ruRlbLBrUR", "RbrBBRBDbdbr",
  "lBLBBlbdBDBL", "DLdRDLLDLDDr", "drDldRRdrDDL", "RBrBRbrbrURu",
  "rbRbrBRBRdrD", "LBublBLUl", "rbUBRbruR", "DBLbld", "dbrBRD", "LulbLBUbl",
  "rURBrbuBR", "dRDrbrBR", "RbbrrURuRbbr", "DLBlbd", "rbRBRdrD", "RBRdrDbr",
  "rbRBURdruD", "RBBrbRBrbRbr", "RbbrrbRRbrrbbR", "RRFrBBRfrBBr",
  "ruLURulU", "rulURuLU", "lBRbLBr", "RblBrbL", "ldRDrLbrBR", "rbRBlRdrDL"
};

cubo *armar_ultimacara(cubo * cubo_in) {
  cubo *punt1, *punt2;
  int i, j, cant;

  cant = cantidad_pasos(cubo_in);

  for (j = 1; j < 5; j++) {
    punt1 = new_cubo();
    copiar(punt1, cubo_in);
    punt1 = rotar2(punt1, j);
    for (i = 0; i < 57 && cantidad_ultimacara(punt1) != 8; i++) {
      punt2 = new_cubo();
      copiar(punt2, punt1);

      apply_move_list(punt2, list_armar_ultimacara[i]);

      if (cantidad_ultimacara(punt2) == 8) {
        liberar_cubo(punt1);
        punt1 = punt2;
        break;
      } else
        liberar_cubo(punt2);
    }

    if (cantidad_ultimacara(punt1) == 8) {
      punt1 = desrotar2(punt1, j);
      for (i = cant; punt1->rec[i] != 0; i++)
        punt1->rec[i] = traducir2(punt1->rec[i], j);
      liberar_cubo(cubo_in);
      return punt1;
    }
    liberar_cubo(punt1);
  }
  B(cubo_in);
  ERROR++;
  //Esto es por si surge algun imprevisto.
  if (ERROR > 10) {
    punt1 = beginner(cubo_in);
    liberar_cubo(cubo_in);
    printf("ERROR: PROBAREMOS CON EL ALGORITMO BEGINNER.\n");
    return punt1;
  }
  return armar_ultimacara(cubo_in);
}


int cant_final(cubo * cubo_in) {
  int **matrix, cant = 0, k;
  matrix = cubo_in->num;

  k = matrix[2][5];
  if (matrix[1][4] == k && matrix[1][5] == k && matrix[1][6] == k)
    cant++;
  k = matrix[5][2];
  if (matrix[4][1] == k && matrix[5][1] == k && matrix[6][1] == k)
    cant++;
  k = matrix[5][8];
  if (matrix[4][9] == k && matrix[5][9] == k && matrix[6][9] == k)
    cant++;
  k = matrix[8][5];
  if (matrix[9][4] == k && matrix[9][5] == k && matrix[9][6] == k)
    cant++;

  return cant;
}

char *list_terminar[21] = {
  "rBrbrbrBRBRR", "RRbrbRBRBRbR", "rUrDDRurDDRR", "RRDDRUrDDRuR",
  "BRdrDUrUdrDRUU", "RRllFRRllBBRRllFRRll", "UruLURuLLdRDLdrD",
  "RBrbrURRbrbRBru", "brBRbRRubUBRUruRR", "RbRBUfUFUURUrur",
  "brBBRBBrURBrbruRR", "BRBBrBBRdrbRBRDRR", "rBBRBrBBLbRBl",
  "RBBrbRBBlBrbL", "bdRDrbrBRRBrbrURu", "BlBrBBLbRlBrBBLbR",
  "bRbLBBrBlRbLBBrBl", "BBRbLBBrBludBBDU", "BBlBrBBLbRUDBBdu",
  "BBudBBDURbLBBrBl", "BBUDBBdulBrBBLbR"
};

cubo *terminar(cubo * cubo_in) {
  cubo *punt1, *punt2;
  int i, j, cant;

  cant = cantidad_pasos(cubo_in);
  for (j = 1; j < 5; j++) {
    punt1 = new_cubo();
    copiar(punt1, cubo_in);
    punt1 = rotar2(punt1, j);
    for (i = 0; i < 21 && cant_final(punt1) != 4; i++) {
      punt2 = new_cubo();
      copiar(punt2, punt1);

      apply_move_list(punt2, list_terminar[i]);

      if (cant_final(punt2) == 4) {
        liberar_cubo(punt1);
        punt1 = punt2;
        break;
      } else
        liberar_cubo(punt2);
    }
    if (cant_final(punt1) == 4) {
      punt1 = desrotar2(punt1, j);
      for (i = cant; punt1->rec[i] != 0; i++)
        punt1->rec[i] = traducir2(punt1->rec[i], j);
      liberar_cubo(cubo_in);
      return punt1;
    }
    liberar_cubo(punt1);
  }

  b(cubo_in);

  ERROR++;
  //Esto es por si surge algun imprevisto.
  if (ERROR > 10) {
    punt1 = beginner(cubo_in);
    liberar_cubo(cubo_in);
    printf("ERROR: PROBAREMOS CON EL ALGORITMO BEGINNER.\n");
    return punt1;
  }
  return terminar(cubo_in);
}


//Principal:
// paso -> representa la etapa del algoritmo a realizar. (0 a 5)
// caso -> representa la rotacion del cubo. (1 a 6)

cubo *rubik_solver(cubo * cubo_in, int paso, int caso) {
  int j, k, variacion;
  cubo *cubo_out = NULL;
  move_t *recorrido;

  printf("SOLVER: Inicio etapa: %d  caso:%d.\n", paso, caso);
  switch (paso) {
  case 0:
    cubo_out = new_cubo();
    copiar(cubo_out, cubo_in);
    cubo_out = rotar(cubo_out, caso);
    break;

  case 1:
    cubo_out = armar_cruz(cubo_in);
    break;

  case 2:
    cubo_out = orientar_cruz1(cubo_in);
    cubo_out = orientar_cruz2(cubo_out);
    break;

  case 3:
    ERROR = 0;
    cubo_out = terminar_primera_segunda(cubo_in);
    break;

  case 4:
    ERROR = 0;
    cubo_out = armar_ultimacara(cubo_in);
    break;

  case 5:{
      ERROR = 0;
      cubo_out = terminar(cubo_in);

      j = cantidad_pasos(cubo_out);
      for (k = 0; k < j; k++)
        cubo_out->rec[k] = traducir(cubo_out->rec[k], caso);
      recorrido = cubo_out->rec;
      do {
        variacion = 0;
        recorrido = reducir(recorrido, &variacion);
      } while (variacion == 1);
      cubo_out->rec = recorrido;

      break;
    }
  }
  printf("SOLVER: Fin etapa: %d  caso:%d.\n", paso, caso);
  return cubo_out;
}
