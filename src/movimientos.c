
// Funciones de relacion entre lo grafico y el cubo almacenado.

#include "cubo.h"

//Movimientos que se ven.

void F_grafi (float angle){

    MATRIX local_world1;
    VECTOR object_rotation1 = { 0.00f, 0.00f, 0.00f, 1.00f },object_pos = { 0.00f, 0.00f, 0.00f, 1.00f };
    object_rotation1[2]=angle;
    create_local_world(local_world1, object_pos, object_rotation1);
    //fondo
    calcular_vertices_rotados(&(vertices_fondo[36*2]), 36, &(vertices_fondo[36*2]), local_world1);
    calcular_vertices_rotados(vertices_fondo, 12, vertices_fondo, local_world1);
    calcular_vertices_rotados(&(vertices_fondo[36]), 12, &(vertices_fondo[36]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[36*4]), 12, &(vertices_fondo[36*4]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[36*5]), 12, &(vertices_fondo[36*5]), local_world1);
    //cara
    calcular_vertices_rotados(&(vertices[36*2]), 36, &(vertices[36*2]), local_world1);
    calcular_vertices_rotados(vertices, 12, vertices, local_world1);
    calcular_vertices_rotados(&(vertices[36]), 12, &(vertices[36]), local_world1);
    calcular_vertices_rotados(&(vertices[36*4]), 12, &(vertices[36*4]), local_world1);
    calcular_vertices_rotados(&(vertices[36*5]), 12, &(vertices[36*5]), local_world1);
}

void F_graf (){
    F_grafi(-0.525f);
}    

void f_graf (){
    F_grafi(0.525f);
}


void B_grafi (float angle){

    MATRIX local_world1;
    VECTOR object_rotation1 = { 0.00f, 0.00f, 0.00f, 1.00f },object_pos = { 0.00f, 0.00f, 0.00f, 1.00f };
    object_rotation1[2]=angle;
    create_local_world(local_world1, object_pos, object_rotation1);
    //fondo
    calcular_vertices_rotados(&(vertices_fondo[36*3]), 36, &(vertices_fondo[36*3]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[0+24]), 12, &(vertices_fondo[0+24]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[36+24]), 12, &(vertices_fondo[36+24]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[36*4+24]), 12, &(vertices_fondo[36*4+24]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[36*5+24]), 12, &(vertices_fondo[36*5+24]), local_world1);
    //cara
    calcular_vertices_rotados(&(vertices[36*3]), 36, &(vertices[36*3]), local_world1);
    calcular_vertices_rotados(&(vertices[0+24]), 12, &(vertices[0+24]), local_world1);
    calcular_vertices_rotados(&(vertices[36+24]), 12, &(vertices[36+24]), local_world1);
    calcular_vertices_rotados(&(vertices[36*4+24]), 12, &(vertices[36*4+24]), local_world1);
    calcular_vertices_rotados(&(vertices[36*5+24]), 12, &(vertices[36*5+24]), local_world1);
}

void B_graf (){
    B_grafi(0.525f);
}    

void b_graf (){
    B_grafi(-0.525f);
}


void R_grafi (float angle){

    MATRIX local_world1;
    VECTOR object_rotation1 = { 0.00f, 0.00f, 0.00f, 1.00f },object_pos = { 0.00f, 0.00f, 0.00f, 1.00f };
    object_rotation1[0]=angle;
    create_local_world(local_world1, object_pos, object_rotation1);

    //fondo
    calcular_vertices_rotados(&(vertices_fondo[0]), 36, &(vertices_fondo[0]), local_world1);
    
    calcular_vertices_rotados(&(vertices_fondo[2*36]), 4, &(vertices_fondo[2*36]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[2*36+12]), 4, &(vertices_fondo[2*36+12]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[2*36+24]), 4, &(vertices_fondo[2*36+24]), local_world1);
    
    calcular_vertices_rotados(&(vertices_fondo[3*36]), 4, &(vertices_fondo[3*36]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[3*36+12]), 4, &(vertices_fondo[3*36+12]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[3*36+24]), 4, &(vertices_fondo[3*36+24]), local_world1);
    
    calcular_vertices_rotados(&(vertices_fondo[4*36]), 4, &(vertices_fondo[4*36]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[4*36+12]), 4, &(vertices_fondo[4*36+12]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[4*36+24]), 4, &(vertices_fondo[4*36+24]), local_world1);
    
    calcular_vertices_rotados(&(vertices_fondo[5*36]), 4, &(vertices_fondo[5*36]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[5*36+12]), 4, &(vertices_fondo[5*36+12]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[5*36+24]), 4, &(vertices_fondo[5*36+24]), local_world1);
    
    //cara    
    calcular_vertices_rotados(&(vertices[0]), 36, &(vertices[0]), local_world1);
    
    calcular_vertices_rotados(&(vertices[2*36]), 4, &(vertices[2*36]), local_world1);
    calcular_vertices_rotados(&(vertices[2*36+12]), 4, &(vertices[2*36+12]), local_world1);
    calcular_vertices_rotados(&(vertices[2*36+24]), 4, &(vertices[2*36+24]), local_world1);
    
    calcular_vertices_rotados(&(vertices[3*36]), 4, &(vertices[3*36]), local_world1);
    calcular_vertices_rotados(&(vertices[3*36+12]), 4, &(vertices[3*36+12]), local_world1);
    calcular_vertices_rotados(&(vertices[3*36+24]), 4, &(vertices[3*36+24]), local_world1);
    
    calcular_vertices_rotados(&(vertices[4*36]), 4, &(vertices[4*36]), local_world1);
    calcular_vertices_rotados(&(vertices[4*36+12]), 4, &(vertices[4*36+12]), local_world1);
    calcular_vertices_rotados(&(vertices[4*36+24]), 4, &(vertices[4*36+24]), local_world1);
    
    calcular_vertices_rotados(&(vertices[5*36]), 4, &(vertices[5*36]), local_world1);
    calcular_vertices_rotados(&(vertices[5*36+12]), 4, &(vertices[5*36+12]), local_world1);
    calcular_vertices_rotados(&(vertices[5*36+24]), 4, &(vertices[5*36+24]), local_world1);
}

