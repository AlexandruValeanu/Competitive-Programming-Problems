#include <bits/stdc++.h>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);

  int N, K;
  cin >> N >> K;

  vector<int> A(N);

  for (auto &x: A)
    cin >> x;

  const int len = N - K;
  deque<pair<int,int>> deck;

  for (int i = 0; i < len - 1; i++){
    int d = A[i + 1] - A[i];

    while (deck.size() > 0 && deck.back().second < d)
      deck.pop_back();

    deck.push_back({i, d});
  }

  int best = deck.front().second;

  for (int i = len - 1; i + 1 < N; i++){
    int d = A[i + 1] - A[i];

    while (deck.size() > 0 && deck.back().second < d)
      deck.pop_back();

    deck.push_back({i, d});

    if (deck.front().first == i - len + 1)
      deck.pop_front();

    best = min(best, deck.front().second);
  }

  cout << best << endl;

  return 0;
}
