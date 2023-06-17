#include <bits/stdc++.h>
using namespace std;

class Vec2 {
public:
  using T = double;
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

class Tower : public Vec2 {
 public:
  double r;
};

class PeriPoint : public Vec2 {
 public:
  const Tower* parent = nullptr;
  PeriPoint(double x, double y, const Tower* parent)
      : Vec2(x, y), parent(parent) {}

  PeriPoint() {};
};

vector<PeriPoint> convexHull(vector<PeriPoint> points) {
  // https://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain#C++
  size_t n = points.size();
  if (n <= 3) {
    return points;
  }

  vector<PeriPoint> H(2*n);
  size_t k = 0;

  sort(points.begin(), points.end());
  
  for (size_t i = 0; i < n; ++i) {
    while (k >= 2 && (H[k-1] - H[k-2]).cross(points[i] - H[k-2]) <= 0) k--;
    H[k++] = points[i];
  }
  
  // Build upper hull
  for (size_t i = n-1, t = k+1; i > 0; --i) {
    while (k >= t && (H[k-1] - H[k-2]).cross(points[i-1] - H[k-2]) <= 0) k--;
    H[k++] = points[i-1];
  }

  H.resize(k-1);
  return H;
}

pair<PeriPoint, PeriPoint> contactPoints(const Tower& t1, const Tower& t2) {
  Vec2 v = t2 - t1;
  double d = v.norm();
  double a = asin((t1.r - t2.r) / d);
  Vec2 v_(sin(a) * v.x + cos(a) * v.y,  //
          -cos(a) * v.x + sin(a) * v.y);
  v_.normalize();
  Vec2 p1 = t1 + v_ * t1.r;
  Vec2 p2 = t2 + v_ * t2.r;
  return {
    {p1.x, p1.y, &t1},
    {p2.x, p2.y, &t2}
  };
}

double arcLength(const Vec2& p1, const Vec2& p2, const Vec2& center) {
  return (p1 - center).angle(p2 - center) * (p1 - center).norm();
}

void solve() {
  int N;
  cin >> N;

  vector<Tower> towers(N);
  for (int i = 0; i < N; ++i) {
    auto& tower = towers[i];
    cin >> tower.x >> tower.y >> tower.r;
  }

  int nSample = 5000;
  vector<PeriPoint> points;
  points.reserve(nSample * N);
  for (const auto& tower : towers) {
    for (int i = 0; i < nSample; ++i) {
      double angle = (double)i / (double)nSample * M_PI * 2.0;
      double x = tower.x + tower.r * cos(angle);
      double y = tower.y + tower.r * sin(angle);
      points.push_back(PeriPoint{x, y, &tower});
    }
  }

  points = convexHull(points);
  size_t pointsSize = points.size();
  for (int i = 0; i < pointsSize; ++i) {
    const auto& p = points[i];
    const auto& q = (i == pointsSize - 1) ? points[0] : points[i + 1];
    if (p.parent != q.parent) {
      const auto [p_, q_] = contactPoints(*p.parent, *q.parent);
      points.push_back(p_);
      points.push_back(q_);
    }
  }

  points = convexHull(points);
  pointsSize = points.size();
  double ans = 0;
  for (int i = 0; i < pointsSize; ++i) {
    const auto& p = points[i];
    const auto& q = (i == pointsSize - 1) ? points[0] : points[i + 1];
    if (p.parent == q.parent) {
      ans += arcLength(p, q, *p.parent);
    }
    else {
      const auto [p_, q_] = contactPoints(*p.parent, *q.parent);
      ans += (p_ - q_).norm();
    }
  }
  cout << setprecision(12) << ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);

  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
