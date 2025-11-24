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

If you'd like, I can also:
- add a short example usage snippet for `BluetoothManager.java` and `btManager.hpp`,
- or create a sample Android Studio module to make integration drop-in.

---
Repository maintained for reuse with embedded projects.
