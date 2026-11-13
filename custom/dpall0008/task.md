# DPALL0008 — Đảo một dải đèn

### Đề bài

Một dải gồm $N$ đèn. Mỗi đèn có một trong ba màu A, B và C. Với hai đèn kề nhau có màu $x,y$ theo thứ tự từ trái sang phải, cặp này đóng góp $W_{x,y}$ điểm. Tổng điểm của dải là tổng điểm của $N-1$ cặp kề nhau. Điểm có thể âm và $W_{x,y}$ có thể khác $W_{y,x}$.

Bạn được đảo ngược thứ tự các đèn trong tối đa một đoạn liên tiếp. Hãy tìm tổng điểm lớn nhất có thể đạt được.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa xâu $S$ có $N$ ký tự, mô tả màu các đèn từ trái sang phải.
- Ba dòng tiếp theo, mỗi dòng chứa ba số nguyên của bảng điểm $W$. Thứ tự các hàng và các cột đều là A, B, C.

### Dữ liệu ra

In tổng điểm lớn nhất có thể đạt được.

### Ràng buộc

- $1\le N\le2\cdot10^5$.
- $S_i\in\{\mathrm{A},\mathrm{B},\mathrm{C}\}$.
- $-10^9\le W_{x,y}\le10^9$.

### Sample Input 1

```text
5
ABACB
0 6 -2
-5 0 4
3 -7 0
```

### Sample Output 1

```text
19
```

### Sample Input 2

```text
4
ABCA
0 6 -2
-5 0 4
3 -7 0
```

### Sample Output 2

```text
13
```

### Giải thích

- Ví dụ 1. Đảo đoạn $[3,4]$ để thu được ABCAB. Tổng điểm là $6+4+3+6=19$.
- Ví dụ 2. Giữ nguyên ABCA cho tổng điểm $6+4+3=13$. Không có phép đảo nào làm tăng tổng điểm.
