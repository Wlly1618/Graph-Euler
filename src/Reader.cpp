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
    std::map<char, std::vector<char>> map_input;

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
        output.push_back(map_input);
        map_input.clear();
      }
      else
      {
        char key = line[0];
        std::vector<char> values;

        size_t open_brace_pos = line.find('{');
        if (open_brace_pos != std::string::npos)
        {
          size_t close_brace_pos = line.find('}', open_brace_pos);
          if (close_brace_pos != std::string::npos)
          {
            std::string elements = line.substr(open_brace_pos + 1, close_brace_pos - open_brace_pos - 1);

            size_t pos = 0;
            while ((pos = elements.find(',', pos)) != std::string::npos)
            {
              values.push_back(elements[pos - 1]);
              pos ++;
            }
          }
        }

        map_input[key] = values;
      }
    }

    input_file.close();
    output.push_back(map_input);
  }
}

vector<map<char, vector<char>>> Reader::get_input()
{
  return output;
}
