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

int main() {

  string S;
  while (true) {
    cin >> S;
    if (S == ".") {
      break;
    }
    auto pi = kmpPartialMatch(S);

    if (pi.back() != 0 && S.size() % (S.size() - pi.back()) == 0) {
      cout << S.size() / (S.size() - pi.back()) << "\n";
    }
    else {
      cout << "1\n";
    }

  }
  

  return 0;
}
