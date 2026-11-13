# DPALL0000 — Qua cầu gỗ

### Đề bài

Cây cầu có $N$ tấm ván đánh số từ $1$ đến $N$. Bạn bắt đầu ở vị trí $0$, ngay trước tấm ván đầu tiên. Mỗi bước đưa bạn từ vị trí hiện tại tiến thêm đúng $1$ hoặc $2$ vị trí, nhưng không được vượt quá $N$.

Mỗi lần đặt chân lên tấm ván $i$, bạn phải trả phí $A_i$. Hãy tìm tổng phí nhỏ nhất để đến tấm ván $N$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In tổng phí nhỏ nhất.

### Ràng buộc

- $1\le N\le 2\cdot 10^5$.
- $0\le A_i\le 10^9$.

### Sample Input 1

```text
5
3 2 4 6 1
```

### Sample Output 1

```text
7
```

### Sample Input 2

```text
2
9 4
```

### Sample Output 2

```text
4
```

### Giải thích

- Ví dụ 1. Đi qua các vị trí $0,2,3,5$ với tổng phí $2+4+1=7$.
- Ví dụ 2. Bước thẳng từ vị trí $0$ đến tấm ván $2$ và trả phí $4$.
