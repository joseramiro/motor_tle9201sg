#ifndef PLIB_TLE9201SG_H
#define PLIB_TLE9201SG_H

/**
 * @file plib_tle9201sg.h
 * @brief Pilote du pont H TLE9201SG
 * @author Ramiro Najera
 * @version 1.0
 * @date 2025-03-18
 */

#include "libs/common_c_libs/plib_comm_struct.h"

/** 
 * @defgroup TLE9201SG_Registers Registres du TLE9201SG
 * @brief Définitions des registres du composant TLE9201SG utilisés pour la communication SPI.
 * @{
 */
#define TLE9201SG_REG_RD_DIA            0x00  /**< Registre de diagnostic (lecture) */
#define TLE9201SG_REG_RES_DIA           0x80  /**< Registre de reset du diagnostic */
#define TLE9201SG_REG_RD_REV            0x20  /**< Registre de révision (lecture) */
#define TLE9201SG_REG_RD_CTRL           0x60  /**< Registre de contrôle (lecture) */
#define TLE9201SG_REG_WR_CTRL           0xE0  /**< Registre de contrôle (écriture) */
#define TLE9201SG_REG_WR_CTRL_RD_DIA    0xC0  /**< Registre combiné de contrôle et diagnostic (lecture) */
/** @} */ // Fin du groupe TLE9201SG_Registers

/** 
 * @enum TLE9201SGDirections_t
 * @brief Définit les directions de rotation du moteur.
 */
typedef enum
{
    TLE9201SG_DIRECTION_FORWARD,     /**< Direction avant (forward) */
    TLE9201SG_DIRECTION_BACKWARD     /**< Direction arrière (backward) */
}TLE9201SGDirections_t;

/**
 * @struct TLE9201SGConf_t
 * @brief Configuration du pont H TLE9201SG
 * Cette structure regroupe les paramètres de configuration nécessaires pour un module TLE9201SG,
 * incluant les fonctions de contrôle GPIO et la configuration SPI.
 */
typedef struct
{
    unsigned char id;                   /**< Identifiant du module */
    void(*dis_set)(void);               /**< Fonction pour activer la broche DIS (désactivation du driver) */
    void(*dis_clear)(void);             /**< Fonction pour désactiver la broche DIS (activation du driver) */
    void(*dir_fw)(void);                /**< Fonction pour activer la direction avant */
    void(*dir_bw)(void);                /**< Fonction pour activer la direction arrière */
    void(*set_pwm)(unsigned int);       /**< Fonction pour définir la valeur du PWM */
    unsigned int(*get_pwm)(void);       /**< Fonction pour récupérer la valeur actuelle du PWM */
    void(*set_freq)(unsigned int);      /**< Fonction pour définir la fréquence du PWM */
    unsigned int(*get_freq)(void);      /**< Fonction pour récupérer la valeur actuelle du PWM */
    SPI_t spi;               /**< Configuration SPI associée au module */
}TLE9201SGConf_t;

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
 * @param conf Pointeur vers la structure de configuration du module.
 */
void TLE9201SG_Enable(TLE9201SGConf_t* conf);

/**
 * @brief Désactive le module TLE9201SG.
 * @param conf Pointeur vers la structure de configuration du module.
 */
void TLE9201SG_Disable(TLE9201SGConf_t* conf);

/**
 * @brief Définit la valeur du signal PWM pour le contrôle du moteur.
 * @param conf Pointeur vers la structure de configuration du module.
 * @param value Valeur du PWM (0 - 100%).
 */
void TLE9201SG_SetPWM(TLE9201SGConf_t* conf, unsigned int value);

/**
 * @brief Récupère la valeur actuelle du signal PWM.
 * @param conf Pointeur vers la structure de configuration du module.
 * @return Valeur actuelle du PWM.
 */
unsigned int TLE9201SG_GetPWM(TLE9201SGConf_t* conf);

/**
 * @brief Définit la valeur de fréquence du signal PWM pour le contrôle du moteur
 * @param conf Pointeur vers la structure de configuration du module
 * @param frequency Fréquence en Hz
 */
void TLE9201SG_SetFrequency(TLE9201SGConf_t* conf, unsigned int frequency);

/**
 * @brief Récupère la valeur de frésuence du signal PWM
 * @param conf Pointeur vers la structure de configuration du module
 * @return unsigned int Valeur actuelle de fréquence en Hz
 */
unsigned int TLE9201SG_GetFrequency(TLE9201SGConf_t *conf);

/**
 * @brief Initialise le module TLE9201SG avec la configuration fournie.
 * @param conf Pointeur vers la structure de configuration du module.
 */
void TLE9201SG_Init(TLE9201SGConf_t* conf);

void TLE9201SG_ReadRegister(TLE9201SGConf_t* conf, unsigned char reg, unsigned char* data);

/**
 * @brief Lit la version du firmware ou de la puce TLE9201SG.
 * @param conf Pointeur vers la structure de configuration du module.
 * @param data Pointeur vers la variable où stocker la version lue.
 */
void TLE9201SG_ReadVersionReg(TLE9201SGConf_t* conf, unsigned char* data);

/**
 * @brief Lit le registre de contrôle du TLE9201SG.
 * @param conf Pointeur vers la structure de configuration du module.
 * @param control Pointeur vers la variable où stocker la valeur du registre de contrôle.
 */
void TLE9201SG_ReadControlReg(TLE9201SGConf_t* conf, unsigned char* control);

/**
 * @brief Lit le registre d'état du TLE9201SG.
 * @param conf Pointeur vers la structure de configuration du module.
 * @param status Pointeur vers la variable où stocker l'état du dispositif.
 */
void TLE9201SG_ReadDiagnosisReg(TLE9201SGConf_t* conf, unsigned char* status);

/**
 * @brief Définit la direction de rotation du moteur.
 * @param conf Pointeur vers la structure de configuration du module.
 * @param direction Direction du moteur (TLE9201SG_DIRECTION_FORWARD ou TLE9201SG_DIRECTION_BACKWARD).
 */
void TLE9201SG_SetDir(TLE9201SGConf_t* conf, unsigned char direction);

/**
 * @brief Démarre le moteur dans la direction spécifiée.
 * @param conf Pointeur vers la structure de configuration du module.
 * @param direction Direction du moteur (TLE9201SG_DIRECTION_FORWARD ou TLE9201SG_DIRECTION_BACKWARD).
 */
void TLE9201SG_StartMotor(TLE9201SGConf_t* conf, unsigned char direction);

/**
 * @brief Arrête le moteur.
 * @param conf Pointeur vers la structure de configuration du module.
 */
void TLE9201SG_StopMotor(TLE9201SGConf_t* conf);

#endif  // PLIB_TLE9201SG_H
