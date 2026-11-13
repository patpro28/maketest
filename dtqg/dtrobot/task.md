# DTROBOT — Robot đếm lần rẽ

### Đề bài

Trên mặt phẳng tọa độ nguyên, hai điểm được gọi là kề nhau nếu tổng độ chênh lệch tuyệt đối của hai tọa độ bằng $1$.

Một robot xuất phát từ $(0,0)$ và mỗi bước di chuyển sang một điểm kề với vị trí hiện tại. Từ bước di chuyển thứ hai, robot có thể đi thẳng, rẽ trái $90^\circ$, rẽ phải $90^\circ$ hoặc quay ngược $180^\circ$.

Cho danh sách các điểm robot đã đi qua theo đúng thứ tự, kể cả vị trí xuất phát. Hãy đếm số lần robot rẽ phải và số lần robot rẽ trái. Đi thẳng và quay ngược không được tính là rẽ trái hoặc rẽ phải.

### Dữ liệu vào

Đọc từ tệp `ROBOT.INP`:

- Dòng đầu chứa số nguyên $n$ là số điểm trong danh sách.
- Trong $n$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $x_i,y_i$ là tọa độ điểm thứ $i$.

### Dữ liệu ra

Ghi ra tệp `ROBOT.OUT` hai số nguyên: số lần rẽ phải, sau đó là số lần rẽ trái.

### Ràng buộc

- $2\le n\le70000$.
- $(x_1,y_1)=(0,0)$.
- $|x_{i+1}-x_i|+|y_{i+1}-y_i|=1$ với mọi $1\le i<n$.

### Sample Input 1

```text
7
0 0
1 0
1 1
2 1
2 0
3 0
3 -1
```

### Sample Output 1

```text
3 2
```

### Giải thích

Trong ví dụ 1, sau bước đầu sang phải, robot lần lượt rẽ trái, rẽ phải, rẽ phải, rẽ trái và rẽ phải. Vì vậy có ba lần rẽ phải và hai lần rẽ trái.

### Nguồn

Chuyển từ `robot.pdf` do người dùng cung cấp. Giới hạn đã được điều chỉnh cho bộ luyện tập.
