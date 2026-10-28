# DPTREE35 — Hoàn thành nhiệm vụ

### Đề bài

Có $N$ nhiệm vụ, được đánh số từ $1$ đến $N$, tạo thành một cây có gốc là nhiệm vụ $1$. Các người con của một nhiệm vụ là những nhiệm vụ con trực tiếp của nó.

Để hoàn thành nhiệm vụ $u$, bạn có thể chọn một trong các cách sau:

- Thuê người làm trọn gói nhiệm vụ $u$ với chi phí $C_u$. Khi đó không cần hoàn thành riêng các nhiệm vụ nằm dưới $u$ và không trả thêm chi phí cho chúng.
- Nếu $u$ có ít nhất một nhiệm vụ con trực tiếp, hoàn thành **tất cả** những nhiệm vụ con đó. Với mỗi nhiệm vụ con, bạn tiếp tục được lựa chọn theo cùng quy tắc.

Một nhiệm vụ lá không có nhiệm vụ con, nên chỉ có thể hoàn thành bằng cách thuê làm trọn gói. Mỗi khoản thuê được tính một lần tại nhiệm vụ được chọn thuê.

Hãy tìm tổng chi phí nhỏ nhất để hoàn thành nhiệm vụ gốc $1$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $C_1,C_2,\ldots,C_N$.
- Trong $N-1$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $u,v$, mô tả một cạnh của cây nhiệm vụ. Cây luôn có gốc là nhiệm vụ $1$.

### Dữ liệu ra

In một số nguyên là tổng chi phí nhỏ nhất để hoàn thành nhiệm vụ $1$.

### Ràng buộc

- $1\le N\le2\cdot10^5$.
- $0\le C_i\le10^9$ với mọi $1\le i\le N$.
- $1\le u,v\le N$; $u\ne v$.
- Các cạnh tạo thành một cây có gốc $1$.

### Sample Input 1

```text
5
20 6 15 4 5
1 2
1 3
3 4
3 5
```

### Sample Output 1

```text
15
```

### Sample Input 2

```text
1
7
```

### Sample Output 2

```text
7
```

### Giải thích

Ở ví dụ 1, nhiệm vụ $3$ có thể hoàn thành bằng cách thuê riêng hai nhiệm vụ $4,5$ với tổng chi phí $4+5=9$. Để hoàn thành nhiệm vụ $1$, thuê nhiệm vụ $2$ với giá $6$ và hoàn thành nhiệm vụ $3$ với giá $9$, tổng cộng $15$, rẻ hơn giá trọn gói $20$.

Ở ví dụ 2, nhiệm vụ $1$ là lá nên phải thuê làm trọn gói với chi phí $7$.
