#include<bits/stdc++.h>
using namespace std;

// 0/1 knapsack problem recursive solution
int knapsack_recursive(int w, int weight[], int value[], int n){
    if(n==0||w==0)
        return 0;

    if(weight[n-1] > w){
        knapsack_recursive(w, weight, value, n-1);
    }else{
        return max(knapsack_recursive(w, weight, value, n-1), knapsack_recursive(w-weight[n-1], weight, value, n-1)+value[n-1]);
    }
}

// 0/1 knapsack problem memoised(top down) solution
int knapsack_memoised(int w, int weight[], int value[], int n, int** dp){
    if(n==0 || w == 0)
        return 0;
    if(dp[n][w]!=-1){
        return dp[n][w];
    }else{
        int ans;
        if(weight[n-1] > w){
            ans = knapsack_memoised(w, weight, value, n-1, dp);
        }else{
            ans = max(knapsack_memoised(w, weight, value, n-1, dp), knapsack_memoised(w-weight[n-1], weight, value, n-1, dp)+value[n-1]);
        }
        dp[n][w] = ans;
        return dp[n][w];
    }
}


// 0/1 knapsack problem dp(bottom up) solution
int knapsack_dp(int w, int weight[], int value[], int n){
    int dp[n+1][w+1];
    for(int i=1; i<n+1; i++){
        for(int j=1; j<w+1; j++){
            if(i==0||j==0){
                dp[i][j]=0;
            }
            if(weight[i-1] <= j){
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-weight[i-1]]+value[i-1]);
            }
            else{
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    return dp[n][w];
}


// subset sum recursive solution
bool subset_sum_recursive(int arr[], int n, int sum){
    if(sum == 0)
        return true;
    if(n==0)
        return false;
    bool ans = false;
    if(arr[n-1] > sum){
        ans = ans || subset_sum_recursive(arr, n-1, sum);
    }else{
        ans = ans || subset_sum_recursive(arr, n-1, sum);
        ans = ans || subset_sum_recursive(arr, n-1, sum-arr[n-1]);
    }
    return ans;
}


// subset sum dp(bottom-up) solution
bool subset_sum_dp(int arr[], int n, int sum){
    bool dp[n+1][sum+1];
    for(int i=0; i<n+1; i++){
        dp[i][0] = true;
    }
    for(int i=1; i<sum+1; i++){
        dp[0][i] = false;
    }
    for(int i=1; i<n+1; i++){
        for(int j=1; j<sum+1; j++){
            if(arr[i-1] > j){
                dp[i][j] = dp[i-1][j];
            }else{
                dp[i][j] = dp[i-1][j] || dp[i-1][j-arr[i-1]];
            }
        }
    }
    return dp[n][sum];
}

//number of subsets with a given sum
int number_of_subsets(int arr[], int n, int sum){
    int dp[n+1][sum+1];
    for(int i=0; i<n+1; i++){
        dp[i][0] = 1;
    }
    for(int i=1; i<sum+1; i++){
        dp[0][i] = 0;
    }
    for(int i=1; i<n+1; i++){
        for(int j=1; j<sum+1; j++){
            if(arr[i-1] <= j){
                dp[i][j] = dp[i-1][j]+dp[i-1][j-arr[i-1]];
            }
            else{
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    return dp[n][sum];
}

//minimum subset difference
int minimum_subset_difference(int arr[], int n){
    int sum = 0;
    for(int i=0; i<n; i++){
        sum += arr[i];
    }
    sum /= 2;
    bool dp[n+1][sum+1];
    for(int i=0; i<n+1; i++){
        dp[i][0] = true;
    }
    for(int i=0; i<sum+1; i++){
        dp[0][i] = false;
    }
    for(int i=1; i<n; i++){
        for(int j=1; j<sum+1; j++){
            if(arr[i-1] <= j){
                dp[i][j] = dp[i-1][j]||dp[i-1][j-arr[i-1]];
            }else{
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    for(int i=sum; i>=0; i++){
        if(dp[n][i]){
            return (2*sum - i);
        }
    }
}

int subsets_with_given_difference(int arr[], int n, int diff){
    int sum = accumulate(arr, arr+n, 0);
    int target = (sum+diff)/2;
    // now the problem just reduces to finding the number of subsets with sum = target
    int dp[n+1][target+1];
    for(int i = 0; i<n+1; i++){
        dp[i][0] = 1;
    }
    for(int i=1; i<target+1; i++){
        dp[0][i] = 0;
    }
    for(int i=1; i<n+1; i++){
        for(int j=1; j<target+1; j++){
            if(arr[i] <= j){
                dp[i][j] = dp[i-1][j] + dp[i-1][j-arr[i-1]];
            }else{
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    return dp[n][target];
}

int main(){
    int n;
    cin >> n;
    int arr[n];
    for(int i=0; i<n; i++){
        cin >> arr[i];
    }
    int data;
    cin >> data;
    cout << subset_sum_recursive(arr, n, data);
}
