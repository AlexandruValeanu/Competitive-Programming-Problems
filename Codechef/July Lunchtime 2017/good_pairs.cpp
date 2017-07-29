#include <bits/stdc++.h>

using namespace std;

constexpr int MAX_VALUE = (1 << 20);
constexpr int MAX_BIT = 19 + 1;

array<int, MAX_VALUE + 1> cnt;
array<int, MAX_VALUE + 1> dp;

void brute(std::vector<int> A){
  int N = A.size();
  long long nr_pairs = 0;

   for (int i = 0; i < N; i++){
     for (int j = i + 1; j < N; j++)
       if ((A[i] | A[j]) <= max(A[i], A[j]))
         nr_pairs++;
   }

   cout << nr_pairs << "\n";
}

int main(){
  ios_base::sync_with_stdio(false);

  int T;
  cin >> T;

  while (T--){
    int N;
    cin >> N;

    std::vector<int> A(N);

    fill(dp.begin(), dp.end(), 0);
    fill(cnt.begin(), cnt.end(), 0);

    long long num_pairs = 0;

    for (int i = 0; i < N; i++){
      int x;
      cin >> x;
      A[i] = x;
      cnt[x]++;

      ++dp[x];
    }

    for (int i = 0; i < 20; ++i) {
  		for (int mask = 0; mask < (1<<20); ++mask) {
  			if((mask & (1 << i)) ==0){
  				dp[mask]+=dp[mask|(1<<i)];
  			}
      }
  	}

    for (int i = 0; i < MAX_VALUE; i++){
      if (cnt[i] == 0)
        continue;

      long long ans = 1LL * cnt[i] * (dp[i] - cnt[i]);
      ans += 1LL * cnt[i] * (cnt[i] - 1) / 2;

      num_pairs += ans;
    }

    //brute(A);
    cout << num_pairs << "\n";
  }

  return 0;
}
