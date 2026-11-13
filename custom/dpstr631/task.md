# DPSTR631 — Xóa chữ có chi phí

### Đề bài

Cho xâu $S$ gồm $N$ chữ cái thường. Xóa ký tự ở vị trí ban đầu thứ $i$ tốn chi phí $D_i$. Các vị trí có cùng chữ vẫn có thể có chi phí khác nhau. Hãy tìm tổng chi phí nhỏ nhất để các ký tự còn lại tạo thành xâu đối xứng. Không được chèn hoặc thay chữ. Được phép xóa mọi ký tự.

Một xâu là **đối xứng** nếu đọc từ trái sang phải và từ phải sang trái đều thu được cùng một xâu. Xâu một ký tự và xâu rỗng đều đối xứng.

Một **dãy con** được tạo bằng cách xóa một số vị trí, có thể không xóa vị trí nào, và giữ nguyên thứ tự các ký tự còn lại. Các vị trí giữ lại không bắt buộc liên tiếp; mỗi vị trí chỉ được dùng một lần.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ ký tự.
- Dòng thứ ba chứa $N$ số nguyên $D_1,D_2,\ldots,D_N$.

### Dữ liệu ra

In tổng chi phí xóa nhỏ nhất. Kết quả được in chính xác, không lấy modulo.

### Ràng buộc

- $1\le N\le5000$.
- $S$ chỉ gồm chữ cái thường từ `a` đến `z`.
- $0\le D_i\le10^9$ với mọi $1\le i\le N$.

### Sample Input 1

```text
4
aaba
1 100 1000 1
```

### Sample Output 1

```text
1
```

### Sample Input 2

```text
3
abc
5 1 7
```

### Sample Output 2

```text
6
```

### Giải thích

Ở ví dụ 1, xóa chữ `a` đầu tiên với chi phí $1$ để giữ `aba`. Dù hai đầu xâu ban đầu cùng là `a`, cố giữ cả hai sẽ phải xóa một chữ bên trong với chi phí ít nhất $100$. Ở ví dụ 2, giữ `c` và xóa hai chữ trước với chi phí $5+1=6$ là tối ưu.
