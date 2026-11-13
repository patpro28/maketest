# SEGTREE228 — Chênh lệch giữa hai trạm đối xứng

### Đề bài

Có $N$ trạm nằm trên một hàng, đánh số từ $1$ đến $N$. Trạm $i$ có số đo nguyên $A_i$. Hai trạm tạo thành một cặp đối xứng nếu chúng có chỉ số khác nhau và tổng hai chỉ số bằng $N+1$. Khi $N$ lẻ, trạm ở giữa không thuộc cặp nào.

Bạn thực hiện lần lượt $M$ thao tác thuộc hai loại sau.

- Cộng $x$ vào từng số đo trong đoạn $[L,R]$.
- Tìm chênh lệch tuyệt đối lớn nhất $|A_i-A_j|$ trong các cặp đối xứng $(i,j)$ có cả hai trạm thuộc đoạn $[L,R]$. Nếu đoạn không chứa cặp nào, trả lời $0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Mỗi dòng trong $M$ dòng tiếp theo chứa một thao tác. Dạng `0 L R x` cộng $x$ vào mọi số đo trong đoạn $[L,R]$. Dạng `1 L R` hỏi chênh lệch lớn nhất của các cặp đối xứng nằm trọn trong đoạn đó.

### Dữ liệu ra

Với mỗi thao tác loại `1`, in kết quả trên một dòng, theo thứ tự truy vấn.

### Ràng buộc

- $1\le N,M\le 100\,000$.
- $|A_i|\le 10^9$ với mọi giá trị ban đầu.
- $1\le L\le R\le N$ trong mọi thao tác.
- $|x|\le 10^9$ trong mọi thao tác loại `0`.

### Sample Input 1

```text
7 9
10 1 9 40 -4 8 6
1 1 7
1 2 6
1 1 4
0 1 3 5
1 1 7
0 2 6 -10
1 2 6
0 5 7 20
1 1 7
```

### Sample Output 1

```text
13
13
0
18
18
22
```

### Sample Input 2

```text
4 5
-2 9 5 1
1 2 3
0 3 4 -5
1 1 4
1 1 2
1 3 3
```

### Sample Output 2

```text
4
9
0
0
```

### Giải thích

Ở ví dụ 1, các cặp đối xứng là $(1,7)$, $(2,6)$ và $(3,5)$. Ban đầu, cặp $(3,5)$ có chênh lệch lớn nhất bằng $|9-(-4)|=13$. Sau khi cộng $5$ vào ba trạm đầu, chênh lệch của cặp này là $18$. Lần cập nhật trên đoạn $[2,6]$ tác động lên cả hai trạm của cặp $(3,5)$, nên chênh lệch của cặp vẫn là $18$. Sau lần cập nhật cuối, cặp $(2,6)$ có chênh lệch lớn nhất bằng $|-4-18|=22$.

Ở ví dụ 2, đoạn $[2,3]$ chứa đúng một cặp có chênh lệch ban đầu bằng $4$. Sau khi giảm số đo tại trạm $3$ đi $5$, chênh lệch của cặp tăng lên $9$. Hai đoạn được hỏi cuối cùng đều không chứa cặp nào.
