#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;
int findEquality(string leftAT, string ATright)
{
    while(!equal(leftAT.begin(), leftAT.end()-1, ATright.begin()))
        leftAT.erase(0, 1);

    return leftAT.length();
}


string glueTwoStrings(string left, string right)
{
    string output = left;
    int same = findEquality(left, right);
    output.erase(output.length()-same, same);
    output.append(right);
    return output;
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
bool isSubSequence(string str1, string str2, int m, int n)
{
    // int m = str1.length();
    //int n = str2.length();
    // Base Cases
    if (m == 0)
        return true;
    if (n == 0)
        return false;

    // If last characters of two strings are matching
    if (str1[m-1] == str2[n-1])
        return isSubSequence(str1, str2, m-1, n-1);

    // If last characters are not matching
    return isSubSequence(str1, str2, m, n-1);
}
int main()
{
   // string OriginalDnaLONGEST;

    //vector<strings> sequencesSub; // все перестановки, которые являются
    // подстроками исходной строки +


    string DnaSequence;

    ifstream source("C:\\Users\\Ogrigorieva\\stuff\\BioinformaticsContest\\lastcombined\\3.txt");

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

    source.close();



    ofstream fout("C:\\Users\\Ogrigorieva\\stuff\\BioinformaticsContest\\lastcombined\\sequences.txt");

    string temp = glueReads(reads);
    if(isSubSequence(temp, DnaSequence, temp.length(), DnaSequence.length()))
        fout << temp << endl;

    while(next_permutation(reads.begin(), reads.end()))
    {
        if(isSubSequence(temp, DnaSequence, temp.length(), DnaSequence.length()))
            fout << temp << endl;
    }

    fout.close();

    cout << "Finished " << endl;

    return 0;
}
