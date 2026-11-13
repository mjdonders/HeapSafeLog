# HeapSafeLog

HeapSafeLog is a lightweight, heap-safe logging library for Arduino.

The main goal is to **prevent heap fragmentation**, which is achieved by avoiding the use of `String`.

It provides a simple variadic logging API with support for custom formatting types such as hexadecimal, decimal, and floating-point wrappers.

---

## Features

- No `String` usage (safe against heap fragmentation)
- Variadic logging API
- Arduino `Print`-compatible backend
- Built-in formatting helpers (hex / dec / float)
- Custom printable interface support
- Configurable log levels (DEBUG / INFO / WARN / ERROR / NONE)
- Minimal overhead

---

## Basic Usage

```cpp
#include <HeapSafeLog.h>

using namespace MDO;

void setup() {
#if defined(ARDUINO_USB_CDC_ON_BOOT) && ARDUINO_USB_CDC_ON_BOOT
    // Native USB CDC (e.g. ESP32-S3)
    Serial.begin(115200);
    logger().begin(Serial);
#else
    // Hardware UART
    logger().begin(Serial, 115200);
#endif

    logger().println("Hello HeapSafeLog!");

    int iValue1 = 6;
    int iValue2 = 42;

    logger().println("Some variables for debug purposes:");
    logger().println("variable 1 value: ", iValue1,
                     " and value2 in hex: ", hex(iValue2));
}
