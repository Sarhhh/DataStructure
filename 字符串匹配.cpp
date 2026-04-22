#include <iostream>
#include <vector>
#include <string>
using namespace std;

int test(string T,string P)
{
    for(int i =0;i<=T.length()-P.length();i++)
    {
        for(int j=0;j<P.length();j++)
        {
            if(T[i]==P[j])
            {
                i++;
            }
            else{
                i-=j;
                break;
            }
        }
        return(i-P.length());
    }
    return -1;
}

int main() {
    string text, pattern;
    cout << "请输入主串：";
    cin >> text;
    cout << "请输入模式串：";
    cin >> pattern;
    int pos = test(text, pattern);
    if (pos != -1) {
        cout << "匹配成功，模式串首次出现位置为：" << pos << endl;
    } else {
        cout << "匹配失败，主串中未找到模式串。" << endl;
    }
    return 0;
}