#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
using std::cout;
using std::cin;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include <set>
using std::set;

#include <string>
using std::string;

#include <algorithm>
using std::find;
using std::distance;

class Graph
{
  private:
    map<char, vector<char>> adjacency_list;
    vector<vector<bool>> matrix;
    vector<int> degrees;
    vector<char> euler;
    string type;
    int total_degrees = 0;
    bool symmetric;
    bool related;
    bool eulerian;

    bool is_symmetric();
    bool is_eulerian();
    void make_matrix();
    void make_matrix(int);
    void circuit_euler();
    void road_euler(int []);
    void do_euler(map<char, vector<char>>, int, char, char);

  public:
    Graph(map<char, vector<char>>);
    Graph();
    ~Graph();
    void show_graph();
    void show_matrix();
    void show_road(vector<char>);
};

#endif // GRAPH_H
