#ifndef BUTTON_H
#define BUTTON_H
#include "main.h"

typedef struct
{
	 uint8_t button_current;
	 uint8_t button_last;
	 uint8_t button_filter;
	 uint8_t is_debounding;
	 uint8_t is_holdpress;
	 uint32_t time_debound;
	 uint32_t time_press_at;
	 GPIO_TypeDef *GPIOx;
   uint16_t GPIO_Pin;
}Button_Typdef;

void button_handle(Button_Typdef* Buttonx);
void button_init(Button_Typdef* Buttonx, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#endif

