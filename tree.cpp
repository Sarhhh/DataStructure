#include <stdio.h>
#include <vector>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
};

// 用vector模拟栈，先根序遍历二叉树
void preorder(TreeNode *t)
{
    if (t == NULL)
        return;

    std::vector<TreeNode *> st; // 用vector当栈用
    TreeNode *p = t;            // p是遍历指针

    while (p != NULL || !st.empty())
    {
        // 一直往左走，沿途访问节点并把右子树入栈
        while (p != NULL)
        {
            printf("%d ", p->val);
            if (p->right != NULL)
            {
                st.push_back(p->right);
            }
            p = p->left;
        }

        // 左子树走到头了，出栈取下一个右子树根节点
        if (!st.empty())
        {
            p = st.back();
            st.pop_back();
        }
    }
}

void inorder(TreeNode *t)
{
    if (t == NULL)
        return;

    std::vector<TreeNode *> st; // 用vector当栈用
    TreeNode *p = t;            // p是遍历指针

    while (p != NULL || !st.empty())
    {
        // 一直往左走，把沿途节点入栈
        while (p != NULL)
        {
            st.push_back(p);
            p = p->left;
        }

        // 左子树走到头了，出栈访问节点并转向右子树
        if (!st.empty())
        {
            p = st.back();
            st.pop_back();
            printf("%d ", p->val);
            p = p->right;
        }
    }
}

void postorder(TreeNode *t)
{
    if (t == NULL)
        return;
    std::vector<TreeNode *> st; // 用vector当栈用
    TreeNode *p = t;            // p是遍历指针
    TreeNode *lastVisited = NULL; // 记录上一个访问过的节点

    while (p != NULL || !st.empty())
    {
        // 一直往左走，把沿途节点入栈
        while (p != NULL)
        {
            st.push_back(p);
            p = p->left;
        }

        // 左子树走到头了，出栈访问节点并转向右子树
        if (!st.empty())
        {
            p = st.back();
            st.pop_back();
            if (p->right != NULL && p->right != last)
            {

                p = p->right;
            }
            else
            {
                printf("%d ", p->val);
                p = st.back();
                st.pop_back();
            }
        }
    }
}

int main()
{
    // 手动构造二叉树
    //         1
    //       /   \
    //      2     3
    //     / \   / \
    //    4   5 6   7
    TreeNode n1, n2, n3, n4, n5, n6, n7;
    n1.val = 1;
    n1.left = &n2;
    n1.right = &n3;
    n2.val = 2;
    n2.left = &n4;
    n2.right = &n5;
    n3.val = 3;
    n3.left = &n6;
    n3.right = &n7;
    n4.val = 4;
    n4.left = NULL;
    n4.right = NULL;
    n5.val = 5;
    n5.left = NULL;
    n5.right = NULL;
    n6.val = 6;
    n6.left = NULL;
    n6.right = NULL;
    n7.val = 7;
    n7.left = NULL;
    n7.right = NULL;

    printf("先根序遍历结果: ");
    preorder(&n1);
    printf("\n");

    printf("中根序遍历结果: ");
    inorder(&n1);
    printf("\n");

    printf("后根序遍历结果: ");
    postorder(&n1);
    printf("\n");

    return 0;
}
