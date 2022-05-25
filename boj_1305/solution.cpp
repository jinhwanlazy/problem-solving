#include <bits/stdc++.h>
#include <random>
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
  
  string s;
  cin >> s;

  auto pi = kmpPartialMatch(s);
  cout << N - pi.back() << "\n";

  return 0;
}
