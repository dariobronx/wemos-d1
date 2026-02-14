/**
 * motor_shield.cpp
 *
 * Implementazione driver per L293D Motor Shield su Wemos D1 R1/R2
 */

#include "motor_shield.h"

// Istanza globale
MotorShield Motors;

// ============================================================================
// COSTRUTTORE
// ============================================================================

MotorShield::MotorShield() {
    _latchState = 0;
    _currentSpeed = SPEED_DEFAULT;
}

// ============================================================================
// INIZIALIZZAZIONE
// ============================================================================

void MotorShield::begin() {
    // Configura tutti i pin come output
    pinMode(MOTOR_LATCH, OUTPUT);
    pinMode(MOTOR_ENABLE, OUTPUT);
    pinMode(MOTOR_DATA, OUTPUT);
    pinMode(MOTOR_CLK, OUTPUT);
    pinMode(PWM_A, OUTPUT);
    pinMode(PWM_B, OUTPUT);

    // Abilita l'output del 74HC595 (OE attivo basso)
    digitalWrite(MOTOR_ENABLE, LOW);

    // Stato iniziale: tutti i motori fermi
    _latchState = 0;
    updateLatch();

    // PWM a 0
    analogWrite(PWM_A, 0);
    analogWrite(PWM_B, 0);

    Serial.println(F("[MotorShield] Inizializzato per Wemos D1 R1/R2"));
    Serial.println(F("[MotorShield] Shield L293D montato direttamente"));
    Serial.print(F("[MotorShield] PWM range: 0-"));
    Serial.println(SPEED_MAX);
}

// ============================================================================
// SHIFT REGISTER
// ============================================================================

void MotorShield::updateLatch() {
    // Abbassa il latch
    digitalWrite(MOTOR_LATCH, LOW);

    // Invia 8 bit, MSB first
    for (int8_t i = 7; i >= 0; i--) {
        // Abbassa il clock
        digitalWrite(MOTOR_CLK, LOW);

        // Imposta il bit di dati
        digitalWrite(MOTOR_DATA, (_latchState >> i) & 0x01);

        // Alza il clock per shiftare il bit
        digitalWrite(MOTOR_CLK, HIGH);
    }

    // Alza il latch per trasferire i dati alle uscite
    digitalWrite(MOTOR_LATCH, HIGH);
}

// ============================================================================
// UTILITY
// ============================================================================

void MotorShield::getMotorBits(uint8_t motor, uint8_t &bitA, uint8_t &bitB) {
    switch (motor) {
        case MOTOR_1:
            bitA = MOTOR1_A;
            bitB = MOTOR1_B;
            break;
        case MOTOR_2:
            bitA = MOTOR2_A;
            bitB = MOTOR2_B;
            break;
        case MOTOR_3:
            bitA = MOTOR3_A;
            bitB = MOTOR3_B;
            break;
        case MOTOR_4:
            bitA = MOTOR4_A;
            bitB = MOTOR4_B;
            break;
        default:
            bitA = 0;
            bitB = 0;
    }
}

// ============================================================================
// CONTROLLO SINGOLO MOTORE
// ============================================================================

void MotorShield::setMotor(uint8_t motor, uint8_t dir, int16_t speed) {
    uint8_t bitA, bitB;
    getMotorBits(motor, bitA, bitB);

    if (bitA == 0) return; // Motore non valido

    // Pulisci i bit di questo motore
    _latchState &= ~(bitA | bitB);

    // Imposta la direzione
    switch (dir) {
        case FORWARD:
            _latchState |= bitA;
            break;
        case BACKWARD:
            _latchState |= bitB;
            break;
        case BRAKE:
            _latchState |= (bitA | bitB);
            break;
        case RELEASE:
        default:
            // Già pulito
            break;
    }

    updateLatch();

    // Imposta PWM se specificato
    if (speed >= 0) {
        if (speed > SPEED_MAX) speed = SPEED_MAX;

        if (motor == MOTOR_1 || motor == MOTOR_2) {
            analogWrite(PWM_A, speed);
        } else {
            analogWrite(PWM_B, speed);
        }
    }
}

void MotorShield::setSpeed(uint16_t speed) {
    if (speed > SPEED_MAX) speed = SPEED_MAX;
    _currentSpeed = speed;

    analogWrite(PWM_A, speed);
    analogWrite(PWM_B, speed);
}

uint16_t MotorShield::getSpeed() {
    return _currentSpeed;
}

uint8_t MotorShield::getLatchState() {
    return _latchState;
}

// ============================================================================
// COMANDI AUTO
// ============================================================================

void MotorShield::forward(uint16_t speed) {
    Serial.print(F("[Motor] AVANTI @ "));
    Serial.println(speed);

    _currentSpeed = speed;
    setSpeed(speed);

    setMotor(MOTOR_1, FORWARD);
    setMotor(MOTOR_2, FORWARD);
    setMotor(MOTOR_3, FORWARD);
    setMotor(MOTOR_4, FORWARD);
}

