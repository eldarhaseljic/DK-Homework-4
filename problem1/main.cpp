#include <iostream>
#include <vector>

#include "lex.yy.c"
#include "parser.h"
#include "token.hpp"

using namespace std;

int main(void) {
  vector<Token> tokens;
  int yytoken;
  while (yytoken = yylex()) {
    tokens.push_back(Token(yytoken, yytext));
  }

  /*
  for (const auto& token : tokens) {
    token.print();
  }
  */

  // TODO uncomment this
  Parser p(tokens);
  if (p.parse())
     cout << "Uneseni string je ispravan." << endl;
  else
     cout << "Uneseni string nije ispravan." << endl;
  return 0;
}
