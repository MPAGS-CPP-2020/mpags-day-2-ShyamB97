// Standard Library includes
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// include out project headers (functions)
#include "TransformChar.hpp"
#include "ProcessCommandLine.hpp"
#include "RunCaesarCipher.hpp"

bool processComandLine(const std::vector<std::string>& args,
                       bool& helpRequested,
                       bool& versionRequested,
                       std::string& inputFileName,
                       std::string& outputFileName,
                       bool& encrypt,
                       size_t& key);

std::string transformChar(const char in_char);

std::string runCaesarCipher(const std::string& in_string, const size_t key, const bool encrypt);

// Main function of the mpags-cipher program
int main(int argc, char* argv[])
{
  // Convert the command-line arguments into a more easily usable form
  const std::vector<std::string> cmdLineArgs {argv, argv+argc};

  // Options that might be set by the command-line arguments
  bool helpRequested {false};
  bool versionRequested {false};
  std::string inputFile {""};
  std::string outputFile {""};
  bool encrypt{true};
  size_t key{5};

  // Parse command lines, if something went wrong we want to exit the code (returns false)
  bool parseSucess {processComandLine(cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile, encrypt, key)};
  if(!parseSucess)
  {
    std::cout << "Something went wrong... exiting" << std::endl;
    return 1;
  }

  // Handle help, if requested
  if (helpRequested) {
    // Line splitting for readability
    std::cout
      << "Usage: mpags-cipher [-i <file>] [-o <file>]\n\n"
      << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
      << "Available options:\n\n"
      << "  -h|--help        Print this help message and exit\n\n"
      << "  --version        Print version information\n\n"
      << "  -i FILE          Read text to be processed from FILE\n"
      << "                   Stdin will be used if not supplied\n\n"
      << "  -o FILE          Write processed text to FILE\n"
      << "                   Stdout will be used if not supplied\n\n"
      << "  -a string        action to do, either 'encrypt' or 'decrypt'\n\n"
      << "  -k size_t        cipher key used to encrypt/decrypt file, default is 5\n\n";
    // Help requires no further action, so return from main
    // with 0 used to indicate success
    //return true;
    return 0;
  }

  // Handle version, if requested
  // Like help, requires no further action,
  // so return from main with zero to indicate success
  if (versionRequested) {
    std::cout << "0.1.0" << std::endl;
    //return true;
    return 0;
  }

  // Initialise variables for processing input text
  char inputChar {'x'};
  std::string inputString {""};
  std::string inputText {""};
  std::string outputText {""};
  std::vector<std::string> outputLines {};

  // Read in user input from stdin/file
  if (!inputFile.empty()) {
    std::ifstream in_file {inputFile};
    if(in_file.good())
    {
      /*read the files contents character by character and then converts the text,
      line by line. Will not read white spaces */
      while(getline(in_file, inputString))
      {
        for(size_t i = 0; i < inputString.length(); i++)
        {
          inputChar = inputString[i];
          inputText += transformChar(inputChar);
        }
        outputText = runCaesarCipher(inputText, key, encrypt);
        outputLines.push_back(outputText);
        inputText = ""; // need to clear the inputText
      }
      in_file.close();
    }
    else
    {
      std::cout << "[error] couldn't open file... exiting" << std::endl;
      return 1;
    }
  }
  else
  {
    // Loop over each character from user input
    // (until Return then CTRL-D (EOF) pressed)
    while(std::cin >> inputChar)
    {
      inputText += transformChar(inputChar);
    }
    outputText = runCaesarCipher(inputText, key, encrypt);
  }

  // Output the transliterated text
  if (!outputFile.empty()) {
    std::ofstream out_file {outputFile};
    if(out_file.good())
    {
      for(size_t j = 0; j < outputLines.size(); j++)
      {
        out_file << outputLines[j] << std::endl;
      }
    }
    else
    {
      std::cout << "[error] couldn't open file... exiting" << std::endl;
      return 1;
    }
    
  }
  else {
    std::cout << outputText << std::endl;
  }

  

  // No requirement to return from main, but we do so for clarity
  // and for consistency with other functions
  return 0;
}