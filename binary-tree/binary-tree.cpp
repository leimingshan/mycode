#include <iostream>
#include <stack>
#include <queue>

using namespace std;

//Define binary tree node
struct TreeNode {
    int value;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
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
    root->lchild = buildInorderPreorder(pre+1, i, offset);
    root->rchild = buildInorderPreorder(pre+i+1, n-i-1, offset+i+1);
    return root;
}
//根据后序遍历和中序遍历构建二叉树
struct TreeNode *buildInorderPostorder(int post[], int n, int offset)
{
    if (n == 0) return NULL;
    int rootVal = post[n-1];
    int i = mapIndex[rootVal] - offset;  // the divider's index

    struct TreeNode* root = new (struct TreeNode);
    root->lchild = buildInorderPostorder(post, i, offset);
    root->rchild = buildInorderPostorder(post+i, n-i-1, offset+i+1);
    return root;
}

//Traverse
//PreOrder
void preOrder(TreeNode *root)
{
    if (root == NULL)
        return;
    cout << root->value << ' ';
    preOrder(root->lchild);
    preOrder(root->rchild);
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
        //watch out!!! push rchild first and then lchild
        if (temp->rchild != NULL)
            s.push(temp->rchild);
        if (temp->lchild != NULL)
            s.push(temp->lchild);
    }
    cout << endl;
    return;
}

//InOrder
void inOrder(TreeNode *root)
{
    if (root == NULL)
        return;
    inOrder(root->lchild);
    cout << root->value << ' ';
    inOrder(root->rchild);
}

void inOrderNonRecursive(TreeNode *root)
{
    if (root == NULL)
        return;
    stack<TreeNode *> s;

    while (root != NULL) {
        s.push(root);
        root = root->lchild;
    }

    while (!s.empty()) {
        root = s.top();
        s.pop();
        cout << root->value << ' ';
        root = root->rchild;

        while (root != NULL) {
            s.push(root);
            root = root->lchild;
        }
    }
    cout << endl;
}

//PostOrder
void postOrder(TreeNode *root)
{
    if (root == NULL)
        return;
    postOrder(root->lchild);
    postOrder(root->rchild);
    cout << root->value << ' ';
}

void postOrderNonRecursive(TreeNode *root)
{
    //this will be very easy if you use 2 stacks
    if (!root) return;
    stack<TreeNode*> s, output;
    s.push(root);
    while (!s.empty()) {
        TreeNode *curr = s.top();
        output.push(curr);
        s.pop();
        if (curr->lchild)
            s.push(curr->lchild);
        if (curr->rchild)
            s.push(curr->rchild);
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
    TreeNode *node;
    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty()) {
        node = q.front();
        q.pop();
        cout << node->value << ' '; //Visit(node);

        if (node->lchild != NULL)
            q.push(node->lchild);
        if (node->rchild != NULL)
            q.push(node->rchild);
    }
    cout << endl;
}

void levelOrderInLine(TreeNode *root)
{

}

//Get binary tree node number
int getNodeNum(TreeNode *root)
{
    if (root == NULL)
        return 0;

    return getNodeNum(root->lchild) + getNodeNum(root->rchild);
}

//Get tree depth
int getDepth(TreeNode *root)
{
    if (root == NULL)
        return 0;
    int ldepth = getDepth(root->lchild);
    int rdepth = getDepth(root->rchild);

    return ldepth > rdepth ? (ldepth + 1) : (rdepth + 1);
}

//

//Test all of the functions above
int main()
{
    int pre[] = {7, 10, 4, 3, 1, 2, 8, 11};
    int in[] = {4, 10, 3, 1, 7, 11, 8, 2};
    int n = sizeof(in) / sizeof(in[0]);
    mapToIndices(in, n);

    struct TreeNode* root = buildInorderPreorder(pre, n, 0);

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


    cout<<endl;
}