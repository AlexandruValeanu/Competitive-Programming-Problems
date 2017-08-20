#include <bits/stdc++.h>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);

  int N;
  cin >> N;

  vector<string> table(2);
  cin >> table[0];
  cin >> table[1];

  constexpr long long MOD = 1000000007;
  long long solutions = 1;

  bool up_down = false;
  int start = 0;

  if (table[0][0] == table[1][0]){
    solutions = (solutions * 3) % MOD;
    start += 1;
  }
  else{
    solutions = (solutions * 6) % MOD;
    up_down = true;
    start += 2;
  }

  for (int i = start; i < N; ){
    if (up_down){
      if (table[0][i] == table[1][i]){
        solutions = (solutions * 1) % MOD;
        up_down = false;
        i += 1;
      }
      else{
        solutions = (solutions * 3) % MOD;
        up_down = true;
        i += 2;
      }
    }
    else{
      if (table[0][i] == table[1][i]){
        solutions = (solutions * 2) % MOD;
        up_down = false;
        i += 1;
      }
      else{
        solutions = (solutions * 2) % MOD;
        up_down = true;
        i += 2;
      }
    }
  }

  cout << solutions << endl;

  return 0;
}
