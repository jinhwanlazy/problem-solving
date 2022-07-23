#include <bits/stdc++.h>
#include <limits>
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
    // To find orientation of ordered triplet (p, q, r).
    // The function returns following values
    // 0 --> p, q and r are colinear
    // +1 --> Clockwise
    // -1 --> Counterclockwise
    static int orientation(const Vec2& p, const Vec2& q, const Vec2& r) {
        // https://www.geeksforgeeks.org/orientation-3-ordered-points/
        T val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
        if (val == 0) {
            return 0;
        }
        return val > 0 ? 1 : -1;
    }

    // Given three colinear points p, q, r, the function checks if
    // point q lies on line segment 'pr'
    static bool onSegment(const Vec2 p, const Vec2 q, const Vec2 r) {
        return q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) &&
               q.y >= min(p.y, r.y);
    }
};


inline double circumradius(const Vec2& a, const Vec2& b, const Vec2& c) {
    const Vec2 d = b - a;
    const Vec2 e = c - a;

    const double bl = d.squaredNorm();
    const double cl = e.squaredNorm();
    const double det = d.cross(e);

    Vec2 radius((e.y * bl - d.y * cl) * 0.5 / det, (d.x * cl - e.x * bl) * 0.5 / det);

    if ((bl > 0.0 || bl < 0.0) &&
        (cl > 0.0 || cl < 0.0) &&
        (det > 0.0 || det < 0.0))
        return radius.squaredNorm();
    return std::numeric_limits<double>::max();
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

    return (d.x * (e.y * cp - bp * f.y) -  //
            d.y * (e.x * cp - bp * f.x) +  //
            ap * (e.x * f.y - e.y * f.x)) < 0.0;
}

// adopted from https://github.com/abellgithub/delaunator-cpp/blob/master/include/delaunator.cpp
namespace delaunator {

constexpr std::size_t INVALID_INDEX =
    (std::numeric_limits<std::size_t>::max)();
#define INLINE inline

class Point
{
public:
    Point(double x, double y) : m_x(x), m_y(y)
    {}
    Point() : m_x(0), m_y(0)
    {}

    double x() const
    { return m_x; }

    double y() const
    { return m_y; }

    double magnitude2() const
    { return m_x * m_x + m_y * m_y; }

    static double determinant(const Point& p1, const Point& p2)
    {
        return p1.m_x * p2.m_y - p1.m_y * p2.m_x;
    }

    static Point vector(const Point& p1, const Point& p2)
    {
        return Point(p2.m_x - p1.m_x, p2.m_y - p1.m_y);
    }

    static double dist2(const Point& p1, const Point& p2)
    {
        Point vec = vector(p1, p2);
        return vec.m_x * vec.m_x + vec.m_y * vec.m_y;
    }

    static bool equal(const Point& p1, const Point& p2, double span)
    {
        double dist = dist2(p1, p2) / span;

        // ABELL - This number should be examined to figure how how
        // it correlates with the breakdown of calculating determinants.
        return dist < 1e-20;
    }

private:
    double m_x;
    double m_y;
};

inline std::ostream& operator<<(std::ostream& out, const Point& p)
{
    out << p.x() << "/" << p.y();
    return out;
}


class Points
{
public:
    using const_iterator = Point const *;

    Points(const std::vector<double>& coords) : m_coords(coords)
    {}

    const Point& operator[](size_t offset)
    {
        return reinterpret_cast<const Point&>(
            *(m_coords.data() + (offset * 2)));
    };

    Points::const_iterator begin() const
        { return reinterpret_cast<const Point *>(m_coords.data()); }
    Points::const_iterator end() const
        { return reinterpret_cast<const Point *>(
            m_coords.data() + m_coords.size()); }
    size_t size() const
        { return m_coords.size() / 2; }

private:
    const std::vector<double>& m_coords;
};

class Delaunator {

public:
    std::vector<double> const& coords;
    Points m_points;

    // 'triangles' stores the indices to the 'X's of the input
    // 'coords'.
    std::vector<std::size_t> triangles;

    // 'halfedges' store indices into 'triangles'.  If halfedges[X] = Y,
    // It says that there's an edge from X to Y where a) X and Y are
    // both indices into triangles and b) X and Y are indices into different
    // triangles in the array.  This allows you to get from a triangle to
    // its adjacent triangle.  If the a triangle edge has no adjacent triangle,
    // its half edge will be INVALID_INDEX.
    std::vector<std::size_t> halfedges;

    std::vector<std::size_t> hull_prev;
    std::vector<std::size_t> hull_next;

    // This contains indexes into the triangles array.
    std::vector<std::size_t> hull_tri;
    std::size_t hull_start;

    INLINE Delaunator(std::vector<double> const& in_coords);
    INLINE double get_hull_area();
    INLINE double get_triangle_area();

private:
    std::vector<std::size_t> m_hash;
    Point m_center;
    std::size_t m_hash_size;
    std::vector<std::size_t> m_edge_stack;

