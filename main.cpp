#include <Graph.h>

using namespace std;

int main()
{
  Graph g1(
    {
      {'A', { 'B', 'C', 'C', 'D', 'D' } },
      {'B', { 'A', 'C', 'C', 'D', 'D' } },
      {'C', { 'A', 'A', 'B', 'B' } },
      {'D', { 'A', 'A', 'B', 'B' } }
    }
  );

  g1.show_graph();
  cout << "\n\n";


 Graph g2(
   {
     {'A', { 'A', 'B', 'C', 'D' } },
     {'B', { 'A', 'C', 'D' } },
     {'C', { 'A', 'B' } },
     {'D', { 'A', 'B' } }
   }
 );

 g2.show_graph();
 cout << "\n\n";
//
// Graph g3(
//   {
//     {'A', { 'B', 'C', 'D' } },
//     {'B', { 'A', 'C', 'D' } },
//     {'C', { 'A', 'B' } },
//     {'D', { 'A', 'B' } }
//   }
// );
//
// g3.show_graph();
// cout << "\n\n";
//
 Graph g4(
   {
     {'A', { 'B', 'F' } },
     {'B', { 'A', 'D', 'E', 'F'} },
     {'C', { 'F', 'D' } },
     {'D', { 'B', 'C', 'E', 'F' } },
     {'E', { 'B', 'D' } },
     {'F', { 'A', 'B', 'C', 'D' } }
   }
 );

 g4.show_graph();
 cout << "\n\n";

// Graph g5(
//   {
//     {'A', { 'B', 'C', 'D', 'E' } },
//     {'B', { 'A', 'D' } },
//     {'C', { 'A' } },
//     {'D', { 'A', 'B', 'E', 'F' } },
//     {'E', { 'A', 'D', 'F' } },
//     {'F', { 'D', 'E' } }
//   }
// );
//
// g5.show_graph();
// cout << "\n\n";

  _flushall();

  return 0;
}
