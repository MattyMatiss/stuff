#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

vector<int> final;

vector<pair<int, int>> whatShouldBeIncluded;

vector<pair<int, int>> whatShouldBeIncludedDNA;

// takes the input dna string, one read, vector to store position, the position to start looking from and stores all found position
void findAllSubs(string left, string right, int fromWhatpositionToLook, const string &DnaString)
{
    string foundpart = left;
    string remainingpart = right;

    int found = DnaString.find(foundpart, fromWhatpositionToLook);

    if(found != -1) // если нашли
    {
        whatShouldBeIncluded.push_back(make_pair(found, found + foundpart.length()-1));
        final.push_back(found+1);
        // важные две строчки
        //if(remainingpart.length() > 0)
           // findAllSubs(remainingpart, "", found + foundpart.length(), DnaString);
    }
    else // если не нашли
    {
        if(foundpart.length() > 1)
        {
            remainingpart.insert(0, 1, foundpart.back());
            foundpart.pop_back();
            findAllSubs(foundpart, remainingpart, fromWhatpositionToLook, DnaString);
        }
    }
}

void findAllSubsDNA(string left, string right, int fromWhatpositionToLook, const string &DnaString)
{
    string foundpart = left;
    string remainingpart = right;

    int found = DnaString.find(foundpart, fromWhatpositionToLook);

    if(found != -1) // если нашли
    {
        whatShouldBeIncludedDNA.push_back(make_pair(found, found + foundpart.length()-1));
        // final.push_back(found+1);
        if(remainingpart.length() > 0)
            findAllSubsDNA(remainingpart, "", found + foundpart.length(), DnaString);
    }
    else // если не нашли
    {
        if(foundpart.length() > 1)
        {
            remainingpart.insert(0, 1, foundpart.back());
            foundpart.pop_back();
            findAllSubsDNA(foundpart, remainingpart, fromWhatpositionToLook, DnaString);
        }
    }
}

// takes set of found positions and compares them to the count of reads. in perfect string must be equal
bool checkNumbersOfReads(vector<pair<int, int>>& positions, vector<string> reads)
{
    bool allcorrect = false;
    bool numberthesame = false;
    bool lengthsthesame = false;
    if(positions.size() == reads.size())
    {
        cout << "Number of positions and number of reads are THE SAME" << endl;
        numberthesame = true;
        cout << "and" << endl;

        vector<pair<int, int>>::iterator positionsiter;
        vector<string>::iterator readsiter = reads.begin();

        for(positionsiter = positions.begin(); positionsiter != positions.end(); positionsiter++, readsiter++)
        {
            if((positionsiter->second - positionsiter->first + 1) == readsiter->length())
            {
                cout << positionsiter->first << " to " << positionsiter->second << " = " << readsiter->length() << endl;
                lengthsthesame = true;
            }
            else
            {
                lengthsthesame = false;
                break;
            }
        }
        if(lengthsthesame == true)
        {
            cout << "All lengths are THE SAME" << endl;
            allcorrect = true;
        }
        else
        {
            cout << "NOT all the lenghts are the same" << endl;
            allcorrect = false;
        }
    }
    else
    {
        cout << "Number of positions and number of reads are NOT THE SAME" << endl;
        numberthesame = false;
        allcorrect = false;
    }


    return allcorrect;
}

bool checkNumbersOfReadsDNA(vector<pair<int, int>>& positions, string sunseq)
{
    bool allcorrect = false;
    bool numberthesame = false;
    bool lengthsthesame = false;
    if(positions.size() == 1)
    {
        cout << "Number of positions and number of reads are THE SAME" << endl;
        numberthesame = true;
        cout << "and" << endl;

        vector<pair<int, int>>::iterator positionsiter = positions.begin();

        if((positionsiter->second - positionsiter->first + 1) == sunseq.length())
        {
            lengthsthesame = true;
        }
        else
        {
            lengthsthesame = false;
        }
        if(lengthsthesame == true)
        {
            cout << "All lengths are THE SAME" << endl;
            allcorrect = true;
        }
        else
        {
            cout << "NOT all the lenghts are the same" << endl;
            allcorrect = false;
        }
    }
    else
    {
        cout << "Number of positions and number of reads are NOT THE SAME" << endl;
        numberthesame = false;
        allcorrect = false;
    }


    return allcorrect;
}

