#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

constexpr static int INF = 1000000;
using LL = long long;

template <typename T>
class Vec3
{
public:

public:
  T x;
  T y;
  T z;

public:
  inline Vec3& operator= (const Vec3& rhs)
  {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
  }

public:
  inline bool operator==(const Vec3& rhs) const
  {
    return ((x == rhs.x) && (y == rhs.y)) && (z == rhs.z);
  }

  inline bool operator!=(const Vec3& rhs) const
  {
    return !(operator==(rhs));
  }

  inline Vec3 operator+ (const Vec3& rhs) const
  {
    return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
  }

  inline Vec3 operator- (const Vec3& rhs) const
  {
    return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
  }

  template<typename U>
  inline Vec3 operator* (U rhs) const
  {
    return Vec3(T(x * rhs), T(y * rhs), T(z * rhs));
  }

  template<typename U>
  inline Vec3 operator/ (U rhs) const
  {
    return Vec3(T(x / rhs), T(y / rhs), T(z / rhs));
  }

  inline Vec3 operator- () const
  {
    return Vec3(-x, -y, -z);
  }

  inline Vec3& operator+= (const Vec3& rhs)
  {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }

  inline Vec3& operator-= (const Vec3& rhs)
  {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }

  template<typename U>
  inline Vec3& operator*= (U rhs)
  {
    x = T(x * rhs);
    y = T(y * rhs);
    z = T(z * rhs);
    return *this;
  }

  template<typename U>
  inline Vec3& operator/= (U rhs)
  {
    x = T(x / rhs);
    y = T(y / rhs);
    z = T(z / rhs);
    return *this;
  }

public:
  inline double norm() const
  {
    return sqrt(squaredNorm());
  }

  inline T squaredNorm() const
  {
    return ((x * x) + (y * y) + (z * z));
  }

  inline double length() const 
  {
    return norm();
  }

  inline double length(const Vec3& pos) const
  {
    return sqrt(squaredLength(pos));
  }

  inline T squaredLength() const 
  {
    return squaredNorm();
  }

  inline T squaredLength(const Vec3& pos) const
  {
    return (((x - pos.x) * (x - pos.x)) + ((y - pos.y) * (y - pos.y)) + ((z - pos.z) * (z - pos.z)));
  }
  
  inline T l1length() const {
    return abs(x) + abs(y) + abs(z);
  }

  inline T l1length(const Vec3& pos) const {
    return abs(x - pos.x) + abs(y - pos.y) + abs(z - pos.z);
  }

  inline void normalize()
  {
    double l = norm();
    if (l < numeric_limits<double>::epsilon()) {
      x = 0;
      y = 0;
      z = 0;
    }
    else {
      x = (T)(x / l);
      y = (T)(y / l);
      z = (T)(z / l);
    }
  }

  inline Vec3 normalized() const
  {
    Vec3 n(*this);
    n.normalize();
    return n;
  }

  inline T dot(const Vec3& rhs) const
  {
    return x * rhs.x + y * rhs.y + z * rhs.z;
  }


public:
  static const Vec3& xAxis() { static Vec3 vec(1, 0, 0); return vec; }
  static const Vec3& yAxis() { static Vec3 vec(0, 1, 0); return vec; }
  static const Vec3& zAxis() { static Vec3 vec(0, 0, 1); return vec; }
  static const Vec3& zero() { static Vec3 vec(0, 0, 0); return vec; }
  friend ostream& operator<< (ostream& ostr, const Vec3& rhs) {
    ostr << setprecision(15) << rhs.x << " " << rhs.y << " " << rhs.z;
    return ostr;
  }

  friend istream& operator>> (istream& istr, Vec3& rhs) {
    istr >> rhs.x >> rhs.y >> rhs.z;
    return istr;
  }

public:
  Vec3() : x(T(0)), y(T(0)), z(T(0)) {}

  Vec3(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}

  Vec3(const Vec3& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}

  ~Vec3() {}

};

using Point = Vec3<LL>;

class Octree {
public:
  Octree(int maxdepth, const Point& low, const Point& high) 
    : depth(maxdepth), low(low), high(high), count(0) {}

  ~Octree() {
    for (Octree* child : children) {
      delete child;
    }
  }