void R_graf (){
    R_grafi(-0.525f);
}    

void r_graf (){
    R_grafi(0.525f);
}


void L_grafi (float angle){

    MATRIX local_world1;
    VECTOR object_rotation1 = { 0.00f, 0.00f, 0.00f, 1.00f },object_pos = { 0.00f, 0.00f, 0.00f, 1.00f };
    object_rotation1[0]=angle;
    create_local_world(local_world1, object_pos, object_rotation1);

    //fondo
    calcular_vertices_rotados(&(vertices_fondo[36]), 36, &(vertices_fondo[36]), local_world1);
    
    calcular_vertices_rotados(&(vertices_fondo[2*36+8]), 4, &(vertices_fondo[2*36+8]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[2*36+20]), 4, &(vertices_fondo[2*36+20]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[2*36+32]), 4, &(vertices_fondo[2*36+32]), local_world1);
    
    calcular_vertices_rotados(&(vertices_fondo[3*36+8]), 4, &(vertices_fondo[3*36+8]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[3*36+20]), 4, &(vertices_fondo[3*36+20]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[3*36+32]), 4, &(vertices_fondo[3*36+32]), local_world1);
    
    calcular_vertices_rotados(&(vertices_fondo[4*36+8]), 4, &(vertices_fondo[4*36+8]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[4*36+20]), 4, &(vertices_fondo[4*36+20]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[4*36+32]), 4, &(vertices_fondo[4*36+32]), local_world1);
    
    calcular_vertices_rotados(&(vertices_fondo[5*36+8]), 4, &(vertices_fondo[5*36+8]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[5*36+20]), 4, &(vertices_fondo[5*36+20]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[5*36+32]), 4, &(vertices_fondo[5*36+32]), local_world1);
    
    //cara
    calcular_vertices_rotados(&(vertices[36]), 36, &(vertices[36]), local_world1);
    
    calcular_vertices_rotados(&(vertices[2*36+8]), 4, &(vertices[2*36+8]), local_world1);
    calcular_vertices_rotados(&(vertices[2*36+20]), 4, &(vertices[2*36+20]), local_world1);
    calcular_vertices_rotados(&(vertices[2*36+32]), 4, &(vertices[2*36+32]), local_world1);
    
    calcular_vertices_rotados(&(vertices[3*36+8]), 4, &(vertices[3*36+8]), local_world1);
    calcular_vertices_rotados(&(vertices[3*36+20]), 4, &(vertices[3*36+20]), local_world1);
    calcular_vertices_rotados(&(vertices[3*36+32]), 4, &(vertices[3*36+32]), local_world1);
    
    calcular_vertices_rotados(&(vertices[4*36+8]), 4, &(vertices[4*36+8]), local_world1);
    calcular_vertices_rotados(&(vertices[4*36+20]), 4, &(vertices[4*36+20]), local_world1);
    calcular_vertices_rotados(&(vertices[4*36+32]), 4, &(vertices[4*36+32]), local_world1);
    
    calcular_vertices_rotados(&(vertices[5*36+8]), 4, &(vertices[5*36+8]), local_world1);
    calcular_vertices_rotados(&(vertices[5*36+20]), 4, &(vertices[5*36+20]), local_world1);
    calcular_vertices_rotados(&(vertices[5*36+32]), 4, &(vertices[5*36+32]), local_world1);
}

void L_graf (){
    L_grafi(0.525f);
}    

void l_graf (){
    L_grafi(-0.525f);
}


