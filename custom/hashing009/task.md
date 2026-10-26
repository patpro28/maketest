# HASHING009 — Thông điệp trên đường đi

### Đề bài

Cho một cây vô hướng gồm $n$ đỉnh, đánh số từ $1$ đến $n$. Đỉnh $i$ mang ký tự $S_i$, là một chữ cái thường tiếng Anh. Các ký tự không thay đổi.

Thông điệp trên đường đi có hướng $u\to v$ là xâu tạo bằng cách đọc ký tự tại các đỉnh trên đường đi đơn duy nhất từ $u$ đến $v$, theo đúng thứ tự di chuyển, **bao gồm cả hai đầu mút**. Nếu $u=v$, thông điệp chỉ có một ký tự.

Mỗi truy vấn gồm bốn đỉnh $u,v,x,y$. Hãy kiểm tra thông điệp trên đường đi $u\to v$ có bằng thông điệp trên đường đi $x\to y$ hay không. Hai đường đi được phép có đỉnh chung. Chiều đi là một phần của truy vấn.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $n,q$.
- Dòng thứ hai chứa xâu $S$ độ dài $n$; ký tự thứ $i$ là ký tự tại đỉnh $i$.
- Trong $n-1$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $a,b$, mô tả một cạnh nối hai đỉnh.
- Trong $q$ dòng tiếp theo, mỗi dòng chứa bốn số nguyên $u,v,x,y$ mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in `YES` nếu hai thông điệp bằng nhau, hoặc `NO` nếu chúng khác nhau.

### Ràng buộc

- $1\le n,q\le2\cdot10^5$.
- $|S|=n$; $S$ chỉ gồm các chữ cái từ `a` đến `z`.
- $1\le a,b,u,v,x,y\le n$.
- Các cạnh tạo thành một cây.

### Sample Input 1

```text
5 4
ababa
1 2
2 3
3 4
4 5
1 3 3 5
1 2 2 1
2 4 4 2
1 1 1 3
```

### Sample Output 1

```text
YES
NO
YES
NO
```

### Sample Input 2

```text
4 3
aabc
1 2
1 3
1 4
2 3 1 3
3 4 3 4
2 2 1 1
```

### Sample Output 2

```text
NO
YES
YES
```

### Giải thích

**Ví dụ 1:** Hai đường đi của truy vấn đầu đều tạo xâu `aba`. Truy vấn thứ hai so sánh `ab` với `ba`. Truy vấn thứ ba so sánh hai xâu `bab`. Truy vấn cuối so sánh `a` với `aba`, khác độ dài.

**Ví dụ 2:** Truy vấn đầu so sánh `aab` với `ab`. Truy vấn thứ hai so sánh cùng một đường đi. Truy vấn cuối so sánh hai đỉnh riêng lẻ đều mang chữ `a`.
