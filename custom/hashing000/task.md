# HASHING000 — Thông điệp xuất hiện nhiều lần

### Đề bài

Cho xâu $S$ có độ dài $n$ chỉ gồm các chữ cái thường tiếng Anh và số nguyên $k$.

Hãy tìm độ dài lớn nhất của một xâu không rỗng xuất hiện trong $S$ ít nhất $k$ lần dưới dạng đoạn liên tiếp. Hai lần xuất hiện được phân biệt bởi vị trí bắt đầu và **được phép chồng lấn**.

Nếu không có xâu nào thỏa mãn, kết quả là $0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $n,k$.
- Dòng thứ hai chứa xâu $S$.

### Dữ liệu ra

In một số nguyên là độ dài lớn nhất tìm được, hoặc $0$ nếu không tồn tại.

### Ràng buộc

- $1\le k\le n\le 2\cdot10^5$.
- $|S|=n$; $S$ chỉ gồm các chữ cái từ `a` đến `z`.

### Sample Input 1

```text
6 2
banana
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
3 2
abc
```

### Sample Output 2

```text
0
```

### Giải thích

**Ví dụ 1:** Xâu `ana` xuất hiện tại các vị trí bắt đầu $2$ và $4$. Hai lần xuất hiện có chung vị trí $4$, điều này được phép. Không có xâu dài hơn xuất hiện hai lần.

**Ví dụ 2:** Mỗi ký tự chỉ xuất hiện một lần nên kết quả là $0$.
