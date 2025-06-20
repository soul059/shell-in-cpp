# Yoo Shell

A simple, cross-platform, and customizable shell created in C++.

## Features

*   **Cross-Platform:** Works on Windows, macOS, and Linux.
*   **Customizable:** Easily configure colors, commands, and startup messages through the `config.json` file.
*   **Lightweight:** A simple and fast shell for basic command-line tasks.

## Configuration

The shell can be configured by editing the `config.json` file. This file allows you to customize:

*   **Colors:** Change the colors of the shell prompt, error messages, and more.
*   **Commands:** Add or remove commands that the shell can execute.
*   **Startup and Shutdown:** Customize the messages displayed when the shell starts and exits.

### `config.json` Structure

```json
{
    "shell": {
        "print":{
            "name": "Yoo",
            "initial print":"Welcome to the Yoo Shell!\n Type 'help' for a list of commands.\n Type 'exit' to exit the shell.\n",
            "end print":"Thank you for using Yoo Shell!\n"
        },
        "commands":{
            "win64":{
                "terminal":["help","exit","dir","cd"],
                "app":["notepad","mspaint"]
            },
            "linux":{
                "terminal":["help","exit","ls","cd"],
                "app":["gedit"]
            }
        },
        "color":{
            "default":"#FFFFFF",
            "error":"#FF0000",
            "success":"#00FF00",
            "info":"#0000FF",
            "end":"#FFFFFF",
            "warning":"#FFFF00",
            "print":"#FF00FF"

        }

    }
}
```

## How to Build and Run

To build and run the shell, you will need a C++ compiler (like g++) and the `fmt` library.

1.  **Clone the repository:**

    ```bash
    git clone <repository-url>
    cd shell-in-cpp
    ```

2.  **Compile the source code:**

    ```bash
    g++ yoo.cpp config.cpp -o yoo.exe -std=c++17
    ```

3.  **Run the shell:**

    ```bash
    ./yoo.exe
    ```
