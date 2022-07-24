# [BOJ15678 - 연세워터파크](https://www.acmicpc.net/problem/15678)
<!--tags: deque, deque dp, dp, ds, priority queue, segtree-->

항상 징검다리 번호가 증가하는 방향으로 움직이는 것으로 생각해도 상관 없음.
$x_i$ 를 i번째 징검다리를 밟았을 때 [1, i]구간에서 얻을 수 있는 점수의
최대값이라고 하면 점화식은

$$
    x_i = \max{\left( K_i, \max_{i-D \le j < i}{K_i + x_j} \right)}
$$

$D$가 최대 $N$이므로 naive한 solution은 $O(N^2)$. 

위 식의 $\max_{i-D \le j < i}{x_j}$ 부분만 따로 떼서 생각하면, 이것은 monotone
queue technique을 사용해 $O(N)$에 구할 수 있다.
