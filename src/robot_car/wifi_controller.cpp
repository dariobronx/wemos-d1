/**
 * wifi_controller.cpp
 *
 * Implementazione controller WiFi AP mode per Wemos D1 R1/R2
 */

#include "wifi_controller.h"

WiFiController WifiCtrl;

WiFiController::WiFiController() : _server(WEB_PORT) {
    _currentSpeed = SPEED_DEFAULT;
}

void WiFiController::begin() {
    Serial.println(F("\n[WiFi] Avvio Access Point..."));

    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(AP_IP, AP_GATEWAY, AP_SUBNET);

    bool success = WiFi.softAP(AP_SSID, AP_PASSWORD, AP_CHANNEL);

    if (success) {
        Serial.println(F("[WiFi] Access Point ATTIVO!"));
        Serial.println(F(""));
        Serial.println(F("╔══════════════════════════════════════╗"));
        Serial.println(F("║         CONNESSIONE WiFi             ║"));
        Serial.println(F("╠══════════════════════════════════════╣"));
        Serial.print(F("║  Rete:     ")); Serial.print(AP_SSID);
        for(int i = strlen(AP_SSID); i < 24; i++) Serial.print(" ");
        Serial.println(F("║"));
        Serial.print(F("║  Password: ")); Serial.print(AP_PASSWORD);
        for(int i = strlen(AP_PASSWORD); i < 24; i++) Serial.print(" ");
        Serial.println(F("║"));
        Serial.print(F("║  IP:       ")); Serial.print(WiFi.softAPIP());
        Serial.println(F("            ║"));
        Serial.println(F("╚══════════════════════════════════════╝"));
    } else {
        Serial.println(F("[WiFi] ERRORE avvio AP!"));
        return;
    }

    // Route del web server
    _server.on("/", HTTP_GET, [this]() { handleRoot(); });
    _server.on("/tank", HTTP_GET, [this]() { handleTankPage(); });
    _server.on("/forward", HTTP_GET, [this]() { handleForward(); });
    _server.on("/backward", HTTP_GET, [this]() { handleBackward(); });
    _server.on("/left", HTTP_GET, [this]() { handleLeft(); });
    _server.on("/right", HTTP_GET, [this]() { handleRight(); });
    _server.on("/spinleft", HTTP_GET, [this]() { handleSpinLeft(); });
    _server.on("/spinright", HTTP_GET, [this]() { handleSpinRight(); });
    _server.on("/stop", HTTP_GET, [this]() { handleStop(); });
    _server.on("/speed", HTTP_GET, [this]() { handleSpeed(); });
    _server.on("/drive", HTTP_GET, [this]() { handleTank(); });
    _server.on("/status", HTTP_GET, [this]() { handleStatus(); });
    _server.onNotFound([this]() { handleNotFound(); });

    _server.begin();
    Serial.println(F("[WiFi] Web server pronto!"));
}

void WiFiController::handleClient() {
    _server.handleClient();
}

String WiFiController::getIP() {
    return WiFi.softAPIP().toString();
}

String WiFiController::getSSID() {
    return String(AP_SSID);
}

String WiFiController::getPassword() {
    return String(AP_PASSWORD);
}

uint8_t WiFiController::getConnectedClients() {
    return WiFi.softAPgetStationNum();
}

void WiFiController::sendJsonResponse(const String& status, const String& message) {
    String json = "{\"status\":\"" + status + "\",\"message\":\"" + message +
                  "\",\"speed\":" + String(_currentSpeed) + "}";
    _server.send(200, "application/json", json);
}

// Handler comandi
void WiFiController::handleForward() {
    Motors.forward(_currentSpeed);
    sendJsonResponse("ok", "forward");
}

void WiFiController::handleBackward() {
    Motors.backward(_currentSpeed);
    sendJsonResponse("ok", "backward");
}

void WiFiController::handleLeft() {
    Motors.turnLeft(_currentSpeed);
    sendJsonResponse("ok", "left");
}

void WiFiController::handleRight() {
    Motors.turnRight(_currentSpeed);
    sendJsonResponse("ok", "right");
}

