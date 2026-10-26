# SEGTREE132 — Chia đều ba chặng

### Đề bài

Cho dãy số nguyên không âm $a_1,\ldots,a_N$. Thực hiện các thao tác:

- `1 i x`: gán $a_i=x$.
- `2`: tìm hai vị trí $1\le p<q<N$ sao cho ba đoạn $[1,p]$, $[p+1,q]$, $[q+1,N]$ có tổng bằng nhau.

Nếu có nhiều cách, chọn cặp $(p,q)$ nhỏ nhất theo thứ tự từ điển: ưu tiên $p$ nhỏ nhất, sau đó $q$ nhỏ nhất. Nếu không có cách chia, in `-1 -1`. Cả ba đoạn phải không rỗng.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $a_1,\ldots,a_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in hai số của cặp đáp án trên một dòng; nếu không có cách chia thì in `-1 -1`.

### Ràng buộc

- $3\le N\le200000$; $1\le Q\le200000$.
- $0\le a_i,x\le10^9$; $1\le i\le N$.

### Sample Input 1

```text
6 9
1 0 1 0 1 0
2
1 3 2
2
1 5 3
2
1 1 2
1 5 2
1 6 0
2
```

### Sample Output 1

```text
1 3
-1 -1
-1 -1
1 3
```

### Sample Input 2

```text
4 5
0 0 0 0
2
1 4 3
2
1 4 0
2
```

### Sample Output 2

```text
1 2
-1 -1
1 2
```

### Giải thích

Ở ví dụ 1, ban đầu chọn $(1,3)$. Sau cập nhật thứ nhất, tổng là $4$ nên không chia đều được. Khi tổng bằng $6$ ở truy vấn thứ ba, không có tiền tố tổng bằng $2$ nên vẫn thất bại. Ở truy vấn cuối, dãy là $(2,0,2,0,2,0)$ nên chọn $(1,3)$. Ở ví dụ 2, dãy toàn $0$ có cặp nhỏ nhất là $(1,2)$; nếu chỉ phần tử cuối bằng $3$, không có cách chia hợp lệ.
