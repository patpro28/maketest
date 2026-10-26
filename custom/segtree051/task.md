# SEGTREE051 — Đếm bội số

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$ và một số nguyên dương $K$ cố định. Bạn cần thực hiện lần lượt $Q$ thao tác thuộc hai loại:

- `1 i x`: gán $A_i=x$.
- `2 l r`: đếm số phần tử chia hết cho $K$ trong đoạn $[l,r]$.

Một phần tử là bội của $K$ nếu tồn tại số nguyên $t$ sao cho phần tử đó bằng $tK$. Vì vậy số $0$ và các bội âm cũng được tính. Mỗi vị trí được đếm riêng, kể cả khi các giá trị bằng nhau. Số $K$ không thay đổi; mỗi truy vấn sử dụng dãy sau tất cả thao tác gán trước đó.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,Q,K$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả các phần tử ban đầu của dãy.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa số phần tử chia hết cho $K$ trong đoạn được hỏi. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N,Q\le200000$.
- $-10^9\le A_i,x\le10^9$; $1\le K\le10^9$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le l\le r\le N$.

### Sample Input 1

```text
6 6 3
-6 0 4 9 -2 12
2 1 6
2 2 5
1 3 -3
2 1 3
1 2 5
2 2 4
```

### Sample Output 1

```text
4
2
3
2
```

### Sample Input 2

```text
3 4 1
-1000000000 0 1000000000
2 1 3
1 2 7
2 2 2
2 1 2
```

### Sample Output 2

```text
3
1
2
```

### Giải thích

Ở ví dụ 1, các bội của $3$ ban đầu là $-6,0,9,12$, có $4$ vị trí. Đoạn $[2,5]$ có hai bội là $0,9$. Sau khi gán $A_3=-3$, ba phần tử đầu đều chia hết cho $3$. Khi gán $A_2=5$, đoạn $[2,4]$ có hai bội là $-3,9$.

Ở ví dụ 2, mọi số nguyên đều chia hết cho $K=1$, nên đáp án bằng độ dài đoạn ở mọi thời điểm.
