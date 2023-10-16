# Class Graph
> The class graph permains to acces to some 

##### Things
> fun to make matrix v1.0
 ```c++
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
cont = 0;
vector<char> edges = vertex.second;

for (auto cmp : cmp_vertex)
{
    flag = false;
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
    break;
}
}
 ```
> fun to make matrix v1.2
```c++
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
set<char> edges;
for (auto edge : vertex.second)
{
    edges.insert(edge);
}

for (auto cmp : cmp_vertex)
{
    if (find(edges.begin(), edges.begin(), cmp) != edges.end())
    {
    flag = true;
    }
    else
    {
    flag = false;
    }

    row.push_back(flag);
}

cont = edges.size();
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
    break;
}
}

symmetric = is_symmetric();
```