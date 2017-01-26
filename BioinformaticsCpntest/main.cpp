#include <iostream>
#include<fstream>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <windows.h>
#include <algorithm>

#define SSTR( x ) static_cast< std::ostringstream & >( \
 ( std::ostringstream() << std::dec << x ) ).str()

using namespace std;

std::string GetLastErrorAsString()
{
    //Get the error message, if any.
    DWORD errorMessageID = ::GetLastError();
    if(errorMessageID == 0)
        return std::string(); //No error message has been recorded

    LPSTR messageBuffer = nullptr;
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

    std::string message(messageBuffer, size);

    //Free the buffer.
    LocalFree(messageBuffer);

    return message;
}

int main(int argc,  char **argv)
{
    setlocale(LC_ALL,"Russian");
    map<set<string>, set<string>> reactions;

    set<string> components;

    ifstream source("C:\\Users\\Ogrigorieva\\stuff\\BioinformaticsCpntest\\bin\\Debug\\try.txt");

    if (!source.is_open())
    {
        cout << "Error opening the file" << endl;
        cout << GetLastErrorAsString();
        return 1;
    }

    string line;
    while(getline(source, line))
    {
        size_t found = line.find_first_of("-");

        if(found==std::string::npos)
        {
            components.insert(line);
        }
        else
        {
            string leftstr = line.substr(0, found);
            string rightstr = line.substr(found+2, line.length());
            set<string> lefttemp;
            set<string> righttemp;

            char ch = '+';
            string number ="";
            number += leftstr[0];
            for (int x = 1; x < leftstr.length(); x++)
            {
                if(leftstr[x] != ch)
                {
                    number += leftstr[x];
                }
                else
                {
                    components.insert(number);
                    lefttemp.insert(number);
                    number = "";
                }
            }
            lefttemp.insert(number);
            components.insert(number);
            number = "";
            number += rightstr[0];
            for (int x = 1; x < rightstr.length(); x++)
            {
                if(rightstr[x] != ch)
                {
                    number += rightstr[x];
                }
                else
                {
                    righttemp.insert(number);
                    number = "";
                }
            }

            righttemp.insert(number);
            number = "";

            reactions.insert(pair<set<string>, set<string>>(lefttemp, righttemp));
        }

    }

    cout << "Reactions:" << endl;
    map<set<string>, set<string>>::iterator iter;
    set<string>::iterator leftiter;
    set<string>::iterator rightiter;

    for (iter = reactions.begin(); iter != reactions.end(); iter++)
    {
        for (leftiter=iter->first.begin(); leftiter != iter->first.end(); leftiter++)
            cout << *leftiter << " ";
        cout << "-> ";
        for (rightiter=iter->second.begin(); rightiter != iter->second.end(); rightiter++)
            cout << *rightiter << " ";
        cout << endl;
    }

    set<string>::iterator itercomp;

    cout << "Chemicals:" << endl;
    for (itercomp = components.begin(); itercomp != components.end(); itercomp++)
        cout << *itercomp << endl;


    return 0;
}
