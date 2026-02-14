# GUIDA COMPLETA - Da Zero al Robot Funzionante

**Livello: Principiante Assoluto**

Questa guida ti accompagna passo-passo dalla scatola dei componenti al robot che si muove controllato dal tuo smartphone. Non serve sapere nulla di elettronica o programmazione.

---

## INDICE

1. [Cosa Ti Serve (Lista della Spesa)](#1-cosa-ti-serve)
2. [Installare Arduino IDE](#2-installare-arduino-ide)
3. [Configurare Arduino per Wemos D1](#3-configurare-arduino-per-wemos-d1)
4. [Montare l'Hardware](#4-montare-lhardware)
5. [Caricare il Programma](#5-caricare-il-programma)
6. [Primo Test dei Motori](#6-primo-test-dei-motori)
7. [Connettere lo Smartphone](#7-connettere-lo-smartphone)
8. [Usare il Robot](#8-usare-il-robot)
9. [Creare l'App Android](#9-creare-lapp-android)
10. [Risoluzione Problemi](#10-risoluzione-problemi)

---

# 1. COSA TI SERVE

## Lista Componenti

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                           LISTA DELLA SPESA                                  │
├─────────────────────────────────────────────────────────────────────────────┤
│                                                                              │
│  □ 1x Wemos D1 R1 o R2                                                      │
│      (la scheda blu con il chip WiFi)                                       │
│      Cerca: "Wemos D1 R1" o "Wemos D1 R2" su Amazon/AliExpress              │
│      Costo: ~5-10€                                                          │
│                                                                              │
│  □ 1x L293D Motor Shield                                                    │
│      (la scheda con i chip neri e i morsetti blu)                           │
│      Cerca: "L293D motor shield Arduino" su Amazon/AliExpress               │
│      Costo: ~3-8€                                                           │
│                                                                              │
│  □ 4x Motori DC con ruote                                                   │
│      (di solito si comprano nel kit chassis)                                │
│      Cerca: "4WD robot car chassis kit" su Amazon/AliExpress                │
│      Costo: ~15-25€                                                         │
│                                                                              │
│  □ 1x Porta batterie (4 o 6 pile AA)                                        │
│      (di solito incluso nel kit chassis)                                    │
│                                                                              │
│  □ 4-6x Batterie AA                                                         │
│      (meglio ricaricabili)                                                  │
│                                                                              │
│  □ 1x Cavo USB (tipo che hai nel cassetto)                                  │
│      Micro-USB o USB-C a seconda della tua Wemos                            │
│                                                                              │
│  □ 1x Cacciavite piccolo a croce                                            │
│      (per i morsetti dei motori)                                            │
│                                                                              │
│  □ 1x Computer (Windows/Mac/Linux)                                          │
│                                                                              │
│  □ 1x Smartphone Android                                                    │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Come Riconoscere i Componenti

### La Wemos D1 R1/R2 (Il "Cervello")

```
    ┌─────────────────────────────────────────────────────────────────┐
    │                                                                 │
    │   Questa è la Wemos D1 R1/R2:                                  │
    │                                                                 │
    │   - Forma rettangolare come una carta di credito grande        │
    │   - Colore BLU                                                 │
    │   - Ha un chip metallico (il modulo WiFi ESP-8266)             │
    │   - Ha una porta USB per collegarla al computer                │
    │   - Ha due file di "buchini" (pin) sui lati lunghi             │
    │                                                                 │
    │   ┌─────────────────────────────────────────────────────────┐  │
    │   │  ○ ○ ○ ○ ○ ○ ○ ○ ○ ○ ○ ○ ○ ○ ○ ○ ○ ○ ○              │  │
    │   │                                                         │  │
    │   │         ┌─────────────────────┐                         │  │
    │   │         │                     │   ← Chip WiFi           │  │
    │   │         │     ESP-8266        │     (metallico)         │  │
    │   │         │                     │                         │  │
    │   │         └─────────────────────┘                         │  │
    │   │                                                         │  │
    │   │  ▓▓▓▓▓▓▓                                               │  │
    │   │  ║ USB ║  ← Porta USB (per programmare)                │  │
    │   │  ▓▓▓▓▓▓▓                                               │  │
    │   │                                                         │  │
    │   │  ○ ○ ○ ○ ○ ○ ○ ○ ○ ○ ○ ○ ○ ○ ○ ○ ○ ○ ○              │  │
    │   └─────────────────────────────────────────────────────────┘  │
    │                                                                 │
    │   ATTENZIONE: NON confondere con Wemos D1 Mini (molto più      │
    │   piccola). Quella giusta ha la forma di Arduino UNO.          │
    │                                                                 │
    └─────────────────────────────────────────────────────────────────┘
```

### Il L293D Motor Shield (Il "Driver Motori")

```
    ┌─────────────────────────────────────────────────────────────────┐
    │                                                                 │
    │   Questo è il L293D Motor Shield:                              │
    │                                                                 │
    │   - Forma rettangolare, stesse dimensioni della Wemos          │
    │   - Ha DUE chip neri grandi (i driver L293D)                   │
    │   - Ha UN chip nero piccolo (lo shift register 74HC595)        │
    │   - Ha 4 morsetti BLU a vite (per collegare i motori)          │
    │   - Sotto ha dei "piedini" che entrano nella Wemos             │
    │                                                                 │
    │   ┌─────────────────────────────────────────────────────────┐  │
    │   │                                                         │  │
    │   │    [M1]  [M2]                    [M3]  [M4]             │  │
    │   │     ↑     ↑                       ↑     ↑               │  │
    │   │     Morsetti blu a vite (per i motori)                  │  │
    │   │                                                         │  │
    │   │   ┌─────────────┐          ┌─────────────┐              │  │
    │   │   │             │          │             │              │  │
    │   │   │   L293D     │          │   L293D     │   ← Chip     │  │
    │   │   │    #1       │          │    #2       │     grandi   │  │
    │   │   │             │          │             │     (neri)   │  │
    │   │   └─────────────┘          └─────────────┘              │  │
    │   │                                                         │  │
    │   │              ┌─────────┐                                │  │
    │   │              │ 74HC595 │  ← Chip piccolo                │  │
    │   │              └─────────┘                                │  │
    │   │                                                         │  │
    │   │   ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼        │  │
    │   │   (piedini che vanno nella Wemos)                       │  │
    │   └─────────────────────────────────────────────────────────┘  │
    │                                                                 │
    └─────────────────────────────────────────────────────────────────┘
```

### I Motori DC (Le "Gambe")

```
    ┌─────────────────────────────────────────────────────────────────┐
    │                                                                 │
    │   Motore DC con riduttore:                                     │
    │                                                                 │
    │        ┌───────────────┐                                       │
    │        │   ┌───────┐   │                                       │
    │        │   │MOTORE │   │                                       │
    │        │   └───┬───┘   │                                       │
    │        │       │       │                                       │
    │        │   ╔═══╧═══╗   │  ← Riduttore (scatola ingranaggi)    │
    │        │   ║       ║   │                                       │
    │        │   ╚═══╤═══╝   │                                       │
    │        └───────┼───────┘                                       │
    │                │                                                │
    │            ════╪════  ← Asse (qui va la ruota)                 │
    │                                                                 │
    │        ~~~~~  ~~~~~   ← Due fili (rosso e nero, o due neri)   │
    │                                                                 │
    │   Ne servono 4 (uno per ogni ruota)                            │
    │                                                                 │
    └─────────────────────────────────────────────────────────────────┘
```

---

# 2. INSTALLARE ARDUINO IDE

Arduino IDE è il programma che userai per "programmare" la Wemos. È gratuito.

## Passo 2.1: Scarica Arduino IDE

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   1. Apri il browser (Chrome, Firefox, Edge...)                             │
│                                                                              │
│   2. Vai su:  https://www.arduino.cc/en/software                            │
│                                                                              │
│   3. Scorri fino a "DOWNLOAD OPTIONS"                                       │
│                                                                              │
│   4. Clicca sulla versione per il tuo sistema:                              │
│                                                                              │
│      ┌─────────────────────────────────────────────────────────────────┐    │
│      │                                                                 │    │
│      │   Se hai WINDOWS:                                               │    │
│      │   → Clicca "Windows Win 10 and newer, 64 bits"                  │    │
│      │                                                                 │    │
│      │   Se hai MAC:                                                   │    │
│      │   → Clicca "macOS 10.15 or newer, 64 bits"                     │    │
│      │                                                                 │    │
│      │   Se hai LINUX:                                                 │    │
│      │   → Clicca "Linux AppImage 64 bits"                             │    │
│      │                                                                 │    │
│      └─────────────────────────────────────────────────────────────────┘    │
│                                                                              │
│   5. Apparirà una pagina che chiede donazione:                              │
│      → Clicca "JUST DOWNLOAD" (scarica gratis)                              │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Passo 2.2: Installa Arduino IDE

### Su Windows:

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   1. Apri la cartella "Download" sul tuo computer                           │
│                                                                              │
│   2. Cerca il file scaricato (es: arduino-ide_2.x.x_Windows_64bit.exe)     │
│                                                                              │
│   3. Fai DOPPIO CLICK sul file                                              │
│                                                                              │
│   4. Se Windows chiede "Vuoi consentire a questa app...":                   │
│      → Clicca "Sì"                                                          │
│                                                                              │
│   5. Segui le schermate:                                                    │
│                                                                              │
│      ┌─────────────────────────────────────┐                                │
│      │  [I Agree]                          │  ← Clicca "I Agree"           │
│      └─────────────────────────────────────┘                                │
│                         ↓                                                    │
│      ┌─────────────────────────────────────┐                                │
│      │  [Next]                             │  ← Clicca "Next"              │
│      └─────────────────────────────────────┘                                │
│                         ↓                                                    │
│      ┌─────────────────────────────────────┐                                │
│      │  [Install]                          │  ← Clicca "Install"           │
│      └─────────────────────────────────────┘                                │
│                         ↓                                                    │
│      (Attendi qualche minuto...)                                            │
│                         ↓                                                    │
│      ┌─────────────────────────────────────┐                                │
│      │  [Finish]                           │  ← Clicca "Finish"            │
│      └─────────────────────────────────────┘                                │
│                                                                              │
│   6. Arduino IDE è installato!                                              │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

### Su Mac:

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   1. Apri la cartella "Download"                                            │
│                                                                              │
│   2. Fai DOPPIO CLICK sul file .dmg scaricato                               │
│                                                                              │
│   3. Si apre una finestra con l'icona di Arduino                            │
│                                                                              │
│   4. Trascina l'icona Arduino nella cartella "Applications":                │
│                                                                              │
│      ┌───────────────────────────────────────────┐                          │
│      │                                           │                          │
│      │    [Arduino]  ─────→   [Applications]     │                          │
│      │                                           │                          │
│      └───────────────────────────────────────────┘                          │
│                                                                              │
│   5. Vai in "Applications" e apri Arduino IDE                               │
│                                                                              │
│   6. Se Mac dice "impossibile aprire perché non verificato":                │
│      → Vai in Preferenze di Sistema → Sicurezza → "Apri comunque"          │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Passo 2.3: Apri Arduino IDE

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   1. Cerca "Arduino IDE" nel menu Start (Windows) o Launchpad (Mac)         │
│                                                                              │
│   2. Clicca per aprirlo                                                     │
│                                                                              │
│   3. La prima volta ci mette un po' a caricare (normale!)                   │
│                                                                              │
│   4. Vedrai questa schermata:                                               │
│                                                                              │
│   ┌─────────────────────────────────────────────────────────────────────┐   │
│   │  File  Edit  Sketch  Tools  Help                                    │   │
│   ├─────────────────────────────────────────────────────────────────────┤   │
│   │  [✓]  [→]              [Upload]  [Serial Monitor]                   │   │
│   ├─────────────────────────────────────────────────────────────────────┤   │
│   │                                                                     │   │
│   │  void setup() {                                                     │   │
│   │    // put your setup code here                                      │   │
│   │  }                                                                  │   │
│   │                                                                     │   │
│   │  void loop() {                                                      │   │
│   │    // put your main code here                                       │   │
│   │  }                                                                  │   │
│   │                                                                     │   │
│   ├─────────────────────────────────────────────────────────────────────┤   │
│   │  Output                                                             │   │
│   └─────────────────────────────────────────────────────────────────────┘   │
│                                                                              │
│   PERFETTO! Arduino IDE è pronto.                                           │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

---

# 3. CONFIGURARE ARDUINO PER WEMOS D1

Arduino IDE non conosce la Wemos D1 di default. Dobbiamo "insegnargli" cos'è.

## Passo 3.1: Aggiungi il Supporto ESP8266

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   1. In Arduino IDE, vai nel menu:                                          │
│                                                                              │
│      File  →  Preferences    (su Mac: Arduino IDE → Preferences)           │
│      ─────    ───────────                                                   │
│                                                                              │
│   2. Si apre questa finestra:                                               │
│                                                                              │
│   ┌───────────────────────────────────────────────────────────────────┐     │
│   │  Preferences                                                      │     │
│   ├───────────────────────────────────────────────────────────────────┤     │
│   │                                                                   │     │
│   │  Sketchbook location: [________________________]                  │     │
│   │                                                                   │     │
│   │  ...                                                              │     │
│   │                                                                   │     │
│   │  Additional boards manager URLs:                                  │     │
│   │  ┌─────────────────────────────────────────────────────────┐     │     │
│   │  │                                                         │ [📋]│     │
│   │  └─────────────────────────────────────────────────────────┘     │     │
│   │         ↑                                                         │     │
│   │         COPIA QUI L'URL (vedi sotto)                             │     │
│   │                                                                   │     │
│   └───────────────────────────────────────────────────────────────────┘     │
│                                                                              │
│   3. Nel campo "Additional boards manager URLs" COPIA E INCOLLA questo:     │
│                                                                              │
│   ┌─────────────────────────────────────────────────────────────────────┐   │
│   │  https://arduino.esp8266.com/stable/package_esp8266com_index.json   │   │
│   └─────────────────────────────────────────────────────────────────────┘   │
│      ↑                                                                       │
│      COPIA ESATTAMENTE QUESTO (seleziona tutto, Ctrl+C, poi Ctrl+V)         │
│                                                                              │
│   4. Clicca "OK" per salvare                                                │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Passo 3.2: Installa il Pacchetto ESP8266

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   1. Vai nel menu:                                                          │
│                                                                              │
│      Tools  →  Board  →  Boards Manager...                                  │
│      ─────     ─────     ───────────────                                    │
│                                                                              │
│   2. Si apre il "Boards Manager" (gestore schede)                           │
│                                                                              │
│   3. Nella barra di ricerca in alto, scrivi:                                │
│                                                                              │
│      ┌─────────────────────────────┐                                        │
│      │  esp8266                    │  ← Scrivi questo                       │
│      └─────────────────────────────┘                                        │
│                                                                              │
│   4. Apparirà un risultato "esp8266 by ESP8266 Community"                   │
│                                                                              │
│   ┌───────────────────────────────────────────────────────────────────┐     │
│   │                                                                   │     │
│   │  esp8266 by ESP8266 Community                                     │     │
│   │                                                                   │     │
│   │  Boards included in this package:                                 │     │
│   │  Generic ESP8266, Wemos D1, NodeMCU...                           │     │
│   │                                                                   │     │
│   │                                    [ INSTALL ]  ← CLICCA QUI!    │     │
│   │                                                                   │     │
│   └───────────────────────────────────────────────────────────────────┘     │
│                                                                              │
│   5. Clicca "INSTALL"                                                       │
│                                                                              │
│   6. ATTENDI! Ci vogliono 2-5 minuti (scarica ~150 MB)                      │
│                                                                              │
│      ┌─────────────────────────────────────────────────────────────────┐    │
│      │  ████████████░░░░░░░░░░░░░░░░░░  45%  Installing...            │    │
│      └─────────────────────────────────────────────────────────────────┘    │
│                                                                              │
│   7. Quando finisce, vedrai "INSTALLED" accanto al pacchetto               │
│                                                                              │
│   8. Chiudi il Boards Manager                                               │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Passo 3.3: Seleziona la Scheda Wemos D1

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   1. Vai nel menu:                                                          │
│                                                                              │
│      Tools  →  Board  →  esp8266  →  LOLIN(WEMOS) D1 R2 & mini             │
│      ─────     ─────     ───────     ─────────────────────────              │
│                                                                              │
│   Percorso completo (clicca in ordine):                                     │
│                                                                              │
│   ┌─────────────────────────────────────────────────────────────────────┐   │
│   │                                                                     │   │
│   │  Tools ──┐                                                          │   │
│   │          ↓                                                          │   │
│   │        Board ──┐                                                    │   │
│   │                ↓                                                    │   │
│   │              esp8266 ──┐                                            │   │
│   │                        ↓                                            │   │
│   │                      • Generic ESP8266 Module                       │   │
│   │                      • Generic ESP8285 Module                       │   │
│   │                      • ...                                          │   │
│   │                      • LOLIN(WEMOS) D1 R2 & mini  ← SELEZIONA!     │   │
│   │                      • LOLIN(WEMOS) D1 mini pro                     │   │
│   │                      • ...                                          │   │
│   │                                                                     │   │
│   └─────────────────────────────────────────────────────────────────────┘   │
│                                                                              │
│   2. Dopo aver selezionato, in basso a destra vedrai:                       │
│                                                                              │
│      "LOLIN(WEMOS) D1 R2 & mini"                                           │
│                                                                              │
│   PERFETTO! Arduino ora sa che useremo una Wemos D1.                        │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Passo 3.4: Installa i Driver USB (SE NECESSARIO)

La Wemos D1 usa un chip per comunicare via USB. Potrebbe servirti un driver.

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   COME CAPIRE SE TI SERVE IL DRIVER:                                        │
│                                                                              │
│   1. Collega la Wemos D1 al computer con il cavo USB                        │
│                                                                              │
│   2. In Arduino IDE vai su: Tools → Port                                    │
│                                                                              │
│   3. SE VEDI una porta tipo:                                                │
│      • "COM3" o "COM4" (Windows)                                            │
│      • "/dev/cu.usbserial-xxx" (Mac)                                        │
│      • "/dev/ttyUSB0" (Linux)                                               │
│      → NON ti serve il driver, vai al passo 4!                              │
│                                                                              │
│   4. SE NON VEDI nessuna porta:                                             │
│      → Devi installare il driver (vedi sotto)                               │
│                                                                              │
├─────────────────────────────────────────────────────────────────────────────┤
│                                                                              │
│   INSTALLARE IL DRIVER CH340:                                               │
│                                                                              │
│   Il chip USB sulla Wemos si chiama CH340. Ecco come installare il driver:  │
│                                                                              │
│   1. Vai su: https://www.wch-ic.com/downloads/CH341SER_ZIP.html             │
│                                                                              │
│   2. Clicca "Download" per scaricare il file ZIP                            │
│                                                                              │
│   3. Estrai il file ZIP (click destro → "Estrai tutto")                     │
│                                                                              │
│   4. Apri la cartella estratta                                              │
│                                                                              │
│   5. Su Windows: Fai doppio click su "SETUP.EXE" e clicca "INSTALL"         │
│      Su Mac: Fai doppio click su "CH34x_Install_V1.5.pkg" e segui le istruzioni │
│                                                                              │
│   6. RIAVVIA IL COMPUTER                                                    │
│                                                                              │
│   7. Ricollega la Wemos e controlla di nuovo Tools → Port                   │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

---

# 4. MONTARE L'HARDWARE

Ora assembliamo fisicamente il robot!

## Passo 4.1: Prepara il Telaio (Chassis)

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   Se hai comprato un kit "4WD robot chassis":                               │
│                                                                              │
│   1. Apri la scatola e identifica i pezzi:                                  │
│                                                                              │
│      ┌─────────────────────────────────────────────────────────────────┐    │
│      │                                                                 │    │
│      │  • 2 piastre di plastica (sopra e sotto)                       │    │
│      │  • 4 motori con ingranaggi                                     │    │
│      │  • 4 ruote                                                      │    │
│      │  • Viti, dadi, distanziali                                     │    │
│      │  • Porta batterie                                               │    │
│      │  • (A volte) Istruzioni di montaggio                           │    │
│      │                                                                 │    │
│      └─────────────────────────────────────────────────────────────────┘    │
│                                                                              │
│   2. Monta i 4 motori sulla piastra inferiore:                              │
│                                                                              │
│      ┌─────────────────────────────────────────┐                            │
│      │                                         │                            │
│      │    [M1]                     [M3]       │   Usa le viti per          │
│      │     │                         │        │   fissare i motori         │
│      │     ●═════╗           ╔═════●         │   ai supporti              │
│      │           ║           ║               │                            │
│      │           ║  PIASTRA  ║               │                            │
│      │           ║ INFERIORE ║               │                            │
│      │           ║           ║               │                            │
│      │     ●═════╝           ╚═════●         │                            │
│      │     │                         │        │                            │
│      │    [M2]                     [M4]       │                            │
│      │                                         │                            │
│      └─────────────────────────────────────────┘                            │
│                                                                              │
│   3. Monta le 4 ruote sugli assi dei motori (basta spingerle)              │
│                                                                              │
│   4. (Opzionale) Monta la piastra superiore con i distanziali              │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Passo 4.2: Monta lo Shield sulla Wemos

**QUESTA È LA PARTE BELLA: È SEMPLICISSIMO!**

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   Lo shield si INCASTRA direttamente sulla Wemos. Non servono cavi!        │
│                                                                              │
│   PRIMA (componenti separati):                                              │
│                                                                              │
│        L293D MOTOR SHIELD                                                    │
│        ┌─────────────────────────────────┐                                  │
│        │  [M1] [M2]         [M3] [M4]    │                                  │
│        │                                 │                                  │
│        │    ┌───────┐    ┌───────┐      │                                  │
│        │    │ L293D │    │ L293D │      │                                  │
│        │    └───────┘    └───────┘      │                                  │
│        │                                 │                                  │
│        │  ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼  │  ← Piedini maschi               │
│        └───────────────┬─────────────────┘                                  │
│                        │                                                     │
│                        │  SPINGI GIÙ                                        │
│                        ↓                                                     │
│        ┌───────────────────────────────────┐                                │
│        │  ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲ ▲    │  ← Pin femmina                 │
│        │                                   │                                │
│        │  ┌─────────────────┐              │                                │
│        │  │    ESP-8266     │              │                                │
│        │  └─────────────────┘              │                                │
│        │                                   │                                │
│        │     WEMOS D1 R1/R2                │                                │
│        │                                   │                                │
│        │  [USB]                            │                                │
│        └───────────────────────────────────┘                                │
│                                                                              │
│                                                                              │
│   DOPO (shield montato):                                                    │
│                                                                              │
│        ┌─────────────────────────────────┐                                  │
│        │  [M1] [M2]         [M3] [M4]    │  ← Shield SOPRA                 │
│        │                                 │                                  │
│        │    ┌───────┐    ┌───────┐      │                                  │
│        │    │ L293D │    │ L293D │      │                                  │
│        │    └───────┘    └───────┘      │                                  │
│        ├─────────────────────────────────┤                                  │
│        │                                 │                                  │
│        │  ┌─────────────────┐            │                                  │
│        │  │    ESP-8266     │            │  ← Wemos SOTTO                  │
│        │  └─────────────────┘            │                                  │
│        │                                 │                                  │
│        │  [USB]                          │                                  │
│        └─────────────────────────────────┘                                  │
│                                                                              │
│                                                                              │
│   ISTRUZIONI:                                                               │
│                                                                              │
│   1. Prendi la Wemos D1 e appoggiala sul tavolo                            │
│                                                                              │
│   2. Prendi lo shield e allinea i piedini sopra i pin della Wemos          │
│                                                                              │
│   3. ATTENZIONE ALL'ORIENTAMENTO:                                           │
│      - La porta USB della Wemos deve restare accessibile!                   │
│      - I morsetti M1, M2 devono stare dallo stesso lato dei pin D0-D7      │
│                                                                              │
│   4. Spingi delicatamente ma con fermezza fino a che lo shield             │
│      è completamente inserito                                               │
│                                                                              │
│   5. Controlla che tutti i pin siano entrati (nessuno piegato)             │
│                                                                              │
│                                                                              │
│      CORRETTO ✓                     SBAGLIATO ✗                            │
│      ───────────                    ────────────                            │
│      ┌─────────┐                    ┌─────────┐                             │
│      │ Shield  │                    │ Shield  │   Pin piegati              │
│      └─┬─┬─┬─┬─┘                    └─┬─┬┬──┬─┘   o fuori!                 │
│        │ │ │ │                        │ │││  │                              │
│      ┌─┴─┴─┴─┴─┐                    ┌─┴─┴┴┴──┐                             │
│      │ Wemos   │                    │ Wemos   │                             │
│      └─────────┘                    └─────────┘                             │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Passo 4.3: Collega i Motori

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   Ogni motore ha 2 fili. Devi collegarli ai morsetti blu sullo shield.     │
│                                                                              │
│   SCHEMA DI COLLEGAMENTO (visto dall'alto):                                 │
│                                                                              │
│                         AVANTI (direzione di marcia)                        │
│                               ↑                                              │
│        ┌──────────────────────────────────────────────┐                     │
│        │                                              │                     │
│        │       MOTORE 1              MOTORE 3        │                     │
│        │        (M1)                  (M3)           │                     │
│        │         ○                     ○             │                     │
│        │        /│\                   /│\            │                     │
│        │         │                     │             │                     │
│        │        ~~~                   ~~~            │  ← Fili motori      │
│        │        │ │                   │ │            │                     │
│        │        │ │                   │ │            │                     │
│        │    ┌───┴─┴───────────────────┴─┴───┐       │                     │
│        │    │  [M1]  [M2]      [M3]  [M4]   │       │  ← Morsetti shield  │
│        │    │                               │       │                     │
│        │    │       MOTOR SHIELD            │       │                     │
│        │    │        + WEMOS                │       │                     │
│        │    │                               │       │                     │
│        │    └───┬─┬───────────────────┬─┬───┘       │                     │
│        │        │ │                   │ │            │                     │
│        │        │ │                   │ │            │                     │
│        │        ~~~                   ~~~            │  ← Fili motori      │
│        │         │                     │             │                     │
│        │        \│/                   \│/            │                     │
│        │         ○                     ○             │                     │
│        │        (M2)                  (M4)           │                     │
│        │       MOTORE 2              MOTORE 4        │                     │
│        │                                              │                     │
│        └──────────────────────────────────────────────┘                     │
│                               ↓                                              │
│                            INDIETRO                                         │
│                                                                              │
│                                                                              │
│   ISTRUZIONI DETTAGLIATE:                                                   │
│                                                                              │
│   1. Prendi un cacciavite piccolo a croce                                  │
│                                                                              │
│   2. Per ogni motore:                                                       │
│                                                                              │
│      a) Allenta le 2 viti del morsetto corrispondente                      │
│                                                                              │
│         ┌─────────┐                                                         │
│         │ [─] [─] │  ← Viti da allentare (gira in senso antiorario)        │
│         │  ○   ○  │  ← Fori dove entrano i fili                            │
│         └─────────┘                                                         │
│                                                                              │
│      b) Inserisci i 2 fili del motore nei 2 fori                           │
│                                                                              │
│      c) Stringi le viti per fissare i fili (gira in senso orario)          │
│                                                                              │
│      d) Tira delicatamente i fili per verificare che siano fissi           │
│                                                                              │
│   3. Non importa quale filo va in quale foro del morsetto!                 │
│      Se il motore gira al contrario, basta invertire i 2 fili dopo.        │
│                                                                              │
│                                                                              │
│   COLLEGAMENTO BATTERIE:                                                    │
│                                                                              │
│   Sullo shield c'è anche un morsetto per le batterie (EXT_PWR):            │
│                                                                              │
│        ┌───────────────────────────────────────┐                            │
│        │                                       │                            │
│        │   [EXT_PWR]     [PWR] ← Se c'è un    │                            │
│        │    (+) (-)       [ ]    jumper qui,  │                            │
│        │     ↑   ↑              RIMUOVILO!    │                            │
│        │     │   │                             │                            │
│        │     │   └──── Filo NERO (-)          │                            │
│        │     │                                 │                            │
│        │     └──────── Filo ROSSO (+)         │                            │
│        │                                       │                            │
│        └───────────────────────────────────────┘                            │
│                                                                              │
│   IMPORTANTE: Se vedi un piccolo "ponte" di plastica (jumper) vicino       │
│   a "PWR", RIMUOVILO tirandolo con le dita. Serve per separare             │
│   l'alimentazione motori da quella della Wemos.                             │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Passo 4.4: Fissa l'Elettronica al Telaio

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   Ora devi fissare la Wemos+Shield al telaio del robot.                    │
│                                                                              │
│   OPZIONI:                                                                  │
│                                                                              │
│   1. VITI E DISTANZIALI (metodo pro)                                       │
│      - Usa le viti M3 e i distanziali del kit                              │
│      - Fissa la Wemos alla piastra superiore                               │
│                                                                              │
│   2. BIADESIVO O VELCRO (metodo facile)                                    │
│      - Metti un pezzo di biadesivo sotto la Wemos                          │
│      - Attaccala alla piastra                                               │
│      - Pratico perché puoi staccarla facilmente                            │
│                                                                              │
│   3. ELASTICI (metodo MacGyver)                                            │
│      - Usa elastici per tenere ferma la scheda                             │
│      - Funziona!                                                            │
│                                                                              │
│                                                                              │
│   VISTA FINALE DEL ROBOT:                                                   │
│                                                                              │
│                    AVANTI                                                    │
│                      ↑                                                       │
│        ┌──────────────────────────────────┐                                 │
│        │   ╔══════════════════════════╗   │                                 │
│        │   ║     WEMOS + SHIELD       ║   │                                 │
│        │   ║  [USB]                   ║   │  ← USB accessibile              │
│        │   ╚══════════════════════════╝   │    per programmare              │
│        │                                  │                                 │
│        │   ┌──────────────────────────┐   │                                 │
│        │   │    PORTA BATTERIE        │   │                                 │
│        │   │   ○ ○ ○ ○ ○ ○           │   │                                 │
│        │   │   (4-6 pile AA)         │   │                                 │
│        │   └──────────────────────────┘   │                                 │
│       ═╪═                              ═╪═│  ← Ruote                        │
│        │                                  │                                 │
│       ═╪═                              ═╪═│                                 │
│        │                                  │                                 │
│        └──────────────────────────────────┘                                 │
│                      ↓                                                       │
│                   INDIETRO                                                   │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

---

# 5. CARICARE IL PROGRAMMA

Ora carichiamo il software sulla Wemos!

## Passo 5.1: Apri il Progetto in Arduino IDE

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   1. Apri Arduino IDE                                                       │
│                                                                              │
│   2. Vai nel menu: File → Open...                                           │
│                                                                              │
│   3. Naviga fino alla cartella del progetto:                                │
│                                                                              │
│      wemos-d1/src/robot_car/                                                │
│                                                                              │
│   4. Seleziona il file: robot_car.ino                                       │
│                                                                              │
│   5. Clicca "Apri"                                                          │
│                                                                              │
│   6. Si apriranno DIVERSE schede (è normale!):                              │
│                                                                              │
│   ┌─────────────────────────────────────────────────────────────────────┐   │
│   │  [robot_car.ino] [motor_shield.h] [motor_shield.cpp] [wifi_...]     │   │
│   ├─────────────────────────────────────────────────────────────────────┤   │
│   │                                                                     │   │
│   │  /**                                                                │   │
│   │   * robot_car.ino                                                   │   │
│   │   *                                                                 │   │
│   │   * Firmware per auto robotica...                                   │   │
│   │   */                                                                │   │
│   │                                                                     │   │
│   │  #include "motor_shield.h"                                          │   │
│   │  #include "wifi_controller.h"                                       │   │
│   │  ...                                                                │   │
│   │                                                                     │   │
│   └─────────────────────────────────────────────────────────────────────┘   │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Passo 5.2: Collega la Wemos al Computer

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   1. Prendi il cavo USB                                                     │
│                                                                              │
│   2. Collega un'estremità alla porta USB della WEMOS                        │
│                                                                              │
│        ┌───────────────────────────────────┐                                │
│        │                                   │                                │
│        │  ▓▓▓▓▓▓▓▓                         │                                │
│        │  ║ USB  ║════════════════════     │  ← Cavo USB                   │
│        │  ▓▓▓▓▓▓▓▓                    ║    │                                │
│        │                              ║    │                                │
│        │      WEMOS D1                ║    │                                │
│        │                              ║    │                                │
│        └──────────────────────────────╫────┘                                │
│                                       ║                                      │
│                                       ║                                      │
│                                       ↓                                      │
│                              ╔════════════════╗                             │
│                              ║   COMPUTER     ║                             │
│                              ║   [USB PORT]   ║                             │
│                              ╚════════════════╝                             │
│                                                                              │
│   3. Collega l'altra estremità a una porta USB del computer                │
│                                                                              │
│   4. La Wemos si accenderà (vedrai un LED lampeggiare)                     │
│                                                                              │
│   NOTA: NON inserire ancora le batterie! Per ora alimentiamo via USB.      │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Passo 5.3: Seleziona la Porta

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   1. In Arduino IDE vai su: Tools → Port                                    │
│                                                                              │
│   2. Vedrai una lista di porte. Seleziona quella della Wemos:               │
│                                                                              │
│      SU WINDOWS:                                                            │
│      ┌─────────────────────────────────────────────────────────────────┐    │
│      │  Tools → Port →                                                 │    │
│      │                  • COM1                                         │    │
│      │                  • COM3  (USB-SERIAL CH340)  ← SELEZIONA!      │    │
│      │                  • COM4                                         │    │
│      └─────────────────────────────────────────────────────────────────┘    │
│                                                                              │
│      SU MAC:                                                                │
│      ┌─────────────────────────────────────────────────────────────────┐    │
│      │  Tools → Port →                                                 │    │
│      │                  • /dev/cu.Bluetooth-Incoming-Port              │    │
│      │                  • /dev/cu.usbserial-1420  ← SELEZIONA!        │    │
│      │                  • /dev/cu.wchusbserial1420                     │    │
│      └─────────────────────────────────────────────────────────────────┘    │
│                                                                              │
│      SU LINUX:                                                              │
│      ┌─────────────────────────────────────────────────────────────────┐    │
│      │  Tools → Port →                                                 │    │
│      │                  • /dev/ttyUSB0  ← SELEZIONA!                  │    │
│      │                  • /dev/ttyACM0                                 │    │
│      └─────────────────────────────────────────────────────────────────┘    │
│                                                                              │
│                                                                              │
│   TRUCCO: Se non sai quale porta è la Wemos:                               │
│                                                                              │
│   1. Scollega il cavo USB dalla Wemos                                      │
│   2. Guarda quali porte ci sono in Tools → Port                            │
│   3. Ricollega il cavo USB                                                 │
│   4. Guarda di nuovo Tools → Port                                          │
│   5. La porta NUOVA che appare è quella della Wemos!                       │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Passo 5.4: Carica il Programma!

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   1. Verifica le impostazioni:                                              │
│                                                                              │
│      ┌─────────────────────────────────────────────────────────────────┐    │
│      │  Board: "LOLIN(WEMOS) D1 R2 & mini"     ← Deve esserci questo  │    │
│      │  Port:  "COM3" (o simile)               ← Deve esserci questo  │    │
│      └─────────────────────────────────────────────────────────────────┘    │
│                                                                              │
│   2. Clicca il pulsante UPLOAD (freccia verso destra):                      │
│                                                                              │
│      ┌─────────────────────────────────────────────────────────────────┐    │
│      │                                                                 │    │
│      │    [✓]    [ → ]    ← CLICCA QUESTA FRECCIA!                    │    │
│      │                                                                 │    │
│      └─────────────────────────────────────────────────────────────────┘    │
│                                                                              │
│   3. Cosa succede ora:                                                      │
│                                                                              │
│      a) COMPILAZIONE (trasforma il codice in linguaggio macchina)          │
│                                                                              │
│         ┌─────────────────────────────────────────────────────────────┐     │
│         │  Compiling sketch...                                        │     │
│         │  ████████████████░░░░░░░░░░░░░░░░  50%                     │     │
│         └─────────────────────────────────────────────────────────────┘     │
│                                                                              │
│         Ci vuole circa 1-2 minuti la prima volta.                          │
│                                                                              │
│      b) UPLOAD (trasferisce il programma alla Wemos)                       │
│                                                                              │
│         ┌─────────────────────────────────────────────────────────────┐     │
│         │  Uploading...                                               │     │
│         │  ████████████████████████████████  100%                    │     │
│         │                                                             │     │
│         │  Done uploading.     ← SUCCESSO!                           │     │
│         └─────────────────────────────────────────────────────────────┘     │
│                                                                              │
│   4. Se vedi "Done uploading" HAI FINITO! Il programma è caricato.         │
│                                                                              │
│                                                                              │
│   ERRORI COMUNI:                                                            │
│                                                                              │
│   • "No such file or directory" → Il driver non è installato               │
│   • "Access denied" → Chiudi altri programmi che usano la porta            │
│   • "espcomm_upload_mem failed" → Prova a tenere premuto il pulsante       │
│                                    RESET sulla Wemos mentre carica          │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

---

# 6. PRIMO TEST DEI MOTORI

Prima di usare il WiFi, testiamo che i motori funzionino!

## Passo 6.1: Attiva la Modalità Test

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   1. In Arduino IDE, vai alla scheda "robot_car.ino"                        │
│                                                                              │
│   2. Cerca questa riga (circa riga 29):                                     │
│                                                                              │
│      #define TEST_MODE false                                                │
│                        ─────                                                 │
│                                                                              │
│   3. Cambia "false" in "true":                                              │
│                                                                              │
│      #define TEST_MODE true                                                 │
│                        ────                                                  │
│                                                                              │
│   4. Ricarica il programma (clicca di nuovo la freccia →)                   │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Passo 6.2: Inserisci le Batterie

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   I motori hanno bisogno di più corrente di quella che può fornire l'USB.   │
│   Ora inseriamo le batterie!                                                │
│                                                                              │
│   1. Inserisci 4-6 batterie AA nel porta batterie                          │
│                                                                              │
│      ┌─────────────────────────────────────────────────────────────────┐    │
│      │                                                                 │    │
│      │     ┌────┐  ┌────┐  ┌────┐  ┌────┐  ┌────┐  ┌────┐            │    │
│      │     │ +  │  │ -  │  │ +  │  │ -  │  │ +  │  │ -  │            │    │
│      │     │    │  │    │  │    │  │    │  │    │  │    │            │    │
│      │     │ AA │  │ AA │  │ AA │  │ AA │  │ AA │  │ AA │            │    │
│      │     │    │  │    │  │    │  │    │  │    │  │    │            │    │
│      │     │ -  │  │ +  │  │ -  │  │ +  │  │ -  │  │ +  │            │    │
│      │     └────┘  └────┘  └────┘  └────┘  └────┘  └────┘            │    │
│      │                                                                 │    │
│      │     RISPETTA LA POLARITÀ! (+) e (-) come indicato.             │    │
│      │                                                                 │    │
│      └─────────────────────────────────────────────────────────────────┘    │
│                                                                              │
│   2. Assicurati che i fili del porta batterie siano collegati a EXT_PWR:   │
│                                                                              │
│      • Filo ROSSO → morsetto (+)                                           │
│      • Filo NERO  → morsetto (-)                                           │
│                                                                              │
│   ATTENZIONE: Se inverti la polarità puoi danneggiare la scheda!           │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Passo 6.3: Esegui il Test

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   1. Tieni il robot SOLLEVATO (ruote in aria) o su un oggetto               │
│      così le ruote possono girare liberamente                               │
│                                                                              │
│        ┌──────────────────────────┐                                         │
│        │                          │                                         │
│        │       ┌──────────┐       │                                         │
│        │       │  ROBOT   │       │                                         │
│        │       └──────────┘       │                                         │
│        │         ╱    ╲          │                                         │
│        │        ╱      ╲         │  ← Solleva il robot!                    │
│        │    ═══╱════════╲═══     │    Le ruote devono essere in aria.      │
│        │      RUOTE LIBERE       │                                         │
│        │                          │                                         │
│        └──────────────────────────┘                                         │
│                                                                              │
│   2. Premi il pulsante RESET sulla Wemos (o scollega e ricollega USB)      │
│                                                                              │
│   3. Il test automatico partirà! Dura circa 20 secondi.                    │
│                                                                              │
│   4. Cosa vedrai:                                                           │
│                                                                              │
│      ┌─────────────────────────────────────────────────────────────────┐    │
│      │  TEST                          │  COSA SUCCEDE                  │    │
│      ├────────────────────────────────┼────────────────────────────────┤    │
│      │  1. AVANTI                     │  Tutte le ruote girano →       │    │
│      │  2. INDIETRO                   │  Tutte le ruote girano ←       │    │
│      │  3. SINISTRA                   │  Solo ruote destre girano      │    │
│      │  4. DESTRA                     │  Solo ruote sinistre girano    │    │
│      │  5. SPIN SINISTRA              │  Ruote opposte (gira sul posto)│    │
│      │  6. SPIN DESTRA                │  Ruote opposte (gira sul posto)│    │
│      │  7. Solo sinistre avanti       │  M1 e M2 girano                │    │
│      │  8. Solo destre avanti         │  M3 e M4 girano                │    │
│      │  9. Test velocità              │  Accelerazione graduale        │    │
│      └─────────────────────────────────────────────────────────────────┘    │
│                                                                              │
│                                                                              │
│   SE UN MOTORE GIRA AL CONTRARIO:                                          │
│                                                                              │
│   Non è un problema! Basta invertire i 2 fili di quel motore:              │
│                                                                              │
│   1. Allenta le viti del morsetto                                          │
│   2. Scambia i 2 fili di posizione                                         │
│   3. Ristringi le viti                                                      │
│   4. Rifai il test                                                          │
│                                                                              │
│                                                                              │
│   SE I MOTORI NON GIRANO:                                                   │
│                                                                              │
│   • Batterie scariche? Prova con batterie nuove                            │
│   • Fili non fissati? Controlla che le viti siano strette                  │
│   • Jumper PWR? Assicurati di averlo RIMOSSO dallo shield                  │
│   • Polarità batterie? Controlla + e -                                      │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Passo 6.4: Disattiva la Modalità Test

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   Quando tutti i motori funzionano correttamente:                          │
│                                                                              │
│   1. In Arduino IDE, cambia di nuovo:                                       │
│                                                                              │
│      #define TEST_MODE true   ← CAMBIA QUESTO                              │
│                                                                              │
│      in:                                                                    │
│                                                                              │
│      #define TEST_MODE false  ← COSÌ                                       │
│                                                                              │
│   2. Ricarica il programma (freccia →)                                     │
│                                                                              │
│   3. Ora il robot creerà la rete WiFi!                                      │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

---

# 7. CONNETTERE LO SMARTPHONE

Ora colleghiamo il telefono al robot!

## Passo 7.1: Trova la Rete WiFi del Robot

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   1. Sul tuo smartphone Android, vai in IMPOSTAZIONI                        │
│                                                                              │
│      ┌─────────────────────────┐                                            │
│      │  ⚙️  Impostazioni       │  ← Tocca qui                              │
│      └─────────────────────────┘                                            │
│                                                                              │
│   2. Tocca "WiFi" o "Rete e Internet" → "WiFi"                             │
│                                                                              │
│      ┌─────────────────────────┐                                            │
│      │  📶  WiFi               │  ← Tocca qui                              │
│      └─────────────────────────┘                                            │
│                                                                              │
│   3. Assicurati che il WiFi sia ATTIVO (interruttore verde/blu)            │
│                                                                              │
│   4. Nella lista delle reti disponibili, cerca "RobotCar":                 │
│                                                                              │
│      ┌─────────────────────────────────────────────────────────────────┐    │
│      │                                                                 │    │
│      │  Reti WiFi disponibili                                         │    │
│      │                                                                 │    │
│      │  ┌─────────────────────────────────────────────────────────┐   │    │
│      │  │  📶  Casa-Mia                              🔒            │   │    │
│      │  └─────────────────────────────────────────────────────────┘   │    │
│      │                                                                 │    │
│      │  ┌─────────────────────────────────────────────────────────┐   │    │
│      │  │  📶  RobotCar                              🔒            │   │    │
│      │  │      ↑                                                   │   │    │
│      │  │      QUESTA! Tocca per connetterti.                     │   │    │
│      │  └─────────────────────────────────────────────────────────┘   │    │
│      │                                                                 │    │
│      │  ┌─────────────────────────────────────────────────────────┐   │    │
│      │  │  📶  Vicino-5G                             🔒            │   │    │
│      │  └─────────────────────────────────────────────────────────┘   │    │
│      │                                                                 │    │
│      └─────────────────────────────────────────────────────────────────┘    │
│                                                                              │
│   5. Tocca "RobotCar"                                                       │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Passo 7.2: Inserisci la Password

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   1. Apparirà una finestra che chiede la password:                          │
│                                                                              │
│      ┌─────────────────────────────────────────────────────────────────┐    │
│      │                                                                 │    │
│      │  Connetti a "RobotCar"                                         │    │
│      │                                                                 │    │
│      │  Password:                                                      │    │
│      │  ┌─────────────────────────────────────────────────────────┐   │    │
│      │  │  robot1234                                              │   │    │
│      │  └─────────────────────────────────────────────────────────┘   │    │
│      │       ↑                                                         │    │
│      │       Scrivi:  robot1234                                       │    │
│      │                                                                 │    │
│      │                               [ANNULLA]  [CONNETTI]            │    │
│      │                                                                 │    │
│      └─────────────────────────────────────────────────────────────────┘    │
│                                                                              │
│   2. Tocca "CONNETTI"                                                       │
│                                                                              │
│   3. Attendi qualche secondo...                                             │
│                                                                              │
│   4. Vedrai "Connesso" sotto "RobotCar"                                     │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Passo 7.3: IMPORTANTE - Mantieni la Connessione!

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   ⚠️  ATTENZIONE: Android potrebbe mostrare questo avviso:                  │
│                                                                              │
│      ┌─────────────────────────────────────────────────────────────────┐    │
│      │                                                                 │    │
│      │  ⚠️  "RobotCar" non ha accesso a Internet.                     │    │
│      │                                                                 │    │
│      │  Vuoi restare connesso a questa rete?                          │    │
│      │                                                                 │    │
│      │                                                                 │    │
│      │        [NO, DISCONNETTI]        [SÌ, RESTA CONNESSO]           │    │
│      │                                          ↑                      │    │
│      │                                  TOCCA QUESTO!                  │    │
│      │                                                                 │    │
│      └─────────────────────────────────────────────────────────────────┘    │
│                                                                              │
│   È NORMALE! Il robot non è connesso a Internet (è un Access Point locale).│
│   DEVI toccare "SÌ" / "Resta connesso" / "Mantieni connessione"!           │
│                                                                              │
│                                                                              │
│   SE IL TELEFONO SI DISCONNETTE CONTINUAMENTE:                              │
│                                                                              │
│   1. Vai in Impostazioni → WiFi → RobotCar → (menu ⋮)                      │
│   2. Cerca "Auto-riconnessione" o "Usa rete anche senza Internet"          │
│   3. Attiva questa opzione                                                  │
│                                                                              │
│   OPPURE:                                                                   │
│                                                                              │
│   1. Disattiva i "Dati mobili" (4G/5G) temporaneamente                     │
│      Così il telefono non cercherà Internet altrove                        │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

---

# 8. USARE IL ROBOT

Finalmente! Controlliamo il robot!

## Passo 8.1: Apri il Browser

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   1. Apri il browser sul telefono (Chrome, Firefox, Samsung Internet...)   │
│                                                                              │
│   2. Nella barra degli indirizzi, scrivi:                                  │
│                                                                              │
│      ┌─────────────────────────────────────────────────────────────────┐    │
│      │  🔒  192.168.4.1                                          [→]  │    │
│      └─────────────────────────────────────────────────────────────────┘    │
│            ↑                                                                 │
│            Scrivi ESATTAMENTE questo indirizzo                              │
│                                                                              │
│   3. Premi INVIO / VAI                                                      │
│                                                                              │
│   4. Si aprirà la pagina di controllo del robot!                           │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Passo 8.2: Pagina Controllo Pulsanti

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   Questa è la pagina principale (192.168.4.1):                              │
│                                                                              │
│   ┌─────────────────────────────────────────────────────────────────────┐   │
│   │                                                                     │   │
│   │                      Robot Car                                      │   │
│   │               Connesso | Velocità: 700                              │   │
│   │                                                                     │   │
│   │                                                                     │   │
│   │          [↺]         [▲]         [↻]                               │   │
│   │                                                                     │   │
│   │        Spin ←      AVANTI      Spin →                              │   │
│   │                                                                     │   │
│   │                                                                     │   │
│   │          [◀]         [■]         [▶]                               │   │
│   │                                                                     │   │
│   │       SINISTRA      STOP       DESTRA                              │   │
│   │                                                                     │   │
│   │                                                                     │   │
│   │                     [▼]                                             │   │
│   │                                                                     │   │
│   │                  INDIETRO                                           │   │
│   │                                                                     │   │
│   │                                                                     │   │
│   │         ══════════════════════════════════                          │   │
│   │                   Velocità: 700                                     │   │
│   │                                                                     │   │
│   │              [ Tank Mode 🎮 ]                                       │   │
│   │                                                                     │   │
│   └─────────────────────────────────────────────────────────────────────┘   │
│                                                                              │
│                                                                              │
│   COME USARE I PULSANTI:                                                    │
│                                                                              │
│   • TIENI PREMUTO un pulsante per far muovere il robot                     │
│   • RILASCIA per fermare                                                    │
│   • Lo slider in basso regola la velocità (trascinalo)                     │
│   • Il pulsante STOP ferma tutto immediatamente                            │
│                                                                              │
│                                                                              │
│   COSA FA OGNI PULSANTE:                                                    │
│                                                                              │
│   ┌────────────┬───────────────────────────────────────────────────────┐    │
│   │  Pulsante  │  Cosa fa                                              │    │
│   ├────────────┼───────────────────────────────────────────────────────┤    │
│   │     ▲      │  Avanti - tutte le ruote girano in avanti            │    │
│   │     ▼      │  Indietro - tutte le ruote girano indietro           │    │
│   │     ◀      │  Sinistra - solo le ruote destre girano (curva)      │    │
│   │     ▶      │  Destra - solo le ruote sinistre girano (curva)      │    │
│   │     ↺      │  Spin sinistra - gira sul posto in senso antiorario  │    │
│   │     ↻      │  Spin destra - gira sul posto in senso orario        │    │
│   │     ■      │  Stop - ferma tutto                                   │    │
│   └────────────┴───────────────────────────────────────────────────────┘    │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Passo 8.3: Pagina Tank Mode (CONSIGLIATA!)

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   Per un controllo più preciso, usa il TANK MODE!                          │
│                                                                              │
│   1. Tocca il pulsante "Tank Mode 🎮" in fondo alla pagina                 │
│                                                                              │
│      OPPURE                                                                 │
│                                                                              │
│   2. Vai direttamente a: 192.168.4.1/tank                                  │
│                                                                              │
│                                                                              │
│   Questa è la pagina Tank Mode:                                             │
│                                                                              │
│   ┌─────────────────────────────────────────────────────────────────────┐   │
│   │                                                                     │   │
│   │                 Robot Car - Tank Mode                               │   │
│   │                                                                     │   │
│   │              SX: 0              DX: 0                               │   │
│   │                                                                     │   │
│   │                                                                     │   │
│   │       SINISTRA               DESTRA                                 │   │
│   │                                                                     │   │
│   │       ┌───────┐             ┌───────┐                              │   │
│   │       │   ▲   │  Avanti     │   ▲   │  Avanti                      │   │
│   │       │   │   │  +100%      │   │   │  +100%                       │   │
│   │       │   │   │             │   │   │                              │   │
│   │       │   │   │             │   │   │                              │   │
│   │       │ ──●── │  Stop       │ ──●── │  Stop                        │   │
│   │       │   │   │  0%         │   │   │  0%                          │   │
│   │       │   │   │             │   │   │                              │   │
│   │       │   │   │             │   │   │                              │   │
│   │       │   ▼   │  Indietro   │   ▼   │  Indietro                    │   │
│   │       └───────┘  -100%      └───────┘  -100%                       │   │
│   │                                                                     │   │
│   │                                                                     │   │
│   │              [ Modalità pulsanti ]                                  │   │
│   │                                                                     │   │
│   └─────────────────────────────────────────────────────────────────────┘   │
│                                                                              │
│                                                                              │
│   COME USARE IL TANK MODE:                                                  │
│                                                                              │
│   • Lo slider SINISTRO controlla le ruote SINISTRE (M1 e M2)               │
│   • Lo slider DESTRO controlla le ruote DESTRE (M3 e M4)                   │
│                                                                              │
│   • Trascina verso l'ALTO = ruote vanno AVANTI                             │
│   • Trascina verso il BASSO = ruote vanno INDIETRO                         │
│   • Al CENTRO = ruote FERME                                                 │
│                                                                              │
│   • Più muovi lo slider, più veloce vanno le ruote!                        │
│                                                                              │
│   • Quando RILASCI il dito, lo slider torna al centro (stop)               │
│                                                                              │
│                                                                              │
│   ESEMPI DI MOVIMENTI:                                                      │
│                                                                              │
│   ┌──────────────────────┬──────────────────────────────────────────────┐   │
│   │  Slider SX │ Slider DX │  Movimento del robot                       │   │
│   ├───────────┼───────────┼──────────────────────────────────────────────┤   │
│   │     ▲     │     ▲     │  Avanti dritto                              │   │
│   │     ▼     │     ▼     │  Indietro dritto                            │   │
│   │     ▲     │   centro  │  Curva a destra (ruote SX girano)           │   │
│   │   centro  │     ▲     │  Curva a sinistra (ruote DX girano)         │   │
│   │     ▲     │     ▼     │  Spin a destra (gira sul posto!)            │   │
│   │     ▼     │     ▲     │  Spin a sinistra (gira sul posto!)          │   │
│   │  poco ▲   │  molto ▲  │  Curva dolce a sinistra                     │   │
│   └───────────┴───────────┴──────────────────────────────────────────────┘   │
│                                                                              │
│                                                                              │
│   SUGGERIMENTO: Il Tank Mode è come guidare un carro armato.               │
│   Con un po' di pratica diventa molto intuitivo!                           │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Passo 8.4: Crea una Scorciatoia sulla Home

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   Per non dover scrivere l'indirizzo ogni volta, crea una scorciatoia!     │
│                                                                              │
│   SU CHROME:                                                                │
│                                                                              │
│   1. Apri 192.168.4.1 (o 192.168.4.1/tank)                                 │
│                                                                              │
│   2. Tocca i TRE PUNTINI (⋮) in alto a destra                              │
│                                                                              │
│      ┌─────────────────────────────────────────────────────────────────┐    │
│      │  ←  🔒 192.168.4.1                                        [ ⋮ ]│    │
│      └─────────────────────────────────────────────────────────────────┘    │
│                                                                        ↑    │
│                                                              Tocca qui      │
│                                                                              │
│   3. Seleziona "Aggiungi a schermata Home"                                 │
│                                                                              │
│      ┌─────────────────────────────────────────────────────────────────┐    │
│      │                                                                 │    │
│      │  Nuova scheda                                                   │    │
│      │  Nuova scheda in incognito                                      │    │
│      │  Preferiti                                                      │    │
│      │  ...                                                            │    │
│      │  Aggiungi a schermata Home  ← TOCCA QUI                        │    │
│      │  ...                                                            │    │
│      │                                                                 │    │
│      └─────────────────────────────────────────────────────────────────┘    │
│                                                                              │
│   4. Dai un nome: "Robot Car" o "Tank Mode"                                │
│                                                                              │
│   5. Tocca "Aggiungi"                                                       │
│                                                                              │
│   6. Ora hai un'ICONA sulla home del telefono!                             │
│                                                                              │
│      ┌─────────────────────────────────────────────────────────────────┐    │
│      │                                                                 │    │
│      │   📱  📷  📞  💬                                              │    │
│      │                                                                 │    │
│      │   🎮                                                           │    │
│      │  Robot                                                          │    │
│      │   Car   ← La tua nuova icona!                                  │    │
│      │                                                                 │    │
│      └─────────────────────────────────────────────────────────────────┘    │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

---

# 9. CREARE L'APP ANDROID

Se vuoi un'app "vera" invece del browser, puoi crearla con MIT App Inventor!

## Passo 9.1: Accedi a MIT App Inventor

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   MIT App Inventor è un sito web GRATUITO dove puoi creare app Android     │
│   senza scrivere codice tradizionale.                                       │
│                                                                              │
│   1. Sul COMPUTER (non sul telefono!), apri il browser                     │
│                                                                              │
│   2. Vai su: https://ai2.appinventor.mit.edu                               │
│                                                                              │
│   3. Clicca "Create Apps!"                                                  │
│                                                                              │
│      ┌─────────────────────────────────────────────────────────────────┐    │
│      │                                                                 │    │
│      │        MIT App Inventor                                         │    │
│      │                                                                 │    │
│      │   Crea app per Android senza programmare!                      │    │
│      │                                                                 │    │
│      │              [ Create Apps! ]  ← CLICCA                        │    │
│      │                                                                 │    │
│      └─────────────────────────────────────────────────────────────────┘    │
│                                                                              │
│   4. Accedi con il tuo account GOOGLE (Gmail)                              │
│                                                                              │
│   5. Accetta i termini di servizio                                          │
│                                                                              │
│   6. Sei dentro!                                                            │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Passo 9.2: Crea un Nuovo Progetto

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   1. Clicca "Start new project"                                            │
│                                                                              │
│   2. Come nome scrivi: RobotCarTank                                        │
│                                                                              │
│   3. Clicca "OK"                                                            │
│                                                                              │
│   4. Si apre l'editor con due modalità:                                    │
│                                                                              │
│      • DESIGNER - dove disegni l'interfaccia (pulsanti, slider, ecc.)     │
│      • BLOCKS - dove definisci cosa fanno i componenti                     │
│                                                                              │
│      Passa da una all'altra con i pulsanti in alto a destra:               │
│                                                                              │
│      ┌─────────────────────────────────────────────────────────────────┐    │
│      │                                      [Designer] [Blocks]        │    │
│      └─────────────────────────────────────────────────────────────────┘    │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Passo 9.3: Crea l'Interfaccia (Designer)

La guida completa è nel file `docs/APP_ANDROID_GUIDA.md`, ma ecco un riassunto:

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   STRUTTURA DELL'APP:                                                       │
│                                                                              │
│   Screen1                                                                   │
│   ├── Label: "Robot Car - Tank Mode"        (titolo)                       │
│   ├── HorizontalArrangement                                                 │
│   │   ├── Label: "SX: 0"                    (valore sinistro)              │
│   │   └── Label: "DX: 0"                    (valore destro)                │
│   ├── HorizontalArrangement                                                 │
│   │   ├── VerticalArrangement                                               │
│   │   │   ├── Label: "SINISTRA"                                            │
│   │   │   └── Slider (sliderLeft)           ← Controlla ruote sinistre    │
│   │   └── VerticalArrangement                                               │
│   │       ├── Label: "DESTRA"                                              │
│   │       └── Slider (sliderRight)          ← Controlla ruote destre      │
│   ├── Button: "STOP"                        (pulsante emergenza)           │
│   ├── Label: "Connetti a WiFi RobotCar"    (stato)                         │
│   └── Web1                                  (componente invisibile)         │
│                                                                              │
│                                                                              │
│   COMPONENTI DALLA PALETTE:                                                 │
│                                                                              │
│   Dalla colonna sinistra "Palette", trascina:                              │
│                                                                              │
│   • User Interface → Label (x5)                                            │
│   • User Interface → Button (x1)                                           │
│   • User Interface → Slider (x2)                                           │
│   • Layout → HorizontalArrangement (x2)                                    │
│   • Layout → VerticalArrangement (x2)                                      │
│   • Connectivity → Web (x1)                                                │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Passo 9.4: Programma l'App (Blocks)

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   1. Clicca "Blocks" in alto a destra                                      │
│                                                                              │
│   2. Crea questi blocchi (trascinando dalla colonna sinistra):             │
│                                                                              │
│                                                                              │
│   VARIABILE GLOBALE:                                                        │
│                                                                              │
│   ┌─────────────────────────────────────────────────────────────────────┐   │
│   │  initialize global  robotIP  to  "http://192.168.4.1"              │   │
│   └─────────────────────────────────────────────────────────────────────┘   │
│                                                                              │
│                                                                              │
│   QUANDO SLIDER SINISTRO CAMBIA:                                           │
│                                                                              │
│   ┌─────────────────────────────────────────────────────────────────────┐   │
│   │  when  sliderLeft.PositionChanged                                   │   │
│   │  do    set Web1.Url to                                              │   │
│   │            join ( get global robotIP )                              │   │
│   │                 ( "/drive?l=" )                                     │   │
│   │                 ( round sliderLeft.ThumbPosition × 10.23 )          │   │
│   │                 ( "&r=" )                                           │   │
│   │                 ( round sliderRight.ThumbPosition × 10.23 )         │   │
│   │        call Web1.Get                                                │   │
│   └─────────────────────────────────────────────────────────────────────┘   │
│                                                                              │
│                                                                              │
│   (Stessa cosa per sliderRight)                                             │
│                                                                              │
│                                                                              │
│   QUANDO RILASCI LO SLIDER (torna a zero):                                 │
│                                                                              │
│   ┌─────────────────────────────────────────────────────────────────────┐   │
│   │  when  sliderLeft.TouchUp                                           │   │
│   │  do    set sliderLeft.ThumbPosition to 0                           │   │
│   │        ... (invia comando stop)                                     │   │
│   └─────────────────────────────────────────────────────────────────────┘   │
│                                                                              │
│                                                                              │
│   Per la guida COMPLETA con tutti i blocchi, vedi:                         │
│   docs/APP_ANDROID_GUIDA.md                                                 │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Passo 9.5: Testa l'App sul Telefono

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   METODO FACILE: MIT AI2 Companion                                         │
│                                                                              │
│   1. Sul telefono, vai nel Play Store                                      │
│                                                                              │
│   2. Cerca "MIT AI2 Companion"                                             │
│                                                                              │
│   3. Installa l'app                                                         │
│                                                                              │
│   4. Sul COMPUTER, in MIT App Inventor:                                    │
│      - Clicca "Connect" → "AI Companion"                                   │
│                                                                              │
│   5. Apparirà un QR code:                                                   │
│                                                                              │
│      ┌─────────────────────────────────────────────────────────────────┐    │
│      │                                                                 │    │
│      │         ▄▄▄▄▄▄▄ ▄ ▄ ▄▄▄▄▄▄▄                                   │    │
│      │         █ ▄▄▄ █ ▀█▀ █ ▄▄▄ █                                   │    │
│      │         █ ███ █ ▀▄▀ █ ███ █                                   │    │
│      │         ▀▀▀▀▀▀▀ ▀ ▀ ▀▀▀▀▀▀▀                                   │    │
│      │                                                                 │    │
│      │         Scansiona con MIT AI2 Companion                        │    │
│      │                                                                 │    │
│      └─────────────────────────────────────────────────────────────────┘    │
│                                                                              │
│   6. Sul telefono, apri MIT AI2 Companion                                  │
│                                                                              │
│   7. Tocca "scan QR code"                                                   │
│                                                                              │
│   8. Inquadra il QR code sul monitor                                       │
│                                                                              │
│   9. L'app apparirà sul telefono IN TEMPO REALE!                           │
│      Ogni modifica che fai sul computer si vede subito sul telefono.       │
│                                                                              │
│                                                                              │
│   NOTA: Per questo test, il telefono deve essere connesso alla stessa      │
│   rete WiFi del computer (non alla rete RobotCar!)                         │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Passo 9.6: Genera l'APK (File Installabile)

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   Quando l'app funziona, crea il file APK da installare:                   │
│                                                                              │
│   1. In MIT App Inventor, clicca:                                          │
│                                                                              │
│      Build  →  Android App (.apk)                                          │
│                                                                              │
│   2. Attendi 1-2 minuti (il sito compila l'app)                            │
│                                                                              │
│      ┌─────────────────────────────────────────────────────────────────┐    │
│      │                                                                 │    │
│      │   Building app...                                               │    │
│      │                                                                 │    │
│      │   ████████████████████░░░░░░░░░░  65%                          │    │
│      │                                                                 │    │
│      └─────────────────────────────────────────────────────────────────┘    │
│                                                                              │
│   3. Quando finisce, appare un QR code:                                    │
│                                                                              │
│      ┌─────────────────────────────────────────────────────────────────┐    │
│      │                                                                 │    │
│      │   Your app is ready!                                            │    │
│      │                                                                 │    │
│      │         ▄▄▄▄▄▄▄ ▄ ▄ ▄▄▄▄▄▄▄                                   │    │
│      │         █ ▄▄▄ █ ▀█▀ █ ▄▄▄ █                                   │    │
│      │         █ ███ █ ▀▄▀ █ ███ █                                   │    │
│      │         ▀▀▀▀▀▀▀ ▀ ▀ ▀▀▀▀▀▀▀                                   │    │
│      │                                                                 │    │
│      │   Scan to download APK                                          │    │
│      │   (or click link below)                                         │    │
│      │                                                                 │    │
│      └─────────────────────────────────────────────────────────────────┘    │
│                                                                              │
│   4. Scansiona il QR code con la fotocamera del telefono                   │
│      (o con un'app QR scanner)                                              │
│                                                                              │
│   5. Si aprirà un link - tocca per scaricare l'APK                         │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Passo 9.7: Installa l'APK sul Telefono

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   Android blocca l'installazione di app da "fonti sconosciute" per         │
│   sicurezza. Devi dare il permesso una volta.                              │
│                                                                              │
│   1. Quando tocchi il file APK scaricato, apparirà:                        │
│                                                                              │
│      ┌─────────────────────────────────────────────────────────────────┐    │
│      │                                                                 │    │
│      │   ⚠️  Per la tua sicurezza, il telefono non può               │    │
│      │      installare app sconosciute da questa fonte.               │    │
│      │                                                                 │    │
│      │                           [IMPOSTAZIONI]                        │    │
│      │                                 ↑                               │    │
│      │                          Tocca qui                              │    │
│      │                                                                 │    │
│      └─────────────────────────────────────────────────────────────────┘    │
│                                                                              │
│   2. Tocca "IMPOSTAZIONI"                                                   │
│                                                                              │
│   3. Attiva "Consenti da questa fonte":                                    │
│                                                                              │
│      ┌─────────────────────────────────────────────────────────────────┐    │
│      │                                                                 │    │
│      │   Consenti da questa fonte                                      │    │
│      │                                                                 │    │
│      │   Chrome (o il tuo browser)                                     │    │
│      │                                                                 │    │
│      │         ○ OFF    ────────────────  ● ON                        │    │
│      │                                      ↑                          │    │
│      │                                Attiva questo                    │    │
│      │                                                                 │    │
│      └─────────────────────────────────────────────────────────────────┘    │
│                                                                              │
│   4. Torna indietro e tocca di nuovo il file APK                           │
│                                                                              │
│   5. Tocca "INSTALLA"                                                       │
│                                                                              │
│      ┌─────────────────────────────────────────────────────────────────┐    │
│      │                                                                 │    │
│      │   Vuoi installare questa app?                                   │    │
│      │                                                                 │    │
│      │   RobotCarTank                                                  │    │
│      │                                                                 │    │
│      │        [ANNULLA]            [INSTALLA]                         │    │
│      │                                  ↑                              │    │
│      │                            Tocca qui                            │    │
│      │                                                                 │    │
│      └─────────────────────────────────────────────────────────────────┘    │
│                                                                              │
│   6. Attendi l'installazione (pochi secondi)                               │
│                                                                              │
│   7. Tocca "APRI" per avviare l'app!                                       │
│                                                                              │
│   8. L'app è ora nel cassetto delle app del telefono!                      │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

---

# 10. RISOLUZIONE PROBLEMI

Ecco i problemi più comuni e come risolverli.

## Problema: La Wemos non viene riconosciuta dal computer

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   SINTOMI:                                                                  │
│   • In Tools → Port non appare nessuna porta nuova                         │
│   • Windows non fa il "ding" quando colleghi la USB                        │
│                                                                              │
│   SOLUZIONI:                                                                │
│                                                                              │
│   1. Prova un altro cavo USB                                               │
│      (alcuni cavi sono solo per ricarica, non per dati!)                   │
│                                                                              │
│   2. Prova un'altra porta USB del computer                                 │
│                                                                              │
│   3. Installa il driver CH340 (vedi Passo 3.4)                             │
│                                                                              │
│   4. Su Linux, potresti dover aggiungere il tuo utente al gruppo dialout: │
│      sudo usermod -a -G dialout $USER                                      │
│      (poi riavvia)                                                          │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Problema: Upload fallisce

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   SINTOMI:                                                                  │
│   • Errore "espcomm_upload_mem failed"                                     │
│   • Errore "Failed to connect to ESP8266"                                  │
│   • Barra di progresso si blocca                                           │
│                                                                              │
│   SOLUZIONI:                                                                │
│                                                                              │
│   1. Prova a premere il pulsante RESET sulla Wemos subito dopo            │
│      aver cliccato Upload                                                   │
│                                                                              │
│   2. Riduci la velocità di upload:                                         │
│      Tools → Upload Speed → 115200 (invece di 921600)                      │
│                                                                              │
│   3. Scollega lo shield dalla Wemos durante l'upload                       │
│      (a volte interferisce)                                                 │
│                                                                              │
│   4. Chiudi il Serial Monitor se è aperto                                  │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Problema: Non trovo la rete "RobotCar"

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   SINTOMI:                                                                  │
│   • Il telefono non vede la rete "RobotCar"                                │
│                                                                              │
│   SOLUZIONI:                                                                │
│                                                                              │
│   1. Assicurati che TEST_MODE sia "false" nel codice                       │
│                                                                              │
│   2. Verifica che la Wemos sia alimentata (LED acceso)                     │
│                                                                              │
│   3. Avvicinati al robot (il WiFi ha portata limitata)                     │
│                                                                              │
│   4. Riavvia la Wemos (premi RESET o togli/rimetti alimentazione)          │
│                                                                              │
│   5. Apri il Serial Monitor in Arduino IDE (Tools → Serial Monitor)        │
│      e verifica che ci sia scritto "Access Point attivo"                   │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Problema: La pagina web non si carica

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   SINTOMI:                                                                  │
│   • Il browser dice "Impossibile raggiungere il sito"                      │
│   • La pagina resta bianca                                                  │
│                                                                              │
│   SOLUZIONI:                                                                │
│                                                                              │
│   1. Verifica di essere connesso alla rete "RobotCar" (non alla tua casa!) │
│                                                                              │
│   2. Verifica l'indirizzo: deve essere 192.168.4.1 (non .1.1 o altro)      │
│                                                                              │
│   3. Disattiva i dati mobili sul telefono                                  │
│                                                                              │
│   4. Prova a digitare http://192.168.4.1 (con http://)                     │
│                                                                              │
│   5. Chiudi e riapri il browser                                            │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Problema: I motori non girano

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   SINTOMI:                                                                  │
│   • Premi i pulsanti ma le ruote non si muovono                            │
│   • Alcuni motori funzionano, altri no                                     │
│                                                                              │
│   SOLUZIONI:                                                                │
│                                                                              │
│   1. BATTERIE:                                                              │
│      • Sono inserite?                                                       │
│      • Sono cariche? (prova con batterie nuove)                            │
│      • La polarità è corretta? (+ e -)                                     │
│                                                                              │
│   2. JUMPER PWR:                                                            │
│      • Hai rimosso il jumper dallo shield?                                 │
│      • Deve essere RIMOSSO quando usi batterie esterne!                    │
│                                                                              │
│   3. COLLEGAMENTI:                                                          │
│      • I fili dei motori sono ben fissati nei morsetti?                    │
│      • Prova a stringere di più le viti                                    │
│                                                                              │
│   4. SHIELD:                                                                │
│      • Lo shield è ben inserito sulla Wemos?                               │
│      • Nessun pin è piegato o fuori posto?                                 │
│                                                                              │
│   5. TEST MODE:                                                             │
│      • Prova con TEST_MODE = true per testare i motori senza WiFi         │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Problema: Un motore gira al contrario

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   SINTOMI:                                                                  │
│   • Quando vai avanti, una ruota va indietro                               │
│                                                                              │
│   SOLUZIONE (facilissima!):                                                 │
│                                                                              │
│   1. Identifica quale motore gira al contrario                             │
│                                                                              │
│   2. Allenta le 2 viti del suo morsetto                                    │
│                                                                              │
│   3. Scambia i 2 fili di posizione:                                        │
│                                                                              │
│      PRIMA:           DOPO:                                                 │
│      [A] [B]    →     [B] [A]                                              │
│                                                                              │
│   4. Ristringi le viti                                                      │
│                                                                              │
│   5. Testa di nuovo - ora dovrebbe girare nel verso giusto!                │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Problema: Il telefono si disconnette dalla rete RobotCar

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│   SINTOMI:                                                                  │
│   • Il telefono torna alla rete di casa da solo                            │
│   • Si disconnette dopo pochi secondi                                       │
│                                                                              │
│   CAUSA:                                                                    │
│   Android preferisce reti con Internet. "RobotCar" non ha Internet,        │
│   quindi Android cerca di "aiutarti" riconnettendoti altrove.              │
│                                                                              │
│   SOLUZIONI:                                                                │
│                                                                              │
│   1. Disattiva i "Dati mobili" (4G/5G) mentre usi il robot                 │
│                                                                              │
│   2. Quando appare l'avviso "Rete senza Internet", tocca sempre            │
│      "Sì, resta connesso"                                                   │
│                                                                              │
│   3. In Impostazioni WiFi, cerca opzioni come:                             │
│      • "Passa automaticamente ai dati mobili" → Disattiva                  │
│      • "WiFi intelligente" → Disattiva                                     │
│      • "Connessione automatica" → Attiva solo per RobotCar                 │
│                                                                              │
│   4. "Dimentica" temporaneamente le altre reti WiFi:                       │
│      Impostazioni → WiFi → (rete) → Dimentica                              │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

---

# SCHEMA RIASSUNTIVO

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                                                                              │
│                        MAPPA DEL TUO PERCORSO                               │
│                                                                              │
│   ┌───────────────┐                                                         │
│   │ 1. COMPONENTI │  Compra: Wemos D1, Shield L293D, 4 motori, batterie    │
│   └───────┬───────┘                                                         │
│           │                                                                  │
│           ▼                                                                  │
│   ┌───────────────┐                                                         │
│   │ 2. ARDUINO IDE│  Scarica e installa da arduino.cc                      │
│   └───────┬───────┘                                                         │
│           │                                                                  │
│           ▼                                                                  │
│   ┌───────────────┐                                                         │
│   │ 3. ESP8266    │  Aggiungi URL → Installa board → Seleziona Wemos D1    │
│   └───────┬───────┘                                                         │
│           │                                                                  │
│           ▼                                                                  │
│   ┌───────────────┐                                                         │
│   │ 4. MONTAGGIO  │  Shield su Wemos → Motori → Batterie                   │
│   └───────┬───────┘                                                         │
│           │                                                                  │
│           ▼                                                                  │
│   ┌───────────────┐                                                         │
│   │ 5. UPLOAD     │  Apri robot_car.ino → Seleziona porta → Carica         │
│   └───────┬───────┘                                                         │
│           │                                                                  │
│           ▼                                                                  │
│   ┌───────────────┐                                                         │
│   │ 6. TEST       │  TEST_MODE=true → Verifica motori → TEST_MODE=false    │
│   └───────┬───────┘                                                         │
│           │                                                                  │
│           ▼                                                                  │
│   ┌───────────────┐                                                         │
│   │ 7. CONNETTI   │  WiFi "RobotCar" → Password: robot1234                 │
│   └───────┬───────┘                                                         │
│           │                                                                  │
│           ▼                                                                  │
│   ┌───────────────┐                                                         │
│   │ 8. CONTROLLA  │  Browser → 192.168.4.1 → Gioca!                        │
│   └───────┬───────┘                                                         │
│           │                                                                  │
│           ▼                                                                  │
│   ┌───────────────┐                                                         │
│   │ 9. APP (opt)  │  MIT App Inventor → Crea app → Genera APK              │
│   └───────────────┘                                                         │
│                                                                              │
│                                                                              │
│                        🎉  DIVERTITI!  🎉                                   │
│                                                                              │
└─────────────────────────────────────────────────────────────────────────────┘
```

---

# GLOSSARIO

Termini tecnici spiegati in modo semplice:

| Termine | Significato |
|---------|-------------|
| **Arduino IDE** | Il programma per scrivere e caricare codice sulla Wemos |
| **Upload** | Trasferire il programma dal computer alla Wemos |
| **Sketch** | Come Arduino chiama un programma |
| **Shield** | Una scheda che si incastra sopra un'altra per aggiungere funzioni |
| **Driver** | Un programmino che permette al computer di "parlare" con un dispositivo |
| **USB** | Il cavo che usi per collegare telefono/stampante al computer |
| **WiFi AP** | Access Point - il robot crea la sua rete WiFi personale |
| **IP** | L'indirizzo numerico di un dispositivo in rete (es. 192.168.4.1) |
| **Browser** | Chrome, Firefox, Safari - il programma per navigare su internet |
| **APK** | Il formato dei file di installazione su Android |
| **PWM** | Tecnica per controllare la velocità dei motori |
| **GPIO** | I "piedini" della scheda che puoi programmare |
| **Serial Monitor** | Una finestra che mostra i messaggi della Wemos |
| **Compilare** | Tradurre il codice in linguaggio comprensibile alla Wemos |

---

**Hai bisogno di aiuto?** Controlla la sezione [Risoluzione Problemi](#10-risoluzione-problemi) o rileggi il passo specifico che ti sta dando problemi.

**Buon divertimento con il tuo robot!** 🤖🚗
