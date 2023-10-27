#include "command.hpp"
#include <cstring>
#include <sched.h>
#include <sstream>
#include <unistd.h>
#include <vector>

Command_::Command_(std::string str) {
  std::vector<int>::size_type numCommands;

  numCommands = check(str);

  if (numCommands) {
    execute(numCommands);
  }
  
}

Command_::Command_(char* arr) {
  std::vector<int>::size_type numCommands;

  // Converting the input argument from char array to string
  std::string str(arr);

  numCommands = check(str);

  if (numCommands) {
    execute(numCommands);
  }
}

std::vector<int>::size_type Command_::check(std::string str) {
  std::vector<std::string> commands;

  commands = Parser_::parse_(Command_::commands_string, str);

  if(commands.size()) {this->commands_vec = commands;}

  return commands.size();
}

void Command_::execute(int numCommands) {
  pid_t pid;

  for (unsigned int i=0; i<numCommands; i++) {
    if ((pid = fork()) == -1) {
      // Failed to fork
      std::cout << "Failed to fork for system command process" <<std::endl;
    } else if (pid == 0) {
      // New child process for client handling
      // Command execution using system function
      system(this->commands_map[this->commands_vec[i]].c_str());
    }
  }
}

Command_::~Command_() {}
