# BS52A — Đánh giá nhóm gia đình

### Đề bài

Trong một khu dân cư, có $N$ gia đình sinh sống dọc theo một con phố. Mỗi gia đình được ghi nhận một **chỉ số điều kiện sinh hoạt** (có thể âm, bằng $0$ hoặc dương), lần lượt là $A_1,A_2,\ldots,A_N$.

Ban quản lý khu phố thường xuyên tổ chức các **buổi sinh hoạt nhóm**, mỗi nhóm gồm **ba gia đình khác nhau**, được chọn sao cho thứ tự xuất hiện của họ trên con phố là tăng dần. Cụ thể, mỗi nhóm được xác định bởi một bộ ba chỉ số $i<j<\ell$; ba vị trí không nhất thiết liên tiếp.

Với mỗi nhóm gồm ba gia đình, ban quản lý đánh giá mức độ ổn định của nhóm đó bằng cách lấy **giá trị nhỏ nhất** trong ba chỉ số sinh hoạt của nhóm:

$$\min(A_i,A_j,A_\ell).$$

Ghi lại toàn bộ các mức đánh giá thu được từ mọi nhóm ba gia đình, ta được **danh sách đánh giá nhóm**, gồm $\dfrac{N(N-1)(N-2)}{6}$ phần tử. Mỗi nhóm đóng góp đúng một phần tử; **các giá trị bằng nhau vẫn được giữ nguyên số lần xuất hiện**.

Có $Q$ yêu cầu độc lập. Với mỗi số nguyên dương $K$, hãy xác định **giá trị nhỏ thứ $K$** trong danh sách đánh giá nhóm, tức là phần tử ở vị trí $K$ sau khi sắp xếp danh sách tăng dần. Các vị trí được đánh số bắt đầu từ $1$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $T$, là số bộ dữ liệu.
- Với mỗi bộ dữ liệu, dòng đầu chứa hai số nguyên $N,Q$, là số gia đình và số yêu cầu.
- Dòng tiếp theo chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, là chỉ số sinh hoạt của các gia đình.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một số nguyên dương $K$, mô tả một yêu cầu.

### Dữ liệu ra

Với mỗi yêu cầu, in trên một dòng giá trị nhỏ thứ $K$ trong danh sách đánh giá nhóm tương ứng. In kết quả theo đúng thứ tự bộ dữ liệu và thứ tự yêu cầu, không thêm dòng trống giữa các bộ dữ liệu.

### Ràng buộc

- $1\le T\le1000$.
- $3\le N\le3\cdot10^5$.
- $1\le Q\le3\cdot10^5$.
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
2
6 2
3 3 3 3 3 3
18
1
4 4
2 4 2 1
1
2
3
4
```

### Sample Output 1

```text
3
3
1
1
1
2
```

### Sample Input 2

```text
1
6 6
-2 5 1 -2 0 4
1
10
16
17
19
20
```

### Sample Output 2

```text
-2
-2
-2
0
0
1
```

### Giải thích

Ở ví dụ 1:

- Bộ dữ liệu 1 có $20$ nhóm ba gia đình. Mọi nhóm đều có mức đánh giá $3$, nên cả hai yêu cầu đều cho kết quả $3$.
- Bộ dữ liệu 2 có bốn nhóm. Ba nhóm chứa gia đình thứ $4$ đều có mức đánh giá $1$; nhóm còn lại gồm các gia đình $1,2,3$ có mức đánh giá $2$. Danh sách đánh giá sau khi sắp xếp là $[1,1,1,2]$.

Ở ví dụ 2, có $20$ nhóm. Có $16$ nhóm chứa ít nhất một trong hai gia đình có chỉ số $-2$, nên có mức đánh giá $-2$. Trong bốn nhóm còn lại, ba nhóm có mức đánh giá $0$ và một nhóm có mức đánh giá $1$. Vì vậy, các vị trí từ $1$ đến $16$ mang giá trị $-2$, các vị trí từ $17$ đến $19$ mang giá trị $0$, còn vị trí $20$ mang giá trị $1$.
