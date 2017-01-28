#include <iostream>
#include<fstream>
#include <map>
#include <set>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

inline bool checkReactionInput(vector<string>::iterator firstComp, vector<string>::iterator lastComp, const set<string>& components)
{
    bool equal = false;
    for(; firstComp != lastComp; firstComp++)
    {
        if(components.find(*firstComp) != components.end())
        {
            equal = true;

        }
        else
        {
            equal = false;
            break;
        }
    }
    return equal;
}

int main()
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    vector<pair<vector<string>, vector<string>>> reactions;

    set<string> components;

    //ifstream source("try.txt");
    ifstream source("short.txt");

    string number;
    char ch;
    string leftstr;
    string rightstr;
    size_t found;
    vector<string> lefttemp;
    vector<string> righttemp;
    size_t x;
    bool equal;

    string line;
    while(getline(source, line)) // построчно считываем вход
    {
        found = line.find_first_of("->"); // стрелочка => это строчка с реакцией

        if(found==std::string::npos) // если стрелочку не нашли, то это компонент
        {
            ch = ' '; // компонентов может идти несколько через пробел в одной строчке
            number =""; // строка для числа, так как оно может состоять более, чем из одного символа
            number += line[0]; // предполагаем, что строка начинается с цифры, добавляем этот символ в число
            for (x = 1; x < line.length(); x++)
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
            leftstr = line.substr(0, found); // строчка до стрелочки
            rightstr = line.substr(found+2, line.length()); // строчка после стрелочки
            lefttemp.clear(); // сюда будем пихать компоненты из левой части по отдельности
            righttemp.clear(); // сюда то же из правой части

            ch = '+'; // разделитель в реакции - +
            number =""; // числобуфер
            number += leftstr[0]; // первый символ вероятно число
            for (x = 1; x < leftstr.length(); x++) // тот же цикл
            {
                if(leftstr[x] != ch)
                {
                    number += leftstr[x];
                }
                else
                {
                    lefttemp.push_back(number);
                    number = "";
                }
            }
            lefttemp.push_back(number);
            number = "";
            // вообще та же хрень для правой части
            number += rightstr[0];
            for (x = 1; x < rightstr.length(); x++)
            {
                if(rightstr[x] != ch)
                {
                    number += rightstr[x];
                }
                else
                {
                    righttemp.push_back(number);
                    number = "";
                }
            }

            righttemp.push_back(number);
            number = "";

            // засовываем в массив реакций пары массивов чисел из правой и левойчастей
            reactions.push_back(make_pair(lefttemp, righttemp));
        }

    }

    vector<pair<vector<string>, vector<string>>>::iterator iter;
    vector<string>::iterator rightiter;

    bool newgoingreactionfound = true;

    while(newgoingreactionfound)
    {
        newgoingreactionfound = false;
        // начинаем смотреть, какие реакции идут
        for (iter = reactions.begin(); iter != reactions.end();)
        {
            equal = false;
            for(rightiter=iter->first.begin(); rightiter != iter->first.end(); rightiter++)
            {
                if(components.find(*rightiter) != components.end())
                {
                    equal = true;
                  //  rightiter=reactions[iter]->first.erase(*rightiter);
                   // if(rightiter==iter->first.end())
                   //     break;
                }
                else
                {
                    equal = false;
                    break;
                }
            }
            if (equal) // checkReactionInput(iter->first.begin(), iter->first.end(), components))
            {
                newgoingreactionfound = true;
                for (rightiter=iter->second.begin(); rightiter != iter->second.end(); rightiter++)
                {
                    components.insert(*rightiter);
                }

                iter = reactions.erase(iter);
                //break; // !!!!!!!!
                if(iter == reactions.end())
                    break;
            }
            iter++;
        }
    }

    // выводим сохраненные компоненты
    set<string>::iterator itercomp;

    for (itercomp = components.begin(); itercomp != components.end(); itercomp++)
        cout << *itercomp << endl;

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<seconds>( t2 - t1 ).count();

    cout << duration << endl;

    return 0;
}
