#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#include "radioenge_modem.h"
#include "termistor.h"

extern osTimerId_t PeriodicSendTimerHandle;
extern osThreadId_t AppSendTaskHandle;
extern ADC_HandleTypeDef hadc1;
extern osEventFlagsId_t ModemStatusFlagsHandle;
extern TIM_HandleTypeDef htim3;


void LoRaWAN_RxEventCallback(uint8_t *data, uint32_t length, uint32_t port, int32_t rssi, int32_t snr)
{

}

void PeriodicSendTimerCallback(void *argument)
{
}

    typedef struct {
    uint32_t seq_no;
    int32_t temp_oCx100;
    } __attribute__((packed)) TEMPERATURE_OBJ_t;

void AppSendTaskCode(void *argument)
{
    /* USER CODE BEGIN 5 */
    /* Infinite loop */    
    
        
    uint32_t read;
    TEMPERATURE_OBJ_t temp;
    temp.seq_no = 0;



    while (1)
    {
        HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, 100);
        read = HAL_ADC_GetValue(&hadc1);
        temp.seq_no++;
        temp.temp_oCx100 = DividerVoltageToDegreesCelsius(3300,(3300.0*read / 4095.0))*100;
        /*sprintf(sendStr,"Temperature: %2d.%2d",temp/100,temp%100);*/
        
        LoRaSendB(2, (uint8_t *)&temp, sizeof(TEMPERATURE_OBJ_t));

        osDelay(15000);
    }

    
}
