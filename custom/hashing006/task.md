# HASHING006 — Những vòng chữ tương đương

### Đề bài

Cho $n$ xâu, mỗi xâu có độ dài đúng $m$ và chỉ gồm các chữ cái thường tiếng Anh.

Một phép xoay vòng chuyển một số ký tự ở đầu xâu xuống cuối xâu, giữ nguyên thứ tự của các ký tự. Có thể chuyển $0$ ký tự. Ví dụ, `abcd`, `bcda`, `cdab` và `dabc` là các phép xoay vòng của nhau.

Hai xâu thuộc cùng một nhóm khi có thể xoay vòng một xâu để thu được xâu kia. Không được đảo ngược xâu. Hãy đếm số nhóm khác nhau trong danh sách; các xâu trùng nhau thuộc cùng nhóm.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $n,m$.
- Trong $n$ dòng tiếp theo, mỗi dòng chứa một xâu độ dài $m$.

### Dữ liệu ra

In số nhóm xâu khác nhau theo quan hệ xoay vòng.

### Ràng buộc

- $1\le n,m\le2\cdot10^5$.
- $n\cdot m\le2\cdot10^5$.
- Mỗi xâu có độ dài đúng $m$ và chỉ gồm các chữ cái từ `a` đến `z`.

### Sample Input 1

```text
5 4
abcd
cdab
bcda
aaaa
aaab
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
3 3
abc
bca
acb
```

### Sample Output 2

```text
2
```

### Giải thích

**Ví dụ 1:** Ba xâu đầu thuộc một nhóm. Hai xâu `aaaa` và `aaab` tạo hai nhóm riêng, nên có tổng cộng $3$ nhóm.

**Ví dụ 2:** `abc` và `bca` thuộc cùng nhóm. `acb` là xâu đảo của `bca`, nhưng không phải phép xoay vòng của `abc`, nên thuộc nhóm khác.
