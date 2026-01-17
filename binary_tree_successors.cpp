#include<bits/stdc++.h>
using namespace std;

class Node {
public:
    int val;
    Node* par;
    Node* left;
    Node* right;

    Node(int v) {
        val = v;
        par = left = right = nullptr;
    }
};

class Tree {
public:
    Node* makeBT(vector<int> &arr) {
        int n = arr.size();
        if(n == 0) return nullptr;

        vector<Node*> nodes(n);
        for(int i = 0; i < n; i++)
            nodes[i] = new Node(arr[i]);

        for(int i = 0; i < n; i++) {
            int l = 2*i + 1;
            int r = 2*i + 2;
            if(l < n) {
                nodes[i]->left = nodes[l];
                nodes[l]->par = nodes[i];
            }
            if(r < n) {
                nodes[i]->right = nodes[r];
                nodes[r]->par = nodes[i];
            }
        }
        return nodes[0];
    }

    int preordersuc(Node* node) {
        if(!node) return -1;

        if(node->left) return node->left->val;
        if(node->right) return node->right->val;

        while(node->par) {
            if(node->par->left == node && node->par->right)
                return node->par->right->val;
            node = node->par;
        }
        return -1;
    }

    int insuc(Node* node) {
        if(!node) return -1;

        if(node->right) {
            Node* curr = node->right;
            while(curr->left)
                curr = curr->left;
            return curr->val;
        }

        while(node->par && node->par->right == node)
            node = node->par;

        return node->par ? node->par->val : -1;
    }

    int postsuc(Node* node) {
        if(!node || !node->par) return -1;

        Node* par = node->par;

        if(par->right == node || par->right == nullptr)
            return par->val;

        Node* curr = par->right;
        while(curr->left || curr->right) {
            if(curr->left) curr = curr->left;
            else curr = curr->right;
        }
        return curr->val;
    }
};

int main() {
    vector<int> arr = {1,2,3,4,5,6,7};
    Tree t;
    Node* root = t.makeBT(arr);

    vector<Node*> nodes = {
        root,
        root->left,
        root->right,
        root->left->left,
        root->left->right,
        root->right->left,
        root->right->right
    };

    for(Node* n : nodes) {
        cout << t.preordersuc(n) << "\n";
        cout << t.insuc(n) << "\n";
        cout << t.postsuc(n) << "\n";
    }
    return 0;
}
