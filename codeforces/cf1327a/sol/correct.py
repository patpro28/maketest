import sys
import math
from sys import stdin, stdout
 
 
# TAKE INPUT
def get_ints_in_variables():
    return map(int, sys.stdin.readline().strip().split())
def get_int(): return int(input())
def get_ints_in_list(): return list(
    map(int, sys.stdin.readline().strip().split()))
def get_list_of_list(n): return [list(
    map(int, sys.stdin.readline().strip().split())) for _ in range(n)]
def get_string(): return sys.stdin.readline().strip()
 
def main():
    # Write Your Code Here
    for t in range(get_int()):
        n, k = get_ints_in_variables()
        if k*k > n:
            print("NO")
        elif n % 2 != k % 2:
            print("NO")
        else:
            print("YES")
            
# for printing format
# print("Case #{}: {}".format(t+1, ans))
#  calling main Function
if __name__ == "__main__":
    main()