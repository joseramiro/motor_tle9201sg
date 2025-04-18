/**
 * @file plib_tle9201sg_spi.c
 * @brief Pilote SPI pour le TLE9201SG (driver de moteur DC)
 * @author Ramiro Najera
 * @version 1.0
 * @date 2025-03-18
 */

#include "plib_tle9201sg_spi.h"
#include "peripheral/spi/spi_master/plib_spi1_master.h"
#include "peripheral/spi/spi_master/plib_spi2_master.h"

/* ==== Fonctions SPI ==== */

void TLE9201SG_Write(SPIConfiguration_t *spi, unsigned char* data)
{
    if(spi->channel == SPI_CH1)
        SPI1_Write(data, 1);
    else if(spi->channel == SPI_CH2)
        SPI2_Write(data, 1);
}

void TLE9201SG_Read(SPIConfiguration_t *spi, unsigned char* data)
{
    if(spi->channel == SPI_CH1)
        SPI1_Read(data, 1);
    else if(spi->channel == SPI_CH2)
        SPI2_Read(data, 1);
}

void TLE9201SG_WriteRead(SPIConfiguration_t *spi, unsigned char reg, unsigned char* readData)
{
    TLE9201SG_Write(spi, &reg);
    TLE9201SG_Read(spi, readData);
}