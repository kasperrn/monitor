# Monitor

A Raspberry Pi-based dashboard application written in C++, utilizing ImGui and GLFW to display widgets like gauges, charts, and labels. Designed for use in kiosk mode, it provides an immersive, full-screen experience with options for custom font and widget configurations.

## Features
- **Kiosk Mode**: Full-screen display without title bars or cursor.
- **Widgets**: Gauges, charts, and labels with adjustable attributes.
- **Custom Fonts**: Load custom font types and sizes for labels.

## Installation
Clone the repository:
```bash
git clone https://github.com/kasperrn/monitor
cd monitor
```
## Build

Ensure that you have the required dependencies installed: `GLFW`, `GLEW`, and `OpenGL`. Then compile the program with:

```bash
make
```
This will produce an executable file named dashboard in the project directory.

## Usage

To run the program in kiosk mode, use the following command:

```bash
./dashboard --kiosk
```
In kiosk mode, the application runs full-screen without window decorations or a visible cursor, providing an immersive display ideal for dashboards.
