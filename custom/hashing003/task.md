# HASHING003 — Bản sao sai một ký tự

### Đề bài

Cho văn bản $S$ có độ dài $n$ và mẫu $P$ có độ dài $m$. Cả hai xâu chỉ gồm các chữ cái thường tiếng Anh.

Hãy đếm số vị trí bắt đầu $i$ sao cho đoạn $S[i..i+m-1]$ nằm hoàn toàn trong $S$ và khác $P$ tại **đúng một vị trí**. Những đoạn bằng hoàn toàn với $P$ không được tính. Các lần xuất hiện được phép chồng lấn.

Nếu $m>n$, kết quả là $0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $n,m$.
- Dòng thứ hai chứa xâu $S$.
- Dòng thứ ba chứa xâu $P$.

### Dữ liệu ra

In số vị trí bắt đầu thỏa mãn.

### Ràng buộc

- $1\le n,m\le2\cdot10^5$.
- $|S|=n$; $|P|=m$.
- Hai xâu chỉ gồm các chữ cái từ `a` đến `z`.

### Sample Input 1

```text
7 3
abacaba
aba
```

### Sample Output 1

```text
1
```

### Sample Input 2

```text
4 1
abca
b
```

### Sample Output 2

```text
3
```

### Giải thích

**Ví dụ 1:** Chỉ đoạn `aca` bắt đầu tại vị trí $3$ khác `aba` đúng một ký tự. Hai đoạn `aba` bắt đầu tại $1$ và $5$ không được tính vì không có ký tự nào khác.

**Ví dụ 2:** Các ký tự ở vị trí $1,3,4$ khác `b`, nên có $3$ đoạn hợp lệ.
