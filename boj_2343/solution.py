N, M = map(int, input().split())
A = list(map(int, input().split()))

high = sum(A)
low = high // M - 1

def check(bucket_size):
    bucket_cnt = 1
    bucket = 0
    for i in A:
        if i > bucket_size:
            return False
        if bucket + i > bucket_size:
            bucket = i
            bucket_cnt += 1
        else:
            bucket += i
    return bucket_cnt <= M
        

while low + 1 < high:
    mid = (low + high) // 2
    if check(mid):
        high = mid
    else:
        low = mid
print(high)
