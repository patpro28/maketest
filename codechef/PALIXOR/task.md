### Đề bài

Cho một mảng $A$ gồm $N$ số nguyên không âm. Tìm số lượng cặp $(i,j)$ $1\le i\le j\le N$ thoả mãn:

- $A_i \oplus A_j$ là một số đối xứng (trong hệ thập phân), ở đây $\oplus$ là phép toán [XOR bit](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)

### Dữ liệu vào

- Dòng đầu chứa một số $T$ là số lượng test.
- Mỗi test gồm $2$ dòng:
    - Dòng đầu chứa một số nguyên $N$ là độ dài dãy.
    - Dòng 2 chứa $N$ số nguyên không âm $A_i$.

### Dữ liệu ra

- Với mỗi test, in ra số cặp tìm được.

### Giới hạn

- $1\le T\le 100$.
- $1\le N\le 10^5$.
- $0\le A_i<2^{15}$.
- Tổng số lượng $N$ trong tất cả test không vượt quá $200000$.

### Sample Input

    2
    4
    13 27 12 26
    3
    2 2 2

### Sample Output

    8
    6

### Giải thích

Test 1: Có $8$ cặp là:

- $13\oplus 13=27\oplus 27=12\oplus 12=26\oplus 26 =0$
- $13\oplus 27=22$
- $13\oplus 12=1$
- $27\oplus 26=1$
- $12\oplus 26=22$

Test 2: Mọi cặp đều là số đối xứng.