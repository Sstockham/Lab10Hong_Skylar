/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"

//Header file created to use definitions of led_pin() and read_char()
#include "blink.h"

int count = 0;
bool on = false;

//Defines task priority 
#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define BLINK_TASK_PRIORITY     ( tskIDLE_PRIORITY + 2UL )

//Defines the task size to be minimal in stack memory
#define MAIN_TASK_STACK_SIZE    configMINIMAL_STACK_SIZE
#define BLINK_TASK_STACK_SIZE   configMINIMAL_STACK_SIZE

void blink_task(__unused void *params) {
    hard_assert(cyw43_arch_init() == PICO_OK);
    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);
        if (count++ % 11) on = !on;
        vTaskDelay(500);
    }
}

void main_task(__unused void *params) {
    xTaskCreate(blink_task, "BlinkThread",
                BLINK_TASK_STACK_SIZE, NULL, BLINK_TASK_PRIORITY, NULL);   
    char c;
    while(c = getchar()) {
        if (c <= 'z' && c >= 'a') putchar(c - 32);
        else if (c >= 'A' && c <= 'Z') putchar(c + 32);
        else putchar(c);
    }
}


//Main Function
int main( void )
{
    //Initializing USB
    stdio_init_all();
    const char *rtos_name;
    rtos_name = "FreeRTOS";

    //Creating a instance of structure for tskTaskControlBlock which is assigned to typedef struct TaskHandle_t
    TaskHandle_t task;

    //xTaskCreate, take function name, task size and task priority.
    xTaskCreate(main_task, "MainThread",
                MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &task);

    //Starts the task created and runs.            
    vTaskStartScheduler();
    return 0;
}