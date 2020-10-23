/*ifndef will basically make sure that the header is only included once
  by checking the flag specified by #define. Headers should never be called more than once.
*/
#ifndef MPAGSCIPHER_TRANSFORMCHAR_HPP
#define MPAGSCIPHER_TRANSFORMCHAR_HPP

#include <string>

std::string transformChar(const char in);

#endif