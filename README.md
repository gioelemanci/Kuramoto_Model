# 🧠 Kuramoto_Model

A C++ simulation and analysis framework for the Kuramoto model of coupled oscillators, featuring real-time visualization with SFML and automated data export for post-processing.

---

## 🚀 Features

- Kuramoto model simulation with customizable parameters
- Real-time graphical visualization using SFML
- Automated analysis:
  - Order parameter computation
  - Phase distribution
  - Mean frequency calculation
  - Locked vs drifting oscillator classification
  - Grouping by natural frequency
- Organized output saved to structured folders
- Cross-platform support (Windows, Linux, WSL)

---

## 🛠️ Requirements

- CMake ≥ 3.14
- C++17-compatible compiler (GCC, Clang, MSVC)
- Git
- Ninja (recommended on Windows)

> ✅ SFML is automatically downloaded and built via `FetchContent`. No manual installation required.

---

## 📦 Build Instructions

### 1. Clone the repository

```bash
git clone https://github.com/gioelemanci/Kuramoto_Model.git
cd Kuramoto_Model
```

### 2. Configure and build

```bash
cmake -S . -B build
cmake --build build
```

### 3. Run the executable

```bash
./build/bin/Kuramoto_Model
```

On Windows (PowerShell):

```bash
.\build_and_run.bat
```

## 📌 Project Structure
```
Kuramoto_Model/
├── src/                # Core implementation
├── include/            # Header files
├── test/               # Unit tests
├── main.cpp            # Entry point
├── CMakeLists.txt      # Build configuration
├── build_and_run.bat   # Windows build

```

## 📁 Output Structure

Simulation results are automatically saved to:

```
analysis_data/
├── phases/
├── order_parameters/
├── frequencies/
├── locked/
├── drifting/
```

These folders are created automatically and can be excluded from version control.

## 🧪 Testing

Unit tests are available for:
- Oscillator classes
- Kuramoto model
- Simulation engine
- Frequency distributions