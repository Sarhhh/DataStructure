#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> sort(vector<int> Nums) // 使用两个队列进行排序
{
    vector<int> a1;
    vector<int> a2;
    vector<int> *p1 = &a1;
    vector<int> *p2 = &a2;
    while (!Nums.empty())
    {
        if (p1->empty() || Nums.back() >= p1->back())
        {
            p1->push_back(Nums.back());
            Nums.pop_back();
        }
        else
        {
            while (Nums.back() >= p1->front())
            {
                p2->push_back(p1->front());
                p1->erase(p1->begin());
            }

            p2->push_back(Nums.back());
            Nums.pop_back();

            while (!p1->empty())
            {
                p2->push_back(p1->front());
                p1->erase(p1->begin());
            }
            vector<int> *p3;
            p3 = p1;
            p1 = p2;
            p2 = p3;
        }
    }
    return vector<int>(*p1);
}

vector<int> sort2(vector<int> Nums) // 使用一个队列进行循环插入排序
{
    vector<int> a;
    int count = 0;
    while (!Nums.empty())
    {
        if (a.empty() || Nums.back() >= a.back())
        {
            a.push_back(Nums.back());
            Nums.pop_back();
            count++;
        }
        else
        {
            int n = count;
            while (Nums.back() >= a.front())
            {
                a.push_back(a.front());
                a.erase(a.begin());
                n--;
            }
            a.push_back(Nums.back());
            Nums.pop_back();
            count++;
            for (int i = 0; i < n; i++)
            {
                a.push_back(a.front());
                a.erase(a.begin());
            }
        }
    }
    return a;
}

int main()
{

    vector<int> stack = {3, 26, 35, 23, 56, 7, 2, 95, 2, 8, 9, 1, 0, 4, 5, 6, 7, 8, 9};
    // vector<int> sortedStack = sort(stack);
    vector<int> sortedStack = sort2(stack);
    cout << "原始队列：";
    for (int num : stack)
    {
        cout << num << " ";
    }
    cout << endl;
    cout << "排序后的队列：";
    for (int num : sortedStack)
    {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}