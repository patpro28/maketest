### Đề bài

Một kho dữ liệu được lưu trên một bảng 3 chiều kích thước $X \times Y \times Z$. Mỗi ô $(x,y,z)$ chứa một số nguyên (có thể âm).  

Bạn được cho nhiều truy vấn, mỗi truy vấn mô tả một **hộp chữ nhật song song với trục tọa độ** bằng hai đỉnh đối nhau $(x_1,y_1,z_1)$ và $(x_2,y_2,z_2)$.  

Hãy tính tổng tất cả các phần tử $a[x][y][z]$ thỏa:
$$x_1 \le x \le x_2,\quad y_1 \le y \le y_2,\quad z_1 \le z \le z_2.$$

### Dữ liệu vào

- Dòng 1: ba số nguyên $X, Y, Z$ — kích thước của bảng.  
- Sau đó là $Z$ khối, mỗi khối tương ứng một lớp theo trục $z$ từ $1$ đến $Z$:  
  - Mỗi khối có $Y$ dòng, mỗi dòng gồm $X$ số nguyên — lần lượt là $a[1..X][1..Y][z]$.  
- Tiếp theo: một số nguyên $Q$ — số truy vấn.  
- $Q$ dòng tiếp theo, mỗi dòng gồm 6 số nguyên $x_1, y_1, z_1, x_2, y_2, z_2$ với $1 \le x_1 \le x_2 \le X$, $1 \le y_1 \le y_2 \le Y$, $1 \le z_1 \le z_2 \le Z$.

### Dữ liệu ra

- In ra $Q$ dòng, mỗi dòng là một số nguyên: tổng các phần tử trong hộp chữ nhật của truy vấn tương ứng.

### Giới hạn

- $1 \le X,Y,Z \le 100$  
- $1 \le Q \le 2 \times 10^5$  
- $|a[x][y][z]| \le 10^9$  
- Đảm bảo $X \cdot Y \cdot Z \le 10^6$  

### Sample Input
	3 2 2
	1 2 3
	4 5 6
	-1 0 7
	8 -3 2
	3
	1 1 1 3 2 2
	2 1 1 3 1 2
	1 2 2 3 2 2

### Sample Output
	34
	12
	7

### Giải thích

- Truy vấn 1: toàn bộ khối $3\times2\times2$, tổng $=34$.  
- Truy vấn 2: hộp $(2..3,1..1,1..2)$ gồm các phần tử $2,3,0,7$, tổng $=12$.  
- Truy vấn 3: hộp $(1..3,2..2,2..2)$ gồm hàng $[8,-3,2]$, tổng $=7$.  
