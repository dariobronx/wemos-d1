# Robot Car WiFi - Wemos D1 R1/R2

Auto robotica a 4 ruote controllata via WiFi con smartphone Android.

```
    ┌─────────────────────────────────────────┐
    │             ROBOT CAR WiFi              │
    │                                         │
    │     ┌──┐   ┌─────────────┐   ┌──┐       │
    │     │M1│   │ L293D Shield│   │M3│       │
    │     └──┘   │  (montato)  │   └──┘       │
    │            │      +      │              │
    │     ┌──┐   │  Wemos D1   │   ┌──┐       │
    │     │M2│   │   R1/R2     │   │M4│       │
    │     └──┘   └─────────────┘   └──┘       │
    │                                         │
    │        WiFi: "RobotCar"                 │
    │     Password: robot1234                 │
    │     http://192.168.4.1                  │
    └─────────────────────────────────────────┘
```

## Caratteristiche

- **WiFi Access Point** - Il robot crea la sua rete WiFi
- **Due modalità di controllo**:
  - Pulsanti direzionali
  - **Tank mode** con due joystick verticali
- **Velocità variabile** - Controllo potenza in tempo reale
- **Nessuna app richiesta** - Funziona con qualsiasi browser

## Hardware

| Componente | Modello |
|------------|---------|
| Controller | **Wemos D1 R1/R2** (ESP-8266, form factor Arduino UNO) |
| Motor Driver | **L293D Motor Shield** (si incastra direttamente!) |
| Motori | 4x DC motor |
| Alimentazione | 4-6 batterie AA (6-9V) |

## Quick Start

### 1. Monta lo Shield
Lo shield L293D si **incastra direttamente** sulla Wemos D1. Niente cavi!

### 2. Collega i Motori
Collega i 4 motori ai terminali M1, M2, M3, M4 dello shield.

### 3. Programma la Board
```
1. Installa Arduino IDE
2. Aggiungi supporto ESP8266 (vedi sotto)
3. Apri src/robot_car/robot_car.ino
4. Seleziona: Strumenti → Scheda → LOLIN(WEMOS) D1 R2 & mini
5. Carica
```

### 4. Controlla il Robot
```
1. Connetti smartphone a WiFi "RobotCar" (password: robot1234)
2. Apri browser: http://192.168.4.1
3. Divertiti!
```

## Modalità di Controllo

### Pulsanti (`/`)
Controllo classico con frecce direzionali e slider velocità.

### Tank Mode (`/tank`) - Consigliato!
Due joystick verticali indipendenti:
- **Slider sinistro** → ruote sinistre (M1, M2)
- **Slider destro** → ruote destre (M3, M4)
- Verso l'alto = avanti, verso il basso = indietro
- Più spostamento = più velocità

```
    SINISTRA        DESTRA
    ┌─────┐         ┌─────┐
    │  ▲  │  +100%  │  ▲  │
    │     │         │     │
    │──●──│    0%   │──●──│
    │     │         │     │
    │  ▼  │  -100%  │  ▼  │
    └─────┘         └─────┘
```

## Installazione Arduino IDE

### 1. Board Manager URL

**File → Preferenze → URL aggiuntive:**
```
https://arduino.esp8266.com/stable/package_esp8266com_index.json
```

### 2. Installa ESP8266

**Strumenti → Scheda → Gestore schede → cerca "esp8266" → Installa**

### 3. Seleziona Board

**Strumenti → Scheda → ESP8266 → LOLIN(WEMOS) D1 R2 & mini**

### 4. Driver USB

- **CH340**: https://www.wch-ic.com/downloads/CH341SER_ZIP.html
- **CP2102**: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers

## Struttura Progetto

```
wemos-d1/
├── README.md                    # Questo file
├── CLAUDE.md                    # Istruzioni AI
├── src/robot_car/
│   ├── robot_car.ino           # Sketch principale
│   ├── motor_shield.h/.cpp     # Driver motori + shift register
│   └── wifi_controller.h/.cpp  # WiFi AP + Web server
└── docs/
    ├── WIRING.md               # Schema montaggio
    ├── TESTING.md              # Guida test
    ├── MANUALE_UTENTE.md       # Guida uso completa
    └── APP_ANDROID_GUIDA.md    # Creazione app APK
```

## API Endpoints

| Endpoint | Descrizione |
|----------|-------------|
| `/` | Pagina controllo pulsanti |
| `/tank` | Pagina controllo tank mode |
| `/drive?l=X&r=Y` | Controllo tank (X,Y: -1023 a +1023) |
| `/forward` | Avanti |
| `/backward` | Indietro |
| `/left` | Sinistra |
| `/right` | Destra |
| `/stop` | Ferma |
| `/speed?v=N` | Imposta velocità (0-1023) |
| `/status` | JSON stato |

## Test Mode

Per testare i motori senza WiFi:

```cpp
// In robot_car.ino, cambia:
#define TEST_MODE true
```

Questo esegue un test automatico di tutti i movimenti.

## Configurazione WiFi

Modifica in `wifi_controller.h`:
```cpp
#define AP_SSID     "RobotCar"      // Nome rete
#define AP_PASSWORD "robot1234"     // Password
```

## Troubleshooting

| Problema | Soluzione |
|----------|-----------|
| Board non riconosciuta | Installa driver CH340/CP2102 |
| Upload fallisce | Riduci velocità a 57600 |
| Rete non visibile | Verifica TEST_MODE = false |
| Motori non girano | Rimuovi jumper PWR, controlla batterie |
| Motore gira al contrario | Inverti i 2 fili del motore |

## Documentazione

- [Schema Montaggio](docs/WIRING.md)
- [Guida Test](docs/TESTING.md)
- [Manuale Utente](docs/MANUALE_UTENTE.md)
- [Creare App Android](docs/APP_ANDROID_GUIDA.md)

## Licenza

Progetto open source per uso personale ed educativo.
