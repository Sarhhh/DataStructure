#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool test(string str)
{
    vector<char> stack;
    vector<char> queue;
    for (size_t i = 0; i < str.length(); i++)
    {
        stack.push_back(str[i]);
        queue.push_back(str[i]);
    }
    while (!stack.empty())
    {
        if (stack.back() != queue.front())
            return false;
        stack.pop_back();
        queue.erase(queue.begin());
    }
    return true;
}

int main()
{
    string s;
    cout << "请输入要判断回文串的字符串:" << endl;
    cin >> s;
    if (test(s))
    {
        cout << "是回文串" << endl;
    }
    else
    {
        cout << "不是回文串" << endl;
    }
    return 0;
}