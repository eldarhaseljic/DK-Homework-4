#ifndef _TOKEN_HPP_
#define _TOKEN_HPP_

#include <iostream>
#include <string>

const int ID = 7;
const int OPENING_BRACKET = 4;
const int CLOSING_BRACKET = 5;
const int MULTIPLY = 3;
const int PLUS = 1;
const int MINUS = 2;
const int NUMBER = 6;

struct Token {
  int tag = 0;
  std::string lexeme;

  Token() = default;
  Token(int i, std::string const& s) : tag(i), lexeme(s) {}

  Token& operator= (Token const& t) {
    tag = t.tag;
    lexeme = t.lexeme;
    return *this;
  }

  bool operator!() { return tag != 0; }

  explicit operator bool() { return tag; }

  void print() const {
    std::cout << "<" << tag << ", " << lexeme << ">" << std::endl;
  }
};

#endif  // _TOKEN_HPP_
