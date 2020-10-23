#include <string>

/*Will encrypt/decrypt an input file by character by
shifting the letter k to the right of the alphabet*/
std::string runCaesarCipher(const std::string& in_string, const size_t key, const bool encrypt)
{
  int sgn{1};
  if(encrypt == false)
  {
    sgn = -1;
  }
  const std::string alphabet{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
  std::string out_string {""};
  for(size_t i = 0; i < in_string.size(); i++)
  {
    int iter = alphabet.find(in_string[i]); // gets element index of the character in the string
    out_string += alphabet[(iter+sgn*key) % 26];  // modulo addition to wrap around alphabet
  }
  return out_string;
}