#include <bits/stdc++.h>

using namespace std;

class UnionFind{
public:
    UnionFind(const int n) : Parent(vector<int>(n + 1)), Rank(vector<int>(n + 1)), Size(vector<int>(n + 1)) {
        for (int i = 1; i <= n; ++i)
            MakeSet(i);
    }

    void MakeSet(int x)
    {
        Parent[x] = x;
        Rank[x] = 0;
        Size[x] = 1;
    }

    int Find(int x)
    {
        if (Parent[x] != x)
            Parent[x] = Find(Parent[x]);

        return Parent[x];
    }

    void Union(int x, int y)
    {
        x = Find(x);
        y = Find(y);

        if (x != y)
        {
            /// append y to x
            if (Rank[x] > Rank[y])
            {
                Parent[y] = x;
                Size[x] += Size[y];
            }
            else /// append x to y
            {
                Parent[x] = y;
                Size[y] += Size[x];

                if (Rank[x] == Rank[y])
                  Rank[y]++;
            }
        }
    }

    bool connected(int x, int y)
    {
        return Find(x) == Find(y);
    }

    int getSize(int x){
      return Size[Find(x)];
    }

private:

    vector<int> Parent;
    vector<int> Rank;
    vector<int> Size;
};

using Edge = tuple<int,int,int>;

long long count_paths(int MAX_VALUE, const int N, const vector<Edge> &edges){
  UnionFind uf(N);

  for (auto edge: edges){
    int a, b, w;
    tie(a, b, w) = edge;

    if (w > MAX_VALUE)
      break;

    uf.Union(a, b);
  }

  map<int,int> mp;
  for (int i = 1; i <= N; i++)
    mp[uf.Find(i)] = uf.getSize(i);

  long long paths = 0;

  for (auto pii: mp){
    int s = pii.second;
    paths += 1LL * s * (s - 1) / 2;
  }

  return paths;
}

int main(){
  ios_base::sync_with_stdio(false);

  int N, M, X;
  cin >> N >> M >> X;

  vector<Edge> edges;

  for (int i = 0; i < M; i++){
    int a, b, w;
    cin >> a >> b >> w;

    edges.push_back(make_tuple(a, b, w));
  }

  sort(edges.begin(), edges.end(), [](const auto &x, const auto &y){
    return get<2>(x) < get<2>(y);
  });

  cout << count_paths(X, N, edges) - count_paths(X - 1, N, edges) << endl;

  return 0;
}
