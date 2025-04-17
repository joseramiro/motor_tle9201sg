#ifndef PLIB_TLE9201SG_H
#define PLIB_TLE9201SG_H

/**
 * @file plib_tle9201sg.h
 * @brief Pilote du pont H TLE9201SG
 * @author Ramiro Najera
 * @version 1.0.0
 * @date 2025-04-24
 * @copyright Copyright (c) 2025
 */

#include "libs/common_c_libs/plib_comm_struct.h"

/** 
 * @defgroup TLE9201SG_Registers Registres du TLE9201SG
 * @brief Définitions des registres du composant TLE9201SG utilisés pour la communication SPI.
 * @{
 */
/** @brief Registre de diagnostic (lecture) */
#define TLE9201SG_REG_RD_DIA            0x00
/** @brief Registre de reset du diagnostic */
#define TLE9201SG_REG_RES_DIA           0x80
/** @brief Registre de révision (lecture) */
#define TLE9201SG_REG_RD_REV            0x20
/** @brief Registre de contrôle (lecture) */
#define TLE9201SG_REG_RD_CTRL           0x60
/** @brief Registre de contrôle (écriture) */
#define TLE9201SG_REG_WR_CTRL           0xE0
/** @brief Registre combiné de contrôle et diagnostic (lecture) */
#define TLE9201SG_REG_WR_CTRL_RD_DIA    0xC0
/** @} */ // Fin du groupe TLE9201SG_Registers

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
 * @struct TLE9201SG_t
 * @brief Configuration du pont H TLE9201SG
 * Cette structure regroupe les paramètres de configuration nécessaires pour un module TLE9201SG,
 * incluant les fonctions de contrôle GPIO et la configuration SPI.
 */
typedef struct
{
    /** @brief Identifiant du module */
    unsigned char id;
    /** @brief Fonction pour piloter la broche DIS (disabled) */
    GPIO_t dis;
    /** @brief Fonction pour piloter la broche DIR (direction) */
    GPIO_t dir;
    /** @brief Fonction pour définir la valeur du PWM */
    void(*set_pwm)(unsigned int);
    /** @brief Fonction pour récupérer la valeur actuelle du PWM */
    unsigned int(*get_pwm)(void);
    /** @brief Fonction pour définir la fréquence du PWM */
    void(*set_freq)(unsigned int);
    /** @brief Fonction pour récupérer la valeur actuelle du PWM */
    unsigned int(*get_freq)(void);
    /** @brief Configuration SPI associée au module */
    SPI_t spi;
}TLE9201SG_t;

/**
 * @brief Démarre une transmission SPI avec le module TLE9201SG.
 * @param spi Pointeur vers la configuration SPI utilisée pour la communication.
 */
void TLE9201SG_StartTranmission(SPI_t *spi);

/**
 * @brief Termine une transmission SPI avec le module TLE9201SG.
 * @param spi Pointeur vers la configuration SPI utilisée pour la communication.
 */
void TLE9201SG_EndTranmission(SPI_t *spi);

/**
 * @brief Active le module TLE9201SG.
 * @param obj Pointeur vers la structure de configuration du module.
 */
void TLE9201SG_Enable(TLE9201SG_t* obj);

/**
 * @brief Désactive le module TLE9201SG.
 * @param obj Pointeur vers la structure de configuration du module.
 */
void TLE9201SG_Disable(TLE9201SG_t* obj);

/**
 * @brief Définit la valeur du signal PWM pour le contrôle du moteur.
 * @param obj Pointeur vers la structure de configuration du module.
 * @param value Valeur du PWM (0 - 100%).
 */
void TLE9201SG_SetPWM(TLE9201SG_t* obj, unsigned int value);

/**
 * @brief Récupère la valeur actuelle du signal PWM.
 * @param obj Pointeur vers la structure de configuration du module.
 * @return Valeur actuelle du PWM.
 */
unsigned int TLE9201SG_GetPWM(TLE9201SG_t* obj);

/**
 * @brief Définit la valeur de fréquence du signal PWM pour le contrôle du moteur
 * @param obj Pointeur vers la structure de configuration du module
 * @param frequency Fréquence en Hz
 */
void TLE9201SG_SetFrequency(TLE9201SG_t* obj, unsigned int frequency);

/**
 * @brief Récupère la valeur de frésuence du signal PWM
 * @param obj Pointeur vers la structure de configuration du module
 * @return unsigned int Valeur actuelle de fréquence en Hz
 */
unsigned int TLE9201SG_GetFrequency(TLE9201SG_t *obj);

/**
 * @brief Initialise le module TLE9201SG avec la configuration fournie.
 * @param obj Pointeur vers la structure de configuration du module.
 */
void TLE9201SG_Init(TLE9201SG_t* obj);

void TLE9201SG_ReadRegister(TLE9201SG_t* obj, unsigned char reg, unsigned char* data);

/**
 * @brief Lit la version du firmware ou de la puce TLE9201SG.
 * @param obj Pointeur vers la structure de configuration du module.
 * @param data Pointeur vers la variable où stocker la version lue.
 */
void TLE9201SG_ReadVersionReg(TLE9201SG_t* obj, unsigned char* data);

/**
 * @brief Lit le registre de contrôle du TLE9201SG.
 * @param obj Pointeur vers la structure de configuration du module.
 * @param control Pointeur vers la variable où stocker la valeur du registre de contrôle.
 */
void TLE9201SG_ReadControlReg(TLE9201SG_t* obj, unsigned char* control);

/**
 * @brief Lit le registre d'état du TLE9201SG.
 * @param obj Pointeur vers la structure de configuration du module.
 * @param status Pointeur vers la variable où stocker l'état du dispositif.
 */
void TLE9201SG_ReadDiagnosisReg(TLE9201SG_t* obj, unsigned char* status);

/**
 * @brief Définit la direction de rotation du moteur.
 * @param obj Pointeur vers la structure de configuration du module.
 * @param direction Direction du moteur (TLE9201SG_DIRECTION_FORWARD ou TLE9201SG_DIRECTION_BACKWARD).
 */
void TLE9201SG_SetDir(TLE9201SG_t* obj, unsigned char direction);

/**
 * @brief Démarre le moteur dans la direction spécifiée.
 * @param obj Pointeur vers la structure de configuration du module.
 * @param direction Direction du moteur (TLE9201SG_DIRECTION_FORWARD ou TLE9201SG_DIRECTION_BACKWARD).
 */
void TLE9201SG_StartMotor(TLE9201SG_t* obj, unsigned char direction);

/**
 * @brief Arrête le moteur.
 * @param obj Pointeur vers la structure de configuration du module.
 */
void TLE9201SG_StopMotor(TLE9201SG_t* obj);

#endif  // PLIB_TLE9201SG_H
