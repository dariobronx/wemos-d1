# App Android per Robot Car

Questa guida descrive come controllare il robot car da Android.

## Opzioni Disponibili

### Opzione 1: Usa la Pagina Web (Consigliato per iniziare)
La pagina web integrata funziona perfettamente su smartphone Android.

### Opzione 2: Salva come App (PWA)
Puoi "installare" la pagina web come app sul telefono.

### Opzione 3: MIT App Inventor
Crea un'app nativa Android con interfaccia personalizzata.

### Opzione 4: App Flutter (Avanzato)
Per sviluppatori, incluso progetto Flutter base.

---

## Opzione 1: Pagina Web

La soluzione più semplice - già pronta!

**Come usarla:**
1. Connetti il telefono alla rete "RobotCar"
2. Apri Chrome/Firefox
3. Vai a `http://192.168.4.1`
4. Usa i controlli touch

**Vantaggi:**
- Nessuna installazione
- Funziona subito
- Interfaccia responsive

---

## Opzione 2: Salva come App (PWA)

Puoi aggiungere la pagina web alla schermata home come se fosse un'app.

### Su Chrome Android:

1. Apri `http://192.168.4.1` in Chrome
2. Tocca i **3 puntini** (menu) in alto a destra
3. Seleziona **"Aggiungi a schermata Home"**
4. Dai un nome (es. "Robot Car")
5. Tocca **"Aggiungi"**

Ora avrai un'icona sulla home che apre direttamente il controllo!

### Su Firefox Android:

1. Apri `http://192.168.4.1` in Firefox
2. Tocca i **3 puntini** (menu)
3. Seleziona **"Installa"** o **"Aggiungi a schermata Home"**

---

## Opzione 3: MIT App Inventor

MIT App Inventor è uno strumento gratuito per creare app Android senza programmare.

### Prerequisiti

- Account Google
- Browser web (Chrome consigliato)
- Telefono Android con app "MIT AI2 Companion"

### Passo 1: Accedi a MIT App Inventor

1. Vai a: https://appinventor.mit.edu/
2. Clicca "Create Apps!"
3. Accedi con Google

### Passo 2: Crea Nuovo Progetto

1. Clicca **"Start new project"**
2. Nome: `RobotCarController`

### Passo 3: Design dell'Interfaccia

Trascina questi componenti dalla Palette:

**Layout:**
```
Screen1
├── VerticalArrangement (AlignHorizontal: Center)
│   ├── Label ("Robot Car Control")
│   ├── Label (lblStatus: "Disconnesso")
│   ├── HorizontalArrangement
│   │   ├── Button (btnSpinLeft: "↺")
│   │   ├── Button (btnForward: "▲")
│   │   └── Button (btnSpinRight: "↻")
│   ├── HorizontalArrangement
│   │   ├── Button (btnLeft: "◀")
│   │   ├── Button (btnStop: "■")
│   │   └── Button (btnRight: "▶")
│   ├── HorizontalArrangement
│   │   ├── Spacer
│   │   ├── Button (btnBackward: "▼")
│   │   └── Spacer
│   ├── Slider (sldSpeed: Min=0, Max=1023, Value=700)
│   └── Label (lblSpeed: "Velocità: 700")
└── Web1 (componente non visibile)
```

**Proprietà componenti:**

| Componente | Proprietà | Valore |
|------------|-----------|--------|
| Tutti i Button | Width | 80 pixels |
| Tutti i Button | Height | 80 pixels |
| Tutti i Button | FontSize | 24 |
| btnStop | BackgroundColor | Red |
| btnSpinLeft/Right | BackgroundColor | Purple |
| Slider | Width | Fill parent |
| Web1 | (nessuna modifica) | |

### Passo 4: Programmazione (Blocks)

Passa alla vista **Blocks** e crea questi blocchi:

**Variabile globale:**
```
initialize global robotIP to "http://192.168.4.1"
```

**Funzione per inviare comandi:**
```
to sendCommand (command)
  set Web1.Url to join(get global robotIP, "/", command)
  call Web1.Get
```

**Eventi pulsanti (TouchDown = premi, TouchUp = rilascia):**

```
when btnForward.TouchDown
  call sendCommand("forward")

when btnForward.TouchUp
  call sendCommand("stop")

when btnBackward.TouchDown
  call sendCommand("backward")

when btnBackward.TouchUp
  call sendCommand("stop")

when btnLeft.TouchDown
  call sendCommand("left")

when btnLeft.TouchUp
  call sendCommand("stop")

when btnRight.TouchDown
  call sendCommand("right")

when btnRight.TouchUp
  call sendCommand("stop")

when btnSpinLeft.TouchDown
  call sendCommand("spinleft")

when btnSpinLeft.TouchUp
  call sendCommand("stop")

when btnSpinRight.TouchDown
  call sendCommand("spinright")

when btnSpinRight.TouchUp
  call sendCommand("stop")

when btnStop.Click
  call sendCommand("stop")
```

