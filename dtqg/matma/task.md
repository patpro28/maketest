# MATMA — Thông điệp có thưởng và phạt

### Đề bài

Bạn cần tạo một xâu $T$ có đúng $L$ ký tự trên bảng chữ cái gồm ba chữ `a`, `b`, `c`.

Có $M$ mẫu xâu. Mẫu thứ $i$ là xâu không rỗng $S_i$, có điểm nguyên $W_i$, có thể âm. Mỗi lần $S_i$ xuất hiện như một xâu con liên tiếp của $T$, bạn nhận thêm $W_i$ điểm.

Tính mọi lần xuất hiện, kể cả các lần chồng lấn. Nếu nhiều mẫu cùng xuất hiện tại một vị trí, tính điểm của từng mẫu. Các mẫu được phép trùng nhau; khi đó mỗi mẫu vẫn được tính điểm độc lập.

Nói cách khác, nếu $\operatorname{occ}(S_i,T)$ là số vị trí bắt đầu một lần xuất hiện của $S_i$ trong $T$, tổng điểm là

$$\sum_{i=1}^{M}W_i\operatorname{occ}(S_i,T).$$

Hãy tìm tổng điểm lớn nhất có thể đạt được. Bạn phải tạo xâu có đúng $L$ ký tự, kể cả khi mọi lựa chọn đều cho điểm âm.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $M,L$.
- Trong $M$ dòng tiếp theo, dòng thứ $i$ chứa xâu $S_i$ và số nguyên $W_i$, cách nhau một dấu cách.

### Dữ liệu ra

In tổng điểm lớn nhất có thể đạt được.

### Ràng buộc

- $1\le M\le20$; $1\le L\le10^{12}$.
- Mỗi $S_i$ chỉ gồm các chữ `a`, `b`, `c` và có độ dài ít nhất $1$.
- $\sum_{i=1}^{M}|S_i|\le80$.
- $-1000\le W_i\le1000$.
- Kết quả có thể âm hoặc vượt phạm vi số nguyên $32$ bit; dùng số nguyên có dấu $64$ bit.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 30% | $L\le10$ |
| 2 | 30% | $L\le10^5$ |
| 3 | 40% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
3 3
a 2
aa 3
ba -4
```

### Sample Output 1

```text
12
```

### Sample Input 2

```text
3 4
a -1
b -2
c -3
```

### Sample Output 2

```text
-4
```

### Sample Input 3

```text
3 2
a 3
a -1
ba 4
```

### Sample Output 3

```text
6
```

### Giải thích

Ở ví dụ 1, chọn `aaa`: mẫu `a` xuất hiện $3$ lần, mẫu `aa` xuất hiện $2$ lần chồng lấn, mẫu `ba` không xuất hiện. Tổng điểm là $3\cdot2+2\cdot3=12$.

Ở ví dụ 2, mọi ký tự đều bị phạt. Chọn `aaaa` để nhận tổng điểm lớn nhất là $-4$; không được chọn xâu rỗng.

Ở ví dụ 3, chọn `ba`. Hai mẫu `a` đóng góp lần lượt $3$ và $-1$ điểm; mẫu `ba` đóng góp $4$ điểm, tổng bằng $6$.
