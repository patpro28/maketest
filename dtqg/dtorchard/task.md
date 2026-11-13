# DTORCHARD — Vườn trái cây

### Đề bài

Khu vườn có $N$ hàng và $M$ cột. Mỗi ô có một cây, với $0$ biểu thị cây táo của Bin và $1$ biểu thị cây chuối của Bon. Mỗi người đã trồng ít nhất một cây.

Bon chọn một hình chữ nhật gồm các ô liên tiếp theo hàng và cột. Phần của Bon là các ô trong hình chữ nhật, còn Bin nhận các ô bên ngoài. Mỗi phần vườn phải có ít nhất một ô.

Bin chuyển mọi cây táo nằm trong phần của Bon sang phần của mình. Bon chuyển mọi cây chuối nằm ngoài hình chữ nhật vào phần của mình. Mỗi cây chuyển qua ranh giới hai phần vườn tốn $1$ đơn vị tiền. Hãy tìm chi phí nhỏ nhất có thể.

### Dữ liệu vào

Đọc dữ liệu từ tệp `ORCHARD.INP`.

- Dòng đầu chứa hai số nguyên $N,M$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa $M$ chữ số $a_{i,1},a_{i,2},\ldots,a_{i,M}$, mô tả các ô của hàng $i$ từ trái sang phải.

### Dữ liệu ra

Ghi vào tệp `ORCHARD.OUT` một số nguyên là chi phí nhỏ nhất.

### Ràng buộc

- $1\le N\le150$ và $2\le M$.
- Nếu $N=1$ thì $M\le10^6$. Nếu $N=2$ thì $M\le10^5$. Nếu $3\le N\le150$ thì $M\le5000$.
- $a_{i,j}\in\{0,1\}$. Khu vườn có ít nhất một ô $0$ và một ô $1$.

### Sample Input 1

```text
5 7
0 0 1 0 0 1 0
0 1 1 1 1 1 0
0 1 1 0 0 1 0
0 1 1 1 1 1 0
0 0 1 0 0 1 0
```

### Sample Output 1

```text
6
```

### Giải thích

Trong ví dụ 1, Bon có thể chọn hình chữ nhật từ hàng $2$ đến hàng $4$ và từ cột $2$ đến cột $6$. Khi đó cần chuyển $2$ cây táo ra ngoài và $4$ cây chuối vào trong. Tổng chi phí nhỏ nhất là $6$.
