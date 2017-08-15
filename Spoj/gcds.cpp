#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <array>
#include <bitset>
#include <unordered_set>

using namespace std;

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

constexpr int MAX_VALUE = 10000000;
constexpr int MAX_N = 100000;

int factor[MAX_VALUE + 1];
vector<int> primes;

void gen_primes(){
  factor[1] = 1;

  for (int i = 2; i <= MAX_VALUE; i++)
    if (!factor[i]){
      primes.push_back(i);

      for (int j = i; j <= MAX_VALUE; j += i)
        factor[j] = i;
    }
}

int main(int argc, char const *argv[]) {
  gen_primes();

   int T = getInt();

   while (T--){
     int N = getInt();
     unordered_set<int> uset;
     uset.reserve(4096);
     uset.max_load_factor(0.3);

     for (int i = 0; i < N; i++){
       int x = getInt();

       while (x > 1){
         uset.insert(factor[x]);
         x /= factor[x];
       }
     }

     int i = 0;
     while (uset.find(primes[i]) != uset.end())
      i++;

     cout << primes[i] << "\n";
   }

  return 0;
}
