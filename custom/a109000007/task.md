# A109000007 — Các điểm trên mặt phẳng

### Đề bài

Một tệp nhị phân lưu tọa độ nguyên của $N$ điểm. Hãy đếm số điểm thuộc từng góc phần tư I, II, III, IV và số điểm nằm trên ít nhất một trục tọa độ.

Góc phần tư I có $x>0,y>0$; II có $x<0,y>0$; III có $x<0,y<0$; IV có $x>0,y<0$. Một điểm có $x=0$ hoặc $y=0$ được tính vào nhóm trên trục đúng một lần, kể cả gốc tọa độ. Các điểm trùng nhau vẫn được tính riêng.

### Dữ liệu vào

- Đọc dữ liệu từ tệp nhị phân **`A109000007.INP`**.
- Đầu tệp là số nguyên $N$ kiểu `int`, cho biết số bản ghi.
- Tiếp theo là đúng $N$ bản ghi `Diem`, mỗi bản ghi gồm tọa độ `x`, `y`.
- Cấu trúc `Diem` được khai báo như sau:

```cpp
struct Diem {
    int x;
    int y;
};
```

### Dữ liệu ra

Ghi kết quả vào tệp văn bản **`A109000007.OUT`**.

In trên một dòng năm số nguyên lần lượt là số điểm thuộc góc phần tư I, II, III, IV và số điểm trên trục, cách nhau một dấu cách.

### Ràng buộc

- $1\le N\le200000$; $-10^9\le x,y\le10^9$.

Trong các ví dụ dưới đây, **Sample Input là bản hiển thị hex của tệp nhị phân**: mỗi cặp ký tự biểu diễn một byte, khoảng trắng và xuống dòng chỉ giúp dễ đọc. Không đưa trực tiếp các ký tự hex này vào chương trình; tệp thật chứa các byte mà chúng biểu diễn.

### Sample Input 1

```text
05 00 00 00 01 00 00 00 02 00 00 00 ff ff ff ff
03 00 00 00 fe ff ff ff fc ff ff ff 05 00 00 00
ff ff ff ff 00 00 00 00 07 00 00 00
```

### Sample Output 1

```text
1 1 1 1 1
```

### Sample Input 2

```text
03 00 00 00 00 00 00 00 00 00 00 00 02 00 00 00
00 00 00 00 00 00 00 00 fd ff ff ff
```

### Sample Output 2

```text
0 0 0 0 3
```

### Giải thích

**Ví dụ 1:** Bốn điểm `(1, 2)`, `(-1, 3)`, `(-2, -4)`, `(5, -1)` lần lượt thuộc bốn góc phần tư; `(0, 7)` nằm trên trục.

**Ví dụ 2:** Cả ba điểm `(0, 0)`, `(2, 0)`, `(0, -3)` đều nằm trên trục. Gốc tọa độ chỉ được tính một lần.
