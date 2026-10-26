# HASHING004 — So sánh từ điển các đoạn

### Đề bài

Cho xâu $S$ có độ dài $n$ và $q$ truy vấn. Mỗi truy vấn gồm bốn chỉ số $l_1,r_1,l_2,r_2$, yêu cầu so sánh hai đoạn $A=S[l_1..r_1]$ và $B=S[l_2..r_2]$ theo thứ tự từ điển.

Nếu có vị trí khác nhau đầu tiên, xâu có ký tự nhỏ hơn tại vị trí đó đứng trước. Nếu một xâu là tiền tố của xâu kia thì xâu ngắn hơn đứng trước. Hai xâu có cùng độ dài và cùng mọi ký tự được xem là bằng nhau.

Các chữ cái có thứ tự `a` < `b` < ... < `z`. Các đoạn có thể chồng lấn.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $n,q$.
- Dòng thứ hai chứa xâu $S$.
- Trong $q$ dòng tiếp theo, mỗi dòng chứa bốn số nguyên $l_1,r_1,l_2,r_2$ mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in trên một dòng ký tự `<` nếu $A$ đứng trước $B$, `>` nếu $A$ đứng sau $B$, hoặc `=` nếu chúng bằng nhau.

### Ràng buộc

- $1\le n,q\le2\cdot10^5$.
- $|S|=n$; $S$ chỉ gồm các chữ cái từ `a` đến `z`.
- $1\le l_1\le r_1\le n$; $1\le l_2\le r_2\le n$.

### Sample Input 1

```text
6 4
banana
1 3 3 5
2 4 4 6
2 3 2 4
3 6 1 1
```

### Sample Output 1

```text
<
=
<
>
```

### Sample Input 2

```text
4 3
aaaa
1 4 2 4
1 2 3 4
1 1 1 4
```

### Sample Output 2

```text
>
=
<
```

### Giải thích

**Ví dụ 1:** Bốn phép so sánh lần lượt là `ban` với `nan`, `ana` với `ana`, `an` với `ana`, và `nana` với `b`.

**Ví dụ 2:** Các đoạn chỉ chứa chữ `a`, nên kết quả được quyết định bởi độ dài.
