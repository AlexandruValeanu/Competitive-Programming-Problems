#include <bits/stdc++.h>

using namespace std;

/*
  Problem: Mathison and the teleportation game
  Author: Alexandru Valeanu
  Score: 100p
  Method: bitmask dp + hashing + parsing
 */

///---------------------------------------------------
const int BUFFER_SIZE = (1 << 16);
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

uint32_t knuth_hash(uint32_t v)
{
    return v * UINT32_C(2654435761);
}

template <const size_t POWER_OF_TWO, class K, class V>
class LinearProbing{
private:

    static const int NIL = 0;
    const size_t mask = (1 << POWER_OF_TWO) - 1;
    pair<K, V> table[1 << POWER_OF_TWO];

    bool check(const size_t pos, const K key) const {
        return table[pos].first != NIL && table[pos].first != key;
    }

    size_t supposedPosition(K key) const{
        uint32_t new_key = knuth_hash(key);
        size_t pos = 0;

        while (check((new_key + pos) & mask, key) == true)
            pos++;

        return (new_key + pos) & mask;
    }

public:

    void update(const K &key, const V &value){
        table[supposedPosition(key)] = make_pair(key, value);
    }

    pair<bool, V> find(const K &key){
        auto p = table[supposedPosition(key)];
        return make_pair(p.first == key, p.second);
    }

    void clear(){
      for (size_t i = 0; i < (1 << POWER_OF_TWO); i++)
        table[i] = pair<K, V>();
    }
};

constexpr int MAX_N = 1000;
constexpr int MAX_MOVES = 9;

constexpr pair<int,int> signs[] = {{-1, -1}, {-1, +1}, {+1, -1}, {+1, +1}};

int board[MAX_N][MAX_N];
pair<int,int> moves[MAX_MOVES];

int R, C;
int NR_MOVES;

bool is_set(int number, int bit){
  return (number >> bit) & 1;
}

bool is_valid(int x, int y){
  return 0 <= x && x < R && 0 <= y && y < C;
}

LinearProbing<22, int, int> cache;

int memo(int x, int y, int mask){
  if (mask == 0)
    return board[x][y];

  auto code = ((x * (R - 1) + y) << 10) ^ mask;
  assert(code != 0);
  auto it = cache.find(code);

  if (it.first)
    return it.second;

  int best = 0;
  pair<int,int> next_move = make_pair(-1, -1);

  for (int bit = 0; bit < NR_MOVES; bit++){
    if (!is_set(mask, bit))
      continue;

    for (auto p: signs){
        int a = x + moves[bit].first * p.first;
        int b = y + moves[bit].second * p.second;

         if (is_valid(a, b)){
           auto tmp = memo(a, b, mask ^ (1 << bit));

           if (tmp > best){
             best = tmp;
             next_move = {a, b};
           }
         }
      }
    }

    best += board[x][y];
    cache.update(code, best);
    return best;
}

int main(){
  int T = getInt();
  assert(1 <= T && T <= 100);

  while (T--){
    R = getInt(); C = getInt(); NR_MOVES = getInt();
    assert(1 <= R && R <= 1000);
    assert(1 <= C && C <= 1000);
    assert(1 <= NR_MOVES && NR_MOVES <= 9);

    int Sx = getInt();
    int Sy = getInt();

    assert(0 <= Sx && Sx < R);
    assert(0 <= Sy && Sy < C);

    for (int i = 0; i < NR_MOVES; i++)
      moves[i].first = getInt();

    for (int i = 0 ; i < NR_MOVES; i++)
      moves[i].second = getInt();

    for (int i = 0; i < NR_MOVES; i++){
      assert(0 <= moves[i].first && moves[i].first <= R);
      assert(0 <= moves[i].second && moves[i].second <= C);
    }

    for (int i = 0; i < R; i++)
      for (int j = 0; j < C; j++){
        board[i][j] = getInt();
        assert(1 <= board[i][j] && board[i][j] <= 1000000);
      }

    cache.clear();
    cout << memo(Sx, Sy, (1 << NR_MOVES) - 1) << "\n";
  }

  return 0;
}
