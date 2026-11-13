# DPSTR131 — Bảo tồn ký tự quý

### Đề bài

Cho hai xâu chữ thường $A$ dài $N$ và $B$ dài $M$. Chi phí xóa ký tự ở vị trí $i$ của $A$ là $U_i$; chi phí xóa ký tự ở vị trí $j$ của $B$ là $V_j$. Chi phí gắn với vị trí trong xâu ban đầu và không thay đổi khi xóa các ký tự khác.

Hãy xóa một số ký tự khỏi hai xâu để các xâu còn lại bằng nhau, với tổng chi phí nhỏ nhất. Được phép không xóa ký tự nào hoặc xóa hết cả hai xâu.

Một xâu $T$ là **dãy con** của xâu $S$ nếu có thể thu được $T$ bằng cách xóa một số ký tự của $S$, có thể không xóa ký tự nào, và giữ nguyên thứ tự các ký tự còn lại. Các ký tự được giữ không bắt buộc nằm liên tiếp. Xâu rỗng là dãy con của mọi xâu.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$, lần lượt là độ dài của $A,B$.
- Dòng thứ hai chứa xâu $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu $B$ có đúng $M$ ký tự.
- Dòng thứ tư chứa $N$ số nguyên $U_1,U_2,\ldots,U_N$.
- Dòng thứ năm chứa $M$ số nguyên $V_1,V_2,\ldots,V_M$.

### Dữ liệu ra

In tổng chi phí xóa nhỏ nhất.

### Ràng buộc

- $1\le N,M\le 600$.
- $A,B$ chỉ gồm các chữ cái thường từ `a` đến `z`.
- $0\le U_i,V_j\le10^9$ với mọi $1\le i\le N$, $1\le j\le M$.

### Sample Input 1

```text
2 2
ab
ba
100 1
1 100
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
3 1
aaa
a
5 9 2
4
```

### Sample Output 2

```text
7
```

### Giải thích

Ở ví dụ 1, xóa chữ `b` trong mỗi xâu, chi phí $1+1=2$, cả hai còn `a`. Ở ví dụ 2, giữ chữ `a` ở vị trí $2$ của xâu thứ nhất để ghép với xâu thứ hai; xóa hai vị trí còn lại tốn $5+2=7$.
