#include<iostream>
#include <cstdlib>
#include<string>
#include<vector>
#include <sstream>
#include <iomanip>
#include "config.h"
#define FMT_HEADER_ONLY
#include "fmt/color.h"
#include "fmt/format.h"
using namespace  std;

string handle_input() {
    string input;
    getline(cin, input); // Read a line of input from the user
    if(input.empty()) {
        return ""; // Return empty string if no input
    }
    return input; // Return the input string
}

int validate_input(const string &input) {
    vector<string> validcommands = shell_commands(); // Get valid commands from config
    if(validcommands.empty()) {
        fmt::print(fmt::fg(hex_to_rgb_my(error_color())), "Error: No valid commands available.\n");
        return 0; // Return 0 for invalid input
    }
    int numcommands =  no_of_commands(); // Get the number of valid commands

    // Check if input is empty
    if(input.empty()) {
        fmt::print(fmt::fg(hex_to_rgb_my(error_color())), "Error: No input provided.\n");
        return 0; // Return 0 for invalid input
    }

    // Split the input into command and arguments
    vector<string> tokens;
    size_t pos = 0;
    string token;
    string delimiter = " ";
    string input_copy = input;

    while ((pos = input_copy.find(delimiter)) != string::npos) {
        token = input_copy.substr(0, pos);
        tokens.push_back(token);
        input_copy = input_copy.substr(pos + delimiter.length());
    }
    tokens.push_back(input_copy); // Add the last token

    // Check if the command is valid
    string command = tokens[0];
    if(tokens[0] == "exit") shell_commands_exit(); // Handle exit command
    if(tokens[0] == "help") {
        shell_commands_help(); // Print help for commands
        return 0; // Return 0 for help command
    }
    if(command == "sudo"){
        string sudo_command = tokens.size() > 1 ? tokens[1] : "";
        if(sudo_command.empty()) {
            fmt::print(fmt::fg(hex_to_rgb_my(error_color())), "Error: No command provided for sudo.\n");
            return 0; // Return 0 for invalid sudo command
        }
        if(sudo_command == "cd") {
            if(tokens.size() < 3) {
                fmt::print(fmt::fg(hex_to_rgb_my(error_color())), "Error: No directory specified for sudo cd.\n");
                return 0; // Return 0 for invalid sudo cd command
            }
            commands_cd(tokens.size() > 2 ? tokens[2] : "");
            return 0; // Return 0 for valid sudo cd command
        } // Handle cd command with sudo
        for(int i = 0; i < numcommands; i++) {
            if(sudo_command == validcommands[i]) {
                return 1; // Return 1 for valid input
            }
        }
    }
    if(command == "cd") {
        if(tokens.size() < 2) {
            fmt::print(fmt::fg(hex_to_rgb_my(error_color())), "Error: No directory specified for cd.\n");
            return 0; // Return 0 for invalid cd command
        }
        commands_cd(tokens[1]); // Call command_cd with the specified directory
        return 0; // Return 1 for valid input
    }
    for(int i = 0; i < numcommands; i++) {
        if(command == validcommands[i]) {
            return 1; // Return 1 for valid input
        }
    }
    fmt::print(fmt::fg(hex_to_rgb_my(error_color())), "Error: Invalid command \'{}'\n",command);
    return 0; // Return 0 for invalid input
}

string input_exicute(const string &input) {
    
    string result;
    // giving system command and storing return value
    int returnCode = system(input.c_str());

    // checking if the command was executed successfully
    if (returnCode == 0) {
        result = "Command executed successfully.";
    }
    else {
        fmt::print(fmt::fg(hex_to_rgb_my(error_color())), "Command execution failed or returned non-zero:  {}\n", returnCode);
    }
    return result; // Return the result of command execution
}
void yoo_loop() {
    while(true) {
        fmt::print(fmt::fg(hex_to_rgb_my(shell_print_color())), shell_print());

        string input = handle_input();
        int chack = validate_input(input);
        if(chack == 0) {
            continue; // Skip to the next iteration if input is invalid
        }
        string result = input_exicute(input);
        if(!result.empty()) {
            fmt::print(fmt::fg(hex_to_rgb_my(succes_color())), "{}\n",result); // Print success message
        }
        else {
            fmt::print(fmt::fg(hex_to_rgb_my(warning_color())), "No output from command.");
        }
        
    }
}

int main(int argc, char **argv) {
    set_configuration(); // Load configuration settings
    //pre shell setup
    fmt::print(fmt::fg(hex_to_rgb_my(pre_start_print_color())), "Shell Name: {}\n", shell_name()); // Print shell name
    fmt::print(fmt::fg(hex_to_rgb_my(pre_start_print_color())), "{}\n",pre_start_print()); // Print shell name
    
    // Start loop for input in shell
    yoo_loop();
    
    // Post shell cleanup
    fmt::print(fmt::fg(hex_to_rgb_my(shell_end_color())), shell_end()); // Print shell name
    shell_commands_exit(); // Call exit function to clean up and exit
    return 0;
}