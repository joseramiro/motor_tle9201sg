#ifndef PLIB_TLE9201SG_SPI_H
#define PLIB_TLE9201SG_SPI_H

/**
 * @file plib_tle9201sg_spi.h
 * @brief Pilote SPI pour le TLE9201SG (driver de moteur DC)
 * @author Ramiro Najera
 * @version 1.0.1
 * @date 2025-04-24
 * @copyright Copyright (c) 2025
 */

#include "libs/common_c_libs/plib_comm_struct.h"

/**
 * @brief Écrit des données dans le TLE9201SG via SPI.
 * @param spi Pointeur vers la configuration SPI utilisée pour la communication.
 * @param data Pointeur vers les données à envoyer.
 */
void TLE9201SG_Write(SPI_t *spi, unsigned char* data);

/**
 * @brief Lit des données depuis le TLE9201SG via SPI.
 * @param spi Pointeur vers la configuration SPI utilisée pour la communication.
 * @param data Pointeur vers la variable où stocker les données lues.
 */
void TLE9201SG_Read(SPI_t *spi, unsigned char* data);

/**
 * @brief Effectue une opération d'écriture/lecture combinée sur le TLE9201SG.
 * @param spi Pointeur vers la configuration SPI utilisée pour la communication.
 * @param reg Registre à lire/écrire.
 * @param readData Pointeur vers la variable où stocker les données lues.
 */
void TLE9201SG_WriteRead(SPI_t *spi, unsigned char reg, unsigned char* readData);

#endif  // PLIB_TLE9201SG_SPI_H
