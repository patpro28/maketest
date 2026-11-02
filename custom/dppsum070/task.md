# PREFIX070 — Tổng trong hình chữ nhật

### Đề bài

Cho bảng số nguyên có $N$ hàng và $M$ cột. Ô ở hàng $i$, cột $j$ có giá trị $A_{i,j}$. Hàng và cột đều được đánh số từ $1$.

Có $Q$ truy vấn. Mỗi truy vấn gồm bốn số $X_1,Y_1,X_2,Y_2$, mô tả hình chữ nhật có góc trên trái $(X_1,Y_1)$ và góc dưới phải $(X_2,Y_2)$. Tính cả các ô trên biên và ở bốn góc.

Với mỗi truy vấn, hãy tính tổng giá trị của tất cả các ô trong hình chữ nhật.

Giá trị các ô có thể âm. Cộng đúng giá trị có dấu của từng ô.

Các giá trị trong bảng không thay đổi giữa các truy vấn.

### Dữ liệu vào

- Dòng đầu chứa 3 số nguyên $N,M,Q$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa $M$ số nguyên $A_{i,1},A_{i,2},\ldots,A_{i,M}$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa bốn số nguyên $X_1,Y_1,X_2,Y_2$.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa tổng giá trị các ô trong hình chữ nhật được hỏi. Tổng có thể âm.

### Ràng buộc

- $1\le N,M\le500$.
- $1\le Q\le200000$.
- $-10^9\le A_{i,j}\le10^9$.
- $1\le X_1\le X_2\le N$; $1\le Y_1\le Y_2\le M$ trong mỗi truy vấn.

### Sample Input 1

```text
3 4 6
-3 0 1 2
4 -2 7 9
10 11 17 121
1 1 3 4
2 2 3 3
1 2 1 4
1 3 3 3
3 4 3 4
2 1 3 4
```

### Sample Output 1

```text
177
33
3
25
121
177
```

### Sample Input 2

```text
1 1 2
-1000000000
1 1 1 1
1 1 1 1
```

### Sample Output 2

```text
-1000000000
-1000000000
```

### Giải thích

Ở ví dụ 1, truy vấn đầu lấy toàn bảng và có kết quả $177$. Truy vấn thứ hai lấy các hàng $2,3$ và các cột $2,3$, có kết quả $33$. Truy vấn thứ năm chỉ lấy ô $(3,4)$, có kết quả $121$. Các truy vấn còn lại cho kết quả theo thứ tự như trên.

Ở ví dụ 2, bảng chỉ có ô $(1,1)$ với giá trị $-1000000000$. Cả hai truy vấn đều lấy ô này, nên cùng cho kết quả $-1000000000$.
