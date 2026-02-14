# Guida Creazione App Android - Tank Mode

Guida passo-passo per creare l'app Android con i due joystick verticali usando MIT App Inventor.

## Prerequisiti

- Account Google
- Browser web (Chrome consigliato)
- Smartphone Android per test/installazione

## Passo 1: Accedi a MIT App Inventor

1. Vai su **https://ai2.appinventor.mit.edu**
2. Clicca **"Create Apps!"**
3. Accedi con il tuo account Google
4. Clicca **"Start new project"**
5. Nome progetto: `RobotCarTank`

## Passo 2: Design dell'Interfaccia

### Impostazioni Screen

1. Seleziona **Screen1** nel pannello Components
2. Nel pannello Properties imposta:
   - **Title**: `Robot Car`
   - **ScreenOrientation**: `Portrait`
   - **BackgroundColor**: `Dark Gray`

### Aggiungi Componenti

Dalla **Palette** (sinistra), trascina questi componenti:

```
Screen1
├── Label (lblTitle)
├── HorizontalArrangement (haValues)
│   ├── Label (lblLeft)
│   └── Label (lblRight)
├── HorizontalArrangement (haSliders)
│   ├── VerticalArrangement (vaLeft)
│   │   ├── Label ("SINISTRA")
│   │   └── Slider (sliderLeft)
│   └── VerticalArrangement (vaRight)
│       ├── Label ("DESTRA")
│       └── Slider (sliderRight)
├── Button (btnStop)
├── Label (lblStatus)
└── Web1 (invisibile)
```

### Proprietà Componenti

**Label - lblTitle:**
- Text: `Robot Car - Tank Mode`
- FontSize: 22
- TextColor: White
- TextAlignment: center
- Width: Fill parent

**HorizontalArrangement - haValues:**
- Width: Fill parent
- AlignHorizontal: Center

**Label - lblLeft:**
- Text: `SX: 0`
- FontSize: 18
- TextColor: Light Blue
- Width: 40%

**Label - lblRight:**
- Text: `DX: 0`
- FontSize: 18
- TextColor: Light Blue
- Width: 40%

**HorizontalArrangement - haSliders:**
- Width: Fill parent
- Height: 70%
- AlignHorizontal: Center

**VerticalArrangement - vaLeft e vaRight:**
- Width: 40%
- Height: Fill parent
- AlignHorizontal: Center

**Label sopra slider:**
- Text: `SINISTRA` o `DESTRA`
- FontSize: 14
- TextColor: Gray

**Slider - sliderLeft e sliderRight:**
- MinValue: -100
- MaxValue: 100
- ThumbPosition: 0
- Width: Fill parent
- Height: Fill parent
- ColorLeft: Green
- ColorRight: Red

**Button - btnStop:**
- Text: `STOP`
- FontSize: 24
- Width: 50%
- Height: 60 pixels
- BackgroundColor: Red
- TextColor: White

**Label - lblStatus:**
- Text: `Connetti a WiFi "RobotCar"`
- FontSize: 12
- TextColor: Gray
- TextAlignment: center

**Web1:**
- (nessuna proprietà visibile, serve per le chiamate HTTP)

## Passo 3: Programmazione (Blocks)

Passa alla modalità **Blocks** (pulsante in alto a destra).

### Variabili Globali

```
initialize global robotIP to "http://192.168.4.1"
initialize global leftPower to 0
initialize global rightPower to 0
initialize global sendTimer to null
```

### Funzione Invio Comando

Crea una procedura `sendDrive`:

```
to sendDrive
  set Web1.Url to
    join (get global robotIP)
         "/drive?l="
         (get global leftPower)
         "&r="
         (get global rightPower)
  call Web1.Get
```

### Slider Sinistro

```
when sliderLeft.PositionChanged
  set global leftPower to round(sliderLeft.ThumbPosition * 10.23)
  set lblLeft.Text to join "SX: " (get global leftPower)
  call sendDrive
```

### Slider Destro

```
when sliderRight.PositionChanged
  set global rightPower to round(sliderRight.ThumbPosition * 10.23)
  set lblRight.Text to join "DX: " (get global rightPower)
  call sendDrive
```

### Rilascio Slider (TouchUp)

Per far tornare gli slider a zero quando rilasci il dito:

