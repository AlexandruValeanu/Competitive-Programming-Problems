#include <bits/stdc++.h>

using namespace std;

/*
  Problem: Mathison and the cubic tree
  Author: Alexandru Valeanu
  Score: 100p (all subtasks)
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

constexpr int MAX_VALUE = 1'000'000;
constexpr int MAX_PRIME_FACTORS = 7;
constexpr int MAX_N = 100'000;

int factor[MAX_VALUE + 1];
int pos_primes[MAX_VALUE + 1];

constexpr int MAX_THREE = 80000;
unsigned long long powerOf3[MAX_THREE];

void compute_powers_three(){
  powerOf3[0] = 1;

  for (int i = 1; i < MAX_THREE; i++)
    powerOf3[i] = 3ULL * powerOf3[i - 1];
}

void compute_sieve(){
  memset(pos_primes, -1, sizeof(pos_primes));
  int cnt = 0;

  for (int i = 2; i <= MAX_VALUE; i++)
    if (!factor[i]){
      pos_primes[i] = cnt;
      cnt++;

      for (int j = i; j <= MAX_VALUE; j += i)
        if (!factor[j])
          factor[j] = i;
    }
}

vector<int> tree[MAX_N];
vector<int> values;
int N;

array<pair<int,int>, MAX_PRIME_FACTORS> factorization;
int size_decomp;
int cached_fact = -1;

void compute_prime_factorization(int number){
  if (number == cached_fact)
    return;

  cached_fact = number;
  size_decomp = 0;

  while (number > 1){
    int f = factor[number];
    int e = 0;

    while (number % f == 0){
      number /= f;
      e++;
    }

    e %= 3;

    if (e != 0)
      factorization[size_decomp++] = make_pair(f, e);
  }
}

//---------------divide-et-conquer----------------------------
int subtreeSize[MAX_N];
bool used[MAX_N];
int nodesSubtree[MAX_N];
int lengthPath[MAX_N];

unsigned long long data_node[MAX_N];
unsigned long long data_node_complement[MAX_N];

unsigned long long data_node_without_root[MAX_N];
unsigned long long data_node_complement_without_root[MAX_N];

int countNodes = 0;
int global_answer = -1;

void clear_arrays(){
  countNodes = 0;
  global_answer = -1;

  for (int i = 0; i < N; i++){
    subtreeSize[i] = 0;
    used[i] = false;
    lengthPath[i] = 0;
    nodesSubtree[i] = 0;
    data_node[i] = 0;
    data_node_complement[i] = 0;
    data_node_without_root[i] = 0;
    data_node_complement_without_root[i] = 0;
  }
}

void computeSubtreeSize(int node, int father){
  subtreeSize[node] = 0;

  for (int son: tree[node]){
    if (son != father && used[son] == false){
      computeSubtreeSize(son, node);
      subtreeSize[node] += subtreeSize[son] + 1;
    }
  }
}

int findCentroid(int node, int father, int nrNodes){
  for (int son: tree[node]){
    if (son != father && used[son] == false){
        if (nrNodes / 2 < subtreeSize[son] + 1)
          return findCentroid(son, node, nrNodes);
    }
  }

  return node;
}

array<int, MAX_THREE> expo_number;
array<int, MAX_THREE> expo_complement;

void update_number(unsigned long long &number, unsigned long long &complement, int key, bool add){
  compute_prime_factorization(key);

  for (int i = 0; i < size_decomp; i++){
    auto p = factorization[i];
    p.second %= 3;
    auto pos = pos_primes[p.first];
    assert(pos != -1);

    int d = expo_number[pos];
    number -= 1ULL * d * powerOf3[pos];
    complement -= 1ULL * expo_complement[pos] * powerOf3[pos];

    assert(0 <= p.second && p.second < 3);

    if (add)
      d = (d + p.second) % 3;
    else
      d = (d - p.second + 3) % 3;

    number += 1ULL * d * powerOf3[pos];
    complement += 1ULL * ((3 - d) % 3) * powerOf3[pos];

    expo_number[pos] = d;
    expo_complement[pos] = ((3 - d) % 3);
  }
}

void computeData(int node, int father, int length, unsigned long long &number, unsigned long long &complement, int root){
  nodesSubtree[ countNodes++ ] = node;
  lengthPath[node] = length;

  update_number(number, complement, values[node], true);
  data_node[node] = number;
  data_node_complement[node] = complement;

  update_number(number, complement, values[root], false);
  data_node_without_root[node] = number;
  data_node_complement_without_root[node] = complement;

  update_number(number, complement, values[root], true);

  for (int son: tree[node]){
    if (son != father && used[son] == false){
      computeData(son, node, length + 1, number, complement, root);
    }
  }

  update_number(number, complement, values[node], false);
}

void computePaths(int node){
  unordered_map<unsigned long long, int> uset;

  unsigned long long root_number = 0;
  unsigned long long root_complement = 0;

  update_number(root_number, root_complement, values[node], true);

  if (root_number == root_complement)
    global_answer = max(global_answer, 1);

  data_node[node] = root_number;
  data_node_complement[node] = root_complement;

  data_node_without_root[node] = 0;
  data_node_complement_without_root[node] = 0;

  // in hash-table without root
  uset[data_node[node]] = 1;

  for (int son: tree[node]){
    if (used[son])
      continue;

    countNodes = 0;
    unsigned long long number = root_number;
    unsigned long long complement = root_complement;
    computeData(son, node, 1 + 1, number, complement, node);

    ///query
    for (int i = 0; i < countNodes; ++i){
        int v = nodesSubtree[i];

        if (data_node[v] == data_node_complement[v]){
          global_answer = max(global_answer, lengthPath[v]);
        }

        auto complement = data_node_complement_without_root[v];

        auto it = uset.find(complement);
        if (it != uset.end()){
          global_answer = max(global_answer, lengthPath[v] + it->second - 1);
        }
    }

    ///update
    for (int i = 0; i < countNodes; ++i){
        int v = nodesSubtree[i];
        uset[data_node[v]] = max(uset[data_node[v]], lengthPath[v]);
    }
  }

  update_number(root_number, root_complement, values[node], false);
}

void divide_conquer(int node, int nrNodes){
  if (nrNodes == 1)
  return;

  computeSubtreeSize(node, -1);

  int center = findCentroid(node, -1, nrNodes);
  used[center] = true;

  computePaths(center);

  int sumKids = 0;
  int upNode = -1;

  for (int son: tree[center]){
    if (used[son] == false){
      if (subtreeSize[son] < subtreeSize[center]){
        divide_conquer(son, subtreeSize[son] + 1);
        sumKids += subtreeSize[son] + 1;
      }
      else
        upNode = son;
    }
  }

  if (upNode != -1)
    divide_conquer(upNode, nrNodes - sumKids - 1);
}

template<class T>
bool is_cube(T n){
  long long root(round(cbrt(n)));
  return n == root * root * root;
}

int main(){
  //ios_base::sync_with_stdio(false);
  compute_sieve();
  compute_powers_three();

  int T = getInt();

  while (T--){
    N = getInt();
    assert(1 <= N && N <= MAX_N);

    values.resize(N);
    for (auto &x: values){
      x = getInt();
      assert(1 <= x && x <= MAX_VALUE);
    }

    for (int i = 0; i < N; i++)
      tree[i].clear();

    for (int i = 0; i < N - 1; i++){
      int u = getInt();
      int v = getInt();
      u--; v--;

      assert(0 <= u && u < N);
      assert(0 <= v && v < N);
      assert(u != v);

      tree[u].emplace_back(v);
      tree[v].emplace_back(u);
    }

    clear_arrays();

    for (int i = 0; i < N; i++)
      if (is_cube(values[i]))
        global_answer = 1;

    divide_conquer(0, N);
    cout << global_answer << "\n";
  }

  return 0;
}
