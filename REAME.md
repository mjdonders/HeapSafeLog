# HeapSafeLog

A lightweight, heap-safe logging library for Arduino.

## 🚀 Why HeapSafeLog?

Most Arduino logging approaches rely on `String`, which can cause **heap fragmentation** and instability over time.

HeapSafeLog avoids this completely by:
- ❌ No use of `String`
- ✅ Variadic logging (`print(a, b, c)`)
- ✅ Zero heap fragmentation risk
- ✅ Arduino-native (`Print` based)
- ✅ Custom printable objects support

---

## 📦 Features

- Variadic logging interface
- Log levels: Debug, Info, Warn, Error
- No dynamic memory usage
- Compatible with all `Print` implementations (Serial, WiFiClient, etc.)
- Extendable via `Printable` interface
- Has some formatters, like hexadecimal print options, and providing of the width of the output (integer, float)

---


## 🧪 Usage

```cpp
#include <HeapSafeLog.h>

void setup() {
    Serial.begin(115200);
    MDO::logger().begin(Serial, 115200);

    MDO::logger().println("Hello", " ", "world", "!", 42);
}