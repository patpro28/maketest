### Đề bài

Bạn được cho một dãy số nguyên $a_1, a_2, \ldots, a_n$. Bạn cần trả lời $m$ truy vấn trên dãy này.

Mỗi truy vấn được mô tả bởi hai chỉ số $l$ và $r$. Cách tính đáp án cho truy vấn như sau:

- Với mỗi phần tử trong đoạn con $a_l, a_{l+1}, \ldots, a_r$, hãy tính số lần xuất hiện của nó trong đoạn này.
- Tạo một tập hợp $occ$ chứa *tất cả các số lần xuất hiện* này (mỗi giá trị chỉ xuất hiện một lần trong tập hợp).
- Đáp án của truy vấn là **số nguyên dương nhỏ nhất không xuất hiện trong tập $occ$** (tức là số MEX của tập $occ$).

Các truy vấn được đưa vào theo dạng mã hoá online: cho truy vấn thứ $i$ với đầu vào là $x, y$, ta xác định:

- Nếu đây là truy vấn đầu tiên thì đặt $a = 0$, ngược lại $a$ là kết quả của truy vấn trước đó.
- Khi đó:
    - $l = x \oplus a$
    - $r = y \oplus a$
    - ($\oplus$ là phép XOR)

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $n, m$.
- Dòng thứ hai chứa $n$ số nguyên $a_1, a_2, \ldots, a_n$.
- $m$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $x, y$ dùng để tính ra $l, r$ như mô tả.

### Dữ liệu ra

- Với mỗi truy vấn, in ra một dòng chứa một số nguyên — đáp án của truy vấn.

### Ràng buộc

- $1 \le n, m \le 10^5$
- $1 \le a_i \le 10^9$
- $0 \le x, y < 2^n$
- Luôn đảm bảo $1 \le l \le r \le n$, với:
  - $l = x \oplus \text{prevAns}$
  - $r = y \oplus \text{prevAns}$

### Sample Input 1
    10 3
    1 1 2 3 4 2 3 3 1 5
    1 10
    5 1
    11 9

### Sample Output 1
    4
    3
    2

### Giải thích

**Truy vấn 1:** 
$l = 1$, $r = 10$.  
Trong đoạn này:  
- $4, 5$ xuất hiện $1$ lần  
- $2$ xuất hiện $2$ lần  
- $1, 3$ xuất hiện $3$ lần  
Vậy $occ = \{1, 2, 3\}$, MEX là $4$.

**Truy vấn 2:** 

Dùng prevAns = 4 → $l = 5 \oplus 4 = 1$, $r = 1 \oplus 4 = 5$.  
$occ = \{1, 2\}$ → MEX = $3$.

**Truy vấn 3:** 

prevAns = 3 → $l = 11 \oplus 3 = 8$, $r = 9 \oplus 3 = 10$.  
Các phần tử đều xuất hiện đúng 1 lần → $occ = \{1\}$ → MEX = $2$.
