
/**
 * @brief QMC5883 sample code
 * 
 */
#include "main.h"
#include "QMC5883.h"


I2C_HandleTypeDef hi2c1;

QMC_HandleTypedef	qmc_sensor;

int main(void)
{
    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_I2C1_Init();
    /* Initialize QMC Sensor */
    QMC5883_Init(&qmc_sensor, &hi2c1, QMC_Rate_50);

    while(1)
    {
        /*read QMC5883 ================================*/
        if(QMC5883_ReadAverage(&qmc_sensor,Max_QMC_AverageCount,1) == QMC_OK)
        {
            printf("$CMP,%d,%d,%d,%03.2f*",qmc_sensor.xaxis,qmc_sensor.yaxis,qmc_sensor.zaxis,qmc_sensor.avg_heading);
        }
        /*end read QMC5883 ================================*/
        HAL_Delay(100);
    }
}


