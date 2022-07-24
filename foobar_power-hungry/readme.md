# [Foobar - Power Hungry](https://foobar.withgoogle.com/)
<!--tags: dp-->

배열의 non-empty subset의 product중 최대값을 찾는 문제.

Brute force 로 답을 찾는다면 $O(2^N)$ 로 시간초과가 날 것이다.

$a_i$ 를 구간 [0-i] 의 non-empty subset product의 최대값, 
$b_i$ 를 동일 구간의 non-empty subset product의 최소값이라고 하면 점화식을
다음과 같이 나타낼 수 있다.

$$
a_i = 
\begin{cases*}
    a_{i-1} x_i & if $x_i > 0$ \\
    b_{i-1} x_i & if $x_i < 0$ \\
    \max{ \left( a_i, x_i \right) } & if $x_i = 0$
\end{cases*}
$$

Loop를 돌면서 $a_i$, 와 $b_i$만 갱신해 나가면 $O(N)$에 답을 구할 수 있다.
