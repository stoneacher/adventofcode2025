#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

std::vector<std::string> loadLines(std::string filepath)
{
  std::ifstream infile(filepath);
  if (!infile)
  {
    throw std::runtime_error("Cannot open file: " + filepath);
  }

  std::vector<std::string> lines;
  std::string line;

  while (std::getline(infile, line))
  {
    lines.push_back(line);
  }

  return lines;
}

int findMaxJolts(std::vector<std::string> lines)
{
  int total_max = 0;
  for (const auto &cur_line : lines)
  {
    int best = -1;
    int best_i = -1, best_j = -1;

    std::cout << "Processing line: " << cur_line << '\n';
    for (size_t i = 0; i + 1 < cur_line.size(); ++i)
    {
      int batt_1 = cur_line[i] - '0';
      for (size_t j = i + 1; j < cur_line.size(); ++j)
      {
        int batt_2 = cur_line[j] - '0';
        int val = batt_1 * 10 + batt_2;

        if (val > best)
        {
          best = val;
          best_i = static_cast<int>(i);
          best_j = static_cast<int>(j);
        }
      }
    }

    std::cout << "  best joltage: " << best << " using digits " << cur_line[best_i]
              << " and " << cur_line[best_j] << " at pos " << best_i << " and " << best_j << '\n';
    total_max += best;
  }

  return total_max;
}

int main(int argc, char *argv[])
{
  std::cout << "Day 3: Lobby\n";
  std::vector<std::string> lines = loadLines(argv[1]);

  for (auto i : lines)
  {
    std::cout << i << std::endl;
  }

  int max_jolts = findMaxJolts(lines);

  std::cout << "max jolts: " << max_jolts << std::endl;

  return 0;
}