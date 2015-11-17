#include "Reader.h"

Reader::Reader(std::string in_dir) {
  path pth(in_dir);
  try {
    if (exists(pth) && is_directory(pth)) {
      boost::filesystem::directory_iterator it( pth ), eod;
      BOOST_FOREACH( boost::filesystem::path const & p, std::make_pair( it, eod ) ) {
        cout << p.string() << std::endl;
      }
    } else {
      cout << pth << " does not exist\n";
    }
  } catch (const filesystem_error& ex) {
    cout << ex.what() << '\n';
  }
}
