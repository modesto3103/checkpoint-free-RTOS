#include <stdio.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

SemaphoreHandle_t xBinarySemaphore1 = NULL;
SemaphoreHandle_t xBinarySemaphore2 = NULL;
SemaphoreHandle_t xBinarySemaphore3 = NULL;

void Task1(void *pvParameters)
{
    while (1) 
    {
        if(xSemaphoreTake(xBinarySemaphore1, portMAX_DELAY) == pdTRUE) 
        {

            printf("[Tarefa 1] Executou - Pedro Modesto Mesquita   |   RM 87880\n");
            vTaskDelay(pdMS_TO_TICKS(1000)); 
            xSemaphoreGive(xBinarySemaphore2);

        }
    }
}

void Task2(void *pvParameters)
{
    while (1) 
    {
        if(xSemaphoreTake(xBinarySemaphore2, portMAX_DELAY) == pdTRUE) 
        {

            printf("[Tarefa 2] Executou - Pedro Modesto Mesquita   |   RM 87880\n");
            vTaskDelay(pdMS_TO_TICKS(1000)); 
            xSemaphoreGive(xBinarySemaphore3);

        }
    }
}

void Task3(void *pvParameters)
{
    while (1) 
    {
        if(xSemaphoreTake(xBinarySemaphore3, portMAX_DELAY) == pdTRUE) 
        {

            printf("[Tarefa 3] Executou - Pedro Modesto Mesquita   |   RM 87880\n");
            vTaskDelay(pdMS_TO_TICKS(1000)); 
            xSemaphoreGive(xBinarySemaphore1);

        }
    }
}

void app_main(void)
{
    xBinarySemaphore1 = xSemaphoreCreateBinary(); // Cria um semáforo binário
    xBinarySemaphore2 = xSemaphoreCreateBinary(); // Cria um semáforo binário  
    xBinarySemaphore3 = xSemaphoreCreateBinary(); // Cria um semáforo binário  

    if (xBinarySemaphore1 == NULL || xBinarySemaphore2 == NULL || xBinarySemaphore3 == NULL) 
    {
        printf("Falha ao criar semáforo binário\n");
        return;
    }
    
    xTaskCreate(Task1, // Função da task
                "Task1", // Nome da task
                2048, // Stack size em bytes
                NULL, // Parâmetros da task
                5, // Prioridade da task
                NULL /* Handle da task (opcional) */ );

    xTaskCreate(Task2, // Função da task
                "Task2", // Nome da task
                2048, // Stack size em bytes
                NULL, // Parâmetros da task
                5, // Prioridade da task
                NULL /* Handle da task (opcional) */ );

    xTaskCreate(Task3, // Função da task
                "Task3", // Nome da task
                2048, // Stack size em bytes
                NULL, // Parâmetros da task
                5, // Prioridade da task
                NULL /* Handle da task (opcional) */ );

    xSemaphoreGive(xBinarySemaphore1);

}
