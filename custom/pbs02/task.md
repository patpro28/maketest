### Đề bài

Cho một dãy số nguyên $A$ gồm $N$ phần tử. Bạn cần trả lời lần lượt $Q$ truy vấn sau: *"Tìm phần tử trung vị trong đoạn $A[l..r]$."*

**Trung vị** của một dãy số $n$ phần tử là phần tử thứ $\lfloor \frac{n + 1}{2} \rfloor$ sau khi sắp xếp dãy đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N$ và $Q$.
- Dòng thứ hai chứa $N$ số nguyên, là các phần tử của dãy $A$.
- $Q$ dòng tiếp theo mỗi dòng chứa hai số nguyên $l$, $r$.

### Dữ liệu ra

- Đối với mỗi truy vấn, in ra giá trị của phần tử trung vị trong đoạn $A[l..r]$.

### Giới hạn

- $1 \le N, Q \le 10^5$
- $1 \le A_i \le 10^9$
- $1 \le l \le r \le N$

### Sample Input

```
8 5
2 8 4 16 5 2 10 6
1 3
2 5
6 8
5 8
1 8
```

### Sample Output

```
4
5
6
5
5
```