#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#include "radioenge_modem.h"
#include "main.h"
#include "uartRingBufDMA.h"

//testando
extern osTimerId_t PeriodicSendTimerHandle;
extern osThreadId_t AppSendTaskHandle;
extern ADC_HandleTypeDef hadc1;
extern osEventFlagsId_t ModemStatusFlagsHandle;
extern TIM_HandleTypeDef htim3;
extern osMessageQueueId_t TemperatureQueueHandle;
char msg[256];


void LoRaWAN_RxEventCallback(uint8_t *data, uint32_t length, uint32_t port, int32_t rssi, int32_t snr)
{

}

void PeriodicSendTimerCallback(void *argument)
{
}



void ReadTempTaskCode(void *argument)
{

uint32_t read;
TEMPERATURE_OBJ_t data;
data.seq_no=0;
while (1){

    //read LM35 Temperature
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 100);
    read = HAL_ADC_GetValue(&hadc1);
    data.seq_no = data.seq_no + 1;
    data.temp_oCx100 = (int32_t)(33000 * ((float)read / 4096));

    // Send Message
    osMessageQueuePut(TemperatureQueueHandle, &data, 0U, osWaitForever);
    osDelay(200);   
    }
}


void AppSendTaskCode(void *argument)
{
    /* USER CODE BEGIN 5 */
    /* Infinite loop */    
    


    TEMPERATURE_OBJ_t rcv_data;
    osStatus_t status;

    while (1)
    {

        status = osMessageQueueGet(TemperatureQueueHandle, &rcv_data, NULL,osWaitForever);  // wait for message
        if (status == osOK)
        {

            sprintf (msg, "Temperature reading %d: %d.%d oC\n",rcv_data.seq_no, rcv_data.temp_oCx100/100, rcv_data.temp_oCx100%100);
                
            SendToUART(msg, strlen(msg));
        }
    }
}




void BlueLedTaskCode(void *argument){

    while(1){
        HAL_GPIO_TogglePin(LED4_BLUE_GPIO_Port,LED4_BLUE_Pin) ;
        osDelay (50) ; // Espera 50 ms)
    }
}

void GreenLedTaskCode(void *argument){

    while(1){
        HAL_GPIO_TogglePin(LED3_GREEN_GPIO_Port,LED3_GREEN_Pin) ;
        osDelay (50) ; // Espera 50 ms)
    }
}

void YellowLedTaskCode(void *argument){

    while(1){
        HAL_GPIO_TogglePin(LED2_YELLOW_GPIO_Port,LED2_YELLOW_Pin) ;
        osDelay (50) ; // Espera 50 ms)
    }
}

void RedLedTaskCode(void *argument){

    while(1){
        HAL_GPIO_TogglePin(LED1_RED_GPIO_Port,LED1_RED_Pin) ;
        osDelay (50) ; // Espera 50 ms)
    }
}


