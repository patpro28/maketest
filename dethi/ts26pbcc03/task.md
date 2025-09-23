### Đề bài

Thành phố A đang quy hoạch xây dựng đô thị kiểu mẫu với các tiêu chuẩn "xanh, sạch, đẹp, hiện đại", trong đó có dự án sơn các ngôi nhà liền kề trên cùng một trục đường để có màu sắc giống nhau, với chi phí cho phép là $k$. Hiện tại mỗi ngôi nhà được sơn với một màu và mỗi màu sơn được biểu diễn bằng một kí tự từ `a` đến `z`. Chi phí chuyền đổi màu sơn của ngôi nhà từ màu sơn $x$ sang màu sơn $y$ là khoảng cách từ vị trí kí tự biểu diễn màu sơn x đến vị trí kí tự biểu diễn màu sơn $y$. Vị trí các kí tự là mã thập phân của nó trong bảng mã ASCII.

Ví dụ: Chi phí chuyển đổi từ màu sơn biểu diễn bằng kí tự `a` sang màu sơn biểu diễn bằng kí tự `b` là $|97 - 98| = 1$.

Hãy viết chương trình giúp ban quản lí quy hoạch đô thị giải quyết dự án trên. 

**Yêu cầu**: Đưa ra sô lượng nhiêu nhât các ngôi nhà liên kê cùng màu sơn sau thực hiện dự án, với tổng chi phí chuyên đôi không vượt quá $k$.

### Dữ liệu vào

- Dòng đầu tiên: một số nguyên dương $k$ $(k \leq 10^5)$ — tổng chi phí cho phép.
- Dòng thứ hai: xâu $S$ $(|S| \leq 5 \times 10^5)$ — biểu diễn màu sơn hiện tại của các ngôi nhà.

### Dữ liệu ra

- Một dòng duy nhất là số lượng lớn nhất các ngôi nhà liên tiếp có thể được sơn cùng một màu sau chuyển đổi, với tổng chi phí không vượt quá $k$.

### Sample Input 1

```
2
babac
```

### Sample Output 1

```
4
```

### Giải thích

Chuyển đổi `'b'` thành `'a'` (hoặc `a` thành `b`) và thu được xâu mới `aaaac` (hoặc `bbbbc`). Tổng chi phí biến đổi là $2$ và đạt được chuỗi có $4$ ký tự giống nhau liên tiếp.

### Sample Input 2

```
2
afab
```

### Sample Output 2

```
2
```

### Giải thích

Ta thực hiện biến đối `b` thành `a` (hoặc `a` thành `b`) và thu được xâu mới `afaa` (hoặc `afbb`). Tổng chi phí biến đổi là $1$ và đạt được chuỗi có $2$ ký tự giống nhau liên tiếp.

### Giới hạn

- 60% số test có $|S| \leq 10^3$
- 40% số test có $|S| \leq 5 \times 10^5$
