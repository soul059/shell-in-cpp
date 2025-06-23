#include<iostream>
#include <cstdlib>
#include<vector>
#include<string>
#include <filesystem>
#include <fstream>
#define FMT_HEADER_ONLY
#include "fmt/color.h"
#include "fmt/format.h"
#include "config.h"
#include "json.hpp"
using namespace  std;

#ifdef _WIN64
    #include <direct.h>
    #define getcwd _getcwd
#else
    #include <unistd.h>
    #define getcwd getcwd
#endif

std::string name;
std::string initial_print;
std::string end_print;

std::string default_color_v;
std::string error_color_v;
std::string success_color_v;
std::string info_color_v;
std::string end_color_v;
std::string print_color_v;
std::string warning_color_v;

#ifdef _WIN64
    std::vector<std::string> commands;
    std::vector<std::string> apps;
#elif __WIN32__
    std::vector<std::string> commands;
    std::vector<std::string> apps;
#elif __APPLE__
    std::vector<std::string> commands;
    std::vector<std::string> apps;
#elif __linux__
    std::vector<std::string> commands;
    std::vector<std::string> apps;
#elif __unix__
    std::vector<std::string> commands;
    std::vector<std::string> apps;
#else    
    std::vector<std::string> commands;
    std::vector<std::string> apps;
#endif



void set_configuration() {
    std::ifstream config_file("config.json");
    if (!config_file.is_open()) {
        std::cerr << "Error: Could not open config file." << std::endl;
        return;
    }
    try
    {
        // Parse JSON from the file
        nlohmann::json json_data;
        config_file >> json_data;
        
        // Helper function to convert JSON array to vector
        auto parseJsonArrayToVector = [](const nlohmann::json& j) -> std::vector<std::string> {
            std::vector<std::string> result;
            if (j.is_array()) {
            for (const auto& item : j) {
                if (item.is_string()) {
                result.push_back(item.get<std::string>());
                } else {
                result.push_back(item.dump());
                }
            }
            }
            return result;
        };

        // Helper function to convert JSON value to string
        auto parseJsonToString = [](const nlohmann::json& j) -> std::string {
            if (j.is_string()) {
            return j.get<std::string>();
            } else {
            return j.dump();
            }
        };
        
        // Parse string values
        initial_print = parseJsonToString(json_data["shell"]["print"]["initial print"]);
        name = parseJsonToString(json_data["shell"]["print"]["name"]);
        end_print = parseJsonToString(json_data["shell"]["print"]["end print"]);
        default_color_v = parseJsonToString(json_data["shell"]["color"]["default"]);
        error_color_v = parseJsonToString(json_data["shell"]["color"]["error"]);
        success_color_v = parseJsonToString(json_data["shell"]["color"]["success"]);
        info_color_v = parseJsonToString(json_data["shell"]["color"]["info"]);
        end_color_v = parseJsonToString(json_data["shell"]["color"]["end"]);
        print_color_v = parseJsonToString(json_data["shell"]["color"]["print"]);
        warning_color_v = parseJsonToString(json_data["shell"]["color"]["warning"]);
        // Parse array values for commands and apps based on platform
        #ifdef _WIN64
            commands = parseJsonArrayToVector(json_data["shell"]["commands"]["win64"]["terminal"]);
            apps = parseJsonArrayToVector(json_data["shell"]["commands"]["win64"]["apps"]);
        #elif __WIN32__
            commands = parseJsonArrayToVector(json_data["shell"]["commands"]["win32"]["terminal"]);
            apps = parseJsonArrayToVector(json_data["shell"]["commands"]["win32"]["apps"]);
        #elif __APPLE__
            commands = parseJsonArrayToVector(json_data["shell"]["commands"]["macos"]["terminal"]);
            apps = parseJsonArrayToVector(json_data["shell"]["commands"]["macos"]["apps"]);
        #elif __linux__
            commands = parseJsonArrayToVector(json_data["shell"]["commands"]["linux"]["terminal"]);
            apps = parseJsonArrayToVector(json_data["shell"]["commands"]["linux"]["apps"]);
        #elif __unix__
            commands = parseJsonArrayToVector(json_data["shell"]["commands"]["unix"]["terminal"]);
            apps = parseJsonArrayToVector(json_data["shell"]["commands"]["unix"]["apps"]);
        #else    
            commands = parseJsonArrayToVector(json_data["shell"]["commands"]["other"]["terminal"]);
            apps = parseJsonArrayToVector(json_data["shell"]["commands"]["other"]["apps"]);
        #endif

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

string pre_start_print() {
    return initial_print;
}
string shell_name() {
    return  name;
}
string shell_print() {
    string result =name + " ";
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
    vector<string> comm = commands; // Start with terminal commands 
    comm.insert(comm.end(), apps.begin(), apps.end());

    return comm;
}
int no_of_commands() {
    return shell_commands().size();
}
void shell_commands_help() {
    string help_text = "Available commands:\n";
    cout << "Commands" << endl;
    cout << "--------" << endl;
    for(const auto& command : shell_commands()) {
        cout << "\t" << command << endl; // Print each command
    }
    cout << "apps" << endl;
    cout << "--------" << endl;
    for (const auto& app : apps) {
        cout << "\t" << app << endl; // Print each app
    }
}


string shell_end() {
    return "Exiting Yoo Shell.";
}

void shell_commands_exit() {
    fmt::print(fmt::fg(hex_to_rgb_my(shell_end_color())), end_print);
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
    return end_color_v; // Reset color
}
string error_color() {
    return error_color_v; // Red color for errors
}
string succes_color() {
    return success_color_v; // Green color for success
}
string warning_color() {
    return warning_color_v; // Yellow color for warnings
}
string shell_print_color() {
    return print_color_v; // Cyan color for shell prompt
}
string pre_start_print_color() {
    return info_color_v; // Green color for welcome message
}
// string shell_color_reset() {
//     return default_color_v; // Reset color
// }

