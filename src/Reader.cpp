#include "Reader.h"

Reader::Reader()
{
  // ctor
}

void Reader::run()
{
  std::ifstream input_file("C:\\Users\\swilf\\OneDrive\\Documents\\Projects\\C++\\Graph-Euler\\graph.txt");

  if (!input_file.is_open())
  {
    std::cerr << "Cannot open...\n";
  }
  else
  {
    std::map<char, std::vector<char>> myMap;

    std::string line;
    while (std::getline(input_file, line))
    {
      if (line.empty())
      {
        continue;
      }

      if (line == "-----")
      {
        // Marca una nueva sección, crea un nuevo mapa
        output.push_back(myMap);
        myMap.clear();
      }
      else
      {
        char key = line[0];
        std::vector<char> values;

        size_t openBracePos = line.find('{');
        if (openBracePos != std::string::npos)
        {
          size_t closeBracePos = line.find('}', openBracePos);
          if (closeBracePos != std::string::npos)
          {
            std::string elements = line.substr(openBracePos + 1, closeBracePos - openBracePos - 1);

            size_t pos = 0;
            while ((pos = elements.find(',', pos)) != std::string::npos)
            {
              values.push_back(elements[pos - 1]);
              pos ++;
            }
          }
        }

        myMap[key] = values;
      }
    }

    input_file.close();
    output.push_back(myMap);
  }
}

vector<map<char, vector<char>>> Reader::get_input()
{
  return output;
}
