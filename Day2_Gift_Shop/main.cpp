#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdint>

typedef struct
{
  std::int64_t min_;
  std::int64_t max_;
} ID_Range;

std::vector<ID_Range> parseRanges(const std::string &filepath)
{
  std::ifstream infile(filepath);
  std::string line;
  if (!std::getline(infile, line))
  {
    throw std::runtime_error("Input file is empty or unreadable");
  }

  std::vector<ID_Range> ranges;
  std::stringstream ss(line);
  std::string token;

  while (std::getline(ss, token, ','))
  {
    size_t dash = token.find('-');
    if (dash == std::string::npos)
    {
      throw std::runtime_error("Invalid range (missing '-'): " + token);
    }

    std::string minStr = token.substr(0, dash);
    std::string maxStr = token.substr(dash + 1);

    std::int64_t minVal = std::stoll(minStr);
    std::int64_t maxVal = std::stoll(maxStr);

    ranges.push_back({minVal, maxVal});
  }

  return ranges;
}

std::int64_t findDuplicates(const std::vector<ID_Range> &ranges)
{
  std::int64_t duplicateCount = 0;

  for (const auto &r : ranges)
  {
    for (std::int64_t id = r.min_; id <= r.max_; ++id)
    {
      std::string s = std::to_string(id);
      size_t n = s.size();
      bool is_repeated = false;

      for (size_t k = 1; k <= n / 2; ++k)
      {
        if (n % k != 0)
          continue;
        size_t reps = n / k;
        if (reps < 2)
          continue;

        std::string part = s.substr(0, k);
        bool ok = true;
        for (size_t pos = k; pos < n; pos += k)
        {
          if (s.substr(pos, k) != part)
          {
            ok = false;
            break;
          }
        }
        if (ok)
        {
          is_repeated = true;
          break;
        }
      }

      if (is_repeated)
      {
        duplicateCount += id;
      }
    }
  }

  return duplicateCount;
}

int main(int argc, char *argv[])
{
  std::ifstream infile(argv[1]);
  if (!infile)
  {
    std::cerr << "Error opening file: " << argv[1] << std::endl;
    return 1;
  }

  std::vector<ID_Range> ranges = parseRanges(argv[1]);

  std::cout << "Parsed Ranges:" << std::endl;
  for (const auto &range : ranges)
  {
    std::cout << "Min: " << range.min_ << ", Max: " << range.max_ << std::endl;
  }

  std::int64_t pw = findDuplicates(ranges);
  printf("Sum of invalid IDs: %lld\n", pw);

  return 0;
}