void WiFiController::handleSpinLeft() {
    Motors.spinLeft(_currentSpeed);
    sendJsonResponse("ok", "spinleft");
}

void WiFiController::handleSpinRight() {
    Motors.spinRight(_currentSpeed);
    sendJsonResponse("ok", "spinright");
}

void WiFiController::handleStop() {
    Motors.stop();
    sendJsonResponse("ok", "stop");
}

void WiFiController::handleSpeed() {
    if (_server.hasArg("v")) {
        int speed = _server.arg("v").toInt();
        if (speed < 0) speed = 0;
        if (speed > SPEED_MAX) speed = SPEED_MAX;
        _currentSpeed = speed;
        Motors.setSpeed(_currentSpeed);
    }
    sendJsonResponse("ok", "speed");
}

void WiFiController::handleTank() {
    int16_t left = 0;
    int16_t right = 0;

    if (_server.hasArg("l")) {
        left = _server.arg("l").toInt();
    }
    if (_server.hasArg("r")) {
        right = _server.arg("r").toInt();
    }

    Motors.tankDrive(left, right);
    sendJsonResponse("ok", "tank");
}

void WiFiController::handleTankPage() {
    _server.send(200, "text/html", getTankControlPage());
}

void WiFiController::handleStatus() {
    String json = "{";
    json += "\"ssid\":\"" + getSSID() + "\",";
    json += "\"ip\":\"" + getIP() + "\",";
    json += "\"clients\":" + String(getConnectedClients()) + ",";
    json += "\"speed\":" + String(_currentSpeed) + ",";
    json += "\"speedMax\":" + String(SPEED_MAX) + ",";
    json += "\"latch\":" + String(Motors.getLatchState());
    json += "}";
    _server.send(200, "application/json", json);
}

void WiFiController::handleNotFound() {
    _server.send(404, "text/plain", "404 Not Found");
}

void WiFiController::handleRoot() {
    _server.send(200, "text/html", getControlPage());
}

