
#include <math3d.h>
#include <stdlib.h>

#include <packet.h>

#include <dma_tags.h>
#include <gif_tags.h>
#include <gs_psm.h>

#include <dma.h>

#include <graph.h>
#include <graph_vram.h>

#include <draw.h>
#include <draw3d.h>

#include "cubo.h"
#include "visual.h"

#include "mesh_data.c"
#include "movimientos.c"

// Este código se basa en el ejemplo:
// ps2dev/ps2sdk/samples/draw/cube/cube.c 

packet_t *packets[2];
int context = 0;
prim_t prim;
color_t color;

MATRIX local_world;
MATRIX world_view;
MATRIX view_screen;
MATRIX local_screen;
MATRIX local_screen_fija;

VECTOR *temp_vertices;
VECTOR *temp_vertices_position;
VECTOR *temp_vertices_fondo;
VECTOR *temp_vertices_avance;

xyz_t *verts;
xyz_t *verts_position;
xyz_t *verts_fondo;
xyz_t *verts_avance;

VECTOR colors_rgb[216];
VECTOR colors_position_rgb[12];
VECTOR colors_fondo_rgb[216];
VECTOR colors_avance_rgb[120];

color_t *colors;
color_t *colors_position;
color_t *colors_fondo;
color_t *colors_avance;

VECTOR object_position = { 0.00f, 0.00f, 0.00f, 1.00f };
VECTOR object_rotation = { 0.00f, 0.00f, 0.00f, 1.00f };

VECTOR camera_position = { 0.00f, 0.00f, 100.00f, 1.00f };
VECTOR camera_rotation = { 0.00f, 0.00f, 0.00f, 1.00f };

int get_color_actual(VECTOR vect) {
  if (vect[0] == 1 && vect[1] == 0 && vect[2] == 0)
    return 1;
  if (vect[0] == 0 && vect[1] == 1 && vect[2] == 0)
    return 2;
  if (vect[0] == 0 && vect[1] == 0 && vect[2] == 1)
    return 3;
  if (vect[0] == 1 && vect[1] == 1 && vect[2] == 0)
    return 4;
  if (vect[0] == 0 && vect[1] == 1 && vect[2] == 1)
    return 5;
  if (vect[0] == 1 && vect[1] == 0 && vect[2] == 1)
    return 6;
  return -1;
}

void actualizar_colores_de_grafico_a_cubo(cubo * cub) {
  int i, j, cont;
  //DATOS EN CERO
  for (i = 1; i <= 3; i++) {
    for (j = 1; j <= 3; j++)
      cub->num[i][j] = 0;
    for (j = 7; j <= 12; j++)
      cub->num[i][j] = 0;
  }
  for (i = 7; i <= 9; i++) {
    for (j = 1; j <= 3; j++)
      cub->num[i][j] = 0;
    for (j = 7; j <= 12; j++)
      cub->num[i][j] = 0;
  }


  //Cara  de frente
  cont = 0;
  for (i = 4; i <= 6; i++)
    for (j = 6; j >= 4; j--, cont++)
      cub->num[i][j] = get_color_actual(colors_rgb[2 * 36 + 4 * cont]);

  //Cara  de izquierda
  cont = 0;
  for (j = 3; j >= 1; j--)
    for (i = 4; i <= 6; i++, cont++)
      cub->num[i][j] = get_color_actual(colors_rgb[1 * 36 + 4 * cont]);

  //Cara de abajo
  cont = 0;
  for (i = 7; i <= 9; i++)
    for (j = 6; j >= 4; j--, cont++)
      cub->num[i][j] = get_color_actual(colors_rgb[5 * 36 + 4 * cont]);

  //Cara de derecha
  cont = 0;
  for (j = 7; j <= 9; j++)
    for (i = 4; i <= 6; i++, cont++)
      cub->num[i][j] = get_color_actual(colors_rgb[4 * cont]);

  //Cara  de arriba
  cont = 0;
  for (i = 3; i >= 1; i--)
    for (j = 6; j >= 4; j--, cont++)
      cub->num[i][j] = get_color_actual(colors_rgb[4 * 36 + 4 * cont]);

  //Cara  de atras
  cont = 0;
  for (i = 4; i <= 6; i++)
    for (j = 10; j <= 12; j++, cont++)
      cub->num[i][j] = get_color_actual(colors_rgb[3 * 36 + 4 * cont]);
}

