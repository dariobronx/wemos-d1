/**
 * wifi_controller.h
 *
 * Controller WiFi in modalità Access Point (AP) per Wemos D1 R1/R2
 * Il Wemos crea la propria rete WiFi a cui lo smartphone si connette direttamente
 */

#ifndef WIFI_CONTROLLER_H
#define WIFI_CONTROLLER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "motor_shield.h"

// ============================================================================
// CONFIGURAZIONE WIFI ACCESS POINT
// ============================================================================

// Nome rete WiFi creata dal robot (puoi cambiarlo!)
#define AP_SSID     "RobotCar"

// Password rete WiFi (minimo 8 caratteri)
#define AP_PASSWORD "robot1234"

// Canale WiFi (1-13, usa 1 o 6 per meno interferenze)
#define AP_CHANNEL  1

// IP fisso del robot
#define AP_IP       IPAddress(192, 168, 4, 1)
#define AP_GATEWAY  IPAddress(192, 168, 4, 1)
#define AP_SUBNET   IPAddress(255, 255, 255, 0)

// Porta web server
#define WEB_PORT    80

// ============================================================================
// CLASSE WIFI CONTROLLER
// ============================================================================

class WiFiController {
public:
    WiFiController();

    /**
     * Inizializza WiFi AP e Web Server
     * Chiamare nel setup() DOPO Motors.begin()
     */
    void begin();

    /**
     * Gestisce le richieste client - chiamare nel loop()
     */
    void handleClient();

    /**
     * Restituisce l'IP del robot
     */
    String getIP();

    /**
     * Restituisce il nome della rete WiFi
     */
    String getSSID();

    /**
     * Restituisce la password
     */
    String getPassword();

    /**
     * Restituisce il numero di client connessi
     */
    uint8_t getConnectedClients();

private:
    ESP8266WebServer _server;
    uint16_t _currentSpeed;

    // Handler
    void handleRoot();
    void handleTankPage();
    void handleForward();
    void handleBackward();
    void handleLeft();
    void handleRight();
    void handleSpinLeft();
    void handleSpinRight();
    void handleStop();
    void handleSpeed();
    void handleTank();
    void handleStatus();
    void handleNotFound();

    String getControlPage();
    String getTankControlPage();
    void sendJsonResponse(const String& status, const String& message);
};

extern WiFiController WifiCtrl;

#endif
