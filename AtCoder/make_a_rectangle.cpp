#include <bits/stdc++.h>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);

  int N;
  cin >> N;

  vector<int> A(N);

  for (auto &x: A)
    cin >> x;

  sort(A.begin(), A.end());

  std::vector<int> sides;

  while (A.size() > 0 && sides.size() < 2){
    int l = A.back();
    A.pop_back();

    if (A.size() > 0 && A.back() == l){
      sides.push_back(l);
      A.pop_back();
    }
  }

  if (sides.size() == 2)
    cout << 1LL * sides[0] * sides[1] << endl;
  else
    cout << 0 << endl;

  return 0;
}
