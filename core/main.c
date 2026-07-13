#include "freeRTOS/include/FreeRTOS.h"
#include "freeRTOS/include/task.h"
#include "stdio.h"
// #include "lib/uart.h"

static uint32_t Task_Stack_Size = 2 * 1024;
static TaskHandle_t task1_handle;

void task1_handle_function( void *pvParameters);

void delay(volatile int t)
{
    while(t--) {
        for(volatile int i=0;i<1000;i++);
    }
}

int main(void)
{

    // uart1_init();

    xTaskCreate(task1_handle_function, "Task1", Task_Stack_Size, NULL, 1, &task1_handle);

    vTaskStartScheduler();
}


void task1_handle_function( void *pvParameters)
{
    while(1) {
        printf("hello\r\n");
        delay(1000);
    }
}
