#ifndef READER_H
#define READER_H
#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
#include <map>
#include <boost/foreach.hpp>

using namespace boost::filesystem;
using std::cout;

class Reader {
public:
  Reader(std::string);
  void ReadDir(std::string);
  std::vector<std::string> ReadFile(std::string);
  std::map<std::string, int> GetWordCount() {
    return word_count;
  }
protected:
private:
  std::vector<std::string> words_dump;
  std::map<std::string, int> word_count;
};

#endif // READER_H