void U_grafi (float angle){

    MATRIX local_world1;
    VECTOR object_rotation1 = { 0.00f, 0.00f, 0.00f, 1.00f },object_pos = { 0.00f, 0.00f, 0.00f, 1.00f };
    object_rotation1[1]=angle;
    create_local_world(local_world1, object_pos, object_rotation1);

    //fondo
    calcular_vertices_rotados(&(vertices_fondo[4*36]), 36, &(vertices_fondo[4*36]), local_world1);
    
    calcular_vertices_rotados(&(vertices_fondo[0]), 4, &(vertices_fondo[0]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[12]), 4, &(vertices_fondo[12]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[24]), 4, &(vertices_fondo[24]), local_world1);
    
    
    calcular_vertices_rotados(&(vertices_fondo[36]), 4, &(vertices_fondo[36]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[36+12]), 4, &(vertices_fondo[36+12]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[36+24]), 4, &(vertices_fondo[36+24]), local_world1);
    
    calcular_vertices_rotados(&(vertices_fondo[2*36]), 12, &(vertices_fondo[2*36]), local_world1);
    
    calcular_vertices_rotados(&(vertices_fondo[3*36]), 12, &(vertices_fondo[3*36]), local_world1);
    
    //cara
    calcular_vertices_rotados(&(vertices[4*36]), 36, &(vertices[4*36]), local_world1);
    
    calcular_vertices_rotados(&(vertices[0]), 4, &(vertices[0]), local_world1);
    calcular_vertices_rotados(&(vertices[12]), 4, &(vertices[12]), local_world1);
    calcular_vertices_rotados(&(vertices[24]), 4, &(vertices[24]), local_world1);
    
    
    calcular_vertices_rotados(&(vertices[36]), 4, &(vertices[36]), local_world1);
    calcular_vertices_rotados(&(vertices[36+12]), 4, &(vertices[36+12]), local_world1);
    calcular_vertices_rotados(&(vertices[36+24]), 4, &(vertices[36+24]), local_world1);
    
    calcular_vertices_rotados(&(vertices[2*36]), 12, &(vertices[2*36]), local_world1);
    
    calcular_vertices_rotados(&(vertices[3*36]), 12, &(vertices[3*36]), local_world1);
}

void U_graf (){
    U_grafi(-0.525f);
}    

void u_graf (){
    U_grafi(0.525f);
}


void D_grafi (float angle){

    MATRIX local_world1;
    VECTOR object_rotation1 = { 0.00f, 0.00f, 0.00f, 1.00f },object_pos = { 0.00f, 0.00f, 0.00f, 1.00f };
    object_rotation1[1]=angle;
    create_local_world(local_world1, object_pos, object_rotation1);

    //fondo
    calcular_vertices_rotados(&(vertices_fondo[5*36]), 36, &(vertices_fondo[5*36]), local_world1);
    
    calcular_vertices_rotados(&(vertices_fondo[0+8]), 4, &(vertices_fondo[0+8]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[12+8]), 4, &(vertices_fondo[12+8]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[24+8]), 4, &(vertices_fondo[24+8]), local_world1);
    
    
    calcular_vertices_rotados(&(vertices_fondo[36+8]), 4, &(vertices_fondo[36+8]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[36+12+8]), 4, &(vertices_fondo[36+12+8]), local_world1);
    calcular_vertices_rotados(&(vertices_fondo[36+24+8]), 4, &(vertices_fondo[36+24+8]), local_world1);
    
    calcular_vertices_rotados(&(vertices_fondo[2*36+24]), 12, &(vertices_fondo[2*36+24]), local_world1);
    
    calcular_vertices_rotados(&(vertices_fondo[3*36+24]), 12, &(vertices_fondo[3*36+24]), local_world1);
    
    //cara
    calcular_vertices_rotados(&(vertices[5*36]), 36, &(vertices[5*36]), local_world1);
    
    calcular_vertices_rotados(&(vertices[0+8]), 4, &(vertices[0+8]), local_world1);
    calcular_vertices_rotados(&(vertices[12+8]), 4, &(vertices[12+8]), local_world1);
    calcular_vertices_rotados(&(vertices[24+8]), 4, &(vertices[24+8]), local_world1);
    
    
    calcular_vertices_rotados(&(vertices[36+8]), 4, &(vertices[36+8]), local_world1);
    calcular_vertices_rotados(&(vertices[36+12+8]), 4, &(vertices[36+12+8]), local_world1);
    calcular_vertices_rotados(&(vertices[36+24+8]), 4, &(vertices[36+24+8]), local_world1);
    
    calcular_vertices_rotados(&(vertices[2*36+24]), 12, &(vertices[2*36+24]), local_world1);
    
    calcular_vertices_rotados(&(vertices[3*36+24]), 12, &(vertices[3*36+24]), local_world1);
}

void D_graf (){
    D_grafi(0.525f);
}    

void d_graf (){
    D_grafi(-0.525f);
}


void graf_move(move_t mov){
    switch(mov) {
        case mov_F : F_graf();break;
        case mov_B : B_graf();break; 
        case mov_R : R_graf();break;
        case mov_L : L_graf();break;
        case mov_U : U_graf();break;
        case mov_D : D_graf();break;
        case mov_f : f_graf();break;
        case mov_b : b_graf();break;
        case mov_r : r_graf();break;
        case mov_l : l_graf();break;
        case mov_u : u_graf();break;
        case mov_d : d_graf();break;
        case mov_none : break;
    }
}
