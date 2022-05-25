#include <bits/stdc++.h>
using namespace std;

vector<size_t> kmpPartialMatch(const vector<int>& query){
    size_t m = query.size();
    vector<size_t> pi(m, 0);

    size_t begin = 1, matched = 0;
    
    while(begin + matched < m){
        if(query[begin + matched] == query[matched]){
            matched++;
            pi[begin + matched - 1] = matched;
        }
        else{
            if(matched == 0)
                begin++;
            else{
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }
    return pi;
}

vector<size_t> kmp(const vector<int>& source, const vector<int>& query) {
  size_t n = source.size();
  size_t m = query.size();

  vector<size_t> res;
  vector<size_t> pi = kmpPartialMatch(query);

  size_t matched = 0;
  for (int i = 0; i < n; i++)
  {
    while (matched > 0 && source[i] != query[matched]) {
      matched = pi[matched - 1];
    }
    if (source[i] == query[matched])
    {
      matched++;
      if (matched == m)
      {
        res.push_back(i - m + 1);
        matched = pi[matched - 1];
      }
    }
  }

  return res;
}


int main() {
  int N;
  scanf("%d", &N);

  vector<int> A(N), B(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
  }
  for (int i = 0; i < N; ++i) {
    scanf("%d", &B[i]);
  }
  sort(A.begin(), A.end());
  sort(B.begin(), B.end());

  vector<int> A_diffs(N), B_diffs(N);
  for (int i = 0; i < N-1; ++i) {
    A_diffs[i] = A[i+1] - A[i];
    B_diffs[i] = B[i+1] - B[i];
  }
  A_diffs[N-1] = A[0] + 360000 - A[N-1];
  B_diffs[N-1] = B[0] + 360000 - B[N-1];
  for (int i = 0; i < N; ++i) {
    A_diffs.push_back(A_diffs[i]);
  }

  auto res = kmp(A_diffs, B_diffs);
  if (res.empty()) {
    cout << "impossible\n";
  }
  else {
    cout << "possible\n";
  }
  return 0;
}
