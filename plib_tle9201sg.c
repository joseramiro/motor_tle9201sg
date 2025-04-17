/**
 * @file plib_tle9201sg.c
 * @brief Pilote du pont H TLE9201SG
 * @author Ramiro Najera
 * @version 1.0.0
 * @date 2025-04-24
 * @copyright Copyright (c) 2025
 */

#include "plib_tle9201sg.h"
#include "plib_tle9201sg_spi.h"

void TLE9201SG_StartTranmission(SPI_t *spi)
{
    spi->cs.clear();
}

void TLE9201SG_EndTranmission(SPI_t *spi)
{
    spi->cs.set();
}

void TLE9201SG_Enable(TLE9201SG_t* obj)
{
    obj->dis.clear();
}

void TLE9201SG_Disable(TLE9201SG_t* obj)
{
    obj->dis.set();
}

void TLE9201SG_SetPWM(TLE9201SG_t* obj, unsigned int value)
{
    obj->set_pwm(value);
}

unsigned int TLE9201SG_GetPWM(TLE9201SG_t* obj) 
{
    return obj->get_pwm();
}

void TLE9201SG_SetFrequency(TLE9201SG_t* obj, unsigned int frequency)
{
    obj->set_freq(frequency);
}

unsigned int TLE9201SG_GetFrequency(TLE9201SG_t *obj)
{
    return obj->get_freq();
}

void TLE9201SG_SetDir(TLE9201SG_t* obj, unsigned char direction)
{
    // Set direction
    if(direction == TLE9201SG_DIRECTION_FORWARD)
        obj->dir.set();
    else if (direction == TLE9201SG_DIRECTION_BACKWARD)
        obj->dir.clear();
}

void TLE9201SG_Init(TLE9201SG_t* obj)
{
    TLE9201SG_SetPWM(obj, 0);
    TLE9201SG_Disable(obj);
    //todo: other init params ?
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

void TLE9201SG_StartMotor(TLE9201SG_t* obj, unsigned char direction)
{
    TLE9201SG_SetDir(obj, direction);
    TLE9201SG_Enable(obj);
}

void TLE9201SG_StopMotor(TLE9201SG_t* obj)
{
    TLE9201SG_Disable(obj);
}