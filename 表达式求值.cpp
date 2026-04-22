#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Node
{
public:
    virtual ~Node() {};
};

class NumNode : public Node
{
public:
    double val;
    NumNode(string s) : val(stod(s)) {};
};

class OpNode : public Node
{
public:
    char op;
};




int main()
{
    string str;
    cout << "请输入一个表达式：";
    getline(cin, str);
    return 0;
}


// vector<Node *> toPostfixExpression(string str)
// {
//     vector<Node *> PostfixExpression;
//     vector<char> OpStack;
//     vector<double> NumStack;

//     for (size_t i = 0; i < str.length(); i++)
//     {
//         string num;
//         for (size_t j = 0; j + i < str.length(); j++)
//         {
//             int PointCount = 0;
//             if ((str[i + j] >= '0' && str[i + j] <= '9') || (str[i + j] == '.' && PointCount == 0))
//             {
//                 num.push_back(str[i + j]);
//                 if (str[i + j] == '.')
//                 {
//                     PointCount++;
//                 }
//             }
//             else
//             {
//                 NumStack.push_back(stod(num));
//                 i += j;
//                 break;
//             }
//             if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '(' || str[i] == ')')
//             {
//                 for (size_t j = 0; j + i < str.length(); j++)
//                 {
//                     if (str[i] == '(')
//                     {
//                         OpStack.push_back(str[i]);
//                         break;
//                     }
//                     else if (str[i] == '+' || str[i] == '-')
//                     {
//                         if (OpStack.empty() ||)
//                     }
//                 }
//             }
//             else
//             {
//                 throw("错误");
//             }
//         }
//     }
// }
