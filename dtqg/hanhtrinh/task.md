# HANHTRINH — Hành trình đúng số chặng

### Đề bài

Có $N$ trạm và $M$ tuyến đường một chiều. Tuyến thứ $i$ đi từ $u_i$ tới $v_i$, mang lại số điểm $w_i$ mỗi lần đi qua. Điểm có thể âm. Có thể có nhiều tuyến cùng đầu mút và tuyến quay về chính trạm xuất phát.

Bạn xuất phát tại trạm $S$, phải đi qua **đúng $K$ tuyến đường**, rồi kết thúc tại trạm $T$. Được phép đi qua một trạm hoặc một tuyến nhiều lần. Không có hành động đứng yên miễn phí; muốn ở lại cùng trạm sau một chặng phải đi qua một tuyến tự khuyên có trong dữ liệu.

Hãy tìm tổng điểm lớn nhất của một hành trình hợp lệ, hoặc cho biết không tồn tại hành trình như vậy. Khi $K=0$, hành trình không đi qua tuyến nào, có tổng điểm $0$ và kết thúc ngay tại $S$.

### Dữ liệu vào

- Dòng đầu chứa năm số nguyên $N,M,S,T,K$.
- Trong $M$ dòng tiếp theo, dòng thứ $i$ chứa ba số nguyên $u_i,v_i,w_i$.

### Dữ liệu ra

In tổng điểm lớn nhất. Nếu không có hành trình hợp lệ, in `IMPOSSIBLE`.

### Ràng buộc

- $1\le N\le30$; $0\le M\le2000$.
- $1\le S,T,u_i,v_i\le N$.
- $0\le K\le10^{12}$.
- $-10^6\le w_i\le10^6$.
- Kết quả hợp lệ nằm trong đoạn $[-10^{18},10^{18}]$; dùng số nguyên có dấu $64$ bit.

### Sample Input 1

```text
3 5 1 3 3
1 2 4
2 3 5
1 3 8
3 3 -2
2 2 1
```

### Sample Output 1

```text
10
```

### Sample Input 2

```text
2 1 1 2 2
1 2 7
```

### Sample Output 2

```text
IMPOSSIBLE
```

### Sample Input 3

```text
1 1 1 1 0
1 1 -5
```

### Sample Output 3

```text
0
```

### Giải thích

Ở ví dụ 1, hành trình $1\to2\to2\to3$ có đúng ba chặng và đạt $4+1+5=10$ điểm.

Ở ví dụ 2, sau chặng đầu tiên bạn tới trạm $2$ và không còn tuyến nào để đi tiếp. Hành trình một chặng không đáp ứng yêu cầu hai chặng.

Ở ví dụ 3, bạn đã ở trạm đích và không cần đi qua tuyến nào.
