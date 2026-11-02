# SEGTREE311 — Trọng lượng sau cập nhật

### Đề bài

Cho dãy số nguyên $a_1,a_2,\dots,a_n$.

**Trọng lượng của đoạn** $[u,v]$ là tổng lớn nhất của một đoạn con liên tiếp **không rỗng**, nằm hoàn toàn trong $[u,v]$. Nói cách khác, trọng lượng là giá trị lớn nhất của

$$a_l+a_{l+1}+\dots+a_r$$

với $u\le l\le r\le v$.

Bạn cần thực hiện $m$ thao tác theo thứ tự được cho, thuộc một trong hai loại:

- `1 u v`: tính và in trọng lượng của đoạn $[u,v]$ trên dãy hiện tại.
- `0 x y`: gán phần tử $a_x$ bằng $y$. Thay đổi này có hiệu lực đối với mọi thao tác tiếp theo.

Đoạn con được chọn có thể chỉ gồm một phần tử hoặc là toàn bộ đoạn được hỏi. Nếu mọi phần tử trong đoạn đều âm, trọng lượng là phần tử lớn nhất trong đoạn, không phải $0$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $n$, là số phần tử của dãy.
- Dòng thứ hai chứa $n$ số nguyên $a_1,a_2,\dots,a_n$.
- Dòng thứ ba chứa số nguyên $m$, là tổng số thao tác.
- Mỗi dòng trong $m$ dòng tiếp theo chứa ba số nguyên theo một trong hai định dạng `1 u v` hoặc `0 x y`.

### Dữ liệu ra

Với mỗi thao tác loại `1`, in một số nguyên trên một dòng: trọng lượng của đoạn được hỏi tại thời điểm đó.

Thao tác loại `0` không yêu cầu in kết quả. Tổng số dòng kết quả bằng số thao tác loại `1`.

### Ràng buộc

- $1\le n,m\le200000$.
- $-10^9\le a_i\le10^9$ ở thời điểm ban đầu.
- Với thao tác loại `1`: $1\le u\le v\le n$.
- Với thao tác loại `0`: $1\le x\le n$, $-10^9\le y\le10^9$.

### Sample Input 1

```text
4
1 2 3 4
4
1 1 3
0 3 -3
1 2 4
1 3 3
```

### Sample Output 1

```text
6
4
-3
```

### Sample Input 2

```text
3
-5 -2 -7
7
1 1 3
0 2 -9
1 1 3
0 1 0
1 1 2
0 3 10
1 1 3
```

### Sample Output 2

```text
-2
-5
0
10
```

### Giải thích

Ở ví dụ 1:

- Ban đầu, đoạn $[1,3]$ gồm $1,2,3$; chọn cả đoạn được tổng lớn nhất là $6$.
- Sau thao tác `0 3 -3`, dãy trở thành $[1,2,-3,4]$.
- Trong đoạn $[2,4]$ gồm $2,-3,4$, chọn riêng phần tử $4$ được tổng lớn nhất là $4$.
- Đoạn $[3,3]$ chỉ có phần tử $-3$, nên trọng lượng bằng $-3$.

Ở ví dụ 2, truy vấn đầu trả về $-2$. Sau khi gán $a_2=-9$, phần tử lớn nhất trong đoạn $[1,3]$ là $-5$, nên truy vấn tiếp theo trả về $-5$. Gán $a_1=0$ khiến trọng lượng đoạn $[1,2]$ bằng $0$. Sau cập nhật cuối, dãy là $[0,-9,10]$ và trọng lượng đoạn $[1,3]$ bằng $10$.