```
when sliderLeft.TouchUp
  set sliderLeft.ThumbPosition to 0
  set global leftPower to 0
  set lblLeft.Text to "SX: 0"
  call sendDrive

when sliderRight.TouchUp
  set sliderRight.ThumbPosition to 0
  set global rightPower to 0
  set lblRight.Text to "DX: 0"
  call sendDrive
```

### Pulsante STOP

```
when btnStop.Click
  set sliderLeft.ThumbPosition to 0
  set sliderRight.ThumbPosition to 0
  set global leftPower to 0
  set global rightPower to 0
  set lblLeft.Text to "SX: 0"
  set lblRight.Text to "DX: 0"
  call sendDrive
```

### Risposta Web

```
when Web1.GotText
  set lblStatus.Text to "Connesso"
```

## Passo 4: Test su Telefono

### Opzione A: MIT AI2 Companion (Consigliato)

1. Installa **"MIT AI2 Companion"** dal Play Store
2. In MIT App Inventor, clicca **Connect → AI Companion**
3. Scansiona il QR code con l'app Companion
4. L'app apparirà in tempo reale sul telefono

### Opzione B: USB

1. Abilita **Debug USB** sul telefono
2. Collega il telefono al PC via USB
3. Clicca **Connect → USB**

## Passo 5: Genera APK

Quando l'app funziona correttamente:

1. Clicca **Build → Android App (.apk)**
2. Attendi la compilazione (~1-2 minuti)
3. Apparirà un **QR code**
4. Scansiona con il telefono per scaricare l'APK
5. Oppure clicca il link per scaricare sul PC

### Installazione APK

1. Sul telefono, apri il file APK scaricato
2. Se necessario, abilita "Installa da fonti sconosciute":
   - Android 8+: Impostazioni → App → Menu → Accesso speciale → Installa app sconosciute → Chrome → Consenti
3. Tocca **Installa**

## Passo 6: Uso dell'App

1. **Accendi il robot**
2. **Connetti il telefono** alla rete WiFi "RobotCar" (password: robot1234)
3. **Apri l'app** Robot Car
4. **Usa gli slider**:
   - Trascina verso l'alto = avanti
   - Trascina verso il basso = indietro
   - Centro = fermo
5. **Rilascia** per fermare automaticamente

## Personalizzazioni

### Cambiare IP del robot

Modifica la variabile `robotIP` nei Blocks:
```
initialize global robotIP to "http://192.168.4.1"
```

### Cambiare colori

Nel Designer, seleziona ogni componente e modifica:
- BackgroundColor
- TextColor

### Aggiungere vibrazione

1. Aggiungi componente **Sound** dalla palette
2. Nel blocco PositionChanged:
   ```
   call Sound1.Vibrate millisecs 50
   ```

## Risoluzione Problemi

### "Unable to connect to companion"

- Assicurati che PC e telefono siano sulla stessa rete WiFi
- Disattiva firewall temporaneamente
- Prova la connessione USB invece

### L'app non si connette al robot

- Verifica di essere connesso alla rete "RobotCar"
- Controlla che l'IP sia corretto (192.168.4.1)
- Prova ad aprire http://192.168.4.1 nel browser prima

### Lo slider non torna a zero

- Verifica di aver aggiunto il blocco `TouchUp` per ogni slider
- Controlla che `set ThumbPosition to 0` sia presente

### APK non si installa

- Abilita "Fonti sconosciute" nelle impostazioni
- Verifica che lo spazio sul telefono sia sufficiente
- Prova a scaricare l'APK di nuovo

## Screenshot Reference

```
┌─────────────────────────────────┐
│      Robot Car - Tank Mode      │
│                                 │
│     SX: 0          DX: 0        │
│                                 │
│  SINISTRA        DESTRA         │
│  ┌───────┐      ┌───────┐       │
│  │       │      │       │       │
│  │   █   │      │   █   │       │
│  │   │   │      │   │   │       │
│  │   │   │      │   │   │       │
│  │   ●   │      │   ●   │       │
│  │   │   │      │   │   │       │
│  │   │   │      │   │   │       │
│  │   █   │      │   █   │       │
│  │       │      │       │       │
│  └───────┘      └───────┘       │
│                                 │
│          [ STOP ]               │
│                                 │
│    Connetti a WiFi "RobotCar"   │
└─────────────────────────────────┘
```
