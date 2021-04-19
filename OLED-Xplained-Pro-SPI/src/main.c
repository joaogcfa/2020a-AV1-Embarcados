#include <asf.h> 

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

//LED1
#define LED1_PIO      PIOA
#define LED1_PIO_ID   ID_PIOA
#define LED1_IDX      0
#define LED1_IDX_MASK (1 << LED1_IDX)

//LED3
#define LED3_PIO      PIOB
#define LED3_PIO_ID   ID_PIOB
#define LED3_IDX      2
#define LED3_IDX_MASK (1 << LED3_IDX)

// Botao 1
#define BUT1_PIO      PIOD
#define BUT1_PIO_ID   ID_PIOD
#define BUT1_IDX  28
#define BUT1_IDX_MASK (1 << BUT1_IDX)

// Botao 2
#define BUT2_PIO      PIOC
#define BUT2_PIO_ID   ID_PIOC
#define BUT2_IDX  31
#define BUT2_IDX_MASK (1 << BUT2_IDX)

//Botao 3
# define BUT3_PIO      PIOA
# define BUT3_PIO_ID   ID_PIOA
# define BUT3_IDX  19
# define BUT3_IDX_MASK (1 << BUT3_IDX)

volatile flag_but1 = 0;
volatile flag_but2 = 0;


void but_callback1(void){
	if(flag_but1 == 0){
		flag_but1 = 1;
	}
	else{
		flag_but1 = 0;
	}
}

void but_callback2(void){
	if(flag_but2 == 0){
		flag_but2 = 1;
	}
	else{
		flag_but2 = 0;
	}
}

void init(void){
	// Initialize the board clock
	sysclk_init();
	board_init();
	delay_init();

	// Desativa WatchDog Timer
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	
	//Inicializa o led
	pmc_enable_periph_clk(LED1_PIO_ID);
	pio_configure(LED1_PIO, PIO_OUTPUT_1, LED1_IDX_MASK, PIO_DEFAULT);
	
	pmc_enable_periph_clk(LED3_PIO_ID);
	pio_configure(LED3_PIO, PIO_OUTPUT_1, LED3_IDX_MASK, PIO_DEFAULT);
	
	//Inicializa o botao como input
	//BOTAO 1
	pmc_enable_periph_clk(BUT1_PIO_ID);
	pio_set_input(BUT1_PIO, BUT1_IDX_MASK,PIO_DEFAULT | PIO_DEBOUNCE);
	pio_set_debounce_filter(BUT1_PIO, BUT1_IDX_MASK, 100);
	
	pio_handler_set(BUT1_PIO,
	BUT1_PIO_ID,
	BUT1_IDX_MASK,
	PIO_IT_RISE_EDGE, // PIO_IT_FALL_EDGE --> Queda
	but_callback1);
	
	pio_enable_interrupt(BUT1_PIO, BUT1_IDX_MASK);
	
	NVIC_EnableIRQ(BUT1_PIO_ID);
	NVIC_SetPriority(BUT1_PIO_ID, 4);
	
	
	
	//BOTAO 2
	pmc_enable_periph_clk(BUT2_PIO_ID);
	pio_set_input(BUT2_PIO, BUT2_IDX_MASK,PIO_DEFAULT | PIO_DEBOUNCE);
	pio_set_debounce_filter(BUT2_PIO, BUT2_IDX_MASK, 100);
	
	pio_handler_set(BUT2_PIO,
	BUT2_PIO_ID,
	BUT2_IDX_MASK,
	PIO_IT_RISE_EDGE, // PIO_IT_FALL_EDGE --> Queda
	but_callback2);
	
	pio_enable_interrupt(BUT2_PIO, BUT2_IDX_MASK);
	
	NVIC_EnableIRQ(BUT2_PIO_ID);
	NVIC_SetPriority(BUT2_PIO_ID, 4);
}

int main (void)
{
	init();

	// Init OLED
	gfx_mono_ssd1306_init();
	
	// Escreve na tela um circulo e um texto
	gfx_mono_draw_filled_circle(20, 16, 16, GFX_PIXEL_SET, GFX_WHOLE);
	gfx_mono_draw_string("mundo", 50,16, &sysfont);

	/* Insert application code here, after the board has been initialized. */
	while(1) {

	}
}
