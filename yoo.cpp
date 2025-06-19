#include<iostream>
#include <cstdlib>
#include<string>
#include<vector>
using namespace  std;

void command_help(string validcom[], int numcom) {
    for(int i=0;i<numcom;i++) {
        cout << validcom[i] << endl; // Print each valid command
    }
}

void command_exit() {
    cout << "Exiting the shell." << endl;
    exit(0); // Exit the program
}

string handle_input() {
    string validcommands[] = {"help", "exit", "list", "add", "remove"};
    int numcommands = sizeof(validcommands) / sizeof(validcommands[0]);

    string input;
    getline(cin, input); // Read a line of input from the user
    if(input.empty()) {
        return ""; // Return empty string if no input
    }
    return input; // Return the input string
}

int validate_input(const string &input) {
    string validcommands[] = {"help", "exit", "ls", "pwd", "cd", "mkdir", "rmdir", "touch", "rm", "cat", "echo"};
    int numcommands = sizeof(validcommands) / sizeof(validcommands[0]);

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
    if(tokens[0] == "exit") command_exit(); // Handle exit command
    if(tokens[0] == "help") {
        command_help(validcommands, numcommands);
        return 0; // Return 0 for help command
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
        cout << "yoo> ";

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
    cout << "Welcome to the yoo shell!" << endl;
    cout << "Type 'help' for a list of commands." << endl;
    cout << "Type 'exit' to leave the shell." << endl;

    // Start loop for input in shell
    yoo_loop();

    // Post shell cleanup
    cout << "Exiting yoo shell." << endl;
    return 0;
}