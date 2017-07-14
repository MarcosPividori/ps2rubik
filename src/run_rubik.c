/**********************************************************************************
 * Programa para PlayStation2: CUBO de RUBIK.
 *
 * Trabajo final de la materia "Arquitectura del computador" LCC.
 * Alumno: Marcos Pividori (marcos_pividori@hotmail.com)
 *
 * Se realizó sobre el entorno ps2dev, usando diferentes librerias, y basandose
 * en ejemplos y test de los joystick, video y audio.
 * Al principio uno elige los colores del cubo para obtener el mismo patrón que uno
 * tiene en sus manos.
 * Luego puede intentar resolverlo o pedirle al juego que le indique al usuario
 * los pasos para resolverlo, y lo guíe hacia la solución.
 * Se utilizan tres métodos diferentes de búsqueda de la solución, con diferentes
 * procesos.
 * El de mejor solución (menos pasos) requerirá mas tiempo de procesamiento
 * a diferencia del de peor solución, que será mas rápido.
 * También es posible generar cubos aleatorios para jugar.
 **********************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <tamtypes.h>
#include <kernel.h>
#include <sifrpc.h>
#include <loadfile.h>
#include <stdio.h>
#include <time.h>
#include <kernel.h>
#include <tamtypes.h>
#include <math3d.h>

#include "cubo.h"
#include "visual.h"
#include "generador.h"
#include "joysticks.h"
#include "rubik_solver.h"
#include "beginner_solver.h"
#include "audio.h"

#define TIME_MOVE 150000
#define YES 1
#define NO  0

typedef enum {
  empty_state,
  solution_top,
  solution_med,
  solution_low,
  solution_end
} state_t;


typedef struct {
  int move_count;
  move_t state_move;
} move_st;

#define init_move_st {   \
    .move_count=0,   \
    .state_move=mov_none \
}


typedef struct {
  int cara_actual;
  int celda_actual;
} cursor_st;

#define init_cursor_st { \
    .cara_actual=0,      \
    .celda_actual=0      \
}


typedef struct {
  move_t *solucion;
  int mov_index;
} solution_reader_st;

#define init_solution_reader_st { \
    .solucion=NULL,               \
    .mov_index=1                  \
}


typedef struct {
  state_t state;
  int rotacion;
  int etapa;
  int min_sol;
  cubo *cubo_ptr;
  cubo *cubo_sol_ptr;
} rubik_solver_st;

#define init_rubik_solver_st { \
    .state=empty_state,        \
    .etapa=0,                  \
    .rotacion=0,               \
    .min_sol=-1,               \
    .cubo_ptr=NULL,            \
    .cubo_sol_ptr=NULL         \
}


typedef struct {
  int cambio_en_solucion;
  int coloreo_inicial_finalizado;

  move_st movement;
  cursor_st cursor;
  solution_reader_st sol_reader;
  rubik_solver_st solver;

  cubo *cubo_principal;
} game_st;

#define init_game_st {                    \
    .cambio_en_solucion=YES,              \
    .coloreo_inicial_finalizado=NO,       \
    .movement=init_move_st,               \
    .cursor=init_cursor_st,               \
    .sol_reader=init_solution_reader_st,  \
    .solver=init_rubik_solver_st,         \
    .cubo_principal=NULL                  \
}

// FUNC PRINCIPAL
int rubik(framebuffer_t * frame, zbuffer_t * z) {
  clock_t timer_principal = clock();
  clock_t timer_audio = clock();

  int audio_cargado = NO;
  int first_loop = YES;
  int j = 0, progress = 100;
  u32 new_pad;
  move_t mov = mov_none;

  game_st st = init_game_st;

  // Allocamos el Cubo Principal.
  st.cubo_principal = new_cubo();

  init_visual();

  init_joystick();

  // Loop Principal 
  while (1) {
    // SONIDO
    if (first_loop == NO) {
      if (audio_cargado == NO) {
        cargar_cancion();
        timer_audio = clock();
        audio_cargado = YES;
      }
      if (clock() - timer_audio > LIMIT_MUSIC) {
        reiniciar_cancion();
        timer_audio = clock();
      }
    }
    // JOYSTICK
    if (st.movement.state_move == mov_none && st.solver.state == empty_state) {

      new_pad = get_joystick_state();

      if (new_pad & PAD_LEFT)
        printf("LEFT\n"), rotar_imagen_y(-0.1f);
      if (new_pad & PAD_DOWN)
        printf("DOWN\n"), rotar_imagen_x(-0.1f);
      if (new_pad & PAD_RIGHT)
        printf("RIGHT\n"), rotar_imagen_y(0.1f);
      if (new_pad & PAD_UP)
        printf("UP\n"), rotar_imagen_x(0.1f);

      if (new_pad & PAD_START) {
        printf("START\n");
        if (st.coloreo_inicial_finalizado == NO) {
          actualizar_colores_de_grafico_a_cubo(st.cubo_principal);
          st.cursor.celda_actual = 4;
          cambiar_cuadrado(st.cursor.cara_actual, st.cursor.celda_actual);
        }
        st.coloreo_inicial_finalizado = YES;
      }

      if (new_pad & PAD_SQUARE) {
        printf("SQUARE\n");
        if (st.movement.state_move == mov_none
            && st.coloreo_inicial_finalizado == YES) {
          st.movement.move_count++;
          switch (st.cursor.cara_actual) {
          case 0:
            mov = mov_R;
            break;
          case 1:
            mov = mov_L;
            break;
          case 2:
            mov = mov_F;
            break;
          case 3:
            mov = mov_B;
            break;
          case 4:
            mov = mov_U;
            break;
          case 5:
            mov = mov_D;
            break;
          }
          if (st.movement.move_count == 3) {
            graf_move(opposite_move(mov));
            graf_move(opposite_move(mov));
            apply_move(st.cubo_principal, mov);
            actualizar_colores_de_cubo_a_grafico(st.cubo_principal);
            st.movement.move_count = 0;
            st.cambio_en_solucion = YES;
          } else
            graf_move(mov);
        }
      }

      if (new_pad & PAD_TRIANGLE) {
        printf("TRIANGLE\n");
        if (st.movement.state_move == mov_none
            && st.coloreo_inicial_finalizado == YES) {
          st.movement.move_count--;
          switch (st.cursor.cara_actual) {
          case 0:
            mov = mov_r;
            break;
          case 1:
            mov = mov_l;
            break;
          case 2:
            mov = mov_f;
            break;
          case 3:
            mov = mov_b;
            break;
          case 4:
            mov = mov_u;
            break;
          case 5:
            mov = mov_d;
            break;
          }
          if (st.movement.move_count == -3) {
            graf_move(opposite_move(mov));
            graf_move(opposite_move(mov));
            apply_move(st.cubo_principal, mov);
            actualizar_colores_de_cubo_a_grafico(st.cubo_principal);
            st.movement.move_count = 0;
            st.cambio_en_solucion = YES;
          } else
            graf_move(mov);
        }
      }

      if (new_pad & PAD_CIRCLE) {
        printf("CIRCLE\n");
        if (st.coloreo_inicial_finalizado == YES) {
          desarmar_cubo(st.cubo_principal);
          actualizar_colores_de_cubo_a_grafico(st.cubo_principal);
          st.cambio_en_solucion = YES;
        }
      }


      if (new_pad & PAD_CROSS) {
        printf("CROSS\n");
        if (st.coloreo_inicial_finalizado == NO)
          cambiar_color_cuadrado(st.cursor.cara_actual, st.cursor.celda_actual);
        else {
          if (st.movement.move_count == 0) {
            if (st.cambio_en_solucion == YES) {
              st.solver.state = solution_top;
              st.solver.etapa = 0;
              st.solver.rotacion = 1;
            } else {
              st.movement.state_move =
                  st.sol_reader.solucion[st.sol_reader.mov_index];
              if (st.sol_reader.solucion[st.sol_reader.mov_index] != 0)
                st.sol_reader.mov_index++;
            }
          }
        }
      }

      if (new_pad & PAD_R1) {
        printf("R1\n");
        if (st.cambio_en_solucion == YES
            && st.movement.move_count == 0
            && st.coloreo_inicial_finalizado == YES) {
          st.solver.state = solution_low;
          st.solver.etapa = 0;
          st.solver.rotacion = 1;
        }
      }

      if (new_pad & PAD_L1) {
        printf("L1\n");
        if (st.cambio_en_solucion == YES
            && st.movement.move_count == 0
            && st.coloreo_inicial_finalizado == YES) {
          st.solver.state = solution_med;
          st.solver.etapa = 0;
          st.solver.rotacion = 1;
        }
      }

      if (new_pad & PAD_R2) {
        printf("R2\n");
        if (st.coloreo_inicial_finalizado == NO) {
          st.cursor.celda_actual = (st.cursor.celda_actual + 1) % 9;
          cambiar_cuadrado(st.cursor.cara_actual, st.cursor.celda_actual);
        } else
          //DEBUG: imprime el estado del cubo.
          mostrar(st.cubo_principal);
      }

      if (new_pad & PAD_L2) {
        printf("L2\n");
        if (st.coloreo_inicial_finalizado == NO) {
          st.cursor.cara_actual = (st.cursor.cara_actual + 1) % 6;
          cambiar_cuadrado(st.cursor.cara_actual, st.cursor.celda_actual);
        } else if (st.movement.move_count == 0) {
          st.cursor.cara_actual = (st.cursor.cara_actual + 1) % 6;
          cambiar_cuadrado(st.cursor.cara_actual, st.cursor.celda_actual);
        }
      }
      //ANALÓGICO DERECHA
      if (get_analogico_derecha_h() > 230)
        rotar_imagen_y(0.02f);

      if (get_analogico_derecha_h() < 20)
        rotar_imagen_y(-0.02f);

      if (get_analogico_derecha_v() > 230)
        rotar_imagen_x(0.02f);

      if (get_analogico_derecha_v() < 20)
        rotar_imagen_x(-0.02f);

      //ANALÓGICO IZQUIERDA
      if (get_analogico_izquierda_h() > 230)
        rotar_imagen_y(0.07f);

      if (get_analogico_izquierda_h() < 20)
        rotar_imagen_y(-0.07f);

      if (get_analogico_izquierda_v() > 230)
        rotar_imagen_x(0.07f);

      if (get_analogico_izquierda_v() < 20)
        rotar_imagen_x(-0.07f);
    }
    // FIN JOYSTICK

    // SOLUCION
    // En caso de estar en un procedimiento de busqueda de la solucion al cubo.
    if (st.solver.state != empty_state) {
      switch (st.solver.state) {

        //Procedimiento 1  - El mejor (Prueba arrancando de todas las caras y elige el mas corto)
      case solution_top:{
          if (st.solver.etapa == 0) {
            if (st.solver.cubo_sol_ptr != NULL && st.solver.rotacion == 1) {
              liberar_cubo(st.solver.cubo_sol_ptr);
              st.solver.cubo_sol_ptr = NULL;
            }
            st.cubo_principal->rec[0] = 0;
            st.solver.cubo_ptr = st.cubo_principal;
          }

          init_small_engine();

          st.solver.cubo_ptr =
              rubik_solver(st.solver.cubo_ptr, st.solver.etapa,
                           st.solver.rotacion);

          if (st.solver.etapa == 5) {
            j = cantidad_pasos(st.solver.cubo_ptr);
            if (st.solver.rotacion == 1) {
              st.solver.min_sol = j;
              st.solver.cubo_sol_ptr = st.solver.cubo_ptr;
            } else if (j < st.solver.min_sol) {
              st.solver.min_sol = j;
              liberar_cubo(st.solver.cubo_sol_ptr);
              st.solver.cubo_sol_ptr = st.solver.cubo_ptr;
            } else
              liberar_cubo(st.solver.cubo_ptr);
            st.solver.etapa = 0;
            st.solver.rotacion++;
          } else
            st.solver.etapa++;
          if (st.solver.rotacion == 7)
            st.solver.state = solution_end;


          stop_small_engine();
          break;
        }

        //Procedimiento 2  -  el intermedio  (Prueba arrancando de una cara en particular)      
      case solution_med:{
          if (st.solver.etapa == 0) {
            if (st.solver.cubo_sol_ptr != NULL) {
              liberar_cubo(st.solver.cubo_sol_ptr);
              st.solver.cubo_sol_ptr = NULL;
            }
            st.cubo_principal->rec[0] = 0;
            st.solver.cubo_ptr = st.cubo_principal;
          }

          init_small_engine();

          st.solver.cubo_ptr =
              rubik_solver(st.solver.cubo_ptr, st.solver.etapa,
                           st.solver.rotacion);

          if (st.solver.etapa == 5) {
            st.solver.cubo_sol_ptr = st.solver.cubo_ptr;
            st.solver.state = solution_end;
          }

          st.solver.etapa++;

          stop_small_engine();
          break;
        }

        //Procedimiento 3  -  El begginer
      case solution_low:{
          if (st.solver.etapa == 0) {
            if (st.solver.cubo_sol_ptr != NULL) {
              liberar_cubo(st.solver.cubo_sol_ptr);
              st.solver.cubo_sol_ptr = NULL;
            }
            st.cubo_principal->rec[0] = 0;
            st.solver.cubo_ptr = st.cubo_principal;
          }

          init_small_engine();

          st.solver.cubo_ptr =
              beginner_solver(st.solver.cubo_ptr, st.solver.etapa);

          if (st.solver.etapa == 9) {
            st.solver.cubo_sol_ptr = st.solver.cubo_ptr;
            st.solver.state = solution_end;
          }

          st.solver.etapa++;

          stop_small_engine();
          break;
        }

        //Fin búsqueda de solución.
      case solution_end:{
          st.sol_reader.solucion = st.solver.cubo_sol_ptr->rec;
          printf("SOLUCION ENCONTRADA:\n");
          mostrar(st.solver.cubo_sol_ptr);
          st.sol_reader.mov_index = 0;
          st.cambio_en_solucion = NO;
          st.solver.state = empty_state;
          break;
        }

      default:
        break;
      }
    }
    // En caso de estar ejecutando un movimiento automatico.
    if (st.movement.state_move != mov_none
        && clock() - timer_principal > TIME_MOVE) {
      timer_principal = clock();
      if (st.movement.move_count < 2) {
        graf_move(st.movement.state_move);
        st.movement.move_count++;
      } else {
        graf_move(opposite_move(st.movement.state_move));
        graf_move(opposite_move(st.movement.state_move));
        apply_move(st.cubo_principal, st.movement.state_move);
        actualizar_colores_de_cubo_a_grafico(st.cubo_principal);
        st.movement.state_move = mov_none;
        st.movement.move_count = 0;
      }
    }
    //Actualizamos la barra de progreso.
    switch (st.solver.state) {
    case empty_state:
      progress = 100;
      break;
    case solution_top:
      progress = (st.solver.rotacion - 1) * 17 + st.solver.etapa * 3;
      break;
    case solution_med:
      progress = st.solver.etapa * 20;
      break;
    case solution_low:
      progress = st.solver.etapa * 11;
      break;
    default:
      break;
    }

    //Actualizamos la imagen en pantalla.
    refresh_visual(first_loop, progress, frame, z);

    first_loop = NO;
  }

  //Fuera del loop Principal
  printf("FINAL!\n");

  SleepThread();

  finish_visual();

  return 0;
}

int main(int argc, char **argv) {
  setear_color();
  init_vertices();
  cambiar_cuadrado(0, 0);

  // The buffers to be used.
  framebuffer_t frame;
  zbuffer_t z;

  // Init GIF dma channel.
  dma_channel_initialize(DMA_CHANNEL_GIF, NULL, 0);
  dma_channel_fast_waits(DMA_CHANNEL_GIF);

  // Init the GS, framebuffer, and zbuffer.
  init_gs(&frame, &z);

  // Init the drawing environment and framebuffer.
  init_drawing_environment(&frame, &z);

  // Funcion Principal.
  rubik(&frame, &z);

  return 0;
}
