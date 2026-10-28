# DICHCHUYEN — Cổng dịch chuyển liên vùng

### Đề bài

Có $N$ địa điểm được đánh số từ $1$ đến $N$. Bạn đang ở địa điểm $S$ và muốn đến địa điểm $T$ bằng các cổng dịch chuyển.

Có $Q$ cổng. Cổng thứ $i$ được mô tả bởi năm số $l_i,r_i,a_i,b_i,c_i$. Khi đang ở **bất kỳ** địa điểm nào thuộc đoạn nguồn $[l_i,r_i]$, bạn có thể trả $c_i$ đồng để dịch chuyển đến **một địa điểm bất kỳ** thuộc đoạn đích $[a_i,b_i]$. Mỗi lần dùng cổng chỉ dịch chuyển từ vị trí hiện tại đến một địa điểm đích đã chọn.

Các cổng có hướng và được sử dụng không giới hạn số lần. Ngoài việc sử dụng cổng, bạn không có cách di chuyển nào khác. Hai đoạn của một cổng có thể giao nhau; các cổng có thể trùng nhau.

Hãy tìm tổng chi phí nhỏ nhất để đi từ $S$ đến $T$. Bạn được phép không sử dụng cổng nào; vì vậy, nếu $S=T$ thì chi phí nhỏ nhất bằng $0$.

### Dữ liệu vào

- Dòng đầu chứa bốn số nguyên $N,Q,S,T$.
- Trong $Q$ dòng tiếp theo, dòng thứ $i$ chứa năm số nguyên $l_i,r_i,a_i,b_i,c_i$, mô tả cổng thứ $i$.

### Dữ liệu ra

In chi phí nhỏ nhất để đi từ $S$ đến $T$, hoặc $-1$ nếu không thể đến $T$.

### Ràng buộc

- $1\le N\le100000$; $0\le Q\le100000$.
- $1\le S,T\le N$.
- $1\le l_i\le r_i\le N$; $1\le a_i\le b_i\le N$.
- $0\le c_i\le10^9$.
- Đáp án có thể vượt phạm vi số nguyên có dấu $32$ bit.

### Sample Input 1

```text
7 4 2 7
1 3 4 5 6
5 5 6 7 2
2 2 7 7 12
4 4 1 2 0
```

### Sample Output 1

```text
8
```

### Sample Input 2

```text
5 2 1 5
2 3 4 5 0
4 5 1 1 1
```

### Sample Output 2

```text
-1
```

### Giải thích

Ở ví dụ 1, dùng cổng thứ nhất để đi từ địa điểm $2$ đến địa điểm $5$ với chi phí $6$. Sau đó dùng cổng thứ hai để đến địa điểm $7$ với chi phí $2$. Tổng chi phí là $8$, nhỏ hơn việc dùng cổng thứ ba với chi phí $12$.

Ở ví dụ 2, địa điểm $1$ không thuộc đoạn nguồn của cổng nào, nên bạn không thể rời khỏi đó để đến địa điểm $5$. Cổng thứ hai chỉ cho phép dịch chuyển theo chiều từ đoạn $[4,5]$ về địa điểm $1$.
