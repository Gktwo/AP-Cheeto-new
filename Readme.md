# AzurPromilia Game Modification Tool

## Overview

This project is a C++ DLL-based modification tool for the AzurPromilia game, built using IL2CPP reverse engineering techniques. It provides various enhancement features to improve gameplay experience.

## Features

### ESP (Extra Sensory Perception)
- **Entity Display**: Show different types of game entities with customizable visibility
  - Monsters, NPCs, Friendly units, Puzzles
  - Configurable display options for distance, entity ID, config name, and type information
- **Visual Enhancements**: Color-coded entity highlighting with distance information
- **Collapsible UI**: Organized settings interface with expandable categories

### Core Components
- **IL2CPP Integration**: Direct game memory access and function hooking
- **ImGui Interface**: Modern, responsive user interface for configuration
- **DirectX 11 Rendering**: Hardware-accelerated overlay rendering
- **Hook Management**: Safe and reliable game function interception

## Technical Stack

- **Language**: C++
- **Graphics**: DirectX 11 + ImGui
- **Libraries**: 
  - magic_enum (enum reflection)
  - nlohmann/json (configuration management)
  - Microsoft Detours (function hooking)
- **Build System**: Visual Studio 2019/2022

## Project Structure

```
├── framework/          # Core IL2CPP integration and initialization
├── libraries/          # Third-party dependencies
│   ├── imgui/         # GUI framework
│   ├── json/          # JSON processing
│   ├── magic_enum/    # Enum utilities
│   └── pipeline/      # Main application logic
├── appdata/           # IL2CPP API definitions
└── user/              # Entry point and main logic
```

## Usage

1. Compile the project using Visual Studio
2. Inject the generated DLL into the target game process
3. Use the in-game overlay to configure ESP settings
4. Toggle features using the collapsible interface

## Disclaimer

This tool is for educational and research purposes only. Use responsibly and in accordance with the game's terms of service.