#include "freeRTOS/include/FreeRTOS.h"
#include "freeRTOS/include/task.h"
#include "lib/uart.h"
#include "lib/base/rcc.h"
#include "lib/base/gpio.h"

static uint32_t Task_Stack_Size = 1024;
static TaskHandle_t task1_handle;

void task1_handle_function(void *pvParameters);

int main(void)
{

    struct rcc_enable_peripheral_config rcc_gpio_config = {
        .rcc_base = &RCC_APB2ENR,
        .peripheral = RCC_APB2ENR_IOPC
    };

    rcc_enable_peripheral(&rcc_gpio_config);

    uart1_init();

    uart_puts("main start\r\n");


    uart_puts("GPIOC clock enabled\r\n");

    struct gpio_config led_config = {
        .gpio_base = GPIOC_BASE,
        .pin = GPIO_PIN_13,
        .mode = GPIO_MODE_OUTPUT_2MHZ
    };

    gpio_init(&led_config);

    uart_puts("GPIOC pin 13 configured as output\r\n");

    BaseType_t res = xTaskCreate(task1_handle_function, "Task1", Task_Stack_Size, NULL, 1, &task1_handle);

    if (res != pdPASS)
    {
        uart_log("ERROR", "Task creation failed\r\n");
    }
    else
    {
        uart_log("INFO", "Starting scheduler\r\n");
    }

    vTaskStartScheduler();

    uart_log("ERROR", "Scheduler failed to start\r\n");
}

void task1_handle_function(void *pvParameters)
{
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
        uart_log("INFO", "Task1 is running\r\n");
        // gpio_set_pin(GPIOC_BASE, GPIO_PIN_13, GPIO_BIT_HIGH);
        vTaskDelay(pdMS_TO_TICKS(1000));
        gpio_set_pin(GPIOC_BASE, GPIO_PIN_13, GPIO_BIT_LOW);
    }
}
