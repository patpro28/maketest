# DPSTRING04 — Sơn lại dải đèn

### Đề bài

Một dải đèn có $N$ bóng, được mô tả bởi xâu $S$ chỉ gồm `R`, `G`, `B`. Ba chữ này biểu diễn ba màu khác nhau. Bạn có thể đổi màu bóng thứ $i$ sang một trong hai màu còn lại với chi phí $W_i$; giữ nguyên màu không mất chi phí.

Hãy tìm tổng chi phí nhỏ nhất để hai bóng đèn kề nhau luôn khác màu. Không được xóa hoặc đổi vị trí bóng đèn.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ ký tự.
- Dòng thứ ba chứa $N$ số nguyên $W_1,W_2,\ldots,W_N$.

### Dữ liệu ra

In tổng chi phí nhỏ nhất có thể đạt được.

### Ràng buộc

- $1\le N\le 50000$.
- Mỗi ký tự của $S$ thuộc tập `R`, `G`, `B`.
- $0\le W_i\le10^9$ với mọi $1\le i\le N$.

### Sample Input 1

```text
4
RRRR
8 1 7 2
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
3
RGB
5 6 7
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, đổi màu các bóng $2,4$ sang `G`, được `RGRG`, tốn $1+2=3$. Ở ví dụ 2, dải đèn ban đầu đã thỏa mãn yêu cầu.
