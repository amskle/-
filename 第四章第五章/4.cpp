#include <bits/stdc++.h>
using namespace std;

struct Node {
    int type; // 0: 变量, 1: &, 2: |, 3: !
    int val;  // 当前值
    int varId; // 如果是变量，记录变量id
    Node* left;
    Node* right;
    Node* parent;
    bool affectedByLeft;  // 左子节点变化是否影响该节点
    bool affectedByRight; // 右子节点变化是否影响该节点
    
    Node(int t) : type(t), val(0), varId(-1), left(nullptr), right(nullptr), parent(nullptr),
                  affectedByLeft(true), affectedByRight(true) {}
};

int n, q;
vector<int> initValues;
vector<Node*> varNodes; // 变量id -> 叶子节点

// 解析后缀表达式
Node* buildExpressionTree(const string& s) {
    stack<Node*> st;
    stringstream ss(s);
    string token;
    
    while (ss >> token) {
        if (token == "&") {
            Node* node = new Node(1);
            node->right = st.top(); st.pop();
            node->left = st.top(); st.pop();
            node->left->parent = node;
            node->right->parent = node;
            st.push(node);
        } 
        else if (token == "|") {
            Node* node = new Node(2);
            node->right = st.top(); st.pop();
            node->left = st.top(); st.pop();
            node->left->parent = node;
            node->right->parent = node;
            st.push(node);
        }
        else if (token == "!") {
            Node* node = new Node(3);
            node->left = st.top(); st.pop();
            node->left->parent = node;
            st.push(node);
        }
        else {
            // 变量: x1, x2, ...
            int varId = stoi(token.substr(1));
            Node* node = new Node(0);
            node->varId = varId;
            varNodes[varId] = node;
            st.push(node);
        }
    }
    
    return st.top();
}

// 计算初始值
int evaluate(Node* node) {
    if (node->type == 0) {
        node->val = initValues[node->varId];
        return node->val;
    }
    else if (node->type == 1) { // &
        int leftVal = evaluate(node->left);
        int rightVal = evaluate(node->right);
        node->val = leftVal & rightVal;
        return node->val;
    }
    else if (node->type == 2) { // |
        int leftVal = evaluate(node->left);
        int rightVal = evaluate(node->right);
        node->val = leftVal | rightVal;
        return node->val;
    }
    else { // !
        node->val = !evaluate(node->left);
        return node->val;
    }
}

// 预处理影响关系
void preprocess(Node* node) {
    if (node->type == 1) { // &
        // 左子节点为0时，右子节点变化不影响
        if (node->left->val == 0) {
            node->affectedByRight = false;
        }
        // 右子节点为0时，左子节点变化不影响
        if (node->right->val == 0) {
            node->affectedByLeft = false;
        }
        preprocess(node->left);
        preprocess(node->right);
    }
    else if (node->type == 2) { // |
        // 左子节点为1时，右子节点变化不影响
        if (node->left->val == 1) {
            node->affectedByRight = false;
        }
        // 右子节点为1时，左子节点变化不影响
        if (node->right->val == 1) {
            node->affectedByLeft = false;
        }
        preprocess(node->left);
        preprocess(node->right);
    }
    else if (node->type == 3) { // !
        preprocess(node->left);
    }
}

// 传播敏感度
void propagateAffection(Node* node, bool affectsParent) {
    if (node == nullptr) return;
    
    if (node->type == 0) {
        // 叶子节点，存储是否影响根
        node->val = affectsParent ? 1 : 0;
        return;
    }
    
    if (node->type == 1) { // &
        propagateAffection(node->left, affectsParent && node->affectedByLeft);
        propagateAffection(node->right, affectsParent && node->affectedByRight);
    }
    else if (node->type == 2) { // |
        propagateAffection(node->left, affectsParent && node->affectedByLeft);
        propagateAffection(node->right, affectsParent && node->affectedByRight);
    }
    else { // !
        propagateAffection(node->left, affectsParent);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    string s;
    getline(cin, s);
    
    cin >> n;
    initValues.resize(n + 1);
    varNodes.resize(n + 1);
    
    for (int i = 1; i <= n; i++) {
        cin >> initValues[i];
    }
    
    Node* root = buildExpressionTree(s);
    evaluate(root);
    preprocess(root);
    propagateAffection(root, true);
    
    cin >> q;
    while (q--) {
        int varId;
        cin >> varId;
        
        Node* varNode = varNodes[varId];
        if (varNode->val) {
            // 该变量影响根节点，输出相反值
            cout << (1 - root->val) << '\n';
        } else {
            // 该变量不影响根节点，输出原值
            cout << root->val << '\n';
        }
    }
    
    return 0;
}