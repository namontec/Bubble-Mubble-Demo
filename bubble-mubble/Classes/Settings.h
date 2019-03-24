#pragma once

#include <map>
#include <vector>
#include <string>


class Settings
{
public:
  Settings(std::string fileName);
  virtual ~Settings();

  int         init();
  std::string getValue(std::string key);

private:
  int         readFile(const std::string        &fileName, 
                       std::vector<std::string> &inputFileLines) const;

  int         parseFile(const std::vector<std::string>     &inputFileLines,
                        std::map<std::string, std::string> &inputStrings, 
                        const std::string                  &delimiter) const;

  std::string fileName_;
  std::vector<std::string> inputFileLines_;
  std::map<std::string, std::string> inputStrings_;
  
};

