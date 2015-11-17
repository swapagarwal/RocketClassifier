#include <iostream>
#include <string>
#include "Parser.h"
#include "Reader.h"

using namespace std;

int main() {
  Reader r("./train");
  auto x = r.GetWordCount();
  return 0;
}
