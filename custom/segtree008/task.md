# SEGTREE008 — Tự do cho đàn kiến

### Đề bài

Trung nuôi $n$ con kiến, đánh số từ $1$ đến $n$. Con kiến thứ $i$ có sức mạnh là số nguyên dương $s_i$.

Với mỗi truy vấn, Trung chọn các con kiến có chỉ số từ $L$ đến $R$. Điểm của mỗi con kiến trong đoạn được tính riêng như sau:

- Ban đầu, mỗi con kiến có $0$ điểm.
- Xét con kiến $i$ với từng con kiến $j$ khác nó trong cùng đoạn. Nếu $s_j$ chia hết cho $s_i$, con kiến $i$ nhận $1$ điểm từ lần so sánh này.

Ví dụ, một con kiến có sức mạnh $2$ nhận được điểm khi so với con có sức mạnh $4$, vì $4$ chia hết cho $2$. Hai con kiến có cùng sức mạnh đều nhận được điểm khi so với nhau.

Trong đoạn có $R-L+1$ con kiến, nên mỗi con được so với đúng $R-L$ con khác. Một con kiến **được tự do** nếu nhận đủ $R-L$ điểm. Nói cách khác, mọi con kiến còn lại trong đoạn đều phải có sức mạnh chia hết cho sức mạnh của nó.

Hãy trả lời số con kiến **không được tự do** trong mỗi đoạn được hỏi.

Các truy vấn độc lập với nhau: sức mạnh và số lượng kiến không thay đổi sau mỗi truy vấn. Nếu $L=R$, con kiến duy nhất có đủ $0$ điểm và được tự do.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $n$, là số con kiến.
- Dòng thứ hai chứa $n$ số nguyên $s_1,s_2,\dots,s_n$.
- Dòng thứ ba chứa số nguyên $m$, là số truy vấn.
- Mỗi dòng trong $m$ dòng tiếp theo chứa hai số nguyên $L,R$, mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in một số nguyên trên một dòng: số con kiến không được tự do trong đoạn $[L,R]$.

### Ràng buộc

- $1\le n,m\le100000$.
- $1\le s_i\le10^9$.
- $1\le L\le R\le n$.

### Sample Input 1

```text
5
1 3 2 4 2
4
1 5
2 5
3 5
4 5
```

### Sample Output 1

```text
4
4
1
1
```

### Sample Input 2

```text
3
6 10 15
3
1 3
1 2
2 2
```

### Sample Output 2

```text
3
2
0
```

### Giải thích

Ở ví dụ 1:

- Đoạn $[1,5]$ có các sức mạnh $1,3,2,4,2$. Chỉ con kiến có sức mạnh $1$ nhận điểm từ tất cả các con còn lại, nên có $4$ con không được tự do.
- Đoạn $[2,5]$ có các sức mạnh $3,2,4,2$. Không con nào nhận điểm từ tất cả các con còn lại, nên cả $4$ con đều không được tự do.
- Đoạn $[3,5]$ có các sức mạnh $2,4,2$. Cả hai con có sức mạnh $2$ đều nhận đủ $2$ điểm và được tự do. Chỉ con có sức mạnh $4$ không được tự do, nên đáp án là $1$.
- Đoạn $[4,5]$ có các sức mạnh $4,2$. Con có sức mạnh $2$ được tự do, con còn lại không được tự do, nên đáp án là $1$.

Ở ví dụ 2, trong cả đoạn $[1,3]$ lẫn đoạn $[1,2]$, không có con kiến nào có sức mạnh mà tất cả sức mạnh còn lại đều chia hết cho nó. Hai truy vấn này lần lượt trả lời $3$ và $2$. Đoạn $[2,2]$ chỉ có một con kiến nên trả lời $0$.
