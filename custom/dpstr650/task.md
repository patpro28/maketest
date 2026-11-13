# DPSTR650 — Sửa bản tin thành gương

### Đề bài

Cho xâu $S$ gồm $N$ chữ cái thường. Với mỗi vị trí ban đầu $i$, bạn được chọn một trong ba cách xử lý: giữ nguyên ký tự với chi phí $0$; xóa ký tự với chi phí $D_i$; hoặc thay ký tự bằng một chữ cái thường khác với chi phí $R_i$. Mỗi vị trí chỉ được xử lý một lần; chi phí luôn gắn với vị trí ban đầu, không đổi sau khi xóa các vị trí khác.

Hãy tìm tổng chi phí nhỏ nhất để các ký tự không bị xóa, đọc theo thứ tự ban đầu và sau khi thay chữ nếu có, tạo thành xâu đối xứng. Không được chèn chữ hoặc đổi thứ tự. Được phép xóa hết các vị trí.

Một xâu là **đối xứng** nếu đọc từ trái sang phải và từ phải sang trái đều thu được cùng một xâu. Xâu một ký tự và xâu rỗng đều đối xứng.

Một **dãy con** được tạo bằng cách xóa một số vị trí, có thể không xóa vị trí nào, và giữ nguyên thứ tự các ký tự còn lại. Các vị trí giữ lại không bắt buộc liên tiếp; mỗi vị trí chỉ được dùng một lần.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ ký tự.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $D_i,R_i$.

### Dữ liệu ra

In tổng chi phí xử lý nhỏ nhất. Kết quả được in chính xác, không lấy modulo.

### Ràng buộc

- $1\le N\le5000$.
- $S$ chỉ gồm chữ cái thường từ `a` đến `z`.
- $0\le D_i,R_i\le10^9$ với mọi $1\le i\le N$.

### Sample Input 1

```text
4
abca
8 9
8 2
8 7
8 9
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
4
aaba
1 1000000000
100 1000000000
1000 1000000000
1 1000000000
```

### Sample Output 2

```text
1
```

### Giải thích

Ở ví dụ 1, thay chữ `b` ở vị trí $2$ bằng `c` với chi phí $2$, được `acca`. Ở ví dụ 2, thay chữ rất đắt; xóa chữ đầu với chi phí $1$ để giữ `aba` là tối ưu.
