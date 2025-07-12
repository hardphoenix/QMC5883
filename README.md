# QMC5883 Compass Library For STM32

## Description
The **QMC5883** is a 3-axis compass sensor with a heading accuracy of 1 degree. It is highly useful for various commercial and automotive applications requiring precise heading detection.

## How to Use

1. Configure your I2C peripheral to operate at **100 kHz**.
2. Note that the I2C address of the chip is defined in the file `QMC5883.h` as:
   ```c
   #define QMC_I2C_Address 0x1A
   ```
3. This code is developed and tested for the QMC5883 sensor and works correctly.

## Example Code
Below is an example of how to integrate and use the QMC5883 library in your STM32 project:

```c
#include "main.h"
#include "QMC5883.h"

I2C_HandleTypeDef hi2c1;

QMC_HandleTypedef qmc_sensor;

int main(void)
{
    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_I2C1_Init();

    /* Initialize QMC Sensor */
    QMC5883_Init(&qmc_sensor, &hi2c1, QMC_Rate_50);

    while(1)
    {
        /* Read QMC5883 */
        if(QMC5883_ReadAverage(&qmc_sensor, Max_QMC_AverageCount, 1) == QMC_OK)
        {
            printf("$CMP,%d,%d,%d,%03.2f*", qmc_sensor.xaxis, qmc_sensor.yaxis, qmc_sensor.zaxis, qmc_sensor.avg_heading);
        }
        /* End read QMC5883 */
        HAL_Delay(100);
    }
}
```

## Features
- 3-axis heading detection.
- Compatible with STM32 HAL I2C library.
- Tested and verified for QMC5883.

## License
This project is open-source and available under the MIT License.

---

Feel free to contribute to this project by submitting issues or pull requests!
---
---
