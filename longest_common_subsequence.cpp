#include<bits/stdc++.h>
using namespace std;

//longest common subsequence recursive cutting string from the beginning
int LCS_recursive(string a, string b){
    //base case
    if(a.size() == 0 || b.size() == 0){
        return 0;
    }
    if(a.size()==1 || b.size()==1){
        return int(a[0] == b[0]);
    }
    //choice diagram
    if(a[0] == b[0]){
        return LCS_recursive(a.substr(1), b.substr(1))+1;
    }
    else{
        return max(LCS_recursive(a.substr(1), b), LCS_recursive(a, b.substr(1)));
    }
}
//longest common subsequence recursive cutting string from the end
int LCS_recursive_from_end(string s1, string s2, int n, int m){
    //base case
    if(n==0 || m==0)
        return 0;
    //choice diagram
    //don't have to take care of accessing out of bound memory location
    if(s1[n-1] == s2[m-1]){
        return LCS_recursive_from_end(s1, s2, n-1, m-1)+1;
    }
    else{
        return max(LCS_recursive_from_end(s1, s2, n-1, m), LCS_recursive_from_end(s1, s2, n, m-1));
    }
}

int dp[1001][1001];
int LCS_memoised_helper(string s1, string s2, int n, int m){
    if(n==0||m==0){
        dp[n][m] = 0;
    }
    if(dp[n][m] != -1){
        return dp[n][m];
    }

    if(s1[n-1] == s2[m-1]){
        dp[n][m] = 1+LCS_memoised_helper(s1, s2, n-1, m-1);
    }else{
        dp[n][m] = max(LCS_memoised_helper(s1, s2, n-1, m), LCS_memoised_helper(s1, s2, n, m-1));
    }
    return dp[n][m];
}

