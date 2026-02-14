# CLAUDE.md - Istruzioni per AI Assistant

## Panoramica Progetto

**Robot Car WiFi** - Auto a 4 ruote controllata via smartphone.

| Aspetto | Valore |
|---------|--------|
| Controller | **Wemos D1 R1/R2** (ESP-8266, form factor Arduino UNO) |
| Motor Driver | **L293D Motor Shield** (montato direttamente, no cavi!) |
| Controllo | WiFi Access Point + Web Server |
| Interfacce | Pulsanti + **Tank Mode** (2 joystick) |

## Architettura Hardware

```
┌──────────────────────────────────────┐
│         L293D MOTOR SHIELD           │
│  (si incastra sopra la Wemos D1)     │
│                                      │
│  M1──┐  M2──┐      M3──┐  M4──┐      │
│      │      │          │      │      │
│  ┌───┴──────┴──┐  ┌────┴──────┴───┐  │
│  │   L293D #1  │  │   L293D #2    │  │
│  └─────────────┘  └───────────────┘  │
│         ┌──────────────┐             │
│         │   74HC595    │             │
│         │ Shift Reg    │             │
│         └──────────────┘             │
│                                      │
│  ▼▼▼▼▼▼ PIN SI INCASTRANO ▼▼▼▼▼▼▼   │
└──────────────────────────────────────┘
               │
┌──────────────▼───────────────────────┐
│          WEMOS D1 R1/R2              │
│                                      │
│  ┌────────────────────────────────┐  │
│  │      ESP-8266 WiFi Module      │  │
│  │   (crea rete "RobotCar")       │  │
│  └────────────────────────────────┘  │
│                                      │
│  [USB]                        [DC]   │
└──────────────────────────────────────┘
```

## Struttura Codice

```
src/robot_car/
├── robot_car.ino        # Entry point, setup/loop, test mode
├── motor_shield.h       # API motori (header)
├── motor_shield.cpp     # Implementazione shift register + PWM
├── wifi_controller.h    # API WiFi/Web (header)
└── wifi_controller.cpp  # Web server + pagine HTML
```

## API MotorShield

```cpp
// Inizializzazione
Motors.begin();

// Movimenti base
Motors.forward(speed);      // Tutti avanti
Motors.backward(speed);     // Tutti indietro
Motors.turnLeft(speed);     // Curva sinistra
Motors.turnRight(speed);    // Curva destra
Motors.spinLeft(speed);     // Rotazione antioraria
Motors.spinRight(speed);    // Rotazione oraria
Motors.stop();              // Ferma tutto
Motors.brake();             // Freno attivo

// Tank mode (controllo indipendente)
Motors.setLeftMotors(power);   // power: -1023 a +1023
Motors.setRightMotors(power);
Motors.tankDrive(left, right); // Entrambi insieme

// Utility
Motors.setSpeed(speed);        // Imposta velocità globale
Motors.getSpeed();             // Leggi velocità
Motors.getLatchState();        // Debug shift register
```

## API WiFiController

```cpp
WifiCtrl.begin();              // Avvia AP + Web Server
WifiCtrl.handleClient();       // Chiamare nel loop()
WifiCtrl.getIP();              // "192.168.4.1"
WifiCtrl.getSSID();            // "RobotCar"
WifiCtrl.getConnectedClients();// Numero client
```

## Endpoints Web

| Route | Metodo | Descrizione |
|-------|--------|-------------|
| `/` | GET | Pagina pulsanti |
| `/tank` | GET | Pagina tank mode |
| `/drive?l=X&r=Y` | GET | Controllo tank (-1023 a +1023) |
| `/forward` | GET | Avanti |
| `/backward` | GET | Indietro |
| `/left` | GET | Sinistra |
| `/right` | GET | Destra |
| `/spinleft` | GET | Spin sinistra |
| `/spinright` | GET | Spin destra |
| `/stop` | GET | Ferma |
| `/speed?v=N` | GET | Imposta velocità |
| `/status` | GET | JSON stato |

## Pin Mapping (automatico via shield)

Lo shield usa questi pin Arduino (mappati a GPIO ESP8266):

| Funzione | Arduino Pin | ESP8266 GPIO |
|----------|-------------|--------------|
| Shift Latch | D4 | GPIO4 |
| Shift Enable | D7 | GPIO13 |
| Shift Data | D8 | GPIO0 |
| Shift Clock | D12 | GPIO12 |
| PWM M1-M2 | D11 | GPIO13 |
| PWM M3-M4 | D3 | GPIO5 |

## Shift Register Bits (74HC595)

```
Bit 0 (0x01) → M3A
Bit 1 (0x02) → M2A
Bit 2 (0x04) → M1A
Bit 3 (0x08) → M1B
Bit 4 (0x10) → M2B
Bit 5 (0x20) → M4A
Bit 6 (0x40) → M4B
Bit 7 (0x80) → M3B
```

## Configurazione

### WiFi (wifi_controller.h)
```cpp
#define AP_SSID     "RobotCar"
#define AP_PASSWORD "robot1234"
#define AP_IP       IPAddress(192, 168, 4, 1)
```

### Test Mode (robot_car.ino)
```cpp
#define TEST_MODE true   // Test motori senza WiFi
#define TEST_MODE false  // Normale (WiFi attivo)
```

## Motori Layout

```
        AVANTI
          ↑
    ┌─────────────┐
    │ M1       M3 │   M1 = Sinistro Anteriore
    │  ●       ●  │   M2 = Sinistro Posteriore
    │             │   M3 = Destro Anteriore
    │  ●       ●  │   M4 = Destro Posteriore
    │ M2       M4 │
    └─────────────┘
          ↓
       INDIETRO
```

## Task Comuni

### Aggiungere nuovo endpoint

1. Aggiungi handler in `wifi_controller.h`:
   ```cpp
   void handleNewCommand();
   ```

2. Implementa in `wifi_controller.cpp`:
   ```cpp
   void WiFiController::handleNewCommand() {
       // logica
       sendJsonResponse("ok", "newcmd");
   }
   ```

3. Registra route in `begin()`:
   ```cpp
   _server.on("/newcmd", HTTP_GET, [this]() { handleNewCommand(); });
   ```

### Invertire direzione motore

Se un motore gira al contrario fisicamente, inverti i fili.
Oppure nel codice, in `motor_shield.cpp`:
```cpp
// Cambia FORWARD con BACKWARD per quel motore specifico
```

### Cambiare velocità default

In `motor_shield.h`:
```cpp
#define SPEED_DEFAULT   700   // 0-1023
```

## Note Tecniche

1. **PWM ESP8266**: 10-bit (0-1023), non 8-bit come Arduino
2. **WiFi AP**: Crea rete propria, non serve router
3. **Shift Register**: Gestisce direzioni, PWM gestisce velocità
4. **Latenza**: ~50-200ms tipica sui comandi

## Documentazione

| File | Contenuto |
|------|-----------|
| `docs/WIRING.md` | Schema montaggio hardware |
| `docs/TESTING.md` | Guida test e debug |
| `docs/MANUALE_UTENTE.md` | Guida per l'utente finale |
| `docs/APP_ANDROID_GUIDA.md` | Come creare APK con MIT App Inventor |
