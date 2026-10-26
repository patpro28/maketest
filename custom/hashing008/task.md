# HASHING008 — Gương chữ biến đổi

### Đề bài

Cho xâu $S$ có độ dài $n$, chỉ gồm các chữ cái thường tiếng Anh. Thực hiện $q$ thao tác theo đúng thứ tự:

- `1 p c`: thay ký tự tại vị trí $p$ bằng ký tự $c$.
- `2 l r`: kiểm tra đoạn $S[l..r]$ hiện tại có phải xâu đối xứng hay không.

Một xâu là đối xứng nếu đọc từ trái sang phải và từ phải sang trái đều thu được cùng một xâu. Các vị trí được đánh số từ $1$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $n,q$.
- Dòng thứ hai chứa xâu ban đầu $S$.
- Trong $q$ dòng tiếp theo, mỗi dòng mô tả một thao tác theo một trong hai dạng trên.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in `YES` nếu đoạn được hỏi đối xứng, hoặc `NO` nếu không. Thao tác loại `1` không tạo đầu ra.

### Ràng buộc

- $1\le n,q\le2\cdot10^5$.
- $|S|=n$; $S$ và ký tự $c$ chỉ dùng các chữ cái từ `a` đến `z`.
- Với thao tác loại `1`: $1\le p\le n$.
- Với thao tác loại `2`: $1\le l\le r\le n$.

### Sample Input 1

```text
5 6
abcba
2 1 5
1 1 z
2 1 5
2 2 4
1 5 z
2 1 5
```

### Sample Output 1

```text
YES
NO
YES
YES
```

### Sample Input 2

```text
1 3
a
2 1 1
1 1 z
2 1 1
```

### Sample Output 2

```text
YES
YES
```

### Giải thích

**Ví dụ 1:** Ban đầu `abcba` đối xứng. Sau lần thay đầu tiên, xâu là `zbcba` nên toàn xâu không đối xứng, nhưng đoạn `bcb` vẫn đối xứng. Sau khi thay ký tự cuối, xâu trở thành `zbcbz`, lại đối xứng.

**Ví dụ 2:** Mọi xâu có một ký tự đều đối xứng.
