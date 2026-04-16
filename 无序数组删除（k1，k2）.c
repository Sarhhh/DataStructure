#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
int main() {
    srand((unsigned int)time(NULL));
    int L[20];
    printf("随机生成的20个数为：\n");
    for (int i = 0; i < 20; i++) {
        L[i] = rand() % 100 + 1;
        printf("%d ", L[i]);
    }

    int k1,k2;
    printf("\n请输入k1和k2的值：");
    scanf("%d %d", &k1, &k2);

    if (k1 > k2) {
        printf("k1应该小于或等于k2，自动交换k1和k2的值...\n");
        int temp = k1;
        k1 = k2;
        k2 = temp;
    }

    
    int count = 0;

    for (int i = 0; i < 20; i++) {
        if (L[i] >= k1 && L[i] <= k2) {
            count++;
        }
        else{
            L[i-count] = L[i];
        }
    }
    
    printf("删除k1和k2之间的数后，剩余的数为：\n");
    for (int i = 0; i < 20 - count; i++) {
        printf("%d ", L[i]);
    }
    return 0;
}