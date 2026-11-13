# DPSTR151 — Giới hạn nguyên âm

### Đề bài

Cho hai xâu chữ thường $A,B$ và số nguyên $K$. Hãy tìm độ dài lớn nhất của một dãy con chung chứa không quá $K$ nguyên âm. Các nguyên âm là `a`, `e`, `i`, `o`, `u`; các chữ cái thường khác là phụ âm.

Số nguyên âm được tính theo số lần xuất hiện, không phải số loại nguyên âm khác nhau. Được phép chọn xâu rỗng, có độ dài $0$.

Một xâu $T$ là **dãy con** của xâu $S$ nếu có thể thu được $T$ bằng cách xóa một số ký tự của $S$, có thể không xóa ký tự nào, và giữ nguyên thứ tự các ký tự còn lại. Các ký tự được giữ không bắt buộc nằm liên tiếp. Xâu rỗng là dãy con của mọi xâu.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,M,K$, trong đó $N,M$ lần lượt là độ dài của $A,B$.
- Dòng thứ hai chứa xâu $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu $B$ có đúng $M$ ký tự.

### Dữ liệu ra

In độ dài lớn nhất của dãy con chung chứa không quá $K$ nguyên âm.

### Ràng buộc

- $1\le N,M\le 200$.
- $A,B$ chỉ gồm các chữ cái thường từ `a` đến `z`.
- $0\le K\le5$.

### Sample Input 1

```text
5 5 1
abcde
abcde
```

### Sample Output 1

```text
4
```

### Sample Input 2

```text
3 3 0
aei
aei
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, giữ `abcd` được độ dài $4$ với một nguyên âm `a`. Không thể giữ cả năm ký tự vì xâu có hai nguyên âm. Ở ví dụ 2, không được chọn nguyên âm nào trong khi tất cả ký tự đều là nguyên âm, nên đáp án là $0$.
