# SEGTREE004 — Chia thanh gỗ

### Đề bài

Có $N$ thanh gỗ được đánh số từ $1$ đến $N$. Thanh thứ $i$ có độ dài nguyên $A_i$.

Với mỗi truy vấn $[l,r]$, bạn muốn cắt **từng thanh riêng biệt** từ thanh $l$ đến thanh $r$ thành các khúc có cùng độ dài nguyên dương $d$. Phải dùng hết mỗi thanh, không được nối gỗ từ các thanh khác nhau. Hãy tìm độ dài $d$ lớn nhất có thể chọn.

Bạn cần trả lời $Q$ truy vấn độc lập. Độ dài các thanh không thay đổi; truy vấn chỉ yêu cầu tính kết quả và không thực hiện việc cắt gỗ.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả độ dài các thanh gỗ.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa hai số nguyên $l,r$, mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa độ dài nguyên lớn nhất có thể chọn cho mỗi khúc gỗ.

### Ràng buộc

- $1\le N,Q\le200000$.
- $1\le A_i\le10^9$.
- Với mỗi truy vấn: $1\le l\le r\le N$.

### Sample Input 1

```text
5 4
12 18 24 7 21
1 3
4 5
2 4
3 3
```

### Sample Output 1

```text
6
7
1
24
```

### Sample Input 2

```text
3 3
1000000000 1000000000 1
1 2
1 3
3 3
```

### Sample Output 2

```text
1000000000
1
1
```

### Giải thích

Ở ví dụ 1, ba thanh đầu có thể cắt thành các khúc dài $6$, vì $6$ cùng chia hết các độ dài $12,18,24$, và không có độ dài lớn hơn thỏa mãn. Hai thanh cuối có thể cắt thành các khúc dài $7$. Các độ dài $18,24,7$ chỉ có ước chung dương lớn nhất là $1$. Truy vấn một thanh cho phép lấy toàn bộ thanh làm một khúc.

Ở ví dụ 2, hai thanh đầu đều dài $10^9$ nên có thể chọn khúc dài $10^9$. Khi xét thêm thanh dài $1$, độ dài khúc lớn nhất chỉ còn $1$.
