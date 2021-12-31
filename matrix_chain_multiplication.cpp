#include<bits/stdc++.h>
using namespace std;
/*
int MCM_recursive(vector<int>& v, int i, int j){
    // dimension of matrix a[i] = v[i-1] x v[i]

    if(i>=j)
        return 0;

    int ans = INT_MAX;
    for(int k = i; k <= j-1; k++){
        int temp_ans_left = MCM_recursive(v, i, k);
        int temp_ans_right = MCM_recursive(v, k+1, j);
        int temp_ans = temp_ans_left + temp_ans_right + v[i-1]*v[k]*v[j];
        ans = min(ans, temp_ans);
    }
    return ans;
}

int dp[100][100];
int MCM_memoised(vector<int>& v, int i, int j){
    if(i >= j){
        dp[i][j] = 0;
        return 0;
    }

    if(dp[i][j] != -1){
        return dp[i][j];
    }

    int ans = INT_MAX;
    for(int k = i; k <= j-1; ++k){
        int temp_ans = MCM_memoised(v, i, k) + MCM_memoised(v, k+1, j) + v[i-1]*v[k]*v[j];
        ans = min(ans, temp_ans);
    }
    dp[i][j] = ans;
    return dp[i][j];
}
*/



bool is_palindrome(string s, int i, int j){
    int ans = true;
    while(i <= j){
        if(s[i] != s[j]){
            ans = false;
            break;
        }
        ++i, --j;
    }
    return ans;
}
int dp_1[100][100];
int palindrome_partition(string s, int i, int j){
    if(i >= j){
        return 0;
    }
    if(is_palindrome(s, i, j)){
        return 0;
    }

    int ans = INT_MAX;
    for(int k = i; k <= j-1; ++k){
        int temp_ans = palindrome_partition(s, i, k) + palindrome_partition(s, k+1, j) + 1;
        ans = min(ans, temp_ans);
    }
    return ans;
}
int palindrome_partition_memo(string s, int i, int j){
    if(i >= j){
        return 0;
    }

    if(dp_1[i][j] != -1){
        return dp_1[i][j];
    }
    if(is_palindrome(s, i, j)){
        return 0;
    }

    int ans = INT_MAX;
    for(int k = i; k <= j-1; ++k){
        int temp_left, temp_right;
        if(dp_1[i][k] != -1){
            temp_left = dp_1[i][k];
        }else{
            temp_left = palindrome_partition_memo(s, i, k);
            dp_1[i][k] = temp_left;
        }
        if(dp_1[k+1][j] != -1){
            temp_right = dp_1[k+1][j];
        }else{
            temp_right = palindrome_partition_memo(s, k+1, j);
            dp_1[k+1][j] = temp_right;
        }
        int temp_ans = temp_left + temp_right + 1;
        ans = min(ans, temp_ans);
    }
    dp_1[i][j] = ans;
    return ans;
}


int bool_true(string s, bool t, int i, int j){
    if(i>=j){
        if(t){
            return s[i] == 'T';
        }else{
            return s[i] == 'F';
        }
    }
    int ans = 0;
    for(int k = i+1; k <= j-1; k+=2){
        int left_false = bool_true(s, false, i, k-1);
        int left_true = bool_true(s, true, i, k-1);
        int right_false = bool_true(s, false, k+1, j);
        int right_true = bool_true(s, true, k+1, j);

        if(s[k] == '|'){
            if(t==true){
                ans += left_false*right_true + left_true*right_false + left_true*right_true;
            }else{
                ans += left_false*right_false;
            }
        }
        else if(s[k] == '^'){
            if(t==true){
                ans += left_false*right_true + left_true*right_false;
            }else{
                ans += left_false*right_false + left_true*right_true;
            }
        }
        else if(s[k] == '&'){
            if(t==true){
                ans += left_true*right_true;
            }else{
                ans += left_false*right_false + left_true*right_false + left_false*right_true;
            }
        }
    }
    return ans;
}

const int d = 1001;
int dp_2[d][d][2];
int bool_true_memo(string s, bool t, int i, int j){
    if(i>=j){
        if(t){
            dp_2[i][j][t] =  s[i] == 'T';
        }else{
            dp_2[i][j][t] =  s[i] == 'F';
        }
        return dp_2[i][j][t];
    }

    if(dp_2[i][j][t] != -1){
        return dp_2[i][j][t];
    }

    int ans = 0;
    for(int k = i+1; k <= j-1; k+=2){
        int left_false = bool_true_memo(s, false, i, k-1);
        int left_true = bool_true_memo(s, true, i, k-1);
        int right_false = bool_true_memo(s, false, k+1, j);
        int right_true = bool_true_memo(s, true, k+1, j);

        if(s[k] == '|'){
            if(t==true){
                ans += left_false*right_true + left_true*right_false + left_true*right_true;
            }else{
                ans += left_false*right_false;
            }
        }
        else if(s[k] == '^'){
            if(t==true){
                ans += left_false*right_true + left_true*right_false;
            }else{
                ans += left_false*right_false + left_true*right_true;
            }
        }
        else if(s[k] == '&'){
            if(t==true){
                ans += left_true*right_true;
            }else{
                ans += left_false*right_false + left_true*right_false + left_false*right_true;
            }
        }
    }
    dp_2[i][j][t] = ans;
    return ans;
}

//T^F&T
int main(){
    //mcm
    /*vector<int> v = {40, 20, 30, 10, 30};
    cout << MCM_recursive(v, 1, v.size()-1) << '\n';
    memset(dp, -1, sizeof(dp));
    cout << MCM_memoised(v, 1, v.size()-1) << '\n';*/

    //palindrome_partition
    /*string s; cin >> s;
    cout << palindrome_partition(s, 0, s.size()-1) << '\n';
    memset(dp_1, -1, sizeof(dp_1));
    cout << palindrome_partition_memo(s, 0, s.size()-1) << '\n';*/

    //bool_true
    string s; cin >> s;
    //cout << bool_true(s, true, 0, s.size()-1) << '\n';
    memset(dp_2, -1, sizeof(dp_2));
    cout << bool_true_memo(s, true, 0, s.size()-1) << '\n';

}
