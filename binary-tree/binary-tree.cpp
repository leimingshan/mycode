#include <iostream>
#include <cstdlib>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

//Define binary tree node
struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
};

//hash for inorder traverse
int map_index[256];
void MapToIndices(int inorder[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        map_index[inorder[i]] = i;
}

//Build BinaryTree
//pre数组为先序遍历序列，注意在递归过程中pre起始位置是变化的。n为结点数目，offset为子树在中序中对应的开始位置。
struct TreeNode* BuildInorderPreorder(int pre[], int n, int offset)
{
    if (n == 0) return NULL;
    int rootVal = pre[0];
    int i = map_index[rootVal] - offset;

    struct TreeNode* root = new (struct TreeNode);
    root->value = rootVal;
    root->left = BuildInorderPreorder(pre+1, i, offset);
    root->right = BuildInorderPreorder(pre+i+1, n-i-1, offset+i+1);
    return root;
}
//根据后序遍历和中序遍历构建二叉树
struct TreeNode *BuildInorderPostorder(int post[], int n, int offset)
{
    if (n == 0) return NULL;
    int rootVal = post[n-1];
    int i = map_index[rootVal] - offset;  // the divider's index

    struct TreeNode* root = new (struct TreeNode);
    root->left = BuildInorderPostorder(post, i, offset);
    root->right = BuildInorderPostorder(post+i, n-i-1, offset+i+1);
    return root;
}

//Traverse
//PreOrder
void PreOrder(TreeNode *root)
{
    if (root == NULL)
        return;
    cout << root->value << ' ';
    PreOrder(root->left);
    PreOrder(root->right);
}

void PreOrderNonRecursive(TreeNode *root)
{
    //use a stack to implement preorder traverse of nonrecursive
    stack<TreeNode *> s;
    s.push(root);

    while (!s.empty()) {
        TreeNode *temp = s.top();
        //visit the node
        cout << temp->value << ' ';
        s.pop();
        //watch out!!! push right first and then left
        if (temp->right != NULL)
            s.push(temp->right);
        if (temp->left != NULL)
            s.push(temp->left);
    }
    cout << endl;
    return;
}

//InOrder
void InOrder(TreeNode *root)
{
    if (root == NULL)
        return;
    InOrder(root->left);
    cout << root->value << ' ';
    InOrder(root->right);
}

void InOrderNonRecursive(TreeNode *root)
{
    if (root == NULL)
        return;
    stack<TreeNode *> s;

    while (root != NULL) {
        s.push(root);
        root = root->left;
    }

    while (!s.empty()) {
        root = s.top();
        s.pop();
        cout << root->value << ' ';
        root = root->right;

        while (root != NULL) {
            s.push(root);
            root = root->left;
        }
    }
    cout << endl;
}

//PostOrder
void PostOrder(TreeNode *root)
{
    if (root == NULL)
        return;
    PostOrder(root->left);
    PostOrder(root->right);
    cout << root->value << ' ';
}

void PostOrderNonRecursive(TreeNode *root)
{
    //this will be very easy if you use 2 stacks
    if (!root) 
        return;

    stack<TreeNode*> s, output;
    s.push(root);
    while (!s.empty()) {
        TreeNode *curr = s.top();
        output.push(curr);
        s.pop();
        if (curr->left)
            s.push(curr->left);
        if (curr->right)
            s.push(curr->right);
    }
    
    while (!output.empty()) {
        cout << output.top()->value << " ";
        output.pop();
    }
    cout << endl;
}

//LevelOrder
//Print levels together
void LevelOrder(TreeNode *root)
{
    if (root == NULL)
        return;

    TreeNode *node;
    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty()) {
        node = q.front();
        q.pop();
        cout << node->value << ' '; //Visit(node);

        if (node->left != NULL)
            q.push(node->left);
        if (node->right != NULL)
            q.push(node->right);
    }
    cout << endl;
}

void LevelOrderInLine(TreeNode *root)
{
    if (root == NULL)
        return;

    queue<TreeNode *> q;
    TreeNode *end = root;
    while (true) {
        if (root->left != NULL)
            q.push(root->left);
        if (root->right != NULL)
            q.push(root->right);

        cout << root->value << ' ';
        if (root == end) {
            cout << endl;
            if (q.empty())
                break;
            end = q.back();
        }
        root = q.front();
        q.pop();
    }
}

//Get binary tree node number
int GetNodeNum(TreeNode *root)
{
    if (root == NULL)
        return 0;

    return GetNodeNum(root->left) + GetNodeNum(root->right) + 1;
}

//Get tree depth
int GetDepth(TreeNode *root)
{
    if (root == NULL)
        return 0;
    int ldepth = GetDepth(root->left);
    int rdepth = GetDepth(root->right);

    return ldepth > rdepth ? (ldepth + 1) : (rdepth + 1);
}

//Get Kth level node number
int GetKthLevelNodeNum(TreeNode *root, int k)
{
    if (root == NULL || k < 1)
        return 0;
    if (k == 1)
        return 1;
    int numLeft = GetKthLevelNodeNum(root->left, k - 1);
    int numRight = GetKthLevelNodeNum(root->right, k - 1);
    return numLeft + numRight;
}

