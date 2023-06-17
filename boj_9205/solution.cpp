#include <bits/stdc++.h>
using namespace std;

class Vec2 {
public:
  using T = long;
  T x;
  T y;

public:
  inline Vec2& operator=(const Vec2& rhs) { x = rhs.x; y = rhs.y; return *this; }

public:
  inline bool operator==(const Vec2& rhs) const { return ((x == rhs.x) && (y == rhs.y)); }
  inline bool operator!=(const Vec2& rhs) const { return !(operator==(rhs)); }
  inline Vec2 operator+(const Vec2& rhs) const { return Vec2(x + rhs.x, y + rhs.y); }
  inline Vec2 operator-(const Vec2& rhs) const { return Vec2(x - rhs.x, y - rhs.y); }
  inline Vec2 operator*(T rhs) const { return Vec2(T(x * rhs), T(y * rhs)); }
  inline Vec2 operator/(T rhs) const { return Vec2(T(x / rhs), T(y / rhs)); }
  inline Vec2 operator-() const { return Vec2(-x, -y); }
  inline Vec2& operator+=(const Vec2& rhs) { x += rhs.x; y += rhs.y; return *this; }
  inline Vec2& operator-=(const Vec2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
  inline Vec2& operator*= (T rhs) { x = T(x * rhs); y = T(y * rhs); return *this; }
  inline Vec2& operator/= (T rhs) { x = T(x / rhs); y = T(y / rhs); return *this; }

  inline double norm() const { return sqrt(squaredNorm()); }
  inline T squaredNorm() const { return ((x * x) + (y * y)); }
  inline T norm1() const { return abs(x) + abs(y); }
  inline void normalize()
  {
    double l = norm();
    if (l < numeric_limits<double>::epsilon()) {
      x = 0;
      y = 0;
    }
    else {
      x = (T)(x / l);
      y = (T)(y / l);
    }
  }

  inline Vec2 normalized() const
  {
    Vec2 n(*this);
    n.normalize();
    return n;
  }

  inline bool close(const Vec2& rhs,
                    const double span = 1.0,
                    const double tol = 1e-20) const {
    return ((*this - rhs).squaredNorm() / span) < tol;
  }

  inline T dot(const Vec2& rhs) const { return x * rhs.x + y * rhs.y; }
  inline T cross(const Vec2& rhs) const { return x * rhs.y - y * rhs.x; }
  inline double angle(const Vec2& rhs) const
  {
    double sqlen = squaredNorm();
    double sqlen2 = rhs.squaredNorm();

    if (sqlen == 0.0 || sqlen2 == 0.0) {
      return 0.0;
    }

    double val = dot(rhs) / sqrt(sqlen) / sqrt(sqlen2);
    val = std::max(-1.0, min(val, 1.0));
    return acos(val);
  }

public:
  static const Vec2& xAxis() { static Vec2 vec(1, 0); return vec; }
  static const Vec2& yAxis() { static Vec2 vec(0, 1); return vec; }
  static const Vec2& zero() { static Vec2 vec(0, 0); return vec; }
  friend ostream& operator<<(ostream& ostr, const Vec2& rhs) {
    ostr << setprecision(15) << rhs.x << " " << rhs.y;
    return ostr;
  }

  friend istream& operator>>(istream& istr, Vec2& rhs) {
    istr >> rhs.x >> rhs.y;
    return istr;
  }

  friend bool operator<(const Vec2& lhs, const Vec2& rhs) {
    return lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y < rhs.y;
  }

public:
  Vec2() : x(T(0)), y(T(0)) {}
  Vec2(T x_, T y_) : x(x_), y(y_) {}
  Vec2(const Vec2& rhs) : x(rhs.x), y(rhs.y) {}
  ~Vec2() {}
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
  cin >> N;

  vector<Vec2> points(N+2);
  for (int i = 0; i < N+2; ++i) {
    cin >> points[i];
  }

  UnionFindSet ufs(N+2);
  for (int i = 0; i < N + 1; ++i) {
    for (int j = i + 1; j < N + 2; ++j) {
      auto d = points[i] - points[j];
      if (abs(d.x) + abs(d.y) <= 50 * 20) {
        ufs.merge(i, j);
      }
    }
  }
  if (ufs.find(0) == ufs.find(N+1)) {
    cout << "happy\n";
  }
  else {
    cout << "sad\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);

  int T;
  cin >> T;
  
  while (T--) {
    solve();
  }

  return 0;
}
