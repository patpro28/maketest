# DTPALORDER — Cắt theo đúng thứ tự

### Đề bài

Cho xâu $S$ gồm các chữ cái La tinh thường và $k$ số nguyên dương $l_1,l_2,\ldots,l_k$.

Hãy chọn $k$ đoạn của $S$, theo thứ tự từ trái sang phải, sao cho đoạn thứ $i$ có độ dài đúng $l_i$ và là xâu đối xứng. Một xâu đối xứng đọc từ trái sang phải giống như đọc từ phải sang trái.

Mỗi đoạn gồm các ký tự ở những vị trí liên tiếp trong $S$. Các đoạn được chọn đôi một không giao nhau và **không bắt buộc nằm sát nhau**: giữa hai đoạn có thể có các ký tự không được chọn. Được phép bỏ ký tự ở đầu và cuối xâu. Thứ tự các độ dài **phải giữ nguyên như đầu vào**.

Hãy xác định có cách chọn hay không và in một cách chọn nếu có.

### Dữ liệu vào

- Dòng đầu chứa xâu $S$.
- Dòng thứ hai chứa số nguyên $k$.
- Dòng thứ ba chứa $k$ số nguyên $l_1,l_2,\ldots,l_k$.

### Dữ liệu ra

Nếu không thể chọn, in `NO`.

Nếu có thể chọn, dòng đầu in `YES`. Trong $k$ dòng tiếp theo, dòng thứ $i$ in hai chỉ số $L_i,R_i$ của đoạn thứ $i$, đánh số từ $1$. Cần có $1\le L_i\le R_i\le |S|$, $R_i-L_i+1=l_i$ và $R_i<L_{i+1}$ với mọi $i<k$. Mỗi đoạn phải đối xứng. Nếu có nhiều đáp án, in một đáp án bất kỳ.

### Ràng buộc

- $1\le n=|S|\le200000$.
- $1\le k\le200000$.
- $1\le l_i\le200000$.
- $S$ chỉ gồm các chữ cái từ `a` đến `z`.

### Sample Input 1

```text
abacdc
2
3 3
```

### Sample Output 1

```text
YES
1 3
4 6
```

### Sample Input 2

```text
abba
2
3 1
```

### Sample Output 2

```text
NO
```

### Giải thích

Ở ví dụ 1, hai đoạn `aba` và `cdc` đều đối xứng và có độ dài $3$.

Ở ví dụ 2, xâu không có đoạn đối xứng dài $3$, nên không thể đáp ứng yêu cầu đầu tiên.
