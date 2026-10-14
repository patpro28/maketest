# FIXSUM - Tổng cố định

Cho hai số nguyên $N$ và $S$ ($N \ge 2$). Bạn cần xây dựng một mảng $A$ gồm $N$ số nguyên thỏa mãn:

- $0 \le A_i \le S$ với mọi $1 \le i \le N$.
- $A_1 + A_2 + \cdots + A_N = S$.
- $A_1 \mathbin{\&} A_2 \mathbin{\&} \cdots \mathbin{\&} A_N = 0$, trong đó $\&$ là phép AND theo bit.

Trong tất cả các mảng thỏa mãn, hãy tìm **giá trị nhỏ nhất có thể của phần tử lớn nhất**. Bạn chỉ cần in giá trị này, không cần in mảng.

## Dữ liệu vào

- Dòng đầu chứa số nguyên $T$, là số lượng bộ test.
- Mỗi bộ test gồm một dòng chứa hai số nguyên $N$ và $S$.

## Dữ liệu ra

Với mỗi bộ test, in trên một dòng giá trị nhỏ nhất có thể của phần tử lớn nhất trong mảng.

## Giới hạn

- $1 \le T \le 10^4$.
- $2 \le N \le 10^9$.
- $1 \le S \le 10^9$.

## Ví dụ

### Input

```text
4
2 7
3 6
5 21
100 256455
```

### Output

```text
4
3
5
2570
```

## Giải thích

- Bộ test 1: Có thể chọn $A = [4, 3]$. Tổng bằng $7$ và $4 \mathbin{\&} 3 = 0$.
- Bộ test 2: Có thể chọn $A = [1, 2, 3]$. Tổng bằng $6$ và $1 \mathbin{\&} 2 \mathbin{\&} 3 = 0$.
- Bộ test 3: Có thể chọn $A = [2, 4, 5, 5, 5]$. Tổng bằng $21$ và AND của tất cả phần tử bằng $0$.
