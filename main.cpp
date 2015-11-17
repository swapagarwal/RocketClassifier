#include <iostream>
#include <string>
#include "Parser.h"
#include "Reader.h"

using namespace std;

int main() {

  Parser p("<html><!--This is a comment. Comments are not displayed in the browser--><body><h1>Hello World! R\n It's World's plan.\n Documenting the documentation for the documented world.</h1></body></html>");
  Reader r(".");
  return 0;
}
