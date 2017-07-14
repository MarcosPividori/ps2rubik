
#ifndef __JOYSTICKS__
#define __JOYSTICKS__

#define ROM_PADMAN

#if defined(ROM_PADMAN) && defined(NEW_PADMAN)
#error Only one of ROM_PADMAN & NEW_PADMAN should be defined!
#endif

#if !defined(ROM_PADMAN) && !defined(NEW_PADMAN)
#error ROM_PADMAN or NEW_PADMAN must be defined!
#endif

#include "libpad.h"

void loadModules();

int waitPadReady(int port, int slot);

int initializePad(int port, int slot);

void init_joystick();

u32 get_joystick_state();

unsigned char get_analogico_derecha_h();

unsigned char get_analogico_derecha_v();

unsigned char get_analogico_izquierda_h();

unsigned char get_analogico_izquierda_v();

void init_small_engine();

void stop_small_engine();

#endif                          // __JOYSTICKS__