    INLINE std::size_t legalize(std::size_t a);
    INLINE std::size_t hash_key(double x, double y) const;
    INLINE std::size_t add_triangle(
        std::size_t i0,
        std::size_t i1,
        std::size_t i2,
        std::size_t a,
        std::size_t b,
        std::size_t c);
    INLINE void link(std::size_t a, std::size_t b);
};

//@see https://stackoverflow.com/questions/33333363/built-in-mod-vs-custom-mod-function-improve-the-performance-of-modulus-op/33333636#33333636
inline size_t fast_mod(const size_t i, const size_t c) {
    return i >= c ? i % c : i;
}

// Kahan and Babuska summation, Neumaier variant; accumulates less FP error
inline double sum(const std::vector<double>& x) {
    double sum = x[0];
    double err = 0.0;

    for (size_t i = 1; i < x.size(); i++) {
        const double k = x[i];
        const double m = sum + k;
        err += std::fabs(sum) >= std::fabs(k) ? sum - m + k : k - m + sum;
        sum = m;
    }
    return sum + err;
}

inline double dist(
    const double ax,
    const double ay,
    const double bx,
    const double by) {
    const double dx = ax - bx;
    const double dy = ay - by;
    return dx * dx + dy * dy;
}

inline double circumradius(const Point& p1, const Point& p2, const Point& p3)
{
    Point d = Point::vector(p1, p2);
    Point e = Point::vector(p1, p3);

    const double bl = d.magnitude2();
    const double cl = e.magnitude2();
    const double det = Point::determinant(d, e);


    Point radius((e.y() * bl - d.y() * cl) * 0.5 / det,
                 (d.x() * cl - e.x() * bl) * 0.5 / det);

  double l2 = radius.x() * radius.x() + radius.y() * radius.y();

    if ((bl > 0.0 || bl < 0.0) &&
        (cl > 0.0 || cl < 0.0) &&
        (det > 0.0 || det < 0.0))
        return radius.magnitude2();
    return (std::numeric_limits<double>::max)();
}

inline double circumradius(
    const double ax,
    const double ay,
    const double bx,
    const double by,
    const double cx,
    const double cy) {
    const double dx = bx - ax;
    const double dy = by - ay;
    const double ex = cx - ax;
    const double ey = cy - ay;

    const double bl = dx * dx + dy * dy;
    const double cl = ex * ex + ey * ey;
    const double d = dx * ey - dy * ex;

    const double x = (ey * bl - dy * cl) * 0.5 / d;
    const double y = (dx * cl - ex * bl) * 0.5 / d;

    if ((bl > 0.0 || bl < 0.0) && (cl > 0.0 || cl < 0.0) && (d > 0.0 || d < 0.0)) {
        return x * x + y * y;
    } else {
        return (std::numeric_limits<double>::max)();
    }
}

inline bool clockwise(const Point& p0, const Point& p1, const Point& p2)
{
    Point v0 = Point::vector(p0, p1);
    Point v1 = Point::vector(p0, p2);
    double det = Point::determinant(v0, v1);
    double dist = v0.magnitude2() + v1.magnitude2();
    double dist2 = Point::dist2(v0, v1);
    if (det == 0)
    {
        return false;
    }
    double reldet = std::abs(dist / det);
    if (reldet > 1e14)
        return false;
    return det < 0;
}

inline bool clockwise(double px, double py, double qx, double qy,
    double rx, double ry)
{
    Point p0(px, py);
    Point p1(qx, qy);
    Point p2(rx, ry);
    return clockwise(p0, p1, p2);
}

inline bool counterclockwise(const Point& p0, const Point& p1, const Point& p2)
{
    Point v0 = Point::vector(p0, p1);
    Point v1 = Point::vector(p0, p2);
    double det = Point::determinant(v0, v1);
    double dist = v0.magnitude2() + v1.magnitude2();
    double dist2 = Point::dist2(v0, v1);
    if (det == 0)
        return false;
    double reldet = std::abs(dist / det);
    if (reldet > 1e14)
        return false;
    return det > 0;
}

inline bool counterclockwise(double px, double py, double qx, double qy,
    double rx, double ry)
{
    Point p0(px, py);
    Point p1(qx, qy);
    Point p2(rx, ry);
    return counterclockwise(p0, p1, p2);
}


inline Point circumcenter(
    const double ax,
    const double ay,
    const double bx,
    const double by,
    const double cx,
    const double cy) {
    const double dx = bx - ax;
    const double dy = by - ay;
    const double ex = cx - ax;
    const double ey = cy - ay;

    const double bl = dx * dx + dy * dy;
    const double cl = ex * ex + ey * ey;
    //ABELL - This is suspect for div-by-0.
    const double d = dx * ey - dy * ex;

    const double x = ax + (ey * bl - dy * cl) * 0.5 / d;
    const double y = ay + (dx * cl - ex * bl) * 0.5 / d;

    return Point(x, y);
}

inline bool in_circle(
    const double ax,
    const double ay,
    const double bx,
    const double by,
    const double cx,
    const double cy,
    const double px,
    const double py) {
    const double dx = ax - px;
    const double dy = ay - py;
    const double ex = bx - px;
    const double ey = by - py;
    const double fx = cx - px;
    const double fy = cy - py;

    const double ap = dx * dx + dy * dy;
    const double bp = ex * ex + ey * ey;
    const double cp = fx * fx + fy * fy;

    return (dx * (ey * cp - bp * fy) -
            dy * (ex * cp - bp * fx) +
            ap * (ex * fy - ey * fx)) < 0.0;
}

constexpr double EPSILON = std::numeric_limits<double>::epsilon();

inline bool check_pts_equal(double x1, double y1, double x2, double y2) {
    return std::fabs(x1 - x2) <= EPSILON &&
           std::fabs(y1 - y2) <= EPSILON;
}

// monotonically increases with real angle, but doesn't need expensive trigonometry
inline double pseudo_angle(const double dx, const double dy) {
    const double p = dx / (std::abs(dx) + std::abs(dy));
    return (dy > 0.0 ? 3.0 - p : 1.0 + p) / 4.0; // [0..1)
}


Delaunator::Delaunator(std::vector<double> const& in_coords)
    : coords(in_coords), m_points(in_coords)
{
    std::size_t n = coords.size() >> 1;

    std::vector<std::size_t> ids(n);
    std::iota(ids.begin(), ids.end(), 0);

    double max_x = std::numeric_limits<double>::lowest();
    double max_y = std::numeric_limits<double>::lowest();
    double min_x = (std::numeric_limits<double>::max)();
    double min_y = (std::numeric_limits<double>::max)();
    for (const Point& p : m_points)
    {
        min_x = std::min(p.x(), min_x);
        min_y = std::min(p.y(), min_y);
        max_x = std::max(p.x(), max_x);
        max_y = std::max(p.y(), max_y);
    }
    double width = max_x - min_x;
    double height = max_y - min_y;
    double span = width * width + height * height; // Everything is square dist.

    Point center((min_x + max_x) / 2, (min_y + max_y) / 2);

    std::size_t i0 = INVALID_INDEX;
    std::size_t i1 = INVALID_INDEX;
    std::size_t i2 = INVALID_INDEX;

    // pick a seed point close to the centroid
    double min_dist = (std::numeric_limits<double>::max)();
    for (size_t i = 0; i < m_points.size(); ++i)
    {
        const Point& p = m_points[i];
        const double d = Point::dist2(center, p);
        if (d < min_dist) {
            i0 = i;
            min_dist = d;
        }
    }

    const Point& p0 = m_points[i0];

    min_dist = (std::numeric_limits<double>::max)();

    // find the point closest to the seed
    for (std::size_t i = 0; i < n; i++) {
        if (i == i0) continue;
        const double d = Point::dist2(p0, m_points[i]);
        if (d < min_dist && d > 0.0) {
            i1 = i;
            min_dist = d;
        }
    }

    const Point& p1 = m_points[i1];

    double min_radius = (std::numeric_limits<double>::max)();

    // find the third point which forms the smallest circumcircle
    // with the first two
    for (std::size_t i = 0; i < n; i++) {
        if (i == i0 || i == i1) continue;

        const double r = circumradius(p0, p1, m_points[i]);
        if (r < min_radius) {
            i2 = i;
            min_radius = r;
        }
    }

    if (!(min_radius < (std::numeric_limits<double>::max)())) {
        throw std::runtime_error("not triangulation");
    }

    const Point& p2 = m_points[i2];

    if (counterclockwise(p0, p1, p2))
        std::swap(i1, i2);

    cout << i0 << ", " << i1 << ", " << i2 << "\n";

    double i0x = p0.x();
    double i0y = p0.y();
    double i1x = m_points[i1].x();
    double i1y = m_points[i1].y();
    double i2x = m_points[i2].x();
    double i2y = m_points[i2].y();

    m_center = circumcenter(i0x, i0y, i1x, i1y, i2x, i2y);

    // Calculate the distances from the center once to avoid having to
    // calculate for each compare.  This used to be done in the comparator,
    // but GCC 7.5+ would copy the comparator to iterators used in the
    // sort, and this was excruciatingly slow when there were many points
    // because you had to copy the vector of distances.
    std::vector<double> dists;
    dists.reserve(m_points.size());
    for (const Point& p : m_points)
        dists.push_back(dist(p.x(), p.y(), m_center.x(), m_center.y()));

    // sort the points by distance from the seed triangle circumcenter
    std::sort(ids.begin(), ids.end(),
        [&dists](std::size_t i, std::size_t j)
            { return dists[i] < dists[j]; });

    // initialize a hash table for storing edges of the advancing convex hull
    m_hash_size = static_cast<std::size_t>(std::ceil(std::sqrt(n)));
    m_hash.resize(m_hash_size);
    std::fill(m_hash.begin(), m_hash.end(), INVALID_INDEX);

    // initialize arrays for tracking the edges of the advancing convex hull
    hull_prev.resize(n);
    hull_next.resize(n);
    hull_tri.resize(n);

    hull_start = i0;

    size_t hull_size = 3;

    hull_next[i0] = hull_prev[i2] = i1;
    hull_next[i1] = hull_prev[i0] = i2;
    hull_next[i2] = hull_prev[i1] = i0;

    hull_tri[i0] = 0;
    hull_tri[i1] = 1;
    hull_tri[i2] = 2;

    m_hash[hash_key(i0x, i0y)] = i0;
    m_hash[hash_key(i1x, i1y)] = i1;
    m_hash[hash_key(i2x, i2y)] = i2;

    // ABELL - Why are we doing this is n < 3?  There is no triangulation if
    //  there is no triangle.

    std::size_t max_triangles = n < 3 ? 1 : 2 * n - 5;
    triangles.reserve(max_triangles * 3);
    halfedges.reserve(max_triangles * 3);
    add_triangle(i0, i1, i2, INVALID_INDEX, INVALID_INDEX, INVALID_INDEX);
    double xp = std::numeric_limits<double>::quiet_NaN();
    double yp = std::numeric_limits<double>::quiet_NaN();

    // Go through points based on distance from the center.
    for (std::size_t k = 0; k < n; k++) {
        const std::size_t i = ids[k];
        const double x = coords[2 * i];
        const double y = coords[2 * i + 1];

        // skip near-duplicate points
        if (k > 0 && check_pts_equal(x, y, xp, yp))
            continue;
        xp = x;
        yp = y;

        //ABELL - This is dumb.  We have the indices.  Use them.
        // skip seed triangle points
        if (check_pts_equal(x, y, i0x, i0y) ||
            check_pts_equal(x, y, i1x, i1y) ||
            check_pts_equal(x, y, i2x, i2y)) continue;

        // find a visible edge on the convex hull using edge hash
        std::size_t start = 0;

        size_t key = hash_key(x, y);
        for (size_t j = 0; j < m_hash_size; j++) {
            start = m_hash[fast_mod(key + j, m_hash_size)];

            // ABELL - Not sure how hull_next[start] could ever equal start
            // I *think* hull_next is just a representation of the hull in one
            // direction.
            if (start != INVALID_INDEX && start != hull_next[start])
                break;
        }

        //ABELL
        // Make sure what we found is on the hull.
        assert(hull_prev[start] != start);
        assert(hull_prev[start] != INVALID_INDEX);

        start = hull_prev[start];
        size_t e = start;
        size_t q;

        // Advance until we find a place in the hull where our current point
        // can be added.
        while (true)
        {
            q = hull_next[e];
            //if (e == 96) {
              //for (int i = 0; i < hull_next.size(); ++i) {
                //printf("%ld ", hull_next[i]);
              //}
              //printf("\n");
              //throw;
            //}
            if (Point::equal(m_points[i], m_points[e], span) ||
                Point::equal(m_points[i], m_points[q], span))
            {
                e = INVALID_INDEX;
                 break;
            }
            if (counterclockwise(x, y, coords[2 * e], coords[2 * e + 1],
                coords[2 * q], coords[2 * q + 1]))
                break;
            e = q;
            if (e == start) {
                e = INVALID_INDEX;
                break;
            }
        }

        // ABELL
        // This seems wrong.  Perhaps we should check what's going on?
        if (e == INVALID_INDEX)     // likely a near-duplicate point; skip it
            continue;

        // add the first triangle from the point
        std::size_t t = add_triangle(
            e,
            i,
            hull_next[e],
            INVALID_INDEX,
            INVALID_INDEX,
            hull_tri[e]);

        hull_tri[i] = legalize(t + 2); // Legalize the triangle we just added.
        hull_tri[e] = t;
        hull_size++;

        // walk forward through the hull, adding more triangles and
        // flipping recursively
        std::size_t next = hull_next[e];
        while (true)
        {
            q = hull_next[next];
            if (!counterclockwise(x, y, coords[2 * next], coords[2 * next + 1],
                coords[2 * q], coords[2 * q + 1]))
                break;
            t = add_triangle(next, i, q,
                hull_tri[i], INVALID_INDEX, hull_tri[next]);
            hull_tri[i] = legalize(t + 2);
            hull_next[next] = next; // mark as removed
            hull_size--;
            next = q;
        }

        // walk backward from the other side, adding more triangles and flipping
        if (e == start) {
            while (true)
            {
                q = hull_prev[e];
                if (!counterclockwise(x, y, coords[2 * q], coords[2 * q + 1],
                    coords[2 * e], coords[2 * e + 1]))
                    break;
                t = add_triangle(q, i, e,
                    INVALID_INDEX, hull_tri[e], hull_tri[q]);
                legalize(t + 2);
                hull_tri[q] = t;
                hull_next[e] = e; // mark as removed
                hull_size--;
                e = q;
            }
        }

        // update the hull indices
        hull_prev[i] = e;
        hull_start = e;
        hull_prev[next] = i;
        hull_next[e] = i;
        hull_next[i] = next;

        m_hash[hash_key(x, y)] = i;
        m_hash[hash_key(coords[2 * e], coords[2 * e + 1])] = e;
    }
}

double Delaunator::get_hull_area()
{
    std::vector<double> hull_area;
    size_t e = hull_start;
    size_t cnt = 1;
    do {
        hull_area.push_back((coords[2 * e] - coords[2 * hull_prev[e]]) *
            (coords[2 * e + 1] + coords[2 * hull_prev[e] + 1]));
        cnt++;
        e = hull_next[e];
    } while (e != hull_start);
    return sum(hull_area);
}

double Delaunator::get_triangle_area()
{
    std::vector<double> vals;
    for (size_t i = 0; i < triangles.size(); i += 3)
    {
        const double ax = coords[2 * triangles[i]];
        const double ay = coords[2 * triangles[i] + 1];
        const double bx = coords[2 * triangles[i + 1]];
        const double by = coords[2 * triangles[i + 1] + 1];
        const double cx = coords[2 * triangles[i + 2]];
        const double cy = coords[2 * triangles[i + 2] + 1];
        double val = std::fabs((by - ay) * (cx - bx) - (bx - ax) * (cy - by));
        vals.push_back(val);
    }
    return sum(vals);
}

std::size_t Delaunator::legalize(std::size_t a) {
    std::size_t i = 0;
    std::size_t ar = 0;
    m_edge_stack.clear();

    // recursion eliminated with a fixed-size stack
    while (true) {
        const size_t b = halfedges[a];

        /* if the pair of triangles doesn't satisfy the Delaunay condition
        * (p1 is inside the circumcircle of [p0, pl, pr]), flip them,
        * then do the same check/flip recursively for the new pair of triangles
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
                a = m_edge_stack[i];
                continue;
            } else {
                //i = INVALID_INDEX;
                break;
            }
        }

        const size_t b0 = 3 * (b / 3);
        const size_t al = a0 + (a + 1) % 3;
        const size_t bl = b0 + (b + 2) % 3;

        const std::size_t p0 = triangles[ar];
        const std::size_t pr = triangles[a];
        const std::size_t pl = triangles[al];
        const std::size_t p1 = triangles[bl];

        const bool illegal = in_circle(
            coords[2 * p0],
            coords[2 * p0 + 1],
            coords[2 * pr],
            coords[2 * pr + 1],
            coords[2 * pl],
            coords[2 * pl + 1],
            coords[2 * p1],
            coords[2 * p1 + 1]);

        if (illegal) {
            triangles[a] = p1;
            triangles[b] = p0;

            auto hbl = halfedges[bl];

            // Edge swapped on the other side of the hull (rare).
            // Fix the halfedge reference
            if (hbl == INVALID_INDEX) {
                std::size_t e = hull_start;
                do {
                    if (hull_tri[e] == bl) {
                        hull_tri[e] = a;
                        break;
                    }
                    e = hull_prev[e];
                } while (e != hull_start);
            }
            link(a, hbl);
            link(b, halfedges[ar]);
            link(ar, bl);
            std::size_t br = b0 + (b + 1) % 3;

            if (i < m_edge_stack.size()) {
                m_edge_stack[i] = br;
            } else {
                m_edge_stack.push_back(br);
            }
            i++;

        } else {
            if (i > 0) {
                i--;
                a = m_edge_stack[i];
                continue;
            } else {
                break;
            }
        }
    }
    return ar;
}

std::size_t Delaunator::hash_key(const double x, const double y) const {
    const double dx = x - m_center.x();
    const double dy = y - m_center.y();
    return fast_mod(
        static_cast<std::size_t>(std::llround(std::floor(pseudo_angle(dx, dy) * static_cast<double>(m_hash_size)))),
        m_hash_size);
}

std::size_t Delaunator::add_triangle(
    std::size_t i0,
    std::size_t i1,
    std::size_t i2,
    std::size_t a,
    std::size_t b,
    std::size_t c) {
    std::size_t t = triangles.size();
    triangles.push_back(i0);
    triangles.push_back(i1);
    triangles.push_back(i2);
    link(t, a);
    link(t + 1, b);
    link(t + 2, c);
    return t;
}

void Delaunator::link(const std::size_t a, const std::size_t b) {
    std::size_t s = halfedges.size();
    if (a == s) {
        halfedges.push_back(b);
    } else if (a < s) {
        halfedges[a] = b;
    } else {
        throw std::runtime_error("Cannot link edge");
    }
    if (b != INVALID_INDEX) {
        std::size_t s2 = halfedges.size();
        if (b == s2) {
            halfedges.push_back(a);
        } else if (b < s2) {
            halfedges[b] = a;
        } else {
            throw std::runtime_error("Cannot link edge");
        }
    }
}

} //namespace delaunator

//class BBox2 {
   //private:
    //Vec2 bottomLeft_;
    //Vec2 topRight_;
    //Vec2 center_;

   //public:
    //BBox2(const vector<Vec2>& points) {
        //topRight_ = Vec2(-INF, -INF);
        //bottomLeft_ = Vec2(INF, INF);
        //for (const auto& p : points) {
            //bottomLeft_.x = min(bottomLeft_.x, p.x);
            //bottomLeft_.y = min(bottomLeft_.y, p.y);
            //topRight_.x = max(topRight_.x, p.x);
            //topRight_.y = max(topRight_.y, p.y);
        //}
        //center_ = (bottomLeft_ + topRight_) / 2;
    //}

    //const Vec2& bottomLeft() const { return bottomLeft_; }
    //const Vec2& topRight() const { return topRight_; }
    //const Vec2& center() const { return center_; }
//};

//class Delaunay {
   //public:
    //vector<Vec2> points_;

    //vector<size_t> triangles_;
    //vector<size_t> halfEdges_;

   //private:
    //Vec2 center_;

    //// temporary arrays for tracking the edges of the advancing convex hull
    //size_t hullStart_;
    //vector<size_t> hullPrev_;
    //vector<size_t> hullNext_;
    //vector<size_t> hullTri_;

    //size_t hashSize_;
    //vector<size_t> hullHash_;

    //static constexpr size_t INVALID_INDEX = (size_t)(-1);

   //public:
    //Delaunay(const vector<Vec2>& points) : points_(points) {
        //initialize();
    //};

    //vector<pair<size_t, size_t>> uniqueEdges() const {
        //set<pair<size_t, size_t>> edges;
        //for (size_t i = 0; i < triangles_.size(); i += 3) {
            //for (size_t j = 0; j < 3; ++j) {
                //size_t u, v;
                //u = triangles_[i + j];
                //v = triangles_[i + (j + 1) % 3];
                //if (u > v) {
                    //swap(u, v);
                //}
                //edges.insert({u, v});
            //}
        //}
        //return vector<pair<size_t, size_t>>(edges.begin(), edges.end());
    //}

   //private:
    //void initialize() {
        //BBox2 bbox(points_);
        //const auto& bboxCenter = bbox.center();

        //size_t i0 = INVALID_INDEX, i1 = INVALID_INDEX, i2 = INVALID_INDEX;
        //const auto findClosestPoint =
            //[&i0, &i1, this](const function<double(const Vec2&)>& criterion) -> size_t {
            //size_t res = INVALID_INDEX;
            //double minDist = INF;
            //for (size_t i = 0; i < points_.size(); ++i) {
                //if (i == i0 || i == i1) 
                    //continue;
                //double dist = criterion(points_[i]);
                //if (dist < minDist) {
                    //minDist = dist;
                    //res = i;
                //}
            //}
            //return res;
        //};

        //i0 = findClosestPoint(
            //[&bboxCenter](const Vec2& p) -> double { return bboxCenter.squaredLength(p); });
        //Vec2 p0 = points_[i0];

        //i1 = findClosestPoint([&p0](const Vec2& p) -> double { return p0.squaredLength(p); });
        //Vec2 p1 = points_[i1];

        //i2 = findClosestPoint(
            //[&p0, &p1](const Vec2& p) -> double { return circumradius(p0, p1, p); });
        //Vec2 p2 = points_[i2];

        //auto orientation = Vec2::orientation(p0, p1, p2);
        //if (orientation == 0) {
            //throw std::runtime_error("no triangle!");
        //}

        //if (orientation == -1) { // counterclockwise
            //swap(i1, i2);
            //swap(p1, p2);
        //}

        //center_ = circumcenter(p0, p1, p2);

        //cout << "bboxTR: " << bbox.topRight() << "\n";
        //cout << "bboxBL: " << bbox.bottomLeft() << "\n";
        //cout << "bboxCenter: " << bboxCenter << "\n";
        //cout << "seed inds: " << i0 << ", " << i1 << ", " << i2 << "\n";
        //cout << "seed points: " << p0 << ", " << p1 << ", " << p2 << "\n";
        //cout << "seed center: " << center_ << "\n";

        //std::vector<std::size_t> inds(points_.size());
        //std::iota(inds.begin(), inds.end(), 0);
        //{
            //vector<double> dists;
            //dists.reserve(points_.size());
            //for (const Vec2& p : points_)
                //dists.push_back(center_.squaredLength(p));
            //std::sort(inds.begin(), inds.end(),
                      //[&dists](std::size_t i, std::size_t j) { return dists[i] < dists[j]; });
        //}

        //// initialize triangles and links
        //size_t maxTriangles = 2 * points_.size() - 5;
        //triangles_.reserve(maxTriangles * 3);
        //halfEdges_.reserve(maxTriangles * 3);
        //addTriangle(i0, i1, i2);

        //// initialize a hash table for storing edges of the advancing convex hull
        //hashSize_ = ceil(sqrt(double(points_.size())));
        //hullHash_.resize(hashSize_, INVALID_INDEX);
        //hullHash_[hashKey(p0)] = i0;
        //hullHash_[hashKey(p1)] = i1;
        //hullHash_[hashKey(p2)] = i2;

        //// initialize arrays for tracking the edges of the advancing convex hull
        //hullPrev_.resize(points_.size(), INVALID_INDEX);
        //hullNext_.resize(points_.size(), INVALID_INDEX);
        //hullTri_.resize(points_.size(), INVALID_INDEX);
        //hullStart_ = i0;
        //size_t hullSize = 3;

        //hullNext_[i0] = hullPrev_[i2] = i1;
        //hullNext_[i1] = hullPrev_[i0] = i2;
        //hullNext_[i2] = hullPrev_[i1] = i0;

        //hullTri_[i0] = 0;
        //hullTri_[i1] = 1;
        //hullTri_[i2] = 2;
        
        //Vec2 xp(numeric_limits<double>::quiet_NaN(), numeric_limits<double>::quiet_NaN());

        //// Go through points based on distance from the center.
        //for (size_t k = 0; k < points_.size(); ++k) {
            //const size_t i = inds[k];
            //const Vec2& p = points_[i];

            //// skip duplicate points
            //if (k > 0 && xp == p)
                //continue;
            //xp = p;

            //// skip seed triangle points
            //if (i == i0 || i == i1 || i == i2)
                //continue;

            //size_t start = 0;
            //size_t key = hashKey(p);
            //for (size_t j = 0; j < hashSize_; j++) {
                //start = hullHash_[(key + j) % hashSize_];

                //if (start != INVALID_INDEX && start != hullNext_[start]) {
                    //break;
                //}
            //}

            //assert(hullPrev_[start] != start);
            //assert(hullPrev_[start] != INVALID_INDEX);

            //cout << "start: " << start << "\n";

            //start = hullPrev_[start];
            //size_t e = start;
            //size_t q;

            //assert(e != INVALID_INDEX);

            //// Advance until we find a place in the hull where our current point
            //// can be added.
            //while (true) {
                //q = hullNext_[e];
                //cout << "intersecting edge: " << e << ", " << q << ", " << Vec2::orientation(p, points_[e], points_[q]) << "\n";
                //if (points_[i] == points_[e] || points_[i] == points_[q]) {
                    //e = INVALID_INDEX;
                    //break;
                //}
                //if (Vec2::orientation(p, points_[e], points_[q]) == -1) {
                    //break;
                //}
                //e = q;
                //if (e == start) {
                    //e = INVALID_INDEX;
                    //break;
                //}
                //assert(e != INVALID_INDEX);
            //}

            ////assert(e != INVALID_INDEX);
            //if (e == INVALID_INDEX)
                //continue;

            //size_t t = addTriangle(e, i, hullNext_[e], INVALID_INDEX, INVALID_INDEX, hullTri_[e]);
            //hullTri_[i] = legalize(t+2);
            //hullTri_[e] = t;
            //hullSize++;

            //// walk forward through the hull, adding more triangles and
            //// flipping recursively
            //std::size_t next = hullNext_[e];
            //while (true)
            //{
                //q = hullNext_[next];
                //if (Vec2::orientation(p, points_[next], points_[q]) != -1) {
                    //break;
                //}
                //t = addTriangle(next, i, q, hullTri_[i], INVALID_INDEX, hullTri_[next]);
                //hullTri_[i] = legalize(t + 2);
                //hullNext_[next] = next;  // mark as removed
                //hullSize--;
                //next = q;
            //}

            //// walk backward from the other side, adding more triangles and flipping
            //if (e == start) {
                //while (true) {
                    //q = hullPrev_[e];
                    //if (Vec2::orientation(p, points_[q], points_[e]) != -1)
                        //break;
                    //t = addTriangle(q, i, e, INVALID_INDEX, hullTri_[e], hullTri_[q]);
                    //legalize(t + 2);
                    //hullTri_[q] = t;
                    //hullNext_[e] = e;  // mark as removed
                    //hullSize--;
                    //e = q;
                //}
            //}
            //// update the hull indices
            //hullPrev_[i] = e;
            //hullStart_ = e;
            //hullPrev_[next] = i;
            //hullNext_[e] = i;
            //hullNext_[i] = next;
        //}
    //}

    //size_t addTriangle(size_t i0,
                       //std::size_t i1,
                       //std::size_t i2,
                       //std::size_t a = INVALID_INDEX,
                       //std::size_t b = INVALID_INDEX,
                       //std::size_t c = INVALID_INDEX) {
        //size_t t = triangles_.size();
        //triangles_.push_back(i0);
        //triangles_.push_back(i1);
        //triangles_.push_back(i2);
        //link(t, a);
        //link(t + 1, b);
        //link(t + 2, c);
        //cout << "added triangle(" << t << ") - " << i0 << ", " << i1 << ", " << i2 << "\n";
        //return t;
    //}

    //void link(const size_t a, const size_t b) {
        //size_t s = halfEdges_.size();
        //if (a == s) {
            //halfEdges_.push_back(b);
        //} else if (a < s) {
            //halfEdges_[a] = b;
        //} else {
            //throw runtime_error("Cannot link edge");
        //}
        //if (b != INVALID_INDEX) {
            //size_t s2 = halfEdges_.size();
            //if (b == s2) {
                //halfEdges_.push_back(a);
            //} else if (b < s2) {
                //halfEdges_[b] = a;
            //} else {
                //throw runtime_error("Cannot link edge");
            //}
        //}
    //}

    //size_t legalize(size_t a) {
        //size_t i = 0;
        //size_t ar = 0;
        //vector<size_t> edgeStack;

        //// recursion eliminated with a fixed-size stack
        //while (true) {
            //const size_t b = halfEdges_[a];

            /* if the pair of triangles doesn't satisfy the Delaunay condition
             * (p1 is inside the circumcircle of [p0, pl, pr]), flip them,
             * then do the same check/flip recursively for the new pair of triangles
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
            //const size_t a0 = 3 * (a / 3);
            //ar = a0 + (a + 2) % 3;

            //if (b == INVALID_INDEX) {
                //if (i > 0) {
                    //i--;
                    //a = edgeStack[i];
                    //continue;
                //} else {
                    ////i = INVALID_INDEX;
                    //break;
                //}
            //}

            //const size_t b0 = 3 * (b / 3);
            //const size_t al = a0 + (a + 1) % 3;
            //const size_t bl = b0 + (b + 2) % 3;

            //const size_t p0 = triangles_[ar];
            //const size_t pr = triangles_[a];
            //const size_t pl = triangles_[al];
            //const size_t p1 = triangles_[bl];

            //const bool illegal = inCircle(points_[p0], points_[pr], points_[pl], points_[p1]);
            //if (illegal) {
                //cout << "illegal triangle found! - " << p1 << " in triangle " << p0 << ", " << pr << ", " << pl << " \n";
                //triangles_[a] = p1;
                //triangles_[b] = p0;

                //auto hbl = halfEdges_[bl];

                //// Edge swapped on the other side of the hull (rare).
                //// Fix the halfedge reference
                //if (hbl == INVALID_INDEX) {
                    //size_t e = hullStart_;
                    //do {
                        //if (hullTri_[e] == bl) {
                            //hullTri_[e] = a;
                            //break;
                        //}
                        //e = hullPrev_[e];
                    //} while (e != hullStart_);
                //}
                //link(a, hbl);
                //link(b, halfEdges_[ar]);
                //link(ar, bl);
                //size_t br = b0 + (b + 1) % 3;

                //if (i < edgeStack.size()) {
                    //edgeStack[i] = br;
                //} else {
                    //edgeStack.push_back(br);
                //}
                //i++;

            //} else {
                //if (i > 0) {
                    //i--;
                    //a = edgeStack[i];
                    //continue;
                //} else {
                    //break;
                //}
            //}
        //}
        //return ar;
    //}

    //static inline double pseudoAngle(const Vec2& v) {
        //const double x = v.x / (std::abs(v.x) + std::abs(v.y));
        //return (v.y > 0.0 ? 3.0 - x : 1.0 + x) / 4.0;
    //}

    //size_t hashKey(const Vec2& p) const {
        //const Vec2 v = p - center_;
        //size_t key = pseudoAngle(v) * double(hullHash_.size());
        //return key % hullHash_.size();
    //}
//};

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
        vector<double> coords(2*N);
        for (int i = 0; i < N; ++i) {
            coords[2*i+0] = points[i].x;
            coords[2*i+1] = points[i].y;
        }
        delaunator::Delaunator delaunay(coords);
        //Delaunay delaunay(points);

        double ans = INF;
        for (int i = 0; i < delaunay.triangles.size(); i+=3) {
            const auto& p0 = points[delaunay.triangles[i+0]];
            const auto& p1 = points[delaunay.triangles[i+1]];
            const auto& p2 = points[delaunay.triangles[i+2]];
            ans = min(ans, p0.length(p1) - p0.r - p1.r);
            ans = min(ans, p1.length(p2) - p1.r - p2.r);
            ans = min(ans, p2.length(p0) - p2.r - p0.r);
        }
        //for (const auto& [u, v] : delaunay.uniqueEdges()) {
            //const auto& p1 = points[u];
            //const auto& p2 = points[v];
            //ans = min(ans, p1.length(p2) - p1.r - p2.r);
            //cout << "edge(" << u << "-" << v << ") -  length: " << p1.length(p2) - p1.r - p2.r << "\n";
        //}
        return ans;
    }
    catch(const std::exception& e) {
        // all points are colinear?
        double ans = std::numeric_limits<double>::max();
        sort(points.begin(), points.end());
        for (int i = 0; i < N-1; ++i) {
            const auto& p0 = points[i];
            const auto& p1 = points[i+1];
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
        //printf("%lf\n", ans);
    }

    return 0;
}

