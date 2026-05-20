#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
    string mergeAlternately(string word1, string word2)
    {
        int m = word1.length(), n = word2.length();
        int i = 0, j = 0;
        string s;
        while (i < m && j < n)
        {
            s.push_back(word1[i]);
            i++;
            s.push_back(word2[j]);
            j++;
        }

        if (i < m)
        {
            s.append(word1.substr(i));
            // s += word1.substr(i);
        }

        if (j < n)
        {
            s.append(word2.substr(j));
            // s += word2.substr(j);
        }
        return s;
    }
};

int main()
{
    string word1 = "awda";
    string word2 = "gdfgwa";
    Solution Solution;
    cout << Solution.mergeAlternately(word1, word2) << endl;
}