  void insert(const Point& p) {
    assert(contains(p));
    count++;
    if (depth == 0) {
      points.push_back(p);
    }
    else {
      Point mid = (low + high) / 2;
      int idx = (p.x > mid.x) + (int(p.y > mid.y) << 1) + (int(p.z > mid.z) << 2);
      if (children[idx] == nullptr) {
        switch (idx) {
          case 0: children[idx] = new Octree(depth-1, {low.x, low.y, low.z}, {mid.x, mid.y, mid.z}); break;
          case 1: children[idx] = new Octree(depth-1, {mid.x+1, low.y, low.z}, {high.x, mid.y, mid.z}); break;
          case 2: children[idx] = new Octree(depth-1, {low.x, mid.y+1, low.z}, {mid.x, high.y, mid.z}); break;
          case 3: children[idx] = new Octree(depth-1, {mid.x+1, mid.y+1, low.z}, {high.x, high.y, mid.z}); break;
          case 4: children[idx] = new Octree(depth-1, {low.x, low.y, mid.z+1}, {mid.x, mid.y, high.z}); break;
          case 5: children[idx] = new Octree(depth-1, {mid.x+1, low.y, mid.z+1}, {high.x, mid.y, high.z}); break;
          case 6: children[idx] = new Octree(depth-1, {low.x, mid.y+1, mid.z+1}, {mid.x, high.y, high.z}); break;
          case 7: children[idx] = new Octree(depth-1, {mid.x+1, mid.y+1, mid.z+1}, {high.x, high.y, high.z}); break;
        }
      }
      children[idx]->insert(p);
    }
  }

  vector<Point> corners() const {
    return {
      {low.x, low.y, low.z}, {high.x, low.y, low.z}, {low.x, high.y, low.z}, {high.x, high.y, low.z},
      {low.x, low.y, high.z}, {high.x, low.y, high.z}, {low.x, high.y, high.z}, {high.x, high.y, high.z}
    };
  }

  bool contains(const Point p) const {
    return low.x <= p.x && p.x <= high.x 
        && low.y <= p.y && p.y <= high.y 
        && low.z <= p.z && p.z <= high.z;
  }

  bool squaredDistance(const Point p) const {
      LL dx = max({low.x - p.x, 0LL, p.x - high.x});
      LL dy = max({low.y - p.y, 0LL, p.y - high.y});
      LL dz = max({low.z - p.z, 0LL, p.z - high.z});
      return dx*dx + dy*dy + dz*dz;
  }

  int query(const Point p, LL r) const {
    if (count == 0) {
      return 0;
    }
    LL r2 = r * r;
    const auto corners = this->corners();
    if (!this->contains(p) && squaredDistance(p) > r2) {
      return 0;
    }

    Point farthest_corner =
        *max_element(corners.begin(), corners.end(),
                     [&p](const Point& lhs, const Point& rhs) {
                       return lhs.squaredLength(p) < rhs.squaredLength(p);
                     });
    if (farthest_corner.squaredLength(p) <= r2) {
      return count;
    }
    int res = 0;
    if (depth == 0) {
      for (const auto& item : points) {
        res += item.squaredLength(p) <= r2;
      }
    }
    else {
      for (Octree* child : children) {
        if (child != nullptr) {
          res += child->query(p, r);
        }
      }
    }
    return res;
  }

  friend ostream& operator<<(ostream& ostr, const Octree& rhs) {
    ostr << "Octree(d: " << rhs.depth << ", n: " << rhs.count << ", low: " << rhs.low << ", high:" << rhs.high << ")\n";
    for (int i = 0; i < 8; ++i) {
      ostr << "-" << i << "- ";
      if (rhs.children[i] == nullptr) {
        ostr << "empty\n";
      }
      else {
        ostr << *rhs.children[i] << "\n";
      }
    }
    ostr << "\n";
    return ostr;
  }

  const int depth;
  const Point low;
  const Point high;
  int count;
  vector<Point> points;
  Octree* children[8] = {nullptr};
};



int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;

  Point minp(0, 0, 0);
  Point maxp(INF, INF, INF);
  vector<Point> points;
  points.reserve(N);
  for (int i = 0; i < N; ++i) {
    Point p;
    cin >> p;
    points.push_back(p);
  }

  Octree tree(2, minp, maxp);
  for (const auto& p : points) {
    tree.insert(p);
  }
  //cout << tree;

  int M;
  cin >> M;
  for (int i = 0; i < M; ++i) {
    Point p;
    LL r;
    cin >> p >> r;
    int ans = tree.query(p, r);
    cout << ans << "\n";
  }

  return 0;
}
