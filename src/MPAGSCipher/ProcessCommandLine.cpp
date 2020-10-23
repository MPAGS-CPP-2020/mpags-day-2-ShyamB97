#include <iostream>
#include <string>
#include <vector>

bool processComandLine(const std::vector<std::string>& args,
                       bool& helpRequested,
                       bool& versionRequested,
                       std::string& inputFileName,
                       std::string& outputFileName,
                       bool& encrypt,
                       size_t& key)
{
  // Add a typedef that assigns another name for the given type for clarity
  typedef std::vector<std::string>::size_type size_type;
  const size_type nCmdLineArgs {args.size()};

  // Process command line arguments - ignore zeroth element, as we know this to
  // be the program name and don't need to worry about it
  for (size_type i {1}; i < nCmdLineArgs; ++i) {

    if (args[i] == "-h" || args[i] == "--help") {
      helpRequested = true;
    }
    else if (args[i] == "--version") {
      versionRequested = true;
    }
    else if (args[i] == "-i") {
      // Handle input file option
      // Next element is filename unless -i is the last argument
      if (i == nCmdLineArgs-1) {
	      std::cerr << "[error] -i requires a filename argument" << std::endl;
	      // exit main with non-zero return to indicate failure
	      return false;
      }
      else {
	      // Got filename, so assign value and advance past it
	      inputFileName = args[i+1];
	      ++i;
      }
    }
    else if (args[i] == "-o") {
      // Handle output file option
      // Next element is filename unless -o is the last argument
      if (i == nCmdLineArgs-1) {
	      std::cerr << "[error] -o requires a filename argument" << std::endl;
	      // exit main with non-zero return to indicate failure
	      return false;
      }
      else {
	      // Got filename, so assign value and advance past it
	      outputFileName = args[i+1];
	      ++i;
      }
    }
    else if (args[i] == "-a") {
        if(i == nCmdLineArgs-1) {
            std::cerr << "[error] -a requires an action arguement, either <encrypt> or <decrypt>" << std::endl;
            return false;
        }
        else {
            if(args[i+1] == "encrypt") {
                encrypt = true;
            }
            else if(args[i+1] == "decrypt") {
                encrypt = false;
            }
            else {
                std::cout << "[Warning] no valid action was specified, defaulting to encryption" << std::endl;
                encrypt = true;
            }
            ++i;
        }
        
    }
    else if(args[i] == "-k"){
        if(i == nCmdLineArgs-1) {
            std::cerr << "[error] -k requires a key input which must be an integer" << std::endl;
            return false;
        }
        else {
            key = std::stoul(args[i+1]); // convert string to size_t
            ++i;
        }
        
    }
    else {
      // Have an unknown flag to output error message and return non-zero
      // exit status to indicate failure
      std::cerr << "[error] unknown argument '" << args[i] << "'\n";
      return false;
    }
  }
  return true;
}