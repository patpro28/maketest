# SEGTREE003 — Mã kiểm tra

### Đề bài

Một hệ thống lưu dãy $N$ số nguyên không âm $A_1,A_2,\ldots,A_N$. Mã kiểm tra của đoạn $[l,r]$ là kết quả phép XOR theo bit của tất cả phần tử trong đoạn: $A_l\oplus A_{l+1}\oplus\cdots\oplus A_r$.

Bạn cần trả lời $Q$ truy vấn mã kiểm tra. Dãy số được giữ nguyên trong suốt quá trình trả lời truy vấn.

Phép XOR theo bit cho bit kết quả bằng $1$ khi hai bit tương ứng khác nhau, và bằng $0$ khi chúng giống nhau. Chẳng hạn, $5\oplus3=6$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả các giá trị của dãy.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa hai số nguyên $l,r$, mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in một dòng chứa mã kiểm tra của đoạn được hỏi.

### Ràng buộc

- $1\le N\le200000$; $1\le Q\le200000$.
- $0\le A_i\le10^9$.
- Với mỗi truy vấn: $1\le l\le r\le N$.

### Sample Input 1

```text
5 4
5 3 5 0 7
1 5
2 4
1 3
4 4
```

### Sample Output 1

```text
4
6
3
0
```

### Sample Input 2

```text
3 3
1000000000 1000000000 1
1 2
1 3
2 2
```

### Sample Output 2

```text
0
1
1000000000
```

### Giải thích

Ở ví dụ 1, mã kiểm tra của cả dãy là $5\oplus3\oplus5\oplus0\oplus7=4$. Đoạn $[2,4]$ có mã $3\oplus5\oplus0=6$. Hai số $5$ trong đoạn $[1,3]$ triệt tiêu nhau khi XOR nên kết quả là $3$.

Ở ví dụ 2, XOR hai giá trị bằng nhau cho kết quả $0$. Vì vậy đoạn $[1,3]$ có mã kiểm tra bằng $1$.
