# BluetoothManager-AndroidStudio-Esp32

This repository contains a simple Bluetooth manager split between an Android-side helper and an ESP32-side header. It was used as the Bluetooth control component for the embedded project: https://github.com/chitic05/Embedded-Mini-Car.git

**Overview**
- **Purpose:** Provide a small, reusable Bluetooth management layer for Android (client) and ESP32 (server) to ease pairing, connecting, and message exchange.
- **Used in:** `Embedded-Mini-Car` project (link above) — this repo supplies the Android app Bluetooth client and the ESP32 helper header used in that project.

**Repository Structure**
- `Android Studio/` - Android-side example including `BluetoothManager.java`.
- `Esp-32/` - ESP32-side helper header `btManager.hpp` (C++/Arduino style).

**Files of Interest**
- `Android Studio/BluetoothManager.java`: simple Android helper class that wraps Bluetooth discovery, connect and message I/O.
- `Esp-32/btManager.hpp`: ESP32-side helper to process serial/Bluetooth messages and provide a small API for your firmware.

**Quick Integration Notes**

- Android (client):
  - Copy or reference `Android Studio/BluetoothManager.java` into your Android project.
  - Typical use: create an instance, request permissions, start discovery or connect to a known address, then use the read/write helpers.

- ESP32 (server/firmware):
  - Include `Esp-32/btManager.hpp` in your firmware source.
  - Initialize the Bluetooth manager during setup and call the processing loop from `loop()` (Arduino) or your main task.

**How I used this in Embedded-Mini-Car**
- The Android app (based on `BluetoothManager.java`) runs on the phone and connects to the ESP32 in the car.
- The ESP32 firmware includes `btManager.hpp` to handle incoming commands (e.g., drive/stop/steer) and to send telemetry back to the app.
- If you want to reproduce the same setup, clone both repositories and follow their README/build instructions:

  - Embedded firmware: https://github.com/chitic05/Embedded-Mini-Car.git
  - Android app: use `Android Studio/` from this repository or port `BluetoothManager.java` into your app module.

**Prerequisites**
- Android: Android Studio, target SDK appropriate for Bluetooth Classic/ BLE depending on the helper implementation; runtime Bluetooth & location permissions may be required.
- ESP32: PlatformIO or Arduino IDE with ESP32 board support installed.

**Build & Run (high-level)**
- ESP32: compile and flash your firmware that includes `btManager.hpp`.
- Android: import the Android files into an Android Studio project, run on a device with Bluetooth, grant permissions, and pair/connect to the ESP32 device.

**License & Notes**
- This repository contains small helper code snippets intended as examples. Check individual files for author/license details.
- For any issues or questions about how this was integrated into `Embedded-Mini-Car`, refer to that repository or open an issue in that repo.

**Example Usage**

Here are short, copy-paste friendly examples to show how to use the Android and ESP32 helpers. Adjust method/class names to match the exact APIs in `Android Studio/BluetoothManager.java` and `Esp-32/btManager.hpp`.

- Android (Java) - simple client example:

```java
// In an Activity
BluetoothManager bt = new BluetoothManager(this);

// Ensure runtime permissions and Bluetooth enabled first
bt.requestPermissionsIfNeeded(this);

// Connect to the ESP32 MAC address (replace with your device address)
bt.connect("00:11:22:33:44:55");

// Send a command to the car
bt.send("DRIVE:FORWARD");

// Listen for incoming messages / telemetry
bt.setOnMessageReceivedListener(new BluetoothManager.OnMessageReceived() {
    @Override
    public void onMessage(String message) {
        // handle telemetry or ACKs here
        Log.d("BT", "Received: " + message);
    }
});
```

- ESP32 (Arduino-style) - simple server example:

```cpp
#include "btManager.hpp"

BTManager bt; // class name may vary; match your header

void setup() {
  Serial.begin(115200);
  // Initialize Bluetooth (device name shown by phone)
  bt.begin("ESP32-CAR");
}

void loop() {
  // Process Bluetooth events (if your helper provides a loop/process method)
  bt.loop();

  // Read a command if available
  if (bt.available()) {
    String cmd = bt.readLine(); // or bt.read()
    if (cmd == "DRIVE:FORWARD") {
      // drive motors forward
    } else if (cmd.startsWith("STEER:")) {
      // parse steering value
    }
  }

  // Send telemetry back to the app
  bt.send("SPEED:120");
  delay(100);
}
```

**Quick test sequence**
- Flash the ESP32 firmware that includes `Esp-32/btManager.hpp`.
- Power the ESP32 and note the Bluetooth name (e.g., `ESP32-CAR`).
- On the phone, enable Bluetooth and pair with the ESP32 if using Classic pairing.
- Run the Android app (or the activity that uses `BluetoothManager.java`), connect to the ESP32 address, then send commands and observe telemetry in the app logs.

If you want, I can also add precise, copy-accurate snippets that match the public method names in your `BluetoothManager.java` and `btManager.hpp` — would you like me to extract those directly from the files and paste exact examples?

---
Repository maintained for reuse with embedded projects.
# BluetoothManager-AndroidStudio-Esp32

This repository contains a simple Bluetooth manager split between an Android-side helper and an ESP32-side header. It was used as the Bluetooth control component for the embedded project: https://github.com/chitic05/Embedded-Mini-Car.git

**Overview**
- **Purpose:** Provide a small, reusable Bluetooth management layer for Android (client) and ESP32 (server) to ease pairing, connecting, and message exchange.
- **Used in:** `Embedded-Mini-Car` project (link above) — this repo supplies the Android app Bluetooth client and the ESP32 helper header used in that project.

**Repository Structure**
- `Android Studio/` - Android-side example including `BluetoothManager.java`.
- `Esp-32/` - ESP32-side helper header `btManager.hpp` (C++/Arduino style).

**Files of Interest**
- `Android Studio/BluetoothManager.java`: simple Android helper class that wraps Bluetooth discovery, connect and message I/O.
- `Esp-32/btManager.hpp`: ESP32-side helper to process serial/Bluetooth messages and provide a small API for your firmware.

**Quick Integration Notes**

- Android (client):
  - Copy or reference `Android Studio/BluetoothManager.java` into your Android project.
  - Typical use: create an instance, request permissions, start discovery or connect to a known address, then use the read/write helpers.

- ESP32 (server/firmware):
  - Include `Esp-32/btManager.hpp` in your firmware source.
  - Initialize the Bluetooth manager during setup and call the processing loop from `loop()` (Arduino) or your main task.

**How I used this in Embedded-Mini-Car**
- The Android app (based on `BluetoothManager.java`) runs on the phone and connects to the ESP32 in the car.
- The ESP32 firmware includes `btManager.hpp` to handle incoming commands (e.g., drive/stop/steer) and to send telemetry back to the app.
- If you want to reproduce the same setup, clone both repositories and follow their README/build instructions:

  - Embedded firmware: https://github.com/chitic05/Embedded-Mini-Car.git
  - Android app: use `Android Studio/` from this repository or port `BluetoothManager.java` into your app module.

**Prerequisites**
- Android: Android Studio, target SDK appropriate for Bluetooth Classic/ BLE depending on the helper implementation; runtime Bluetooth & location permissions may be required.
- ESP32: PlatformIO or Arduino IDE with ESP32 board support installed.

**Build & Run (high-level)**
- ESP32: compile and flash your firmware that includes `btManager.hpp`.
- Android: import the Android files into an Android Studio project, run on a device with Bluetooth, grant permissions, and pair/connect to the ESP32 device.