#include <bits/stdc++.h>

using namespace std;

constexpr int SIGMA = 26;

struct Node{
  shared_ptr<Node> child[SIGMA];
  size_t max_length = 0;
  size_t size = 0;
  size_t count = 0;
};

auto root = make_shared<Node>();

void update_trie(shared_ptr<Node> &node, const string& str, bool add, size_t p = 0){
  if (p == str.size()){
    if (add)
      node->count++;
    else
      node->count--;

    if (node->count == 0)
      node->max_length = 0;
    else
      node->max_length = str.size();

    node->size = node->count;
    for (int i = 0; i < SIGMA; i++)
      if (node->child[i]){
        node->max_length = max(node->max_length, node->child[i]->max_length);
        node->size += node->child[i]->size;
      }
  }
  else{
    if (!node->child[str[p] - 'a'])
      node->child[str[p] - 'a'] = make_shared<Node>();

    update_trie(node->child[str[p] - 'a'], str, add, p + 1);

    node->size = node->count;
    for (int i = 0; i < SIGMA; i++){
      if (node->child[i]){
        node->max_length = max(node->max_length, node->child[i]->max_length);
        node->size += node->child[i]->size;
      }
    }
  }
}

string get_prefix(shared_ptr<Node> node, const string &str, size_t p = 0){
  if (!node)
    return "";

  if (p == str.size()){
    if (node->count == 1)
      return str;
    else
      return "";
  }

  if (node->count == 1)
    return str.substr(0, p);
  else
    return get_prefix(node->child[str[p] - 'a'], str, p + 1);
}

int main(){
  ios_base::sync_with_stdio(false);

  int N, K;
  cin >> N >> K;

  vector<string> strings(N);

  for (auto &x: strings)
    cin >> x;

  sort(strings.begin(), strings.end(), [](auto &x, auto &y){
    return x.size() < y.size();
  });

  for (auto &s: strings){
    string prefix_string = get_prefix(root, s);

    if (!prefix_string.empty()){
      update_trie(root, prefix_string, false);
    }

    update_trie(root, s, true);

    if ((int)root->size == K)
      break;
  }

  if ((int)root->size == K)
    cout << root->max_length << "\n";
  else
    cout << "-1\n";

  return 0;
}