**Slider velocità:**
```
when sldSpeed.PositionChanged
  set lblSpeed.Text to join("Velocità: ", sldSpeed.ThumbPosition)
  set Web1.Url to join(get global robotIP, "/speed?v=", sldSpeed.ThumbPosition)
  call Web1.Get
```

**Risposta Web:**
```
when Web1.GotText
  set lblStatus.Text to "Connesso"
```

### Passo 5: Test su Telefono

1. Installa "MIT AI2 Companion" dal Play Store
2. In App Inventor, clicca **Connect → AI Companion**
3. Scansiona il QR code con l'app
4. L'app apparirà sul telefono per il test

### Passo 6: Esporta APK

1. Clicca **Build → Android App (.apk)**
2. Attendi la compilazione
3. Scarica l'APK o scansiona il QR
4. Installa sul telefono (abilita "Origini sconosciute")

---

## Opzione 4: App Flutter (Avanzato)

Per sviluppatori che vogliono un'app più professionale.

### Struttura Progetto

```
android/
└── robot_car_app/
    ├── lib/
    │   └── main.dart
    ├── pubspec.yaml
    └── ...
```

### Codice Flutter Base

Crea un nuovo progetto Flutter e usa questo codice:

```dart
// lib/main.dart
import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;

void main() => runApp(RobotCarApp());

class RobotCarApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Robot Car',
      theme: ThemeData.dark(),
      home: ControlPage(),
    );
  }
}

class ControlPage extends StatefulWidget {
  @override
  _ControlPageState createState() => _ControlPageState();
}

class _ControlPageState extends State<ControlPage> {
  final String robotIP = 'http://192.168.4.1';
  double speed = 700;

  Future<void> sendCommand(String cmd) async {
    try {
      await http.get(Uri.parse('$robotIP/$cmd'));
    } catch (e) {
      print('Errore: $e');
    }
  }

  Widget buildButton(String label, String command, {Color? color}) {
    return GestureDetector(
      onTapDown: (_) => sendCommand(command),
      onTapUp: (_) => sendCommand('stop'),
      onTapCancel: () => sendCommand('stop'),
      child: Container(
        width: 80,
        height: 80,
        decoration: BoxDecoration(
          color: color ?? Colors.blue,
          borderRadius: BorderRadius.circular(15),
        ),
        child: Center(
          child: Text(label, style: TextStyle(fontSize: 28)),
        ),
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: Text('Robot Car Control')),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                buildButton('↺', 'spinleft', color: Colors.purple),
                SizedBox(width: 10),
                buildButton('▲', 'forward'),
                SizedBox(width: 10),
                buildButton('↻', 'spinright', color: Colors.purple),
              ],
            ),
            SizedBox(height: 10),
            Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                buildButton('◀', 'left'),
                SizedBox(width: 10),
                buildButton('■', 'stop', color: Colors.red),
                SizedBox(width: 10),
                buildButton('▶', 'right'),
              ],
            ),
            SizedBox(height: 10),
            buildButton('▼', 'backward'),
            SizedBox(height: 40),
            Text('Velocità: ${speed.toInt()}'),
            Slider(
              value: speed,
              min: 0,
              max: 1023,
              onChanged: (v) {
                setState(() => speed = v);
                sendCommand('speed?v=${v.toInt()}');
              },
            ),
          ],
        ),
      ),
    );
  }
}
```

### pubspec.yaml

```yaml
dependencies:
  flutter:
    sdk: flutter
  http: ^1.1.0
```

### Build APK

```bash
flutter build apk --release
```

L'APK sarà in `build/app/outputs/flutter-apk/app-release.apk`

---

## Confronto Opzioni

| Caratteristica | Web | PWA | MIT App Inventor | Flutter |
|----------------|-----|-----|------------------|---------|
| Difficoltà | Nessuna | Facile | Media | Alta |
| Installazione | No | Sì | Sì | Sì |
| Offline | No | No | Sì | Sì |
| Personalizzazione | Bassa | Bassa | Media | Alta |
| Performance | Buona | Buona | Media | Ottima |

---

## Risoluzione Problemi

### L'app non si connette

1. Verifica di essere connesso alla rete "RobotCar"
2. Verifica che l'IP sia `192.168.4.1`
3. Prova a pingare il robot (se hai terminale):
   ```
   ping 192.168.4.1
   ```

### I comandi sono lenti

- La latenza WiFi è normale (~50-200ms)
- Assicurati di essere vicino al robot
- Evita interferenze da altri dispositivi WiFi

### L'app MIT non funziona

- Assicurati che il componente Web1 sia presente
- Verifica che gli URL siano corretti
- Controlla i blocchi nel debugger
