### Đề bài

Cho một cây có $N$ nút. Bạn cần trả lời $Q$ truy vấn.  
Mỗi truy vấn cho ba nút $A, B, C$.  
Hãy đếm số lượng các nút $D$ sao cho nếu chọn $D$ làm gốc của cây, thì **LCA** của $A$ và $B$ bằng $C$.

### Dữ liệu vào

- Dòng đầu: hai số nguyên $N, Q$.
- $N-1$ dòng tiếp theo: mỗi dòng chứa hai số nguyên biểu diễn một cạnh của cây.
- $Q$ dòng tiếp theo: mỗi dòng chứa ba số nguyên $A, B, C$.

### Dữ liệu ra

- Với mỗi truy vấn, in ra một số nguyên trên một dòng: số lượng nút $D$ thỏa mãn điều kiện.

### Ràng buộc

- $1 \le N, Q \le 10^5$
- Ba nút $A, B, C$ trong mỗi truy vấn là **phân biệt**

### Sample Input 1
    7 5
    1 2
    2 3
    3 4
    4 5
    2 6
    1 7
    6 5 1
    6 5 2
    6 5 3
    7 6 2
    7 5 2

### Sample Output 1
    0
    3
    1
    4
    2
