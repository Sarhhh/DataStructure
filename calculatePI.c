#include <stdio.h>
#include <math.h>

int main()
{
    double pi = 0.0;
    int n;
    printf("请输入迭代次数 n：");
    scanf("%d", &n);

    for (int k = 0; k < n; k++)
    {
        pi += (pow(-1, k) * (4.0 / (2 * k + 1)));
    }

    // int sign = 1;
    // for(int k = 0;k<n;k++)
    // {
    //     pi += (sign * (4.0 / (2 * k + 1)));
    //     sign = -sign;
    // }
    printf("π的近似值为: %.12f\n", pi);
    getchar(); // 等待用户输入以查看结果
    return 0;
}