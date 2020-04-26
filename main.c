#include <gb/gb.h>
#include <stdio.h>
#include "carinha.c"
#include "background.c"
#include "background_sprite.c"

//declaração de variaveis globais
int pulando = 0;
int posicaoXPlayer = 20;
int posicaoYPlayer = 135;

//declaração das funções
void cair();
void pular();
void iniciarHardware();
void executarControle();
int  retornarAlturaChao();

//função principal
void main() {
    iniciarHardware();

    //sprite background
    set_bkg_data(0,6,background_sprite);
    set_bkg_tiles(0,0,45,18,background);
    SHOW_BKG;

    //sprite player
    set_sprite_data(0,2,carinha);
    set_sprite_tile(0,0);
    move_sprite(0,posicaoXPlayer,posicaoYPlayer);
    SHOW_SPRITES;

	while(1) {

        //gravidade
        cair();

        if(posicaoXPlayer >= 1000) { //100
            scroll_bkg(10,0);
        } else if(posicaoXPlayer <= -200) { //-20
            scroll_bkg(-10,0);
        } else {
            executarControle();
        }
        delay(80);
    }
}

void iniciarHardware() {
	DISPLAY_ON;		    // Liga Display
	NR52_REG = 0x8F;	// Liga Som
	NR51_REG = 0x11;	// Ativa canal de audio
	NR50_REG = 0x77;	// Volume no maximo
}

void cair() {
    if(retornarAlturaChao() > posicaoYPlayer) {
        posicaoYPlayer+=5;
        move_sprite(0,posicaoXPlayer,posicaoYPlayer);
    }
    if(posicaoYPlayer==135){
        pulando=0;
    }
}

void pular() {
    pulando++;
    if(posicaoYPlayer > 90 && pulando < 10) {
        posicaoYPlayer-=10;
    }
}

void executarControle() {
    switch (joypad()) {
        case J_LEFT:
            if(posicaoXPlayer>=10){
                posicaoXPlayer-=5;
            }
            break;
        case J_LEFT + J_B:
            pular();
            if(posicaoXPlayer>=10){
                posicaoXPlayer-=5;
            }
            break;
        case J_RIGHT:
            posicaoXPlayer+=5;
            break;
        case J_RIGHT + J_B:
            pular();
            posicaoXPlayer+=5;
            break;
        case J_B:
            pular();
            break;
        case J_A:
            printf("%d\n",posicaoXPlayer); 
            break;
    }
    move_sprite(0,posicaoXPlayer,posicaoYPlayer);
}

int retornarAlturaChao() {
    return 135;
}