#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;
typedef long long ll;
#define MAX_U 21
#define MAX_V 201

ll dp[MAX_U][MAX_V];



// just use an exhaustive search
ll solve(int current, int rest ,int* ubd, int m){
  if(current == m-1){
    if(dp[current][rest] < 0)
      dp[current][rest] = (ubd[current] >= rest);
    return dp[current][rest];
  }

  
  if(rest == 0){
    if(dp[current][rest] < 0)
      dp[current][rest] = 1;
    return dp[current][rest]; // since all the gf now could take 0
  }


  if(dp[current][rest] >= 0){
    return dp[current][rest];
  }



  //rest won't become negative
  
  int k = min(ubd[current], rest); //upper bound of the iteration

  ll  ans = 0;

  for(int i = 0; i <= k; i++){
    ans += solve(current+1, rest - i, ubd, m);
  }


  if(dp[current][rest] < 0){
    dp[current][rest] = ans;
  }

  return dp[current][rest];
}


int main(){
  int M, N;

  
  cin >> M >> N;
  while(M != 0 && N !=0){

    // set the dp
    memset(dp, -1, sizeof(dp));
    int * ubd = new int[M];

    int a_i, b_i;
  
    for(int i = 0; i < M; i++){
      cin >> a_i >> b_i;
      N -= a_i;
      ubd[i] = b_i-a_i;
    }

  
    cout << solve(0, N, ubd, M) << endl;

    delete [] ubd;

    cin >> M >> N;
  }
  return 0;
}
