#ifndef MPAGSCIPHER_TRANSFORMCHAR_HPP
#define MPAGSCIPHER_TRANSFORMCHAR_HPP

#include <string>
#include <vector>

bool processComandLine(const std::vector<std::string>& args,
                       bool& helpRequested,
                       bool& versionRequested,
                       std::string& inputFileName,
                       std::string& outputFileName);

#endif