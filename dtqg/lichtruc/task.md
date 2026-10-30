# LICHTRUC — Lịch công việc tuần hoàn

### Đề bài

Bạn cần lập lịch trong $D$ ngày. Mỗi ngày, bạn được nghỉ hoặc làm đúng một trong ba công việc $A,B,C$. Nghỉ mang lại $0$ điểm. Nếu làm công việc $A,B,C$ trong ngày có mẫu $i$, bạn nhận lần lượt $a_i,b_i,c_i$ điểm; các số này có thể âm.

Lịch điểm có chu kỳ $P$: ngày thứ $d$ dùng mẫu $((d-1)\bmod P)+1$. Một lịch hợp lệ phải thỏa mãn:

- Không làm việc trong ba ngày liên tiếp: trong mỗi ba ngày liên tiếp phải có ít nhất một ngày nghỉ.
- Nếu hai ngày liên tiếp đều làm việc, hai công việc phải khác nhau. Một ngày nghỉ ngăn cách hai ngày làm việc thì không đặt thêm điều kiện về loại công việc.

Hãy tìm tổng điểm lớn nhất trong đúng $D$ ngày. Trước ngày đầu tiên, bạn ở trạng thái đã nghỉ. Sau ngày cuối cùng không cần nghỉ thêm. Khi $D=0$, tổng điểm bằng $0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $P,D$.
- Trong $P$ dòng tiếp theo, dòng thứ $i$ chứa ba số nguyên $a_i,b_i,c_i$.

### Dữ liệu ra

In tổng điểm lớn nhất của một lịch hợp lệ.

### Ràng buộc

- $1\le P\le10^5$.
- $0\le D\le10^{12}$.
- $-10^6\le a_i,b_i,c_i\le10^6$.
- Kết quả không vượt $10^{18}$; dùng số nguyên có dấu $64$ bit.

### Sample Input 1

```text
2 4
3 1 0
0 4 2
```

### Sample Output 1

```text
11
```

### Sample Input 2

```text
1 5
5 1 -2
```

### Sample Output 2

```text
15
```

### Sample Input 3

```text
1 0
100 -2 3
```

### Sample Output 3

```text
0
```

### Giải thích

Ở ví dụ 1, lịch $A,B,\text{nghỉ},B$ đạt $3+4+0+4=11$ điểm. Quy tắc về ba ngày liên tiếp vẫn áp dụng qua ranh giới giữa hai chu kỳ.

Ở ví dụ 2, lịch $A,\text{nghỉ},A,\text{nghỉ},A$ đạt $15$ điểm. Bạn được chủ động nghỉ ngay cả khi còn có thể làm việc.

Ở ví dụ 3, lịch có không ngày nên tổng điểm bằng $0$.
