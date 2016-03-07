
// Este código se basa en el ejemplo:
// ps2dev/ps2sdk/samples/draw/cube/cube.c 

int points_count = 324;

int points[324];

VECTOR col[6] = {
  {  1,  0,  0, 1.00f },
  {  0,  1,  0, 1.00f },
  {  0,  0,  1, 1.00f },
  
  {  1,   1,  0, 1.00f },
  {  0,   1,  1, 1.00f },
  {  1,   0,  1, 1.00f },
};

VECTOR cuad[4]= {
  {  15.25f,  14.75f,  5.25f, 1.00f },
  {  15.25f,  14.75f, 14.75f, 1.00f },
  {  15.25f,   5.25f,  5.25f, 1.00f },
  {  15.25f,   5.25f, 14.75f, 1.00f },
};

VECTOR cuad_fondo[4] = {
  {  15.00f,  15.00f,  5.00f, 1.00f },  
  {  15.00f,  15.00f, 15.00f, 1.00f },
  {  15.00f,   5.00f,  5.00f, 1.00f },
  {  15.00f,   5.00f, 15.00f, 1.00f },
};

VECTOR vertices_position[12] = {
  
  {  17.00f,  15.00f,  5.00f, 1.00f },
  {  17.00f,  15.00f, 15.00f, 1.00f },
  {  17.00f,  12.00f,  5.00f, 1.00f },
  
  {  17.00f,   5.00f,  5.00f, 1.00f },
  {  17.00f,  15.00f,  5.00f, 1.00f },
  {  17.00f,   5.00f,  8.00f, 1.00f },
  
  {  17.00f,   5.00f,  5.00f, 1.00f },
  {  17.00f,   5.00f, 15.00f, 1.00f },
  {  17.00f,   8.00f, 15.00f, 1.00f },
  
  {  17.00f,   5.00f, 15.00f, 1.00f },
  {  17.00f,  15.00f, 15.00f, 1.00f },
  {  17.00f,  15.00f, 12.00f, 1.00f }
  
};
     
VECTOR vertices_avance[120];
VECTOR vertices_fondo[216];
VECTOR vertices[216];
 
int vertex_count = 216;

