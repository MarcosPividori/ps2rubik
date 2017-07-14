
#include<stdio.h>
#include<stdlib.h>
#include "cubo.h"

cubo *new_cubo() {
  cubo *punt;
  int **punt1, i;
  move_t *punt2;

  punt = (cubo *) malloc(sizeof(cubo));
  punt1 = (int **) malloc(10 * sizeof(int *));

  if (punt <= 0 || punt1 <= 0)
    return NULL;

  for (i = 0; i < 10; i++) {
    punt1[i] = (int *) malloc(13 * sizeof(int));
    if (punt1[i] <= 0)
      return NULL;
  }

  punt2 = (move_t *) malloc(MAXPASOS * sizeof(move_t));

  if (punt2 <= 0)
    return NULL;

  punt2[0] = 0;

  punt->num = punt1;
  punt->rec = punt2;
  return punt;
}

void liberar_cubo(cubo * punt) {
  int i;
  if (punt != NULL) {
    free(punt->rec);
    for (i = 0; i < 10; i++)
      free(punt->num[i]);
    free(punt->num);
    free(punt);
  }
}

void copiar(cubo * a, cubo * b) {
  int i, j;
  for (i = 1; i < 10; i++)
    for (j = 1; j < 13; j++)
      a->num[i][j] = b->num[i][j];
  for (i = 0; i < MAXPASOS && b->rec[i] != 0; i++)
    a->rec[i] = b->rec[i];
  a->rec[i] = 0;
}

void mostrar(cubo * Cub) {
  int i, j, **Cubo;
  char c = 0;
  Cubo = Cub->num;

  for (i = 1; i < 10; i++) {
    for (j = 1; j < 13; j++) {
      printf("%d ", Cubo[i][j]);
      if (j == 12)
        printf("\n");
    }
  }
  printf("\n");
  for (i = 0; i < MAXPASOS && Cub->rec[i] != 0; i++) {
    switch (Cub->rec[i]) {
    case mov_F:
      c = 'F';
      break;
    case mov_B:
      c = 'B';
      break;
    case mov_R:
      c = 'R';
      break;
    case mov_L:
      c = 'L';
      break;
    case mov_U:
      c = 'U';
      break;
    case mov_D:
      c = 'D';
      break;
    case mov_f:
      c = 'f';
      break;
    case mov_b:
      c = 'b';
      break;
    case mov_r:
      c = 'r';
      break;
    case mov_l:
      c = 'l';
      break;
    case mov_u:
      c = 'u';
      break;
    case mov_d:
      c = 'd';
      break;
    case mov_none:
      c = 0;
      break;
    }
    printf("%c ", c);
  }
  printf("\n");
}

int cantidad_pasos(cubo * Cub) {
  int cant;
  for (cant = 0; Cub->rec[cant] != 0; cant++);
  return cant;
}

void marcar(cubo * Cub, move_t move) {
  int k;
  for (k = 0; k < MAXPASOS && Cub->rec[k] != 0; k++);
  if (k < (MAXPASOS - 1)) {
    Cub->rec[k] = move;
    Cub->rec[k + 1] = 0;
  }
}

void desmarcar(cubo * Cub, move_t move) {
  int k;
  for (k = 0; k < MAXPASOS && Cub->rec[k] != 0; k++);
  k = k - 3;
  Cub->rec[k] = move;
  Cub->rec[k + 1] = 0;
}

void girar_der(cubo * Cub, int i, int j) {
  int k, **Cubo;
  Cubo = Cub->num;

  k = Cubo[i][j];
  Cubo[i][j] = Cubo[i + 2][j];
  Cubo[i + 2][j] = Cubo[i + 2][j + 2];
  Cubo[i + 2][j + 2] = Cubo[i][j + 2];
  Cubo[i][j + 2] = k;
  k = Cubo[i][j + 1];
  Cubo[i][j + 1] = Cubo[i + 1][j];
  Cubo[i + 1][j] = Cubo[i + 2][j + 1];
  Cubo[i + 2][j + 1] = Cubo[i + 1][j + 2];
  Cubo[i + 1][j + 2] = k;
}


void F(cubo * Cub) {
  int k, **Cubo;
  Cubo = Cub->num;

  girar_der(Cub, 4, 4);
  k = Cubo[4][7];
  Cubo[4][7] = Cubo[3][4];
  Cubo[3][4] = Cubo[6][3];
  Cubo[6][3] = Cubo[7][6];
  Cubo[7][6] = k;
  k = Cubo[5][7];
  Cubo[5][7] = Cubo[3][5];
  Cubo[3][5] = Cubo[5][3];
  Cubo[5][3] = Cubo[7][5];
  Cubo[7][5] = k;
  k = Cubo[6][7];
  Cubo[6][7] = Cubo[3][6];
  Cubo[3][6] = Cubo[4][3];
  Cubo[4][3] = Cubo[7][4];
  Cubo[7][4] = k;

  marcar(Cub, mov_F);
}

void B(cubo * Cub) {
  int k, **Cubo;
  Cubo = Cub->num;

  girar_der(Cub, 4, 10);
  k = Cubo[4][9];
  Cubo[4][9] = Cubo[9][6];
  Cubo[9][6] = Cubo[6][1];
  Cubo[6][1] = Cubo[1][4];
  Cubo[1][4] = k;
  k = Cubo[5][9];
  Cubo[5][9] = Cubo[9][5];
  Cubo[9][5] = Cubo[5][1];
  Cubo[5][1] = Cubo[1][5];
  Cubo[1][5] = k;
  k = Cubo[6][9];
  Cubo[6][9] = Cubo[9][4];
  Cubo[9][4] = Cubo[4][1];
  Cubo[4][1] = Cubo[1][6];
  Cubo[1][6] = k;

  marcar(Cub, mov_B);
}

