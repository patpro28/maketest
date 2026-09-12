### Đề bài

Một nhà đầu tư bí ẩn đã thuê Hưng để quản lý bộ sưu tập băng video của mình. 
Có $N$ băng video, xếp theo thứ tự từ trái sang phải.

Băng thứ i có:
- độ dài $L_i$  
- loại $C_i$

Hưng phải xử lý $Q$ thao tác, theo đúng thứ tự. Mỗi thao tác thuộc một trong ba loại sau:

1. **Truy vấn**: Cho $l, r$, hãy tính tổng độ dài của các băng video trong đoạn $[l, r]$ sao cho băng đó là **băng trái nhất của loại đó trong đoạn**.  
   Tức là tính tổng các $L_i$ với $i \in [l, r]$ thỏa mãn **không tồn tại** $j$ sao cho $l \le j < i$ và $C_j = C_i$.

2. **Cập nhật độ dài**: Cho $x, y$, đặt:
   $$L_x := y$$

3. **Cập nhật loại**: Cho $x, y$, đặt:
   $$C_x := y$$

**Lưu ý về input** (truy vấn bị mã hoá):  
Gọi $last_i$ là kết quả của truy vấn loại 1 gần nhất trước truy vấn thứ i. Nếu không có thì $last_i=0$.

- Với truy vấn dạng `1 a b`: đặt  
  $$l = a \oplus last_i,\quad r = b \oplus last_i$$
- Với truy vấn dạng `2 a b`: đặt  
  $$x = a \oplus last_i,\quad y = b \oplus last_i$$
- Với truy vấn dạng `3 a b`: đặt  
  $$x = a \oplus last_i,\quad y = b \oplus last_i$$

### Dữ liệu vào

- Dòng 1: hai số nguyên $N, Q$  
- $N$ dòng tiếp theo: mỗi dòng chứa $L_i, C_i$  
- $Q$ dòng tiếp theo là các truy vấn ở dạng đã mã hoá như mô tả.

### Dữ liệu ra

Với mỗi truy vấn loại 1, in ra kết quả trên một dòng.

### Ràng buộc

- $1 \le N, Q \le 10^5$
- $1 \le L_i, y \le 10^4$
- $1 \le C_i, x \le N$
- $1 \le l \le r \le N$

### Sample Input 1
    6 6
    2 5
    6 1
    4 3
    1 3
    1 4
    1 1
    1 3 6
    2 0 2
    1 5 5
    3 6 5
    2 2 6
    1 5 2

### Sample Output 1
    6
    4
    13

