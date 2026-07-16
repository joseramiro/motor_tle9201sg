#ifndef PLIB_TLE9201SG_H
#define PLIB_TLE9201SG_H

/**
 * @file plib_tle9201sg.h
 * @brief Pilote du pont H TLE9201SG
 * @author Ramiro Najera
 * @version 1.0.4
 * @date 2025-04-24
 * @copyright Copyright (c) 2025
 */

#include <stdint.h>
#include "libs/common_c_libs/plib_comm_struct.h"

/**
 * @struct TLE9201SG_t
 * @brief Configuration du pont H TLE9201SG
 * Cette structure regroupe les paramètres de configuration nécessaires pour un module TLE9201SG,
 * incluant les fonctions de contrôle GPIO et la configuration SPI.
 */
typedef struct
{
    /** @brief Identifiant du module */
    uint8_t id;
    /** @brief Fonction pour piloter la broche DIS (disabled) */
    GPIO_t pinDIS;
    /** @brief Fonction pour piloter la broche DIR (direction) */
    GPIO_t pinDIR;
    /** @brief Fonction pour définir la valeur du PWM */
    void(*SetPwm)(uint16_t);
    /** @brief Fonction pour définir la fréquence du PWM */
    void(*SetFrequency)(uint16_t);
    /** @brief Fonction pour récupérer la valeur actuelle du PWM */
    uint16_t(*GetFrequency)(void);
    /** @brief Configuration SPI associée au module */
    SPI_t spi;
}TLE9201SG_t;

// Public API

/**
 * @brief Initialise le module TLE9201SG avec la configuration fournie.
 * @param obj Pointeur vers la structure de configuration du module.
 */
void TLE9201SG_Init(TLE9201SG_t* obj);

/**
 * @brief Initialise une liste de modules TLE9201SG
 * @param objList Liste de modules TLE9201SG
 * @param size Taille de liste
 * @param frequency Frequence de PWM pour toute la liste
 */
void TLE9201SG_InitList(TLE9201SG_t *objList, const uint8_t size, const uint16_t frequency);

/**
 * @brief Définit la valeur de fréquence du signal PWM pour le contrôle du moteur
 * @param obj Pointeur vers la structure de configuration du module
 * @param frequency Fréquence en Hz
 */
void TLE9201SG_SetFrequency(TLE9201SG_t* obj, const uint16_t frequency);

/**
 * @brief Récupère la valeur de frésuence du signal PWM
 * @param obj Pointeur vers la structure de configuration du module
 * @return uint16_t Valeur actuelle de fréquence en Hz
 */
uint16_t TLE9201SG_GetFrequency(TLE9201SG_t *obj);

/**
 * @brief Lit la version du firmware ou de la puce TLE9201SG.
 * @param obj Pointeur vers la structure de configuration du module.
 * @param data Pointeur vers la variable où stocker la version lue.
 */
void TLE9201SG_ReadVersionReg(TLE9201SG_t* obj, uint8_t* data);

/**
 * @brief Lit le registre de contrôle du TLE9201SG.
 * @param obj Pointeur vers la structure de configuration du module.
 * @param control Pointeur vers la variable où stocker la valeur du registre de contrôle.
 */
void TLE9201SG_ReadControlReg(TLE9201SG_t* obj, uint8_t* control);

/**
 * @brief Lit le registre d'état du TLE9201SG.
 * @param obj Pointeur vers la structure de configuration du module.
 * @param status Pointeur vers la variable où stocker l'état du dispositif.
 */
void TLE9201SG_ReadDiagnosisReg(TLE9201SG_t* obj, uint8_t* status);

/**
 * @brief Démarre le moteur dans la direction montante
 * @param obj Pointeur vers la structure de configuration du module
 * @param pwm Vitesse du moteur (PWM)
 */
void TLE9201SG_MoveForward(TLE9201SG_t* obj, const uint8_t pwm);

/**
 * @brief Démarre le moteur dans la direction descendante
 * @param obj Pointeur vers la structure de configuration du module
 * @param pwm Vitesse du moteur (PWM)
 */
void TLE9201SG_MoveBackward(TLE9201SG_t* obj, const uint8_t pwm);

/**
 * @brief Arrête le moteur.
 * @param obj Pointeur vers la structure de configuration du module.
 */
void TLE9201SG_Stop(TLE9201SG_t* obj);

#endif  // PLIB_TLE9201SG_H
