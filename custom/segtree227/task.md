# SEGTREE227 — Hiệu chỉnh đường dốc

### Đề bài

Có $N$ trạm được đánh số từ $1$ đến $N$. Trạm $i$ ghi nhận số đo nguyên $A_i$. Một đường chuẩn có độ dốc cố định $d$, nghĩa là độ cao chuẩn tăng thêm $d$ khi đi từ một trạm sang trạm tiếp theo. Giá trị $d$ có thể âm.

Bạn thực hiện lần lượt $M$ thao tác thuộc hai loại sau.

- Cộng $x$ vào từng số đo trong đoạn $[L,R]$.
- Với đoạn $[L,R]$ và khoảng $[P,Q]$, chọn một số nguyên $H$ thỏa mãn $P\le H\le Q$ làm độ cao chuẩn tại trạm $L$. Khi đó, độ cao chuẩn tại trạm $i$ là $H+(i-L)d$. Tìm giá trị nhỏ nhất có thể của độ lệch tuyệt đối lớn nhất trên đoạn, tức là $\max_{L\le i\le R}|A_i-H-(i-L)d|$.

Lựa chọn $H$ chỉ dùng để tính kết quả của truy vấn hiện tại. Các số đo chỉ thay đổi khi có thao tác cộng đoạn.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,M,d$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Mỗi dòng trong $M$ dòng tiếp theo chứa một thao tác. Dạng `0 L R x` cộng $x$ vào mọi số đo trong đoạn $[L,R]$. Dạng `1 L R P Q` hỏi độ lệch nhỏ nhất có thể trên đoạn đó.

### Dữ liệu ra

Với mỗi thao tác loại `1`, in giá trị nhỏ nhất có thể của độ lệch tuyệt đối lớn nhất trên một dòng, theo thứ tự truy vấn.

### Ràng buộc

- $1\le N,M\le 100\,000$.
- $|A_i|\le 10^9$ với mọi giá trị ban đầu.
- $|d|\le 10^9$.
- $1\le L\le R\le N$ trong mọi thao tác.
- $|x|\le 10^9$ trong mọi thao tác loại `0`.
- $-10^{15}\le P\le Q\le 10^{15}$ trong mọi thao tác loại `1`.

### Sample Input 1

```text
5 5 2
1 5 8 8 13
1 1 5 -10 10
1 2 4 6 7
0 2 4 -7
1 2 5 -8 4
1 3 3 -5 -2
```

### Sample Output 1

```text
2
2
5
3
```

### Sample Input 2

```text
4 5 -3
-9 -11 -14 -17
1 1 4 -20 0
0 2 3 1
1 2 4 -10 -10
1 2 3 -20 0
1 4 4 -19 -18
```

### Sample Output 2

```text
1
1
0
1
```

### Giải thích

Ở ví dụ 1, với truy vấn đầu tiên, chọn $H=3$ cho đường chuẩn có các độ cao $3,5,7,9,11$. Sai số lớn nhất là $2$. Trong truy vấn thứ hai, chọn $H=6$ cho sai số lớn nhất là $2$. Sau khi giảm các số đo trong đoạn $[2,4]$ đi $7$, chọn $H=2$ cho truy vấn trên đoạn $[2,5]$ để sai số lớn nhất là $5$. Ở truy vấn cuối, số đo tại trạm $3$ bằng $1$ và mốc gần nhất được phép là $-2$.

Ở ví dụ 2, sau khi cộng $1$ vào đoạn $[2,3]$, các trạm $2,3$ có số đo lần lượt là $-10,-13$. Chọn $H=-10$ cho truy vấn trên đoạn $[2,3]$ khớp chính xác cả hai số đo.
