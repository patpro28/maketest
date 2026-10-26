# DOITUYEN — Đổi tuyến

### Đề bài

Một mạng giao thông gồm $N$ thành phố và $M$ chặng đường có hướng. Mỗi chặng có một mã tuyến và một thời gian di chuyển. Mã tuyến chỉ là nhãn: các chặng cùng mã không nhất thiết tạo thành một đường liên tục. Có thể có nhiều chặng giống nhau và có thể có chặng đi từ một thành phố về chính nó.

Bạn cần đi từ thành phố $S$ đến thành phố $T$. Mỗi lần đi qua một chặng, bạn trả thời gian di chuyển của chặng đó. Nếu hai chặng liên tiếp trên hành trình có mã tuyến khác nhau, bạn trả thêm $P_u$ thời gian đổi tuyến tại thành phố $u$ nằm giữa chúng. Nếu hai mã tuyến giống nhau thì không trả thời gian đổi tuyến.

Bạn không mất thời gian đổi tuyến khi lên chặng đầu tiên, cũng không mất thêm thời gian khi kết thúc hành trình. Được phép đi qua một thành phố hoặc một chặng nhiều lần. Nếu $S=T$, có thể chọn hành trình không có chặng nào, với tổng thời gian bằng $0$.

Hãy tìm tổng thời gian nhỏ nhất để đi từ $S$ đến $T$.

### Dữ liệu vào

- Dòng đầu chứa bốn số nguyên $N,M,S,T$.
- Dòng thứ hai chứa $N$ số nguyên $P_1,P_2,\ldots,P_N$.
- Trong $M$ dòng tiếp theo, mỗi dòng chứa bốn số nguyên $u,v,C,W$, mô tả một chặng từ $u$ đến $v$, thuộc tuyến có mã $C$, với thời gian di chuyển $W$.

### Dữ liệu ra

In tổng thời gian nhỏ nhất. Nếu không có hành trình từ $S$ đến $T$, in $-1$.

### Ràng buộc

- $1\le N\le 2\cdot10^5$; $0\le M\le 2\cdot10^5$.
- $1\le S,T,u,v\le N$.
- $0\le P_i\le 10^9$.
- $1\le C\le 10^9$; $1\le W\le 10^9$.
- Kết quả có thể vượt phạm vi số nguyên $32$ bit; dùng số nguyên có dấu $64$ bit.

### Sample Input 1

```text
4 4 1 4
0 100 0 0
1 2 10 1
1 3 20 2
3 2 20 2
2 4 20 1
```

### Sample Output 1

```text
5
```

### Sample Input 2

```text
3 1 1 3
5 7 9
1 2 4 6
```

### Sample Output 2

```text
-1
```

### Sample Input 3

```text
1 1 1 1
100
1 1 1 10
```

### Sample Output 3

```text
0
```

### Giải thích

Ở ví dụ 1, đi theo hành trình $1\to3\to2\to4$, luôn dùng tuyến $20$, hết $2+2+1=5$ đơn vị thời gian. Nếu đi $1\to2\to4$, thời gian là $1+100+1=102$ do phải đổi tuyến tại thành phố $2$.

Ở ví dụ 2, không có hành trình từ thành phố $1$ đến thành phố $3$.

Ở ví dụ 3, thành phố xuất phát cũng là đích; chọn hành trình không có chặng nào.
