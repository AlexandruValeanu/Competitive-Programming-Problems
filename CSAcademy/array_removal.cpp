#include <bits/stdc++.h>

using namespace std;

constexpr int MAX_N = 100'000;

int father[MAX_N + 1];
long long sum[MAX_N + 1];
int order[MAX_N + 1];
bool exists[MAX_N + 1];

int get(int x){
  if (x == father[x])
    return x;
  else
    return father[x] = get(father[x]);
}

void join(int x, int y){
  x = get(x);
  y = get(y);

  if (x != y){
    if (rand() & 1)
      swap(x, y);

    father[x] = y;
    sum[y] += sum[x];
  }
}

int main(){
  ios_base::sync_with_stdio(false);
  srand(0xDEAD);

  int N;
  cin >> N;

  for (int i = 1, v; i <= N; i++){
    cin >> v;
    father[i] = i;
    sum[i] = v;
    exists[i] = false;
  }

  for (int i = 1; i <= N; i++)
    cin >> order[i];

  vector<long long> answers;
  long long answer = 0;

  for (int i = N; i >= 1; i--){
    int p = order[i];
    exists[p] = true;

    if (p - 1 >= 1 && exists[p - 1])
      join(p, p - 1);

    if (p + 1 <= N && exists[p + 1])
      join(p, p + 1);

    answer = max(answer, sum[get(p)]);
    answers.push_back(answer);
  }

  for (auto it = answers.rbegin(); it != answers.rend(); ++it)
    cout << *it << "\n";

  return 0;
}
