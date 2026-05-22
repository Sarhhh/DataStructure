#include <iostream>
#include <vector>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
};

int Depth(TreeNode *root) // 层序遍历法
{
    if (root == NULL)
    {
        return 0;
    }
    int depth = 0;
    vector<TreeNode *> queue;
    queue.push_back(root);
    while (!queue.empty())
    {
        depth++;
        vector<TreeNode *> tmp;
        while (!queue.empty())
        {
            TreeNode *node = queue.front();
            queue.erase(queue.begin());
            if (node->left != NULL)
            {
                tmp.push_back(node->left);
            }
            if (node->right != NULL)
            {
                tmp.push_back(node->right);
            }
        }
        queue = tmp;
    }
    return depth;
}

int DepthRecursive(TreeNode *root) // 递归法
{
    if(root==NULL)
    {
        return 0;
    }
    else
    {
        return max(DepthRecursive(root->left), DepthRecursive(root->right)) + 1;
    }
}

int main()
{
    TreeNode n1, n2, n3, n4, n5, n6, n7, n8, n9;
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
    n4.left = &n8;
    n4.right = &n9;
    n5.val = 5;
    n5.left = NULL;
    n5.right = NULL;
    n6.val = 6;
    n6.left = NULL;
    n6.right = NULL;
    n7.val = 7;
    n7.left = NULL;
    n7.right = NULL;
    n8.val = 8;
    n8.left = NULL;
    n8.right = NULL;
    n9.val = 9;
    n9.left = NULL;
    n9.right = NULL;

    cout << "层序遍历计算出树的深度是：" << Depth(&n1) << endl;
    cout << "递归遍历计算出树的深度是：" << DepthRecursive(&n1)  << endl;
}