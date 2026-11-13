# SEGTREE226 — Biên độ sau khi bỏ một số đo

### Đề bài

Cho $N$ số đo nguyên $A_1,A_2,\ldots,A_N$. Biên độ của một tập số đo không rỗng là hiệu giữa giá trị lớn nhất và nhỏ nhất.

Bạn thực hiện lần lượt $M$ thao tác thuộc hai loại sau.

- Cộng $x$ vào từng số đo từ vị trí $L$ đến vị trí $R$.
- Xét các số đo từ vị trí $L$ đến vị trí $R$. Nếu đoạn có ít nhất hai vị trí, hãy chọn đúng một vị trí để bỏ qua và tìm biên độ nhỏ nhất của các số đo còn lại. Nếu đoạn chỉ có một vị trí, trả lời $0$.

Vị trí được bỏ qua chỉ ảnh hưởng đến kết quả của truy vấn đó. Nếu nhiều vị trí có cùng giá trị, mỗi vị trí vẫn là một số đo riêng.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Mỗi dòng trong $M$ dòng tiếp theo chứa một thao tác. Dạng `0 L R x` cộng $x$ vào mọi số đo trong đoạn $[L,R]$. Dạng `1 L R` hỏi biên độ nhỏ nhất có thể của đoạn $[L,R]$.

### Dữ liệu ra

Với mỗi thao tác loại `1`, in biên độ nhỏ nhất trên một dòng, theo thứ tự truy vấn.

### Ràng buộc

- $1\le N,M\le 100\,000$.
- $|A_i|\le 10^9$ với mọi giá trị ban đầu.
- $1\le L\le R\le N$ trong mọi thao tác.
- $|x|\le 10^9$ trong mọi thao tác loại `0`.

### Sample Input 1

```text
6 5
1 1 4 8 8 10
1 1 6
0 2 4 3
1 1 6
1 3 5
1 1 2
```

### Sample Output 1

```text
7
7
1
0
```

### Sample Input 2

```text
5 6
-4 -4 -4 5 5
1 1 5
0 1 3 9
1 1 5
1 3 3
0 1 5 -7
1 2 4
```

### Sample Output 2

```text
9
0
0
0
```

### Giải thích

Ở ví dụ 1, trong truy vấn đầu tiên, bỏ giá trị $10$ thì biên độ còn $8-1=7$. Sau khi cộng $3$ vào đoạn $[2,4]$, dãy trở thành $1,4,7,11,8,10$. Khi hỏi cả dãy, bỏ giá trị $1$ cho biên độ $11-4=7$. Trong đoạn $[3,5]$, bỏ giá trị $11$ cho biên độ $8-7=1$. Truy vấn cuối chỉ còn một số đo sau khi bỏ qua một vị trí.

Ở ví dụ 2, trong truy vấn đầu tiên, cả $-4$ và $5$ đều xuất hiện nhiều lần. Bỏ một vị trí bất kỳ vẫn để lại cả hai giá trị, nên biên độ là $9$. Sau lần cập nhật đầu tiên, các số đo đều bằng $5$.
