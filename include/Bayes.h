#ifndef BAYES_H
#define BAYES_H
#include <boost/filesystem.hpp>
#include <map>
#include <string>
#include <vector>

class Bayes
{
  public:
    Bayes();
    void train();
    void test(std::string);
    bool query(std::vector<std::string>&);
    void print(std::string, bool);
    void saveTrain();
    bool readTrain();
    // double prob_word(string word, std::map<std::string, int> cat_words);
  protected:
  private:
    std::map<std::string, int> spam_words, ham_words;
    int spam_count, ham_count;
    int query_spam, query_ham;
};

#endif // BAYES_H
