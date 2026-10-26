# DPSTRING00 — Xóa chữ trùng nhau

### Đề bài

Cho xâu $S$ chỉ gồm hai chữ cái `a` và `b`. Bạn được xóa một số ký tự, có thể không xóa ký tự nào. Các ký tự còn lại giữ nguyên thứ tự ban đầu.

Hãy tìm số ký tự ít nhất cần xóa để hai ký tự liên tiếp bất kỳ trong xâu còn lại luôn khác nhau. Xâu có không quá một ký tự cũng thỏa mãn điều kiện.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ ký tự.

### Dữ liệu ra

In số ký tự ít nhất cần xóa.

### Ràng buộc

- $1\le N\le 50000$.
- Mỗi ký tự của $S$ thuộc tập `a`, `b`.

### Sample Input 1

```text
6
aaabba
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
4
abab
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, giữ lại các ký tự tại vị trí $1,4,6$ được xâu `aba`, cần xóa $3$ ký tự. Mỗi nhóm ký tự giống nhau liên tiếp chỉ giữ được tối đa một ký tự, nên không thể xóa ít hơn. Ở ví dụ 2, xâu ban đầu đã hợp lệ.
