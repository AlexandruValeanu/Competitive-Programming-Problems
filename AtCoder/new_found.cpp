#include <bits/stdc++.h>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);

  // int x, a, b;
  // cin >> x >> a >> b;
  //
  // if (abs(x - a) < abs(x - b))
  //   cout << "A\n";
  // else
  //   cout << "B\n";

  string s;
  cin >> s;

  for (char c = 'a'; c <= 'z'; c++){
    if (count(s.begin(), s.end(), c) == 0){
      cout << c << endl;
      return 0;
    }
  }

  cout << "None\n";

  return 0;
}
