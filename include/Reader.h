#ifndef READER_H
#define READER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

class Reader
{
  private:
    string input;
    vector<map<char, vector<char>>> output;

  public:
    Reader();
    void run();
    vector<map<char, vector<char>>> get_input();
};

#endif // READER_H
