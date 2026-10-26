# HASHING005 — Mật khẩu chung của nhiều người

### Đề bài

Cho $k$ xâu $S_1,S_2,\ldots,S_k$, chỉ gồm các chữ cái thường tiếng Anh.

Hãy tìm độ dài lớn nhất của một xâu không rỗng xuất hiện dưới dạng đoạn liên tiếp trong **tất cả** $k$ xâu. Nếu không có xâu nào như vậy, kết quả là $0$.

Các xâu trong danh sách có thể giống nhau. Khi $k=1$, cả xâu duy nhất cũng là một đoạn hợp lệ.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $k$.
- Trong $k$ dòng tiếp theo, dòng thứ $i$ chứa xâu $S_i$.

### Dữ liệu ra

In độ dài lớn nhất của một xâu con chung liên tiếp, hoặc $0$ nếu không tồn tại.

### Ràng buộc

- $1\le k\le2\cdot10^5$.
- $1\le |S_i|$ với mọi $i$.
- $\sum_{i=1}^{k}|S_i|\le2\cdot10^5$.
- Các xâu chỉ gồm các chữ cái từ `a` đến `z`.

### Sample Input 1

```text
3
banana
ananas
bandana
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
2
abc
def
```

### Sample Output 2

```text
0
```

### Giải thích

**Ví dụ 1:** Xâu `ana` xuất hiện trong cả ba xâu. Không có xâu chung liên tiếp nào dài hơn $3$.

**Ví dụ 2:** Hai xâu không có ký tự chung nên kết quả là $0$.
