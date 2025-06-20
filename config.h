#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>

std::string pre_start_print();
std::string shell_name();
std::string shell_print();
std::vector<std::string> shell_commands();
int no_of_commands();
void shell_commands_help();
void shell_commands_exit();
std::string shell_end();

void commands_cd(std::string);

#endif
