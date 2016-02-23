#ifndef __CUBO__
#define __CUBO__

#define MAXPASOS 200

typedef enum {
    mov_none = 0,
    mov_F,
    mov_B,
    mov_R,
    mov_L,
    mov_U,
    mov_D,
    mov_f, 
    mov_b, 
    mov_r, 
    mov_l, 
    mov_u, 
    mov_d
} move_t;

struct cub
{
    int **num;
    move_t *rec;
};

typedef struct cub cubo;


cubo* new_cubo();

void liberar_cubo(cubo *punt);

void copiar(cubo *a,cubo *b);

void mostrar(cubo *Cub);

int cantidad_pasos(cubo *Cub);

void F(cubo *Cub);
void B(cubo *Cub);
void R(cubo *Cub);
void L(cubo *Cub);
void U(cubo *Cub);
void D(cubo *Cub);
void f(cubo *Cub); 
void b(cubo *Cub);
void r(cubo *Cub);
void l(cubo *Cub);
void u(cubo *Cub);
void d(cubo *Cub);

move_t opposite_move(move_t mov);

void apply_move(cubo *Cub,move_t mov);

void apply_move_list(cubo *cub,char *moves);

#endif //__CUBO__
