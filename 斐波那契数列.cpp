#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

double digui(int n)
{
    if ( n == 0)
    {
        return 0;
    }
    else if (n == 1)
    {
        return 1;
    }
    else
    {
        return digui(n - 1) + digui(n - 2);
    }
}

double xunhuan(int n)
{
    double a = 0,b=1,c;
    if (n == 0)
    {
        return 0;
    }
    else if (n == 1)
    {
        return 1;
    }
    else
    {
        for (; n> 1; n--)
        {
            c = a + b;
            a = b;
            b = c;
        }
        return c;
    }

}

int main()
{
    int n;
    cout << "请输入一个整数：";
    cin >> n;

    clock_t start,end;
    start=clock();
    cout << "递归实现的斐波那契数列第 " << n << " 项是：" << digui(n) << endl;
    end = clock();
    cout << "耗时:" << double(end - start) * 1000.0 / CLOCKS_PER_SEC << endl;
    start=clock();
    cout << "循环实现的斐波那契数列第 " << n << " 项是：" << xunhuan(n) << endl;
    end = clock();
    cout << "耗时:" << double(end - start) * 1000.0 / CLOCKS_PER_SEC << endl;

    return 0;
}