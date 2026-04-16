#include <iostream>
#include <vector>

using namespace std;

vector<int> a(8, -1);

void show(vector<int> a)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < a[i]; j++)
        {
            cout << "* ";
        }
        cout << 'Q' << " ";
        for (int j = a[i] + 1; j < 8; j++)
        {
            cout << "* ";
        }
        cout << endl;
    }
    cout << endl;
}

int panduan(int row, int cow)
{
    for (int i = 0; i < row; i++)
    {
        if (cow == a[i] || (cow - a[i]) == (row - i) || (cow - a[i] == (i - row)))
        {
            return 0;
        }
        else
        {
        }
    }
    return 1;
}

void digui(int r)
{
    if (r == 8)
    {
        show(a);
        return;
    }
    for (int i = 0; i < 8; i++)
    {
        if (panduan(r, i))
        {
            a[r] = i;
            digui(r + 1);
            a[r] = -1;
        }
    }
}

int main()
{
    digui(0);
}