//Get leaf node number
int GetLeafNodeNum(TreeNode *root)
{
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    return GetLeafNodeNum(root->left) + GetLeafNodeNum(root->right);
}

//Compare two binary trees if they have the same structure(ignor value)
bool cmpTreeStructure(TreeNode *root1, TreeNode *root2)
{
    if (root1 == NULL && root2 == NULL)
        return true;
    else if (root1 == NULL || root2 == NULL)
        return false;

    return cmpTreeStructure(root1->left, root2->left) && cmpTreeStructure(root1->right, root2->right);
}

//This binary tree is an AVL tree or not
bool IsAVL(TreeNode *root, int &height)
{
    if (root == NULL) {
        height = 0;
        return true;
    }
    int leftHeight, rightHeight;
    bool leftRe = IsAVL(root->left, leftHeight);
    bool rightRe = IsAVL(root->right, rightHeight);

    if (leftRe && rightRe && abs(leftHeight - rightHeight) <= 1) {
        height = max(leftHeight, rightHeight) + 1;
        return true;
    } else {
        height = max(leftHeight, rightHeight) + 1;
        return false;
    }
}

//Get the mirror of the binary tree
TreeNode *Mirror(TreeNode *root)
{
    if (root == NULL)
        return NULL;
    TreeNode *left = Mirror(root->left);
    TreeNode *right = Mirror(root->right);
    root->left = right;
    root->right = left;
    return root;
}

//Lowest Common Ancestor of two different nodes
//1.The node can be its own parent
int lca(const TreeNode *root, const TreeNode *va, const TreeNode *vb, 
        const TreeNode *&result)
{
    const int N = 2;
    int left = root->left ? lca(root->left, va, vb, result) : 0;
    if (left == N)
        return N;

    int right = root->right ? lca(root->right, va, vb, result) : 0;
    if (right == N)
        return N;

    int mid = (root == va) + (root == vb);
    int ret = left + right + mid;
    if (ret == N)
        result = root;
    return ret;
}
//2. The node cannot be its own parent
int lca2(const TreeNode *root, const TreeNode *va, const TreeNode *vb,
         const TreeNode *parent, const TreeNode *&result)
{
    const int N = 2;
    int left = root->left ? lca2(root->left, va, vb, root, result) : 0;
    if (left == N)
        return N;

    int right = root->right ? lca2(root->right, va, vb, root, result) : 0;
    if (right == N)
        return N;

    int mid = (root == va) + (root == vb);
    int ret = left + right + mid;
    if (ret == N)
        result = (mid != 0 ? parent : root);
    return ret;
}

//Get the node path according to the given sum
//Use a deque to store current path
void GetNodePath(TreeNode *root, const int sum, int current_sum, deque<int> &dq)
{
    if (root == NULL) //Only check for the root of the tree
        return;
    current_sum += root->value;
    if (root->left == NULL && root->right == NULL) {
        if (sum != current_sum)
            return;
        else {
            //Print the node path
            deque<int>::iterator it = dq.begin();
            while (it != dq.end())
                cout << *it++ << ' ';
            cout << root->value << endl;
            return;
        }
    }
    dq.push_back(root->value);
    if (root->left)
        GetNodePath(root->left, sum, current_sum, dq);
    if (root->right)
        GetNodePath(root->right, sum, current_sum, dq);
    dq.pop_back();
    return;
}

void PrintNodePath(TreeNode *root, int sum)
{
    if (root == NULL)
        return;
    deque<int> dq;
    GetNodePath(root, sum, 0, dq);
}

//Test all of the functions above
int main()
{
    int pre[] = {7, 10, 4, 3, 1, 2, 8, 11};
    int in[] = {4, 10, 3, 1, 7, 11, 8, 2};
    int n = sizeof(in) / sizeof(in[0]);
    MapToIndices(in, n);

    struct TreeNode* root = BuildInorderPreorder(pre, n, 0);
    //Sample display
    cout << "The BinaryTree used in this program is:" << endl;
    cout << "              7    " << endl
         << "            /   \\ " << endl
         << "          10     2 " << endl
         << "          /\\    / " << endl
         << "         4 3   8 "   << endl
         << "            \\  /"   <<endl
         << "            1 11"  << endl;
    //Traverse
    cout << "PreOrder:" <<endl;
    PreOrder(root);
    cout << endl;
    PreOrderNonRecursive(root);

    cout << "InOrder:" <<endl;
    InOrder(root);
    cout << endl;
    InOrderNonRecursive(root);
    
    cout << "PostOrder:" <<endl;
    PostOrder(root);
    cout << endl;
    PostOrderNonRecursive(root);

    cout << "LevelOrder:" << endl;
    LevelOrder(root);
    cout << "LevelOrderInLine:" << endl;
    LevelOrderInLine(root);

    cout << "TotalNodeNum:" << endl << GetNodeNum(root) << endl;
    cout << "Depth:" << endl << GetDepth(root) << endl;
    cout << "3rd-level Node Num:" << endl << GetKthLevelNodeNum(root, 3) << endl;
    cout << "LeafNodeNum:" << endl << GetLeafNodeNum(root) << endl;
    int height = 0;
    cout << "IsAVL:" << endl << IsAVL(root, height) << endl;

    cout << "The Node Path of sum 28:" << endl;
    PrintNodePath(root, 28);
    
    return 0;
}