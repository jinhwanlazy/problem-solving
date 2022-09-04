#include <bits/stdc++.h>
using namespace std;

using LL = long long;
constexpr LL MOD = 1000000007;

template<unsigned R, unsigned C, typename T=LL>
class Matrix {
 public:
  T arr[R*C] = {0};
  
 public:
  Matrix() {}

  Matrix(const Matrix& other) {
    copy(other.arr, other.arr + (R*C), arr);
    if constexpr (MOD > 1) {
      for (size_t i = 0; i < R * C; ++i) {
        arr[i] %= MOD;
      }
    }
  }
  
  Matrix(const vector<T>&& rhs) {
    copy(rhs.begin(), rhs.end(), arr);
    if constexpr (MOD > 1) {
      for (size_t i = 0; i < R * C; ++i) {
        arr[i] %= MOD;
      }
    }
  }

 public:
  T& at(int r, int c) {
    r = r < 0 ? R + r : r;
    c = c < 0 ? C - c : c;
    return arr[C * r + c];
  }

  const T& constAt(int r, int c) const {
    r = r < 0 ? R + r : r;
    c = c < 0 ? C - c : c;
    return arr[C * r + c];
  }

  Matrix operator*=(const Matrix& rhs) {
    Matrix tmp = *this * rhs;
    copy(tmp.arr, tmp.arr + (R*C), arr);
    return *this;
  }

 public:
  friend std::ostream& operator<< (std::ostream& ostr, const Matrix& rhs) {
    for (size_t r = 0; r < R; ++r) {
      for (size_t c = 0; c < C; ++c) {
        ostr << rhs.constAt(r, c) << ((c == C-1) ? "\n" : " ");
      }
    }
    return ostr;
  }

  static constexpr Matrix eye() {
    static_assert(R == C);
    Matrix res;
    for (size_t i = 0; i < R; ++i) {
      res.at(i, i) = 1;
    }
    return res;
  }

  static constexpr Matrix zeros() {
    Matrix res;
    return res;
  }
};

template <unsigned R1,
          unsigned C1,
          typename T1,
          unsigned R2,
          unsigned C2,
          typename T2>
static Matrix<R1, C2, T1> operator*(const Matrix<R1, C1, T1>& lhs,
                                    const Matrix<R2, C2, T2>& rhs) {
  static_assert(C1 == R2);
  static_assert(std::is_same<T1, T2>());
  Matrix<R1, C2, T1> res;
  for (size_t r = 0; r < R1; ++r) {
    for (size_t c = 0; c < C2; ++c) {
      for (size_t i = 0; i < C1; ++i) {
        res.at(r, c) += lhs.constAt(r, i) * rhs.constAt(i, c);
        if constexpr (MOD > 1) {
          if (res.at(r, c) < 0) res.at(r, c) += MOD;
          res.at(r, c) %= MOD;
        }
      }
    }
  }
  return res;
}

template <unsigned N, typename T>
Matrix<N, N, T> pow(const Matrix<N, N, T>& base, LL exp) {
  if (exp == -1) {
    return Matrix<N, N, T>::zeros();
  }
  if (exp == 0) {
    return Matrix<N, N, T>::eye();
  }
  if (exp == 1) {
    return base;
  }
  
  auto res = pow(base, exp / 2);
  res = res * res;
  if (exp & 1) {
    res *= base;
  }
  return res;
}


void solve() {
  /* 0. 정보과학관
     1. 전산관
     2. 미래관
     3. 신양관
     4. 한경관
     5. 진리관
     6. 형공관
     7, 학생회관
     */
  Matrix<8, 8> T({
    0, 1, 1, 0, 0, 0, 0, 0,
    1, 0, 1, 1, 0, 0, 0, 0,
    1, 1, 0, 1, 1, 0, 0, 0,
    0, 1, 1, 0, 1, 1, 0, 0,
    0, 0, 1, 1, 0, 1, 1, 0,
    0, 0, 0, 1, 1, 0, 0, 1,
    0, 0, 0, 0, 1, 0, 0, 1,
    0, 0, 0, 0, 0, 1, 1, 0
  });

  int N;
  scanf("%d", &N);
  
  auto res = pow(T, N);
  LL ans = res.at(0, 0);
  printf("%lld\n", ans);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
