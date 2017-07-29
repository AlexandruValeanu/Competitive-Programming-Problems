#include <bits/stdc++.h>

using namespace std;

std::vector<std::string> split(const std::string& s, char seperator)
{
   std::vector<std::string> output;

    std::string::size_type prev_pos = 0, pos = 0;

    while((pos = s.find(seperator, pos)) != std::string::npos)
    {
        std::string substring( s.substr(prev_pos, pos-prev_pos) );

        output.push_back(substring);

        prev_pos = ++pos;
    }

    output.push_back(s.substr(prev_pos, pos-prev_pos)); // Last word

    return output;
}

int main(){
  ios_base::sync_with_stdio(false);

  int T;
  cin >> T;
  cin.get();

  while (T--) {
    string line;
    getline(cin, line);

    auto As = split(line, ' ');
    vector<int> A;

    for (auto s: As)
      A.push_back(stoi(s));

    int n = A.size();
    auto it = find(A.begin(), A.end(), n - 1);
    if (it != A.end())
      A.erase(it);

    int best = 0;

    for (auto x: A)
      best = max(best, x);

    cout << best << endl;
  }

  return 0;
}
