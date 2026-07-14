# cub3D – 42 Project

*This project has been created as part of the 42 curriculum by joapedro and grui-ant.*

# 🎮 cub3D – 42 Project

## 📖 Description

cub3D is a graphics project from the 42 curriculum inspired by the classic game **Wolfenstein 3D**.

The goal of this project is to create a simple first-person 3D game engine using **raycasting** techniques. The project introduces the fundamentals of computer graphics, window management, textures, and real-time rendering.

Throughout this project, you will learn how to:

- Create and manage graphical windows
- Handle keyboard input and user interaction
- Work with images and textures
- Implement raycasting algorithms
- Calculate player movement and rotation
- Render a 3D environment from a 2D map
- Manage memory and resources correctly
- Organize a larger C project

The project uses the **MiniLibX** graphical library provided by 42.

---

# ⚙️ Instructions

## 🛠️ Compilation

Clone the repository and enter the project directory:

```bash
cd cub3D
```

Compile the project using:

```bash
make
```

The executable will be created:

```bash
./cub3D
```

Run the game with a map file:

```bash
./cub3D maps/example.cub
```

### The project is divided into different modules to keep the code organized:

- **Parsing**  
  Responsible for reading and validating map files.

- **Rendering**  
  Handles raycasting calculations and drawing the 3D world.

- **Movement**  
  Manages player movement, rotation, and controls.

- **Textures**  
  Loads and applies wall textures.

- **Utils**  
  Contains helper functions used throughout the project.

---

# 🕹️ Controls

| Key | Action |
|-----|--------|
| W | Move forward |
| S | Move backward |
| A | Move left |
| D | Move right |
| ← | Rotate left |
| → | Rotate right |
| ESC | Exit game |

---

# 🗺️ Map Format

Maps use the `.cub` extension.

Example:

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,225,225

111111
100001
100N01
100001
111111
```

The map contains:

- Texture paths
- Floor and ceiling colors
- A 2D representation of the game world
- Player starting position and orientation

---

# 🧠 Concepts Covered

Through this project, you will learn:

- Raycasting algorithms
- Trigonometry and vector calculations
- Computer graphics fundamentals
- Image manipulation
- Event handling
- Keyboard input management
- Memory allocation and freeing
- File parsing
- Error handling
- Modular C programming

---

# 🎯 Learning Objectives

By completing cub3D, you should understand:

- How simple 3D engines work
- How 2D maps can be transformed into 3D views
- How rays are calculated and projected
- How textures are applied to walls
- How to manage a graphical application
- How to structure a larger C project

---

# ⚠️ Notes

- The project must compile with:

```
-Wall
-Wextra
-Werror
```

- Memory leaks must be avoided.
- All allocated resources must be properly freed.
- The program must handle invalid maps gracefully.
- The project follows the 42 Norm.
- The MiniLibX library is required.
- AI was used as learning reference.

---

# 📚 Resources

## Raycasting

- Lode's Computer Graphics Tutorial  
  https://lodev.org/cgtutor/raycasting.html

- Abdilah CH tutorial
  https://devabdilah.medium.com/3d-ray-casting-game-with-cub3d-7a116376056a

## MiniLibX

- 42 MiniLibX Documentation
- `man mlx`

## C Documentation

- C Reference  
  https://en.cppreference.com/w/c
