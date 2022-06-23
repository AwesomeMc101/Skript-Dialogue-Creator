// Skript Dialogue Creator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>

#include <istream>
#include <sstream>
#include <ostream>
#include <strstream>
#include <fstream>

#include <Windows.h> //REMOVE IF ONLINE OR ON MAC/LINUX

std::vector<std::string> extraKeywords = { "sound", "player" };

int main()
{
    std::cout << "Skript Dialogue Creator (SDC) by AwesomeMc101#6494 (Contact ME for support!) " << std::endl;
    SetConsoleTitleA("Skript Dialogue Creator | AwesomeMc101#6494"); //REMOVE IF ONLINE OR ON MAC/LINUX

    std::string filename = "";
    std::cout << "Please enter file name with dialogue in correct format." << std::endl;
    std::getline(std::cin, filename);

    std::ifstream infile;
    infile.open(filename);
    if (!infile.is_open())
    {
        std::cout << "Error opening file." << std::endl;
        return 1;
    }
    std::string linex;

    std::vector<std::string> lines;

    while (std::getline(infile, linex))
    {
        std::istringstream iss(linex);
        /*int a, b;
        if (!(iss >> a >> b)) { 
            std::cout << "[ERROR STREAMING FILE TO SDC] | ABORTING" << std::endl;
            break; }*/
        lines.push_back(linex);
    }

    std::cout << "What would you like your seperator to be? i.e. 'Mom: Hey!' (the seperator being ':')" << std::endl;
    std::string seperator = "";
    std::getline(std::cin, seperator);

    std::vector<std::string> skriptLines;

    //ik that i could just do it inside of the getline but thats DUMB
    for (int i = 0; i < lines.size(); i++)
    {
        std::string line = lines[i];
        std::vector<std::string> tokens;
        char* token;
        char* rest = (char*)line.c_str();
        while ((token = strtok_s(rest, "->", &rest)))
        {
            tokens.push_back(token);
        }
        if (tokens.size() > 2)
        {
            std::cout << "ERROR [LINEINFO " << i << "]: TOKEN MISMATCH (TOO MANY ->) MAX 2, YOU HAVE " << tokens.size() << "!" << std::endl;
            return 1;
        }

        int type = 0; //0 = regular name, 1 = playercall, 2 = soundcall


        std::cout << "[DEBUG INFO]" << std::endl;
        for (int ext = 0; ext < extraKeywords.size(); ext++)
        {
            std::cout << "does " << extraKeywords[ext] << " == " << tokens[0] << std::endl;
            
            if (tokens[0] == extraKeywords[ext])
            {
                std::cout << "true\n";
                switch (ext) {
                case 0:
                    type = 2;
                    break;
                case 1:
                    type = 1;
                    break;
                }
                if (type == 0)
                {
                    std::cout << "ERROR [LINEINFO " << i << "]: KEYWORD UNMATCH ERROR, DEFAULTING TO TYPE: 0" << std::endl;
                }
            }
            else if (tokens[0] == extraKeywords[ext] + " ")
            {
                std::cout << "true\n";
                switch (ext) {
                case 0:
                    type = 2;
                    break;
                case 1:
                    type = 1;
                    break;
                }
                if (type == 0)
                {
                    std::cout << "ERROR [LINEINFO " << i << "]: KEYWORD UNMATCH ERROR, DEFAULTING TO TYPE: 0" << std::endl;
                }
            }
        }
        std::cout << "[TOKENIZER COMPLETE]" << std::endl;
        if (type == 0)
        {
            std::string jLine = "message \"" + tokens[0] + seperator + tokens[1] + "\" to player";
            skriptLines.push_back(jLine);
        }
        else if (type == 1)
        {
            std::string uLine = "message \"%player%" + seperator + tokens[1] + "\" to player";
            skriptLines.push_back(uLine);
        }
        else if (type == 2)
        {
            //play sound "entity.egg.throw" with volume 1 and pitch 2 to player
            std::string sLine = "play sound \"" + tokens[1] + "\" with volume 1 and pitch 1 to player";
            skriptLines.push_back(sLine);
        }
        
    }

    std::cout << "\n\n----Your Code----\n\n";
    for (std::string skrl : skriptLines)
    {
        std::cout << skrl << std::endl;
    }

}
