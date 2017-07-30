#include <bits/stdc++.h>

using namespace std;

bool is_overflow(long long a, long long b){
	long long tmp;
	return __builtin_mul_overflow(a, b, &tmp);
}

bool is_possible(const std::vector<long long> &A, const int num_steps, const int K, long long C){
  const int n = A.size();
  std::vector<std::vector<long long>> steps(num_steps);

  int nxt = 0 ;
	for (int i = 0 ; i < n ; i ++) {
		if ((int)steps[nxt].size() == K) {
			break;
		}

		if (steps[nxt].empty() || (!is_overflow(steps[nxt].back(), C) && steps[nxt].back() * C <= A[i])) {
			steps[nxt].push_back(A[i]) ;
			nxt = (nxt + 1) % num_steps;
		}
	}

  return (int)steps[num_steps - 1].size() == K;
}

int main(){
  ios_base::sync_with_stdio(false);

  int T;
  cin >> T;

  while (T--){
    int N, K;
    long long C;
    cin >> N >> K >> C;

    std::vector<long long> A(N);
    for (auto &x: A)
      cin >> x;

    sort(A.begin(), A.end());

    int l = 1, r = N;
    int found = 0;

    while (l <= r){
      int m = (l + r) / 2;

      if (is_possible(A, m, K, C)){
        found = m;
        l = m + 1;
      }
      else
        r = m - 1;
    }

    cout << found << "\n";
  }

  return 0;
}