String WiFiController::getControlPage() {
    String html = R"rawliteral(
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
    <title>Robot Car</title>
    <style>
        * { box-sizing: border-box; margin: 0; padding: 0; touch-action: manipulation; }
        body {
            font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
            background: linear-gradient(135deg, #0f0c29 0%, #302b63 50%, #24243e 100%);
            min-height: 100vh;
            color: #fff;
            padding: 15px;
            user-select: none;
            -webkit-user-select: none;
            -webkit-touch-callout: none;
        }
        h1 { text-align: center; margin-bottom: 15px; font-size: 22px; }
        .status {
            text-align: center;
            padding: 8px 15px;
            background: rgba(255,255,255,0.1);
            border-radius: 20px;
            margin-bottom: 20px;
            font-size: 14px;
        }
        .status .connected { color: #2ecc71; }
        .controls {
            display: grid;
            grid-template-columns: repeat(3, 1fr);
            gap: 10px;
            max-width: 300px;
            margin: 0 auto 25px;
        }
        .btn {
            background: linear-gradient(145deg, #667eea, #764ba2);
            border: none;
            border-radius: 18px;
            color: white;
            font-size: 32px;
            padding: 22px;
            cursor: pointer;
            box-shadow: 0 8px 25px rgba(102, 126, 234, 0.4);
            transition: transform 0.1s, box-shadow 0.1s;
            display: flex;
            align-items: center;
            justify-content: center;
        }
        .btn:active, .btn.pressed {
            transform: scale(0.92);
            box-shadow: 0 4px 15px rgba(102, 126, 234, 0.3);
        }
        .btn-stop {
            background: linear-gradient(145deg, #e74c3c, #c0392b);
            box-shadow: 0 8px 25px rgba(231, 76, 60, 0.4);
        }
        .btn-spin {
            background: linear-gradient(145deg, #9b59b6, #8e44ad);
            font-size: 18px;
            box-shadow: 0 8px 25px rgba(155, 89, 182, 0.4);
        }
        .spacer { visibility: hidden; }
        .speed-section {
            max-width: 300px;
            margin: 0 auto;
            padding: 20px;
            background: rgba(255,255,255,0.08);
            border-radius: 20px;
        }
        .speed-label {
            display: flex;
            justify-content: space-between;
            margin-bottom: 12px;
            font-size: 14px;
        }
        .speed-value {
            font-size: 24px;
            font-weight: bold;
            color: #667eea;
        }
        input[type="range"] {
            width: 100%;
            height: 35px;
            -webkit-appearance: none;
            background: rgba(255,255,255,0.15);
            border-radius: 18px;
            outline: none;
        }
        input[type="range"]::-webkit-slider-thumb {
            -webkit-appearance: none;
            width: 45px;
            height: 45px;
            background: linear-gradient(145deg, #667eea, #764ba2);
            border-radius: 50%;
            cursor: pointer;
            box-shadow: 0 4px 15px rgba(0,0,0,0.3);
        }
        .info {
            margin-top: 20px;
            text-align: center;
            font-size: 12px;
            color: rgba(255,255,255,0.5);
        }
    </style>
</head>
<body>
    <h1>Robot Car</h1>
    <div class="status">
        <span class="connected">Connesso</span> | Velocita: <span id="speedDisp">700</span>
    </div>
    <div class="controls">
        <button class="btn btn-spin" data-cmd="spinleft">&#8634;</button>
        <button class="btn" data-cmd="forward">&#9650;</button>
        <button class="btn btn-spin" data-cmd="spinright">&#8635;</button>
        <button class="btn" data-cmd="left">&#9664;</button>
        <button class="btn btn-stop" data-cmd="stop">&#9632;</button>
        <button class="btn" data-cmd="right">&#9654;</button>
        <div class="spacer"></div>
        <button class="btn" data-cmd="backward">&#9660;</button>
        <div class="spacer"></div>
    </div>
    <div class="speed-section">
        <div class="speed-label">
            <span>Velocita</span>
            <span class="speed-value" id="speedVal">700</span>
        </div>
        <input type="range" id="slider" min="0" max="1023" value="700">
    </div>
    <div class="info">
        WiFi: RobotCar | IP: 192.168.4.1
    </div>
    <script>
        const slider = document.getElementById('slider');
        const speedVal = document.getElementById('speedVal');
        const speedDisp = document.getElementById('speedDisp');
        let speed = 700;

        function send(cmd) {
            fetch('/' + cmd).catch(e => console.log(e));
        }

        slider.oninput = function() {
            speed = this.value;
            speedVal.textContent = speed;
            speedDisp.textContent = speed;
            send('speed?v=' + speed);
        };

        document.querySelectorAll('.btn').forEach(btn => {
            const cmd = btn.dataset.cmd;
            if (!cmd) return;

            const isStop = cmd === 'stop';

            // Touch events
            btn.addEventListener('touchstart', e => {
                e.preventDefault();
                btn.classList.add('pressed');
                send(cmd);
            }, {passive: false});

            btn.addEventListener('touchend', e => {
                e.preventDefault();
                btn.classList.remove('pressed');
                if (!isStop) send('stop');
            }, {passive: false});

            // Mouse events
            btn.addEventListener('mousedown', e => {
                btn.classList.add('pressed');
                send(cmd);
            });

            btn.addEventListener('mouseup', e => {
                btn.classList.remove('pressed');
                if (!isStop) send('stop');
            });

            btn.addEventListener('mouseleave', e => {
                if (btn.classList.contains('pressed')) {
                    btn.classList.remove('pressed');
                    if (!isStop) send('stop');
                }
            });
        });
    </script>
</body>
</html>
)rawliteral";
    return html;
}

String WiFiController::getTankControlPage() {
    String html = R"rawliteral(
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
    <title>Robot Car - Tank Mode</title>
    <style>
        * { box-sizing: border-box; margin: 0; padding: 0; }
        html, body {
            width: 100%; height: 100%;
            overflow: hidden;
            touch-action: none;
            user-select: none;
            -webkit-user-select: none;
        }
        body {
            font-family: -apple-system, BlinkMacSystemFont, sans-serif;
            background: linear-gradient(135deg, #1a1a2e 0%, #16213e 100%);
            color: #fff;
            display: flex;
            flex-direction: column;
        }
        .header {
            text-align: center;
            padding: 10px;
            font-size: 18px;
            background: rgba(0,0,0,0.3);
        }
        .values {
            display: flex;
            justify-content: space-around;
            padding: 8px;
            font-size: 14px;
            background: rgba(0,0,0,0.2);
        }
        .val { font-family: monospace; color: #667eea; }
        .container {
            flex: 1;
            display: flex;
            justify-content: space-around;
            align-items: stretch;
            padding: 20px;
            gap: 40px;
        }
        .slider-container {
            display: flex;
            flex-direction: column;
            align-items: center;
            flex: 1;
            max-width: 150px;
        }
        .label {
            font-size: 14px;
            margin-bottom: 10px;
            color: rgba(255,255,255,0.7);
        }
        .track {
            flex: 1;
            width: 80px;
            background: rgba(255,255,255,0.1);
            border-radius: 40px;
            position: relative;
            overflow: hidden;
        }
        .track-fill-up {
            position: absolute;
            bottom: 50%;
            left: 0;
            right: 0;
            background: linear-gradient(to top, #2ecc71, #27ae60);
            border-radius: 40px 40px 0 0;
        }
        .track-fill-down {
            position: absolute;
            top: 50%;
            left: 0;
            right: 0;
            background: linear-gradient(to bottom, #e74c3c, #c0392b);
            border-radius: 0 0 40px 40px;
        }
        .center-line {
            position: absolute;
            top: 50%;
            left: 10px;
            right: 10px;
            height: 3px;
            background: rgba(255,255,255,0.5);
            transform: translateY(-50%);
            border-radius: 2px;
        }
        .thumb {
            position: absolute;
            left: 50%;
            transform: translate(-50%, -50%);
            width: 70px;
            height: 70px;
            background: linear-gradient(145deg, #667eea, #764ba2);
            border-radius: 50%;
            box-shadow: 0 4px 20px rgba(0,0,0,0.5);
            cursor: pointer;
            z-index: 10;
        }
        .footer {
            text-align: center;
            padding: 10px;
            font-size: 12px;
            color: rgba(255,255,255,0.4);
        }
        .footer a { color: #667eea; text-decoration: none; }
    </style>
</head>
<body>
    <div class="header">Robot Car - Tank Mode</div>
    <div class="values">
        <span>SX: <span class="val" id="leftVal">0</span></span>
        <span>DX: <span class="val" id="rightVal">0</span></span>
    </div>
    <div class="container">
        <div class="slider-container">
            <div class="label">SINISTRA</div>
            <div class="track" id="leftTrack">
                <div class="track-fill-up" id="leftFillUp"></div>
                <div class="track-fill-down" id="leftFillDown"></div>
                <div class="center-line"></div>
                <div class="thumb" id="leftThumb"></div>
            </div>
        </div>
        <div class="slider-container">
            <div class="label">DESTRA</div>
            <div class="track" id="rightTrack">
                <div class="track-fill-up" id="rightFillUp"></div>
                <div class="track-fill-down" id="rightFillDown"></div>
                <div class="center-line"></div>
                <div class="thumb" id="rightThumb"></div>
            </div>
        </div>
    </div>
    <div class="footer"><a href="/">Modalita pulsanti</a></div>
    <script>
        let leftPower = 0, rightPower = 0;
        let leftActive = false, rightActive = false;
        let sendInterval = null;

        const leftTrack = document.getElementById('leftTrack');
        const rightTrack = document.getElementById('rightTrack');
        const leftThumb = document.getElementById('leftThumb');
        const rightThumb = document.getElementById('rightThumb');
        const leftFillUp = document.getElementById('leftFillUp');
        const leftFillDown = document.getElementById('leftFillDown');
        const rightFillUp = document.getElementById('rightFillUp');
        const rightFillDown = document.getElementById('rightFillDown');
        const leftVal = document.getElementById('leftVal');
        const rightVal = document.getElementById('rightVal');

        function updateSlider(track, thumb, fillUp, fillDown, valEl, power) {
            const rect = track.getBoundingClientRect();
            const centerY = rect.height / 2;
            const percent = power / 1023;
            const offset = -percent * centerY;

            thumb.style.top = (centerY + offset) + 'px';

            if (power > 0) {
                fillUp.style.height = (percent * 50) + '%';
                fillDown.style.height = '0%';
            } else if (power < 0) {
                fillUp.style.height = '0%';
                fillDown.style.height = (-percent * 50) + '%';
            } else {
                fillUp.style.height = '0%';
                fillDown.style.height = '0%';
            }

            valEl.textContent = power;
        }

        function calcPower(track, clientY) {
            const rect = track.getBoundingClientRect();
            const centerY = rect.top + rect.height / 2;
            const offset = centerY - clientY;
            const maxOffset = rect.height / 2;
            let power = Math.round((offset / maxOffset) * 1023);
            power = Math.max(-1023, Math.min(1023, power));
            return power;
        }

        function sendCommand() {
            fetch('/drive?l=' + leftPower + '&r=' + rightPower).catch(e => {});
        }

        function startSending() {
            if (!sendInterval) {
                sendInterval = setInterval(sendCommand, 100);
            }
        }

        function stopSending() {
            if (sendInterval && !leftActive && !rightActive) {
                clearInterval(sendInterval);
                sendInterval = null;
            }
        }

        // Left slider
        function handleLeftMove(clientY) {
            leftPower = calcPower(leftTrack, clientY);
            updateSlider(leftTrack, leftThumb, leftFillUp, leftFillDown, leftVal, leftPower);
        }

        leftTrack.addEventListener('touchstart', e => {
            e.preventDefault();
            leftActive = true;
            handleLeftMove(e.touches[0].clientY);
            startSending();
        }, {passive: false});

        leftTrack.addEventListener('touchmove', e => {
            e.preventDefault();
            if (leftActive) handleLeftMove(e.touches[0].clientY);
        }, {passive: false});

        leftTrack.addEventListener('touchend', e => {
            leftActive = false;
            leftPower = 0;
            updateSlider(leftTrack, leftThumb, leftFillUp, leftFillDown, leftVal, 0);
            sendCommand();
            stopSending();
        });

        // Right slider
        function handleRightMove(clientY) {
            rightPower = calcPower(rightTrack, clientY);
            updateSlider(rightTrack, rightThumb, rightFillUp, rightFillDown, rightVal, rightPower);
        }

        rightTrack.addEventListener('touchstart', e => {
            e.preventDefault();
            rightActive = true;
            handleRightMove(e.touches[0].clientY);
            startSending();
        }, {passive: false});

        rightTrack.addEventListener('touchmove', e => {
            e.preventDefault();
            if (rightActive) handleRightMove(e.touches[0].clientY);
        }, {passive: false});

        rightTrack.addEventListener('touchend', e => {
            rightActive = false;
            rightPower = 0;
            updateSlider(rightTrack, rightThumb, rightFillUp, rightFillDown, rightVal, 0);
            sendCommand();
            stopSending();
        });

        // Mouse support (for testing on PC)
        leftTrack.addEventListener('mousedown', e => {
            leftActive = true;
            handleLeftMove(e.clientY);
            startSending();
        });

        rightTrack.addEventListener('mousedown', e => {
            rightActive = true;
            handleRightMove(e.clientY);
            startSending();
        });

        document.addEventListener('mousemove', e => {
            if (leftActive) handleLeftMove(e.clientY);
            if (rightActive) handleRightMove(e.clientY);
        });

        document.addEventListener('mouseup', e => {
            if (leftActive) {
                leftActive = false;
                leftPower = 0;
                updateSlider(leftTrack, leftThumb, leftFillUp, leftFillDown, leftVal, 0);
            }
            if (rightActive) {
                rightActive = false;
                rightPower = 0;
                updateSlider(rightTrack, rightThumb, rightFillUp, rightFillDown, rightVal, 0);
            }
            sendCommand();
            stopSending();
        });

        // Init position
        updateSlider(leftTrack, leftThumb, leftFillUp, leftFillDown, leftVal, 0);
        updateSlider(rightTrack, rightThumb, rightFillUp, rightFillDown, rightVal, 0);
    </script>
</body>
</html>
)rawliteral";
    return html;
}
