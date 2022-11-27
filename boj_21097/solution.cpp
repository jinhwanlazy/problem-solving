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

class Circle
{
  using T = Vec2::T;

public:
  Vec2 center;
  T radius;
  inline bool operator==(const Circle& rhs) const {
    return ((center == rhs.center) && (radius == rhs.radius));
  }

public:
  double area() const { return radius * radius * M_PI; }

public:
  bool contains(const Vec2& rhs) const {
    Vec2 d = rhs - center;
    return rhs.squaredLength(center) <= radius * radius;
  }

  bool contains(const Circle& rhs) const {
    return radius >= (center.length(rhs.center) + rhs.radius);
  }

  bool overlaps(const Circle& rhs) const {
    double d = center.length(rhs.center);
    return d < radius + rhs.radius;
    //return abs(radius - rhs.radius) < d && d < radius + rhs.radius;
  }

  optional<pair<Vec2, Vec2>> intersection(const Circle& rhs) const {
    // http://paulbourke.net/geometry/circlesphere/
    if (*this == rhs) {
      return nullopt;
    }
    const Vec2& p0 = this->center;
    const Vec2& p1 = rhs.center;
    double r0 = this->radius;
    double r1 = rhs.radius;
    double d = p0.length(p1);

    if (d >= r0 + r1) {
      return nullopt;
    }
    if (d <= abs(r0 - r1)) {
      return nullopt;
    }

    double a = (r0*r0 - r1*r1 + d*d) / (2 * d);
    double h = sqrt(r0*r0 - a*a);
    Vec2 p2 = p0 + (p1 - p0) * (a / d);
    Vec2 diff = Vec2{p1.y-p0.y, p1.x-p0.x} * h / d;
    return make_pair(p2 + diff, p2 - diff);
  }

  double overlappingArea(const Circle& rhs) const {
    if (!overlaps(rhs)) {
      return 0;
    }
    if (rhs.contains(*this)) {
      return area();
    }
    if (this->contains(rhs)) {
      return rhs.area();
    }
    const double& r0 = radius;
    const double& r1 = rhs.radius;
    const double d = center.length(rhs.center);
    const double angle0 = acos((r0 * r0 + d * d - r1 * r1) / (2 * r0 * d));
    const double angle1 = acos((r1 * r1 + d * d - r0 * r0) / (2 * r1 * d));
    const double rr0 = radius * radius;
    const double rr1 = rhs.radius * rhs.radius;

    double ans = 
      + rr0 * angle0 - rr0 * sin(2*angle0) * 0.5
      + rr1 * angle1 - rr1 * sin(2*angle1) * 0.5;
    return ans;
  }

public:
  friend istream& operator>> (istream& istr, Circle& rhs) {
    istr >> rhs.center.x >> rhs.center.y >> rhs.radius;
    return istr;
  }

public:
  Circle() : center(0, 0), radius(T(0)) {}

  Circle(T x, T y, T r) : center(x, y), radius(r) {}

  Circle(const Circle& rhs) : center(rhs.center), radius(rhs.radius) {}

  ~Circle() {}
};

class Seg2 {
 public:
  Vec2 start;
  Vec2 end;

 public:
  Vec2 center() const { return (start + end) / 2; }

  Vec2 direction() const { return end - start; }

  Vec2 normalizedDirection() const { return direction().normalized(); }

  double length() const { return (end - start).length(); }

 public:
  bool contains(const Vec2& point) const {
    static constexpr double epsilon = 1e-10;
    return Vec2::onSegment(start, point, end) && (start - point).cross(point - end) < epsilon;
  }

  bool contains(const Seg2& rhs) const { return contains(rhs.start) && contains(rhs.end); }

  bool intersects(const Seg2& rhs) const {
    const auto& p1 = this->start;
    const auto& q1 = this->end;
    const auto& p2 = rhs.start;
    const auto& q2 = rhs.end;

    int o1 = Vec2::orientation(p1, q1, p2);
    int o2 = Vec2::orientation(p1, q1, q2);
    int o3 = Vec2::orientation(p2, q2, p1);
    int o4 = Vec2::orientation(p2, q2, q1);

    if (o1 * o2 < 0 && o3 * o4 < 0)
      return true;

    if (o1 == 0 && Vec2::onSegment(p1, p2, q1))
      return true;
    if (o2 == 0 && Vec2::onSegment(p1, q2, q1))
      return true;
    if (o3 == 0 && Vec2::onSegment(p2, p1, q2))
      return true;
    if (o4 == 0 && Vec2::onSegment(p2, q1, q2))
      return true;
    return false;
  }

