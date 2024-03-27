# Ecosystem Simulation Project

This project simulates the ecosystem of creatures within a virtual environment, demonstrating various behaviors and interactions.

## Repository

[Github Repository](https://github.com/matdou/SimulationEcosysteme)

## Getting Started

To run this project on your local machine, follow these instructions.

### Prerequisites

Ensure you have a C++ compiler that supports at least C++14 standards.

### Installation and Execution

1. Clone the repository to your local machine.
2. Navigate to the cloned directory.
3. Run the `make` command to build the project:

    ```
    make
    ```

4. After a successful build, the executable will be located in the `bin` directory. Run it with:

    ```
    bin/main
    ```

## Project Details

- **Course:** Advanced C++
- **Institution:** IMT Atlantique
- **Date:** March 2024

### Participants

Mathis DOUTRE - Florian DESPLANQUE - Meriam CHOUMMIKH - Tantrède DONNAIS - Axel RUBIO

### Objective

The objective of this school project is to create a simulation environment that mimics the behavior and interactions of a small ecosystem of creatures. It aims to model realistic behaviors as observed in nature within a controlled virtual setting.

### Contributing

This project is an educational endeavor, and contributions are restricted to participating students.



## Environment Setup for macOS

Ensure your shell is zsh before proceeding. Run `bash echo $SHELL` in your terminal. If the output is `/bin/zsh`, you're using zsh.

### Update zsh Configuration

Edit .zshrc: Open with `open -a TextEdit ~/.zshrc`.

### Add Variables:
```sh
export CPATH=/opt/X11/include:$CPATH
export LIBRARY_PATH=/opt/X11/lib:$LIBRARY_PATH
export DYLD_LIBRARY_PATH=/opt/X11/lib:$DYLD_LIBRARY_PATH
```

### Apply Changes:
Run `source ~/.zshrc` in your terminal.

This setup ensures the X11 headers and libraries are correctly recognized for development.
