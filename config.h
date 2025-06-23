#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#define FMT_HEADER_ONLY
#include "fmt/color.h"
#include "fmt/format.h"

inline fmt::rgb hex_to_rgb_my(const std::string& hex) {
    if (hex.length() < 2) { // Prevent crash on empty or short strings
        return fmt::rgb(255, 255, 255); // Return white as default
    }
    unsigned int r, g, b;
    std::stringstream ss;
    ss << std::hex << hex.substr(1); // skip the '#'
    unsigned int hex_value;
    ss >> hex_value;
    r = (hex_value >> 16) & 0xFF;
    g = (hex_value >> 8) & 0xFF;
    b = hex_value & 0xFF;
    return fmt::rgb(r, g, b);
}

void set_configuration();

std::string pre_start_print_color();
std::string shell_print_color();
std::string shell_end_color();
std::string error_color();
std::string succes_color();
// std::string shell_color_reset();
std::string warning_color();


std::string pre_start_print();
std::string shell_name();
std::string shell_print();
std::string shell_end();

std::vector<std::string> shell_commands();
int no_of_commands();

void shell_commands_exit();
void shell_commands_help();
void shell_commands_history();
void commands_cd(std::string);

void set_history(std::string& command);
std::vector<std::string> get_history();

#endif