// takes set of all needed positions and returns unique positions for cutting
map<int, int> getUniquePositions()
{
    if(whatShouldBeIncluded.size() == 0)
        return map<int, int>();

    map<int, int> uniqueparts;
    map<int, int>::iterator UPiter;
    vector<pair<int, int>>::iterator WSBIiter;

    cout << "Unchanged positions:" << endl;
    for(WSBIiter = whatShouldBeIncluded.begin(); WSBIiter != whatShouldBeIncluded.end(); WSBIiter++)
        cout << WSBIiter->first << " " << WSBIiter->second<< " length: " <<
                WSBIiter->second - WSBIiter->first + 1  << endl;

    WSBIiter = whatShouldBeIncluded.begin();
    uniqueparts.insert(*WSBIiter);
    WSBIiter++;

    for(; WSBIiter != whatShouldBeIncluded.end(); WSBIiter++)
    {
        UPiter = uniqueparts.end();
        UPiter--;
        if(WSBIiter->first <= UPiter->second)
        {
            // если пересекаются
            if(WSBIiter->second <= UPiter->second)
            {
                // если полностью перекрывается
                continue;
            }
            else
            {
                // если только частично (то есть правая часть вылезает)
                UPiter->second = WSBIiter->second;
            }
        }
        else
        {
            // если не пересекаются
            uniqueparts.insert(make_pair(WSBIiter->first, WSBIiter->second));
        }
    }
    cout << "Changed positions:" << endl;
    for(UPiter = uniqueparts.begin(); UPiter != uniqueparts.end(); UPiter++)
        cout << UPiter->first << " " << UPiter->second << " length: " <<
                UPiter->second - UPiter->first + 1 << endl;

    return uniqueparts;
}

map<int, int> getUniquePositionsDNA()
{
    if(whatShouldBeIncludedDNA.size() == 0)
        return map<int, int>();

    map<int, int> uniqueparts;
    map<int, int>::iterator UPiter;
    vector<pair<int, int>>::iterator WSBIiter;

    cout << "Unchanged positions:" << endl;
    for(WSBIiter = whatShouldBeIncludedDNA.begin(); WSBIiter != whatShouldBeIncludedDNA.end(); WSBIiter++)
        cout << WSBIiter->first << " " << WSBIiter->second<< " length: " <<
                WSBIiter->second - WSBIiter->first + 1  << endl;

    WSBIiter = whatShouldBeIncludedDNA.begin();
    uniqueparts.insert(*WSBIiter);
    WSBIiter++;

    for(; WSBIiter != whatShouldBeIncludedDNA.end(); WSBIiter++)
    {
        UPiter = uniqueparts.end();
        UPiter--;
        if(WSBIiter->first <= UPiter->second)
        {
            // если пересекаются
            if(WSBIiter->second <= UPiter->second)
            {
                // если полностью перекрывается
                continue;
            }
            else
            {
                // если только частично (то есть правая часть вылезает)
                UPiter->second = WSBIiter->second;
            }
        }
        else
        {
            // если не пересекаются
            uniqueparts.insert(make_pair(WSBIiter->first, WSBIiter->second));
        }
    }
    cout << "Changed positions:" << endl;
    for(UPiter = uniqueparts.begin(); UPiter != uniqueparts.end(); UPiter++)
        cout << UPiter->first << " " << UPiter->second << " length: " <<
                UPiter->second - UPiter->first + 1 << endl;

    return uniqueparts;
}

// takes input dna string and positions of this string that should remain and returns new string
string cutitoff(string DnaSequence, map<int, int> uniquePositions)
{
    if(uniquePositions.size() == 0)
        return DnaSequence;

    map<int, int>::iterator UPiter;
    string outputSequence = "";

    for(UPiter = uniquePositions.begin(); UPiter != uniquePositions.end(); UPiter++)
        outputSequence.append(DnaSequence.substr(UPiter->first, UPiter->second-UPiter->first+1));

    cout << "Before cutting: " << endl << DnaSequence << endl << "After cutting: " << endl << outputSequence << endl;

    return outputSequence;
}

string cutitoffDNA(string DnaSequence, map<int, int> uniquePositions)
{
    if(uniquePositions.size() == 0)
        return DnaSequence;

    map<int, int>::iterator UPiter;
    string outputSequence = "";

    for(UPiter = uniquePositions.begin(); UPiter != uniquePositions.end(); UPiter++)
        outputSequence.append(DnaSequence.substr(UPiter->first, UPiter->second-UPiter->first+1));

    cout << "Before cutting: " << endl << DnaSequence << endl << "After cutting: " << endl << outputSequence << endl;

    return outputSequence;
}

/*string throwaway(string sequence, vector<string> reads)
{
    string output = sequence;

    // найти все риды. если рид не разбит, удалить его из списка и пока забыть о нем
    // если рид разбит, найти все его координаты и выкинуть лишнее

    vector<string>::iterator readsiter;
    whatShouldBeIncluded.clear();
    for(readsiter = reads.begin(); readsiter != reads.end(); readsiter++)
    {
        findAllSubs(*readsiter, "", 0, DnaSequence);
    }

    multimap<int, int>::iterator WSBIiter = whatShouldBeIncluded.begin();
    readsiter = reads.begin();
    while(readsiter != reads.end() && WSBIiter != whatShouldBeIncluded.end())
    {
        if((WSBIiter->first - WSBIiter->second + 1) == readsiter->length())
        {
            readsiter = reads.erase(readsiter);
            WSBIiter = whatShouldBeIncluded.erase(WSBIiter);
            if(readsiter == reads.end() || WSBIiter == whatShouldBeIncluded.end())
                break;
        }
        else
        {
            vector<int> positionsofTHERead;
        }

    }

    return output;
}*/

