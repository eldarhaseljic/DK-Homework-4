%{
#include "token.hpp"
%}

ws            [ \t\n]
letter        [a-zA-Z]
digit         [0-9]
number        {digit}+
identifier    {letter}({letter}|{digit})*

%%

{ws}
"{"                           { return OPENBRACES; } 
"}"                           { return CLOSEDBRACES; } 
","                           { return COMMA; } 
":"                           { return COLON; } 
{number}                      { return NUMBER; } 
"["                           { return OPENBRACKET; }
"]"                           { return CLOSEDBRACKET; }
"null"                        { return NULLABLE; }
"true"                        { return TRUE; }
"false"                       { return FALSE;}
{identifier}                  { return STRING; } 

%%

/*
int main(void){
  int tok;
  while(tok = yylex() ){
    Token t(tok, yytext);
    t.print();
  }  
  return 0;
}
*/

int yywrap(){
  return 1;
}

