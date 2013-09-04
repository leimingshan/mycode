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
int mapIndex[256];
void mapToIndices(int inorder[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        mapIndex[inorder[i]] = i;
}

//Build BinaryTree
//pre数组为先序遍历序列，注意在递归过程中pre起始位置是变化的。n为结点数目，offset为子树在中序中对应的开始位置。
struct TreeNode* buildInorderPreorder(int pre[], int n, int offset)
{
    if (n == 0) return NULL;
    int rootVal = pre[0];
    int i = mapIndex[rootVal] - offset;

    struct TreeNode* root = new (struct TreeNode);
    root->value = rootVal;
    root->left = buildInorderPreorder(pre+1, i, offset);
    root->right = buildInorderPreorder(pre+i+1, n-i-1, offset+i+1);
    return root;
}
//根据后序遍历和中序遍历构建二叉树
struct TreeNode *buildInorderPostorder(int post[], int n, int offset)
{
    if (n == 0) return NULL;
    int rootVal = post[n-1];
    int i = mapIndex[rootVal] - offset;  // the divider's index

    struct TreeNode* root = new (struct TreeNode);
    root->left = buildInorderPostorder(post, i, offset);
    root->right = buildInorderPostorder(post+i, n-i-1, offset+i+1);
    return root;
}

//Traverse
//PreOrder
void preOrder(TreeNode *root)
{
    if (root == NULL)
        return;
    cout << root->value << ' ';
    preOrder(root->left);
    preOrder(root->right);
}

void preOrderNonRecursive(TreeNode *root)
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
void inOrder(TreeNode *root)
{
    if (root == NULL)
        return;
    inOrder(root->left);
    cout << root->value << ' ';
    inOrder(root->right);
}

void inOrderNonRecursive(TreeNode *root)
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
void postOrder(TreeNode *root)
{
    if (root == NULL)
        return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->value << ' ';
}

void postOrderNonRecursive(TreeNode *root)
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
void levelOrder(TreeNode *root)
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

void levelOrderInLine(TreeNode *root)
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
int getNodeNum(TreeNode *root)
{
    if (root == NULL)
        return 0;

    return getNodeNum(root->left) + getNodeNum(root->right) + 1;
}

//Get tree depth
int getDepth(TreeNode *root)
{
    if (root == NULL)
        return 0;
    int ldepth = getDepth(root->left);
    int rdepth = getDepth(root->right);

    return ldepth > rdepth ? (ldepth + 1) : (rdepth + 1);
}

//Get Kth level node number
int getKthLevelNodeNum(TreeNode *root, int k)
{
    if (root == NULL || k < 1)
        return 0;
    if (k == 1)
        return 1;
    int numLeft = getKthLevelNodeNum(root->left, k - 1);
    int numRight = getKthLevelNodeNum(root->right, k - 1);
    return numLeft + numRight;
}

//Get leaf node number
int getLeafNodeNum(TreeNode *root)
{
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    return getLeafNodeNum(root->left) + getLeafNodeNum(root->right);
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
bool isAVL(TreeNode *root, int &height)
{
    if (root == NULL) {
        height = 0;
        return true;
    }
    int leftHeight, rightHeight;
    bool leftRe = isAVL(root->left, leftHeight);
    bool rightRe = isAVL(root->right, rightHeight);

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
    int left = root->left ? lca(root->left, va, vb, root, result) : 0;
    if (left == N)
        return N;

    int right = root->right ? lca(root->right, va, vb, root, result) : 0;
    if (right == N)
        return N;

    int mid = (root == va) + (root == vb);
    int ret = left + right + mid;
    if (ret == N)
        result = (mid != 0 ? parent : root);
    return ret;
}

//Test all of the functions above
int main()
{
    int pre[] = {7, 10, 4, 3, 1, 2, 8, 11};
    int in[] = {4, 10, 3, 1, 7, 11, 8, 2};
    int n = sizeof(in) / sizeof(in[0]);
    mapToIndices(in, n);

    struct TreeNode* root = buildInorderPreorder(pre, n, 0);
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
    preOrder(root);
    cout << endl;
    preOrderNonRecursive(root);

    cout << "InOrder:" <<endl;
    inOrder(root);
    cout << endl;
    inOrderNonRecursive(root);
    
    cout << "PostOrder:" <<endl;
    postOrder(root);
    cout << endl;
    postOrderNonRecursive(root);

    cout << "LevelOrder:" << endl;
    levelOrder(root);
    cout << "LevelOrderInLine:" << endl;
    levelOrderInLine(root);

    cout << "TotalNodeNum:" << endl << getNodeNum(root) << endl;
    cout << "Depth:" << endl << getDepth(root) << endl;
    cout << "3rd-level Node Num:" << endl << getKthLevelNodeNum(root, 3) << endl;
    cout << "LeafNodeNum:" << endl << getLeafNodeNum(root) << endl;
    int height = 0;
    cout << "isAVL:" << endl << isAVL(root, height) << endl;

    return 0;
}