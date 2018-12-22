#include <ftw.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <sstream>
#include <streambuf>
#include <string>
#include <vector>

using namespace std;

const size_t table_size = 99971;
vector<list<string> > table(table_size);
void hashing(string objectName) {
  ifstream s(objectName);
  ostringstream str = ostringstream();
  str << s.rdbuf();

  hash<string> str_hash;             //use build-in hash function with type string
  size_t key = str_hash(str.str());  //calculate key

  table[key % table_size].push_front(objectName);
  //cout << key % table_size << endl;
}

static int nftwfunc(const char * objectName,
                    const struct stat * buffer,
                    int type,
                    struct FTW * ftw) {
  if (type != FTW_SL && type != FTW_D) {
    //cout << "file found\n";
    hashing(objectName);
  }
  return 0;
}

void fileSearch(const char * path) {
  int fd_limit = 5;
  int flags = FTW_PHYS;
  int ret;
  ret = nftw(path, nftwfunc, fd_limit, flags);
  if (ret == -1) {  //failed
    perror("failed when nftw\n");
    exit(EXIT_FAILURE);
  }
}
string reading(string file) {
  ifstream t(file);

  ostringstream ss = ostringstream();
  ss << t.rdbuf();
  return ss.str();
}

void checkSimilar(list<string> & listing) {
  size_t size = listing.size();
  for (size_t i = 0; i < size; i++) {
    string to_check = listing.front();
    //    size_t hash_check = hashing(reading(to_check));
    string hash_content = reading(to_check);

    listing.pop_front();

    for (list<string>::iterator it = listing.begin(); it != listing.end(); ++it) {
      //      if (hash_check == hashing(reading(*it)))
      if (hash_content == reading(*it)) {
        cout << "#Removing " << to_check << " (duplicate of " << *it << ").\n";
        cout << "rm " << to_check << endl;
        break;
      }
    }
  }
}

void check() {
  for (size_t i = 0; i < table_size; i++) {
    if (table[i].size() > 1) {  //means one key contains more than one files
      checkSimilar(table[i]);
    }
  }
}
int main(int argc, char ** argv) {
  if (argc <= 1) {
    cerr << "need at last one input!\n";
  }

  for (int i = 1; i < argc; i++) {
    fileSearch(argv[i]);
  }

  cout << "#!/bin/bash\n";
  check();

  return 0;
}
