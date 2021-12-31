#include<bits/stdc++.h>
using namespace std;

//unbounded knapsack recursive
int unbounded_knapsack_revcursive(int weight[], int value[], int n, int W){
    if(n==0||W==0){
        return 0;
    }
    int ans;
    if(weight[n-1] > W){
        ans = unbounded_knapsack_revcursive(weight, value, n-1, W);
    }else{
        ans = max(unbounded_knapsack_revcursive(weight, value, n-1, W), max(unbounded_knapsack_revcursive(weight, value, n, W-weight[n-1])+value[n-1], unbounded_knapsack_revcursive(weight, value, n-1, W-weight[n-1])+value[n-1]));
    }
    return ans;
}
// unbounded knapsack
int unbounded_knapsack(int weight[], int value[], int n, int W){
    int dp[n+1][W+1];
    for(int i=0; i<n+1; i++){
        dp[i][0] = 0;
    }
    for(int i=0; i<W+1; i++){
        dp[0][i] = 0;
    }
    for(int i=1; i<n+1; i++){
        for(int j=1; j<W+1; j++){
            if(weight[i-1] <= j){
                //in 0/1 knapsack replace i-1 => i: thats the only change
                //dp[i][j] = max(dp[i-1][j], dp[i-1][j-weight[i-1]]+value[n-1]);
                  dp[i][j] = max(dp[i-1][j], dp[i][j-weight[i-1]]+value[i-1]);
            }else{
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    return dp[n][W];
}

int rod_cutting(int price[], int n){
    int length[n];
    for(int i=0; i<n; i++){
        length[i] = i+1;
    }
    int dp[n+1][n+1];
    for(int i=0; i<n+1; i++){
        dp[i][0] = 0;
        dp[0][i] = 0;
    }
    for(int i=1; i<n+1; i++){
        for(int j=1; j<n+1; j++){
            if(length[i-1] <= j){
                dp[i][j] = max(dp[i-1][j], dp[i][j-length[i-1]]+price[i-1]);
            }else{
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    return dp[n][n];
}

int coin_change_num_ways(int coins[], int n, int sum){
    int dp[n+1][sum+1];
    for(int i=0; i<n+1; i++){
        dp[i][0] = 1;
    }
    for(int i=1; i<sum+1; i++){
        dp[0][i] = 0;
    }
    for(int i=1; i<n+1; i++){
        for(int j=1; j<sum+1; j++){
            if(coins[i-1] <= j){
                dp[i][j] = dp[i-1][j]+dp[i][j-coins[i-1]];
            }
            else{
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    return dp[n][sum];
}


int coin_change_min_coins(int coins[], int n, int sum){
    int dp[n+1][sum+1];
    for(int i=0; i<=n; i++){
        dp[i][0] = 0;
    }
    for(int i=0; i<=sum; i++){
        dp[0][i] = (int)1e9;
    }
    for(int i=1; i<=sum; i++){
        dp[1][i] = (i%coins[0]==0?i/coins[0]:(int)1e9);
    }
    for(int i=2; i<=n; i++){
        for(int j=1; j<=sum; j++){
            if(coins[i-1] <= j){
                dp[i][j] = min(dp[i-1][j], dp[i][j-coins[i-1]]+1);
            }else{
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    return dp[n][sum];
}
int main(){
    int n; cin >> n;
    int weight[n], value[n];
    for(int i=0; i<n; i++){
        cin >> weight[i];
    }
    for(int i=0; i<n; i++){
        cin >> value[i];
    }
    int W; cin >> W;
    cout << unbounded_knapsack(weight, value, n, W) << "\n";
    cout << unbounded_knapsack_revcursive(weight, value, n, W);
}
