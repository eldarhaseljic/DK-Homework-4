%{
#include "token.hpp"
%}

ws          [ \t\n]
letter      [a-zA-Z]
digit       [0-9]
number      {digit}+
identifier  {letter}({letter}|{digit})*

%%

{ws}          ;
{identifier}  { return ID; }
"("           { return OPENING_BRACKET; }
")"           { return CLOSING_BRACKET; }
"*"           { return MULTIPLY; }
"+"           { return PLUS; }
"-"           { return MINUS; }
{number}      { return NUMBER; }

%%

/*
int main(void)
{
  int tok;
  while(tok = yylex() )
  {
    Token t(tok, yytext);
    t.print();
  }  
  return 0;
}
*/

int yywrap(){
  return 1;
}
