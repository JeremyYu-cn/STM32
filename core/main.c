#include "freeRTOS/include/FreeRTOS.h"
#include "freeRTOS/include/task.h"
#include "lib/uart.h"

static uint32_t Task_Stack_Size = 1024;
static TaskHandle_t task1_handle;

void task1_handle_function( void *pvParameters);

int main(void)
{

    uart1_init();

    uart_puts("main start\r\n");

    xTaskCreate(task1_handle_function, "Task1", Task_Stack_Size, NULL, 1, &task1_handle);

    vTaskStartScheduler();
}


void task1_handle_function( void *pvParameters)
{
    while(1) {
        uart_log("Task1", "hello\r\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
