# DAYNEN — Dãy số nén

### Đề bài

Bạn tạo lần lượt $N$ dãy số $S_1,S_2,\ldots,S_N$. Mỗi phần tử thuộc tập $\{1,2,\ldots,C\}$. Ở bước $i$, một trong ba chỉ dẫn sau xác định dãy $S_i$:

- `1 x`: $S_i$ chỉ gồm một phần tử $x$.
- `2 u v`: $S_i$ là dãy $S_u$ nối với dãy $S_v$, theo đúng thứ tự đó.
- `3 u k`: $S_i$ là $k$ bản sao liên tiếp của $S_u$. Nếu $k=0$, $S_i$ là dãy rỗng.

Các dãy đã tạo không bị thay đổi. Khi dùng chỉ dẫn loại $2$ hoặc $3$, các chỉ số được tham chiếu đều nhỏ hơn $i$.

Sau mỗi bước, hãy tìm độ dài dãy con không giảm dài nhất của $S_i$. Một dãy con được tạo bằng cách xóa tùy ý một số phần tử, giữ nguyên thứ tự các phần tử còn lại; các phần tử được chọn không cần liên tiếp. Không giảm nghĩa là phần tử sau lớn hơn hoặc bằng phần tử trước. Dãy rỗng có đáp án $0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,C$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa một chỉ dẫn tạo $S_i$ theo định dạng trên.

### Dữ liệu ra

In $N$ dòng. Dòng thứ $i$ chứa độ dài dãy con không giảm dài nhất của $S_i$.

### Ràng buộc

- $1\le N\le20000$; $1\le C\le5$.
- Với chỉ dẫn loại $1$: $1\le x\le C$.
- Với chỉ dẫn loại $2$: $1\le u,v<i$; cho phép $u=v$.
- Với chỉ dẫn loại $3$: $1\le u<i$ và $0\le k\le10^{12}$.
- Độ dài của **mỗi dãy được tạo**, trước khi lấy dãy con, không vượt $10^{12}$. Dữ liệu bảo đảm điều kiện này.
- Dùng số nguyên có dấu $64$ bit cho độ dài và đáp án.

### Sample Input 1

```text
7 3
1 2
1 1
2 1 2
3 3 3
2 4 1
3 5 0
2 6 5
```

### Sample Output 1

```text
1
1
1
3
4
0
4
```

### Sample Input 2

```text
4 1
1 1
3 1 1000000000000
3 2 0
2 3 1
```

### Sample Output 2

```text
1
1000000000000
0
1
```

### Sample Input 3

```text
5 3
1 1
1 3
1 2
2 1 2
2 4 3
```

### Sample Output 3

```text
1
1
1
2
2
```

### Giải thích

Ở ví dụ 1, $S_3=[2,1]$ và $S_4=[2,1,2,1,2,1]$. Trong $S_4$ có thể lấy ba số $2$. Nối thêm một số $2$ tạo $S_5$ có đáp án $4$. Dãy $S_6$ rỗng, nên nối $S_6$ với $S_5$ giữ nguyên đáp án của $S_5$.

Ở ví dụ 2, $S_2$ gồm $10^{12}$ số $1$ và có thể chọn tất cả chúng. Các phần tử bằng nhau được phép cùng xuất hiện trong dãy con không giảm.

Ở ví dụ 3, dãy cuối là $[1,3,2]$. Có thể chọn $[1,3]$ hoặc $[1,2]$, đều dài $2$.
