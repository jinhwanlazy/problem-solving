#include <bits/stdc++.h>
using namespace std;

constexpr static int DI[4] = {0, 1, 0, -1};
constexpr static int DJ[4] = {1, 0, -1, 0};

class Board {
  int N_;
  vector<vector<int>> board_;
  unordered_set<int> mergeFlags_;

  
 public:
  Board(int N) : N_(N), board_(N, vector<int>(N, 0)) {}

  void sweep(int direction) {
    switch (direction) {
      case 0: sweepRight(); break;
      case 1: sweepDown(); break;
      case 2: sweepLeft(); break;
      case 3: sweepUp(); break;
    }
  }

  void sweepRight() {
    clearMergeFlags();
    for (int j = N_-1; j >= 0; --j) {
      for (int i = 0; i < N_; ++i) {
        move(i, j, DI[0], DJ[0]);
      }
    }
  }
  
  void sweepDown() {
    clearMergeFlags();
    for (int i = N_-1; i >= 0; --i) {
      for (int j = 0; j < N_; ++j) {
        move(i, j, DI[1], DJ[1]);
      }
    }
  }

  void sweepLeft() {
    clearMergeFlags();
    for (int j = 0; j < N_; ++j) {
      for (int i = 0; i < N_; ++i) {
        move(i, j, DI[2], DJ[2]);
      }
    }
  }

  void sweepUp() {
    clearMergeFlags();
    for (int i = 0; i < N_; ++i) {
      for (int j = 0; j < N_; ++j) {
        move(i, j, DI[3], DJ[3]);
      }
    }
  }

  void move(int i, int j, int di, int dj) {
    while (true) {
      int ii = i + di;
      int jj = j + dj;
      if (!(0 <= ii && ii < N_ && 0 <= jj && jj < N_)) {
        break;
      }

      if (empty(ii, jj)) {
        board_[ii][jj] = board_[i][j];
        board_[i][j] = 0;
        i = ii;
        j = jj;
        continue;
      }
      else if (board_[i][j] == board_[ii][jj] && !merged(ii, jj)) {
        board_[ii][jj] *= 2;
        board_[i][j] = 0;
        setMerged(ii, jj);
        break;
      } else {
        break;
      }
    }
  }

  int maxValue() const {
    int res = 0;
    for (int i = 0; i < N_; ++i) {
      for (int j = 0; j < N_; ++j) {
        res = max(res, board_[i][j]);
      }
    }
    return res;
  }
  
 private:
  bool empty(int i, int j) const {
    return board_[i][j] == 0;
  }
  
  bool merged(int i, int j) const {
    return mergeFlags_.find(i * N_ + j) != mergeFlags_.end();
  }
  
  void setMerged(int i, int j) {
    mergeFlags_.insert(i * N_ + j);
  }

  void clearMergeFlags() {
    mergeFlags_.clear();
  }

public:
  friend istream& operator>>(istream& istr, Board& b) {
    for (int i = 0; i < b.N_; ++i) {
      for (int j = 0; j < b.N_; ++j) {
        cin >> b.board_[i][j];
      }
    }
    return istr;
  };

  friend ostream& operator<<(ostream& ostr, Board& b) {
    for (int i = 0; i < b.N_; ++i) {
      for (int j = 0; j < b.N_; ++j) {
        cout << b.board_[i][j] << " ";
      }
      cout << "\n";
    }
    return ostr;
  };
  
};

void solve() {
  int N;
  cin >> N;

  Board b(N);
  cin >> b;

  int ans = 0;
  stack<pair<Board, int>> Q;
  Q.push({b, 0});
  while (!Q.empty()) {
    auto [b, depth] = Q.top();
    Q.pop();

    ans = max(ans, b.maxValue());
    if (depth == 5) {
      continue;
    }

    for (int i = 0; i < 4; ++i) {
      Board tmp = b;
      tmp.sweep(i);
      Q.push({tmp, depth+1});
    }
  }
  cout << ans;
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
