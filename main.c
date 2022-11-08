#include "stm32f0xx.h"
#include <stdint.h>
#include <stdlib.h>
#include "lcd.h"

void setup_tim17()
{
    // Set this to invoke the ISR 100 times per second.
    RCC->APB2ENR |= RCC_APB2ENR_TIM17EN;

    TIM17->PSC = 48000 - 1;
    TIM17->ARR = 100 - 1;

    TIM17->DIER |= TIM_DIER_UIE;

    TIM17->CR1 |= TIM_CR1_CEN;

    NVIC->ISER[0] = 1 << TIM17_IRQn;

}

void setup_portb()
{
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN | RCC_AHBENR_GPIOBEN;
    GPIOB->MODER &= ~0xffff;
    GPIOB->MODER |= 0x55;

    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR4;
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR5;
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR6;
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR7;
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR4_1;
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR5_1;
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR6_1;
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR7_1;
    GPIOC->MODER &= ~0x3FFFFF;
    GPIOC->MODER |= 0x155555;

}

char check_key()
{
    GPIOB->BRR = 1<<3;
    GPIOB->BSRR = 1<<0;
    if ((GPIOB->IDR >> 4) & 1)
        return '1';
    else if ((GPIOB->IDR >> 5) & 1)
        return '2';
    else if ((GPIOB->IDR >> 6) & 1)
        return '3';
    else if ((GPIOB->IDR >> 7) & 1)
        return 'A';

    GPIOB->BRR = 1<<0;
    GPIOB->BSRR = 1<<1;
    if ((GPIOB->IDR >> 4) & 1)
        return '4';
    else if ((GPIOB->IDR >> 5) & 1)
        return '5';
    else if ((GPIOB->IDR >> 6) & 1)
        return '6';
    else if ((GPIOB->IDR >> 7) & 1)
            return 'B';

    GPIOB->BRR = 1<<1;
    GPIOB->BSRR = 1<<2;
    if ((GPIOB->IDR >> 4) & 1)
        return '7';
    else if ((GPIOB->IDR >> 5) & 1)
        return '8';
    else if ((GPIOB->IDR >> 6) & 1)
        return '9';
    else if ((GPIOB->IDR >> 7) & 1)
            return 'C';

    GPIOB->BRR = 1<<2;
    GPIOB->BSRR = 1<<3;
    if ((GPIOB->IDR >> 4) & 1)
        return '*';
    else if ((GPIOB->IDR >> 5) & 1)
        return '0';
    else if ((GPIOB->IDR >> 6) & 1)
        return '#';
    else if ((GPIOB->IDR >> 7) & 1)
            return 'D';
    else
        return 0;


    // If the '*' key is pressed, return '*'
    // If the 'D' key is pressed, return 'D'
    // Otherwise, return 0
}

void setup_spi1()
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    GPIOA->MODER &= ~(0x3FFFFFF);
    GPIOA->MODER |= 0x8A50;
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    SPI1->CR1 &= ~(SPI_CR1_BR);
    SPI1->CR1 |= SPI_CR1_MSTR;
    SPI1->CR1 |= SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE;
    SPI1->CR2 = SPI_CR2_NSSP | SPI_CR2_SSOE | SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0;
    SPI1->CR1 |= SPI_CR1_SPE;

}


extern const Picture background; // A 240x320 background image
extern const Picture xcross; // A 19x19 purple ball with white boundaries
extern const Picture ocircle;

int i = 0;

void TIM17_IRQHandler(void)
{
    TIM17->SR &= ~TIM_SR_UIF;
    char key = check_key();
    if (key == '1' & i < 1)
    {
        LCD_DrawPicture(7, 10, &xcross);
        i++;
    }
    else if (key == '1' & i > 0)
    {
        LCD_DrawPicture(7,10,&ocircle);
        i--;
    }
    if (key == '2' & i < 1)
    {
        LCD_DrawPicture(90, 10, &xcross);
        i++;
    }
    else if (key == '2' & i > 0)
        {
            LCD_DrawPicture(90,10,&ocircle);
            i--;
        }
    if (key == '3' & i < 1)
    {
        LCD_DrawPicture(168, 10, &xcross);
        i++;
    }
    else if (key == '3' & i > 0)
        {
            LCD_DrawPicture(168,10,&ocircle);
            i--;
        }
    if (key == '4' & i < 1)
    {
        LCD_DrawPicture(7, 112, &xcross);
        i++;
    }
    else if (key == '4' & i > 0)
        {
            LCD_DrawPicture(7,112,&ocircle);
            i--;
        }
    if (key == '5' & i < 1)
    {
        LCD_DrawPicture(90, 112, &xcross);
        i++;
    }
    else if (key == '5' & i > 0)
        {
            LCD_DrawPicture(90,112,&ocircle);
            i--;
        }
    if (key == '6' & i < 1)
    {
        LCD_DrawPicture(168, 112, &xcross);
        i++;
    }
    else if (key == '6' & i > 0)
        {
            LCD_DrawPicture(168,112,&ocircle);
            i--;
        }
    if (key == '7' & i < 1)
    {
        LCD_DrawPicture(7, 217, &xcross);
        i++;
    }
    else if (key == '7' & i > 0)
        {
            LCD_DrawPicture(7,217,&ocircle);
            i--;
        }
    if (key == '8' & i < 1)
    {
        LCD_DrawPicture(90, 217, &xcross);
        i++;
    }
    else if (key == '8' & i > 0)
    {
        LCD_DrawPicture(90,217,&ocircle);
        i--;
    }
    if (key == '9' & i < 1)
    {
        LCD_DrawPicture(168, 217, &xcross);
        i++;
    }
    else if (key == '9' & i > 0)
    {
            LCD_DrawPicture(168,217,&ocircle);
            i--;
    }





}

int main(void)
{
    setup_portb();
    setup_spi1();
    LCD_Init();

    // Draw the background.
    LCD_DrawPicture(0,0,&background);


    // Center the 19x19 ball into center of the 29x29 object.
    // Now, the 19x19 ball has 5-pixel white borders in all directions.
    //pic_overlay(object,5,5,&ball,0xffff);

    setup_tim17();
}

