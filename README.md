# Dungeon Crawler Game (Text Based)

This is a complete terminal-based Dungeon Crawler RPG game. It was developed as part of an academic project to demonstrate  object-oriented programming, data structures, algorithms, and modern C++ features in a compact and playable format.

The game offers an immersive, text-based experience where the player navigates through rooms, collects weapons and food, engages in combat with enemies, and manages their health and inventory in real time.

## Features

- **Terminal UI**: Built using `ncurses`, the game displays a multi-window interface including inventory, game status, and real-time feedback.
- **Player Mechanics**: The player moves through rooms, picks up weapons and food, and fights enemies using turn-based combat.
- **Object-Oriented Design**: Uses classes and inheritance to model game entities such as `Enemy`, `Weapon`, and `Food`, derived from an abstract base class `RoomElements`.
- **Inventory System**: Implements a template-based `Inventory<T>` class for storing weapons and food items using a dynamic array with automatic resizing.
- **Custom Queue**: Room elements are managed using a custom `ElementQueue` with FIFO logic for exploration.
- **Sorting Algorithms**: Weapons are sorted using Insertion Sort based on damage; food items are sorted using Shell Sort based on health value.
- **Modern C++**: Includes RAII principles, exception handling for game-over scenarios, and lambda functions for clean initialization and gameplay logic.

## How It Works

- The player starts with a basic inventory and health.
- As the player progresses through rooms, they encounter enemies or find items (weapons or food).
- Combat is turn-based: the player and enemy exchange attacks until one is defeated.
- Weapons affect damage dealt; food restores health.
- Inventory is dynamically managed and sorted after each update.
- The game ends when the player’s health reaches zero or the player escapes the dungeon.

## Build and Run

### Requirements

- A C++17-compatible compiler
- `ncurses` library installed (Linux/macOS). For Windows, use `pdcurses`.
