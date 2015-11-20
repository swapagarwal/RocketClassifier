#include "Bayes.h"
#include "Reader.h"
#define DEBUG if(1)

const std::string spam_path = "./train/spam/test";
const std::string ham_path = "./train/non_spam/test";
const std::string store_path = "./saved_file.txt";

Bayes::Bayes()
{
  if(!readTrain()) {
    train();
    saveTrain();
  }
}

void Bayes::train() {
  DEBUG std::cerr << "Training spam\n";
  Reader spam_reader(spam_path);
  spam_words = spam_reader.GetWordCount();
  spam_count = spam_reader.GetFileCount();
  DEBUG std::cerr << "Training non-spam\n";
  Reader ham_reader(ham_path);
  ham_words = ham_reader.GetWordCount();
  ham_count = ham_reader.GetFileCount();
  DEBUG std::cerr << "Trained with " << spam_count << " spam with "<< spam_words.size() << " words and " << ham_count << " non-spam documents with " << ham_words.size() << " words.\n";
}

void Bayes::saveTrain() {
  using std::endl;
  std::ofstream fout(store_path);
  fout << spam_count << ' ' << ham_count << endl;
  fout << spam_words.size() << endl;
  for (auto& p : spam_words) {
    fout << p.first << endl;
    fout << p.second << endl;
  }
  fout << ham_words.size() << endl;
  for (auto& p : ham_words) {
    fout << p.first << endl;
    fout << p.second << endl;
  }
}

bool Bayes::readTrain() {
  std::ifstream fin(store_path);
  if (!fin) {
    DEBUG std::cerr << "No saved training data found.\n";
    return 0;
  }
  fin >> spam_count >> ham_count;
  int sz;
  std::pair<std::string, int> p;
  fin >> sz;
  std::string temp;
  getline(fin, temp);
  for (int i = 0; i < sz; i++) {
    std::getline(fin, p.first);
    std::getline(fin, temp);
    p.second = std::stoi(temp);
    spam_words.insert(p);
  }
  fin >> sz;
  getline(fin, temp);
  for (int i = 0; i < sz; i++) {
    std::getline(fin, p.first);
    std::getline(fin, temp);
    p.second = std::stoi(temp);
    ham_words.insert(p);
  }
  DEBUG std::cerr << "Trained with " << spam_count << " spam with "<< spam_words.size() << " words and " << ham_count << " non-spam documents with " << ham_words.size() << " words.\n";
  return true;
}

void Bayes::test(std::string dir) {
  query_spam = 0;
  query_ham = 0;
  path pth(dir);
  try {
    if (exists(pth) && is_directory(pth)) {
      boost::filesystem::directory_iterator it(pth), eod;
      int file_count = 0, tot = std::distance(directory_iterator(pth), directory_iterator()), op = -1;
      BOOST_FOREACH( boost::filesystem::path const & p, std::make_pair( it, eod ) ) {
        auto words = Reader::ReadFile(p.string());
        file_count++;
        int per = (file_count * 100) / tot;
        if (op != per) {
          std::cerr << "\r" << per << "% completed.";
          op = per;
        }
        print(p.string(), query(words));
      }
      std::cerr << std::endl;
    } else {
      cout << pth << " does not exist\n";
    }
  } catch (const filesystem_error& ex) {
    cout << ex.what() << '\n';
  }
  cout << "query completed with " << query_spam << " spam and " << query_ham << " non-spam documents.\n";
}

bool Bayes::query(std::vector<std::string>& words) {
  double pspam = 0, pham;
  pham = 0;
  for (auto& word : words) {
    int scount = spam_words[word];
    int hcount = ham_words[word];
    int total = scount + hcount;
    if (scount) {
      pspam += log(static_cast<double> (scount) / total);
    }
    if (hcount) {
      pham += log(static_cast<double> (hcount) / total);
    }
  }
  return pspam > pham;
}

void Bayes::print(std::string file, bool spam) {
  //std:: cout << file << '\t';
  if (spam) {
    // std::cout << "spam\n";
    query_spam++;
  } else {
    // std::cout << "not spam\n";
    query_ham++;
  }
}
