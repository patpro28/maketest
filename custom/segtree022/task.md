# SEGTREE022 — Hai vận động viên mạnh nhất

### Đề bài

Có $N$ vận động viên được đánh số từ $1$ đến $N$. Năng lực của người thứ $i$ là số nguyên $A_i$ và có thể âm.

Bạn cần thực hiện lần lượt $Q$ thao tác thuộc hai loại:

- `1 i x`: sửa năng lực của vận động viên $i$ thành $x$.
- `2 l r`: chọn đúng hai vận động viên ở hai vị trí khác nhau trong đoạn $[l,r]$ sao cho tổng năng lực của họ lớn nhất, rồi in tổng đó.

Mọi đoạn truy vấn có ít nhất hai người. Hai người có năng lực bằng nhau vẫn là hai người riêng biệt và có thể được chọn cùng nhau. Mỗi truy vấn sử dụng năng lực sau tất cả thao tác sửa trước đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả năng lực ban đầu của các vận động viên.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa tổng năng lực lớn nhất của đúng hai người khác nhau trong đoạn được hỏi. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $2\le N\le200000$; $1\le Q\le200000$.
- $-10^9\le A_i,x\le10^9$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le l<r\le N$.

### Sample Input 1

```text
5 6
5 9 9 -2 7
2 1 5
2 2 3
1 2 -4
2 1 3
1 3 -8
2 2 4
```

### Sample Output 1

```text
18
18
14
-6
```

### Sample Input 2

```text
2 4
-1000000000 -1000000000
2 1 2
1 1 1000000000
2 1 2
2 1 2
```

### Sample Output 2

```text
-2000000000
0
0
```

### Giải thích

Ở ví dụ 1, hai người thứ $2,3$ đều có năng lực $9$ và được chọn cùng nhau, nên hai truy vấn đầu có đáp án $18$. Sau khi sửa năng lực người thứ $2$ thành $-4$, đoạn $[1,3]$ chọn hai giá trị $5,9$, tổng bằng $14$. Sau lần sửa tiếp theo, đoạn $[2,4]$ có các giá trị $-4,-8,-2$, nên tổng tốt nhất là $-4+(-2)=-6$.

Ở ví dụ 2, mỗi truy vấn đều phải chọn cả hai người. Không được bỏ chọn người chỉ vì năng lực âm.
