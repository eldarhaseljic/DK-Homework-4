#ifndef _PARSER_HPP
#define _PARSER_HPP value

#include <vector>
#include <stack>
#include "token.hpp"

struct Parser{
  
  std::vector<Token> tokens;
  int currentIndex = 0;
  int bufferLength = 0;
  std::vector< std::vector < std::vector < char > > > grammar = 
  { 
    { {}, {'T','e'}, {}, {'T','e'}, {} , {'T','e'}, {'T','e'} , {}}, 
    
    { {'+', 'T', 'e'}, { '-','T','e'}, {}, {}, {'x'} , {}, {} , {'x'}}, 
    
    { {}, {'F','t'}, {}, {'F','t'}, {} , {'F','t'}, {'F','t'} , {}}, 
    
    { {'x'}, {'x'}, { '*', 'F', 't' }, {}, {'x'} , {}, {} , {'x'}}, 
    
    { {}, {'-','F'}, {}, {'I'}, {} , {'I'}, {'I'} , {}}, 
    
    { {}, {}, {}, {'(','E', ')'}, {} , {'B'}, {'W'} , {}}, 
  };

  Parser(std::vector<Token> const & t)
    : tokens(t), bufferLength(t.size()) {};
  
  int toNum(char);
  bool parse();
};

int  Parser::toNum(char c)
{
  switch(c)
  {
    case '$':
      return 8;
    case 'I':
      return 6;
    case 'F':
      return 5;
    case 't':
      return 4;
    case 'T':
      return 3;
    case 'e':
      return 2;
    case 'E':
      return 1;
    //terminali
    case 'B':
      return NUMBER;
    case 'W':
      return ID;
    case '(':
      return OPENING_BRACKET;
    case ')':
      return CLOSING_BRACKET;
    case '*':
      return MULTIPLY;
    case '+':
      return PLUS;
    case '-':
      return MINUS;
  }
  return 0;
}


bool Parser::parse()
{
  std::stack<char> Stack;
  Stack.push('$');
  Stack.push('E');
  do{
    char c = Stack.top();
    Stack.pop();
    switch(c)
    {
      //epsilon
      case 'x':
        break;

      //NETERMINALI
      case 'E':
      case 'e':
      case 'T':
      case 't':
      case 'F':
      case 'I':
      {
        
        int row = toNum(c);
        if(row == 0)  {  return false; }
        int col;
        
        if(currentIndex == tokens.size())
        {
          col = toNum('$') - 1;
        }
        else
        { 
          col = tokens.at(currentIndex).tag-1;
        }

        if(grammar.at(row-1).at(col).empty())
        {
          return false;
        }
        else
        {
          for(auto i = grammar.at(row-1).at(col).size(); i>0; --i)
            {
              Stack.push(grammar.at(row-1).at(col).at(i-1));
            }
        }
        break;
      }

      //TERMINALI
      case '+':
      case '-':
      case '*':
      case '(':
      case ')':
      case 'W':
      case 'B':
      {
        if (toNum(c) == tokens.at(currentIndex).tag)
        { 
          ++currentIndex;
        }
      break;
      }
      case '$':
      { 
        if(currentIndex == tokens.size())
          return true;
        return false;
      }
    }
  }
  while(!Stack.empty());

  if(Stack.empty() && (currentIndex == tokens.size()))
    return true;
  return false;
}

#endif /* ifndef _PARSER_HPP */
