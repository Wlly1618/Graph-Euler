#include <Graph.h>

using namespace std;

int main()
{
  Graph g1(
    {
      {'A', { 'B', 'C', 'D' } },
      {'B', { 'A', 'C', 'D' } },
      {'C', { 'A', 'B' } },
      {'D', { 'A', 'B' } }
    }
  );

  g1.show_graph();

  return 0;
}
