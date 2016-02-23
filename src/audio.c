
#include <audsrv.h>
#include <loadfile.h>
#include <sifrpc.h>
#include <stdio.h>
#include "audio.h"

// Este código se basa en el ejemplo:
// ps2dev/ps2sdk/samples/rpc/audsrv/playadpcm/playadpcm.c

audsrv_adpcm_t cancion_part1;
audsrv_adpcm_t cancion_part2;
    
void cargar_cancion()
{
    FILE* adpcm;
    int size;
    u8 *buffer;

    SifInitRpc(0); 

    printf("Kicking IRXs\n");
    SifLoadModule("rom0:LIBSD", 0, NULL);

    printf("Loading audsrv\n");
    //SifLoadModule("cdrom0:\\audsrv.irx", 0, NULL);
    SifLoadModule("host:audsrv.irx", 0, NULL);

    audsrv_init();

    //adpcm = fopen("cdrom0:\\aud.adp","r");
    adpcm = fopen("host:aud.adp","r");

    if (adpcm == NULL) {
        printf("No se pudo abrir el archivo\n");
        audsrv_quit();
        return;
    }
    
    size = 1000000;
    buffer = malloc(size);

    audsrv_adpcm_init();
    audsrv_set_volume(MAX_VOLUME);
    
    // Subo la primera parte de la cancion.
    fread(buffer, 1, size, adpcm);
    audsrv_load_adpcm(&cancion_part1, buffer, 1000000);
    
    // Subo la segunda parte de la cancion.
    fseek(adpcm, 1000000, SEEK_SET);
    fread(buffer, 1, 1000000, adpcm);
    audsrv_load_adpcm(&cancion_part2, buffer, 1000000);        
    
    audsrv_play_adpcm(&cancion_part1);

    fclose(adpcm);
    free (buffer);
}

void reiniciar_cancion()
{
    // Reinicio la canción.
    audsrv_stop_audio();
    audsrv_set_volume(MIN_VOLUME);
    audsrv_quit();
    audsrv_init();
    audsrv_play_adpcm(&cancion_part1);
    audsrv_set_volume(MAX_VOLUME);
}
