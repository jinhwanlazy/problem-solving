#include <bits/stdc++.h>
using namespace std;

using LL = long long;

struct UnionFindSet {
  UnionFindSet(int size) : root_(size) {
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

  void merge(int i, int j) {
    int i_root = find(i);
    int j_root = find(j);
    if (i_root == j_root) {
      return;
    }
    // if (rank_[i_root] < rank_[j_root]) {
    root_[i_root] = j_root;
    // return;
    //}
    // root_[j_root] = i_root;
    // if (rank_[i_root] == rank_[j_root]) {
    // rank_[i_root]++;
    //}
  }

  vector<int> root_;
  // vector<int> rank_;
};

class Point3 {
  using T = int;

 public:
  T x;
  T y;
  T z;

 public:
  inline Point3& operator=(const Point3& rhs) {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
  }

 public:
  inline bool operator==(const Point3& rhs) const {
    return ((x == rhs.x) && (y == rhs.y) && (z == rhs.z));
  }

  inline bool operator!=(const Point3& rhs) const { return !(operator==(rhs)); }

  inline Point3 operator+(const Point3& rhs) const {
    return Point3(x + rhs.x, y + rhs.y, z + rhs.z);
  }

  inline Point3 operator-(const Point3& rhs) const {
    return Point3(x - rhs.x, y - rhs.y, z - rhs.z);
  }

  inline Point3 operator*(double rhs) const {
    return Point3(T(x * rhs), T(y * rhs), T(z * rhs));
  }

  inline Point3 operator*(const Point3& rhs) const {
    return Point3(T(x * rhs.x), T(y * rhs.y), T(z * rhs.z));
  }

  inline Point3 operator/(double rhs) const {
    return Point3(T(x / rhs), T(y / rhs), T(z / rhs));
  }

  inline Point3 operator-() const { return Point3(-x, -y, -z); }

  inline Point3& operator+=(const Point3& rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }

  inline Point3& operator-=(const Point3& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }

  inline Point3& operator*=(double rhs) {
    x = T(x * rhs);
    y = T(y * rhs);
    z = T(z * rhs);
    return *this;
  }

  inline Point3& operator*=(const Point3& rhs) {
    x = T(x * rhs.x);
    y = T(y * rhs.y);
    z = T(z * rhs.z);
    return *this;
  }

  inline Point3& operator/=(double rhs) {
    // TODO: Need to consider zero tolerance
    assert(fabs(rhs) > numeric_limits<double>::epsilon());
    x = T(x / rhs);
    y = T(y / rhs);
    z = T(z / rhs);
    return *this;
  }

 public:
  inline double norm() const { return length(); }

  inline double squaredNorm() const { return squaredLength(); }

  inline double length() const { return sqrt(squaredLength()); }

  inline double squaredLength() const { return ((x * x) + (y * y) + (z * z)); }

  inline double length(const Point3& rhs) const {
    return sqrt(squaredLength(rhs));
  }

  inline double squaredLength(const Point3& rhs) const {
    return ((x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y) +
            (z - rhs.z) * (z - rhs.z));
  }

  inline T l1() const { return abs(x) + abs(y) + abs(z); }

  inline T l1(const Point3& rhs) const {
    return abs(x - rhs.x) + abs(y - rhs.y) + abs(z - rhs.z);
  }

  inline void normalize() {
    double l = norm();

    if (l < numeric_limits<double>::epsilon()) {
      x = y = z = 0;
    } else {
      x = (T)(x / l);
      y = (T)(y / l);
      z = (T)(z / l);
    }
  }

  inline Point3 normalized() const {
    Point3 n(*this);
    n.normalize();
    return n;
  }

  inline void reverse() {
    x *= T(-1);
    y *= T(-1);
    z *= T(-1);
  }

  inline T dot(const Point3& rhs) const {
    return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
  }

  inline Point3 cross(const Point3& rhs) const {
    return Point3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z,
                  x * rhs.y - y * rhs.x);
  }

  inline Point3 normalizedCross(const Point3& rhs) const {
    Point3 nc = cross(rhs);
    nc.normalize();
    return nc;
  }

  inline double angle(const Point3& rhs) const {
    double sqlen = squaredLength();
    double sqlen2 = rhs.squaredLength();

    if (sqlen == 0.0 || sqlen2 == 0.0) {  // TBD: use epsilon ?
      return 0.0;
    }

    double val = dot(rhs) / std::sqrt(sqlen) / std::sqrt(sqlen2);
    val = std::max(-1.0, std::min(val, 1.0));
    return acos(val);
  }

  inline double acuteAngle(const Point3& rhs) const {
    double ang = angle(rhs);
    return (ang > M_PI_2) ? (M_PI - ang) : ang;
  }

 public:
  static const Point3& xAxis() {
    static Point3 vec(1, 0, 0);
    return vec;
  }
  static const Point3& yAxis() {
    static Point3 vec(0, 1, 0);
    return vec;
  }
  static const Point3& zAxis() {
    static Point3 vec(0, 0, 1);
    return vec;
  }
  static const Point3& zero() {
    static Point3 vec(0, 0, 0);
    return vec;
  }

  friend istream& operator>>(istream& istr, Point3& rhs) {
    istr >> rhs.x >> rhs.y >> rhs.z;
    return istr;
  }

 public:
  Point3() : x(T(0)), y(T(0)), z(T(0)) {}

  Point3(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}

  Point3(const Point3& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}

 public:
  ~Point3() {}
};

struct Edge {
  int u;
  int v;
  int w; /* cost */

  friend bool operator<(const Edge& lhs, const Edge& rhs) {
    return lhs.w > rhs.w;
  }
};

int main() {
  int N;
  scanf("%d", &N);

  vector<Point3> pts(N);
  for (int i = 0; i < N; ++i) {
    cin >> pts[i];
  }

  vector<int> indices(N);
  for (int i = 0; i < N; ++i) {
    indices[i] = i;
  }

  priority_queue<Edge> pq;

  sort(indices.begin(), indices.end(),
       [&pts](int i, int j) { return pts[i].x < pts[j].x; });
  for (int i = 1; i < N; ++i) {
    pq.push({indices[i - 1], indices[i],
             abs(pts[indices[i - 1]].x - pts[indices[i]].x)});
  }
  sort(indices.begin(), indices.end(),
       [&pts](int i, int j) { return pts[i].y < pts[j].y; });
  for (int i = 1; i < N; ++i) {
    pq.push({indices[i - 1], indices[i],
             abs(pts[indices[i - 1]].y - pts[indices[i]].y)});
  }
  sort(indices.begin(), indices.end(),
       [&pts](int i, int j) { return pts[i].z < pts[j].z; });
  for (int i = 1; i < N; ++i) {
    pq.push({indices[i - 1], indices[i],
             abs(pts[indices[i - 1]].z - pts[indices[i]].z)});
  }

  UnionFindSet ufs(N);
  LL ans = 0;
  while (!pq.empty()) {
    auto [u, v, w] = pq.top();
    pq.pop();
    if (ufs.find(u) == ufs.find(v)) {
      continue;
    }
    ans += (LL)w;
    ufs.merge(u, v);
  }
  printf("%lld\n", ans);

  return 0;
}
