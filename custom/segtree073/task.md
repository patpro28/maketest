# SEGTREE073 — Cân bằng đoạn

### Đề bài

Cho dãy số nguyên dương $A_1,A_2,\dots,A_N$. Bạn cần thực hiện lần lượt $Q$ truy vấn thuộc hai loại:

- `1 i X`: gán phần tử $A_i$ bằng $X$.
- `2 L R`: tính số thao tác ít nhất cần thực hiện để tất cả phần tử trong đoạn $[L,R]$ trở nên bằng nhau.

Trong truy vấn loại `2`, mỗi thao tác được phép là chọn một chỉ số $i$ trong đoạn $[L,R]$ rồi tăng $A_i$ thêm $1$ hoặc thêm $2$. Mỗi lần tăng như vậy được tính là một thao tác. Bạn được tự chọn giá trị chung mà các phần tử sẽ đạt tới.

**Truy vấn loại `2` chỉ yêu cầu tính đáp án, không thực sự thay đổi dãy.** Chỉ truy vấn loại `1` mới cập nhật giá trị dùng cho các truy vấn tiếp theo.

Nếu các phần tử trong đoạn đã bằng nhau, số thao tác cần thực hiện là $0$. Đặc biệt, một đoạn chỉ có một phần tử luôn có đáp án $0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên dương $A_1,A_2,\dots,A_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một truy vấn theo định dạng `1 i X` hoặc `2 L R`.

### Dữ liệu ra

Với mỗi truy vấn loại `2`, in một số nguyên trên một dòng: số thao tác ít nhất để các phần tử trong đoạn được hỏi trở nên bằng nhau.

Truy vấn loại `1` không yêu cầu in kết quả.

### Ràng buộc

- $1\le N,Q\le5\cdot10^5$.
- $1\le A_i\le10^9$ ở thời điểm ban đầu.
- Với truy vấn loại `1`: $1\le i\le N$, $1\le X\le10^9$.
- Với truy vấn loại `2`: $1\le L\le R\le N$.

### Sample Input 1

```text
4 3
1 3 4 1
2 1 2
1 2 4
2 2 3
```

### Sample Output 1

```text
1
0
```

### Sample Input 2

```text
5 7
1 2 3 4 5
2 1 5
2 1 5
1 5 4
2 1 5
1 1 4
2 1 5
2 2 2
```

### Sample Output 2

```text
6
6
4
2
0
```

### Giải thích

Ở ví dụ 1, đoạn $[1,2]$ gồm $1,3$. Chỉ cần tăng phần tử đầu thêm $2$ một lần để hai phần tử bằng nhau, nên đáp án là $1$. Truy vấn này không làm thay đổi dãy. Sau truy vấn `1 2 4`, dãy trở thành $[1,4,4,1]$; đoạn $[2,3]$ đã có hai phần tử bằng nhau nên đáp án tiếp theo là $0$.

Ở ví dụ 2:

- Với dãy ban đầu, có thể đưa mọi phần tử lên $5$. Các phần tử $1,2,3,4,5$ lần lượt cần $2,2,1,1,0$ thao tác, tổng cộng $6$ thao tác. Hai truy vấn đầu giống nhau và không thay đổi dãy, nên đều trả lời $6$.
- Sau khi gán $A_5=4$, dãy là $[1,2,3,4,4]$. Đưa các phần tử lên $4$ lần lượt cần $2,1,1,0,0$ thao tác, tổng cộng $4$.
- Sau khi gán $A_1=4$, dãy là $[4,2,3,4,4]$. Chỉ hai phần tử $2,3$ cần tăng, mỗi phần tử cần một thao tác, nên đáp án là $2$.
- Truy vấn cuối xét đoạn chỉ có một phần tử, nên đáp án là $0$.
