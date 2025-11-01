# include<bits/stdc++.h>
using namespace std;

class LeaderBoard{
    public:
    unordered_map<int, int> playerscores;
    multiset<int, greater<int>> scores;
    
    void addScore(int playerId, int score){
        int oriscore = playerscores[playerId];
        int newscore = oriscore+score;
        playerscores[playerId]=newscore;
        scores.erase(oriscore);
        scores.insert(newscore);
    }
    
    int top(int k) {
        auto it=scores.begin();
        int topkscores=0;
        while(k>0 && it!=scores.end()) {
            topkscores+=(*it);
            it++;
            k--;
        }
        return topkscores;
    }
    
    void reset(int playerId) {
        int oriscore = playerscores[playerId];
        playerscores[playerId]=0;
        scores.insert(0);
        scores.erase(oriscore);
    }
};

int main() {
    LeaderBoard* lb = new LeaderBoard();
    lb->addScore(0, 100);
    lb->addScore(1, 34);
    lb->addScore(4, 6);
    cout << "Top 2 total: " << lb->top(2) << endl;
    lb->reset(1);
     cout << "Top 2 after reset: " << lb->top(2) << endl;
    return 0;
}