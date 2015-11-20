#include <iostream>
#include <string>
#include "Bayes.h"
#include "../stem/stemming/english_stem.h"

using namespace std;

int main() {
  Bayes b;
  b.test("./train/non_spam/training");
  return 0;
}
