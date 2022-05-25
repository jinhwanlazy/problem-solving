#include <bits/stdc++.h>
using namespace std;

vector<size_t> kmpPartialMatch(const string& query){
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

vector<size_t> kmp(const string& source, const string& query) {
  size_t n = source.size();
  size_t m = query.size();

  vector<size_t> res;
  vector<size_t> pi = kmpPartialMatch(query);

  size_t begin = 0, matched = 0;
  while (begin <= n - m) {
    if (matched < m && source[begin + matched] == query[matched]) {
      ++matched;
      if (matched == m) {
        res.push_back(begin);
      }
    } else {
      if (matched == 0)
        ++begin;
      else {
        begin += matched - pi[matched - 1];
        matched = pi[matched - 1];
      }
    }
  }
  return res;
}

int main() {
  int N, M;
  scanf("%d %d", &N, &M);

  string S;
  cin >> S;

  stringstream ss;
  for (int i = 0; i < N; ++i) {
    ss << "IO";
  }
  ss << "I";

  auto res = kmp(S, ss.str());
  cout << res.size() << "\n";

  return 0;
}
