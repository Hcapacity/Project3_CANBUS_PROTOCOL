#include "Button.h"


__weak void btn_release_button_callback(Button_Typdef* Buttonx){
  // Do something
}
__weak void btn_press_hold_button_callback(Button_Typdef* Buttonx){
   // Do something
}
__weak void btn_press_short_button_callback(Button_Typdef* Buttonx){
   // Do something
}
__weak void btn_press_button_callback(Button_Typdef* Buttonx){
   // Do something
}
__weak void led_handle(){
	// Do something
}
void button_init(Button_Typdef* Buttonx, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	Buttonx->GPIOx = GPIOx;
	Buttonx->GPIO_Pin = GPIO_Pin;
	Buttonx->button_current = 0;
	Buttonx->button_last = 0;
	Buttonx->button_filter = 0;
}

void button_handle(Button_Typdef* Buttonx){
	 // -------------fiter noise-----------------
   uint8_t sta = HAL_GPIO_ReadPin(Buttonx->GPIOx, Buttonx->GPIO_Pin);
	 if( sta != Buttonx->button_filter){
		 Buttonx->is_debounding = 1;
		 Buttonx->button_filter = sta;
		 Buttonx->time_debound = HAL_GetTick();
	 }
	 if(Buttonx->is_debounding && HAL_GetTick() - Buttonx->time_debound >= 15){
	    Buttonx->button_current = Buttonx->button_filter;
		  Buttonx->is_debounding = 0;
	 }
	 // --------------handle button------------------
	 
	 //press, release, press-short
	 if(Buttonx->button_current != Buttonx->button_last){
	    if(Buttonx->button_current == 1){
			  Buttonx->button_last = 1;
				btn_press_button_callback(Buttonx);
				Buttonx->time_press_at = HAL_GetTick();
				Buttonx->is_holdpress = 1;
			}
			else{
				Buttonx->button_last = 0;
				if(HAL_GetTick() - Buttonx->time_press_at >= 50){
					btn_press_short_button_callback(Buttonx);
				}
				btn_release_button_callback(Buttonx);
			  Buttonx->is_holdpress = 0;
			}
	 }
	 
	 // --------------hold-press---------------
	 if(Buttonx->is_holdpress && HAL_GetTick() - Buttonx->time_press_at >= 3000){
		 Buttonx->is_holdpress = 0;
		 btn_press_hold_button_callback(Buttonx);
	 }
}


