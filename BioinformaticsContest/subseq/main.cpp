#include <iostream>

using namespace std;
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
int main(int argc, char *argv[])
{
    string sub = "abcde";
    string seq = "aaabbbcccdddeee";
    cout << isSubSequence(sub, seq, sub.length(), seq.length()) << endl;
    return 0;
}
