#include <bits/stdc++.h>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);

  int N;
  cin >> N;

  map<string, int> mp;

  while (N--){
    string s;
    cin >> s;
    sort(s.begin(), s.end());
    mp[s]++;
  }

  int best = 0;

  for (auto pii: mp)
    best = max(best, pii.second);

  cout << best << endl;

  return 0;
}
