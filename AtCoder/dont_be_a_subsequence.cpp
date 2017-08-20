#include <bits/stdc++.h>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);

  string text;
  cin >> text;

  const int N = (int)text.size();
  constexpr int SIGMA = 26;

  vector<vector<int>> next(N + 1);
  vector<int> point(SIGMA);

  for (int i = 0; i <= N; i++){
    next[i].assign(SIGMA, N);
  }

  for (int i = N - 1; i >= 0; i--){
    for (int j = 0; j < SIGMA; j++){
      next[i][j] = next[i + 1][j];
      next[i][text[i] - 'a'] = i;
    }
  }


  vector<int> dp(N + 2);
  dp[N] = 1;

  for (int i = N - 1; i >= 0; i--){
    dp[i] = N + 1;

    for (int j = 0; j < SIGMA; j++){
      dp[i] = min(dp[i], dp[next[i][j] + 1] + 1);
    }
  }

  int pos = 0, len = 0;
  while (len < dp[0]){
    for (int j = 0; j < SIGMA; j++){
      if (dp[pos] == dp[next[pos][j] + 1] + 1){
        cout << char('a' + j);
        pos = next[pos][j] + 1;
        len++;
        break;
      }
    }
  }

  cout << endl;

  return 0;
}
