/**
 * @file plib_tle9201sg.c
 * @brief Pilote du pont H TLE9201SG
 * @author Ramiro Najera
 * @version 1.0.4
 * @date 2025-04-24
 * @copyright Copyright (c) 2025
 */

#include <stddef.h>
#include "plib_tle9201sg.h"
#include "plib_tle9201sg_spi.h"

void TLE9201SG_StartTranmission(SPI_t *spi)
{
    if(spi->pinEN.Clear != NULL)
        spi->pinEN.Clear();
    if(spi->pinCS.Clear != NULL) 
        spi->pinCS.Clear();
}

void TLE9201SG_EndTranmission(SPI_t *spi)
{
    if(spi->pinCS.Set != NULL)
        spi->pinCS.Set();
    if(spi->pinEN.Set != NULL)
        spi->pinEN.Set();
}

void TLE9201SG_Enable(TLE9201SG_t* obj)
{
    if(obj->pinDIS.Clear != NULL)
        obj->pinDIS.Clear();
}

void TLE9201SG_Disable(TLE9201SG_t* obj)
{
    if(obj->pinDIS.Set != NULL)
        obj->pinDIS.Set();
}

void TLE9201SG_SetPWM(TLE9201SG_t* obj, unsigned int value)
{
    if(obj->SetPwm != NULL)
        obj->SetPwm(value);
}

unsigned int TLE9201SG_GetPWM(TLE9201SG_t* obj) 
{
    if(obj->GetPwm != NULL)
        return obj->GetPwm();
    return 0;
}

void TLE9201SG_SetFrequency(TLE9201SG_t* obj, unsigned int frequency)
{
    if(obj->SetFrequency != NULL)
        obj->SetFrequency(frequency);
}

unsigned int TLE9201SG_GetFrequency(TLE9201SG_t *obj)
{
    if(obj->GetFrequency != NULL)
        return obj->GetFrequency();
    return 0;
}

void TLE9201SG_SetDir(TLE9201SG_t* obj, unsigned char direction)
{
    // Set direction
    if(obj->pinDIR.Set != NULL && direction == TLE9201SG_DIRECTION_FORWARD)
        obj->pinDIR.Set();
    else if (obj->pinDIR.Set != NULL && direction == TLE9201SG_DIRECTION_BACKWARD)
        obj->pinDIR.Clear();
}

void TLE9201SG_Init(TLE9201SG_t* obj)
{
    TLE9201SG_SetPWM(obj, 0);
    TLE9201SG_Disable(obj);
}

void TLE9201SG_InitList(TLE9201SG_t *objList, unsigned char size, unsigned int frequency)
{ 
    // Init each TLE9201SG module
    for(unsigned char i = 0; i < size; i++)
    {
        TLE9201SG_Init(&objList[i]);
    }
    // Set frequency (one module is enough)
    TLE9201SG_SetFrequency(&objList[0], frequency);
}

void TLE9201SG_ReadRegister(TLE9201SG_t* obj, unsigned char reg, unsigned char* data)
{
    TLE9201SG_StartTranmission(&obj->spi);
    TLE9201SG_WriteRead(&obj->spi, reg, data);
    TLE9201SG_EndTranmission(&obj->spi);
}

void TLE9201SG_ReadVersionReg(TLE9201SG_t* obj, unsigned char* data)
{
    TLE9201SG_ReadRegister(obj, TLE9201SG_REG_RD_REV, data);
}

void TLE9201SG_ReadControlReg(TLE9201SG_t* obj, unsigned char* control)
{
    TLE9201SG_ReadRegister(obj, TLE9201SG_REG_RD_CTRL, control);
}

void TLE9201SG_ReadDiagnosisReg(TLE9201SG_t* obj, unsigned char* status)
{
    TLE9201SG_ReadRegister(obj, TLE9201SG_REG_RD_DIA, status);
}

void TLE9201SG_StartMotor(TLE9201SG_t* obj, unsigned char direction, unsigned char pwm)
{
    TLE9201SG_SetDir(obj, direction);
    obj->SetPwm(pwm);
    TLE9201SG_Enable(obj);
}

void TLE9201SG_StopMotor(TLE9201SG_t* obj)
{
    TLE9201SG_Disable(obj);
    obj->SetPwm(0);
}