/**
 * @file plib_tle9201sg.c
 * @brief Pilote du pont H TLE9201SG
 * @author Ramiro Najera
 * @version 1.0
 * @date 2025-03-18
 */

#include "plib_tle9201sg.h"
#include "plib_tle9201sg_spi.h"

void TLE9201SG_StartTranmission(SPIConfiguration_t *spi)
{
    spi->cs_clear();    //Schedule_IO_Exp_Update_Pot_CS(module, 0);   
}

void TLE9201SG_EndTranmission(SPIConfiguration_t *spi)
{
    spi->cs_set();  //Schedule_IO_Exp_Update_Pot_CS(module, 1);
}

void TLE9201SG_Enable(TLE9201SGConf_t* conf)
{
    conf->dis_clear();  //Schedule_IO_Exp_Update_Pot_DIS(module, 0);
}

void TLE9201SG_Disable(TLE9201SGConf_t* conf)
{
    conf->dis_set();    //Schedule_IO_Exp_Update_Pot_DIS(module, 1);
}

void TLE9201SG_SetPWM(TLE9201SGConf_t* conf, unsigned int value)
{
    conf->set_pwm(value);
}

unsigned int TLE9201SG_GetPWM(TLE9201SGConf_t* conf) 
{
    return conf->get_pwm();
}

void TLE9201SG_SetFrequency(TLE9201SGConf_t* conf, unsigned int frequency)
{
    conf->set_freq(frequency);
}

unsigned int TLE9201SG_GetFrequency(TLE9201SGConf_t *conf)
{
    return conf->get_freq();
}

void TLE9201SG_SetDir(TLE9201SGConf_t* conf, unsigned char direction)
{
    // Set direction
    if(direction == TLE9201SG_DIRECTION_FORWARD)
        conf->dir_fw();
    else if (direction == TLE9201SG_DIRECTION_BACKWARD)
        conf->dir_bw();
}

void TLE9201SG_Init(TLE9201SGConf_t* conf)
{
    TLE9201SG_SetPWM(conf, 0);
    TLE9201SG_Disable(conf);
    //todo: other init params ?
}

void TLE9201SG_ReadRegister(TLE9201SGConf_t* conf, unsigned char reg, unsigned char* data)
{
    TLE9201SG_StartTranmission(&conf->spi);
    TLE9201SG_WriteRead(&conf->spi, reg, data);
    TLE9201SG_EndTranmission(&conf->spi);
}

void TLE9201SG_ReadVersionReg(TLE9201SGConf_t* conf, unsigned char* data)
{
    TLE9201SG_ReadRegister(conf, TLE9201SG_REG_RD_REV, data);
}

void TLE9201SG_ReadControlReg(TLE9201SGConf_t* conf, unsigned char* control)
{
    TLE9201SG_ReadRegister(conf, TLE9201SG_REG_RD_CTRL, control);
}

void TLE9201SG_ReadDiagnosisReg(TLE9201SGConf_t* conf, unsigned char* status)
{
    TLE9201SG_ReadRegister(conf, TLE9201SG_REG_RD_DIA, status);
}

void TLE9201SG_StartMotor(TLE9201SGConf_t* conf, unsigned char direction)
{
    TLE9201SG_SetDir(conf, direction);
    TLE9201SG_Enable(conf);
}

void TLE9201SG_StopMotor(TLE9201SGConf_t* conf)
{
    TLE9201SG_Disable(conf);
}