### Đề bài

Cho một dãy số nguyên $A$ gồm $N$ phần tử. Bạn cần trả lời lần lượt $Q$ truy vấn sau: *"Tìm phần tử nhỏ thứ $k$ trong đoạn $A[l..r]$."*

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N$ và $Q$.
- Dòng thứ hai chứa $N$ số nguyên, là các phần tử của dãy $A$.
- $Q$ dòng tiếp theo mỗi dòng chứa ba số nguyên $l$, $r$, $k$.

### Dữ liệu ra

- Đối với mỗi truy vấn, in ra giá trị của phần tử nhỏ thứ $k$ trong đoạn $A[l..r]$.

### Giới hạn

- $1 \le N, Q \le 10^5$
- $1 \le A_i \le 10^9$
- $1 \le l \le r \le N$
- $1 \le k \le r - l + 1$

### Sample Input

```
7 3
1 5 2 6 3 7 4
2 5 3
4 4 1
1 7 3
```

### Sample Output

```
5
6
3
```