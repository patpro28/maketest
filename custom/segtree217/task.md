# SEGTREE217 — Tuyến lấy mẫu cách đều

### Đề bài

Cho dãy $A_1,\dots,A_N$ và bước nhảy cố định $K$. Tuyến từ $L$ đến $R$ gồm các vị trí $L,L+K,L+2K,\dots$ không vượt quá $R$. Tuyến luôn chứa $L$. Vị trí $R$ thuộc tuyến khi $R-L$ chia hết cho $K$.

Thực hiện $Q$ thao tác theo thứ tự đầu vào.

- `1 L R X`. Cộng $X$ vào từng phần tử trên tuyến từ $L$ đến $R$.
- `2 L R`. In tổng các phần tử hiện tại trên tuyến từ $L$ đến $R$.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,Q,K$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,\dots,A_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác theo định dạng trên.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in kết quả trên một dòng. Các kết quả xuất hiện theo thứ tự thao tác.

### Ràng buộc

- $1\le N,Q\le200000$.
- $1\le L\le R\le N$ với mỗi thao tác.
- $|A_i|,|X|\le10^8$ ở đầu vào.
- $1\le K\le N$.

### Sample Input 1

```text
8 5 3
1 2 3 4 5 6 7 8
2 2 8
1 1 6 10
2 1 8
2 2 7
2 4 6
```

### Sample Output 1

```text
15
32
7
14
```

### Sample Input 2

```text
4 3 4
4 3 2 1
1 2 4 -5
2 2 4
2 1 4
```

### Sample Output 2

```text
-2
4
```

### Giải thích

Ở ví dụ 1, tuyến đầu gồm $2,5,8$, có tổng $15$. Cập nhật tác động tại $1,4$. Tuyến tiếp theo gồm $1,4,7$, có tổng $11+14+7=32$. Hai tuyến cuối gồm $2,5$ và chỉ vị trí $4$.

Ở ví dụ 2, bước nhảy bằng $4$ nên mỗi tuyến chỉ có vị trí đầu. Chỉ phần tử ở vị trí $2$ được cộng $-5$.
