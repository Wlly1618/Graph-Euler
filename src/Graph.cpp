#include "Graph.h"

Graph::Graph()
{
  cout << "Use the constructor to create the graph\n";
  cout << "Graph example({{'x', {'y', 'z'}}, {'y', {'x', 'z'}}, {'z', {'x', 'y'}}})\n";
}

Graph::Graph(map<char, vector<char>> input)
{
  adjacency_list = input;
  make_matrix();
  eulerian = is_eulerian();
}

void Graph::show_graph()
{
  int i = 0;
  for (const auto &node : adjacency_list)
  {
    cout << "Node: " << node.first << "\tDegree: " << degrees[i] << "\tEdges: ";
    for (const auto &edge : node.second)
    {
      cout << edge << " ";
    }
    cout << "\n";
    i++;
  }

  cout << "\n";

  cout << "Information graph\n\n";
  string msg_true = "true", msg_false = "false";

  if (symmetric)
    cout << "\tSymmetric: \t" << msg_true << "\n";
  else
    cout << "\tSymmetric: \t" << msg_false << "\n";

  if (related)
    cout << "\tRelated: \t" << msg_true << "\n";
  else
    cout << "\tRelated: \t" << msg_false << "\n";

  if (eulerian)
  {
    cout << "\tEulerian: \t" << msg_true << "\n\n\t";
    show_road(euler);
  }
  else
  {
    cout << "\tEulerian: \t" << msg_false << "\n";

    cout << "\nGraph No Eulerian\n";
  }
}

void Graph::show_road(const vector<char> road)
{
  for (const auto &edge : road)
  {
    cout << edge << "\t";
  }
  cout << "\n";
}

void Graph::show_matrix()
{
  cout << "\n";
  vector<char> col(adjacency_list.size());
  int i = 0;
  for (const auto &vertex : adjacency_list)
  {
    cout << vertex.first << "\t";
    col.push_back(vertex.first);
  }

  cout << "\n";
  for (const auto &row : matrix)
  {
    cout << col[i] << "\t";
    for (const auto &cols : row)
    {
      cout << cols << "\t";
    }

    i++;
    cout << "\n";
  }
}

void Graph::make_matrix()
{
  vector<char> cmp_vertex;
  for (const auto vertex : adjacency_list)
  {
    cmp_vertex.push_back(vertex.first);
  }

  vector<bool> row;
  bool flag;
  int cont;

  for (const auto &vertex : adjacency_list)
  {
    flag = false;
    cont = 0;
    vector<char> edges = vertex.second;

    for (auto cmp : cmp_vertex)
    {
      int i = 0;
      for (auto edge : edges)
      {
        if (cmp == edge)
        {
          flag = true;
          edges.erase(edges.begin() + i);

          if (vertex.first != edge)
          {
            cont++;
          }
          break;
        }
        i++;
      }
      row.push_back(flag);
    }

    degrees.push_back(cont);
    total_degrees += cont;

    matrix.push_back(row);
    row.clear();
    edges.clear();
  }

  related = true;
  for (const auto &t : degrees)
  {
    if (t == 0)
    {
      related = false;
    }
  }

  symmetric = is_symmetric();
}

bool Graph::is_symmetric()
{
  int n = matrix.size(), m = matrix[0].size();
  for (int i = 0; i < n; i++)
  {
    for (int j = i + 1; j < m; j++)
    {
      if (matrix[i][j] != matrix[j][i])
      {
        return false;
      }
    }
  }

  return true;
}

bool Graph::is_eulerian()
{
  if (symmetric && related)
  {
    int unpair_nodes = 0, j = 0, n = degrees.size(), start_last[2];

    for (int i = 0; i < n; i++)
    {
      if ((degrees.at(i) % 2) == 1)
      {
        unpair_nodes++;
        start_last[j] = i;
        j++;
      }
    }

    if (unpair_nodes == 0)
    {
      do_euler();
      return true;
    }

    if (unpair_nodes == 2)
    {
      do_euler(start_last);
      return true;
    }
  }

  return false;
}

map<char, vector<char>> update(char start, char last, map<char, vector<char>> list)
{
  auto start_it = list.find(start);
  auto last_it = list.find(last);

  vector<char>::iterator pos_last = std::find(start_it->second.begin(), start_it->second.end(), last);
  vector<char>::iterator pos_start = std::find(last_it->second.begin(), last_it->second.end(), start);

  if (start_it != list.end() && last_it != list.end())
  {
    int i = std::distance(start_it->second.begin(), pos_last);
    int j = std::distance(last_it->second.begin(), pos_start);

    if (i < (int) start_it->second.size())
    {
      start_it->second.erase(start_it->second.begin() + i);
    }

    if (j < (int) last_it->second.size())
    {
      last_it->second.erase(last_it->second.begin() + j);
    }
  }

  return list;
}

void Graph::do_euler()
{
  int size = total_degrees / 2;
  char start, next, last;
  map<char, vector<char>> temp = adjacency_list;

  map<char, vector<char>>::iterator it = temp.begin();

  start = it->first;
  last = start;
  vector<char> circuit;
  circuit.push_back(start);

  int i;
  do
  {
    i = 0;
    for (auto &node : temp)
    {
      if (node.first == start)
      {
        if (node.second.at(i) == last && node.second.size() > 2)
        {
          i = 1;
        }
        next = node.second.at(i);
        temp = update(start, next, temp);
        size--;
        start = next;
        circuit.push_back(start);
        break;
      }
    }
  } while (size > 1);

  circuit.push_back(last);

  euler = circuit;
}

void Graph::do_euler(int start_last[2])
{
  int size = total_degrees / 2;
  char start, next, last;
  map<char, vector<char>> temp = adjacency_list;
  vector<char> road;

  int k = 0;
  map<char, vector<char>>::iterator it = temp.begin();
  for (; it != temp.end(); it++)
  {
    if (k == start_last[0])
    {
      start = it->first;
      break;
    }
    k++;
  }

  std::advance(it, k);

  for (; it != temp.end(); it++)
  {
    if (k == start_last[1])
    {
      last = it->first;
    }
    k++;
  }

  int i;
  road.push_back(start);

  do
  {
    i = 0;
    for (auto &node : temp)
    {
      if (node.first == start)
      {
        if (node.second.at(i) == last && node.second.size() > 2)
        {
          i = 1;
        }
        next = node.second[i];
        temp = update(start, next, temp);
        size--;
        start = next;
        road.push_back(start);
        break;
      }
    }
  } while (size > 1);

  road.push_back(last);

  euler = road;
}
