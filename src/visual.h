#ifndef __VISUAL__
#define __VISUAL__

#include <math3d.h>

#include <packet.h>

#include <dma_tags.h>
#include <gif_tags.h>
#include <gs_psm.h>

#include <dma.h>

#include <graph.h>
#include <graph_vram.h>

#include <draw.h>
#include <draw3d.h>

void actualizar_colores_de_grafico_a_cubo(cubo * cub);

void actualizar_colores_de_cubo_a_grafico(cubo * cub);

void init_gs(framebuffer_t * frame, zbuffer_t * z);

void init_drawing_environment(framebuffer_t * frame, zbuffer_t * z);

void init_visual();

void finish_visual();

void refresh_visual(int first_call, int progress, framebuffer_t * frame,
                    zbuffer_t * z);

void setear_color();

void init_vertices();

void cambiar_color(int i, int l);

void cambiar_color_barra(int i, int l);

void cambiar_cuadrado(int j, int k);

void cambiar_color_cuadrado(int j, int k);

void rotar_imagen_x(float ang);

void rotar_imagen_y(float ang);

void graf_move(move_t mov);

#endif                          // __VISUAL__
