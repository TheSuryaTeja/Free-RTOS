#include "TM4C123.h"                    // Device header
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#define SYS_CTRL_RCGC2  (*((volatile unsigned long *)0x400FE108))   //offset of RCGC2 register is 0x108
#define CLK_GPIOF   0x20;
#include "queue.h"                      // ARM.FreeRTOS::RTOS:Core

TaskHandle_t myTaskHandle0 = NULL;
TaskHandle_t myTaskHandle1 = NULL;
TaskHandle_t myTaskHandle2 = NULL;
xQueueHandle Global_Queue_Handle = NULL;

void delay(int time) {
	for (int i = 0 ; i < time; i++) {
		for (int j = 0 ; j < 99999; j++) {
			
		}
	}
	
}

// 02 red
// 04 green
// 08 blue

void vPeriodicTask0 () {
	unsigned int my_send_data = 0x04;
	while (1) {
		xQueueSend(Global_Queue_Handle, &my_send_data,1000);
		GPIOF->DATA = 0x02; //red
		delay(30);
		}
  }
void vPeriodicTask1 (void *p) {
	unsigned int my_recieve_data;
	while (1) {
		if(xQueueReceive(Global_Queue_Handle, &my_recieve_data,1000))
			GPIOF->DATA = my_recieve_data;
			delay(30);
		
		GPIOF->DATA = 0x08;	//blue
		delay(30);
		}
}

int main () {
	while (1) {
   SYS_CTRL_RCGC2 |= CLK_GPIOF
   GPIOF->DIR |= 0x0000000E;    //set PF1, PF2, PF3 as output
   GPIOF->DEN |= 0x0E;    //enable PF1, PF2, PF3
   GPIOF->DATA = 0x0;
		Global_Queue_Handle = xQueueCreate(1, 3*sizeof(int));
	xTaskCreate(vPeriodicTask0, "some name", 200, NULL, 1, NULL);
	xTaskCreate(vPeriodicTask1, "name", 200, NULL, 2, NULL);	
	vTaskStartScheduler();
	}
	return 0;
}