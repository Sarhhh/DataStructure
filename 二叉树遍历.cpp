#include <iostream>
#include <vector>

using namespace std;

struct TreeNode
{
    TreeNode *left;
    int val;
    TreeNode *right;
};

void preorder(TreeNode *t)
{
    vector<TreeNode *> stk;
    TreeNode *p = t;

    do
    {
        // p 不为空 → 访问根，右孩子入栈，往左走
        if (p != NULL)
        {
            cout << p->val << " ";
            if (p->right != NULL)
                stk.push_back(p->right);
            p = p->left;
        }
        else // p 为空 → 弹栈
        {
            p = stk.back();
            stk.pop_back();
        }
    } while (p != NULL || !stk.empty());
    cout << endl;
}

int main()
{
    // 手动构造二叉树
    //         1
    //       /   \
    //      2     3
    //     / \   / \
    //    4   5 6   7
    TreeNode n1, n2, n3,n4, n5, n6, n7;
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

    cout << "先序遍历: ";
    preorder(&n1);
    return 0;
}