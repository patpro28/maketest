# SEGTREE205 — Đổi nhãn ba màu

### Đề bài

Có $N$ ô nằm trên một hàng, đánh số từ $1$ đến $N$. Mỗi ô có một trong ba màu, mang mã $1,2,3$. Màu ban đầu của ô thứ $i$ là $A_i$.

Thực hiện lần lượt $Q$ thao tác:

- `1 L R x y`: đổi chỗ hai màu $x,y$ trong đoạn $[L,R]$. Mỗi ô đang có màu $x$ chuyển thành $y$; mỗi ô đang có màu $y$ chuyển thành $x$; các ô có màu khác giữ nguyên. Tất cả thay đổi của một thao tác diễn ra đồng thời.
- `2 p`: cho biết màu hiện tại của ô $p$.

Nếu $x=y$, thao tác không làm thay đổi ô nào. Các thao tác được thực hiện theo đúng thứ tự đầu vào.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\dots,A_N$, mô tả trạng thái ban đầu.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo định dạng trên.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in một số nguyên trên một dòng: mã màu hiện tại của ô được hỏi. Thao tác loại `1` không yêu cầu in kết quả.

### Ràng buộc

- $1\le N,Q\le200000$.
- $1\le A_i\le3$ ở thời điểm ban đầu.
- Với thao tác loại `1`: $1\le L\le R\le N$.
- Với thao tác loại `1`: $1\le x,y\le3$.
- Với thao tác loại `2`: $1\le p\le N$.

### Sample Input 1

```text
5 7
1 2 3 1 2
1 1 5 1 2
2 1
1 2 4 2 3
2 3
2 4
1 1 3 1 3
2 2
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
1 6
1
1 1 1 1 2
1 1 1 2 3
2 1
1 1 1 3 3
1 1 1 1 3
2 1
```

### Sample Output 2

```text
3
1
```

### Giải thích

Ở ví dụ 1, lần đổi đầu tạo dãy $[2,1,3,2,1]$. Đổi hai màu $2,3$ trong đoạn $[2,4]$ tạo dãy $[2,1,2,3,1]$. Đổi hai màu $1,3$ trong đoạn $[1,3]$ tạo dãy $[2,3,2,3,1]$. Các câu trả lời lần lượt là $2,2,3,3$.

Ở ví dụ 2, màu của ô duy nhất lần lượt đổi từ $1$ sang $2$, rồi sang $3$. Đổi chỗ màu $3$ với chính nó không làm thay đổi ô. Lần đổi cuối đưa màu từ $3$ về $1$, nên hai câu trả lời là $3$ và $1$.
