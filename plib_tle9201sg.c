/**
 * @file plib_tle9201sg.c
 * @brief Pilote du pont H TLE9201SG
 * @author Ramiro Najera
 * @version 1.0.4
 * @date 2025-04-24
 * @copyright Copyright (c) 2025
 */

#include "plib_tle9201sg.h"

/** 
 * @enum TLE9201SGDirections_t
 * @brief Définit les directions de rotation du moteur.
 */
typedef enum
{
    /** @brief Direction avant (forward) */
    TLE9201SG_DIRECTION_FORWARD,
    /** @brief Direction arrière (backward) */
    TLE9201SG_DIRECTION_BACKWARD
}TLE9201SGDirections_t;

/**
 * @enum TLE9201SGRegisters_t
 * @brief Définit les registres SPI
 */
typedef enum
{
    /** @brief Registre de diagnostic (lecture) */
    TLE9201SG_REG_RD_DIA = 0x00,
    /** @brief Registre de reset du diagnostic */
    TLE9201SG_REG_RES_DIA = 0x80,
    /** @brief Registre de révision (lecture) */
    TLE9201SG_REG_RD_REV = 0x20,
    /** @brief Registre de contrôle (lecture) */
    TLE9201SG_REG_RD_CTRL = 0x60,
    /** @brief Registre de contrôle (écriture) */
    TLE9201SG_REG_WR_CTRL = 0xE0,
    /** @brief Registre combiné de contrôle et diagnostic (lecture) */
    TLE9201SG_REG_WR_CTRL_RD_DIA = 0xC0
}TLE9201SGRegisters_t;

// Static functions

static void Write(SPI_t *spi, uint8_t* data)
{
    if(spi->Write)
        spi->Write(data, 1);
}

static void Read(SPI_t *spi, uint8_t* data)
{
    if(spi->Read)
        spi->Read(data, 1);
}

static void WriteRead(SPI_t *spi, uint8_t reg, uint8_t* readData)
{
    Write(spi, &reg);
    Read(spi, readData);
}

static void StartTranmission(SPI_t *spi)
{
    if(spi->pinEN.Clear)
        spi->pinEN.Clear();
    if(spi->pinCS.Clear) 
        spi->pinCS.Clear();
}

static void EndTranmission(SPI_t *spi)
{
    if(spi->pinCS.Set)
        spi->pinCS.Set();
    if(spi->pinEN.Set)
        spi->pinEN.Set();
}

void ReadRegister(TLE9201SG_t* obj, uint8_t reg, uint8_t* data)
{
    StartTranmission(&obj->spi);
    WriteRead(&obj->spi, reg, data);
    EndTranmission(&obj->spi);
}

static void Enable(TLE9201SG_t* obj)
{
    if(obj->pinDIS.Clear)
        obj->pinDIS.Clear();
}

static void Disable(TLE9201SG_t* obj)
{
    if(obj->pinDIS.Set)
        obj->pinDIS.Set();
}

static void SetDirection(TLE9201SG_t* obj, uint8_t direction)
{
    // Set direction
    if(obj->pinDIR.Set && direction == TLE9201SG_DIRECTION_FORWARD)
        obj->pinDIR.Set();
    else if (obj->pinDIR.Set && direction == TLE9201SG_DIRECTION_BACKWARD)
        obj->pinDIR.Clear();
}

static void Move(TLE9201SG_t* obj, const uint8_t direction, const uint8_t pwm)
{
    SetDirection(obj, direction);
    obj->SetPwm(pwm);
    Enable(obj);
}

static void SetPWM(TLE9201SG_t* obj, const uint16_t value)
{
    if(obj->SetPwm)
        obj->SetPwm(value);
}

// Public API

void TLE9201SG_Init(TLE9201SG_t* obj)
{
    SetPWM(obj, 0);
    Disable(obj);
}

void TLE9201SG_InitList(TLE9201SG_t *objList, const uint8_t size, const uint16_t frequency)
{ 
    // Init each TLE9201SG module
    for(uint8_t i = 0; i < size; i++)
    {
        TLE9201SG_Init(&objList[i]);
    }
    // Set frequency (one module is enough)
    TLE9201SG_SetFrequency(&objList[0], frequency);
}

void TLE9201SG_SetFrequency(TLE9201SG_t* obj, const uint16_t frequency)
{
    if(obj->SetFrequency != NULL)
        obj->SetFrequency(frequency);
}

uint16_t TLE9201SG_GetFrequency(TLE9201SG_t *obj)
{
    if(obj->GetFrequency != NULL)
        return obj->GetFrequency();
    return 0;
}

void TLE9201SG_ReadVersionReg(TLE9201SG_t* obj, uint8_t* data)
{
    ReadRegister(obj, TLE9201SG_REG_RD_REV, data);
}

void TLE9201SG_ReadControlReg(TLE9201SG_t* obj, uint8_t* control)
{
    ReadRegister(obj, TLE9201SG_REG_RD_CTRL, control);
}

void TLE9201SG_ReadDiagnosisReg(TLE9201SG_t* obj, uint8_t* status)
{
    ReadRegister(obj, TLE9201SG_REG_RD_DIA, status);
}

void TLE9201SG_MoveForward(TLE9201SG_t* obj, const uint8_t pwm)
{
    Move(obj, TLE9201SG_DIRECTION_FORWARD ,pwm);
}

void TLE9201SG_MoveBackward(TLE9201SG_t* obj, const uint8_t pwm)
{
    Move(obj, TLE9201SG_DIRECTION_BACKWARD ,pwm);
}

void TLE9201SG_Stop(TLE9201SG_t* obj)
{
    Disable(obj);
    obj->SetPwm(0);
}