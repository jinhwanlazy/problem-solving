import sys
input = sys.stdin.readline

from bisect import bisect
from dataclasses import dataclass

@dataclass
class Line:
    slope: int
    y_intercept: int
    x_intersection: float

    def eval(self, x):
        return self.slope * x + self.y_intercept

    def intersection(self, other):
        return -(self.y_intercept - other.y_intercept) / (self.slope - other.slope)

N = int(input())
A = list(map(int, input().split()))
B = list(map(int, input().split()))

dp = [0] * N
lines = [Line(B[0], 0, 0.0)]
for i in range(1, N):
    j = bisect(lines, A[i], key=lambda line: line.x_intersection)
    dp[i] = lines[j-1].eval(A[i])

    new_line = Line(B[i], dp[i], 0.0)
    while lines:
        new_line.x_intersection = new_line.intersection(lines[-1])
        if new_line.x_intersection < lines[-1].x_intersection:
            lines.pop()
        else:
            break
    lines.append(new_line)
        
print(dp[-1])
