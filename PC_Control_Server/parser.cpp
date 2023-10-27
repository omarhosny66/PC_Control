#include "parser.hpp"
#include <cstring>
#include <sstream>
#include <vector>

Parser_::Parser_() {}

std::vector<std::string> Parser_::parse_(std::string str1, std::string str2) {
  // Method return vector
  std::vector<std::string> vec_str;

  // Split the string around spaces
  std::stringstream str_stream(str1);

  // For storing each word in the str_stream
  std::string word;

  // Traverse through all words checking if words in str1 found in str2
  while (str_stream >> word) {
    bool isFound =
        str2.find(word.c_str(), 0, strlen(word.c_str())) != std::string::npos;

    // In case of similarity found store the word in the return vector string
    if (isFound) {
      std::cout << word << std::endl;
      vec_str.push_back(word);
    } 
  }

  return vec_str;
}

std::vector<std::string> Parser_::parse_(char* arr1, char* arr2) {
  // Method return vector
  std::vector<std::string> vec_str;

  // Converting the input arguments from char array to string
  std::string str1(arr1);
  std::string str2(arr2);

  // Split the string around spaces
  std::stringstream str_stream(str1);

  // For storing each word in the str_stream
  std::string word;

  // Traverse through all words checking if words in str1 found in str2
  while (str_stream >> word) {
    bool isFound =
        str2.find(word.c_str(), 0, strlen(word.c_str())) != std::string::npos;

    // In case of similarity found store the word in the return vector string
    if (isFound) {
      std::cout << word << std::endl;
      vec_str.push_back(word);
    } 
  }

  return vec_str;
}

Parser_::~Parser_() {}