//takes input dna string and returns the perfect dna string after splicing
bool makeItPerfect(string DnaSequence, vector<string> reads)
{
    whatShouldBeIncluded.clear();
    vector<string>::iterator readsiter;

    for(readsiter = reads.begin(); readsiter != reads.end(); readsiter++)
    {
        findAllSubs(*readsiter, "", 0, DnaSequence);
    }

    cout << "Found not unique positions:" << endl;
    vector<pair<int, int>>::iterator WSBIiter;
    for(WSBIiter = whatShouldBeIncluded.begin(); WSBIiter != whatShouldBeIncluded.end(); WSBIiter++)
        cout << WSBIiter->first << " " << WSBIiter->second << endl;

   // return checkNumbersOfReads(whatShouldBeIncluded, reads);
    if(checkNumbersOfReads(whatShouldBeIncluded, reads)) // если все прекрасно, количество позиций и чтений совпадают
        return 1;
    else // если нет
    {
       return makeItPerfect(cutitoff(DnaSequence, getUniquePositions()), reads);
    }
}

bool makeItPerfectDNA(string DnaSequence, string subseq)
{
    whatShouldBeIncludedDNA.clear();

    findAllSubsDNA(subseq, "", 0, DnaSequence);

    cout << "Found not unique positions:" << endl;
    vector<pair<int, int>>::iterator WSBIiter;
    for(WSBIiter = whatShouldBeIncludedDNA.begin(); WSBIiter != whatShouldBeIncludedDNA.end(); WSBIiter++)
        cout << WSBIiter->first << " " << WSBIiter->second << endl;

    //return checkNumbersOfReadsDNA(whatShouldBeIncludedDNA, subseq);
    if(checkNumbersOfReadsDNA(whatShouldBeIncludedDNA, subseq)) // если все прекрасно, количество позиций и чтений совпадают
        return true;
    else // если нет
    {
        makeItPerfectDNA(cutitoffDNA(DnaSequence, getUniquePositionsDNA()), subseq);
    }
}

bool isSubSeqOf(string seq, string subSeq)
{
    bool result = false;

    findAllSubsDNA(subSeq, "", 0, seq);
    seq = cutitoffDNA(seq, getUniquePositionsDNA());

    return seq == subSeq;
}

bool isSubSequenceChar(char str1[], char str2[], int m, int n)
{
    // Base Cases
    if (m == 0) return true;
    if (n == 0) return false;

    // If last characters of two strings are matching
    if (str1[m-1] == str2[n-1])
        return isSubSequenceChar(str1, str2, m-1, n-1);

    // If last characters are not matching
    return isSubSequenceChar(str1, str2, m, n-1);
}

bool isSubSequence(string str1, string str2, int m, int n)
{
    // int m = str1.length();
    //int n = str2.length();
    // Base Cases
    if (m == 0) return true;
    if (n == 0) return false;

    // If last characters of two strings are matching
    if (str1[m-1] == str2[n-1])
        return isSubSequence(str1, str2, m-1, n-1);

    // If last characters are not matching
    return isSubSequence(str1, str2, m, n-1);
}

int main()
{
    string OriginalDna;
    string DnaSequence;

    ifstream source("C:\\Users\\Ogrigorieva\\stuff\\BioinformaticsContest\\build-lastlittle-Desktop_Qt_5_7_1_MinGW_32bit-Debug\\debug\\3.txt");

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

    cout << DnaSequence << endl;

    vector<string>::iterator readsiter;

    int i = 0;
    for(readsiter = reads.begin(); readsiter != reads.end(); readsiter++)
    {
        cout << "#" << i++ << ": ";
        cout << *readsiter << " " << "length: " << readsiter->length() << endl;
    }

   // ifstream dnas("sequences.txt");
    //getline(dnas, DnaSequence);

    /// вот тут начинается цирк с огнями

    cout << makeItPerfect(DnaSequence, reads);


    //cout << makeItPerfect(DnaSequence, reads);
    /*&& !isSubSequence(DnaSequence, OriginalDna, DnaSequence.length(), OriginalDna.length())
                      && (isSubSeqOf(OriginalDna, DnaSequence))
                      && (!makeItPerfectDNA(OriginalDna, DnaSequence))
                      &&*/
  /*  while( getline(dnas, DnaSequence) )
    {
        if(!makeItPerfect(DnaSequence, reads))
        {
            final.clear();
        }
        else
        {
            if(isSubSequence(DnaSequence, OriginalDna, DnaSequence.length(), OriginalDna.length()))
            {
                cout << DnaSequence << endl;
                ofstream fout("answer.txt");

                fout << DnaSequence << endl;

                vector<int>::iterator VIiter;

                for(VIiter = final.begin(); VIiter != final.end(); VIiter++)
                    fout << *VIiter << endl;
                cout << "1 - continue, 0 - break" << endl;
                int answer;
                cin >> answer;
                if (answer == 1)
                    continue;
                if (answer == 0)
                    break;
            }
            else
                cout << "Not a subsequence" << endl;
        }
    }*/



    return 0;
}
