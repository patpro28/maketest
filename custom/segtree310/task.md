# SEGTREE310 — Trọng lượng của đoạn

### Đề bài

Cho dãy số nguyên $a_1,a_2,\dots,a_n$ và $m$ truy vấn. Mỗi truy vấn gồm hai chỉ số $u,v$ với $u\le v$.

Với mỗi truy vấn, hãy chọn một đoạn con liên tiếp **không rỗng**, nằm hoàn toàn trong đoạn $[u,v]$, sao cho tổng các phần tử của đoạn con là lớn nhất. Tổng lớn nhất đó được gọi là **trọng lượng của đoạn** $[u,v]$.

Nói cách khác, cần tìm giá trị lớn nhất của

$$a_l+a_{l+1}+\dots+a_r$$

với $u\le l\le r\le v$.

Đoạn con được chọn có thể chỉ gồm một phần tử hoặc là toàn bộ đoạn $[u,v]$. Nếu mọi phần tử trong đoạn đều âm, kết quả là phần tử lớn nhất trong đoạn, không phải $0$.

Dãy số không thay đổi trong suốt các truy vấn.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $n$, là số phần tử của dãy.
- Dòng thứ hai chứa $n$ số nguyên $a_1,a_2,\dots,a_n$.
- Dòng thứ ba chứa số nguyên $m$, là số truy vấn.
- Mỗi dòng trong $m$ dòng tiếp theo chứa hai số nguyên $u,v$, mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in một số nguyên trên một dòng: trọng lượng của đoạn $[u,v]$.

### Ràng buộc

- $1\le n,m\le50000$.
- $-10^9\le a_i\le10^9$.
- $1\le u\le v\le n$.

### Sample Input 1

```text
5
2 3 -2 4 2
3
1 4
2 4
3 5
```

### Sample Output 1

```text
7
5
6
```

### Sample Input 2

```text
5
-5 -2 -7 -2 -9
4
1 5
3 3
4 5
1 1
```

### Sample Output 2

```text
-2
-7
-2
-5
```

### Giải thích

Ở ví dụ 1:

- Với đoạn $[1,4]$, chọn cả bốn phần tử được tổng $2+3-2+4=7$.
- Với đoạn $[2,4]$, chọn cả ba phần tử được tổng $3-2+4=5$.
- Với đoạn $[3,5]$, chọn đoạn con $[4,5]$ được tổng $4+2=6$.

Ở ví dụ 2, các phần tử đều âm nên chọn một phần tử lớn nhất trong đoạn được hỏi. Bốn truy vấn lần lượt cho kết quả $-2,-7,-2,-5$.
