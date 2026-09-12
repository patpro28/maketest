### Đề bài

Chef có một cây gồm $N$ đỉnh, được đánh số từ $1$ đến $N$. Cây được gốc tại đỉnh $1$.  
Mỗi đỉnh $i$ có trọng số $w_i$.

Với một đỉnh $u$ có độ sâu $d$ (gốc có độ sâu $1$), ta xét dãy các đỉnh trên đường đi từ $u$ về gốc:

$$(v_1, v_2, \ldots, v_d), \quad v_1 = u,\; v_d = 1.$$

Khi đó, ta định nghĩa vector:

$$F_u = (w_{v_1}, w_{v_2}, \ldots, w_{v_d}).$$

Với hai đỉnh $u$ và $v$ có cùng độ sâu $d$, ta định nghĩa tích vô hướng:

$$F_u \cdot F_v = \sum_{i=1}^{d} F_{u,i} \cdot F_{v,i}.$$

Bạn cần trả lời $Q$ truy vấn. Mỗi truy vấn gồm hai đỉnh $u, v$ có cùng độ sâu; hãy tính:

$$F_u \cdot F_v \pmod{2^{32}}.$$

### Dữ liệu vào

- Dòng đầu: hai số nguyên $N, Q$.
- Dòng thứ hai: $N$ số nguyên $w_1, w_2, \ldots, w_N$.
- $N-1$ dòng tiếp theo: mỗi dòng chứa hai số $u, v$ mô tả một cạnh.
- $Q$ dòng tiếp theo: mỗi dòng chứa hai số $u, v$ (có cùng độ sâu).

### Dữ liệu ra

- Với mỗi truy vấn, in ra một số nguyên là giá trị $F_u \cdot F_v \bmod 2^{32}$.

### Ràng buộc

- $1 \le N, Q \le 3 \cdot 10^5$.
- $1 \le w_i \le 10^9$.
- $1 \le u, v \le N$.
- Trong mỗi truy vấn: $u, v$ có cùng độ sâu.
- Cây gốc tại đỉnh $1$.

### Sample Input 1
    5 2
    5 4 3 2 1
    1 2
    1 3
    2 4
    2 5
    2 3
    4 5

### Sample Output 1
    37
    43

### Giải thích

- Truy vấn $(2,3)$:  
  Đường đi từ $2$ về gốc: $(2,1)$ → vector $F_2 = (4, 5)$.  
  Đường đi từ $3$ về gốc: $(3,1)$ → vector $F_3 = (3, 5)$.  
  $$F_2 \cdot F_3 = 4\cdot 3 + 5\cdot 5 = 12 + 25 = 37.$$

- Truy vấn $(4,5)$:  
  $F_4 = (2,4,5)$,  
  $F_5 = (1,4,5)$,  
  $$F_4 \cdot F_5 = 2\cdot 1 + 4\cdot 4 + 5\cdot 5 = 2 + 16 + 25 = 43.$$
