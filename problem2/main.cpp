#include "lex.yy.c"
#include "parser.hpp"

int main(void) {
  std::vector<Token> tokens;
  int yytoken;
  while ((yytoken = yylex()) != 0) {
    tokens.push_back(Token(yytoken, yytext));
  }
 /* 
  for (const auto& token : tokens) {
    token.print();
  }
  */

  Parser predictive(tokens);
  if(predictive.parse())
    std::cout << "Uneseni string je ispravan" << std::endl;
  else
    std::cout << "Uneseni string nije ispravan" << std::endl;
  return 0;
}
