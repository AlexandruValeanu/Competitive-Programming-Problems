#include <bits/stdc++.h>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);

  int x, a, b;
  cin >> x >> a >> b;

  if (abs(x - a) < abs(x - b))
    cout << "A\n";
  else
    cout << "B\n";

  return 0;
}
