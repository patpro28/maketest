# SEGTREE128 — Hàng chờ luân chuyển

### Đề bài

Ban đầu có $N$ người mang các mã phân biệt $1,2,\dots,N$, đứng trong một hàng theo đúng thứ tự đó từ đầu hàng đến cuối hàng.

Thực hiện $Q$ thao tác:

- `1 x`: đưa người mang mã $x$ ra khỏi vị trí hiện tại và chuyển xuống cuối hàng. Thứ tự tương đối của mọi người khác được giữ nguyên. Nếu $x$ đang ở cuối hàng thì thứ tự không đổi.
- `2 k`: cho biết mã của người đang đứng ở vị trí thứ $k$ từ đầu hàng, với vị trí đầu tiên được đánh số $1$.

Không ai rời khỏi hàng và không có người mới gia nhập.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo định dạng trên. Không có dòng mô tả hàng ban đầu.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in mã của người đứng ở vị trí được hỏi trên một dòng.

### Ràng buộc

- $1\le N,Q\le2\cdot10^5$.
- Với thao tác loại `1`: $1\le x\le N$.
- Với thao tác loại `2`: $1\le k\le N$.

### Sample Input 1

```text
4 8
2 2
1 2
2 2
2 4
1 1
2 1
1 1
2 4
```

### Sample Output 1

```text
2
3
2
3
1
```

### Sample Input 2

```text
1 4
1 1
2 1
1 1
2 1
```

### Sample Output 2

```text
1
1
```

### Giải thích

Ở ví dụ 1, hàng ban đầu là $[1,2,3,4]$. Chuyển người $2$ xuống cuối tạo hàng $[1,3,4,2]$; chuyển người $1$ xuống cuối tạo hàng $[3,4,2,1]$. Chuyển tiếp người $1$ khi người này đã ở cuối không làm thay đổi thứ tự. Các câu trả lời lần lượt là $2,3,2,3,1$.

Ở ví dụ 2, hàng luôn chỉ có người mang mã $1$.
