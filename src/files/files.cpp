#include "files.h"

#include <fstream>

namespace util
{
    namespace file
    {
        std::string read(const std::string& path)
        {
            std::string content;
            std::ifstream infile;

            infile.open(path);

            while (!infile.eof())
            {
                std::string line;

                getline(infile, line);

                content.append(line.empty() ? "\n" : line);
            }

            infile.close();

            return content;
        }
    }
}