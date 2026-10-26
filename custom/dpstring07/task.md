# DPSTRING07 — Ghép cặp khác chữ

### Đề bài

Cho xâu $S$ chỉ gồm `a` và `b`, gồm $N$ ký tự. Ký tự ở vị trí $i$ có điểm $W_i$.

Bạn chọn một dãy con $T$ có độ dài chẵn. Chia $T$ thành các cặp không giao nhau $(T_1,T_2),(T_3,T_4),\ldots$. Trong mỗi cặp, hai ký tự phải khác nhau. Không có điều kiện giữa hai ký tự thuộc hai cặp khác nhau.

Hãy tìm tổng điểm lớn nhất của các vị trí được chọn. Được phép chọn dãy rỗng, có điểm bằng $0$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ ký tự.
- Dòng thứ ba chứa $N$ số nguyên $W_1,W_2,\ldots,W_N$.

### Dữ liệu ra

In tổng điểm lớn nhất có thể đạt được.

### Ràng buộc

- $1\le N\le 50000$.
- Mỗi ký tự của $S$ thuộc tập `a`, `b`.
- $0\le W_i\le10^9$ với mọi $1\le i\le N$.

### Sample Input 1

```text
5
aabba
10 1 2 9 8
```

### Sample Output 1

```text
29
```

### Sample Input 2

```text
3
aaa
4 5 6
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, chọn các vị trí $1,3,4,5$, được `abba`, chia thành `ab` và `ba`, tổng điểm $10+2+9+8=29$. Hai chữ `b` ở giữa thuộc hai cặp khác nhau nên được phép đứng cạnh nhau. Ở ví dụ 2, không tạo được cặp khác chữ nào, nên chỉ chọn dãy rỗng.
