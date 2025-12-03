<div align="center">

# Python Scripting Engine

![Build](https://img.shields.io/badge/build-passing-darkgreen?style=for-the-badge)
[![Python](https://img.shields.io/badge/python-3.xx-blue?style=for-the-badge)](https://docs.python.org/3/)
[![License](https://img.shields.io/badge/License-AGPL-maroon?style=for-the-badge)](LICENSE)

A Python Scripting Engine module for AzerothCore that allows server administrators and developers to create custom gameplay features using **Python 3** without modifying the core codebase.

</div>

---

## Overview

This module integrates the Python interpreter directly into the AzerothCore worldserver, letting you write game scripts in Python instead of C++. This dramatically reduces development time for custom features, allows rapid iteration without recompiling the core, and makes AzerothCore accessible to developers in the broader Python community.

### Key Features

-   **Accessible Development**: Python allows developers without C++ experience to create server features effortlessly
-   **Python 3 Integration**: Full embedding of the Python interpreter with C++ interoperability
-   **Event-Driven Architecture**: Hook into core game events using a straightforward Python API
-   **Hot-Reload Support**: Modify and reload scripts without recompiling or restarting the server

> [!IMPORTANT]
> The module is designed for rapid feature development and scripting convenience -- not as a replacement for performance-critical C++ systems. When used appropriately, the productivity gains far outweigh the performance trade-offs for most server features.

## Installation

### System Requirements
- AzerothCore (latest master branch)
- Python 3.10+ with development headers
- Boost 1.74+ with matching Python component
- CMake 3.16+
- Git

### Build Instructions
> [!WARNING]
> Before starting, ensure that you have all dependencies installed on your system: Boost.Python and Python 3 development headers. For example, for **Ubuntu/Debian**, you should run these commands first: `sudo apt update && sudo apt install python3-dev libpython3-dev libboost-python-dev`
```bash
# Navigate to your AzerothCore modules directory and clone the repository
cd <azerothcore-source-path>/modules
git clone https://github.com/privatecore/mod-python-engine.git

# Navigate to your AzerothCore build directory and run CMake
cd <azerothcore-source-path>/build
cmake ../ -DCMAKE_INSTALL_PREFIX=/path/to/install

# Compile the server to integrate the new module
make -j$(nproc)
make install
```

### Docker Setup
If building inside a container, ensure runtime dependencies are installed in the **runtime image**.

You can find a configuration example in the `modules/mod-python-engine/apps/docker` directory. Simply copy the `docker-compose.override.yml` file to your `<azerothcore-source-path>` and then run the following commands:
```bash
# You need to build dependencies container first, otherwise build will fail
docker compose build ac-dependencies
docker compose build
```

## Configuration

The module comes with a default configuration file. Rename `mod-python.conf.dist` to `mod-python.conf` in your server's configuration directory.
```config
# Enable or disable the Python scripting engine
Python.Enabled = 1

# Path to your Python scripts (relative or absolute)
Python.ScriptsPath = "python_scripts"
```

## Example

### Directory Structure
Place your `.py` files in the folder specified by `Python.ScriptsPath`. The engine recursively loads all `.py` files found in this directory.

### Example Script: Hello World
```python
import azerothcore as ac

def on_login(player):
    name = player.GetName()
    print(f"Player {name} has logged in!")
    player.SendSysMessage(f"Welcome to the server, {name}!")

# Register the hook
ac.Register("PLAYER_ON_LOGIN", on_login)
```

### Example Script: Gossip Hello
```python
import azerothcore as ac

ITEM_ID = 12345
NPC_ID = 99999

def on_gossip_hello(player, creature):
    creature.Say("Under sun and sky, outlander. We greet you warmly.", 0)
    if player.GetClass() == ac.Class.Warrior:
        player.AddItem(ITEM_ID, 1)

# Register hook for specific entry ID
ac.Register("CREATURE_ON_GOSSIP_HELLO", on_gossip_hello, NPC_ID)
```

## Contributing

Contributions are welcome! Please feel free to submit pull requests, report bugs, or suggest new features through the [GitHub Issues](https://github.com/privatecore/mod-python-engine/issues) page.

## License

This module is released under the [GNU AGPL v3](LICENSE) license, compatible with AzerothCore.
