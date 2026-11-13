# DPALL0004 — Robot qua đúng K khúc cua

### Đề bài

Cho bảng gồm $R$ hàng và $C$ cột. Ô có giá trị $-1$ là ô cấm. Các ô còn lại có chi phí bằng giá trị ghi trong ô.

Robot xuất phát tại ô $(1,1)$ và cần đến ô $(R,C)$. Mỗi bước đi sang phải hoặc xuống dưới đúng một ô. Robot không thể đi vào hay xuất phát từ ô cấm. Hai bước liên tiếp khác hướng tạo thành một lần đổi hướng. Bước đầu tiên không tính là đổi hướng.

Tìm tổng chi phí nhỏ nhất của một đường đi đổi hướng đúng $K$ lần. Chi phí tính trên mọi ô của đường đi, gồm cả ô xuất phát và ô đích.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $R,C,K$.
- Trong $R$ dòng tiếp theo, dòng thứ $i$ chứa $C$ số nguyên $A_{i,1},A_{i,2},\ldots,A_{i,C}$.

### Dữ liệu ra

In tổng chi phí nhỏ nhất nếu có đường đi hợp lệ. Nếu không, in $-1$.

### Ràng buộc

- $1\le R,C\le200$; $0\le K\le30$.
- $-1\le A_{i,j}\le10^9$.

### Sample Input 1

```text
2 3 1
1 2 1
9 1 1
```

### Sample Output 1

```text
5
```

### Sample Input 2

```text
3 3 1
1 2 -1
1 3 1
-1 1 2
```

### Sample Output 2

```text
-1
```

### Giải thích

- Ví dụ 1. Đi hai bước sang phải rồi một bước xuống dưới. Đường đi đổi hướng một lần và có chi phí $1+2+1+1=5$.
- Ví dụ 2. Một đường đi chỉ đổi hướng một lần phải đi qua góc trên phải hoặc góc dưới trái. Cả hai ô đều bị cấm.