void R(cubo * Cub) {
  int k, l, m, n, **Cubo;
  Cubo = Cub->num;

  girar_der(Cub, 4, 7);
  k = Cubo[4][10];
  l = Cubo[5][10];
  m = Cubo[6][10];
  Cubo[4][10] = Cubo[3][6];
  Cubo[5][10] = Cubo[2][6];
  Cubo[6][10] = Cubo[1][6];
  for (n = 1; n < 7; n++)
    Cubo[n][6] = Cubo[n + 3][6];
  Cubo[7][6] = m;
  Cubo[8][6] = l;
  Cubo[9][6] = k;

  marcar(Cub, mov_R);
}

void L(cubo * Cub) {
  int k, l, m, n, **Cubo;
  Cubo = Cub->num;

  girar_der(Cub, 4, 1);
  k = Cubo[4][12];
  l = Cubo[5][12];
  m = Cubo[6][12];
  Cubo[4][12] = Cubo[9][4];
  Cubo[5][12] = Cubo[8][4];
  Cubo[6][12] = Cubo[7][4];
  for (n = 9; n > 3; n--)
    Cubo[n][4] = Cubo[n - 3][4];
  Cubo[3][4] = k;
  Cubo[2][4] = l;
  Cubo[1][4] = m;

  marcar(Cub, mov_L);
}


void U(cubo * Cub) {
  int k, l, m, n, **Cubo;
  Cubo = Cub->num;

  girar_der(Cub, 1, 4);
  k = Cubo[4][1];
  l = Cubo[4][2];
  m = Cubo[4][3];
  for (n = 1; n < 10; n++)
    Cubo[4][n] = Cubo[4][n + 3];
  Cubo[4][10] = k;
  Cubo[4][11] = l;
  Cubo[4][12] = m;

  marcar(Cub, mov_U);
}

void D(cubo * Cub) {
  int k, l, m, n, **Cubo;
  Cubo = Cub->num;

  girar_der(Cub, 7, 4);
  k = Cubo[6][10];
  l = Cubo[6][11];
  m = Cubo[6][12];
  for (n = 12; n > 3; n--)
    Cubo[6][n] = Cubo[6][n - 3];
  Cubo[6][1] = k;
  Cubo[6][2] = l;
  Cubo[6][3] = m;

  marcar(Cub, mov_D);
}

void f(cubo * Cub) {
  F(Cub);
  F(Cub);
  F(Cub);
  desmarcar(Cub, mov_f);
}
void b(cubo * Cub) {
  B(Cub);
  B(Cub);
  B(Cub);
  desmarcar(Cub, mov_b);
}
void r(cubo * Cub) {
  R(Cub);
  R(Cub);
  R(Cub);
  desmarcar(Cub, mov_r);
}
void l(cubo * Cub) {
  L(Cub);
  L(Cub);
  L(Cub);
  desmarcar(Cub, mov_l);
}
void u(cubo * Cub) {
  U(Cub);
  U(Cub);
  U(Cub);
  desmarcar(Cub, mov_u);
}
void d(cubo * Cub) {
  D(Cub);
  D(Cub);
  D(Cub);
  desmarcar(Cub, mov_d);
}

move_t opposite_move(move_t mov) {
  switch (mov) {
  case mov_F:
    return mov_f;
  case mov_B:
    return mov_b;
  case mov_R:
    return mov_r;
  case mov_L:
    return mov_l;
  case mov_U:
    return mov_u;
  case mov_D:
    return mov_d;
  case mov_f:
    return mov_F;
  case mov_b:
    return mov_B;
  case mov_r:
    return mov_R;
  case mov_l:
    return mov_L;
  case mov_u:
    return mov_U;
  case mov_d:
    return mov_D;
  case mov_none:
    return mov_none;
  }
  return mov;
}

void apply_move(cubo * Cub, move_t mov) {
  switch (mov) {
  case mov_F:
    return F(Cub);
  case mov_B:
    return B(Cub);
  case mov_R:
    return R(Cub);
  case mov_L:
    return L(Cub);
  case mov_U:
    return U(Cub);
  case mov_D:
    return D(Cub);
  case mov_f:
    return f(Cub);
  case mov_b:
    return b(Cub);
  case mov_r:
    return r(Cub);
  case mov_l:
    return l(Cub);
  case mov_u:
    return u(Cub);
  case mov_d:
    return d(Cub);
  case mov_none:
    return;
  }
}

void apply_move_list(cubo * cub, char *moves) {
  int i;
  for (i = 0; moves[i] != 0; i++) {
    switch (moves[i]) {
    case 'F':
      apply_move(cub, mov_F);
      break;
    case 'B':
      apply_move(cub, mov_B);
      break;
    case 'R':
      apply_move(cub, mov_R);
      break;
    case 'L':
      apply_move(cub, mov_L);
      break;
    case 'U':
      apply_move(cub, mov_U);
      break;
    case 'D':
      apply_move(cub, mov_D);
      break;
    case 'f':
      apply_move(cub, mov_f);
      break;
    case 'b':
      apply_move(cub, mov_b);
      break;
    case 'r':
      apply_move(cub, mov_r);
      break;
    case 'l':
      apply_move(cub, mov_l);
      break;
    case 'u':
      apply_move(cub, mov_u);
      break;
    case 'd':
      apply_move(cub, mov_d);
      break;
    }
  }
}
