#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool test(string str)
{
    vector<char> stack;
    for(size_t i = 0; i < str.length(); i++) //length()返回的是size_t类型，编译器一直warming，所以改成size_t
    {
        char ch = str[i];
        switch (ch)
        {
        case '(':
        case '{':
        case '[':
            stack.push_back(ch);
            break;
        case ')':
            if(stack.empty() || stack.back() != '(')
                return false;
            stack.pop_back();
            break;
        case '}':
            if(stack.empty() || stack.back() != '{')
                return false;
            stack.pop_back();
            break;
        case ']':
            if(stack.empty() || stack.back() != '[')
                return false;
            stack.pop_back();
            break;
        default:
            break;
        }
    }
    return stack.empty();
}

int main()
{
    string str;
    cout << "请输入一个字符串，程序将判断其中的括号是否匹配：" << endl;
    getline(cin, str);
    if (test(str))
    {
        cout << "括号匹配" << endl;
    }
    else
    {
        cout << "括号不匹配" << endl;
    }
    return 0;
}