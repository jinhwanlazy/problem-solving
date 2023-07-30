input()
x=0
print(sum(x:=min(x+1,v)for v in map(int,input().split()[::-1])))