void init_vertices()
{
    int i1,i2,i,j;
    int cont1,cont2;
    
    for(cont1=0,cont2=0;cont1<324;) {
        points[cont1]=cont2;
        points[cont1+1]=cont2+1;
        points[cont1+2]=cont2+2;
        points[cont1+3]=cont2+1;
        points[cont1+4]=cont2+2;
        points[cont1+5]=cont2+3;
     
        cont1+=6;
        cont2+=4;
    }

    //Inicializamos los vertices de barra de progreso.
    vertices_avance[0][0]= -30.00f;
    vertices_avance[0][1]= 23.00f;
    vertices_avance[0][2]= 25.00f;
    vertices_avance[0][3]= 1.00f;
    vertices_avance[1][0]= -30.00f;
    vertices_avance[1][1]= 21.50f;
    vertices_avance[1][2]= 25.00f;
    vertices_avance[1][3]= 1.00f;
    vertices_avance[2][0]= -28.50f;
    vertices_avance[2][1]= 21.50f;
    vertices_avance[2][2]= 25.00f;
    vertices_avance[2][3]= 1.00f;
    vertices_avance[3][0]= -28.50f;
    vertices_avance[3][1]= 23.00f;
    vertices_avance[3][2]= 25.00f;
    vertices_avance[3][3]= 1.00f;
    
    for(i=4;i<120;i++) {    
        vertices_avance[i][0]=vertices_avance[i-4][0]+2;
        vertices_avance[i][1]=vertices_avance[i-4][1];
        vertices_avance[i][2]=vertices_avance[i-4][2];
        vertices_avance[i][3]=vertices_avance[i-4][3];
    }

    //Inicializamos los vertices del fondo.
    VECTOR cara_fondo[36];
    for(i=0;i<36;i++)
    {
        cara_fondo[i][0] = cuad_fondo[i%4][0];
        cara_fondo[i][1] = cuad_fondo[i%4][1] - 10 * ((i/4)%3);
        cara_fondo[i][2] = cuad_fondo[i%4][2] - 10 * ((i/12)%3);
        cara_fondo[i][3] = cuad_fondo[i%4][3];
    }

    for(i1=0,i2=0;i1<36;i1++,i2++)
        for(j=0;j<4;j++)
            vertices_fondo[i2][j]=cara_fondo[i1][j];

    for(i1=0,i2=36;i1<36;i1++,i2++){
        vertices_fondo[i2][0]=-cara_fondo[i1][0];
        vertices_fondo[i2][1]=cara_fondo[i1][1];
        vertices_fondo[i2][2]=cara_fondo[i1][2];
        vertices_fondo[i2][3]=cara_fondo[i1][3];
    }

    for(i1=0,i2=2*36;i1<36;i1++,i2++){
        vertices_fondo[i2][0]=cara_fondo[i1][1];
        vertices_fondo[i2][1]=cara_fondo[i1][2];
        vertices_fondo[i2][2]=cara_fondo[i1][0];
        vertices_fondo[i2][3]=cara_fondo[i1][3];
    }

    for(i1=0,i2=3*36;i1<36;i1++,i2++){
        vertices_fondo[i2][0]=cara_fondo[i1][1];
        vertices_fondo[i2][1]=cara_fondo[i1][2];
        vertices_fondo[i2][2]=-cara_fondo[i1][0];
        vertices_fondo[i2][3]=cara_fondo[i1][3];
    }

    for(i1=0,i2=4*36;i1<36;i1++,i2++){
        vertices_fondo[i2][0]=cara_fondo[i1][1];
        vertices_fondo[i2][1]=cara_fondo[i1][0];
        vertices_fondo[i2][2]=cara_fondo[i1][2];
        vertices_fondo[i2][3]=cara_fondo[i1][3];
    }

    for(i1=0,i2=5*36;i1<36;i1++,i2++){
        vertices_fondo[i2][0]=cara_fondo[i1][1];
        vertices_fondo[i2][1]=-cara_fondo[i1][0];
        vertices_fondo[i2][2]=cara_fondo[i1][2];
        vertices_fondo[i2][3]=cara_fondo[i1][3];
    }

    //Inicializamos los vertices de la cara.
    VECTOR cara[36];
    for(i=0;i<36;i++)
    {
        cara[i][0] = cuad[i%4][0];
        cara[i][1] = cuad[i%4][1] - 10 * ((i/4)%3);
        cara[i][2] = cuad[i%4][2] - 10 * ((i/12)%3);
        cara[i][3] = cuad[i%4][3];
    }

    for(i1=0,i2=0;i1<36;i1++,i2++)
        for(j=0;j<4;j++)
            vertices[i2][j]=cara[i1][j];

    for(i1=0,i2=36;i1<36;i1++,i2++){
        vertices[i2][0]=-cara[i1][0];
        vertices[i2][1]=cara[i1][1];
        vertices[i2][2]=cara[i1][2];
        vertices[i2][3]=cara[i1][3];
    }

    for(i1=0,i2=2*36;i1<36;i1++,i2++){
        vertices[i2][0]=cara[i1][1];
        vertices[i2][1]=cara[i1][2];
        vertices[i2][2]=cara[i1][0];
        vertices[i2][3]=cara[i1][3];
    }

    for(i1=0,i2=3*36;i1<36;i1++,i2++){
        vertices[i2][0]=cara[i1][1];
        vertices[i2][1]=cara[i1][2];
        vertices[i2][2]=-cara[i1][0];
        vertices[i2][3]=cara[i1][3];
    }

    for(i1=0,i2=4*36;i1<36;i1++,i2++){
        vertices[i2][0]=cara[i1][1];
        vertices[i2][1]=cara[i1][0];
        vertices[i2][2]=cara[i1][2];
        vertices[i2][3]=cara[i1][3];
    }

    for(i1=0,i2=5*36;i1<36;i1++,i2++){
        vertices[i2][0]=cara[i1][1];
        vertices[i2][1]=-cara[i1][0];
        vertices[i2][2]=cara[i1][2];
        vertices[i2][3]=cara[i1][3];
    }
}

void calcular_vertices_rotados(VECTOR *output, int count, VECTOR *vertices, MATRIX local_screen) {
    asm __volatile__ (
        "lqc2        vf1, 0x00(%3)    \n" // Carga la columna 1 de local_screen en vf1.
        "lqc2        vf2, 0x10(%3)    \n" // Carga la columna 2 de local_screen en vf2.
        "lqc2        vf3, 0x20(%3)    \n" // Carga la columna 3 de local_screen en vf3.
        "lqc2        vf4, 0x30(%3)    \n" // Carga la columna 4 de local_screen en vf4.
        "1:                           \n" // Inicia el loop que recorrera el arreglo de vertices.
        "lqc2        vf6, 0x00(%2)    \n" // Carga vertice en vf6.
        "vmulaw      ACC, vf4, vf0    \n" // Guarda la cuarta columna intacta en acc.
        "vmaddax     ACC, vf1, vf6    \n" // Multiplica la primer columna con la componente x del vector y lo suma a acc.
        "vmadday     ACC, vf2, vf6    \n" // Multiplica la segunda columna con la componente y del vector y lo suma a acc.
        "vmaddaz     ACC, vf3, vf6    \n" // Multiplica la tercera columna con la componente z del vector y lo suma a acc.
                                          // En este punto se encuentra el resultado de la multiplicacion en acc.
        "vmadd.xyz   vf5, vf0, vf0    \n" // Copia el valor las primeras 3 componentes (x,y,z) de ACC en vf5.
        "vaddz.w     vf5, vf0, vf0    \n" // Setea el valor 0 en la cuarta componente (w) de vf5.
        "sqc2        vf5, 0x00(%0)    \n" // Mueve vf5 a output.
        "addi        %0, 0x10         \n" // Avanza uno en output .
        "addi        %2, 0x10         \n" // Avanza uno en vertices.
        "addi        %1, -1           \n" // Resta uno al contador.
        "bne         $0, %1, 1b       \n" // Si no terminó, salta al inicio del loop.
        : : "r" (output), "r" (count), "r" (vertices), "r" (local_screen) : "$10"
    );
}