void actualizar_colores_de_cubo_a_grafico(cubo * cub) {
  int i, j, cont;

  //Cara  de arriba
  cont = 0;
  for (i = 3; i >= 1; i--)
    for (j = 6; j >= 4; j--, cont++)
      cambiar_color(4 * 9 + cont, (cub->num[i][j]) - 1);

  //Cara  de izquierda
  cont = 0;
  for (j = 3; j >= 1; j--)
    for (i = 4; i <= 6; i++, cont++)
      cambiar_color(1 * 9 + cont, (cub->num[i][j]) - 1);

  //Cara  de frente
  cont = 0;
  for (i = 4; i <= 6; i++)
    for (j = 6; j >= 4; j--, cont++)
      cambiar_color(2 * 9 + cont, (cub->num[i][j]) - 1);

  //Cara de derecha
  cont = 0;
  for (j = 7; j <= 9; j++)
    for (i = 4; i <= 6; i++, cont++)
      cambiar_color(cont, (cub->num[i][j]) - 1);

  //Cara  de atras
  cont = 0;
  for (i = 4; i <= 6; i++)
    for (j = 10; j <= 12; j++, cont++)
      cambiar_color(3 * 9 + cont, (cub->num[i][j]) - 1);

  //Cara de abajo
  cont = 0;
  for (i = 7; i <= 9; i++)
    for (j = 6; j >= 4; j--, cont++)
      cambiar_color(5 * 9 + cont, (cub->num[i][j]) - 1);
}

void init_gs(framebuffer_t * frame, zbuffer_t * z) {
  // Define a 32-bit 640x512 framebuffer.
  frame->width = 640;
  frame->height = 512;
  frame->mask = 0;
  frame->psm = GS_PSM_32;
  frame->address =
      graph_vram_allocate(frame->width, frame->height, frame->psm,
                          GRAPH_ALIGN_PAGE);

  // Enable the zbuffer.
  z->enable = DRAW_ENABLE;
  z->mask = 0;
  z->method = ZTEST_METHOD_GREATER_EQUAL;
  z->zsm = GS_ZBUF_32;
  z->address =
      graph_vram_allocate(frame->width, frame->height, z->zsm,
                          GRAPH_ALIGN_PAGE);

  // Initialize the screen and tie the first framebuffer to the read circuits.
  graph_initialize(frame->address, frame->width, frame->height, frame->psm, 0,
                   0);
}

void init_drawing_environment(framebuffer_t * frame, zbuffer_t * z) {
  packet_t *packet = packet_init(16, PACKET_NORMAL);

  // This is our generic qword pointer.
  qword_t *q = packet->data;

  // This will setup a default drawing environment.
  q = draw_setup_environment(q, 0, frame, z);

  // Now reset the primitive origin to 2048-width/2,2048-height/2.
  q = draw_primitive_xyoffset(q, 0, (2048 - 320), (2048 - 256));

  // Finish setting up the environment.
  q = draw_finish(q);

  // Now send the packet, no need to wait since it's the first.
  dma_channel_send_normal(DMA_CHANNEL_GIF, packet->data, q - packet->data, 0,
                          0);

  dma_wait_fast();

  packet_free(packet);
}

void init_visual() {
  packets[0] = packet_init(10000, PACKET_NORMAL);
  packets[1] = packet_init(10000, PACKET_NORMAL);

  // Allocate calculation space.
  temp_vertices = (VECTOR *) memalign(128, sizeof(VECTOR) * vertex_count);
  temp_vertices_position = (VECTOR *) memalign(128, sizeof(VECTOR) * 12);
  temp_vertices_fondo = (VECTOR *) memalign(128, sizeof(VECTOR) * 216);
  temp_vertices_avance = (VECTOR *) memalign(128, sizeof(VECTOR) * 120);

  // Allocate register space.
  verts = (xyz_t *) memalign(128, sizeof(vertex_t) * vertex_count);
  colors = (color_t *) memalign(128, sizeof(color_t) * vertex_count);
  verts_position = (xyz_t *) memalign(128, sizeof(vertex_t) * 12);
  colors_position = (color_t *) memalign(128, sizeof(color_t) * 12);
  verts_fondo = (xyz_t *) memalign(128, sizeof(vertex_t) * 216);
  colors_fondo = (color_t *) memalign(128, sizeof(color_t) * 216);
  verts_avance = (xyz_t *) memalign(128, sizeof(vertex_t) * 120);
  colors_avance = (color_t *) memalign(128, sizeof(color_t) * 120);

  // Define the triangle primitive we want to use.
  prim.type = PRIM_TRIANGLE;
  prim.shading = PRIM_SHADE_GOURAUD;
  prim.mapping = DRAW_DISABLE;
  prim.fogging = DRAW_DISABLE;
  prim.blending = DRAW_DISABLE;
  prim.antialiasing = DRAW_ENABLE;
  prim.mapping_type = PRIM_MAP_ST;
  prim.colorfix = PRIM_UNFIXED;

  color.r = 0x80;
  color.g = 0x80;
  color.b = 0x80;
  color.a = 0x80;
  color.q = 1.0f;

  // Create the view_screen matrix.
  create_view_screen(view_screen, graph_aspect_ratio(), -3.00f, 3.00f, -3.00f,
                     3.00f, 1.00f, 2000.00f);

  // Wait for any previous dma transfers to finish before continuing.
  dma_wait_fast();
}

