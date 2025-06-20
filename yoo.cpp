#include<iostream>
#include <cstdlib>
#include<string>
#include<vector>
#include "config.h" // Assuming config.h contains necessary declarations
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
        cout << "Error: No valid commands available." << endl;
        return 0; // Return 0 for invalid input
    }
    int numcommands =  no_of_commands(); // Get the number of valid commands

    // Check if input is empty
    if(input.empty()) {
        cout << "Error: No input provided." << endl;
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
            cout << "Error: No command provided for sudo." << endl;
            return 0; // Return 0 for invalid sudo command
        }
        if(sudo_command == "cd") {
            if(tokens.size() < 3) {
                cout << "Error: No directory specified for sudo cd." << endl;
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
            cout << "Error: No directory specified for cd." << endl;
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

    cout << "Error: Invalid command '" << command << "'." << endl;
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
        cout << "Command execution failed or returned "
                "non-zero: "
             << returnCode << endl;
    }
    return result; // Return the result of command execution
}
void yoo_loop() {
    while(true) {
        cout <<  shell_print(); // Print the shell prompt
        cout.flush(); // Ensure the prompt is displayed immediately

        string input = handle_input();
        int chack = validate_input(input);
        if(chack == 0) {
            continue; // Skip to the next iteration if input is invalid
        }
        string result = input_exicute(input);
        if(!result.empty()) {
            cout << result << endl; // Print the result of command execution
        }
        else {
            cout << "No output from command." << endl; // Handle case where no output is returned
        }
        
    }
}

int main(int argc, char **argv) {
    //pre shell setup
    cout << "Shell Name: " << shell_name() << endl; // Print shell name
    cout << pre_start_print() << endl; // Print welcome message

    // Start loop for input in shell
    yoo_loop();

    // Post shell cleanup
    cout << shell_end() << endl; // Print shell end message
    shell_commands_exit(); // Call exit function to clean up and exit
    return 0;
}