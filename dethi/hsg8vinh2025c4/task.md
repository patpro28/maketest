### Đề bài

An đang chơi một trò chơi ở hội chợ gần nhà. Trong trò chơi, người ta đưa ra $N$ bảng điện tử, trong mỗi bảng có các giá trị lần lượt là $a_1, a_2, \ldots, a_N$. An được phép tăng/giảm một lượng giá trị tuỳ ý trên các bảng từ vị trí $L$ đến vị trí $R$, khi đó giá trị trên các bảng này sẽ cùng tăng/giảm một lượng giá trị như nhau. Điểm số của người chơi là số lượng bảng có cùng giá trị với nhau. Em hãy cho biết điểm số cao nhất An có thể đạt được.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N, L, R$ $(1 \le N \le 10^5, 1 \le L \le R \le N)$.
- Dòng thứ hai chứa $N$ số nguyên $a_1, a_2, \ldots, a_N$ $(1 \le a_i \le 10^9)$.

### Dữ liệu ra

- Một số nguyên duy nhất là điểm số cao nhất An có thể đạt được.

### Sample Input

```
7 5 7
3 1 3 3 4 4 3
```

### Sample Output

```
5
```

### Giải thích

Giảm đi 1 cho đoạn $[5,7]$ ta sẽ được $3,1,3,3,3,3,2$ và có $5$ bảng có giá trị bằng $3$.