void MotorShield::backward(uint16_t speed) {
    Serial.print(F("[Motor] INDIETRO @ "));
    Serial.println(speed);

    _currentSpeed = speed;
    setSpeed(speed);

    setMotor(MOTOR_1, BACKWARD);
    setMotor(MOTOR_2, BACKWARD);
    setMotor(MOTOR_3, BACKWARD);
    setMotor(MOTOR_4, BACKWARD);
}

void MotorShield::turnLeft(uint16_t speed) {
    Serial.print(F("[Motor] SINISTRA @ "));
    Serial.println(speed);

    _currentSpeed = speed;
    setSpeed(speed);

    // Ruote sinistre ferme, destre avanti
    setMotor(MOTOR_1, RELEASE);
    setMotor(MOTOR_2, RELEASE);
    setMotor(MOTOR_3, FORWARD);
    setMotor(MOTOR_4, FORWARD);
}

void MotorShield::turnRight(uint16_t speed) {
    Serial.print(F("[Motor] DESTRA @ "));
    Serial.println(speed);

    _currentSpeed = speed;
    setSpeed(speed);

    // Ruote sinistre avanti, destre ferme
    setMotor(MOTOR_1, FORWARD);
    setMotor(MOTOR_2, FORWARD);
    setMotor(MOTOR_3, RELEASE);
    setMotor(MOTOR_4, RELEASE);
}

void MotorShield::spinLeft(uint16_t speed) {
    Serial.print(F("[Motor] SPIN SX @ "));
    Serial.println(speed);

    _currentSpeed = speed;
    setSpeed(speed);

    // Ruote sinistre indietro, destre avanti
    setMotor(MOTOR_1, BACKWARD);
    setMotor(MOTOR_2, BACKWARD);
    setMotor(MOTOR_3, FORWARD);
    setMotor(MOTOR_4, FORWARD);
}

void MotorShield::spinRight(uint16_t speed) {
    Serial.print(F("[Motor] SPIN DX @ "));
    Serial.println(speed);

    _currentSpeed = speed;
    setSpeed(speed);

    // Ruote sinistre avanti, destre indietro
    setMotor(MOTOR_1, FORWARD);
    setMotor(MOTOR_2, FORWARD);
    setMotor(MOTOR_3, BACKWARD);
    setMotor(MOTOR_4, BACKWARD);
}

void MotorShield::stop() {
    Serial.println(F("[Motor] STOP"));

    setMotor(MOTOR_1, RELEASE);
    setMotor(MOTOR_2, RELEASE);
    setMotor(MOTOR_3, RELEASE);
    setMotor(MOTOR_4, RELEASE);

    analogWrite(PWM_A, 0);
    analogWrite(PWM_B, 0);
}

void MotorShield::brake() {
    Serial.println(F("[Motor] BRAKE"));

    setMotor(MOTOR_1, BRAKE);
    setMotor(MOTOR_2, BRAKE);
    setMotor(MOTOR_3, BRAKE);
    setMotor(MOTOR_4, BRAKE);
}

// ============================================================================
// CONTROLLO TANK (due joystick indipendenti)
// ============================================================================

void MotorShield::setLeftMotors(int16_t power) {
    // Limita il range
    if (power > SPEED_MAX) power = SPEED_MAX;
    if (power < -SPEED_MAX) power = -SPEED_MAX;

    uint8_t dir;
    uint16_t speed;

    if (power > 0) {
        dir = FORWARD;
        speed = power;
    } else if (power < 0) {
        dir = BACKWARD;
        speed = -power;
    } else {
        dir = RELEASE;
        speed = 0;
    }

    // Imposta direzione
    setMotor(MOTOR_1, dir);
    setMotor(MOTOR_2, dir);

    // Imposta velocità (PWM_A controlla M1 e M2)
    analogWrite(PWM_A, speed);
}

void MotorShield::setRightMotors(int16_t power) {
    // Limita il range
    if (power > SPEED_MAX) power = SPEED_MAX;
    if (power < -SPEED_MAX) power = -SPEED_MAX;

    uint8_t dir;
    uint16_t speed;

    if (power > 0) {
        dir = FORWARD;
        speed = power;
    } else if (power < 0) {
        dir = BACKWARD;
        speed = -power;
    } else {
        dir = RELEASE;
        speed = 0;
    }

    // Imposta direzione
    setMotor(MOTOR_3, dir);
    setMotor(MOTOR_4, dir);

    // Imposta velocità (PWM_B controlla M3 e M4)
    analogWrite(PWM_B, speed);
}

void MotorShield::tankDrive(int16_t leftPower, int16_t rightPower) {
    setLeftMotors(leftPower);
    setRightMotors(rightPower);
}
