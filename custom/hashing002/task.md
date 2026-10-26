# HASHING002 — Sao chép không chồng lấn

### Đề bài

Cho xâu $S$ có độ dài $n$, chỉ gồm các chữ cái thường tiếng Anh.

Hãy tìm độ dài lớn nhất $d$ sao cho tồn tại hai đoạn $S[i..i+d-1]$ và $S[j..j+d-1]$ bằng nhau, với $i<j$ và $i+d-1<j$. Hai đoạn phải nằm hoàn toàn trong $S$ và không được có vị trí chung; chúng có thể nằm sát nhau.

Nếu không tồn tại hai đoạn không rỗng như vậy, kết quả là $0$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $n$.
- Dòng thứ hai chứa xâu $S$.

### Dữ liệu ra

In độ dài lớn nhất của hai đoạn thỏa mãn, hoặc $0$ nếu không tồn tại.

### Ràng buộc

- $1\le n\le2\cdot10^5$.
- $|S|=n$; $S$ chỉ gồm các chữ cái từ `a` đến `z`.

### Sample Input 1

```text
5
aaaaa
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
5
abcde
```

### Sample Output 2

```text
0
```

### Giải thích

**Ví dụ 1:** Hai đoạn ở các vị trí $[1,2]$ và $[3,4]$ đều là `aa` và không chồng lấn. Hai đoạn có độ dài $3$ sẽ cần ít nhất $6$ vị trí nên không thể chọn.

**Ví dụ 2:** Không có hai ký tự giống nhau nên không thể chọn hai đoạn không rỗng bằng nhau.
