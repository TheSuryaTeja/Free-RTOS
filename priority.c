#include "TM4C123.h"                    // Device header
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#define SYS_CTRL_RCGC2  (*((volatile unsigned long *)0x400FE108))   //offset of RCGC2 register is 0x108
#define CLK_GPIOF   0x20;
TaskHandle_t myTaskHandle0 = NULL;
TaskHandle_t myTaskHandle1 = NULL;
TaskHandle_t myTaskHandle2 = NULL;

void delay(int time) {
	for (int i = 0 ; i < time; i++) {
		for (int j = 0 ; j < 99999; j++) {
			
		}
	}
	
}

void vPeriodicTask0 () {
	GPIOF->DATA = 0x02;//red
	delay(50);
	vTaskDelete(myTaskHandle0);
}
void vPeriodicTask1 (void *p) {
	GPIOF->DATA = 0x04; //blue
	delay(50);
	vTaskDelete(myTaskHandle1);
}
void vPeriodicTask2 (void *p) {
	GPIOF->DATA = 0x08; //green
	delay(50);
	vTaskDelete(myTaskHandle2);
}
int main () {
	while (1) {
   SYS_CTRL_RCGC2 |= CLK_GPIOF
   GPIOF->DIR |= 0x0000000E;    //set PF1, PF2, PF3 as output
   GPIOF->DEN |= 0x0E;    //enable PF1, PF2, PF3
   GPIOF->DATA = 0x0;
	xTaskCreate(vPeriodicTask0, "some name", 200, NULL, 1, NULL);
	xTaskCreate(vPeriodicTask1, "name", 200, NULL, 2, NULL);	
	xTaskCreate(vPeriodicTask2, "so name", 200, NULL, 3, NULL);
	
	vTaskStartScheduler();
	}
	return 0;
}