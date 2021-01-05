#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <stdio.h>
#include <stdlib.h>
#include <tuple>
#include <functional>
#include <windows.h>
#include <shlobj.h>
#include <algorithm>
#include "Console.h"
#include <dirent.h>
using namespace std;
namespace con = JadedHoboConsole;

std::string hDIR;

class InputParser{
    public:
        InputParser (int &argc, char **argv){
            for (int i=1; i < argc; ++i)
                this->tokens.push_back(std::string(argv[i]));
        }
        /// @author iain
        const std::string& getCmdOption(const std::string &option) const{
            std::vector<std::string>::const_iterator itr;
            itr =  std::find(this->tokens.begin(), this->tokens.end(), option);
            if (itr != this->tokens.end() && ++itr != this->tokens.end()){
                return *itr;
            }
            static const std::string empty_string("");
            return empty_string;
        }
        /// @author iain
        bool cmdOptionExists(const std::string &option) const{
            return std::find(this->tokens.begin(), this->tokens.end(), option)
                   != this->tokens.end();
        }
    private:
        std::vector <std::string> tokens;
};

char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

void WriteInfo(string fName, string msg)
{
    ofstream file;
    file.open (fName);
    if (file.is_open())
    {
        file << msg << "\n";
        file.close();
  }
}

void parseCSV(string nFile,int lineNo)
{
    std::ifstream  data(nFile);
    std::string line;
    std::vector<pair<pair<std::string, std::string>, std::string>> parsedCsv;
    std::vector<string> result;
    while(std::getline(data,line))
    {
        std::stringstream lineStream(line);
        std::string cell;
        std::vector<std::string> parsedRow;
        while(std::getline(lineStream,cell,','))
        {
            parsedRow.push_back(cell);
        }

        //cout << parsedRow[0] << ","  << parsedRow[1]  << endl;
        parsedCsv.push_back(make_pair(make_pair(parsedRow[0],parsedRow[2]),parsedRow[1]));
    }

    int idx=0;

    if (lineNo==0) {
        cout << "dirMarks " << con::fg_green << "v0.2" << con::fg_norm << " Window 10" << endl;
        cout << con::fg_cyan << "----+-----------------------" << con::fg_norm << endl;

        for (auto it = begin (parsedCsv); it != end (parsedCsv); ++it) {
            idx++;
            cout.width(5); cout << std::right << con::fg_yellow << idx << "  ";
            cout.width(20); cout << std::left << con::fg_green << (it->first).first ;
            con::console.SetColor(std::stoi((it->first).second),0);
            cout << it->second << con::fg_norm << endl;
            //printf(" %d %-20s %s \n",idx, it->first.c_str(), it->second.c_str());
            result.push_back(it->second);
        }
        cout << con::fg_cyan << "----+-----------------------" << con::fg_norm << endl;
    }

    char input[100];
    vector<int> numbers;

    if (lineNo == 0) {
        cout << "Select dirMark: ";
        cin.getline(input, sizeof(input));
        stringstream stream(input);
        while (stream.rdbuf()->in_avail() != 0) {
            std::string n;
            stream >> n;
            if(is_number(n)) {
                numbers.push_back(std::stoi(n));
            }
        }
    } else {
        for (auto it = begin (parsedCsv); it != end (parsedCsv); ++it) {
            idx++;
            result.push_back(it->second);
        }
        numbers.push_back(lineNo);
    }

    if (numbers.size()>0) {
        if ((numbers[0]<=idx)&&(numbers[0]>0)) {
            //cout << "--> " << numbers[0] << " , " << result[numbers[0]-1]<< endl;
            WriteInfo(hDIR+"\\cddir",result[numbers[0]-1]);
        }
    } else {
        WriteInfo(hDIR+"\\cddir","");
    }

};

std::string curr_dir()
{
    char* cwd = _getcwd( 0, 0 ) ; // **** microsoft specific ****
    std::string working_directory(cwd) ;
    std::free(cwd) ;
    return working_directory ;
}

int main(int argc, char **argv)
{
    int i=0;
    InputParser input(argc, argv);
    if(input.cmdOptionExists("-h")){
        cout << "  -g          goto bookMark" << endl;
        cout << "  -s alias    Set CurrDirector as alias" << endl;

    }

    char path[ MAX_PATH ];
    if (SHGetFolderPathA( NULL, CSIDL_PROFILE, NULL, 0, path ) == S_OK)
    {
      hDIR=path;
    }

    /*
    if (SHGetFolderPathA( NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path ) != S_OK)
    {
      cout << "I could not retrieve the user's application data directory!\n";
    }
    else
    {
      cout << "Application data directory = \"" << path << "\"\n";
    }
    */

    const std::string &lineNo =input.getCmdOption("-g");
    if (!lineNo.empty())
    {
        parseCSV(hDIR+"\\bookm.csv",std::stoi( lineNo ));
        i++;
    }
    const std::string &msg = input.getCmdOption("-s");
    if (!msg.empty())
    {
        std::ofstream outfile;

        outfile.open(hDIR+"\\bookm.csv", std::ios::app); // append instead of overwrite
        outfile << msg << "," << curr_dir() << "," << "7" << endl;;
        outfile.close();
        i++;

    }

    if (i == 0) {
        parseCSV(hDIR+"\\bookm.csv",0);
    }

    con::console.SetColor(7,0);
    return 0;
}