void finish_visual() {
  packet_free(packets[0]);
  packet_free(packets[1]);
}

void refresh_visual(int first_call, int progress, framebuffer_t * frame,
                    zbuffer_t * z) {
  packet_t *current;
  qword_t *q;
  qword_t *dmatag;
  int i;

  current = packets[context];
  // Create the local_world matrix.
  create_local_world(local_world, object_position, object_rotation);
  // Create the world_view matrix.
  create_world_view(world_view, camera_position, camera_rotation);
  // Create the local_screen matrix.
  create_local_screen(local_screen, local_world, world_view, view_screen);

  if (first_call)
    create_local_screen(local_screen_fija, local_world, world_view,
                        view_screen);

  // Calculate the vertex values.
  calculate_vertices(temp_vertices, vertex_count, vertices, local_screen);
  calculate_vertices(temp_vertices_position, 12, vertices_position,
                     local_screen);
  calculate_vertices(temp_vertices_fondo, vertex_count, vertices_fondo,
                     local_screen);
  calculate_vertices(temp_vertices_avance, 120, vertices_avance,
                     local_screen_fija);

  // Convert floating point vertices to fixed point and translate to center of screen.
  draw_convert_xyz(verts, 2048, 2048, 32, vertex_count,
                   (vertex_f_t *) temp_vertices);
  draw_convert_xyz(verts_position, 2048, 2048, 32, 12,
                   (vertex_f_t *) temp_vertices_position);
  draw_convert_xyz(verts_fondo, 2048, 2048, 32, vertex_count,
                   (vertex_f_t *) temp_vertices_fondo);
  draw_convert_xyz(verts_avance, 2048, 2048, 32, 120,
                   (vertex_f_t *) temp_vertices_avance);

  // Convert floating point colours to fixed point.
  draw_convert_rgbq(colors, vertex_count, (vertex_f_t *) temp_vertices,
                    (color_f_t *) colors_rgb, color.a);
  draw_convert_rgbq(colors_position, 12, (vertex_f_t *) temp_vertices_position,
                    (color_f_t *) colors_position_rgb, color.a);
  draw_convert_rgbq(colors_fondo, vertex_count,
                    (vertex_f_t *) temp_vertices_fondo,
                    (color_f_t *) colors_fondo_rgb, color.a);
  draw_convert_rgbq(colors_avance, 120, (vertex_f_t *) temp_vertices_avance,
                    (color_f_t *) colors_avance_rgb, color.a);

  // Grab our dmatag pointer for the dma chain.
  dmatag = current->data;

  // Now grab our qword pointer and increment past the dmatag.
  q = dmatag;
  q++;

  // Clear framebuffer but don't update zbuffer.
  q = draw_disable_tests(q, 0, z);
  q = draw_clear(q, 0, 2048.0f - 320.0f, 2048.0f - 256.0f, frame->width,
                 frame->height, 0x00, 0x00, 0x00);
  q = draw_enable_tests(q, 0, z);

  // Draw the triangles using triangle primitive type.
  q = draw_prim_start(q, 0, &prim, &color);

  for (i = 0; i < points_count; i++) {
    q->dw[0] = colors[points[i]].rgbaq;
    q->dw[1] = verts[points[i]].xyz;
    q++;
  }

  for (i = 0; i < 12; i++) {
    q->dw[0] = colors_position[i].rgbaq;
    q->dw[1] = verts_position[i].xyz;
    q++;
  }

  for (i = 0; i < points_count; i++) {
    q->dw[0] = colors_fondo[points[i]].rgbaq;
    q->dw[1] = verts_fondo[points[i]].xyz;
    q++;
  }

  for (i = 0; i < (1.8 * progress); i++) {
    q->dw[0] = colors_avance[points[i]].rgbaq;
    q->dw[1] = verts_avance[points[i]].xyz;
    q++;
  }

  q = draw_prim_end(q, 2, DRAW_RGBAQ_REGLIST);

  // Setup a finish event.
  q = draw_finish(q);

  // Define our dmatag for the dma chain.
  DMATAG_END(dmatag, q - current->data - 1, 0, 0, 0);

  // Now send our current dma chain.
  dma_wait_fast();
  dma_channel_send_chain(DMA_CHANNEL_GIF, current->data, q - current->data, 0,
                         0);

  // Now switch our packets so we can process data while the DMAC is working.
  context ^= 1;

  // Wait for scene to finish drawing
  draw_wait_finish();

  graph_wait_vsync();
}

