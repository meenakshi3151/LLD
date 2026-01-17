#include<bits/stdc++.h>
using namespace std;

class Node{
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

class Tree{
public:
    int dia;

    Tree() {
        dia = 0;
    }

    vector<int> topview(Node* root) {
        vector<int> res;
        if(!root) return res;

        queue<pair<Node*,int>> q;
        map<int,int> mp;
        q.push({root, 0});

        while(!q.empty()) {
            auto [node, hd] = q.front();
            q.pop();

            if(mp.find(hd) == mp.end())
                mp[hd] = node->val;

            if(node->left) q.push({node->left, hd - 1});
            if(node->right) q.push({node->right, hd + 1});
        }

        for(auto &x : mp)
            res.push_back(x.second);

        return res;
    }

    vector<int> bottomview(Node* root) {
        vector<int> res;
        if(!root) return res;

        queue<pair<Node*,int>> q;
        map<int,int> mp;
        q.push({root, 0});

        while(!q.empty()) {
            auto [node, hd] = q.front();
            q.pop();

            mp[hd] = node->val;

            if(node->left) q.push({node->left, hd - 1});
            if(node->right) q.push({node->right, hd + 1});
        }

        for(auto &x : mp)
            res.push_back(x.second);

        return res;
    }

    int height(Node* root) {
        if(!root) return 0;

        return max(height(root->left), height(root->right)) + 1;
    }

    int diameterUtil(Node* root) {
        if(!root) return 0;

        int lh = diameterUtil(root->left);
        int rh = diameterUtil(root->right);
        dia = max(dia, lh + rh + 1);

        return max(lh, rh) + 1;
    }

    int diameter(Node* root) {
        dia = 0;
        diameterUtil(root);
        return dia;
    }

    int width(Node* root) {
        if(!root) return 0;

        queue<pair<Node*, long long>> q;
        q.push({root, 0});
        int ans = 0;

        while(!q.empty()) {
            int n = q.size();
            long long minIdx = q.front().second;

            long long first = 0, last = 0;

            for(int i = 0; i < n; i++) {
                auto [node, idx] = q.front();
                q.pop();

                idx -= minIdx;

                if(i == 0) first = idx;
                if(i == n - 1) last = idx;

                if(node->left) q.push({node->left, 2 * idx + 1});
                if(node->right) q.push({node->right, 2 * idx + 2});
            }
            ans = max(ans, (int)(last - first + 1));
        }
        return ans;
    }

    void preorder(Node* root, vector<int> &vec){
        if(!root) return;
        vec.push_back(root->val);
        preorder(root->left, vec);
        preorder(root->right, vec);
    }

    void inorder(Node* root, vector<int> &vec){
        if(!root) return;
        inorder(root->left, vec);
        vec.push_back(root->val);
        inorder(root->right, vec);
    }

    void postorder(Node* root, vector<int> &vec){
        if(!root) return;
        postorder(root->left, vec);
        postorder(root->right, vec);
        vec.push_back(root->val);
    }
};

class BinarySearchTree{
public:
    Node* makeBST(vector<int> &arr, int l, int r, Node* parent = nullptr) {
        if(l > r) return nullptr;

        int mid = (l + r) / 2;
        Node* root = new Node(arr[mid]);
        root->par = parent;

        root->left = makeBST(arr, l, mid - 1, root);
        root->right = makeBST(arr, mid + 1, r, root);

        return root;
    }
};

class BinaryTree{
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
};

int main() {
    vector<int> arr = {1,2,3,4,5,6,7};

    BinaryTree bt;
    Node* root = bt.makeBT(arr);

    Tree t;

    cout << "Height: " << t.height(root) << endl;
    cout << "Diameter: " << t.diameter(root) << endl;
    cout << "Width: " << t.width(root) << endl;

    vector<int> top = t.topview(root);
    cout << "Top View: ";
    for(int x : top) cout << x << " ";
    cout << endl;

    return 0;
}
