#include <iostream>
#include<fstream>
#include <map>
#include <set>
#include <string>
#include <sstream>
//#include <windows.h>
#include <algorithm>
#include <chrono>

#define SSTR( x ) static_cast< std::ostringstream & >( \
    ( std::ostringstream() << std::dec << x ) ).str()

using namespace std;
using namespace std::chrono;

bool checkReactionInput(set<string>::iterator firstComp, set<string>::iterator lastComp, const set<string>& components)
{
    bool equal = false;
    //cout << "Reaction input:" << endl;
    for(firstComp; firstComp != lastComp; firstComp++)
    {
        if(components.find(*firstComp) != components.end())
            equal = true;
        else
        {
            equal = false;
            break;
        }
        //cout << *firstComp << endl;
    }
    return equal;
}

/*std::string GetLastErrorAsString()
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
}*/

int main(int argc,  char **argv)
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    multimap<set<string>, set<string>> reactions;

    set<string> components;

    ifstream source("try.txt");

    /*if (!source.is_open())
    {
        //cout << "Error opening the file" << endl;
        //        cout << GetLastErrorAsString();
        return 1;
    }*/

    //cout << "Input: " << endl;
    string line;
    while(getline(source, line)) // построчно считываем вход
    {
       // cout << line << endl;
        size_t found = line.find_first_of("->"); // стрелочка => это строчка с реакцией

        if(found==std::string::npos) // если стрелочку не нашли, то это компонент
        {
            char ch = ' '; // компонентов может идти несколько через пробел в одной строчке
            string number =""; // строка для числа, так как оно может состоять более, чем из одного символа
            number += line[0]; // предполагаем, что строка начинается с цифры, добавляем этот символ в число
            for (int x = 1; x < line.length(); x++)
            {
                if(line[x] != ch) // если символ - не пробел
                {
                    number += line[x]; // добавляем его в число
                }
                else // если символ - пробел
                {
                    components.insert(number); // добавляем собранное число в компоненты
                    number = ""; // и очищаем числобуфер
                }
            }
            components.insert(number); // последнее собранное число без пробела в конце
        }
        else // если стрелочку нашли, то есть это реакция
        {
            string leftstr = line.substr(0, found); // строчка до стрелочки
            string rightstr = line.substr(found+2, line.length()); // строчка после стрелочки
            set<string> lefttemp; // сюда будем пихать компоненты из левой части по отдельности
            set<string> righttemp; // сюда то же из правой части

            char ch = '+'; // разделитель в реакции - +
            string number =""; // числобуфер
            number += leftstr[0]; // первый символ вероятно число
            for (int x = 1; x < leftstr.length(); x++) // тот же цикл
            {
                if(leftstr[x] != ch)
                {
                    number += leftstr[x];
                }
                else
                {
                    //components.insert(number);
                    lefttemp.insert(number);
                    number = "";
                }
            }
            lefttemp.insert(number);
            //components.insert(number);
            number = "";
            // вообще та же хрень для правой части
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

            // засовываем в массив реакций пары массивов чисел из правой и левойчастей
            reactions.insert(pair<set<string>, set<string>>(lefttemp, righttemp));
        }

    }

    map<set<string>, set<string>>::iterator iter;
    //set<string>::iterator leftiter;
    set<string>::iterator rightiter;

    // выводим сохраненные реакции
    /*cout << "Reactions:" << endl;

    for (iter = reactions.begin(); iter != reactions.end(); iter++)
    {
        for (leftiter=iter->first.begin(); leftiter != iter->first.end(); leftiter++)
            cout << *leftiter << " ";
        cout << "-> ";
        for (rightiter=iter->second.begin(); rightiter != iter->second.end(); rightiter++)
            cout << *rightiter << " ";
        cout << endl;
    }*/

    bool newgoingreactionfound = true;
    //string zero = "0";

    while(newgoingreactionfound)
    {
       // cout << "Searching through reactions..." << endl;
        newgoingreactionfound = false;
        // начинаем смотреть, какие реакции идут
        for (iter = reactions.begin(); iter != reactions.end();)
        {
            if (checkReactionInput(iter->first.begin(), iter->first.end(), components))
            {
                //cout << "Another going reaction was found!" << endl;
                newgoingreactionfound = true;
                for (rightiter=iter->second.begin(); rightiter != iter->second.end(); rightiter++)
                {
                   // cout << "Inserting " << *rightiter << " in components" << endl;
                    components.insert(*rightiter);
                }
                //

               iter = reactions.erase(iter);
               if(iter == reactions.end())
                   break;
            }
            iter++;
        }
    }

    // выводим сохраненные компоненты
    set<string>::iterator itercomp;

    //cout << "Output:" << endl;
    for (itercomp = components.begin(); itercomp != components.end(); itercomp++)
        cout << *itercomp << endl;

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<seconds>( t2 - t1 ).count();

    cout << duration << endl;


    return 0;
}
