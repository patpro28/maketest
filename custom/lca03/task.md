### Đề bài

Như bạn có thể biết, sloth sống trên cây. Theo đó, David có một chú sloth nuôi mà anh ấy cho nó chơi trên những cái cây không trọng số của mình. Thỉnh thoảng, David thấy chú sloth đang ở một đỉnh $a$ trong cây và yêu cầu nó di chuyển đến đỉnh $b$.

Sloth rất ngoan nhưng chỉ đủ năng lượng để đi tối đa $c$ cạnh.  
Nếu khoảng cách từ $a$ đến $b$ nhỏ hơn hoặc bằng $c$ thì nó sẽ đến nơi và ngủ.  
Nếu lớn hơn $c$ thì nó sẽ đi dọc đường từ $a$ về phía $b$ đúng $c$ cạnh rồi dừng lại và treo mình để... ngủ tiếp.

Hãy xác định sloth sẽ dừng ở đỉnh nào. Bạn cần trả lời $q$ truy vấn như vậy.

### Dữ liệu vào

- Dòng 1: số nguyên $n$ — số đỉnh của cây.  
- $n-1$ dòng tiếp theo: mỗi dòng gồm hai số nguyên $u, v$ mô tả một cạnh của cây.  
- Dòng tiếp: số nguyên $q$ — số truy vấn.  
- $q$ dòng tiếp theo: mỗi dòng gồm ba số $a, b, c$ — vị trí đầu, vị trí đích, và năng lượng tối đa.

### Dữ liệu ra

- Với mỗi truy vấn, in ra một số nguyên: đỉnh nơi sloth dừng lại.

### Ràng buộc

- $1 \le n, q \le 3 \times 10^5$  
- $1 \le a, b, c, u, v \le n$  
- Đồ thị là một cây.

### Sample Input 1
    1
    1
    1 1 1

### Sample Output 1
    1

### Sample Input 2
    3
    3 2
    2 1
    3
    2 2 2
    1 1 2
    3 3 3

### Sample Output 2
    2
    1
    3

### Sample Input 3
    5
    4 2
    1 4
    5 4
    3 4
    5
    3 5 2
    3 5 4
    1 5 5
    4 5 4
    1 5 4

### Sample Output 3
    5
    5
    5
    5
    5
