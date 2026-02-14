/**
 * motor_shield.h
 *
 * Driver per L293D Motor Shield montato su Wemos D1 R1/R2
 * Lo shield si incastra direttamente sulla board (form factor Arduino UNO)
 *
 * Il L293D Motor Shield usa un 74HC595 shift register per controllare
 * le direzioni dei motori, e 2 pin PWM per le velocità.
 *
 * Pin utilizzati dallo shield (standard Arduino):
 *   Pin 4  - LATCH (74HC595 STCP)
 *   Pin 7  - ENABLE (74HC595 OE) - attivo basso
 *   Pin 8  - DATA (74HC595 DS)
 *   Pin 12 - CLOCK (74HC595 SHCP)
 *   Pin 11 - PWM per motori 1 e 2
 *   Pin 3  - PWM per motori 3 e 4
 */

#ifndef MOTOR_SHIELD_H
#define MOTOR_SHIELD_H

#include <Arduino.h>

// ============================================================================
// PIN DELLO SHIELD L293D (standard Arduino, mappati automaticamente su ESP8266)
// ============================================================================

// Pin Shift Register 74HC595
#define MOTOR_LATCH   4     // STCP - Storage Register Clock (Latch)
#define MOTOR_ENABLE  7     // OE - Output Enable (attivo basso)
#define MOTOR_DATA    8     // DS - Serial Data Input
#define MOTOR_CLK     12    // SHCP - Shift Register Clock

// Pin PWM per velocità motori
#define PWM_A         11    // ENA/ENB per motori 1 e 2
#define PWM_B         3     // ENA/ENB per motori 3 e 4

// ============================================================================
// COSTANTI MOTORI
// ============================================================================

// Identificatori motori
#define MOTOR_1     1     // M1 - Anteriore Sinistro
#define MOTOR_2     2     // M2 - Posteriore Sinistro
#define MOTOR_3     3     // M3 - Anteriore Destro
#define MOTOR_4     4     // M4 - Posteriore Destro

// Direzioni
#define FORWARD     1
#define BACKWARD    2
#define RELEASE     3
#define BRAKE       4

// Velocità (ESP8266 usa PWM 10-bit: 0-1023)
#define SPEED_MIN       0
#define SPEED_MAX       1023
#define SPEED_DEFAULT   700

// ============================================================================
// BIT MAPPING SHIFT REGISTER
// ============================================================================
// Il 74HC595 sullo shield AFMotor/L293D mappa così:
//   Bit 1 (0x02) - M1A
//   Bit 2 (0x04) - M1B
//   Bit 3 (0x08) - M2A
//   Bit 4 (0x10) - M2B
//   Bit 5 (0x20) - M4A
//   Bit 6 (0x40) - M4B
//   Bit 0 (0x01) - M3A (attenzione: ordine diverso!)
//   Bit 7 (0x80) - M3B

#define MOTOR1_A    0x04
#define MOTOR1_B    0x08
#define MOTOR2_A    0x02
#define MOTOR2_B    0x10
#define MOTOR3_A    0x01    // Bit 0!
#define MOTOR3_B    0x80    // Bit 7!
#define MOTOR4_A    0x20
#define MOTOR4_B    0x40

// ============================================================================
// CLASSE MOTOR SHIELD
// ============================================================================

class MotorShield {
public:
    /**
     * Costruttore
     */
    MotorShield();

    /**
     * Inizializza i pin e lo shield
     * Chiamare nel setup()
     */
    void begin();

    /**
     * Imposta direzione e velocità di un singolo motore
     * @param motor   Numero motore (MOTOR_1, MOTOR_2, MOTOR_3, MOTOR_4)
     * @param dir     Direzione (FORWARD, BACKWARD, RELEASE, BRAKE)
     * @param speed   Velocità 0-1023 (opzionale, default usa _currentSpeed)
     */
    void setMotor(uint8_t motor, uint8_t dir, int16_t speed = -1);

    /**
     * Imposta la velocità globale (tutti i motori)
     * @param speed  Velocità 0-1023
     */
    void setSpeed(uint16_t speed);

    // ========================================================================
    // COMANDI AUTO (4 RUOTE)
    // ========================================================================

    /** Muovi avanti */
    void forward(uint16_t speed = SPEED_DEFAULT);

    /** Muovi indietro */
    void backward(uint16_t speed = SPEED_DEFAULT);

    /** Gira a sinistra (ruote destre avanti) */
    void turnLeft(uint16_t speed = SPEED_DEFAULT);

    /** Gira a destra (ruote sinistre avanti) */
    void turnRight(uint16_t speed = SPEED_DEFAULT);

    /** Ruota su se stesso a sinistra */
    void spinLeft(uint16_t speed = SPEED_DEFAULT);

    /** Ruota su se stesso a destra */
    void spinRight(uint16_t speed = SPEED_DEFAULT);

    /** Ferma tutti i motori (rilascio) */
    void stop();

    /** Frena tutti i motori (frenata attiva) */
    void brake();

    /** Restituisce la velocità corrente */
    uint16_t getSpeed();

    /** Restituisce lo stato del latch (per debug) */
    uint8_t getLatchState();

    // ========================================================================
    // CONTROLLO TANK (due joystick indipendenti)
    // ========================================================================

    /**
     * Controlla i motori sinistri (M1, M2)
     * @param power  -1023 a +1023 (negativo=indietro, positivo=avanti, 0=fermo)
     */
    void setLeftMotors(int16_t power);

    /**
     * Controlla i motori destri (M3, M4)
     * @param power  -1023 a +1023 (negativo=indietro, positivo=avanti, 0=fermo)
     */
    void setRightMotors(int16_t power);

    /**
     * Controlla entrambi i lati (modalità tank)
     * @param leftPower   Potenza motori sinistri (-1023 a +1023)
     * @param rightPower  Potenza motori destri (-1023 a +1023)
     */
    void tankDrive(int16_t leftPower, int16_t rightPower);

private:
    uint8_t _latchState;      // Stato corrente dei bit del 74HC595
    uint16_t _currentSpeed;   // Velocità corrente

    /**
     * Aggiorna lo shift register con lo stato corrente
     */
    void updateLatch();

    /**
     * Ottiene le maschere di bit per un motore
     */
    void getMotorBits(uint8_t motor, uint8_t &bitA, uint8_t &bitB);
};

// Istanza globale
extern MotorShield Motors;

#endif // MOTOR_SHIELD_H
