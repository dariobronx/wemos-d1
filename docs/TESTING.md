# Guida ai Test - Robot Car

Questa guida ti aiuterà a testare e debuggare il tuo robot car passo per passo.

## Indice

1. [Test Preliminari (senza motori)](#1-test-preliminari-senza-motori)
2. [Test Shift Register](#2-test-shift-register)
3. [Test Motori Singoli](#3-test-motori-singoli)
4. [Test Movimenti Auto](#4-test-movimenti-auto)
5. [Test WiFi e Web Server](#5-test-wifi-e-web-server)
6. [Troubleshooting](#6-troubleshooting)

---

## 1. Test Preliminari (senza motori)

### 1.1 Test Upload del Codice

**Obiettivo**: Verificare che il Wemos comunichi correttamente con Arduino IDE

**Procedura**:
1. Collega il Wemos al PC via USB
2. Apri Arduino IDE
3. Seleziona: **Strumenti → Scheda → LOLIN(WEMOS) D1 R2 & mini**
4. Seleziona la porta COM corretta
5. Apri il progetto `src/robot_car/robot_car.ino`
6. Clicca **Upload** (freccia →)

**Risultato atteso**:
```
Sketch uses xxxxx bytes (xx%) of program storage space.
Global variables use xxxx bytes (xx%) of dynamic memory.
Uploading...
Done uploading.
```

**Se fallisce**:
- Verifica i driver USB (CH340/CP2102)
- Prova a ridurre Upload Speed a 57600
- Prova un altro cavo USB

### 1.2 Test Serial Monitor

**Obiettivo**: Verificare la comunicazione seriale

**Procedura**:
1. Dopo l'upload, apri **Strumenti → Monitor Seriale**
2. Imposta baud rate a **115200**
3. Premi il pulsante RST sul Wemos

**Risultato atteso**:
```
╔════════════════════════════════════════╗
║         ROBOT CAR - WiFi Control       ║
║      Wemos D1 Mini + L293D Shield      ║
╚════════════════════════════════════════╝

>> Inizializzazione Motor Shield...
[MotorShield] Inizializzato
[MotorShield] Pin Clock: 14
[MotorShield] Pin Data:  12
[MotorShield] Pin Latch: 13
[MotorShield] Pin PWM12: 5
[MotorShield] Pin PWM34: 4

>> Inizializzazione WiFi...
[WiFi] Access Point avviato!
[WiFi] SSID: RobotCar
[WiFi] Password: robot1234
[WiFi] IP: 192.168.4.1
```

---

## 2. Test Shift Register

### 2.1 Test con LED (opzionale ma consigliato)

**Obiettivo**: Verificare che lo shift register funzioni prima di collegare i motori

**Materiale**: 1 LED + resistenza 220Ω (opzionale)

**Procedura**:
1. NON collegare ancora i motori
2. Collega un LED tra un pin di uscita dello shift register e GND
3. Modifica temporaneamente `robot_car.ino`:

```cpp
#define TEST_MODE true  // Cambia da false a true
```

4. Carica il codice
5. Osserva i messaggi nel Serial Monitor

**Risultato atteso**: Il LED dovrebbe accendersi/spegnersi durante i test

### 2.2 Test con Multimetro

**Obiettivo**: Verificare i segnali sui pin del motor shield

**Procedura**:
1. Imposta il multimetro su voltaggio DC (20V range)
2. Collega la sonda nera a GND
3. Tocca i pin dello shield mentre esegui comandi

**Pin da testare durante "forward"**:
| Pin Shield | Valore atteso |
|------------|---------------|
| Pin 12 (Clock) | Impulsi (difficile da vedere) |
| Pin 8 (Data) | Varia |
| Pin 4 (Latch) | Impulsi |
| Pin 11 (PWM) | ~2.3V (se velocità 700/1023) |
| Pin 3 (PWM) | ~2.3V (se velocità 700/1023) |

---

## 3. Test Motori Singoli

### 3.1 Preparazione

1. Verifica tutti i collegamenti secondo `docs/WIRING.md`
2. Collega le batterie
3. Assicurati che il jumper PWR sia **RIMOSSO**
4. Carica il codice con `TEST_MODE true`

### 3.2 Esecuzione Test Automatico

Il test automatico eseguirà:

```
--- TEST SINGOLI MOTORI ---

8. Test M1 (Anteriore Sinistro)...   ← Solo M1 deve girare
9. Test M2 (Posteriore Sinistro)...  ← Solo M2 deve girare
10. Test M3 (Anteriore Destro)...    ← Solo M3 deve girare
11. Test M4 (Posteriore Destro)...   ← Solo M4 deve girare
```

### 3.3 Checklist Test Motori

Per ogni motore, verifica:

| Motore | Posizione | Gira? | Direzione corretta? | Note |
|--------|-----------|-------|---------------------|------|
| M1 | Ant. Sinistro | [ ] Sì / [ ] No | [ ] Sì / [ ] Invertire | |
| M2 | Post. Sinistro | [ ] Sì / [ ] No | [ ] Sì / [ ] Invertire | |
| M3 | Ant. Destro | [ ] Sì / [ ] No | [ ] Sì / [ ] Invertire | |
| M4 | Post. Destro | [ ] Sì / [ ] No | [ ] Sì / [ ] Invertire | |

**Se un motore non gira**:
- Verifica il collegamento ai terminali M1-M4
- Verifica l'alimentazione (batterie cariche?)
- Verifica i cavi jumper Wemos → Shield

**Se un motore gira al contrario**:
- Inverti i 2 fili del motore sul terminale a vite

---

## 4. Test Movimenti Auto

### 4.1 Test Direzioni

Il test automatico esegue queste sequenze:

| Fase | Comando | Comportamento atteso |
|------|---------|---------------------|
| 1 | AVANTI | Tutte le ruote girano in avanti |
| 2 | INDIETRO | Tutte le ruote girano all'indietro |
| 3 | SINISTRA | Solo ruote destre girano (avanti) |
| 4 | DESTRA | Solo ruote sinistre girano (avanti) |
| 5 | SPIN SX | Ruote SX indietro, DX avanti |
| 6 | SPIN DX | Ruote SX avanti, DX indietro |

### 4.2 Checklist Movimenti

| Movimento | Funziona? | L'auto va nella direzione giusta? |
|-----------|-----------|----------------------------------|
| Avanti | [ ] Sì / [ ] No | [ ] Sì / [ ] No |
| Indietro | [ ] Sì / [ ] No | [ ] Sì / [ ] No |
| Sinistra | [ ] Sì / [ ] No | [ ] Sì / [ ] No |
| Destra | [ ] Sì / [ ] No | [ ] Sì / [ ] No |
| Spin Sinistra | [ ] Sì / [ ] No | [ ] Sì / [ ] No |
| Spin Destra | [ ] Sì / [ ] No | [ ] Sì / [ ] No |

### 4.3 Correzione Direzioni Invertite

Se l'auto va nella direzione opposta a quella attesa, hai due opzioni:

**Opzione 1: Invertire fisicamente i fili dei motori**
- Semplice ma richiede di aprire le connessioni

**Opzione 2: Invertire nel software**
Modifica in `motor_shield.cpp` la funzione corrispondente:

```cpp
// Esempio: se "forward" fa andare indietro
void MotorShield::forward(uint16_t speed) {
    // Cambia DIR_FORWARD con DIR_BACKWARD
    setMotor(MOTOR_1, DIR_BACKWARD);  // Era DIR_FORWARD
    // ...
}
```

---

## 5. Test WiFi e Web Server

### 5.1 Test Access Point

**Procedura**:
1. Imposta `TEST_MODE false` nel codice
2. Carica il codice
3. Sul telefono, vai in Impostazioni WiFi
4. Cerca la rete "RobotCar"
5. Connettiti con password "robot1234"

**Risultato atteso**: Connessione riuscita

**Serial Monitor dovrebbe mostrare**:
```
[Info] Client connessi: 1
```

### 5.2 Test Pagina Web

**Procedura**:
1. Apri il browser del telefono
2. Vai a `http://192.168.4.1`

**Risultato atteso**: Pagina di controllo con:
- Pulsanti frecce direzionali
- Pulsante STOP centrale (rosso)
- Pulsanti spin (viola)
- Slider velocità

### 5.3 Test Comandi Web

Testa ogni pulsante e verifica:

| Pulsante | URL chiamato | Motori reagiscono? |
|----------|--------------|-------------------|
| ▲ (Avanti) | /forward | [ ] Sì / [ ] No |
| ▼ (Indietro) | /backward | [ ] Sì / [ ] No |
| ◀ (Sinistra) | /left | [ ] Sì / [ ] No |
| ▶ (Destra) | /right | [ ] Sì / [ ] No |
| ■ (Stop) | /stop | [ ] Sì / [ ] No |
| ↺ (Spin SX) | /spinleft | [ ] Sì / [ ] No |
| ↻ (Spin DX) | /spinright | [ ] Sì / [ ] No |
| Slider | /speed?v=XXX | [ ] Sì / [ ] No |

### 5.4 Test con URL Diretti

Puoi testare i comandi direttamente dal browser:

```
http://192.168.4.1/forward    → Avanti
http://192.168.4.1/backward   → Indietro
http://192.168.4.1/left       → Sinistra
http://192.168.4.1/right      → Destra
http://192.168.4.1/stop       → Stop
http://192.168.4.1/speed?v=500  → Imposta velocità 500
http://192.168.4.1/status     → JSON con stato
```

---

## 6. Troubleshooting

### 6.1 Problemi Upload

| Problema | Soluzione |
|----------|-----------|
| "Port not found" | Installa driver CH340/CP2102 |
| "Upload failed" | Riduci Upload Speed a 57600 |
| "Timed out waiting for packet header" | Tieni premuto FLASH durante l'upload |

### 6.2 Problemi Motori

| Problema | Possibile causa | Soluzione |
|----------|-----------------|-----------|
| Nessun motore gira | Batterie scariche | Cambia batterie |
| | Jumper PWR inserito | Rimuovi jumper |
| | Cavi scollegati | Verifica collegamenti |
| Un solo motore non gira | Terminale allentato | Stringi la vite |
| | Motore guasto | Testa con alimentazione diretta |
| Motori girano piano | Batterie quasi scariche | Cambia batterie |
| | PWM troppo basso | Aumenta velocità |
| Motori girano al contrario | Polarità invertita | Inverti fili motore |

### 6.3 Problemi WiFi

| Problema | Possibile causa | Soluzione |
|----------|-----------------|-----------|
| Rete non visibile | Codice non caricato | Verifica upload |
| | TEST_MODE attivo | Imposta TEST_MODE false |
| Non si connette | Password errata | Usa "robot1234" |
| Pagina non carica | IP errato | Usa 192.168.4.1 |
| | Server non avviato | Controlla Serial Monitor |
| Comandi non funzionano | Errore JavaScript | Apri console browser (F12) |

### 6.4 Debug Avanzato

**Vedere lo stato dello shift register**:
```
http://192.168.4.1/status
```

Risposta JSON:
```json
{
  "ip": "192.168.4.1",
  "clients": 1,
  "speed": 700,
  "speedMax": 1023,
  "shiftReg": 85
}
```

Il valore `shiftReg` mostra i bit attivi (es. 85 = 01010101 in binario)

**Decodifica shiftReg**:
| Bit | Valore | Significato |
|-----|--------|-------------|
| 0 | 1 | M1 avanti |
| 1 | 2 | M1 indietro |
| 2 | 4 | M2 avanti |
| 3 | 8 | M2 indietro |
| 4 | 16 | M3 avanti |
| 5 | 32 | M3 indietro |
| 6 | 64 | M4 avanti |
| 7 | 128 | M4 indietro |

Esempio: `shiftReg: 85` = 1+4+16+64 = M1, M2, M3, M4 tutti avanti

---

## Registro Test

Usa questa tabella per annotare i risultati dei tuoi test:

| Data | Test | Risultato | Note |
|------|------|-----------|------|
| | Upload codice | | |
| | Serial Monitor | | |
| | Motore M1 | | |
| | Motore M2 | | |
| | Motore M3 | | |
| | Motore M4 | | |
| | WiFi AP | | |
| | Pagina web | | |
| | Comandi web | | |
| | Test su strada | | |

---

## Prossimi Passi

Una volta completati tutti i test:

1. [ ] Monta l'elettronica sul chassis
2. [ ] Fissa i cavi in modo ordinato
3. [ ] Testa l'auto su una superficie piana
4. [ ] Regola la velocità per il tuo ambiente
5. [ ] (Opzionale) Installa l'app Android per controllo migliorato
