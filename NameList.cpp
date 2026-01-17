#include<bits/stdc++.h>
using namespace std;

class Name {
public:
    bool isEnd;
    Name* child[26];

    Name() {
        isEnd = false;
        for(int i = 0; i < 26; i++) child[i] = nullptr;
    }
};

class NameList {
public:
    Name* root;

    NameList() {
        root = new Name();
    }

    void insertName(string name) {
        Name* node = root;
        for(char c : name) {
            int idx = c - 'a';
            if(node->child[idx] == nullptr) {
                node->child[idx] = new Name();
            }
            node = node->child[idx];
        }
        node->isEnd = true;
    }

    bool searchName(string name) {
        Name* node = root;
        for(char c : name) {
            int idx = c - 'a';
            if(node->child[idx] == nullptr)
                return false;
            node = node->child[idx];
        }
        return node->isEnd;
    }

    bool isPrefix(string name) {
        Name* node = root;
        for(char c : name) {
            int idx = c - 'a';
            if(node->child[idx] == nullptr)
                return false;
            node = node->child[idx];
        }
        return true;
    }

    void findAllNamesWithPrefix(Name* node, string pre, vector<string> &ans) {
        if(node->isEnd)
            ans.push_back(pre);

        for(int i = 0; i < 26; i++) {
            if(node->child[i]) {
                findAllNamesWithPrefix(node->child[i], pre + char(i + 'a'), ans);
            }
        }
    }

    vector<string> giveSuggestions(string pre) {
        if(!isPrefix(pre)) {
            cout << "No name exists with the given prefix.\n";
            return {};
        }

        Name* node = root;
        for(char c : pre) {
            node = node->child[c - 'a'];
        }

        vector<string> ans;
        findAllNamesWithPrefix(node, pre, ans);
        return ans;
    }
};

int main() {

    NameList nameList;

    nameList.insertName("alice");
    nameList.insertName("ali");
    nameList.insertName("alex");
    nameList.insertName("bob");
    nameList.insertName("bobby");
    nameList.insertName("carol");

    cout << "Search alice: " << nameList.searchName("alice") << endl;
    cout << "Search alina: " << nameList.searchName("alina") << endl;

    cout << "Is prefix al: " << nameList.isPref ix("al") << endl;
    cout << "Is prefix ca: " << nameList.isPrefix("ca") << endl;
    cout << "Is prefix da: " << nameList.isPrefix("da") << endl;

    vector<string> suggestions = nameList.giveSuggestions("al");
    cout << "Suggestions for prefix 'al':\n";
    for(string s : suggestions) {
        cout << s << endl;
    }

    vector<string> suggestions2 = nameList.giveSuggestions("bo");
    cout << "\nSuggestions for prefix 'bo':\n";
    for(string s : suggestions2) {
        cout << s << endl;
    }

    return 0;
}
