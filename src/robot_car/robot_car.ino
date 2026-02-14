/**
 * robot_car.ino
 *
 * Firmware per auto robotica a 4 ruote controllata via WiFi
 *
 * Hardware:
 *   - Wemos D1 R1/R2 (ESP-8266, form factor Arduino UNO)
 *   - L293D Motor Shield (montato direttamente sopra)
 *   - 4 motori DC
 *   - Batterie 6-9V
 *
 * Controllo:
 *   - WiFi Access Point: "RobotCar" (password: robot1234)
 *   - Pagina pulsanti:   http://192.168.4.1/
 *   - Pagina tank mode:  http://192.168.4.1/tank
 *
 * Tank Mode: Due joystick verticali per controllo indipendente
 *            ruote sinistre e destre con velocita' variabile.
 */

#include "motor_shield.h"
#include "wifi_controller.h"

// ============================================================================
// CONFIGURAZIONE
// ============================================================================

// Modalita' test: true = test motori senza WiFi, false = normale
#define TEST_MODE false

// Tempo di ogni fase del test (ms)
#define TEST_DURATION 1500

// ============================================================================
// SETUP
// ============================================================================

void setup() {
    Serial.begin(115200);
    delay(100);

    Serial.println(F("\n\n"));
    Serial.println(F("╔════════════════════════════════════════════╗"));
    Serial.println(F("║         ROBOT CAR - WiFi Control           ║"));
    Serial.println(F("║     Wemos D1 R1/R2 + L293D Shield          ║"));
    Serial.println(F("╚════════════════════════════════════════════╝"));

    // Inizializza motori
    Serial.println(F("\n[Setup] Inizializzazione motori..."));
    Motors.begin();

    if (TEST_MODE) {
        Serial.println(F("\n*** MODALITA' TEST ATTIVA ***"));
        runMotorTest();
    } else {
        // Inizializza WiFi
        Serial.println(F("\n[Setup] Inizializzazione WiFi..."));
        WifiCtrl.begin();

        Serial.println(F("\n════════════════════════════════════════════"));
        Serial.println(F(" PRONTO!"));
        Serial.println(F(""));
        Serial.println(F(" 1. Connetti smartphone a WiFi 'RobotCar'"));
        Serial.println(F("    Password: robot1234"));
        Serial.println(F(""));
        Serial.println(F(" 2. Apri nel browser:"));
        Serial.println(F("    - http://192.168.4.1      (pulsanti)"));
        Serial.println(F("    - http://192.168.4.1/tank (joystick)"));
        Serial.println(F("════════════════════════════════════════════\n"));
    }
}

// ============================================================================
// LOOP
// ============================================================================

void loop() {
    if (!TEST_MODE) {
        WifiCtrl.handleClient();

        // Info periodica
        static unsigned long lastInfo = 0;
        if (millis() - lastInfo > 10000) {
            lastInfo = millis();
            Serial.print(F("[Info] Client: "));
            Serial.print(WifiCtrl.getConnectedClients());
            Serial.print(F(" | Heap: "));
            Serial.println(ESP.getFreeHeap());
        }
    }
    yield();
}

// ============================================================================
// TEST MOTORI
// ============================================================================

void runMotorTest() {
    Serial.println(F("\n--- TEST MOVIMENTI BASE ---\n"));

    Serial.println(F("1. AVANTI"));
    Motors.forward(700);
    delay(TEST_DURATION);
    Motors.stop();
    delay(300);

    Serial.println(F("2. INDIETRO"));
    Motors.backward(700);
    delay(TEST_DURATION);
    Motors.stop();
    delay(300);

    Serial.println(F("3. SINISTRA"));
    Motors.turnLeft(700);
    delay(TEST_DURATION);
    Motors.stop();
    delay(300);

    Serial.println(F("4. DESTRA"));
    Motors.turnRight(700);
    delay(TEST_DURATION);
    Motors.stop();
    delay(300);

    Serial.println(F("5. SPIN SINISTRA"));
    Motors.spinLeft(600);
    delay(TEST_DURATION);
    Motors.stop();
    delay(300);

    Serial.println(F("6. SPIN DESTRA"));
    Motors.spinRight(600);
    delay(TEST_DURATION);
    Motors.stop();
    delay(300);

    Serial.println(F("\n--- TEST TANK MODE ---\n"));

    Serial.println(F("7. Solo ruote sinistre avanti"));
    Motors.tankDrive(700, 0);
    delay(TEST_DURATION);
    Motors.stop();
    delay(300);

    Serial.println(F("8. Solo ruote destre avanti"));
    Motors.tankDrive(0, 700);
    delay(TEST_DURATION);
    Motors.stop();
    delay(300);

    Serial.println(F("9. Sinistre avanti, destre indietro"));
    Motors.tankDrive(700, -700);
    delay(TEST_DURATION);
    Motors.stop();
    delay(300);

    Serial.println(F("\n--- TEST VELOCITA' ---\n"));

    Serial.println(F("10. Velocita' crescente"));
    for (int s = 300; s <= 900; s += 200) {
        Serial.print(F("    Speed: ")); Serial.println(s);
        Motors.forward(s);
        delay(800);
    }
    Motors.stop();

    Serial.println(F("\n╔════════════════════════════════════════════╗"));
    Serial.println(F("║           TEST COMPLETATO!                 ║"));
    Serial.println(F("╚════════════════════════════════════════════╝"));
    Serial.println(F("\nSe un motore gira al contrario, inverti i suoi fili."));
    Serial.println(F("Imposta TEST_MODE=false per usare il WiFi.\n"));
}
