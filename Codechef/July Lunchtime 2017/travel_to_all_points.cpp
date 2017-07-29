#include <bits/stdc++.h>

using namespace std;

///---------------------------------------------------
const int BUFFER_SIZE = (1 << 20);
char buffer[BUFFER_SIZE];
int position = BUFFER_SIZE;

inline char getChar()
{
    if ( position == BUFFER_SIZE )
    {
        position = 0;
        fread(buffer, BUFFER_SIZE, 1, stdin);
    }

    return buffer[position++];
}

inline int getInt()
{
    register int a = 0;
    char ch;
    int sgn = 1;

    do
    {
        ch = getChar();

    } while ( !isdigit(ch) && ch != '-' );

    if ( ch == '-' )
    {
        sgn = -1;
        ch = getChar();
    }

    do
    {
        a = (a << 3) + (a << 1) + ch - '0';
        ch = getChar();

    } while ( isdigit(ch) );

    return a * sgn;
}
///---------------------------------------------------

struct Point{
  long long x, y;
  int ind;

  bool operator < (const Point &X) const{
    if (x != X.x)
      return x < X.x;
    else
      return y < X.y;
  }
};

using Elem = pair<long long, int>;

long long dist(Point A, Point B){
  return max(abs(A.x - B.x), abs(A.y - B.y));
}

bool is_possible(const std::vector<Point> &points, const vector<Elem> &x_coords, const vector<Elem> &y_coords, long long D){
  const int n = points.size();
  std::vector<bool> visited(n, false);

  int lx = 0, ly = 0;
  int rx = n - 1, ry = n - 1;

  queue<int> Q;
  Q.push(0);
  visited[0] = true;

  while (Q.size() > 0){
    int curr = Q.front();
    Q.pop();

    const int X = points[curr].x;
    const int Y = points[curr].y;

    while (rx >= lx && abs(X - x_coords[rx].first) >= D){
      int ind = x_coords[rx].second;

      if (!visited[ind]){
        Q.push(ind);
        visited[ind] = true;
      }

      rx--;
    }

    while (lx <= rx && abs(X - x_coords[lx].first) >= D){
      int ind = x_coords[lx].second;

      if (!visited[ind]){
        Q.push(ind);
        visited[ind] = true;
      }

      lx++;
    }

    while (ry >= ly && abs(Y - y_coords[ry].first) >= D){
      int ind = y_coords[ry].second;

      if (!visited[ind]){
        Q.push(ind);
        visited[ind] = true;
      }

      ry--;
    }

    while (ly <= ry && abs(Y - y_coords[ly].first) >= D){
      int ind = y_coords[ly].second;

      if (!visited[ind]){
        Q.push(ind);
        visited[ind] = true;
      }

      ly++;
    }
  }

  return count(visited.begin(), visited.end(), false) == 0;
}

int main(){
  int T = getInt();

  while (T--){
    int N = getInt();

    std::vector<Point> points;

    for (int i = 0; i < N; i++){
      long long x, y;
      x = getInt();
      y = getInt();
      points.push_back({x + y, x - y, i});
    }

    int n = N;

    std::vector<Elem> x_coords;
    std::vector<Elem> y_coords;

    for (int i = 0; i < n; i++){
      x_coords.push_back({points[i].x, points[i].ind});
      y_coords.push_back({points[i].y, points[i].ind});
    }

    sort(x_coords.begin(), x_coords.end());
    sort(y_coords.begin(), y_coords.end());

    long long l = 0, r = 2'000'000'000;
    long long found = -1;

    while (l <= r){
      int m = (l + r) / 2;

      if (is_possible(points, x_coords, y_coords, m)){
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
