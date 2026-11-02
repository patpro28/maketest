# SEGTREE005 — Cực đại sau các phép cộng

### Đề bài

Có một dãy gồm $n$ phần tử, đánh số từ $1$ đến $n$. Ban đầu, mọi phần tử đều bằng $0$.

Trước hết, thực hiện $m$ phép biến đổi. Mỗi phép được mô tả bởi ba số $u,v,k$: cộng $k$ vào **từng phần tử** có chỉ số từ $u$ đến $v$, kể cả hai đầu đoạn.

Sau khi hoàn thành **toàn bộ $m$ phép biến đổi**, bạn cần trả lời $q$ câu hỏi. Mỗi câu hỏi gồm hai chỉ số $u,v$, yêu cầu cho biết:

- Giá trị lớn nhất của một phần tử trong đoạn $[u,v]$.
- Số phần tử trong đoạn $[u,v]$ có giá trị bằng giá trị lớn nhất đó.

Trong giai đoạn trả lời câu hỏi, dãy không thay đổi. Các phần tử không được phép biến đổi nào tác động tới vẫn có giá trị bằng $0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $n,m$.
- Mỗi dòng trong $m$ dòng tiếp theo chứa ba số nguyên $u,v,k$, mô tả một phép biến đổi.
- Dòng tiếp theo chứa số nguyên $q$, là số câu hỏi.
- Mỗi dòng trong $q$ dòng tiếp theo chứa hai số nguyên $u,v$, mô tả một câu hỏi.

### Dữ liệu ra

Với mỗi câu hỏi, in hai số nguyên trên một dòng: giá trị lớn nhất trong đoạn được hỏi và số lần xuất hiện của giá trị đó trong đoạn, cách nhau bởi một dấu cách.

### Ràng buộc

- $1\le n,m,q\le200000$.
- Với mọi phép biến đổi và câu hỏi: $1\le u\le v\le n$.
- Với mỗi phép biến đổi: $1\le k\le10^9$.
- Giá trị của một phần tử sau các phép biến đổi có thể đạt $2\cdot10^{14}$.

### Sample Input 1

```text
6 2
1 3 2
4 6 3
1
3 4
```

### Sample Output 1

```text
3 1
```

### Sample Input 2

```text
8 3
2 4 2
4 6 2
6 6 2
5
1 8
1 1
7 8
2 3
4 6
```

### Sample Output 2

```text
4 2
0 1
0 2
2 2
4 2
```

### Giải thích

Ở ví dụ 1, sau hai phép biến đổi, dãy là $[2,2,2,3,3,3]$. Đoạn $[3,4]$ gồm hai giá trị $2,3$, nên giá trị lớn nhất là $3$ và xuất hiện $1$ lần.

Ở ví dụ 2, dãy sau các phép biến đổi là $[0,2,2,4,2,4,0,0]$:

- Đoạn $[1,8]$ có giá trị lớn nhất $4$, xuất hiện tại hai vị trí $4,6$.
- Đoạn $[1,1]$ chỉ có một phần tử bằng $0$.
- Đoạn $[7,8]$ có hai phần tử đều bằng $0$.
- Đoạn $[2,3]$ có hai phần tử đều bằng $2$.
- Đoạn $[4,6]$ có giá trị lớn nhất $4$, xuất hiện $2$ lần.
