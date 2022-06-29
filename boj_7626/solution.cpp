#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using LL = long long;

template<typename T>
class CountingSegTree {
 public:
  vector<T> tree_;
  size_t n_;

  vector<int> count_;

 public:
  CountingSegTree(size_t size) {
    n_ = size;
    tree_.resize(4 * n_, 0);
    count_.resize(4 * n_, 0);
  }

  T query(size_t left, size_t right) {
    return query(left, right, 1, 0, n_ - 1);
  }

  void updateRange(size_t left, size_t right, int inc, 
      const function<T(int, size_t, size_t)>& transform) {
    updateRange(left, right, inc, 1, 0, n_ - 1, transform);
  }

 private:
  T query(size_t left,
          size_t right,
          size_t node_idx,
          size_t node_left,
          size_t node_right) {
    if (right < node_left || node_right < left) {
      return 0;
    }
    if (left <= node_left && node_right <= right) {
      return tree_[node_idx];
    }
    size_t mid = (node_left + node_right) / 2;
    T res_left = query(left, right, node_idx * 2, node_left, mid);
    T res_right = query(left, right, node_idx * 2 + 1, mid + 1, node_right);
    return aggregate(res_left, res_right);
  }

  void updateRange(
      size_t left, 
      size_t right,
      const int& inc,
      size_t node_idx,
      size_t node_left,
      size_t node_right, 
      const function<T(int, size_t, size_t)>& transform) {
    if (right < node_left || node_right < left) {
      return;
    }
    if (left <= node_left && node_right <= right) {
      count_[node_idx] += inc;
    }
    else {
      size_t mid = (node_left + node_right) / 2;
      updateRange(left, right, inc, node_idx * 2, node_left, mid, transform);
      updateRange(left, right, inc, node_idx * 2 + 1, mid+1, node_right, transform);
    }

    if (count_[node_idx]) {
      tree_[node_idx] = transform(0, node_left, node_right);
    }
    else if (node_left == node_right) {
      tree_[node_idx] = 0;
    }
    else {
      tree_[node_idx] = aggregate(tree_[node_idx * 2], tree_[node_idx * 2 + 1]);
    }
  }

  static T aggregate(const T& lhs, const T& rhs) { return lhs + rhs; }
};

struct RectEnd {
  int x;
  int y1;
  int y2;
  bool isEnd=false;
  
  friend bool operator< (const RectEnd& l, const RectEnd& r) {
    return l.x < r.x;
  }
};

int main() {
  int N;
  scanf("%d", &N);
  
  vector<RectEnd> es;
  vector<int> ys;
  es.reserve(2*N);
  ys.reserve(2*N);
  for (int i = 0; i < N; ++i) {
    int x1, y1, x2, y2;
    scanf("%d %d %d %d", &x1, &x2, &y1, &y2);
    es.push_back({x1, y1, y2, false});
    es.push_back({x2, y1, y2, true});
    ys.push_back(y1);
    ys.push_back(y2);
  }

  sort(all(es));
  sort(all(ys));
  ys.erase(unique(all(ys)), ys.end());
  
  map<int, int> yIndex;
  for (int y : ys) {
    yIndex[y] = yIndex.size();
  }
  
  CountingSegTree<int> seg(ys.size()-1);

  LL ans = 0;
  for (int i = 0; i < es.size()-1; ++i) {
    const auto& l = es[i];
    const auto& r = es[i+1];

    int y1i = yIndex[l.y1];
    int y2i = yIndex[l.y2];

    seg.updateRange(y1i, y2i-1, (int)(l.isEnd ? -1 : +1), 
        [&](int i, size_t l, size_t r)->int { return ys[r+1] - ys[l]; });
    ans += (LL)(r.x - l.x) * (LL)seg.tree_[1];
  }
  printf("%lld\n", ans);
  
  return 0;
}
