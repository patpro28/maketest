# DPSTR600 — Hỏi đoạn đối xứng

### Đề bài

Cho xâu $S$ gồm $N$ chữ cái thường và $Q$ truy vấn. Mỗi truy vấn cho hai chỉ số $L,R$, yêu cầu xác định đoạn **liên tiếp** $S[L\ldots R]$ có đối xứng hay không. Xâu không thay đổi giữa các truy vấn. Các vị trí được đánh số từ $1$ đến $N$.

Một xâu là **đối xứng** nếu đọc từ trái sang phải và từ phải sang trái đều thu được cùng một xâu. Xâu một ký tự và xâu rỗng đều đối xứng.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ ký tự.
- Trong $Q$ dòng tiếp theo, mỗi dòng chứa hai số nguyên $L,R$ mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in `YES` nếu đoạn được hỏi đối xứng, ngược lại in `NO`. Mỗi kết quả nằm trên một dòng.

### Ràng buộc

- $1\le N\le5000$.
- $S$ chỉ gồm chữ cái thường từ `a` đến `z`.
- $1\le Q\le500000$; mỗi truy vấn thỏa $1\le L\le R\le N$.

### Sample Input 1

```text
4 4
abac
1 3
1 4
2 2
3 4
```

### Sample Output 1

```text
YES
NO
YES
NO
```

### Sample Input 2

```text
4 3
abba
1 4
2 3
1 2
```

### Sample Output 2

```text
YES
YES
NO
```

### Giải thích

Ở ví dụ 1, đoạn $[1,3]$ là `aba` nên đối xứng; đoạn $[1,4]$ là `abac` nên không đối xứng; đoạn $[2,2]$ có một ký tự; đoạn $[3,4]$ là `ac` nên không đối xứng. Ở ví dụ 2, `abba` và `bb` đối xứng, còn `ab` không đối xứng.
