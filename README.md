# 2d_classic_platformer

This is a simple project designed to demonstrate and practice player movements, jump mechanisms, and collision detection for a 2D classic platformer game.

## Overview

In this project, we implement a basic platformer game environment using SDL (Simple DirectMedia Layer). The game features a player character that can move horizontally, jump, and interact with the environment through collision detection.

## Features

- **Player Movements**: The player character can move horizontally using the left and right arrow keys.
- **Jump Mechanism**: The player character can jump using the 'W' key. The jump height and gravity can be adjusted as needed.
- **Collision Detection**: The game implements collision detection between the player character and the game environment, including platforms. This ensures realistic interactions between the player and the environment.
- **Tile Map**: The game environment consists of a tile map represented by a vector of tiles. Tiles are defined as solid or non-solid, allowing for flexible level design.

## Getting Started

To run the project, you'll need to set up an SDL development environment. Follow these steps:

1. Install SDL: Download and install the SDL library for your platform from the official SDL website.
2. Clone the Repository: Clone this repository to your local machine.
3. Build the Project: Use your preferred build system (e.g., CMake) to build the project files.
4. Run the Game: Execute the built executable to run the game.

## Usage

- **Controls**:
  - Use the left and right arrow keys to move the player character horizontally.
  - Press the 'W' key to make the player character jump.
  - Press the 'ESC' key to exit the game.

## Customization

Feel free to customize the game as needed. You can adjust various parameters such as player speed, jump height, gravity, and level design by modifying the source code.

## Credits

This project was created by [Appyouz]. It is intended for educational purposes and to serve as a starting point for building 2D platformer games using SDL.

## License

This project is licensed under the [MIT License](LICENSE).
