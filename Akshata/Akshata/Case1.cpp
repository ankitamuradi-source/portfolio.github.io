// FloatingMicroFarms_knapsack.cpp
// Algorithm: 0/1 Knapsack (Dynamic Programming)
// Models: each "module" is a crop option with area cost and expected yield (profit).
#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; // number of crop-module types
    int capacity; // total floating area available (discrete units)
    cin>>n>>capacity;
    vector<int> area(n), yieldv(n);
    for(int i=0;i<n;i++) cin>>area[i]>>yieldv[i]; // input pairs: area yield
    vector<int> dp(capacity+1,0);
    for(int i=0;i<n;i++){
        for(int w=capacity; w>=area[i]; --w)
            dp[w] = max(dp[w], dp[w-area[i]] + yieldv[i]);
    }
    cout<<"Max yield: "<<dp[capacity]<<"\n";
    return 0;
}
/*
Usage example:
10  // n
50  // capacity
5 8   (area yield)
10 18
...
*/

