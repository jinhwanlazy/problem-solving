#include <bits/stdc++.h>
using namespace std;

class Vec2
{
public:
  using T = double;

public:
  T x;
  T y;

public:
  inline Vec2& operator= (const Vec2& rhs)
  {
    x = rhs.x;
    y = rhs.y;
    return *this;
  }

public:
  inline bool operator==(const Vec2& rhs) const
  {
    return ((x == rhs.x) && (y == rhs.y));
  }

  inline bool operator!=(const Vec2& rhs) const
  {
    return !(operator==(rhs));
  }

  inline Vec2 operator+ (const Vec2& rhs) const
  {
    return Vec2(x + rhs.x, y + rhs.y);
  }

  inline Vec2 operator- (const Vec2& rhs) const
  {
    return Vec2(x - rhs.x, y - rhs.y);
  }

  inline Vec2 operator* (T rhs) const
  {
    return Vec2(T(x * rhs), T(y * rhs));
  }

  inline Vec2 operator/ (T rhs) const
  {
    return Vec2(T(x / rhs), T(y / rhs));
  }

  inline Vec2 operator- () const
  {
    return Vec2(-x, -y);
  }

  inline Vec2& operator+= (const Vec2& rhs)
  {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  inline Vec2& operator-= (const Vec2& rhs)
  {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  inline Vec2& operator*= (T rhs)
  {
    x = T(x * rhs);
    y = T(y * rhs);
    return *this;
  }

  inline Vec2& operator/= (T rhs)
  {
    x = T(x / rhs);
    y = T(y / rhs);
    return *this;
  }

public:
  inline double norm() const
  {
    return sqrt(squaredNorm());
  }

  inline T squaredNorm() const
  {
    return ((x * x) + (y * y));
  }

  inline double length() const 
  {
    return norm();
  }

  inline double length(const Vec2& pos) const
  {
    return sqrt(squaredLength(pos));
  }

  inline T squaredLength() const 
  {
    return squaredNorm();
  }

  inline T squaredLength(const Vec2& pos) const
  {
    return (((x - pos.x) * (x - pos.x)) + ((y - pos.y) * (y - pos.y)));
  }
  
  inline T l1length() const {
    return abs(x) + abs(y);
  }

  inline T l1length(const Vec2& pos) const {
    return abs(x - pos.x) + abs(y - pos.x);
  }

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

  inline T dot(const Vec2& rhs) const
  {
    return x * rhs.x + y * rhs.y;
  }

  inline T cross(const Vec2& rhs) const
  {
    return x * rhs.y - y * rhs.x;
  }

  inline double angle(const Vec2& rhs) const
  {
    double sqlen = squaredLength();
    double sqlen2 = rhs.squaredLength();

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
  friend ostream& operator<< (ostream& ostr, const Vec2& rhs) {
    ostr << setprecision(15) << rhs.x << " " << rhs.y;
    return ostr;
  }

  friend istream& operator>> (istream& istr, Vec2& rhs) {
    istr >> rhs.x >> rhs.y;
    return istr;
  }

  friend bool operator< (const Vec2& lhs, const Vec2& rhs) {
    return lhs.x != rhs.x ? lhs.x < rhs.x : lhs.y < rhs.y;
  }

public:
  Vec2() : x(T(0)), y(T(0)) {}

  Vec2(T x_, T y_) : x(x_), y(y_) {}

  Vec2(const Vec2& rhs) : x(rhs.x), y(rhs.y) {}

  ~Vec2() {}

public:
  // To find orientation of ordered triplet (p, q, r). 
  // The function returns following values 
  // 0 --> p, q and r are colinear 
  // +1 --> Clockwise 
  // -1 --> Counterclockwise 
  static int orientation(const Vec2& p, const Vec2& q, const Vec2& r)
  {
    // https://www.geeksforgeeks.org/orientation-3-ordered-points/
    T val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) {
      return 0;
    }
    return val > 0 ? 1 : -1;
  }

  // Given three colinear points p, q, r, the function checks if 
  // point q lies on line segment 'pr' 
  static bool onSegment(const Vec2 p, const Vec2 q, const Vec2 r)
  {
    return q.x <= max(p.x, r.x) 
      && q.x >= min(p.x, r.x) 
      && q.y <= max(p.y, r.y) 
      && q.y >= min(p.y, r.y);
  }
};

vector<int> convexHull(vector<Vec2> points) {
  // https://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain#C++
  size_t n = points.size();
  if (n <= 3) {
    return {};
  }

  vector<Vec2> H(2*n);
  vector<int> inds(2*n);
  size_t k = 0;

  sort(points.begin(), points.end());
  
  for (size_t i = 0; i < n; ++i) {
    while (k >= 2 && (H[k-1] - H[k-2]).cross(points[i] - H[k-2]) < 0) k--;
    inds[k] = i;
    H[k++] = points[i];
  }
  
  // Build upper hull
  for (size_t i = n-1, t = k+1; i > 0; --i) {
    while (k >= t && (H[k-1] - H[k-2]).cross(points[i-1] - H[k-2]) < 0) k--;
    inds[k] = i-1;
    H[k++] = points[i-1];
  }

  H.resize(k-1);
  inds.resize(k-1);
  return inds;
}

bool isInside(const vector<Vec2>& points, const vector<int>& inds, const Vec2& p) {
  for (size_t i = 0; i < inds.size(); ++i) {
    size_t j = (i + 1) % inds.size();
    int o = Vec2::orientation(points[i], points[j], p);
    if (o != -1) {
      return false;
    }
  }
  return true;
}

void solve() {
  int N;
  cin >> N;

  Vec2 P;
  cin >> P;

  vector<Vec2> vs(N);
  for (int i = 0; i < N; ++i) {
    cin >> vs[i];
  }

  int step = 0;
  while (true) {
    vector<int> hull = convexHull(vs);
    if (hull.empty()) {
      break;
    }
    if (isInside(vs, hull, P)) {
      break;
    }
    //for (int i = 0; i < hull.size(); ++i) {
      //printf("%d ", hull[i]);
    //}
    //printf("\n");
    
    set<int> s(hull.begin(), hull.end());
    vector<Vec2> vsSwap;
    for (size_t i = 0; i < vs.size(); ++i) {
      if (s.find(i) == s.end()) {
        vsSwap.push_back(vs[i]);
      }
    }
    vs.swap(vsSwap);
    step++;
  }
  cout << step;

}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
