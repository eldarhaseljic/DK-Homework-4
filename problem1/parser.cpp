#include "parser.h"

#include <iostream>
#include <string>
#include <vector>

#include "token.hpp"

using namespace std;
/*
 * Gramatika iz fajla rules.txt
 */

Parser::Parser(std::vector<Token> const& t)
    : tokens(t), bufferLength(t.size()) {}

// start of parsing
bool Parser::parse() {
  currentIndex = 0;

  bool retval = Start();

  if (currentIndex < bufferLength) retval = false;
  return retval;
}

// first production rule
// TODO this should match json object
bool Parser::Start() {
  cout << currentIndex << " start" << endl;
  // TODO match here
  //return false;
  return terminal(OPENBRACES) && pairs() && terminal(CLOSEDBRACES);
  // 
}

bool Parser::terminal(int t) {
  if (currentIndex >= bufferLength) return false;
  bool x = (t == tokens[currentIndex].tag);
  if (x == true) currentIndex++;
  return x;
}

bool Parser::pairs() {
  cout << currentIndex << " pairs" << endl;
  // TODO make recursive list parser here
  //return false;
  auto temp = currentIndex;
  return (pair() && pairs_tail()) || (currentIndex = temp, pair()) || epsilon();
  // NOTE: look at pairs_tail as well
}

bool Parser::pair() {
  cout << currentIndex << " pair" << endl;
  // TODO pair parser key : value
  //return false;
  return terminal(STRING) && terminal(COLON) && value();
  // 
}

bool Parser::epsilon() {
  cout << currentIndex << " epsilon" << endl;
  return true;
}

bool Parser::pairs_tail() {
  cout << currentIndex << " pairs tail" << endl;
  // TODO
  //return false;
  auto temp = currentIndex;
  return (terminal(COMMA) && pair() && pairs_tail()) || 
         (currentIndex = temp, terminal(COMMA) && pair());
  //
}

bool Parser::value() {
  cout << currentIndex << " value" << endl;
  // TODO add other values here
  return terminal(NUMBER) || terminal(STRING) || 
         terminal(TRUE)   || terminal(FALSE)  ||
         terminal(NULLABLE) || Start() || array();
}

bool Parser::array() {
  return terminal(OPENBRACKET) && elements() && terminal(CLOSEDBRACKET);
}

bool Parser::elements() 
{
  auto temp = currentIndex;
  return (value() && elements_tail()) || (currentIndex = temp, value()) || epsilon();
}

bool Parser::elements_tail() {
  auto temp = currentIndex;
  return (terminal(COMMA) && value() && elements_tail()) ||
         (currentIndex = temp, terminal(COMMA) && value());
}

