# SEGTREE080 — Đoạn ngoặc hợp lệ

### Đề bài

Cho xâu $S$ độ dài $N$, chỉ gồm hai ký tự `(` và `)`. Các ký tự được đánh số từ $1$ đến $N$.

Một dãy ngoặc được gọi là **đúng** nếu tổng số ngoặc mở bằng tổng số ngoặc đóng, đồng thời trong mọi tiền tố của dãy, số ngoặc mở không ít hơn số ngoặc đóng.

Bạn cần trả lời $Q$ truy vấn. Với mỗi đoạn $[l,r]$, hãy kiểm tra xâu con $S_lS_{l+1}\ldots S_r$ có phải dãy ngoặc đúng hay không. Chỉ xét các ký tự bên trong đoạn được hỏi; không được thêm, xóa hay đổi thứ tự ký tự. Xâu $S$ được giữ nguyên trong suốt quá trình trả lời truy vấn.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa xâu $S$ gồm đúng $N$ ký tự `(` hoặc `)`.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa hai số nguyên $l,r$, mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa `YES` nếu xâu con được hỏi là dãy ngoặc đúng; ngược lại in `NO`.

### Ràng buộc

- $1\le N\le200000$; $1\le Q\le200000$.
- Xâu $S$ chỉ gồm các ký tự `(` và `)`.
- Với mỗi truy vấn: $1\le l\le r\le N$.

### Sample Input 1

```text
8 5
(()())()
1 8
2 3
3 4
1 5
7 8
```

### Sample Output 1

```text
YES
YES
NO
NO
YES
```

### Sample Input 2

```text
6 4
())(()
1 6
1 2
4 6
5 6
```

### Sample Output 2

```text
NO
YES
NO
YES
```

### Giải thích

Ở ví dụ 1, cả xâu là dãy ngoặc đúng. Hai đoạn $[2,3]$ và $[7,8]$ đều là `()`. Đoạn $[3,4]$ là `)(`, có ngoặc đóng xuất hiện trước ngoặc mở. Đoạn $[1,5]$ còn thiếu một ngoặc đóng nên không đúng.

Ở ví dụ 2, cả xâu có số ngoặc mở bằng số ngoặc đóng nhưng tiền tố `())` có nhiều ngoặc đóng hơn ngoặc mở, nên không phải dãy ngoặc đúng. Đoạn $[4,6]$ là `(()`, còn hai đoạn được trả lời `YES` đều là `()`.
