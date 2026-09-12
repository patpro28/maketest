### Đề bài

Trong một trò chơi mô phỏng rạp chiếu phim, có tổng cộng $2N+1$ vị trí được xếp thành một hàng thẳng, đánh số từ $1$ đến $2N+1$ theo thứ tự từ trái sang phải.

Hiện tại:

- Các vị trí có số lẻ $1, 3, 5, \ldots, 2N+1$ đã có người ngồi.
- Các vị trí có số chẵn $2, 4, 6, \ldots, 2N$ đang trống.

Với mỗi $i = 1, 2, \ldots, N+1$, người ngồi tại vị trí $2i-1$ có mức độ náo nhiệt là $A_i$.

Nếu người chơi chọn ngồi vào một vị trí trống, thì **độ ồn** của vị trí đó được xác định là **giá trị lớn nhất** giữa mức độ náo nhiệt của hai người ngồi ở hai vị trí kề bên trái và phải.  
Cụ thể:

- Độ ồn của vị trí $2$ là $\max(A_1, A_2)$.
- Độ ồn của vị trí $4$ là $\max(A_2, A_3)$, và tiếp tục như vậy.

Người chơi muốn chọn một vị trí trống sao cho **độ ồn là nhỏ nhất có thể** để có trải nghiệm tốt nhất.

Hãy xác định giá trị độ ồn nhỏ nhất có thể đạt được.

### Dữ liệu vào

- Dòng đầu tiên chứa số nguyên $T$ — số lượng test.
- Mỗi test gồm hai dòng:
  - Dòng thứ nhất chứa số nguyên $N$.
  - Dòng thứ hai chứa $N+1$ số nguyên $A_1, A_2, \ldots, A_{N+1}$.

### Dữ liệu ra

Với mỗi test, in ra trên một dòng một số nguyên — độ ồn nhỏ nhất có thể đạt được khi chọn một vị trí trống.

### Ràng buộc

- $1 \le T \le 100$
- $1 \le N \le 100$
- $1 \le A_i \le 100$

### Sample Input 1
    3
    1
    4 5
    2
    6 2 10
    4
    20 2 8 19 7

### Sample Output 1
    5
    6
    8

### Giải thích

- **Test 1:**  
  Chỉ có thể chọn vị trí $2$, với độ ồn $\max(4, 5) = 5$.

- **Test 2:**  
  Có thể chọn vị trí $2$ với độ ồn $\max(6, 2) = 6$ hoặc vị trí $4$ với độ ồn $\max(2, 10) = 10$. Giá trị nhỏ nhất là $6$.

- **Test 3:**  
  Các vị trí trống tạo ra các độ ồn lần lượt là $\max(20, 2)$, $\max(2, 8)$, $\max(8, 19)$ và $\max(19, 7)$. Trong các giá trị này, độ ồn nhỏ nhất là $8$.