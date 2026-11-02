# SEGTREE009 — Cặp hàng kề nhau rẻ nhất

### Đề bài

Có $N$ món hàng xếp thành một hàng. Món thứ $i$ có giá $A_i$.

Với mỗi truy vấn $[L,R]$, bạn muốn mua **đúng hai món nằm kề nhau**, và cả hai món đều phải thuộc đoạn $[L,R]$. Hãy tìm tổng giá nhỏ nhất có thể trả.

Hai món được chọn phải có chỉ số $i,i+1$ với $L\le i<R$. Không được chọn hai món chỉ vì chúng có giá nhỏ nhất nếu chúng không kề nhau. Nếu $L=R$, không thể chọn đủ hai món và bạn cần trả lời $-1$.

Có $Q$ truy vấn. Giá và thứ tự các món hàng không thay đổi trong suốt các truy vấn.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\dots,A_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa hai số nguyên $L,R$, mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in tổng giá nhỏ nhất của hai món kề nhau cùng thuộc đoạn, hoặc $-1$ nếu đoạn chỉ có một món. Mỗi câu trả lời nằm trên một dòng.

### Ràng buộc

- $1\le N,Q\le200000$.
- $0\le A_i\le10^9$.
- Với mỗi truy vấn: $1\le L\le R\le N$.

### Sample Input 1

```text
6 5
1 100 2 3 100 1
1 6
1 2
2 5
4 4
5 6
```

### Sample Output 1

```text
5
101
5
-1
101
```

### Sample Input 2

```text
4 4
1000000000 1000000000 0 0
1 2
2 4
2 3
3 4
```

### Sample Output 2

```text
2000000000
0
1000000000
0
```

### Giải thích

Ở ví dụ 1, trong đoạn $[1,6]$, cặp món ở vị trí $3,4$ có tổng giá $2+3=5$, là nhỏ nhất. Hai món có giá $1$ không kề nhau nên không thể chọn cùng nhau. Đoạn $[1,2]$ chỉ có một cặp, tổng giá $101$. Đoạn $[2,5]$ cũng chọn cặp $3,4$, tổng giá $5$. Đoạn $[4,4]$ trả lời $-1$. Cặp duy nhất trong đoạn $[5,6]$ có tổng giá $101$.

Ở ví dụ 2, tổng giá cặp trong đoạn $[1,2]$ là $2000000000$. Hai truy vấn $[2,4]$ và $[3,4]$ chọn cặp giá $0,0$, còn đoạn $[2,3]$ có tổng giá $1000000000$.
