# BS14 — Chỉ số nhóm cao nhất

### Đề bài

Trong một khu dân cư có $N$ gia đình sống dọc theo một con phố, được đánh số từ $1$ đến $N$. Gia đình thứ $i$ có chỉ số điều kiện sinh hoạt là số nguyên $A_i$. Chỉ số này có thể âm, bằng $0$ hoặc dương.

Ban quản lý xét tất cả các nhóm gồm ba gia đình khác nhau. Mỗi nhóm được xác định bởi một bộ ba chỉ số $i<j<\ell$, không yêu cầu ba gia đình ở các vị trí liên tiếp. Mức đánh giá của nhóm là **giá trị lớn nhất** trong ba chỉ số:

$$\max(A_i,A_j,A_\ell).$$

Ghi lại mức đánh giá của từng nhóm, ta thu được một danh sách có $\dfrac{N(N-1)(N-2)}{6}$ phần tử. Mỗi nhóm đóng góp đúng một phần tử. **Các phần tử có giá trị bằng nhau vẫn được giữ nguyên số lần xuất hiện**, không gộp thành một phần tử.

Có $Q$ yêu cầu độc lập. Với mỗi số nguyên dương $K$, hãy tìm phần tử nhỏ thứ $K$ trong danh sách đánh giá, tức là phần tử ở vị trí $K$ sau khi sắp xếp danh sách tăng dần. Các vị trí được đánh số bắt đầu từ $1$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $T$, là số bộ dữ liệu.
- Với mỗi bộ dữ liệu, dòng đầu chứa hai số nguyên $N,Q$.
- Dòng tiếp theo chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một số nguyên dương $K$, mô tả một yêu cầu.

### Dữ liệu ra

Với mỗi yêu cầu, in trên một dòng giá trị nhỏ thứ $K$ trong danh sách đánh giá của bộ dữ liệu tương ứng. In các kết quả theo đúng thứ tự bộ dữ liệu và thứ tự yêu cầu, không thêm dòng trống giữa các bộ dữ liệu.

### Ràng buộc

- $1\le T\le1000$.
- $3\le N\le3\cdot10^5$; $1\le Q\le3\cdot10^5$.
- $-10^9\le A_i\le10^9$ với mọi $1\le i\le N$.
- $1\le K\le\dfrac{N(N-1)(N-2)}{6}$ trong mỗi yêu cầu.
- Tổng $N$ trên tất cả bộ dữ liệu không vượt quá $3\cdot10^5$.
- Tổng $Q$ trên tất cả bộ dữ liệu không vượt quá $3\cdot10^5$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 100% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
1
5 6
4 1 3 2 5
1
2
4
5
9
10
```

### Sample Output 1

```text
3
4
4
5
5
5
```

### Sample Input 2

```text
2
4 4
-2 5 -2 0
1
2
3
4
6 3
7 7 7 7 7 7
1
10
20
```

### Sample Output 2

```text
0
5
5
5
7
7
7
```

### Giải thích

Ở ví dụ 1, sau khi sắp xếp, danh sách đánh giá của $10$ nhóm là:

$$[3,4,4,4,5,5,5,5,5,5].$$

Vì vậy, các phần tử ở vị trí $1,2,4,5,9,10$ lần lượt là $3,4,4,5,5,5$.

Ở ví dụ 2:

- Bộ dữ liệu 1 có bốn nhóm, với danh sách đánh giá sau khi sắp xếp là $[0,5,5,5]$. Nhóm có chỉ số $(1,3,4)$ gồm các giá trị $-2,-2,0$ nên có mức đánh giá $0$; ba nhóm còn lại đều có mức đánh giá $5$.
- Bộ dữ liệu 2 có $20$ nhóm và mọi nhóm đều có mức đánh giá $7$, nên cả ba yêu cầu đều cho kết quả $7$.
