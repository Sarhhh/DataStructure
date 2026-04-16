#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

double eval(double a, double b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    default:
        throw invalid_argument("Invalid operator");
    }
}

enum class OperatorPriority
{
    LPAREN = 0,  // '('
    ADD = 1,     // '+', '-'
    MUL = 2,     // '*', '/'
    RPAREN = 3,  // ')'
    INVALID = -1 // 非法字符
};

OperatorPriority getOperatorPriority(char op)
{
    switch (op)
    {
    case '(':
        return OperatorPriority::LPAREN;
    case '+':
    case '-':
        return OperatorPriority::ADD;
    case '*':
    case '/':
        return OperatorPriority::MUL;
    case ')':
        return OperatorPriority::RPAREN;
    default:
        return OperatorPriority::INVALID;
    }
}

double caluculator(string s)
{
    vector<double> stack_num;
    vector<char> stack_op;
    stringstream ss(s);
    while (ss && ss.peek() != EOF)
    {
        if (isspace(ss.peek()))
        {
            ss.get(); // 把空格单独取出来
            continue;
        }

        if (isdigit(ss.peek()))
        {
            double num;
            ss >> num;
            stack_num.push_back(num);
        }
        else
        {
            char op;
            ss >> op;
            if (getOperatorPriority(op) == OperatorPriority::INVALID)
            {
                throw invalid_argument("Invalid operator: " + string(1, op));
            }

            bool test = stack_num.empty() || (!stack_op.empty() && stack_op.back() != '(');
            if (test)
            {
                if (op == '*' || op == '/')
                {
                    throw invalid_argument("Expression cannot start with '*' or '/'");
                }
                if (op == '+' || op == '-')
                {
                    stack_num.push_back(0);
                    stack_op.push_back(op);
                }
            }

            if (op == '(')
            {
                stack_op.push_back(op);
            }
            else if (op == ')')
            {
                while (!stack_op.empty() && stack_op.back() != '(')
                {
                    double num1 = stack_num.back();
                    stack_num.pop_back();
                    double num2 = stack_num.back();
                    stack_num.pop_back();
                    char oper = stack_op.back();
                    stack_op.pop_back();
                    double result = eval(num2, num1, oper);
                    stack_num.push_back(result);
                }
                if (!stack_op.empty() && stack_op.back() == '(')
                {
                    stack_op.pop_back();
                }
                else
                {
                    throw invalid_argument("Mismatched parentheses");
                }
            }
            else
            {
                while (!stack_op.empty() && getOperatorPriority(op) <= getOperatorPriority(stack_op.back()))
                {
                    double num1 = stack_num.back();
                    stack_num.pop_back();
                    double num2 = stack_num.back();
                    stack_num.pop_back();
                    char oper = stack_op.back();
                    stack_op.pop_back();
                    double result = eval(num2, num1, oper);
                    stack_num.push_back(result);
                }
                stack_op.push_back(op);
            }
        }
    }
    while (!stack_op.empty())
    {
        double num1 = stack_num.back();
        stack_num.pop_back();
        double num2 = stack_num.back();
        stack_num.pop_back();
        char oper = stack_op.back();
        stack_op.pop_back();
        double result = eval(num2, num1, oper);
        stack_num.push_back(result);
    }
    return stack_num.back();
}

int main()
{
    while (true)
    {
        string str;
        cout << "请输入表达式:" << endl;
        getline(cin, str);
        if (str == "exit")
        {
            break;
        }
        else
        {
            cout << "表达式的值是:" << caluculator(str) << endl;
        }
    }
    return 0;
}