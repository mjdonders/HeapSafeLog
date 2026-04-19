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
    logger().begin(Serial, 115200);

    logger().println("Hello HeapSafeLog!");
	
	int iValue1 = 6;
	int iValue2 = 42;
	logger().println("Some variables for debug purposes:");
	logger().println("variable 1 value: ", iValue1, " and value2 in hex: ", MDO::hex(iValue2));
}
