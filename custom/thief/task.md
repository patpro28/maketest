### Đề bài

Một tên trộm đột nhập vào một ngôi nhà chứa $N$ món đồ. Mỗi món đồ thứ $i$ có trọng lượng $w_i$ và giá trị $c_i$. Tên trộm có một chiếc túi có khả năng chứa tổng trọng lượng tối đa là $W$. Nếu tổng trọng lượng vượt quá $W$, túi sẽ rách và không thể mang được gì cả.

Sau khi nhét đầy túi, hắn nghĩ: “Tay còn lại có thể cầm thêm một món đồ nữa”. Do đó, hắn có thể lấy thêm một món đồ nữa miễn là trọng lượng của món đó không vượt quá $H$.

Nhiệm vụ của bạn là tìm giá trị lớn nhất tổng giá trị các món đồ tên trộm có thể mang đi (gồm cả trong túi và một món cầm tay).

### Dữ liệu vào

- Dòng đầu tiên chứa ba số nguyên dương $N, W, H$ $(1 \leq N \leq 100, 1 \leq W, H \leq 10^9)$.
- $N$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $w_i, c_i$ $(1 \leq w_i \leq 10^9, 1 \leq c_i \leq 10^3)$ — trọng lượng và giá trị của món đồ thứ $i$.

### Dữ liệu ra

- Một dòng duy nhất in ra tổng giá trị lớn nhất có thể đạt được.

### Sample Input 1

    3 10 2
    2 5
    1 9
    4 6

### Sample Output 1

    20

### Sample Input 2

    3 2 4
    2 5
    1 9
    4 6

### Sample Output 2

    15

### Giải thích

- Ở ví dụ 1: Tên trộm có thể cho hết 3 món vào túi (tổng trọng lượng là 7 < 10), tổng giá trị là $5 + 9 + 6 = 20$.
- Ở ví dụ 2: Hắn có thể cho món đồ thứ 2 (trọng lượng 1, giá trị 9) vào túi, và món đồ thứ 3 (trọng lượng 4, giá trị 6) cầm bằng tay (vì trọng lượng $4 ≤ H = 4$). Tổng giá trị là $9 + 6 = 15$.
