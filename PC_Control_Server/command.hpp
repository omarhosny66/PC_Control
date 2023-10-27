#ifndef COMMAND_
#define COMMAND_

#include <iostream>
#include "parser.hpp"
#include <map>
#include <string>
#include <vector>

class Command_ {
private:
public:
  std::string commands_string = "terminal calculator firefox";
  std::vector<std::string> commands_vec;
  std::map<std::string, std::string> commands_map{
      {"terminal", "gnome-terminal"},
      {"calculator", "gnome-calculator"},
      {"firefox", "firefox"}};

  Command_(std::string str);
  Command_(char* arr);
  std::vector<int>::size_type check(std::string str);
  void execute(int numCommands);
  ~Command_();
};

#endif // COMMAND_