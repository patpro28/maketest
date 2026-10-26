# HASHING007 — Hai mảnh bản đồ có thể xoay

### Đề bài

Cho bảng ký tự gồm $R$ hàng và $C$ cột. Hàng được đánh số từ trên xuống dưới, cột từ trái sang phải, bắt đầu từ $1$.

Mỗi truy vấn gồm năm số $r_1,c_1,r_2,c_2,d$, chỉ định hai mảnh hình vuông cạnh $d$, có ô trên cùng bên trái lần lượt là $(r_1,c_1)$ và $(r_2,c_2)$.

Hãy kiểm tra có thể xoay mảnh thứ hai theo chiều kim đồng hồ một góc $0$, $90$, $180$ hoặc $270$ độ để thu được mảnh thứ nhất hay không. Không được lật gương. Hai mảnh có thể chồng lấn. Bảng không thay đổi sau truy vấn.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $R,C,q$.
- Trong $R$ dòng tiếp theo, mỗi dòng chứa một xâu độ dài $C$, mô tả một hàng của bảng.
- Trong $q$ dòng tiếp theo, mỗi dòng chứa năm số nguyên $r_1,c_1,r_2,c_2,d$ mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in `YES` nếu có phép xoay thỏa mãn, hoặc `NO` nếu không có.

### Ràng buộc

- $1\le R,C\le1000$; $1\le q\le2\cdot10^5$.
- Mỗi ô chứa một chữ cái từ `a` đến `z`.
- $1\le d\le\min(R,C)$.
- $1\le r_1,r_2\le R-d+1$; $1\le c_1,c_2\le C-d+1$.

### Sample Input 1

```text
2 4 3
abca
cddb
1 1 1 3 2
1 1 1 1 2
1 1 2 2 1
```

### Sample Output 1

```text
YES
YES
NO
```

### Sample Input 2

```text
2 4 2
abac
cdbd
1 1 1 3 2
1 2 1 2 2
```

### Sample Output 2

```text
NO
YES
```

### Giải thích

**Ví dụ 1:** Mảnh thứ nhất của truy vấn đầu có hai hàng `ab`, `cd`; mảnh thứ hai có hai hàng `ca`, `db`. Xoay mảnh thứ hai $270$ độ theo chiều kim đồng hồ sẽ được mảnh thứ nhất. Truy vấn thứ hai so sánh cùng một mảnh. Truy vấn cuối so sánh `a` với `d`.

**Ví dụ 2:** Hai mảnh ở truy vấn đầu có các hàng `ab`, `cd` và `ac`, `bd`. Chúng là ảnh lật qua đường chéo của nhau, nhưng không trùng nhau bằng phép xoay. Truy vấn thứ hai so sánh cùng một mảnh.
