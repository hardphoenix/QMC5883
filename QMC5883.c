/*
 * QMC8583.c
 *
 *  Created on: Dec 9, 2024
 *
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This File Part Of QMC5883 3-Axis Compass Sensor Library.
 * Port For STM32 MicroController With HAL Library.
 *
 *	Author: Mohammad Hosein Taheri
 *	gmail: etatosel@gmail.com
 *
 * Versoin: 0.9
 */



#include "QMC5883.h"
#include <math.h>


uint8_t QMC5883_Init(QMC_HandleTypedef *qmc, I2C_HandleTypeDef *i2c, QMC_DataRate_t data_rate)
{
	uint8_t array[2];
	qmc->i2c = i2c;
	qmc->ctl_reg = 0x11;
	array[0] = 1;
	array[1] = qmc->ctl_reg;

	if(data_rate == QMC_Rate_200)qmc->ctl_reg |= 0b00001100;
	else if(data_rate == QMC_Rate_100)qmc->ctl_reg |= 0b00001000;
	else if(data_rate == QMC_Rate_50)qmc->ctl_reg |= 0b00000100;
	else if(data_rate == QMC_rate_10)qmc->ctl_reg |= 0b00000000;
	else qmc->ctl_reg |= 0b00001100;

	if(HAL_I2C_Mem_Write(qmc->i2c, QMC_I2C_Address, 0x0B, 1, &array[0], 1, 100) != HAL_OK)return QMC_ERR;
	if(HAL_I2C_Mem_Write(qmc->i2c, QMC_I2C_Address, 0x09, 1, &array[1], 1, 100) != HAL_OK)return QMC_ERR;

	return QMC_OK;
}


uint8_t QMC5883_Read(QMC_HandleTypedef *qmc)
{
	qmc->data[0] = 0; 	//clear data index 0
	HAL_I2C_Mem_Read(qmc->i2c, QMC_I2C_Address, 0x06, 1, qmc->data, 1, 100);

	/*data ready for read =========*/
	if((qmc->data[0] & 0x01) == 1)
	{
		HAL_I2C_Mem_Read(qmc->i2c, QMC_I2C_Address, 0x00, 1, qmc->data, 6, 100);
		qmc->xaxis = (qmc->data[1]<<8) | qmc->data[0];
		qmc->yaxis = (qmc->data[3]<<8) | qmc->data[2];
		qmc->zaxis = (qmc->data[5]<<8) | qmc->data[4];

		qmc->compass = atan2f(qmc->yaxis,qmc->xaxis) * 180.00/M_PI;
		if(qmc->compass > 0)
		{
			qmc->heading = qmc->compass;
		}
		else
		{
			qmc->heading = 360 + qmc->compass;
		}
	}
	else
	{
		return QMC_ERR;
	}
	return QMC_OK;
}



uint8_t QMC5883_ReadAverage(QMC_HandleTypedef *qmc, uint32_t maxAvrage, uint32_t timePerAvg)
{
	int i;
	float avg = 0.00f;
	avg = (float)maxAvrage;
	float avgH = 0.00f;
	float avgC = 0.00f;

	for (i=0; i < maxAvrage; i++)
	{
		QMC5883_ReadHeading(qmc);
		avgC += qmc->avg_compass;
		avgH += qmc->heading;

		sysdelay(timePerAvg);
	}
	qmc->avg_heading = avgH / avg;
	qmc->avg_compass = avgC / avg;

	return QMC_OK;
}


float   QMC5883_ReadHeading(QMC_HandleTypedef *qmc)
{
	QMC5883_Read(qmc);
	return qmc->heading;
}


uint8_t QMC5883_Standby(QMC_HandleTypedef *qmc)
{
	uint8_t array[1] = {0};
	if(HAL_I2C_Mem_Read(qmc->i2c, QMC_I2C_Address, 0x09, 1, &array[0], 1, 100) != HAL_OK)return QMC_ERR;
	return QMC_OK;
}


uint8_t QMC5883_Reset(QMC_HandleTypedef *qmc)
{
	uint8_t array[1]= {0};
	if(HAL_I2C_Mem_Read(qmc->i2c, QMC_I2C_Address, 0x0A, 1, &array[0], 1, 100) != HAL_OK)return QMC_ERR;
	return QMC_OK;
}

