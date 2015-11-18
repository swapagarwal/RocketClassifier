#include <iostream>
#include <string>
#include "Bayes.h"

using namespace std;

int main() {
  Bayes b;
  b.test("./train/spam/test");
  return 0;
}
