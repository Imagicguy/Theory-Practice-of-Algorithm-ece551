#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void readStn() {
  vector<string> lines;
  string temp;
  while (getline(cin, temp)) {
    lines.push_back(temp + "\n");  //string or char
  }
  sort(lines.begin(), lines.end());
  for (vector<string>::iterator it = lines.begin(); it < lines.end(); ++it) {
    cout << *it;
  }
}

void readFile(ifstream & streamIn) {
  vector<string> lines;
  string temp;
  while (getline(streamIn, temp)) {
    lines.push_back(temp + "\n");
  }
  sort(lines.begin(), lines.end());
  for (vector<string>::iterator it = lines.begin(); it < lines.end(); ++it) {
    cout << *it;
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    readStn();
  }
  else {
    for (int i = 1; i < argc; i++) {
      ifstream streamIn(argv[i]);
      if (streamIn.is_open()) {
        readFile(streamIn);
        streamIn.close();
      }
      else {
        cerr << "failed to open file";
        exit(EXIT_FAILURE);
      }
    }
  }
  return EXIT_SUCCESS;
}
