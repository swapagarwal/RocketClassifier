#ifndef TRAINER_H
#define TRAINER_H
#include <map>
#include <string>

class Trainer
{
  public:
    Trainer();
  protected:
  private:
    std::map<std::string, int> spam_words, ham_words;
};

#endif // TRAINER_H
