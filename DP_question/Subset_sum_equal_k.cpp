#include<bits/stdc++.h>
using namespace std;

//recursion :
bool f(int i,int target,vector<int> a){
    if(target == 0) return true;
    if(i==0) return (a[i] == target);

    bool not_take = f(i-1,target,a);
    bool take = false;
    if(target >= a[i]){
        take = f(i-1,target-a[i],a);
    }

    return (take or not_take);
}

//memoisation : 
bool f2(int i, int target, vector<int> a, vector<vector<bool>> &dp){
    if(target == 0) return true;
    if(i==0) return a[i] == target;

    if(dp[i][target]) return true;

    bool not_take = f2(i-1,target,a,dp);
    bool take = false;
    if(target >= a[i]){
        take = f2(i-1,target-a[i],a,dp);
    }

    return dp[i][target] = (take or not_take);
}

//tabulation : 
bool f3(int n, int target, vector<int> a, vector<vector<bool>> &dp){
    //base cases : 
    for(int i=0;i<n;i++){
        dp[i][0] = true;
    }
    if(a[0]!=0 and a[0] <= target)
        dp[0][a[0]] = true;
    

    for(int i=1;i<n;i++){
        for(int j=0;j<=target;j++){
            bool not_take = dp[i-1][j];
            bool take = false;
            if(j>=a[i]){
                take = dp[i-1][j-a[i]];
            }

            dp[i][j] = take or not_take;
        }
    }

    return dp[n-1][target];
}

//space optimisation : 
bool f4(int n, int target, vector<int> a){
    vector<bool> prev(target+1,0), curr(target+1,0);
    //base cases : 
    prev[0] = curr[0] = true;
    prev[a[0]] = true;

    for(int i=1;i<n;i++){
        for(int j=0;j<=target;j++){
            bool not_take = prev[j];
            bool take = false;
            if(j>=a[i]){
                take = prev[target-a[i]];
            }

            curr[j] = take or not_take;
        }

        prev = curr;
    }

    return prev[target];
}

bool subsetSumToK(int n, int k, vector<int> &arr){
    //return f(n-1,k,arr);

    // vector<vector<bool>> dp(n,vector<bool>(k+1,false));
    // return f2(n-1,k,arr,dp);

    vector<vector<bool>> dp(n,vector<bool>(k+1,false));
    return f3(n,k,arr,dp);

    //return f4(n,k,arr);
}

int main(){
    int n,k;
    cin>>n;
    vector<int> arr(n);
    for(auto &ele : arr){
        cin>>ele;
    }
    cin>>k;
    cout<<subsetSumToK(n,k,arr);
    return 0;
}
