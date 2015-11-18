#include "Reader.h"
#include "Parser.h"

Reader::Reader(std::string in_dir) {
  file_count = 0;
  ReadDir(in_dir);
  for (string& word : words_dump) {
    word_count[word]++;
  }
}

void Reader::ReadDir(std::string in_dir) {
  auto& out = this->words_dump;
  path pth(in_dir);
  try {
    if (exists(pth) && is_directory(pth)) {
      boost::filesystem::directory_iterator it( pth ), eod;
      BOOST_FOREACH( boost::filesystem::path const & p, std::make_pair( it, eod ) ) {
        auto words = ReadFile(p.string());
        file_count++;
        out.insert(std::end(out), std::begin(words), std::end(words));
      }
    } else {
      cout << pth << " does not exist\n";
    }
  } catch (const filesystem_error& ex) {
    cout << ex.what() << '\n';
  }
}

vector<string> Reader::ReadFile(std::string filename) {
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  std::string contents;
  in.seekg(0, std::ios::end);
  contents.resize(in.tellg());
  in.seekg(0, std::ios::beg);
  in.read(&contents[0], contents.size());
  in.close();
  Parser p(contents);
  return p.Getparsed_out();
}
