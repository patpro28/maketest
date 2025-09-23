n, i=abs(int(input())), 0
while n>0 or n&1:
    i+=1; n-=i
print(i)