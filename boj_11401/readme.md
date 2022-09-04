# [BOJ11401 - 이항 계수 3](https://www.acmicpc.net/problem/11401)
<!--tags: combinatorics, exponentiation by squaring, fermat's little thm, math, modular multiplicative inverse, number theory-->

$$
\binom{n}{k} = \frac{n!}{k!(n-k)!} 
$$

위 공식을 단순하게 적용하면 $O(N)$ 에 답을 구할 수 있을텐데, 
문제는 나눗셈에는 Modular 분배법칙이 성립하지 않는 다는 것이다.

여기서 필요한 것이 *페르마의 소정리*.

$$
B^{P - 1} \equiv 1 \mod P
$$

위 식을 적절히 변형하면
$$
B B^{P-2} \equiv 1 \mod P \\
B^{P-2} \equiv B^{-1} \mod P
$$

이것을 첫번째 식에 적용하면

$$
{n \choose k} &\equiv \prod_{i=k+1}^{n}i \(n-k\)!^{-1} \mod P \\
              &\equiv \prod_{i=k+1}^{n}i \(n-k\)!^{P-2} \mod P
$$

이 된다. 
