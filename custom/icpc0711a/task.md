# ICPC0711A — Xâu ABC

### Đề bài

Cho xâu $S$ gồm $N$ ký tự in hoa và $Q$ truy vấn. Mỗi truy vấn gồm vị trí $X$ và ký tự $C$: gán $S[X]=C$, sau đó đếm số lần xâu `ABC` xuất hiện như một **xâu con liên tiếp** của $S$. Các vị trí được đánh số từ $1$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa xâu $S$ gồm $N$ ký tự in hoa.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa số nguyên $X$ và ký tự $C$.

### Dữ liệu ra

Với mỗi truy vấn, in số lần xuất hiện của `ABC` sau khi thực hiện phép gán, mỗi kết quả trên một dòng.

### Ràng buộc

- $1\le N,Q\le2\cdot10^5$.
- $1\le X\le N$.
- $S$ và $C$ chỉ chứa các chữ cái in hoa từ `A` đến `Z`.

### Sample Input 1

```text
10 4
ABCDEABCFA
5 B
3 A
5 C
8 G
```

### Sample Output 1

```text
2
1
1
0
```

### Sample Input 2

```text
3 3
CBA
1 A
2 B
3 C
```

### Sample Output 2

```text
0
0
1
```

### Giải thích

Ở ví dụ 1, xâu lần lượt trở thành `ABCDBABCFA`, `ABADBABCFA`, `ABADCABCFA` và `ABADCABGFA`, có tương ứng $2,1,1,0$ lần xuất hiện của `ABC`.

Ở ví dụ 2, xâu lần lượt là `ABA`, `ABA`, `ABC`.
