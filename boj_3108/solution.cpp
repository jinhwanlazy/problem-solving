#include <bits/stdc++.h>
using namespace std;

class Square
{
  using T = int;

public:
  
  T left;
  T right;
  T bottom;
  T top;
public:
  inline bool operator==(const Square& rhs) const {
    return (top == rhs.top && bottom == rhs.bottom && left == rhs.left && right == rhs.right);
  }

public:
  T area() const { return (top - bottom) * (right - left); }

  bool touches(const Square& other) const {
    if (other.right < left || right < other.left) {
      return false;
    }
    if (other.top < bottom || top < other.bottom) {
      return false;
    }
    if (other.left < left && right < other.right && other.bottom < bottom && top < other.top) {
      return false;
    }
    if (left < other.left && other.right < right && bottom < other.bottom && other.top < top) {
      return false;
    }
    return true;
  }

public:
  friend istream& operator>> (istream& istr, Square& rhs) {
    //istr >> rhs.left >> rhs.right >> rhs.bottom >> rhs.top;
    istr >> rhs.left >> rhs.bottom >> rhs.right >> rhs.top;
    return istr;
  }

public:
  Square() : left(0), right(1), bottom(0), top(1) {}

  Square(T l, T r, T b, T t) : left(l), right(r), bottom(b), top(t) {}

  ~Square() {}
};

struct UnionFindSet {
  UnionFindSet(int size) : root_(size), rank_(size, 0), size_(size, 1) {
    for (int i = 0; i < size; ++i) {
      root_[i] = i;
    }
  }

  int find(int i) {
    if (root_[i] == i) {
      return i;
    }
    int root = find(root_[i]);
    root_[i] = root;
    return root;
  }

  int merge(int i, int j) {
    int i_root = find(i);
    int j_root = find(j);
    if (i_root == j_root) {
      return size_[i_root];
    }
    if (rank_[i_root] < rank_[j_root]) {
      root_[i_root] = j_root;
      size_[j_root] += size_[i_root];
      size_[i_root] = 0;
      return size_[j_root];
    }
    root_[j_root] = i_root;
    size_[i_root] += size_[j_root];
    size_[j_root] = 0;
    if (rank_[i_root] == rank_[j_root]) {
      rank_[i_root]++;
    }
    return size_[i_root];
  }

  bool resize(size_t size) {
    size_t size_before = root_.size();

    if (size_before >= size) {
      return false;
    }
    root_.resize(size);
    rank_.resize(size, 0);
    size_.resize(size, 1);
    for (size_t i = size_before; i < size; ++i) {
      root_[i] = i;
    }
    return true;
  }

  size_t size() const {
    return root_.size();
  }

  vector<int> root_;
  vector<int> rank_;
  vector<int> size_;
};


void solve() {
  int N;
  scanf("%d", &N);

  vector<Square> squares(N);
  for (int i = 0; i < N; ++i) {
    cin >> squares[i];
  }
  
  int ans = 0;
  for (const auto& [l, r, b, t] : squares) {
    if (l <= 0 && 0 <= r && (b == 0 || t == 0)) {
      ans -= 1;
      break;
    }
    if (b <= 0 && 0 <= t && (l == 0 || r == 0)) {
      ans -= 1;
      break;
    }
  }
  
  UnionFindSet s(N);
  for (int i = 0; i < N-1; ++i) {
    for (int j = i + 1; j < N; ++j) {
      if (squares[i].touches(squares[j])) {
        s.merge(i, j);
      }
    }
  }
  
  set<int> unique;
  for (int i = 0; i < N; ++i) {
    unique.insert(s.find(i));
  }
  ans += unique.size();
  printf("%d\n", ans);

}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
