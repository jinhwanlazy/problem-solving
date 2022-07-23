# [BOJ 5977](https://www.acmicpc.net/problem/5977)

점화식은

$$
X_i = \max_{ i-K \le j \le i }{ S_i - S_{j} + X_{j-1} }
$$

where 

$$
\begin{align}
  X_i &= [1, i] \text{ 구간에서의 최대합} \\
  S_i &= \sum_{j=1}^{i}{e_j}
\end{align}
$$

이걸 naive하게 계산하려고 하면 $O(N^2)$.

$S_i$는 $j$에 의존하지 않기 때문에 따로 빼 내면

$$
X_i = S_i + \max_{ i-K \le j \le i }{ X_{j-1} - S_{j} }
$$

위 식의 뒷부분은 Monotone queue technique을 사용하면 $O(N)$에 구할 수 있다.
