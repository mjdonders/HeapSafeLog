# HeapSafeLog

HeapSafeLog is a lightweight, heap-safe logging library for Arduino designed to avoid String usage and prevent heap fragmentation.

It provides a simple variadic logging API with support for custom formatted types such as hex, decimal, and floating-point wrappers.

---

## ✨ Features

- 🚫 No `String` usage (heap fragmentation safe)
- ⚡ Variadic logging API
- 🧠 Arduino `Print` compatible backend
- 🔢 Built-in formatting helpers (hex / dec / float)
- 🧩 Custom printable interface support
- 📦 Minimal overhead, embedded-friendly design

---

## 🚀 Basic Usage

```cpp
#include <HeapSafeLog.h>

using namespace MDO;

void setup() {
    Serial.begin(115200);
    logger().begin(Serial, 115200);

    logger().println("Hello HeapSafeLog!");
}