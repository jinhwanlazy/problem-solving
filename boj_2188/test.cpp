// Algorithm Analysis
// 이분 매칭 알고리즘 (Bipartite Matching)

#include <iostream>
#include <vector>
#define MAX 101

using namespace std;
vector<int> vtx[MAX];      // 정점 vtx
vector<int> slt(MAX, -1);  // vtx가 점유하고 있는 정점
bool done[MAX];            // 처리 여부
int n = 5;                 // 정점 수, 간선 수

bool dfs(int x) {
  // 연결된 모든 정점에 대해 들어갈 수 있는 지 시도
  if (done[x])
    return false;
  done[x] = true;
  for (int i = 0; i < vtx[x].size(); i++) {
    int p = vtx[x][i];
    // 이미 처리한 정점은 고려하지 않음
    // 비어있거나 점유 정점에 더 들어갈 공간이 있는 경우
    if (slt[p] == -1 || dfs(slt[p])) {
      cout << x << " - " << p << "\n";
      slt[p] = x;
      return true;
    }
  }
  return false;
}

int main() {
  vtx[0].push_back(0);
  vtx[0].push_back(1);
  vtx[0].push_back(2);
  vtx[1].push_back(0);
  vtx[2].push_back(1);

  int cnt = 0;  // 매칭 수
  for (int i = 0; i < n; i++) {
    fill(done, done + MAX, false);
    if (dfs(i))
      cnt++;
  }
  printf("%매칭 %d번 성공\n", cnt);
  for (int i = 0; i < MAX; i++) {
    if (slt[i] != -1) {
      printf("%d => %d\n", slt[i], i);
    }
  }
}
