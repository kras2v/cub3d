# Cub3D

[Screencast from 2025-09-18 20-45-01.webm](https://github.com/user-attachments/assets/3f2d8064-8754-422e-8689-449b92febf4e)

Cub3D is a 3D game project developed in C using **MiniLibX**, inspired by the classic Wolfenstein 3D.
It demonstrates understanding of **raycasting**, **graphics rendering**, and **game logic** in a minimalistic environment.

---

## Table of Contents

* [Installation](#installation)
* [Dependencies](#dependencies)
* [Usage](#usage)
* [Controls](#controls)
* [Features](#features)
* [Project Structure](#project-structure)
* [Author](#author)

---

## Installation

1. Clone the repository:

```bash
git clone https://github.com/kras2v/cub3d.git
cd cub3d
```

2. Compile the project:

```bash
make
```

3. Run the game:

```bash
./cub3d maps/<map_file>.cub
```

---

## Dependencies

* C compiler (`gcc`)
* [MiniLibX](https://github.com/42Paris/minilibx-linux)
* X11 development libraries (Linux):
  
---

## Usage

```bash
./cub3d maps/<map_file>.cub
```

* Replace `<map_file>` with a `.cub` file containing your map layout.
* The program reads the map, renders walls, floors, and sprites in a first-person 3D perspective.

---

## Controls

* **W / Up Arrow** – Move forward
* **S / Down Arrow** – Move backward
* **A / Left Arrow** – Move left
* **D / Right Arrow** – Move right
* **Left / Right Arrow** – Rotate view
* **ESC** – Exit the game
* **Mouse Movement** – Rotate view horizontally

---

## Features

* Raycasting engine for 3D rendering
* Textured walls and floor/ceiling
* Sprite rendering
* Collision detection
* Animated sprite
* Doors that opens and closes
* Configurable `.cub` map files

---

## Project Structure

```
cub3d/
│
├── bonus/                # Bonus part
  ├── srcs_bonus/         # Bonus source code
  ├── includes_bonus/     # Bonus headers
├── libs/libft/           # Libft library
├── mandatory/            # Mandatory part
  ├── mandatory_srcs/     # Mandatory source code
  ├── mandatory_includes/ # Mandatory headers
├── maps/                 # Example map files
├── textures/             # Textures
├── minilibx_linux/       # MiniLibX submodule
├── Makefile
└── README.md

```

---

## Authors

* Valeriia Krasnianska – [GitHub](https://github.com/kras2v)
* Elina Klymova        - [GitHub](https://github.com/elinakly)
* School 42 Project