void setear_color() {
  int i;
  //Seteamos el color de las celdas del cubo.
  for (i = 0; i < 54; i++) {
    switch (i / 9) {
    case 0:
      cambiar_color(i, 0);
      break;
    case 1:
      cambiar_color(i, 1);
      break;
    case 2:
      cambiar_color(i, 2);
      break;
    case 3:
      cambiar_color(i, 3);
      break;
    case 4:
      cambiar_color(i, 4);
      break;
    case 5:
      cambiar_color(i, 5);
      break;
    }
  }

  //Color position
  for (i = 0; i < 12; i++) {
    colors_position_rgb[i][0] = 1;
    colors_position_rgb[i][1] = 1;
    colors_position_rgb[i][2] = 1;
    colors_position_rgb[i][3] = 1;
  }

  //Color fondo negro del cubo.
  for (i = 0; i < vertex_count; i++) {
    colors_fondo_rgb[i][0] = 0;
    colors_fondo_rgb[i][1] = 0;
    colors_fondo_rgb[i][2] = 0;
    colors_fondo_rgb[i][3] = 1;
  }

  //Color barra de progreso.
  for (i = 0; i < 30; i++)
    cambiar_color_barra(i, i % 6);
}

void cambiar_color(int i, int l) {
  int j;
  for (j = 0; j < 4; j++) {
    colors_rgb[4 * i + j][0] = col[l][0];
    colors_rgb[4 * i + j][1] = col[l][1];
    colors_rgb[4 * i + j][2] = col[l][2];
    colors_rgb[4 * i + j][3] = 1.00f;
  }
}

void cambiar_color_barra(int i, int l) {
  int j;
  for (j = 0; j < 4; j++) {
    colors_avance_rgb[4 * i + j][0] = col[l][0];
    colors_avance_rgb[4 * i + j][1] = col[l][1];
    colors_avance_rgb[4 * i + j][2] = col[l][2];
    colors_avance_rgb[4 * i + j][3] = 1.00f;
  }
}

void cambiar_cuadrado(int j, int k) {
  int i, l;

  for (l = 0; l < 4; l++) {
    for (i = 0; i < 3; i++) {
      vertices_position[l * 3][i] = vertices[j * 36 + k * 4 + l % 4][i];
      vertices_position[l * 3 + 1][i] =
          vertices[j * 36 + k * 4 + (l + 1) % 4][i];
      vertices_position[l * 3 + 2][i] =
          vertices[j * 36 + k * 4 + (l + 2) % 4][i];
    }
  }

  if (j == 0 || j == 1) {
    for (l = 0; l < 12; l++)
      vertices_position[l][0] *= 1.1333;
    vertices_position[1][2] -= 7;
    vertices_position[4][2] += 7;
    vertices_position[8][1] -= 7;
    vertices_position[9][1] += 7;
  }

  if (j == 2 || j == 3) {
    for (l = 0; l < 12; l++)
      vertices_position[l][2] *= 1.1333;
    vertices_position[1][1] -= 7;
    vertices_position[4][1] += 7;
    vertices_position[8][0] -= 7;
    vertices_position[9][0] += 7;
  }

  if (j == 4 || j == 5) {
    for (l = 0; l < 12; l++)
      vertices_position[l][1] *= 1.1333;
    vertices_position[2][0] += 7;
    vertices_position[3][0] -= 7;
    vertices_position[7][2] -= 7;
    vertices_position[10][2] += 7;
  }

}

void cambiar_color_cuadrado(int j, int k) {
  int i, indice = 0;

  for (i = 0; i < 6; i++)
    if (colors_rgb[j * 36 + k * 4][0] == col[i][0]
        && colors_rgb[j * 36 + k * 4][1] == col[i][1]
        && colors_rgb[j * 36 + k * 4][2] == col[i][2])
      indice = i;
  indice++;

  for (i = 0; i < 4; i++) {
    colors_rgb[j * 36 + k * 4 + i][0] = col[indice % 6][0];
    colors_rgb[j * 36 + k * 4 + i][1] = col[indice % 6][1];
    colors_rgb[j * 36 + k * 4 + i][2] = col[indice % 6][2];
  }
}

void rotar_imagen_x(float ang) {
  object_rotation[0] += ang;
}

void rotar_imagen_y(float ang) {
  object_rotation[1] += ang;
}
