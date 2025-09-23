### Đề bài

Có $N$ trạm vũ trụ bay quanh Trái Đất, trong đó $C_i$ là **sức chứa tối đa** của trạm thứ $i$.

Có thêm $Q$ nhiệm vụ, mỗi nhiệm vụ có hai yêu cầu: **nhu cầu phi hành đoàn** $X$ và **nhu cầu lưu trữ** $Y$.

Phi hành đoàn **phải ở cùng một cabin** (một trạm), còn $N−1$ cabin còn lại dùng để cất trữ. Nếu chọn cabin $i$ cho phi hành đoàn, cần thỏa:

- $X \le C_i$ (cabin $i$ đủ chỗ cho toàn bộ phi hành đoàn),
- $Y \le \sum\limits_{j\ne i} C_j = \left(\sum\limits_{j=1}^{N} C_j\right) - C_i$ (tổng sức chứa của các cabin khác đủ cho nhu cầu lưu trữ).

Có thể không tồn tại cabin hợp lệ ban đầu. Để đáp ứng một nhiệm vụ, ta được **nâng cấp** sức chứa: mỗi **1 token** cho phép tăng **bất kỳ** $C_i$ lên thêm $1$ đơn vị (có thể tăng nhiều trạm, nhiều lần).

Với **mỗi nhiệm vụ**, hãy tính **số token tối thiểu** cần chi để tồn tại **ít nhất một** lựa chọn cabin phi hành đoàn thỏa cả hai điều kiện. (Mỗi nhiệm vụ được xét **độc lập**, luôn bắt đầu từ dãy $C$ ban đầu). Dưới các ràng buộc, có thể chứng minh luôn có cách đáp ứng.

### Dữ liệu vào

- Dòng đầu: số nguyên $T$ — số bộ test.
- Với mỗi bộ test:
  - Dòng 1: số nguyên $N$ — số trạm vũ trụ.
  - Dòng 2: $N$ số nguyên $C_1, C_2, \dots, C_N$ — sức chứa các trạm.
  - Dòng 3: số nguyên $Q$ — số nhiệm vụ.
  - $Q$ dòng tiếp theo: mỗi dòng chứa hai số nguyên $X_i, Y_i$ — yêu cầu của nhiệm vụ thứ $i$.

### Dữ liệu ra

- Với mỗi bộ test, in ra **$Q$ số nguyên cách nhau bởi dấu cách**, số thứ $i$ là **số token tối thiểu** cần thiết cho nhiệm vụ thứ $i$.

### Giới hạn

- $1 \le T \le 10^4$
- $2 \le N \le 2 \cdot 10^5$
- $1 \le Q \le 2 \cdot 10^5$
- $1 \le C_i, X_i, Y_i \le 10^9$
- Tổng các giá trị $N$ qua mọi bộ test $\le 2 \cdot 10^5$
- Tổng các giá trị $Q$ qua mọi bộ test $\le 2 \cdot 10^5$

### Sample Input 1

```
2
4
4 3 8 1
2
5 7
7 9
5
1 2 3 4 5
3
5 10
5 15
7 7
```

### Sample Output 1

```
0
1
0
5
2
```

### Giải thích

- Bộ test 1:
    - Nhiệm vụ 1: Chọn trạm 3 (có sức chứa 8) cho phi hành đoàn, tổng sức chứa của các trạm còn lại là $4 + 3 + 1 = 8$, đủ cho nhu cầu lưu trữ $Y = 7$. Không cần nâng cấp.
    - Nhiệm vụ 2: Chọn trạm 3 (có sức chứa 8) cho phi hành đoàn, tổng sức chứa của các trạm còn lại là $4 + 3 + 1 = 8$, không đủ cho nhu cầu lưu trữ $Y = 9$. Cần nâng cấp ít nhất một trạm, chọn nâng cấp trạm 1 (từ 4 lên 5) tốn 1 token.