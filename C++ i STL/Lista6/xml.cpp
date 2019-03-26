#include <regex>
#include <iostream>
#include <fstream>

void tabs(int t){
    for(int i=0;i<t;i++)
        std::cout << "\t";
}

int main(int argc, char **argv){
    std::fstream file;
    file.open(argv[1]);
    std::string line;
    std::regex oneline ("<.+>.+<\\/.+>");
    std::regex start ("<[^\\/]+>");
    std::regex end("<\\/.+>");
    std::regex spaces("\\s{2,}");
    std::regex starttag("<\\w*>");
    std::regex endtag("<\\/\\w*>");
    std::regex onlylast("<\\w*>[^<]+");
    std::regex onlyfirst("([^<>])+(<\\/\\w*>)");
    int tab = 0;
    while(std::getline(file, line)){
        line = std::regex_replace(line, spaces, " ");
        if(std::regex_match(line, oneline)){
            tabs(tab);
            std::cout << std::regex_replace(line, onlyfirst, "") << "\n";
            tabs(tab + 1);
            std::cout << std::regex_replace(std::regex_replace(line, starttag,""), endtag, "" ) << "\n";
            tabs(tab);
            std::cout << std::regex_replace(line, onlylast, "") << "\n";
        }

        else if(std::regex_match(line, start)){
            tabs(tab);
            tab++;
            std::cout << line << "\n";
        }

        else if(std::regex_match(line, end)){
            tab--;
            tabs(tab);
            std::cout << line << "\n";
        }

        else {
            tabs(tab);
            std::cout << line << "\n";
        }
    }
}

