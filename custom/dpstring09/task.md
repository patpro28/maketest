# DPSTRING09 — Bốn màu cách biệt

### Đề bài

Cho xâu $S$ dài $N$ chỉ gồm `A`, `B`, `C`, `D`, biểu diễn màu của một dải ô. Bạn có thể đổi màu ô thứ $i$ sang một trong ba màu khác với chi phí $W_i$; giữ nguyên màu không mất chi phí.

Sau khi đổi màu, mọi cặp vị trí cách nhau một hoặc hai đơn vị phải có màu khác nhau. Cụ thể, với xâu kết quả $T$, cần có $T_i\ne T_{i-1}$ khi $i\ge2$ và $T_i\ne T_{i-2}$ khi $i\ge3$.

Hãy tìm tổng chi phí nhỏ nhất. Không được xóa hoặc đổi vị trí các ô.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ ký tự.
- Dòng thứ ba chứa $N$ số nguyên $W_1,W_2,\ldots,W_N$.

### Dữ liệu ra

In tổng chi phí nhỏ nhất có thể đạt được.

### Ràng buộc

- $1\le N\le 10000$.
- Mỗi ký tự của $S$ thuộc tập `A`, `B`, `C`, `D`.
- $0\le W_i\le10^9$ với mọi $1\le i\le N$.

### Sample Input 1

```text
4
AAAA
7 1 2 8
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
4
ABCA
9 8 7 6
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, đổi ô $2$ thành `B`, ô $3$ thành `C`, được `ABCA`, tốn $1+2=3$. Ở ví dụ 2, `ABCA` đã hợp lệ: hai chữ `A` cách nhau ba vị trí nên được phép giống nhau.
