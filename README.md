
Ps2Rubik:
=========
 
 Juego para PS2, resolviendo el cubo de rubik.

 Trabajo final de la materia "Arquitectura del computador" LCC.
 
 Alumno: Marcos Pividori.

![](/sound/rubik.png?raw=true)

 Se realizó sobre el entorno ps2dev, usando diferentes librerias, y basándose en
 ejemplos y tests de joysticks, video y audio.

INTRODUCCIÓN:
-------------
 Necesitamos un método que nos permita ejecutar software en la PS2 sin necesidad
 de grabarlo en un CD, ya que esto sería muy costoso.

 Por otro lado, no podemos probar nuestros programas en una computadora común,
 porque constan de una arquitectura totalmente diferente. Para resolver esto,
 haremos uso de dos herramientas clave: un compilador cruzado, que nos permite
 compilar en una PC común codigo para procesadores MIPS, y de un sistema
 cliente-servidor para ejecutar los programas en la consola.

 Como la PlayStation consta de dos microprocesadores MIPS distintos, serán
 necesarios dos compiladores cruzados: ee-gcc y iop-gcc (Se puede también usar
 solo uno, depende el uso que uno quiera hacer de los procesadores).
 
 Una vez compilado el código (ejecutando: make all), para correrlo en la PS2
 presentamos dos opciones:

 - **PS2Client + PS2Link:**
   
   Es un método muy útil y simple, conectando la consola con la pc a través de un
   cable de red, y haciendo uso de dos aplicaciones: Ps2Client en la PC y Ps2Link
   en la PS2.

   *Ps2Link:* es un "bootloader" que, utilizado junto con un controlador Ethernet
   y una pila TCP/IP, permite descargar y ejecutar software en la PS2. Este
   programa se ejecuta en la PS2 a través de un CD con el formato correspondiente
   (el CD está disponible para quien lo necesite).

   *Ps2Client:* es un cliente que nos permite conectarnos con PS2Link y transmitir
   comandos. Se maneja desde la consola de la PC.

   (Ver instrucciones detalladas).

 - **PCSX2:**
   
   *PCSX2* es un emulador para PlayStation2 de código abierto (http://pcsx2.net/). 
   Si no contamos con una PS2 en concreto, podemos ejecutar nuestros programas
   en el emulador sin problemas.
   (Ver instrucciones detalladas).

Finalmente, una vez terminado el proyecto, es posible grabar el programa en un CD
(con el formato correspondiente) y prescindir de estas aplicaciones para
ejecutarlo en la PS2 real.


EJECUTAR EL JUEGO UTILIZANDO PS2CLIENT Y PS2LINK:
-------------------------------------------------
 Si deseamos ejecutar el juego en una PlayStation real:
   + Conectar la PS2 con la computadora a través de un cable de Red.

   + Configurar la red cableada en la PC con:
      - Dirección: 192.168.0.10
      - Máscara de red: 255.255.255.0
      - P. de enlace: 192.168.0.1

   + Encender la PS2 con el cd que contiene el programa Ps2Link.

   + Para correr el programa:
       cd bin
       ps2client -h 192.168.0.102 execee host:run_rubik.elf

   + Para resetear la conexión:
       ps2client -h 192.168.0.102 reset

 Nota: Estas config. para la red son específicas para el cd de ps2link disponible.


EJECUTAR EL JUEGO UTILIZANDO PCSX2:
----------------------------------
 Si deseamos ejecutar el juego en el emulador PCSX2:
   + Descargar e instalar el emulador PCSX2 (http://pcsx2.net/).

   + Configurar los controles del joystick y demás detalles.

   + En Sistema, seleccionar "Activar sistema de archivos del host".
     (Para que nuestros programas puedan ubicar los archivos externos, como ser
      los archivos de audio).

   + Para correr el programa, ir a: "Sistema->Ejecutar Elf", y seleccionar
     el archivo run_rubik.elf en el directorio bin.

   + Si deseamos ver información de la salida estándar, podemos abrir la consola
     en "Otros->Mostrar Consola".


GUÍA DE JUEGO:
-------------

**DEFINIR EL CUBO A RESOLVER:**

 Al inicio, el programa nos da la opcion de ingresar nuestro cubo de rubik,
 es decir, los colores y la distribucion del cubo que tenemos.
 
 - Si solamente queremos jugar con un cubo aleatorio, al inicio pulsamos START
   sin cambiar nada y después con el boton O podemos pedir combinaciones
   aleatorias del cubo para resolver.

 - Si, en cambio, queremos resolver un cubo que tenemos en nuestras manos:
   Al inicio, contamos de un cursor que podemos mover por las diferentes caras
   con L2 y con R2.
   Una vez posicionados sobre el color a cambiar, pulsamos X hasta lograr el
   color deseado.
   Una vez que terminamos de definir nuestro cubo, pulsamos START.


**JUGAR:**
 
 Para mover el cubo, tenemos un "cursor" que nos muestra la cara seleccionada y
 podemos cambiarlo de cara con L1. Una vez decidida la cara, la rotamos con los
 botones CUADRADO en sentido horario y con TRIANGULO en sentido antihorario.

 Si deseamos que el juego nos ayude, podemos pedirle que busque los pasos hacia
 la solución. Para esto, cuenta de 3 mecanismos:
   + Mejor: (Boton X) Tarda más pero da la solucion con menos pasos.
   + Medio: (Boton L1) Es un punto medio entre los dos extremos.
   + Peor: (Boton R1) Tarda poco pero da soluciones de muchos pasos.

 Un vez apretado el boton, se llenará la barra de progreso.
 Una vez terminado, apretando el boton X, el programa nos guiará realizando los
 pasos de la solución. En cualquier momento se puede parar y seguir jugando.
 Pero si uno hace movimientos, y de nuevo quiere ayuda, tendrá que buscar la
 solución nuevamente.

 De igual manera, en cualquier momento se puede apretar el boton O para obtener
 un cubo aleatorio.


**MOVER LA CÁMARA:**
 
 Siempre podemos mover la camara desde donde se ve el cubo usando los controles
 analógicos, o las flechas.



Cualquier consulta, me pueden contactar por email.
