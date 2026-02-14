# Schema di Collegamento

## Hardware Utilizzato

| Componente | Modello |
|------------|---------|
| Controller | **Wemos D1 R1/R2** (ESP-8266, form factor Arduino UNO) |
| Motor Driver | **L293D Motor Shield** (con 74HC595) |
| Motori | 4x DC motor |
| Alimentazione | 4-6 batterie AA (6-9V) |

## Montaggio Shield

**Il L293D Motor Shield si monta DIRETTAMENTE sopra la Wemos D1!**

Non servono cavi jumper: lo shield si incastra sui pin header della board.

```
          ┌─────────────────────────────────────┐
          │      L293D MOTOR SHIELD             │
          │                                     │
          │   [M1]  [M2]      [M3]  [M4]        │  ← Connettori motori
          │                                     │
          │      ┌────────┐  ┌────────┐         │
          │      │ L293D  │  │ L293D  │         │  ← Chip driver
          │      └────────┘  └────────┘         │
          │          ┌──────────┐               │
          │          │ 74HC595  │               │  ← Shift register
          │          └──────────┘               │
          │                                     │
          │   ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼    │  ← Pin maschi
          └───────────────┬─────────────────────┘
                          │
                 SI INCASTRA SU
                          │
          ┌───────────────▼─────────────────────┐
          │                                     │
          │      ┌───────────────────┐          │
          │      │   ESP-8266 (WiFi) │          │
          │      └───────────────────┘          │
          │                                     │
          │         WEMOS D1 R1/R2              │
          │                                     │
          │   ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲    │  ← Pin femmina
          │                                     │
          │      [USB]              [DC]        │
          └─────────────────────────────────────┘
```

## Passo 1: Montaggio Shield

1. **Allinea i pin** dello shield con i connettori della Wemos
2. **Premi con delicatezza** fino a che lo shield è completamente inserito
3. **Verifica** che tutti i pin siano entrati correttamente

```
    CORRETTO                    ERRATO
    ─────────                   ─────────
    ┌───────┐                   ┌───────┐
    │Shield │                   │Shield │  ← Non allineato!
    └┬┬┬┬┬┬┬┘                   └┬┬┬┬┬┬┬┘
     ││││││││                     │││││││
    ┌┴┴┴┴┴┴┴┐                   ┌┴┴┴┴┴┴ ┐  ← Pin fuori!
    │ Wemos │                   │ Wemos │
    └───────┘                   └───────┘
```

## Passo 2: Collegamento Motori

I motori si collegano ai terminali a vite blu sullo shield:

```
        VISTA AUTO DALL'ALTO

              AVANTI
                ↑
        ┌──────────────────┐
        │                  │
        │  (M1)      (M3)  │     M1 = Motore Sinistro Anteriore
        │   ●          ●   │     M2 = Motore Sinistro Posteriore
        │                  │     M3 = Motore Destro Anteriore
        │     [ROBOT]      │     M4 = Motore Destro Posteriore
        │                  │
        │   ●          ●   │
        │  (M2)      (M4)  │
        │                  │
        └──────────────────┘
                ↓
             INDIETRO
```

**Per ogni motore:**
1. Inserisci i 2 fili del motore nel terminale corrispondente
2. Stringi le viti per fissare i fili

**NOTA:** Se un motore gira al contrario, inverti semplicemente i suoi 2 fili.

## Passo 3: Alimentazione

### Opzione A: Batterie AA (Consigliato)

```
    PORTA BATTERIE (4-6 AA)
    ┌─────────────────────────┐
    │ [+]  [-]  [+]  [-]  ... │    4 pile = 6V
    └───┬─────────────────┬───┘    6 pile = 9V
        │                 │
        │ (rosso)         │ (nero)
        ↓                 ↓
    ┌─────────────────────────────────────┐
    │        L293D MOTOR SHIELD           │
    │                                     │
    │   [EXT_PWR]                         │
    │    (+)  (-)  ← Collega qui          │
    │                                     │
    │   [JUMPER PWR] ← RIMUOVI!           │
    │                                     │
    └─────────────────────────────────────┘
```

**IMPORTANTE:** Rimuovi il jumper "PWR" dallo shield quando usi alimentazione esterna!

### Opzione B: Alimentatore DC

Puoi usare un alimentatore 7-12V DC collegato al jack della Wemos D1.

## Schema Completo

```
                      ┌─────────────────────────────┐
                      │     L293D MOTOR SHIELD      │
                      │                             │
    Batterie ────────→│ EXT_PWR (+) (-)            │
    6-9V              │                             │
                      │  M1    M2    M3    M4      │
                      │  ││    ││    ││    ││      │
                      └──┼┼────┼┼────┼┼────┼┼──────┘
                         ││    ││    ││    ││
                         ││    ││    ││    ││
                    ┌────┘│    │└────┘│    │└────┐
                    │     │    │      │    │     │
                    ▼     ▼    ▼      ▼    ▼     ▼
               ┌────────┐  ┌────────┐  ┌────────┐  ┌────────┐
               │ MOTORE │  │ MOTORE │  │ MOTORE │  │ MOTORE │
               │   M1   │  │   M2   │  │   M3   │  │   M4   │
               │ SX ANT │  │ SX POST│  │ DX ANT │  │ DX POST│
               └────────┘  └────────┘  └────────┘  └────────┘

                      ┌─────────────────────────────┐
     PC (per         │       WEMOS D1 R1/R2        │
     programmare)    │                             │
         │           │  ┌─────────────────────┐    │
         └──USB─────→│  │    ESP-8266 WiFi    │    │
                     │  └─────────────────────┘    │
                     │                             │
                     └─────────────────────────────┘
```

## Checklist Prima dell'Accensione

- [ ] Shield montato correttamente sulla Wemos
- [ ] Jumper PWR rimosso dallo shield
- [ ] Batterie collegate a EXT_PWR (polarità corretta!)
- [ ] Motori collegati a M1, M2, M3, M4
- [ ] Nessun cortocircuito visibile
- [ ] Cavo USB collegato per la programmazione

## Pin Utilizzati (automaticamente)

Lo shield usa questi pin della Wemos (non devi collegarli manualmente):

| Funzione | Pin Arduino | Pin ESP8266 |
|----------|-------------|-------------|
| Shift Latch | D4 | GPIO4 |
| Shift Enable | D7 | GPIO13 |
| Shift Data | D8 | GPIO0 |
| Shift Clock | D12 | GPIO12 |
| PWM Motor 1-2 | D11 | GPIO13 |
| PWM Motor 3-4 | D3 | GPIO5 |

## Risoluzione Problemi

### I motori non girano
1. Verifica che le batterie siano cariche
2. Controlla che il jumper PWR sia RIMOSSO
3. Verifica che lo shield sia ben inserito

### Un motore gira al contrario
- Inverti i 2 fili di quel motore sul terminale a vite

### La Wemos non si accende
- Verifica il cavo USB
- Prova ad alimentare solo via USB (senza batterie)

### Il WiFi non funziona
- Assicurati che TEST_MODE sia `false` nel codice
- Verifica sul Serial Monitor che l'AP sia attivo