int LCS_dp(string s1, string s2){
    int n = s1.size(), m = s2.size();
    int dp[n+1][m+1];
    for(int i=0; i<n+1; i++){
        dp[i][0] = 0;
    }
    for(int i=0; i<m+1; i++){
        dp[0][i] = 0;
    }
    for(int i=1; i<n+1; i++){
        for(int j=1; j<m+1; j++){
            if(s1[i-1] == s2[j-1]){
                dp[i][j] = 1+dp[i-1][j-1];
            }else{
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    return dp[n][m];
}

int LCS_memoised(string s1, string s2){
    memset(dp, -1, sizeof(dp));
    int ans = LCS_memoised_helper(s1, s2, s1.size(), s2.size());
    cout << ans << '\n';
    return dp[s1.size()][s2.size()];
}

int longest_common_substring(string s1, string s2){
    int n = s1.size(), m = s2.size();
    int dp[n+1][m+1];
    for(int i=0; i<n+1; i++){
        dp[i][0] = 0;
    }
    for(int i=0; i<m+1; i++){
        dp[0][i] = 0;
    }
    int ans = 0;
    for(int i=1; i<n+1; i++){
        for(int j=1; j<m+1; j++){
            if(s1[i-1] == s2[j-1]){
                dp[i][j] = 1+dp[i-1][j-1];
            }else{
                dp[i][j] = 0; // only change
            }
            ans = max(ans, dp[i][j]);
        }
    }
    return ans;
}

string print_LCS(string s1, string s2){

    int n = s1.size(), m = s2.size();
    int dp[n+1][m+1];
    for(int i=0; i<n+1; i++){
        dp[i][0] = 0;
    }
    for(int i=0; i<m+1; i++){
        dp[0][i] = 0;
    }
    for(int i=1; i<n+1; i++){
        for(int j=1; j<m+1; j++){
            if(s1[i-1] == s2[j-1]){
                dp[i][j] = 1+dp[i-1][j-1];
            }else{
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    int i = n, j = m;
    string output = "";
    while(i>0 || j>0){
        if(s1[i-1] == s2[j-1]){
            output += s1[i-1];
            i--, j--;
        }
        else{
            if(dp[i-1][j] >= dp[i][j-1]){
                i--;
            }else{
                j--;
            }
        }
    }
    reverse(output.begin(), output.end());
    return output;
}

int shortest_commom_supersequence(string s1, string s2){
    int n = s1.size(), m = s2.size();
    int dp[n+1][m+1];
    for(int i=0; i<n+1; i++){
        dp[i][0] = 0;
    }
    for(int i=0; i<m+1; i++){
        dp[0][i] = 0;
    }
    for(int i=1; i<n+1; i++){
        for(int j=1; j<m+1; j++){
            if(s1[i-1] == s2[j-1]){
                dp[i][j] = 1+dp[i-1][j-1];
            }else{
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    int lcs_length = dp[n][m];
    return (n+m-lcs_length);
}

pair<int, int> minimum_number_of_insertions_deletions(string s1, string s2){
    int n = s1.size(), m = s2.size();
    int dp[n+1][m+1];
    for(int i=0; i<n+1; i++){
        dp[i][0] = 0;
    }
    for(int i=0; i<m+1; i++){
        dp[0][i] = 0;
    }
    for(int i=1; i<n+1; i++){
        for(int j=1; j<m+1; j++){
            if(s1[i-1] == s2[j-1]){
                dp[i][j] = 1+dp[i-1][j-1];
            }else{
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    int lcs_length = dp[n][m];
    pair<int, int> output = make_pair(n-lcs_length, m-lcs_length);
    return output;
}

int longest_palindromic_subsequence(string s){
    string s1 = s;
    reverse(s.begin(), s.end());
    string s2 = s;
    int n = s1.size(), m = s2.size();
    int dp[n+1][m+1];
    for(int i=0; i<n+1; i++){
        dp[i][0] = 0;
    }
    for(int i=0; i<m+1; i++){
        dp[0][i] = 0;
    }
    for(int i=1; i<n+1; i++){
        for(int j=1; j<m+1; j++){
            if(s1[i-1] == s2[j-1]){
                dp[i][j] = 1+dp[i-1][j-1];
            }else{
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    return dp[n][m];
}

int min_deletions_to_make_palindrome(string s){
    string s1 = s;
    reverse(s.begin(), s.end());
    string s2 = s;
    int n = s1.size(), m = s2.size();
    int dp[n+1][m+1];
    for(int i=0; i<n+1; i++){
        dp[i][0] = 0;
    }
    for(int i=0; i<m+1; i++){
        dp[0][i] = 0;
    }
    for(int i=1; i<n+1; i++){
        for(int j=1; j<m+1; j++){
            if(s1[i-1] == s2[j-1]){
                dp[i][j] = 1+dp[i-1][j-1];
            }else{
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    return (s.size() - dp[n][m]);
}

int longest_palindromic_substring(string s){
    string s1 = s;
    reverse(s.begin(), s.end());
    string s2 = s;
    int n = s1.size(), m = s2.size();
    int dp[n+1][m+1];
    for(int i=0; i<n+1; i++){
        dp[i][0] = 0;
    }
    for(int i=0; i<m+1; i++){
        dp[0][i] = 0;
    }
    for(int i=1; i<n+1; i++){
        for(int j=1; j<m+1; j++){
            if(s1[i-1] == s2[j-1]){
                dp[i][j] = 1+dp[i-1][j-1];
            }else{
                dp[i][j] = 0;
            }
        }
    }
    return dp[n][m];
}


string printRandomString(int n)
{
    char alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u',
                          'v', 'w', 'x', 'y', 'z' };

    string res = "";
    for (int i = 0; i < n; i++)
        res.push_back(alphabet[rand() % 26]);

    return res;
}

int main(){
    //longest common substring(recursive, memoised, dp)
    //print longest common subsequence
    //shortest common super sequence
    //print shortest common super sequence
    //minimum number of insertions/deletions to make a -> b
    //largest repeating subsequence
    //length of longest subsequence in a which is a substring of b
    //subsequence pattern matching
    //how many times a appears as a subsequence in b
    //largest palindromic subsequence
    //largest palindromic substring
    //number of palindromic substrings
    //minimum insertions/deletions in a string to make it a pallindrome

    srand(time(NULL));
    string a = printRandomString(10);
    string b = printRandomString(10);

    cout << a << '\n' << b << '\n';
    //cout << LCS_recursive(a, b) << '\n';
    //cout << LCS_recursive_from_end(a, b, 10, 10) << '\n';
    //cout << LCS_memoised(a, b) << '\n';
    //cout << LCS_dp("ABCDGH", "AEDFHR") << '\n';
    //cout << longest_common_substring("abcdef", "abxef") << '\n';
    //cout << print_LCS("ABCDGH", "AEDFHR") << '\n';
    //cout << shortest_commom_supersequence("geek", "eke") << '\n';
    //cout << minimum_number_of_insertions_deletions("heap", "pea").first << " " << minimum_number_of_insertions_deletions("heap", "pea").second << '\n';
    //cout << longest_palindromic_subsequence("bbbab");
    cout << longest_palindromic_substring("geeks") << '\n';
    cout << min_deletions_to_make_palindrome("aebcbda");
}