  bool colinear(const Seg2& rhs) const {
    // https://stackoverflow.com/a/565282
    const auto& p = this->start;
    const auto r = this->end - this->start;
    const auto& q = rhs.start;
    const auto s = rhs.end - rhs.start;

    auto a = r.cross(s);
    auto b = (q - p).cross(r);
    return a == 0 && b == 0;
  }

  Seg2 overlap(const Seg2& rhs) const {
    if (!colinear(rhs)) {
      throw runtime_error("two vector should be colinear");
    }
    if (isOn(rhs.start) && isOn(rhs.end)) {
      return rhs;
    }
    if (rhs.isOn(start) && rhs.isOn(end)) {
      return *this;
    }
    Vec2 s = isOn(rhs.start) ? rhs.start : rhs.end;
    Vec2 e = rhs.isOn(start) ? start : end;
    return {s, e};
  }

  bool isOn(const Vec2& p) const {
    return p.x <= max(start.x, end.x)		 //
            && p.x >= min(start.x, end.x)	//
            && p.y <= max(start.y, end.y)	//
            && p.y >= min(start.y, end.y);
  }

  Vec2 intersection(const Seg2& rhs) const {
    // https://stackoverflow.com/a/565282
    const auto& p = this->start;
    const auto r = this->end - this->start;
    const auto& q = rhs.start;
    const auto s = rhs.end - rhs.start;

    auto a = r.cross(s);
    auto b = (q - p).cross(r);
    if (a == 0 && b == 0) {
      // case1: colinear
      if (this->contains(rhs.start)) {
        return rhs.start;
      } else {
        return rhs.end;
      }
    } else if (a == 0 && b != 0) {
      // case2: parallel
      throw runtime_error("case 2. should be checked using intersects() before");
    }
    double t = (q - p).cross(s) / a;
    double u = (q - p).cross(r) / a;
    if (0 <= t && t <= 1.0 && 0 <= u && u <= 1.0) {
      // case3: intersects
      return p + r * t;
    } else {
      // case 4: not parallel but do not intersects
      throw runtime_error("case 4. should be checked using intersects() before");
    }
  }

 public:
  friend ostream& operator<<(ostream& ostr, const Seg2& rhs) {
    ostr << "Seg2(" << rhs.start << ", " << rhs.end << ")";
    return ostr;
  }

  friend istream& operator>>(istream& istr, Seg2& rhs) {
    istr >> rhs.start >> rhs.end;
    return istr;
  }

 public:
  Seg2(){};

  Seg2(const Vec2& start, const Vec2& end) : start(start), end(end){};

  Seg2(Vec2::T startX, Vec2::T startY, Vec2::T endX, Vec2::T endY)
      : start{startX, startY}, end{endX, endY} {};

  Seg2(const Seg2& rhs) : start(rhs.start), end(rhs.end){};

 public:
  ~Seg2() {}
};

double distance(const Vec2& p, const Vec2& q) {
  return (p - q).norm();
}

double distance(const Vec2& p, const Seg2& seg) {
  const Vec2 v = seg.direction();
  if (v.dot(p - seg.start) <= 0) {
    return (seg.start - p).norm();
  }
  if (-v.dot(p - seg.end) <= 0) {
    return (seg.end - p).norm();
  }
  const double l2 = v.squaredNorm();
  const double t = max(0.0, min(1.0, (p - seg.start).dot(v) / l2));
  const Vec2 q = seg.start + v * t;
  return (p - q).norm();
}

double angle(const Vec2& p, const Vec2& q) {
  return atan2(abs(p.cross(q)), p.dot(q));
}

void solve() {
  Vec2 a, b;
  Circle o;
  cin >> a >> b >> o;

  a -= o.center;
  b -= o.center;
  o.center = Vec2::zero();
  const double& r = o.radius;

  double ans = 0;
  if (distance(o.center, Seg2(a, b)) < r) {
    ans += sqrt(a.squaredNorm() - r * r);
    ans += sqrt(b.squaredNorm() - r * r);

    double theta = angle(a, b) - acos(r / a.norm()) - acos(r / b.norm());
    ans += theta * r;
  }
  else {
    auto eval = [&a, &b](const Vec2& c) {
      return (c - a).norm() + (c - b).norm();
    };
    auto l = a.normalized() * o.radius;
    auto r = b.normalized() * o.radius;
    for (int i = 0; i < 100; ++i) {
      // ternary search [l, p, q, r]
      auto p = (l + (r - l) * 1.0 / 3.0).normalized() * o.radius;
      auto q = (l + (r - l) * 2.0 / 3.0).normalized() * o.radius;
      if (eval(p) < eval(q)) 
        r = q;
      else 
        l = p;
    }
    auto c = (l + r).normalized() * o.radius;
    ans = eval(c);
  }

  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout << fixed << setprecision(3);
  int T;
  cin >> T;
  while (T--) {
    solve();
  }

  return 0;
}
