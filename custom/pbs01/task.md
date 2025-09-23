### Đề bài

Cho một dãy số nguyên $A$ gồm $N$ phần tử. Bạn cần thực hiện lần lượt $Q$ truy vấn thuộc một trong hai loại sau:

- `1 l v`: Thay đổi $A_l$ thành $v$.
- `2 l r k`: Trả về giá trị của phần tử nhỏ thứ $k$ trong đoạn $A[l..r]$.

### Dữ liệu vào

- Dòng đầu chứa một số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên, là các phần tử của dãy $A$.
- Dòng thứ ba chứa một số nguyên $Q$.
- $Q$ dòng tiếp theo mỗi dòng chứa một truy vấn theo định dạng đã nêu ở trên.

### Dữ liệu ra

- Đối với mỗi truy vấn loại 2, in ra giá trị của phần tử nhỏ thứ $k$ trong đoạn $A[l..r]$.

### Giới hạn

- $1 \le N, Q \le 10^5$
- $1 \le A_i, v \le 10^9$
- $1 \le l \le r \le N$
- $1 \le k \le r - l + 1$

### Sample Input

```
5
1 2 3 4 5
3
2 2 4 2
1 3 6
2 2 4 2
```

### Sample Output

```
3
4
```