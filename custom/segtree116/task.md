# SEGTREE116 — Lịch hẹn bị chồng

### Đề bài

Có $N$ cuộc hẹn được đánh số từ $1$ đến $N$. Cuộc hẹn thứ $i$ bắt đầu ở thời điểm $s_i$ và kết thúc ở thời điểm $e_i$, với $s_i\le e_i$. Các thời điểm bắt đầu cố định và thỏa mãn $s_1<s_2<\dots<s_N$.

Một cặp cuộc hẹn liên tiếp $i,i+1$ bị chồng nếu $e_i>s_{i+1}$. Nếu $e_i=s_{i+1}$ thì cặp đó không bị chồng.

Thực hiện $Q$ thao tác thuộc hai loại:

- `1 i x`: thay thời điểm kết thúc $e_i$ bằng $x$; luôn có $x\ge s_i$.
- `2`: tìm chỉ số nhỏ nhất $i$ trong $[1,N-1]$ sao cho cặp $i,i+1$ bị chồng. Nếu không có, trả lời $-1$.

Chỉ xét các cặp liên tiếp theo thứ tự đánh số, kể cả khi một cuộc hẹn kéo dài qua nhiều cuộc hẹn khác.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $s_1,s_2,\dots,s_N$.
- Dòng thứ ba chứa $N$ số nguyên $e_1,e_2,\dots,e_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo định dạng trên.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in một số nguyên trên một dòng: chỉ số nhỏ nhất của cặp bị chồng, hoặc $-1$ nếu không có.

### Ràng buộc

- $1\le N,Q\le2\cdot10^5$.
- $1\le s_1<s_2<\dots<s_N\le10^9$.
- $s_i\le e_i\le10^9$.
- Với thao tác loại `1`: $1\le i\le N$ và $s_i\le x\le10^9$.

### Sample Input 1

```text
4 7
1 4 7 10
4 8 10 12
2
1 2 7
2
1 1 5
2
1 4 100
2
```

### Sample Output 1

```text
2
-1
1
1
```

### Sample Input 2

```text
1 4
5
5
2
1 1 1000000000
2
2
```

### Sample Output 2

```text
-1
-1
-1
```

### Giải thích

Ở ví dụ 1, ban đầu chỉ cặp $2,3$ bị chồng vì $8>7$, nên câu trả lời đầu tiên là $2$. Sau khi đặt $e_2=7$, không còn cặp nào bị chồng. Khi đặt $e_1=5$, cặp $1,2$ bị chồng, nên hai câu trả lời còn lại đều là $1$; thay đổi $e_4$ không tạo cặp liên tiếp mới.

Ở ví dụ 2, chỉ có một cuộc hẹn nên mọi truy vấn đều trả lời $-1$.
