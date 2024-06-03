/**
  ******************************************************************************
  * @file    main.c
  * @author  Weili An
  * @version V1.0
  * @date    Oct 17, 2022
  * @brief   ECE 362 Lab 6 Student template
  ******************************************************************************
*/


#include "stm32f0xx.h"
#include <stdint.h>

void initc();
void initb();
void togglexn(GPIO_TypeDef *port, int n);
void init_exti();
void set_col(int col);
void SysTick_Handler();
void init_systick();
void adjust_priorities();

extern void nano_wait(int);

volatile int current_col = 1;

int main(void) {
    // Uncomment when most things are working
    // autotest();
    
    initb();
    initc();
    init_exti();
    init_systick();
    adjust_priorities();

    // Slowly blinking
    for(;;) {
        togglexn(GPIOC, 9);
        nano_wait(500000000);
    }
}

/**
 * @brief Init GPIO port C
 *        PC0-PC3 as input pins with the pull down resistor enabled
 *        PC4-PC9 as output pins
 * 
 */
void initc() {
           RCC -> AHBENR |= RCC_AHBENR_GPIOCEN;
           GPIOC -> MODER &= ~0x000fffff;
           GPIOC -> MODER |=  0x00055500;

           GPIOC->PUPDR &=  ~0x000000ff;
           GPIOC -> PUPDR |= 0x000000AA;

}

/**
 * @brief Init GPIO port B
 *        PB0, PB2, PB3, PB4 as input pins
 *          enable pull down resistor on PB2 and PB3
 *        PB8-PB11 as output pins
 * 
 */
void initb() {
    RCC -> AHBENR |= RCC_AHBENR_GPIOBEN;
    GPIOC -> MODER &= ~0x00ff03f3;
    GPIOC -> MODER |=  0x00ff0000;
    GPIOC->PUPDR &=  ~0x000000f0;
    GPIOC -> PUPDR |= 0x000000A0;

}

/**
 * @brief Change the ODR value from 0 to 1 or 1 to 0 for a specified 
 *        pin of a port.
 * 
 * @param port : The passed in GPIO Port
 * @param n    : The pin number
 */
void togglexn(GPIO_TypeDef *port, int n) {
   port -> ODR ^= 1 <<n;

}

//==========================================================
// Write the EXTI interrupt handler for pins 0 and 1 below.
// Copy the name from startup/startup_stm32.s, create a label
// of that name below, declare it to be global, and declare
// it to be a function.
// It acknowledge the pending bit for pin 0, and it should
// call togglexn(GPIOB, 8).

void EXTI0_1_IQHandler(){
    EXTI-> PR |= EXTI_PR_PR0;
    togglexn(GPIOB,8);
}
//==========================================================
// Write the EXTI interrupt handler for pins 2-3 below.
// It should acknowledge the pending bit for pin2, and it
// should call togglexn(GPIOB, 9).
void EXTI2_3_IQHandler(){
    EXTI-> PR |= EXTI_PR_PR2;
    togglexn(GPIOB,9);
}

//==========================================================
// Write the EXTI interrupt handler for pins 4-15 below.
// It should acknowledge the pending bit for pin4, and it
// should call togglxn(GPIOB, 10).
void EXTI4_15_IQHandler(){
    EXTI-> PR |= EXTI_PR_PR4;
    togglexn(GPIOB,10);
}

/**
 * @brief Follow lab manual section 4.4 to initialize EXTI
 *        (1-2) Enable the SYSCFG subsystem, and select Port B for
 *            pins 0, 2, 3, and 4.
 *        (3) Configure the EXTI_RTSR register so that an EXTI
 *            interrupt is generated on the rising edge of
 *            pins 0, 2, 3, and 4.
 *        (4) Configure the EXTI_IMR register so that the EXTI
 *            interrupts are unmasked for pins 2, 3, and 4.
 *        (5) Enable the three interupts for EXTI pins 0-1, 2-3 and
 *            4-15. Don't enable any other interrupts.
 */
void init_exti() {
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;


    SYSCFG -> EXTICR[1] |= SYSCFG_EXTICR1_EXTI0_PB;
    SYSCFG -> EXTICR[0] |= ((SYSCFG_EXTICR1_EXTI0_PB) | (SYSCFG_EXTICR1_EXTI2_PB) | (SYSCFG_EXTICR1_EXTI3_PB));
    EXTI -> RTSR |= ((EXTI_RTSR_TR0) | (EXTI_RTSR_TR1) | (EXTI_RTSR_TR2)|(EXTI_RTSR_TR3) | (EXTI_RTSR_TR4) ) ;
    EXTI -> IMR |= ((EXTI_IMR_MR0) | (EXTI_IMR_MR2)|(EXTI_IMR_MR3)| (EXTI_IMR_MR4));
    NVIC->ISER[0] |= ((0b1000000 ) | (0b1000000 ) | (0b1000000));

}

/**
 * @brief For the keypad pins, 
 *        Set the specified column level to logic "high.
 *        Set the other three three columns to logic "low".
 * 
 * @param col 
 */
void set_col(int col) {
    GPIOC-> ODR &= ~0X00f0;

    GPIOC->ODR |= 0B1 << (8-col);

}

/**
 * @brief The ISR for the SysTick interrupt.
 * 
 */
void SysTick_Handler() {
   int16_t r = GPIOC->IDR & 0xF;
    if(r & (1 < (4-current_col))){
        togglexn(GPIOB,current_col +7);
    }
    current_col = current_col+1;
    if(current_col > 4){
        current_col = 1;

    }
    set_col(current_col);
}

/**
 * @brief Enable the SysTick interrupt to occur every 1/16 seconds.
 * 
 */
void init_systick() {
   SysTick->LOAD = 375000-1;
    SysTick->CTRL &= ~0X7;
    SysTick->CTRL |= 0X3;

}

/**
 * @brief Bonus question
 *        Set the priority for EXTI pins 2-3 interrupt to 192.
 *        Set the priority for EXTI pins 4-15 interrupt to 128.
 *        Do not adjust the priority for any other interrupts.
 * 
 */
void adjust_priorities() {
  NVIC->IP[1] &= 0Xffff0000;
  NVIC->IP[1] |= 0X00c00000;
  NVIC->IP[1] |= 0X80000000;

}
