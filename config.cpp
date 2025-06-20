#include<iostream>
#include <cstdlib>
#include<vector>
#include<string>
#include <filesystem>
#include "config.h"
using namespace  std;

#ifdef _WIN64
    #include <direct.h>
    #define getcwd _getcwd
#else
    #include <unistd.h>
    #define getcwd getcwd
#endif


string pre_start_print() {
    return "Welcome to the Yoo Shell!\n Type 'help' for a list of commands.\n Type 'exit' to exit the shell.\n";
}
string shell_name() {
    return "yoo";
}
string shell_print() {
    string result ="yoo ";
    // std::filesystem::path cwd = std::filesystem::current_path();
    // result += cwd.string(); // Get current working directory
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        result += cwd; // Append current working directory
    } else {
        result += "Unknown Directory"; // Fallback if getcwd fails
    }
    result += " > "; // Append shell prompt
    return result;
}
vector<string> shell_commands() {
    vector<string> comm ; 
    #ifdef _WIN64
        comm = {"help","exit","dir","cd","mkdir","rmdir","del","cls","time","copy","ping","ipconfig","fc","calc","echo"};
        vector<string> apps = {"notepad"}; // Windows
        comm.insert(comm.end(), apps.begin(), apps.end()); // Add applications to commands
    #elif __APPLE__
        comm = {}; // macOS
    #elif __linux__
        comm = {"help", "exit", "sudo","ls", "pwd", "cd", "mkdir", "rmdir", "touch", "rm", "cat", "echo"}; // Linux
    #elif __unix__
        comm = {}; // Other UNIX-based OS
    #else
        comm = {}; // Default for unknown OS
    #endif

    return comm;
}
int no_of_commands() {
    return shell_commands().size();
}
void shell_commands_help() {
    string help_text = "Available commands:\n";
    for(const auto& command : shell_commands()) {
        cout << command << endl; // Print each command
        help_text += command + "\n"; // Append command to help text
    }
}


string shell_end() {
    return "Exiting Yoo Shell.";
}

void shell_commands_exit() {
    cout << shell_end_color <<"Exiting the shell."<<shell_color_reset << endl;
    exit(0); // Exit the program
}

void commands_cd(string path) {
    #ifdef _WIN64
        if (_chdir(path.c_str()) != 0) {
            cerr << "Error changing directory to " << path << endl;
        }
    #else
        if (chdir(path.c_str()) != 0) {
            cerr << "Error changing directory to " << path << endl;
        }
    #endif
}


// Color functions for terminal output
string shell_end_color() {
    return "\033[0m"; // Reset color
}
string error_color() {
    return "\033[31m"; // Red color for errors
}
string succes_color() {
    return "\033[32m"; // Green color for success
}
string shell_print_color() {
    return "\033[36m"; // Cyan color for shell prompt
}
string pre_start_print_color() {
    return "\033[32m"; // Green color for welcome message
}
string shell_color_reset() {
    return "\033[0m"; // Reset color
}
