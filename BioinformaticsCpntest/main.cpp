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
    map<set<string>, set<string>> reactions; // склеиваем input и output
    //с разделителями и засовываем сюда. Задумка, что строчки
    //будут приведены к единому формату и повторения исключатся

    set<string> components; // присутствующие компоненты

    // сначала проходим весь файл,
    // в components пихаем все свободные
    // в reactions через input и output пихаем реакции

    // проходим реакции, проверяем по первой части, идет ли,
    // если нет - удаляем

    // добавляем в components компоненты из вторых частей reactions

    /*  if(argc != 2)
      {
          cout << "Something wrong with arguments" << endl;
          return 1;
      }*/

    ifstream source("C:\\Users\\Ogrigorieva\\stuff\\BioinformaticsCpntest\\bin\\Debug\\try.txt");/*argv[1]*/

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
        // std::replace(line.begin(), line.end(), '+', ' ');

        if(found==std::string::npos)
        {
            components.insert(line);
        }
        else
        {
            string leftstr = line.substr(0, found);
            string rightstr = line.substr(found+2, sizeof(line));
            set<string> lefttemp;
            set<string> righttemp;

            //  cout << "Left: " << leftstr << endl;

            //map<string> input; // сюда считываем числа до стрелочки

            char ch = '+';
            string number ="";
            number += leftstr[0];
            for (int x = 1; x < leftstr.length(); x++)
            {
                if(leftstr[x] != ch)
                {
                    number += leftstr[x];
                    //cout << "number: " << number << endl;
                }
                else
                {
                    // input.insert(number);
                    components.insert(number);
                    lefttemp.insert(number);
                    //  cout << "number: " << number << endl;
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
                    //cout << "number: " << number << endl;
                }
                else
                {
                    // input.insert(number);
                    righttemp.insert(number);
                    //  cout << "number: " << number << endl;
                    number = "";
                }
            }

            righttemp.insert(number);
            number = "";

            reactions.insert(pair<setstring, string>(leftstr, rightstr));


//            input.insert(number);

            //  map<string>::iterator iterin;

            // for (iterin = input.begin(); iterin != input.end(); iterin++)
            //   cout << *iterin << endl;


            /* std::stringstream leftstream(left);
             std::string numberstr;


             while(std::getline(leftstream, numberstr, '+'))
             {
                 int number;
                 stringstream(numberstr) >> number;
                 input.insert(number);
                 numberstr = "";
             }


             std::stringstream rightstream(left);

             set<int> output; // сюда считываем числа после стрелочки

             while(std::getline(rightstream, numberstr, '+'))
             {
                 int number;
                 stringstream(numberstr) >> number;
                 output.insert(number);
                 numberstr = "";
             }

             set<int>::iterator iterout;

             cout << "Chemicals:" << endl;
             for (iterout = output.begin(); iterout != output.end(); iterout++)
                 cout << *iterout << endl;

             line="";

             for (auto x : input)
                 line += SSTR(x) + ' ';

             string arrow = "->";
             line.replace(line.end(), line.end(), arrow);

             for (auto x : output)
                 line += SSTR(x) + ' ';

             //line.erase(line.end());*/

            //!!!!!!!!!!!!!!  reactions.insert(line);
        }

    }



    /*  cout << "Reactions:" << endl;
      map<string>::iterator iter;

      for (iter = reactions.begin(); iter != reactions.end(); iter++)
          cout << *iter << endl;*/

    set<string>::iterator itercomp;

    cout << "Chemicals:" << endl;
    for (itercomp = components.begin(); itercomp != components.end(); itercomp++)
        cout << *itercomp << endl;


    return 0;
}
