# Manuale Utente - Robot Car WiFi

Guida completa per controllare il robot car dal tuo smartphone Android.

## Indice

1. [Prima Configurazione](#1-prima-configurazione)
2. [Connessione WiFi](#2-connessione-wifi)
3. [Controllo via Browser](#3-controllo-via-browser)
4. [App Android](#4-app-android)
5. [Modalità di Controllo](#5-modalità-di-controllo)
6. [Risoluzione Problemi](#6-risoluzione-problemi)

---

## 1. Prima Configurazione

### Cosa ti serve

- Robot car assemblato e programmato
- Smartphone Android (o qualsiasi dispositivo con WiFi e browser)
- Batterie cariche nel robot

### Accensione del Robot

1. **Inserisci le batterie** nel porta batterie
2. **Collega le batterie** ai terminali EXT_PWR dello shield (se non già fatto)
3. Il robot si accenderà automaticamente

Quando il robot è pronto:
- Il LED sulla Wemos lampeggerà brevemente
- La rete WiFi "RobotCar" apparirà nelle reti disponibili

---

## 2. Connessione WiFi

### Dati di Connessione

| Parametro | Valore |
|-----------|--------|
| **Nome rete (SSID)** | `RobotCar` |
| **Password** | `robot1234` |
| **IP del robot** | `192.168.4.1` |

### Passo-Passo Android

1. **Apri Impostazioni** sul telefono

2. **Vai su WiFi**

3. **Cerca la rete** "RobotCar"
   ```
   Reti disponibili:
   ├── Casa-WiFi
   ├── RobotCar        ← Seleziona questa!
   └── Vicino-5G
   ```

4. **Inserisci la password**: `robot1234`

5. **Connetti**

6. **IMPORTANTE**: Android potrebbe mostrare un avviso:
   ```
   ┌─────────────────────────────────────┐
   │  "RobotCar" non ha accesso a       │
   │  Internet. Restare connessi?        │
   │                                     │
   │     [No]            [Sì]            │
   └─────────────────────────────────────┘
   ```
   **Tocca "Sì"** (o "Mantieni connessione")!

### Verifica Connessione

Sei connesso correttamente quando:
- L'icona WiFi mostra "RobotCar"
- Non sei più connesso alla tua rete di casa
- Il simbolo WiFi potrebbe mostrare "!" (normale, non c'è internet)

---

## 3. Controllo via Browser

### Pagina Pulsanti (Base)

1. **Apri il browser** (Chrome, Firefox, ecc.)

2. **Digita l'indirizzo**: `192.168.4.1`
   ```
   ┌─────────────────────────────────────┐
   │ 🔒 192.168.4.1                    ⋮ │
   └─────────────────────────────────────┘
   ```

3. **Premi Invio**

4. Apparirà la pagina di controllo:
   ```
   ┌─────────────────────────────────────┐
   │         Robot Car                   │
   │     Connesso | Velocità: 700        │
   │                                     │
   │      [↺]    [▲]    [↻]              │
   │                                     │
   │      [◀]    [■]    [▶]              │
   │                                     │
   │             [▼]                     │
   │                                     │
   │     ═══════════════════════         │
   │          Velocità: 700              │
   └─────────────────────────────────────┘
   ```

### Pagina Tank Mode (Joystick)

1. **Digita**: `192.168.4.1/tank`

2. Apparirà la pagina con i due joystick verticali:
   ```
   ┌─────────────────────────────────────┐
   │      Robot Car - Tank Mode          │
   │        SX: 0       DX: 0            │
   │                                     │
   │    SINISTRA        DESTRA           │
   │    ┌─────┐         ┌─────┐          │
   │    │  ▲  │         │  ▲  │          │
   │    │     │         │     │          │
   │    │──●──│         │──●──│          │
   │    │     │         │     │          │
   │    │  ▼  │         │  ▼  │          │
   │    └─────┘         └─────┘          │
   │                                     │
   │      [ Modalità pulsanti ]          │
   └─────────────────────────────────────┘
   ```

### Salvare come App (Scorciatoia)

Per accedere rapidamente senza digitare l'indirizzo:

**Su Chrome:**
1. Apri `192.168.4.1` (o `/tank`)
2. Tocca i **3 puntini** (⋮) in alto a destra
3. Seleziona **"Aggiungi a schermata Home"**
4. Dai un nome: "Robot Car"
5. Tocca **"Aggiungi"**

Ora avrai un'icona sulla home del telefono!

---

## 4. App Android

Per un'esperienza migliore, puoi creare un'app dedicata con MIT App Inventor.

### Creazione App con MIT App Inventor

MIT App Inventor è gratuito e funziona nel browser.

#### Passo 1: Accedi

1. Vai su: **https://appinventor.mit.edu**
2. Clicca **"Create Apps!"**
3. Accedi con account Google

#### Passo 2: Importa il Progetto

1. Scarica il file `RobotCarController.aia` dalla cartella `android/` del progetto
2. In MIT App Inventor: **Projects → Import project (.aia)**
3. Seleziona il file scaricato

#### Passo 3: Genera l'APK

1. Clicca **Build → Android App (.apk)**
2. Attendi la compilazione (~1-2 minuti)
3. Apparirà un QR code
4. **Scansiona il QR** con il telefono per scaricare l'APK

#### Passo 4: Installa l'APK

1. Apri il file APK scaricato
2. Se richiesto, abilita **"Origini sconosciute"**:
   - Impostazioni → Sicurezza → Origini sconosciute → Attiva
3. Completa l'installazione

---

## 5. Modalità di Controllo

### Modalità Pulsanti

Controllo semplice con pulsanti direzionali.

| Pulsante | Azione |
|----------|--------|
| ▲ | Avanti (tutti i motori) |
| ▼ | Indietro (tutti i motori) |
| ◀ | Sinistra (solo ruote destre girano) |
| ▶ | Destra (solo ruote sinistre girano) |
| ↺ | Spin sinistra (ruota sul posto) |
| ↻ | Spin destra (ruota sul posto) |
| ■ | Stop (ferma tutto) |
| Slider | Regola la velocità |

**Come usare:**
- **Tieni premuto** il pulsante per muovere
- **Rilascia** per fermare
- Il pulsante STOP ferma immediatamente

### Modalità Tank (Joystick)

Controllo avanzato con due joystick verticali indipendenti.

```
    SINISTRA                DESTRA
    (M1, M2)                (M3, M4)

    ┌─────┐                 ┌─────┐
    │  ▲  │ Avanti          │  ▲  │ Avanti
    │ +++ │                  │ +++ │
    │──●──│ Centro=Stop     │──●──│ Centro=Stop
    │ --- │                  │ --- │
    │  ▼  │ Indietro        │  ▼  │ Indietro
    └─────┘                 └─────┘
```

**Come funziona:**
- **Slider sinistro**: controlla ruote sinistre
- **Slider destro**: controlla ruote destre
- **Posizione centrale**: motori fermi
- **Più in alto/basso**: più velocità

**Movimenti:**
| Sinistra | Destra | Risultato |
|----------|--------|-----------|
| ▲ Alto | ▲ Alto | Avanti dritto |
| ▼ Basso | ▼ Basso | Indietro dritto |
| ▲ Alto | Centro | Curva a destra |
| Centro | ▲ Alto | Curva a sinistra |
| ▲ Alto | ▼ Basso | Spin a destra |
| ▼ Basso | ▲ Alto | Spin a sinistra |

**Rilasciando** il dito, lo slider torna al centro (stop).

---

## 6. Risoluzione Problemi

### Non trovo la rete "RobotCar"

| Verifica | Soluzione |
|----------|-----------|
| Robot acceso? | Controlla le batterie |
| Batterie cariche? | Sostituisci le batterie |
| Sei vicino? | Avvicinati al robot (range ~30m) |
| TEST_MODE attivo? | Modifica il codice e ricarica |

### La pagina non si carica

1. **Verifica la connessione** WiFi a "RobotCar"
2. **Controlla l'indirizzo**: deve essere `192.168.4.1`
3. **Riavvia il robot** (togli e rimetti batterie)
4. **Disattiva i dati mobili** sul telefono

### I comandi sono lenti

- È normale una latenza di 50-200ms
- Avvicinati al robot
- Evita interferenze (altri WiFi, microonde)

### I motori non rispondono

1. Verifica le batterie dei motori
2. Controlla i collegamenti dei motori
3. Verifica che il jumper PWR sia rimosso
4. Prova la modalità TEST (TEST_MODE = true)

### Un motore gira al contrario

- Inverti i 2 fili di quel motore sul terminale a vite

### Il telefono si disconnette

Android potrebbe preferire reti con internet. Soluzioni:

1. **Disattiva i dati mobili** mentre usi il robot
2. **Disattiva il WiFi intelligente** (che cambia rete automaticamente)
3. Nelle impostazioni WiFi, **dimentica** altre reti temporaneamente

### L'app crasha

- Verifica di essere connesso a "RobotCar"
- Riavvia l'app
- Reinstalla l'APK

---

## Crediti

Robot Car WiFi - Progetto open source
- Controller: Wemos D1 R1/R2 (ESP-8266)
- Motor Driver: L293D Shield
