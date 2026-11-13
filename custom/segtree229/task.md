# SEGTREE229 — San bằng hai khu vực với ngân sách chung

### Đề bài

Cho $N$ vị trí trên một hàng, vị trí $i$ có độ cao nguyên $A_i$. Biên độ của một đoạn là hiệu giữa độ cao lớn nhất và nhỏ nhất trong đoạn đó.

Bạn thực hiện lần lượt $M$ thao tác thuộc hai loại sau.

- Cộng $x$ vào độ cao của từng vị trí trong đoạn $[L,R]$.
- Cho đoạn $[L,R]$, hai khu vực rời nhau $[U,V]$ và $[S,T]$ nằm trong đoạn đó, cùng ngân sách $B$. Chọn hai số nguyên không âm $h_1,h_2$ thỏa mãn $h_1+h_2\le B$. Tăng mọi vị trí trong khu vực thứ nhất thêm $h_1$ và mọi vị trí trong khu vực thứ hai thêm $h_2$. Hỏi biên độ nhỏ nhất có thể của toàn đoạn $[L,R]$ sau hai lần tăng giả định.

Ngân sách tính theo tổng hai mức tăng $h_1+h_2$. Các mức tăng giả định chỉ dùng để tính kết quả truy vấn. Mọi truy vấn sau đó tiếp tục sử dụng dãy do các thao tác cộng đoạn tạo ra.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Mỗi dòng trong $M$ dòng tiếp theo chứa một thao tác. Dạng `0 L R x` cộng $x$ vào mọi độ cao trong đoạn $[L,R]$. Dạng `1 L R U V S T B` hỏi biên độ nhỏ nhất với hai khu vực và ngân sách đã cho.

### Dữ liệu ra

Với mỗi thao tác loại `1`, in biên độ nhỏ nhất trên một dòng, theo thứ tự truy vấn.

### Ràng buộc

- $1\le N,M\le 100\,000$.
- $|A_i|\le 10^9$ với mọi giá trị ban đầu.
- Với thao tác loại `0`, $1\le L\le R\le N$ và $|x|\le 10^9$.
- Với thao tác loại `1`, $1\le L\le U\le V<S\le T\le R\le N$ và $0\le B\le 10^{15}$.

### Sample Input 1

```text
7 5
10 1 2 8 3 4 9
1 1 7 2 3 5 6 8
1 1 7 2 3 5 6 0
0 2 6 2
1 1 7 2 3 5 6 9
1 2 6 2 4 5 6 20
```

### Sample Output 1

```text
4
9
2
7
```

### Sample Input 2

```text
4 6
-5 -1 8 9
1 1 4 1 2 3 4 20
1 1 4 1 2 3 4 0
1 2 3 2 2 3 3 3
0 2 2 7
1 2 3 2 2 3 3 10
1 1 4 2 2 3 4 1000000000000000
```

### Sample Output 2

```text
4
14
6
0
14
```

### Giải thích

Ở ví dụ 1, trong truy vấn đầu tiên, chọn $h_1=5$ và $h_2=3$ để đưa mọi độ cao của đoạn vào khoảng $[6,10]$. Để biên độ còn $3$, hai khu vực phải có độ cao ít nhất là $7$ vì vị trí $1$ vẫn cao $10$. Khi đó cần tăng lần lượt ít nhất $6$ và $4$, vượt ngân sách. Truy vấn thứ hai có ngân sách bằng $0$ nên biên độ là $9$. Sau thao tác cộng đoạn, truy vấn tiếp theo có thể đưa toàn đoạn vào khoảng $[8,10]$. Trong truy vấn cuối, khu vực $[2,4]$ có hai độ cao $3$ và $10$. Hiệu của chúng luôn bằng $7$ khi khu vực được tăng đều, và biên độ $7$ đã đạt được khi chưa tăng.

Ở ví dụ 2, truy vấn đầu tiên có thể tăng khu vực $[1,2]$ thêm $10$ và giữ nguyên khu vực $[3,4]$, cho biên độ $4$. Hai vị trí đầu chênh lệch $4$ nên không thể giảm thêm. Sau cập nhật tại vị trí $2$, hai độ cao trong đoạn $[2,3]$ là $6$ và $8$. Tăng vị trí $2$ thêm $2$ trong truy vấn cho biên độ $0$. Ở truy vấn cuối, vị trí $1$ nằm ngoài hai khu vực và giữ độ cao $-5$, còn vị trí $4$ cao ít nhất $9$, nên biên độ ít nhất là $14$.
