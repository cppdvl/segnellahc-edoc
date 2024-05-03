#include <set>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <numeric>
#include <utility>
#include <iostream>
#include <filesystem>
#include <functional>

namespace application
{
    std::tuple<int, int, int> count(const::std::string& fileName)
    {
        std::ifstream file(fileName);
        std::string fileContent{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
        bool lastIsSpace = true;
        int characters = fileContent.size();
        
        int lines = std::count(fileContent.begin(), fileContent.end(), '\n');
        lines += (fileContent.back() != '\n') ? 1 : 0;

        int words = std::count_if(fileContent.begin(), fileContent.end(), [&lastIsSpace](char c){
                    bool positive = lastIsSpace && !std::isspace(c);
                    lastIsSpace = std::isspace(c);
                    return positive;
                    });
        return std::make_tuple(characters, lines, words);
    }
}
namespace application
{
    bool fileexists(const std::string & filename)
    {
        return std::filesystem::exists(filename);
    }
}

namespace application
{
    
    int linefactor = 0;
    int wordfactor = 0;
    int characterfactor = 0;
    std::vector<std::string> files{};
    void run(int argc, char *argv[]) 
    {
        for (int i = 1; i < argc; i++)
        {
            if (argv[i][0] == '-')
            {
                linefactor = std::count (argv[i], argv[i] + strlen(argv[i]), 'l');
                wordfactor = std::count (argv[i], argv[i] + strlen(argv[i]), 'w');
                characterfactor = std::count (argv[i], argv[i] + strlen(argv[i]), 'c');
                continue;
            }
            if (application::fileexists(std::string{argv[i]}))
            {

                auto [c, l, w] = application::count(std::string{argv[i]});
                if (w*wordfactor) std::cout << "Word count: " << w << std::endl;
                if (l*linefactor) std::cout << "Line count: " << l << std::endl;
                if (c*characterfactor) std::cout << "Character count: " << c << std::endl;
            }
        }
    }
}


int main(int argc, char ** argv) {
    
    application::run(argc, argv);
    return 0;
}
