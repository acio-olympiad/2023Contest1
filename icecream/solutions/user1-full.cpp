/*
Solution to ACIO 2023 Contest 1: Ice-Cream Obsession (by ndosh#0179 and User 1#4291):
    We begin by creating an array of choices we can make for each topic. 
    For the ith lecture: we can attend no lectures for topic i,
    attend the first lecture for topic i, attend the first two lectures for topic i, and so on. 
    Each choice is represented by a pair storing the number of hours used up if we make that choice, as well as the number of skill points we gain. 
    Next, we create a two-dimensional DP array.
    dp[i][j] will contain the maximum number of skill points we consider the first i topics and have j hours left to spend.
    For each i, we must choose exactly one choice for topic i. 
    Our DP transition is therefore dp[i][j] = max(dp[i-1][j+h]+s) for all pairs of {h,s} in our choices for topic i.
    The answer to the problem is the maximum value of dp[N][i], for all i, when we have make a choice for all topics.
    The time complexity of this approach amortises to O(H(N+L)).
*/

#include<bits/stdc++.h>
using namespace std;

using ll=long long;
using pll=pair<ll,ll>;

vector<pll> choices[1005]; // {cost,skill}

ll dp[1005][1005]; // max skill level considering the first i topics, with j hours left to spend

int main(){
    int N,L,H;
    cin>>N>>L>>H;

    fill(choices,choices+1005,(vector<pll>){{0,0}});
    for(int i=1;i<=L;i++){
        int t,h,s;
        cin>>t>>h>>s;

        pll cur=choices[t].back();
        choices[t].push_back({cur.first+h,cur.second+s});
    }

    for(int i=1;i<=N;i++){
        for(int j=0;j<=H;j++){
            for(pll choice:choices[i]){
                ll h,s;
                tie(h,s)=choice;

                if(h+j<=H) dp[i][j]=max(dp[i][j],dp[i-1][j+h]+s);
            }
        }
    }

    cout<<*max_element(dp[N],dp[N]+H+1);
}