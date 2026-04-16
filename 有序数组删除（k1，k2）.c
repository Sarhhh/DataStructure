#include <stdio.h>

int main()
{
    int a[] = {4, 17, 22, 27, 42, 56, 63, 78, 85, 91}; // 定义一个整数非递减数组
    int n = sizeof(a) / sizeof(a[0]);                  // 计算数组元素的数量
    printf("原数组为：\n");                            // 输出原数组
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

    int k1, k2;
    printf("\n请输入k1和k2的值：\n"); 
    scanf("%d %d", &k1, &k2);
    if (k1 > k2)
    { // 保证k1小于或等于k2，如果输入的k1大于k2，则交换它们的值
        printf("k1应该小于或等于k2，自动交换k1和k2的值...\n");
        int temp = k1;
        k1 = k2;
        k2 = temp;
    }

    int l = 0, r = n - 1; // 定义需要删除的数的左右边界,在后续遍历后,l指向第一个大于等于k1的数，r指向最后一个小于等于k2的数
    for (; l < n && a[l] < k1; l++)
    { // 从左向右遍历数组，找到第一个大于等于k1的数的位置，即l的值为第一个大于等于k1的数的下标
    }
    for (; r >= 0 && a[r] > k2; r--)
    { // 从右向左遍历数组，找到最后一个小于等于k2的数的位置，即r的值为最后一个小于等于k2的数的下标
    }

    int index = r - l + 1; // 计算k1和k2之间的数的个数,即需要删除的数的个数
    for (++r; r < n; r++)
    { // 将数组中k1和k2之间的数删除，即将k2右边的数向左移动index个位置
        a[r - index] = a[r];
    }

    n = n - index;                                  // 更新数组长度
    printf("删除k1和k2之间的数后，剩余的数为：\n"); // 输出删除k1和k2之间的数后的数组
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

    return 0;
}