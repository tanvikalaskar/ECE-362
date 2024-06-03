/**
  ******************************************************************************
  * @file    main.c
  * @author  Weili An
  * @version V1.0
  * @date    Oct 24, 2022
  * @brief   ECE 362 Lab 7 template
  ******************************************************************************
*/


#include "stm32f0xx.h"
#include <stdint.h>

// Global data structure
char* login          = "xyz"; // Replace with your login.
char disp[9]         = "Hello...";
uint8_t col          = 0;
uint8_t mode         = 'A';
uint8_t thrust       = 0;
int16_t fuel         = 800;
int16_t alt          = 4500;
int16_t velo         = 0;

// Make them visible to autotest.o
extern char* login;
// Keymap is in `font.S` to match up what autotester expected
extern char keymap;
extern char disp[9];
extern uint8_t col;
extern uint8_t mode;
extern uint8_t thrust;
extern int16_t fuel;
extern int16_t alt;
extern int16_t velo;

char* keymap_arr = &keymap;

// Font array in assembly file
// as I am too lazy to convert it into C array
extern uint8_t font[];

// The functions we should implement
void enable_ports();
void setup_tim6();
void show_char(int n, char c);
void drive_column(int c);
int read_rows();
char rows_to_key(int rows);
void handle_key(char key);
void setup_tim7();
void write_display();
void update_variables();
void setup_tim14();

// Auotest functions
extern void check_wiring();
extern void autotest();
extern void fill_alpha();

int main(void) {
    // check_wiring();
    autotest();
    // fill_alpha();
    enable_ports();
    setup_tim6();
    setup_tim7();
    setup_tim14();

    for(;;) {
        asm("wfi");
    }
}

/**
 * @brief Enable the ports and configure pins as described
 *        in lab handout
 * 
 */
void enable_ports(){
    RCC -> AHBENR |= RCC_AHBENR_GPIOCEN;
    RCC -> AHBENR |= RCC_AHBENR_GPIOBEN;
    GPIOB -> MODER &= ~0x003fffff;
    GPIOB -> MODER |=  0x00155555;

    GPIOC -> MODER &= ~0x0003ff00;
    GPIOC -> MODER |=  0x00015500;

    GPIOC ->MODER &=  ~0x000000ff;

    GPIOC->PUPDR &=  ~0x000000ff;
    GPIOC -> PUPDR |= 0x000000AA;


}

//-------------------------------
// Timer 6 ISR goes here
//-------------------------------
// TODO
 void TIM6_DAC_IRQHandler() {
     TIM6 -> SR &= ~TIM_SR_UIF;


     if((GPIOC -> ODR)  >> 8 == 1) {
         GPIOC -> BRR = 1 << 8;
     }
     else{
         GPIOC -> BSRR = 1 << 8;

     }
 }

/**
 * @brief Set up timer 6 as described in handout
 * 
 */
void setup_tim6() {
    RCC -> APB1ENR |= RCC_APB1ENR_TIM6EN;
    TIM6 -> PSC = 48000 - 1;
    TIM6 -> ARR = 500 - 1;
    TIM6 -> DIER = TIM_DIER_UIE;
    TIM6 -> CR1 |= TIM_CR1_CEN;
    NVIC_EnableIRQ(TIM6_DAC_IRQn);
}

/**
 * @brief Show a character `c` on column `n`
 *        of the segment LED display
 * 
 * @param n 
 * @param c 
 */
void show_char(int n, char c) {
    if (n >= 0 && n <=7){
        GPIOB -> ODR = font[c];
        GPIOB -> ODR  |= (n << 8);
    }

}

/**
 * @brief Drive the column pins of the keypad
 *        First clear the keypad column output
 *        Then drive the column represented by `c`
 * 
 * @param c 
 */
void drive_column(int c) {
    c &= 0x3;
    GPIOC -> BRR |= 0x00f0;

    GPIOC -> BSRR |= 1 <<(c+4);


}

/**
 * @brief Read the rows value of the keypad
 * 
 * @return int 
 */
int read_rows() {
    return GPIOC -> IDR & 0xf;


}

/**
 * @brief Convert the pressed key to character
 *        Use the rows value and the current `col`
 *        being scanning to compute an offset into
 *        the character map array
 * 
 * @param rows 
 * @return char 
 */
char rows_to_key(int rows) {
    uint8_t h = 0;
       if(rows == 0x1){
           h = 0;
       }
       if(rows == 0x2){
           h = 1;

       }

       if(rows == 0x4){
                 h = 2;
             }
       if(rows == 0x8){
                 h = 3;
             }
      uint8_t o = h + (col *4);
      return keymap_arr[o];

}


/**
 * @brief Handle key pressed in the game
 * 
 * @param key 
 */
void handle_key(char key) {
    if ( key == 'A' || key == 'B'|| key == 'D'){
        mode = key;
    }
    else{
        thrust = key - 48;
    }

}

//-------------------------------
// Timer 7 ISR goes here
//-------------------------------
// TODO
void TIM7_IRQHandler (){


TIM7 -> SR &= ~TIM_SR_UIF;

    int r = read_rows();
    if (r!= 0){
        char a = rows_to_key(r);
        handle_key(a);
    }
    show_char(col,disp[col]);
    col = col+1;
    if (col > 7){
        col = 0;
    }

   drive_column(col); }

/**
 * @brief Setup timer 7 as described in lab handout
 * 
 */
void setup_tim7() {

    RCC -> APB1ENR |= RCC_APB1ENR_TIM7EN;
     TIM7 -> PSC = 480 - 1;
     TIM7 -> ARR = 100 - 1;
     TIM7-> DIER = TIM_DIER_UIE;
     TIM7 -> CR1 |= TIM_CR1_CEN;
     NVIC_EnableIRQ(TIM7_IRQn);

}

/**
 * @brief Write the display based on game's mode
 * 
 */
void write_display() {
    if (mode == 'C'){
        snprintf(disp,9,"Crashed");
    }

    if (mode == 'L'){
          snprintf(disp,9,"Landed ");
      }

    if (mode == 'A'){
            snprintf(disp,9,"ALt%5d", alt);
        }
    if (mode == 'B'){
               snprintf(disp,9,"FUEL %3d", fuel);
           }
    if (mode == 'D'){
                   snprintf(disp,9,"Spd %4d", velo);
               }

}

/**
 * @brief Game logic
 * 
 */
void update_variables() {
  fuel = fuel -thrust;
  if(fuel <= 0){
      thrust = 0;
      fuel = 0;
  }
  alt = alt + velo;
  if (alt <= 0){
   if (-velo < 10){
      mode = 'L';
  }
   else{
      mode = 'C';
  }
  return;
}
 velo = velo + (thrust - 5);
}

//-------------------------------
// Timer 14 ISR goes here
//-------------------------------
// TODO
void TIM14_IRQHandler()  {
    TIM14 -> SR &= ~TIM_SR_UIF;

    update_variables();
    write_display();
}

/**
 * @brief Setup timer 14 as described in lab
 *        handout
 * 
 */
void setup_tim14() {
       RCC -> APB1ENR |= RCC_APB1ENR_TIM14EN;
       TIM14 -> PSC = 48000 - 1;
       TIM14 -> ARR = 500 - 1;
       TIM14-> DIER&= TIM_DIER_UIE;
       TIM14-> CR1 |= TIM_CR1_CEN;
       NVIC_EnableIRQ(TIM14_IRQn);

}
