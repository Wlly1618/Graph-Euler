#include <Graph.h>
#include <Reader.h>

int main()
{
  Reader read;
  read.run();

  vector<map<char, vector<char>>> graphs = read.get_input();

  for (const auto graph : graphs)
  {
    Graph g(graph);
    g.show_graph();
    for (int i=0; i<100; i++) cout << "-";
    cout << "\n\n";
  }

  _flushall();

  return 0;
}
