#include <cstdio>
#include <set>
#include <vector>

int process() {
  int N, K, W;
  scanf("%d %d", &N, &K);
  std::vector<int> required_time(N);
  std::vector<int> start_time(N, -1);
  std::vector<std::vector<int>> dependancies(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &required_time[i]);
  }
  for (int i = 0; i < K; ++i) {
    int X, Y;
    scanf("%d %d", &X, &Y);
    dependancies[--Y].push_back(--X);
  }
  scanf("%d", &W);
  W--;
  auto buildDone = [&](int bid, int current_time) -> bool {
    return start_time[bid] != -1 &&
           start_time[bid] + required_time[bid] <= current_time;
  };
  auto canStart = [&](int bid, int current_time) -> bool {
    for (auto dep : dependancies[bid]) {
      if (!buildDone(dep, current_time)) {
        return false;
      }
    }
    return true;
  };
  std::set<int> events({0});
  while (!events.empty()) {
    auto i = *events.begin();
    events.erase(events.begin());
    if (buildDone(W, i)) {
      printf("%d\n", i);
      return 0;
    }
    for (int bid = 0; bid < N; ++bid) {
      if (start_time[bid] == -1 && canStart(bid, i)) {
        start_time[bid] = i;
        events.insert(i + required_time[bid]);
      }
    }
  }
  return 0;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int i = 0; i < T; ++i) {
    process();
  }
  return 0;
}
