#include <bits/stdc++.h>
using namespace std;

constexpr static double INF = numeric_limits<double>::max();


class Vec2 {
 public:
  using T = double;

 public:
  T x;
  T y;
  T r;

 public:
  inline Vec2& operator=(const Vec2& rhs) {
    x = rhs.x;
    y = rhs.y;
    return *this;
  }

 public:
  inline bool operator==(const Vec2& rhs) const { return ((x == rhs.x) && (y == rhs.y)); }

  inline bool operator!=(const Vec2& rhs) const { return !(operator==(rhs)); }

  inline Vec2 operator+(const Vec2& rhs) const { return Vec2(x + rhs.x, y + rhs.y); }

  inline Vec2 operator-(const Vec2& rhs) const { return Vec2(x - rhs.x, y - rhs.y); }

  inline Vec2 operator*(T rhs) const { return Vec2(T(x * rhs), T(y * rhs)); }

  inline Vec2 operator/(T rhs) const { return Vec2(T(x / rhs), T(y / rhs)); }

  inline Vec2 operator-() const { return Vec2(-x, -y); }

  inline Vec2& operator+=(const Vec2& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  inline Vec2& operator-=(const Vec2& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  inline Vec2& operator*=(T rhs) {
    x = T(x * rhs);
    y = T(y * rhs);
    return *this;
  }

  inline Vec2& operator/=(T rhs) {
    x = T(x / rhs);
    y = T(y / rhs);
    return *this;
  }

 public:
  inline double norm() const { return sqrt(squaredNorm()); }

  inline T squaredNorm() const { return ((x * x) + (y * y)); }

  inline double length() const { return norm(); }

  inline double length(const Vec2& pos) const { return sqrt(squaredLength(pos)); }

  inline T squaredLength() const { return squaredNorm(); }

  inline T squaredLength(const Vec2& pos) const {
    return (((x - pos.x) * (x - pos.x)) + ((y - pos.y) * (y - pos.y)));
  }

  inline T l1length() const { return abs(x) + abs(y); }

  inline T l1length(const Vec2& pos) const { return abs(x - pos.x) + abs(y - pos.x); }

  inline bool close(const Vec2& rhs, const double span = 1.0, const double tol = 1e-20) const {
    return (squaredLength(rhs) / span) < tol;
  }

  inline void normalize() {
    double l = norm();
    if (l < numeric_limits<double>::epsilon()) {
      x = 0;
      y = 0;
    } else {
      x = (T)(x / l);
      y = (T)(y / l);
    }
  }

  inline Vec2 normalized() const {
    Vec2 n(*this);
    n.normalize();
    return n;
  }

  inline T dot(const Vec2& rhs) const { return x * rhs.x + y * rhs.y; }

  inline T cross(const Vec2& rhs) const { return x * rhs.y - y * rhs.x; }

  inline double angle(const Vec2& rhs) const {
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
  static const Vec2& xAxis() {
    static Vec2 vec(1, 0);
    return vec;
  }
  static const Vec2& yAxis() {
    static Vec2 vec(0, 1);
    return vec;
  }
  static const Vec2& zero() {
    static Vec2 vec(0, 0);
    return vec;
  }
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
  Vec2() : x(T(0)), y(T(0)), r(0) {}

  Vec2(T x_, T y_) : x(x_), y(y_), r(0) {}

  ~Vec2() {}

 public:
  // Given three colinear points p, q, r, the function checks if
  // point q lies on line segment 'pr'
  static bool onSegment(const Vec2 p, const Vec2 q, const Vec2 r) {
    return q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) &&
           q.y >= min(p.y, r.y);
  }
};

inline int orientation(const Vec2& p, const Vec2& q, const Vec2& r) {
  // https://www.geeksforgeeks.org/orientation-3-ordered-points/
  // To find orientation of ordered triplet (p, q, r).
  // The function returns following values
  // 0 --> p, q and r are colinear
  // +1 --> Clockwise
  // -1 --> Counterclockwise
  Vec2::T val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
  if (val == 0) {
    return 0;
  }
  return val > 0 ? 1 : -1;
}

inline bool clockwise(const Vec2& p, const Vec2& q, const Vec2& r) {
  return orientation(p, q, r) == 1;
}

inline bool counterclockwise(const Vec2& p, const Vec2& q, const Vec2& r) {
  return orientation(p, q, r) == -1;
}

inline bool colinear(const Vec2& p, const Vec2& q, const Vec2& r) {
  return orientation(p, q, r) == 0;
}

inline double circumradius(const Vec2& p1, const Vec2& p2, const Vec2& p3) {
  Vec2 d = p2 - p1;
  Vec2 e = p3 - p1;

  const double bl = d.squaredNorm();
  const double cl = e.squaredNorm();
  const double det = d.cross(e);

  Vec2 radius(
      (e.y * bl - d.y * cl) * 0.5 / det, 
      (d.x * cl - e.x * bl) * 0.5 / det);

  if ((bl > 0.0 || bl < 0.0) && (cl > 0.0 || cl < 0.0) && (det > 0.0 || det < 0.0))
    return radius.squaredNorm();
  return (std::numeric_limits<double>::max)();
}

inline Vec2 circumcenter(const Vec2& a, const Vec2& b, const Vec2& c) {
  const Vec2 d = b - a;
  const Vec2 e = c - a;

  const double bl = d.squaredNorm();
  const double cl = e.squaredNorm();
  const double det = d.cross(e);

  Vec2 radiusVec((e.y * bl - d.y * cl) * 0.5 / det, (d.x * cl - e.x * bl) * 0.5 / det);
  return a + radiusVec;
}

inline bool inCircle(const Vec2& a, const Vec2& b, const Vec2& c, const Vec2& p) {
  const Vec2 d = a - p;
  const Vec2 e = b - p;
  const Vec2 f = c - p;

  const double ap = d.squaredLength();
  const double bp = e.squaredLength();
  const double cp = f.squaredLength();

  return d.cross(e * cp - f * bp) + ap * e.cross(f) < 0.0;
}

class BBox2 {
 private:
  Vec2 bottomLeft_;
  Vec2 topRight_;
  Vec2 center_;
  double span_;

 public:
  BBox2(const vector<Vec2>& points) {
    topRight_ = Vec2(-INF, -INF);
    bottomLeft_ = Vec2(INF, INF);
    for (const auto& p : points) {
      bottomLeft_.x = min(bottomLeft_.x, p.x);
      bottomLeft_.y = min(bottomLeft_.y, p.y);
      topRight_.x = max(topRight_.x, p.x);
      topRight_.y = max(topRight_.y, p.y);
    }
    center_ = (bottomLeft_ + topRight_) / 2;
    span_ = bottomLeft_.squaredLength(topRight_);
  }

  const Vec2& bottomLeft() const { return bottomLeft_; }
  const Vec2& topRight() const { return topRight_; }
  const Vec2& center() const { return center_; }
  const double& span() const { return span_; }
};

// Delaunator, mostly adopted from
// https://github.com/abellgithub/delaunator-cpp/blob/master/include/delaunator.cpp
class Delaunator {
 public:
  std::vector<Vec2> points_;
  std::vector<std::size_t> triangles_;

  std::vector<std::size_t> halfedges_;

  std::vector<std::size_t> hullPrev_;
  std::vector<std::size_t> hullNext_;
  std::vector<std::size_t> hullTri_;
  std::size_t hullStart_;

 private:
  static constexpr std::size_t INVALID_INDEX = -1;

  std::vector<std::size_t> hullHash_;
  Vec2 center_;
  std::size_t hashSize_;

 public:
  Delaunator(std::vector<Vec2> const& points) : points_(points) {
    std::size_t n = points.size();

    BBox2 bbox(points_);
    Vec2 center = bbox.center();

    std::size_t i0 = INVALID_INDEX;
    std::size_t i1 = INVALID_INDEX;
    std::size_t i2 = INVALID_INDEX;

    double min_dist = INF;
    for (size_t i = 0; i < points_.size(); ++i)
    {
        const Vec2& p = points_[i];
        const double d = p.squaredLength(center);
        if (d < min_dist) {
            i0 = i;
            min_dist = d;
        }
    }
    Vec2 p0 = points_[i0];

    min_dist = (std::numeric_limits<double>::max)();
    for (std::size_t i = 0; i < n; i++) {
        if (i == i0) continue;
        const double d = p0.squaredLength(points_[i]);
        if (d < min_dist && d > 0.0) {
            i1 = i;
            min_dist = d;
        }
    }
    Vec2 p1 = points_[i1];

    double min_radius = INF;
    for (std::size_t i = 0; i < n; i++) {
      if (i == i0 || i == i1)
        continue;
      const double r = circumradius(p0, p1, points_[i]);
      if (r < min_radius) {
        i2 = i;
        min_radius = r;
      }
    }
    Vec2 p2 = points_[i2];

    if (!(min_radius < INF)) {
      throw std::runtime_error("not triangulation");
    }

    if (counterclockwise(p0, p1, p2)) {
      std::swap(i1, i2);
      std::swap(p1, p2);
    }

    center_ = circumcenter(p0, p1, p2);

    std::vector<double> dists;
    dists.reserve(points_.size());
    for (const auto& p : points_)
      dists.push_back(p.squaredLength(center_));

    // sort the points by distance from the seed triangle circumcenter
    std::vector<std::size_t> ids(n);
    std::iota(ids.begin(), ids.end(), 0);
    std::sort(ids.begin(), ids.end(),
              [&dists](std::size_t i, std::size_t j) { return dists[i] < dists[j]; });

    // initialize a hash table for storing edges of the advancing convex hull
    hashSize_ = static_cast<std::size_t>(std::ceil(std::sqrt(n)));
    hullHash_.resize(hashSize_, INVALID_INDEX);

    // initialize arrays for tracking the edges of the advancing convex hull
    hullPrev_.resize(n);
    hullNext_.resize(n);
    hullTri_.resize(n);

    hullStart_ = i0;

    size_t hull_size = 3;

    hullNext_[i0] = hullPrev_[i2] = i1;
    hullNext_[i1] = hullPrev_[i0] = i2;
    hullNext_[i2] = hullPrev_[i1] = i0;

    hullTri_[i0] = 0;
    hullTri_[i1] = 1;
    hullTri_[i2] = 2;

    hullHash_[hash_key(p0)] = i0;
    hullHash_[hash_key(p1)] = i1;
    hullHash_[hash_key(p2)] = i2;

    std::size_t max_triangles_ = n < 3 ? 1 : 2 * n - 5;
    triangles_.reserve(max_triangles_ * 3);
    halfedges_.reserve(max_triangles_ * 3);
    add_triangle(i0, i1, i2, INVALID_INDEX, INVALID_INDEX, INVALID_INDEX);
    Vec2 pPrev{std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN()};

    // Go through points based on distance from the center.
    for (std::size_t k = 0; k < n; k++) {
      const std::size_t i = ids[k];
      const Vec2 p = points_[i];

      // skip near-duplicate points
      if (k > 0 && p == pPrev)
        continue;
      pPrev = p;

      if (p == p0 || p == p1 || p == p2) {
        continue;
      }

      // find a visible edge on the convex hull using edge hash
      std::size_t start = 0;

      size_t key = hash_key(p);
      for (size_t j = 0; j < hashSize_; j++) {
        start = hullHash_[(key + j) % hashSize_];
        if (start != INVALID_INDEX && start != hullNext_[start])
          break;
      }

      assert(hullPrev_[start] != start);
      assert(hullPrev_[start] != INVALID_INDEX);

      start = hullPrev_[start];
      size_t e = start;
      size_t q;

      // Advance until we find a place in the hull where our current point can be added.
      while (true) {
        q = hullNext_[e];
        if (p.close(points_[e], bbox.span()) || p.close(points_[q], bbox.span())) {
          e = INVALID_INDEX;
          break;
        }
        if (counterclockwise(p, points_[e], points_[q]))
          break;
        e = q;
        if (e == start) {
          e = INVALID_INDEX;
          break;
        }
      }

      if (e == INVALID_INDEX)  // likely a near-duplicate point; skip it
        continue;

      // add the first triangle from the point
      std::size_t t = add_triangle(e, i, hullNext_[e], INVALID_INDEX, INVALID_INDEX, hullTri_[e]);

      hullTri_[i] = legalize(t + 2);  // Legalize the triangle we just added.
      hullTri_[e] = t;
      hull_size++;

      // walk forward through the hull, adding more triangles_ and flipping recursively
      std::size_t next = hullNext_[e];
      while (true) {
        q = hullNext_[next];
        if (!counterclockwise(p, points_[next], points_[q]))
          break;
        t = add_triangle(next, i, q, hullTri_[i], INVALID_INDEX, hullTri_[next]);
        hullTri_[i] = legalize(t + 2);
        hullNext_[next] = next;  // mark as removed
        hull_size--;
        next = q;
      }

      // walk backward from the other side, adding more triangles_ and flipping
      if (e == start) {
        while (true) {
          q = hullPrev_[e];
          if (!counterclockwise(p, points_[q], points_[e]))
            break;
          t = add_triangle(q, i, e, INVALID_INDEX, hullTri_[e], hullTri_[q]);
          legalize(t + 2);
          hullTri_[q] = t;
          hullNext_[e] = e;  // mark as removed
          hull_size--;
          e = q;
        }
      }

      // update the hull indices
      hullPrev_[i] = e;
      hullStart_ = e;
      hullPrev_[next] = i;
      hullNext_[e] = i;
      hullNext_[i] = next;

      hullHash_[hash_key(p)] = i;
      hullHash_[hash_key(points_[e])] = e;
    }
  }

 private:
  std::size_t legalize(std::size_t a) {
    std::size_t i = 0;
    std::size_t ar = 0;
    std::vector<std::size_t> edgesStack;

    // recursion eliminated with a fixed-size stack
    while (true) {
      const size_t b = halfedges_[a];

      /* if the pair of triangles_ doesn't satisfy the Delaunay condition
       * (p1 is inside the circumcircle of [p0, pl, pr]), flip them,
       * then do the same check/flip recursively for the new pair of triangles_
       *
       *           pl                    pl
       *          /||\                  /  \
       *       al/ || \bl            al/    \a
       *        /  ||  \              /      \
       *       /  a||b  \    flip    /___ar___\
       *     p0\   ||   /p1   =>   p0\---bl---/p1
       *        \  ||  /              \      /
       *       ar\ || /br             b\    /br
       *          \||/                  \  /
       *           pr                    pr
       */
      const size_t a0 = 3 * (a / 3);
      ar = a0 + (a + 2) % 3;

      if (b == INVALID_INDEX) {
        if (i > 0) {
          i--;
          a = edgesStack[i];
          continue;
        } else {
          // i = INVALID_INDEX;
          break;
        }
      }

      const size_t b0 = 3 * (b / 3);
      const size_t al = a0 + (a + 1) % 3;
      const size_t bl = b0 + (b + 2) % 3;

      const std::size_t p0 = triangles_[ar];
      const std::size_t pr = triangles_[a];
      const std::size_t pl = triangles_[al];
      const std::size_t p1 = triangles_[bl];

      const bool illegal = inCircle(points_[p0], points_[pr], points_[pl], points_[p1]);

      if (illegal) {
        triangles_[a] = p1;
        triangles_[b] = p0;

        auto hbl = halfedges_[bl];

        // Edge swapped on the other side of the hull (rare).
        // Fix the halfedge reference
        if (hbl == INVALID_INDEX) {
          std::size_t e = hullStart_;
          do {
            if (hullTri_[e] == bl) {
              hullTri_[e] = a;
              break;
            }
            e = hullPrev_[e];
          } while (e != hullStart_);
        }
        link(a, hbl);
        link(b, halfedges_[ar]);
        link(ar, bl);
        std::size_t br = b0 + (b + 1) % 3;

        if (i < edgesStack.size()) {
          edgesStack[i] = br;
        } else {
          edgesStack.push_back(br);
        }
        i++;

      } else {
        if (i > 0) {
          i--;
          a = edgesStack[i];
          continue;
        } else {
          break;
        }
      }
    }
    return ar;
  };

  // monotonically increases with real angle, but doesn't need expensive trigonometry
  static inline double pseudo_angle(const double dx, const double dy) {
    const double p = dx / (std::abs(dx) + std::abs(dy));
    return (dy > 0.0 ? 3.0 - p : 1.0 + p) / 4.0;  // [0..1)
  }

  std::size_t hash_key(double x, double y) const {
    const double dx = x - center_.x;
    const double dy = y - center_.y;
    size_t key = std::llround(std::floor(pseudo_angle(dx, dy) * static_cast<double>(hashSize_)));
    return key % hashSize_;
  };

  std::size_t hash_key(const Vec2& p) const {
    const Vec2 v = p - center_;
    size_t key = std::llround(std::floor(pseudo_angle(v.x, v.y) * static_cast<double>(hashSize_)));
    return key % hashSize_;
  };

  std::size_t add_triangle(std::size_t i0,
                           std::size_t i1,
                           std::size_t i2,
                           std::size_t a,
                           std::size_t b,
                           std::size_t c) {
    std::size_t t = triangles_.size();
    triangles_.push_back(i0);
    triangles_.push_back(i1);
    triangles_.push_back(i2);
    link(t, a);
    link(t + 1, b);
    link(t + 2, c);
    return t;
  }

  void link(std::size_t a, std::size_t b) {
    std::size_t s = halfedges_.size();
    if (a == s) {
      halfedges_.push_back(b);
    } else if (a < s) {
      halfedges_[a] = b;
    } else {
      throw std::runtime_error("Cannot link edge");
    }
    if (b != INVALID_INDEX) {
      std::size_t s2 = halfedges_.size();
      if (b == s2) {
        halfedges_.push_back(a);
      } else if (b < s2) {
        halfedges_[b] = a;
      } else {
        throw std::runtime_error("Cannot link edge");
      }
    }
  }
};

double solve(int N) {
  vector<Vec2> points(N);
  for (int i = 0; i < N; ++i) {
    auto& [x, y, r] = points[i];
    scanf("%lf %lf %lf", &r, &x, &y);
  }
  if (N == 2) {
    return points[0].length(points[1]) - points[0].r - points[1].r;
  }

  try {
    Delaunator delaunay(points);

    double ans = INF;
    for (size_t i = 0; i < delaunay.triangles_.size(); i += 3) {
      const auto& p0 = points[delaunay.triangles_[i + 0]];
      const auto& p1 = points[delaunay.triangles_[i + 1]];
      const auto& p2 = points[delaunay.triangles_[i + 2]];
      ans = min(ans, p0.length(p1) - p0.r - p1.r);
      ans = min(ans, p1.length(p2) - p1.r - p2.r);
      ans = min(ans, p2.length(p0) - p2.r - p0.r);
    }
    return ans;
  } catch (const std::exception& e) {
    // all points are colinear?
    double ans = std::numeric_limits<double>::max();
    sort(points.begin(), points.end());
    for (int i = 0; i < N - 1; ++i) {
      const auto& p0 = points[i];
      const auto& p1 = points[i + 1];
      ans = min(ans, p0.length(p1) - p0.r - p1.r);
    }
    return ans;
  }
  return 0;
}

int main() {
  while (true) {
    int N;
    scanf("%d", &N);
    if (N == 0) {
      break;
    }

    double ans = solve(N);
    printf("%lf\n", ans);
  }

  return 0;
}
