#include <bits/stdc++.h>
using namespace std;

template <typename array_t>
class Manacher {
 public:
  Manacher(const array_t& s)
      : s_(2 * s.size() + 1, PADDING), radii_(2 * s.size() + 1, 0) {
    for (size_t i = 0; i < s.size(); ++i) {
      s_[2 * i + 1] = s[i];
    }
  }

  size_t solve() {
    size_t center = 0, radius = 0;
    while (center < s_.size()) {
      while (center - (radius + 1) >= 0 &&				 //
              center + (radius + 1) < s_.size() &&	//
              s_[center - (radius + 1)] == s_[center + (radius + 1)]) {
        radius++;
      }
      radii_[center] = radius;

      size_t right = center + 1;
      size_t maxRadius = radius;
      radius = 0;
      while (right <= center + maxRadius) {
        size_t left = center * 2 - right;
        size_t maxMirroredRadius = center + maxRadius - right;
        if (radii_[left] < maxMirroredRadius) {
          radii_[right++] = radii_[left];
        } else if (radii_[left] > maxMirroredRadius) {
          radii_[right++] = maxMirroredRadius;
        } else {
          radius = maxMirroredRadius;
          break;
        }
      }
      center = right;
    }
    return *max_element(radii_.begin(), radii_.end());
  }

 private:
  static constexpr typename array_t::value_type PADDING = 0;
  array_t s_;
  vector<size_t> radii_;
};


void solve() {
  string s;
  cin >> s;
  
  Manacher manacher(s);
  size_t ans = manacher.solve();
  printf("%lu\n", ans);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
