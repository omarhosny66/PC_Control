#ifndef PARSER_
#define PARSER_

#include <iostream>
#include <string>
#include <vector>

class Parser_ {
private:
public:
  Parser_();
  static std::vector<std::string> parse_(std::string str1, std::string str2);
  static std::vector<std::string> parse_(char* arr1, char* arr2);  
  ~Parser_();
};

#endif // PARSER_