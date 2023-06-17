ref = {
    "A+": 4.5,
    "A0": 4.0,
    "B+": 3.5,
    "B0": 3.0,
    "C+": 2.5,
    "C0": 2.0,
    "D+": 1.5,
    "D0": 1.0,
    "F": 0.0,
}


score_sum = 0
weight_sum = 0
for _ in range(20):
    name, weight, score = input().split()
    weight = float(weight)
    if score in ref:
        score_sum += ref[score] * weight
        weight_sum += weight
print(f'{score_sum/weight_sum:.6f}')
