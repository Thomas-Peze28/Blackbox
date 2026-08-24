# Blackbox

Blackbox is an asynchronous lightweight logging library in C++20. It lets you emit log messages without blocking the main execution thread, with colored terminal output and plain-text file output.

## Features

- Asynchronous logging through a thread-safe queue.
- Log levels: `TRACE`, `DEBUG`, `INFO`, `WARN`, `ERROR`, `FATAL`.
- Colored terminal output.
- Logging to a file of your choice.
- Simple macro-based API: `LOG_TRACE`, `LOG_DEBUG`, `LOG_INFO`, `LOG_WARN`, `LOG_ERROR`, `LOG_FATAL`.

## Requirements

- A C++20-compatible compiler.
- `make`
- `g++`
- `pthread`

## Build

```bash
make
```

The example binary is generated in `bin/example_basic`.

To clean build artifacts:

```bash
make clean
```

## Usage

Here is an initialization example:

```cpp
#include "blackbox/Logger.hpp"

int main()
{
    blackbox::Logger::instance().init("log/blackbox.log", blackbox::LogLevel::TRACE);

    LOG_INFO("Main program started");
    LOG_WARN("Warning: CPU load is " << 87.5 << "%");
    LOG_ERROR("Error detected: " << "File not found");

    return 0;
}
```

### Output

Here is an example output:

```bash
2026-08-24 20:14:56 [INFO] [examples/main.cpp:17] Main program started
2026-08-24 20:14:56 [TRACE] [examples/main.cpp:18] Debug trace: x value = 42
2026-08-24 20:14:56 [DEBUG] [examples/main.cpp:19] Connection active on port 8080
2026-08-24 20:14:56 [WARN] [examples/main.cpp:20] Warning: CPU load is 87.5%
2026-08-24 20:14:56 [ERROR] [examples/main.cpp:21] Error detected: File not found
2026-08-24 20:14:56 [FATAL] [examples/main.cpp:22] Critical module shutdown
```

## Installation

To copy the public header into `/usr/local/include`:

```bash
make install
```

To uninstall:

```bash
make uninstall
```

## Example

The example in `examples/main.cpp` writes logs to `log/blackbox.log`.

Run the example after building:

```bash
./bin/example_basic
```
