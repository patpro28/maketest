# DPTREE28 — Điều chỉnh cây biểu thức

### Đề bài

Cho một cây nhị phân có gốc là đỉnh $1$, gồm $N$ đỉnh được đánh số từ $1$ đến $N$. Mỗi đỉnh hoặc là lá, hoặc có đúng hai người con khác nhau.

Mỗi lá phải được gán một trong ba giá trị $0,1,2$. Tại lá $u$, chi phí gán ba giá trị này lần lượt là $C_{u,0},C_{u,1},C_{u,2}$.

Mỗi đỉnh không phải lá mang một phép toán cố định: cộng hoặc nhân. Giá trị của đỉnh đó là kết quả thực hiện phép toán trên giá trị hai người con, rồi lấy dư cho $3$. Phép lấy dư được thực hiện tại mọi đỉnh không phải lá.

Cho số $R\in\{0,1,2\}$. Hãy tìm tổng chi phí nhỏ nhất để giá trị tại gốc bằng $R$. Chi phí chỉ tính ở các lá; bạn không được thay đổi phép toán hay cấu trúc cây.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,R$.
- Trong $N$ dòng tiếp theo, dòng thứ $u$ mô tả đỉnh $u$ theo một trong ba dạng:
  - `0 C0 C1 C2`: đỉnh là lá; ba số cuối là chi phí gán các giá trị $0,1,2$.
  - `1 x y`: đỉnh mang phép cộng và có hai người con $x,y$.
  - `2 x y`: đỉnh mang phép nhân và có hai người con $x,y$.

### Dữ liệu ra

In một số nguyên là tổng chi phí nhỏ nhất để giá trị của gốc bằng số dư đích.

### Ràng buộc

- $1\le N\le199999$.
- $N$ là số lẻ; $R\in\{0,1,2\}$.
- $0\le C_{u,r}\le10^9$ với mọi lá $u$ và $r\in\{0,1,2\}$.
- Mọi chỉ số người con thuộc đoạn $[1,N]$.
- Các mô tả tạo thành một cây nhị phân có gốc $1$; mỗi đỉnh không phải lá có đúng hai con khác nhau.
- Nhãn của một người con có thể nhỏ hơn hoặc lớn hơn nhãn của cha.

### Sample Input 1

```text
3 2
1 2 3
0 0 5 9
0 4 0 6
```

### Sample Output 1

```text
5
```

### Sample Input 2

```text
3 2
2 2 3
0 0 5 9
0 4 0 6
```

### Sample Output 2

```text
9
```

### Giải thích

Ở ví dụ 1, gán cả hai lá giá trị $1$. Giá trị của gốc là $(1+1)\bmod3=2$, tổng chi phí bằng $5+0=5$, nhỏ nhất có thể.

Ở ví dụ 2, gán lá $2$ giá trị $2$ và lá $3$ giá trị $1$. Giá trị gốc là $(2\cdot1)\bmod3=2$, tổng chi phí bằng $9+0=9$, nhỏ nhất có thể.
