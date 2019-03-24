#include "Settings.h"
#include <fstream>


Settings::Settings(std::string fileName) : fileName_(fileName)
{

}


Settings::~Settings()
{
}

int Settings::init()
{
  readFile(fileName_, inputFileLines_);
  parseFile(inputFileLines_, inputStrings_, "=");

  return 0;
}

std::string Settings::getValue(std::string key)
{
  return inputStrings_[key];
}


int Settings::readFile(const std::string &fileName, std::vector<std::string> &inputFileLines) const
{
  std::ifstream inputFile(fileName);
  if (!inputFile) {
    return 1; //error reading file
  }

  std::string tempLine;
  while (std::getline(inputFile, tempLine)) {
    inputFileLines.push_back(tempLine);
  }

  return 0;
}

int Settings::parseFile(const std::vector<std::string> &inputFileLines, std::map<std::string, std::string> &inputStrings, const std::string &delimiter) const
{
  std::string key, value;
  for (auto parseString : inputFileLines) {
    
    int position = parseString.find(delimiter);
    key = parseString.substr(0, position);
    value = parseString.substr(position + 1, std::string::npos);
    inputStrings[key] = value;
  }

  return 0;
}


