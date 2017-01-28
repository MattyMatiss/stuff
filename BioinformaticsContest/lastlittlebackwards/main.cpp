#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int findEquality(string leftAT, string ATright)
{
    while(!equal(leftAT.begin(), leftAT.end()-1, ATright.begin()))
        leftAT.erase(0, 1);

    return leftAT.length();
}

void findEqualityTEST()
{
    int check = findEquality("gggwwwwert", "ertiiiiitttttttttttttt");
    if(check != 3)
    {
        cout << "!!! findEquality() doesn't work!" << endl;
        cout << "It should be 3, not " << check << endl;
    }
}

string glueTwoStrings(string left, string right)
{
    string output = left;
    int same = findEquality(left, right);
    output.erase(output.length()-same, same);
    output.append(right);
    return output;
}

void glueTwoStringsTEST()
{
    string check = glueTwoStrings("gwert", "ertit");
    if(check != "gwertit")
    {
        cout << "!!! glueTwoStrings() doesn't work!" << endl;
        cout << "It should be \"gwertit\", not " << check << endl;
    }
}

string glueReads(vector<string>& reads)
{
    string GluedString = "";
    vector<string>::iterator readsiter = reads.begin();
    GluedString.append(*readsiter);
    for(; readsiter != reads.end(); readsiter++)
        GluedString = glueTwoStrings(GluedString, *readsiter);

    return GluedString;
}

struct compare {
    bool operator()(const std::string& first, const std::string& second) {
        return first.size() < second.size();
    }
};

int main()
{
    string DnaSequence;

    ifstream source("incm.txt");

    string counttemp;
    int count;

    getline(source, DnaSequence);
    getline(source, counttemp);
    istringstream convert(counttemp);
    convert >> count;

    vector<string> reads;

    string readtemp;
    while (getline(source, readtemp))
    {
        reads.push_back(readtemp);
    }

    findEqualityTEST();

    glueTwoStringsTEST();

    //vector<string> test = {"1eee", "eee2rrr", "rrr3ttt", "ttt4yyy", "yyy5ooo", "ooo6"};

    //cout << glueReads(test);

    //vector<string> allPremuts;

    //sort(reads.begin(), reads.end());

    ofstream fout("sequences.txt");

    //for(VSiter = allPremuts.begin(); VSiter != allPremuts.end(); VSiter++)
        //fout << *VSiter << endl;

    do {
       // allPremuts.push_back(glueReads(reads));
        fout << glueReads(reads) << endl;
    } while(next_permutation(reads.begin(), reads.end()));

   // vector<string>::iterator VSiter;
   // compare c;
   // sort(allPremuts.begin(), allPremuts.end(), c);



















    return 0;
}
