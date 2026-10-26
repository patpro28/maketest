# SEGTREE193 — Chọn hộp vừa nhất

### Đề bài

Có $N$ hộp ban đầu, hộp thứ $i$ còn sức chứa $c_i$, là số nguyên trong $[0,C]$. Thực hiện các thao tác:

- `1 c`: thêm một hộp mới có sức chứa còn lại bằng $c$.
- `2 w`: đặt một món kích thước $w$ vào hộp có sức chứa còn lại nhỏ nhất nhưng không dưới $w$. Nếu tồn tại, in sức chứa của hộp **trước khi đặt**, rồi giảm sức chứa của hộp đó đi $w$. Nếu không có, in `-1` và không thay đổi hộp nào.

Các hộp có thể có cùng sức chứa. Khi nhiều hộp cùng phù hợp nhất, chọn hộp nào cũng tạo cùng trạng thái về số lượng hộp ở từng mức sức chứa. Hộp có sức chứa còn lại bằng $0$ vẫn được giữ lại.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $C,N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $c_1,\ldots,c_N$. Nếu $N=0$, dòng này là dòng trống.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in đáp án trên một dòng. Thao tác loại `1` không tạo đầu ra.

### Ràng buộc

- $1\le C,Q\le200000$; $0\le N\le200000$.
- $0\le c_i,c\le C$; $1\le w\le C$.

### Sample Input 1

```text
10 3 7
0 5 8
2 4
2 6
2 3
1 4
2 4
2 2
2 1
```

### Sample Output 1

```text
5
8
-1
4
2
1
```

### Sample Input 2

```text
1 0 5

2 1
1 0
2 1
1 1
2 1
```

### Sample Output 2

```text
-1
-1
1
```

### Giải thích

Ở ví dụ 1, hai món đầu dùng hộp có sức chứa $5$ và $8$, để lại các mức $0,1,2$. Không hộp nào đủ cho món kích thước $3$. Sau khi thêm hộp sức chứa $4$, các lần đặt tiếp theo lần lượt chọn mức $4,2,1$. Ở ví dụ 2, ban đầu không có hộp; thêm hộp sức chứa $0$ vẫn không đặt được món kích thước $1$. Sau khi thêm hộp sức chứa $1$, món cuối được đặt thành công.
