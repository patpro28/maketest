# BS52C — Mức đánh giá đại diện

### Đề bài

Có $N$ phần tử, phần tử thứ $i$ có giá trị nguyên $A_i$, có thể âm, bằng $0$ hoặc dương.

Xét mọi nhóm gồm ba vị trí khác nhau $i<j<\ell$, không yêu cầu các vị trí liên tiếp. Sắp xếp ba giá trị $A_i,A_j,A_\ell$ theo thứ tự không giảm thành $x\le y\le z$. Mức đánh giá của nhóm là giá trị ở giữa $y$; định nghĩa này vẫn áp dụng khi có các giá trị bằng nhau.

Ghi mức đánh giá của tất cả nhóm vào một danh sách gồm $\dfrac{N(N-1)(N-2)}6$ phần tử. Mỗi nhóm đóng góp đúng một phần tử. Các giá trị bằng nhau được giữ nguyên số lần xuất hiện.

Có $Q$ truy vấn độc lập. Với mỗi số nguyên dương $K$, hãy tìm phần tử nhỏ thứ $K$ trong danh sách đánh giá, tức là phần tử ở vị trí $K$ sau khi sắp xếp danh sách không giảm. Các vị trí được đánh số bắt đầu từ $1$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa một số nguyên dương $K$ mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in trên một dòng giá trị nhỏ thứ $K$ trong danh sách đánh giá. In theo đúng thứ tự truy vấn.

### Ràng buộc

- $3\le N\le3\cdot10^5$; $1\le Q\le3\cdot10^5$.
- $-10^9\le A_i\le10^9$ với mọi $1\le i\le N$.
- $1\le K\le\dfrac{N(N-1)(N-2)}6$ trong mỗi truy vấn.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 100% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
4 4
1 2 3 4
1
2
3
4
```

### Sample Output 1

```text
2
2
3
3
```

### Sample Input 2

```text
4 4
-2 5 -2 0
1
2
3
4
```

### Sample Output 2

```text
-2
-2
0
0
```

### Giải thích

Ở ví dụ 1, các nhóm $(1,2,3)$, $(1,2,4)$, $(1,3,4)$ và $(2,3,4)$ có mức đánh giá lần lượt là $2,2,3,3$.

Ở ví dụ 2, hai nhóm chứa cả hai phần tử có giá trị $-2$ đều có mức đánh giá $-2$. Hai nhóm còn lại có mức đánh giá $0$. Danh sách sau khi sắp xếp là $[-2,-2,0,0]$.
