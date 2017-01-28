#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    vector<pair<vector<int>, vector<int>>> reactions;
    vector<int> left;
    vector<int> right;

    for (size_t i = 0; i < 50000; i++)
    {
        for(size_t j = 0; j < 100; j++)
        {
            left.push_back(rand() % 100000 +1);
            right.push_back(rand() % 100000 +1);
        }
        reactions.push_back(make_pair(left, right));
        left.clear();
        right.clear();
    }

    ofstream fout;
    fout.open("try.txt");

    for(int i = 0; i < 1000; i++)
    {
        for(int j=0; j < 100; j++)
            fout << rand() % 100000 +1 << " ";
        fout << endl;
    }

    vector<pair<vector<int>, vector<int>>>::iterator veciter;
    vector<int>::iterator liter;
    vector<int>::iterator riter;

    for(veciter = reactions.begin(); veciter != reactions.end(); veciter++)
    {
        for(liter = veciter->first.begin(); liter != veciter->first.end()-1;)
        {
            fout << *liter << "+";
            liter++;
        }
        fout << *liter << "->";
        for(riter = veciter->second.begin(); riter != veciter->second.end()-1;)
        {
            fout << *riter << "+";
            riter++;
        }
        fout << *riter <<  endl;
    }

    fout.close();

    return 0;
}
