#include "Trainer.h"
#include "Reader.h"

Trainer::Trainer()
{
  Reader spam_reader("./train"), ham_reader("./train");
  spam_words = spam_reader.GetWordCount();
  ham_words = ham_reader.GetWordCount();
}
