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

class Square
{
  using T = Vec2::T;
  
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

public:
  bool contains(const Vec2& rhs) const {
    return left <= rhs.x && rhs.x <= right && bottom <= rhs.y && rhs.y <= top;
  }

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
    istr >> rhs.left >> rhs.top >> rhs.right >> rhs.bottom;
    return istr;
  }

public:
  Square() : left(0), right(1), bottom(0), top(1) {}

  Square(T l, T r, T b, T t) : left(l), right(r), bottom(b), top(t) {}

  ~Square() {}
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

bool intersects(const Seg2& seg1, Seg2& seg2) {
  return false;
}

bool intersects(const Square& sq, const Seg2& seg) {
  vector<Seg2> tests = {
    {{sq.left, sq.bottom}, {sq.right, sq.bottom}},
    {{sq.right, sq.bottom}, {sq.right, sq.top}},
    {{sq.right, sq.top}, {sq.left, sq.top}},
    {{sq.left, sq.top}, {sq.left, sq.bottom}},
  };
  for (const Seg2& test : tests) {
    if (seg.intersects(test)) {
      return true;
    }
  }
  return false;
}

bool contains(const Square& sq, const Seg2& seg) {
  return sq.contains(seg.start) && sq.contains(seg.end);
}
 
void solve() {
  Seg2 seg;
  Square sq;
  cin >> seg >> sq;

  double l = min(sq.left, sq.right);
  double r = max(sq.left, sq.right);
  double b = min(sq.bottom, sq.top);
  double t = max(sq.bottom, sq.top);
  sq = {l, r, b, t};

  char ans = contains(sq, seg) || intersects(sq, seg) ? 'T' : 'F';
  cout << ans << "\n";
}

int main() {
  int T;
  scanf("%d", &T);
  
  while (T--) {
    solve();
  }

  return 0;
}
