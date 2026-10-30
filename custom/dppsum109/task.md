# PREFIX09 — Trạm xuất phát trên vòng tròn

### Đề bài

Có $N$ trạm trên một vòng tròn, đánh số từ $1$ đến $N$ theo chiều di chuyển. Sau trạm $N$ là trạm $1$. Khi đến trạm $i$, xe nhận $A_i$ đơn vị nhiên liệu rồi cần tiêu tốn $B_i$ đơn vị nhiên liệu để đi đến trạm tiếp theo.

Xe có bình chứa không giới hạn và bắt đầu với bình rỗng tại một trạm do bạn chọn. Xe nhận nhiên liệu tại trạm xuất phát trước khi đi. Mỗi trạm chỉ cấp nhiên liệu một lần trong chuyến đi; chuyến đi kết thúc ngay khi xe trở lại trạm xuất phát sau đúng $N$ chặng. Nhiên liệu luôn phải không âm.

Hãy tìm tất cả trạm xuất phát cho phép xe đi đủ một vòng, theo thứ tự chỉ số tăng dần.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $A_i,B_i$.

### Dữ liệu ra

Dòng đầu in số trạm xuất phát hợp lệ. Dòng thứ hai in các chỉ số trạm đó theo thứ tự tăng dần, cách nhau bởi dấu cách. Nếu không có trạm hợp lệ, dòng thứ hai để trống.

### Ràng buộc

- $1\le N\le200000$.
- $0\le A_i,B_i\le10^9$.

### Sample Input 1

```text
3
1 2
3 1
1 2
```

### Sample Output 1

```text
1
2
```

### Sample Input 2

```text
2
0 1
1 1
```

### Sample Output 2

```text
0

```

### Giải thích

Ở ví dụ 1, xuất phát từ trạm $2$, lượng nhiên liệu sau ba chặng lần lượt là $2,1,0$. Hai trạm còn lại đều thiếu nhiên liệu ở một chặng. Ở ví dụ 2, tổng nhiên liệu nhận là $1$, nhỏ hơn tổng nhiên liệu cần là $2$, nên không có trạm hợp lệ.
