/*
 * QMC5883.h
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

#ifndef SRC_QMC5883L_QMC5883_H_
#define SRC_QMC5883L_QMC5883_H_

#include "main.h"

#define QMC_I2C_Address		0x1A

#define QMC_OK			1
#define QMC_ERR			0

#define qmc_stanby		0
#define qmc_continus	1


typedef enum
{
	QMC_Rate_200 = 0,
	QMC_Rate_100 = 1,
	QMC_Rate_50 = 2,
	QMC_Rate_10	= 3,
}QMC_DataRate_t;

/*Hardware abstract ======*/
typedef struct
{
	I2C_HandleTypeDef *i2c;
	uint8_t 		  ctl_reg;
	uint8_t			  data[6];
	int16_t			  xaxis;
	int16_t		 	  yaxis;
	int16_t			  zaxis;
	float 			  heading;
	float 			  compass;

	float 			  avg_heading;
	float 		      avg_compass;
}QMC_HandleTypedef;


uint8_t QMC5883_Init(QMC_HandleTypedef *qmc, I2C_HandleTypeDef *i2c, QMC_DataRate_t data_rate);
uint8_t QMC5883_ReadAverage(QMC_HandleTypedef *qmc, uint32_t maxAvrage, uint32_t timePerAvg);
uint8_t QMC5883_Read(QMC_HandleTypedef *qmc);
float   QMC5883_ReadHeading(QMC_HandleTypedef *qmc);
uint8_t QMC5883_Standby(QMC_HandleTypedef *qmc);
uint8_t QMC5883_Reset(QMC_HandleTypedef *qmc);




#endif /* SRC_QMC5883L_QMC5883_H_ */
