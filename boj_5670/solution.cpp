#include <bits/stdc++.h>
using namespace std;

template <unsigned N, const char* alphabets>
class Trie_ {
 private:
  struct Node {
    Node* children[N] = {nullptr};
    size_t n_children = 0;
    bool is_terminal = false;

    void clear() {
      for (int i = 0; i < N; ++i) {
        if (children[i] != nullptr) {
          children[i]->clear();
          delete children[i];
          children[i] = nullptr;
        }
      }
    }
  };
  
  Node root_;
  unordered_map<char, size_t> char2idx_;

 public:
  Trie_() {
    for (int i = 0; i < N; ++i) {
      char2idx_[alphabets[i]] = i;
    }
  }
  
  ~Trie_() {
    root_.clear();
  }
  
  void insert(const string& key) {
    Node* node = &root_;
    for (char c : key) {
      int idx = char2idx_[c];
      if (node->children[idx] == nullptr) {
        node->children[idx] = new Node();
        node->n_children++;
      }
      node = node->children[idx];
    }
    node->is_terminal = true;
  }

  int count_type(const string& key) {
    int res = 0;
    Node* node = &root_;
    for (int i = 0; i < key.size(); ++i) {
      const char c = key[i];
      int child_idx = char2idx_[c];
      if (node == &root_ || node->is_terminal || node->n_children > 1) {
        res += 1;
      }
      node = node->children[child_idx];
    }
    return res;
  }

};

constexpr char lowercase[27] = "abcdefghijklmnopqrstuvwxyz";
using Trie = Trie_<26, lowercase>;

int main() {
  int T;
  while (cin >> T) {
    Trie trie;
    vector<string> words;
    words.reserve(T);
    while (T--) {
      string s;
      cin >> s;
      words.push_back(s);
      trie.insert(s);
    }
    double mean_typing = 0;
    for (const string& word : words) {
      mean_typing += trie.count_type(word);
      //cout << word << ", " <<  trie.count_type(word) << "\n";
    }
    mean_typing /= (double)words.size();
    cout << fixed << setprecision(2) << mean_typing << "\n";
  }

  return 0;
}
