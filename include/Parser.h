#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <boost/tokenizer.hpp>
#include <cctype>
#include "gumbo.h"
#include "../stem/stemming/english_stem.h"

using namespace std;

class Parser {
  public:
    void tokenize(string);
    Parser(string);
    string Getinput_str() {
      return input_str;
    }
    void Setinput_str(string val) {
      input_str = val;
    }
    vector<string> Getparsed_out() {
      return parsed_out;
    }
    std::string cleantext(GumboNode* node);
  protected:
  private:
    string input_str;
    vector<string> parsed_out;
};

#endif // PARSER_H
