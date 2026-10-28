# TRAMTIEPTE — Trạm tiếp tế

### Đề bài

Có $N$ khu dân cư, được đánh số từ $1$ đến $N$, nối với nhau bằng $N-1$ con đường hai chiều tạo thành một cây. Mỗi con đường có độ dài nguyên dương. Gọi $d(u,v)$ là tổng độ dài các con đường trên đường đi duy nhất từ khu $u$ đến khu $v$.

Khu $i$ cần nhận $A_i$ kiện hàng. Bạn phải xây **đúng một** trạm tiếp tế tại một khu dân cư. Phí xây trạm tại khu $u$ là $B_u$. Chi phí vận chuyển một kiện hàng từ trạm tới khu $i$ bằng $d(u,i)$; các kiện hàng được tính phí độc lập.

Nếu đặt trạm tại $u$, tổng chi phí là

$$B_u+\sum_{i=1}^{N} A_i\,d(u,i).$$

Hãy chọn vị trí đặt trạm để tổng chi phí nhỏ nhất. Nếu có nhiều vị trí cùng đạt chi phí nhỏ nhất, chọn khu có chỉ số nhỏ nhất. Kể cả khi mọi $A_i$ đều bằng $0$, bạn vẫn phải xây một trạm.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.
- Dòng thứ ba chứa $N$ số nguyên $B_1,B_2,\ldots,B_N$.
- Trong $N-1$ dòng tiếp theo, mỗi dòng chứa ba số nguyên $u,v,W$, mô tả con đường hai chiều nối $u$ với $v$ có độ dài $W$.

### Dữ liệu ra

In hai số nguyên trên một dòng: chỉ số khu được chọn và tổng chi phí nhỏ nhất.

### Ràng buộc

- $1\le N\le 2\cdot10^5$.
- $0\le A_i\le 1000$.
- $0\le B_i\le 10^{15}$.
- $1\le u,v\le N$; $1\le W\le 1000$.
- Các con đường tạo thành một cây.
- Kết quả có thể vượt phạm vi số nguyên $32$ bit; dùng số nguyên có dấu $64$ bit.

### Sample Input 1

```text
4
1 2 1 0
0 5 0 0
1 2 2
2 3 1
2 4 3
```

### Sample Output 1

```text
3 5
```

### Sample Input 2

```text
2
1 1
0 0
1 2 7
```

### Sample Output 2

```text
1 7
```

### Sample Input 3

```text
1
0
1000000000000000
```

### Sample Output 3

```text
1 1000000000000000
```

### Giải thích

Ở ví dụ 1, tổng chi phí khi đặt trạm tại các khu $1,2,3,4$ lần lượt là $7,8,5,15$. Vì vậy chọn khu $3$.

Ở ví dụ 2, cả hai vị trí đều có tổng chi phí $7$, nên chọn khu $1$ theo quy tắc phá hòa.

Ở ví dụ 3, không cần vận chuyển hàng nhưng vẫn phải xây trạm tại khu duy nhất, với chi phí $10^{15}$.
