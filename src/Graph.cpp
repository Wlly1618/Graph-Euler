#include "Graph.h"

Graph::Graph()
{
  cout << "Use the constructor to create the graph\n";
  cout << "Graph example({{'x', {'y', 'z'}}, {'y', {'x', 'z'}}, {'z', {'x', 'y'}}})\n";
}

Graph::~Graph()
{
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
    cout << "Vertex: " << node.first << "\tDegree: " << degrees[i] << "\tEdges: ";
    for (const auto &edge : node.second)
    {
      cout << edge << " ";
    }
    cout << "\n";
    i++;
  }

  cout << "\nTotal Degrees: " << total_degrees << "\n";

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
    cout << "\t" << type << " Eulerian: \t" << msg_true << "\n\n\t";
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
  cout << "\n\t";
  for (auto t : degrees)
  {
    cout << t << "\t";
  }
  cout << "\nTotal: " << total_degrees;

  cout << "\n\n\t";
  vector<char> col(adjacency_list.size());
  int i = 0;
  for (const auto &vertex : adjacency_list)
  {
    cout << vertex.first << "\t";
    col.push_back(vertex.first);
  }

  cout << "\n\n";

  for (const auto &row : matrix)
  {
    cout << col[i] << "\t";
    for (const auto &cols : row)
    {
      cout << cols << "\t";
    }

    i++;
    cout << "\n\n";
  }
}

void Graph::make_matrix()
{
  vector<char> temp_list;
  for (const auto t : adjacency_list)
  {
    temp_list.push_back(t.first);
  }

  bool flag;
  int cont;
  vector<bool> row;
  row.clear();

  for (const auto &vertex : adjacency_list)
  {
    vector<char> edges = vertex.second;
    cont = 0;

    for (auto temp_vertex : temp_list)
    {
      flag = false;
      vector<char>::iterator it;
      do
      {
        it = find(edges.begin(), edges.end(), temp_vertex);
        if (it != edges.end())
        {
          edges.erase(it);
          if (vertex.first != temp_vertex)
          {
            cont ++;
          }
          else
          {
            cont += 2;
          }

          flag = true;
        }
      } while (it != edges.end());

      row.push_back(flag);
    }

    matrix.push_back(row);
    degrees.push_back(cont);
    total_degrees += cont;
    row.clear();
    edges.clear();
  }

  related = true;
  for (const auto &t : degrees)
  {
    if (t == 0)
    {
      related = false;
      break;
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
      type = "Circuit";
      circuit_euler();
      return true;
    }

    if (unpair_nodes == 2)
    {
      type = "Road";
      road_euler(start_last);
      return true;
    }
  }

  return false;
}

void Graph::circuit_euler()
{
  int size = total_degrees / 2;
  char start, last;
  map<char, vector<char>> temp = adjacency_list;

  map<char, vector<char>>::iterator it = temp.begin();

  start = it->first;
  last = start;
  vector<char> circuit;

  do_euler(temp, size, start, last);
}

void Graph::road_euler(int start_last[2])
{
  int size = total_degrees / 2;
  char start, last;
  map<char, vector<char>> temp = adjacency_list;
  vector<char> road;
  bool f_1 = false, f_2 = false;
  int k = 0;
  for (auto it = temp.begin(); it != temp.end(); it++)
  {
    if (k == start_last[0])
    {
      start = it->first;
      f_1 = true;
    }

    if (k == start_last[1])
    {
      last = it->first;
      f_2 = true;
    }

    if (f_1 && f_2)
    {
      break;
    }

    k++;
  }

  do_euler(temp, size, start, last);
}

map<char, vector<char>> update(char start, char last, map<char, vector<char>> list)
{
  auto start_it = list.find(start);
  auto last_it = list.find(last);

  vector<char>::iterator pos_last = find(start_it->second.begin(), start_it->second.end(), last);
  vector<char>::iterator pos_start = find(last_it->second.begin(), last_it->second.end(), start);

  if (start_it != list.end() && last_it != list.end())
  {
    if (pos_last != start_it->second.end())
    {
      start_it->second.erase(pos_last);
    }

    if (pos_start != last_it->second.end())
    {
      last_it->second.erase(pos_start);
    }
  }

  return list;
}

map<char, vector<char>> update(char start, map<char, vector<char>> list)
{
  auto start_it = list.find(start);

  vector<char>::iterator pos = find(start_it->second.begin(), start_it->second.end(), start);

  if (start_it != list.end())
  {
    if (pos != start_it->second.end())
    {
      start_it->second.erase(pos);
    }
  }

  return list;
}

void Graph::do_euler(map<char, vector<char>> temp, int size, char start, char last)
{
  char next;
  int i;

  euler.push_back(start);

  do
  {
    i = 0;
    for (auto &node : temp)
    {
      if (node.first == start)
      {
        if (node.second.at(i) == last && node.second.size() > 1)
        {
          i = 1;
        }

        next = node.second.at(i);
        if (start != next)
        {
          temp = update(start, next, temp);
        }
        else
        {
          temp = update(start, temp);
        }

        size --;
        start = next;
        euler.push_back(start);
        break;
      }
    }
  } while (size > 1);

  euler.push_back(last);
}
