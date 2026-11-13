# DTBANKSMALL — Phân bổ ít gói kích cầu

### Đề bài

Chính phủ có $n$ công trình, công trình thứ $i$ cần đúng $a_i$ triệu đồng, và $m$ gói kích cầu, gói thứ $j$ có giá trị $b_j$ triệu đồng.

Mỗi gói có thể được cấp nguyên vẹn cho đúng một công trình hoặc không sử dụng. Không được chia nhỏ một gói. Tổng giá trị các gói cấp cho công trình thứ $i$ phải bằng đúng $a_i$.

Hãy đếm số phương án phân bổ đủ tiền cho tất cả công trình, lấy phần dư khi chia cho $10^9+7$. Các công trình được phân biệt theo chỉ số, các gói cũng được phân biệt theo chỉ số dù có cùng giá trị. Hai phương án khác nhau nếu có một gói được dùng cho công trình khác hoặc được sử dụng trong phương án này nhưng không sử dụng trong phương án kia.

Trong phiên bản này, số gói kích cầu không vượt quá $10$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $T$, số bộ dữ liệu.
- Với mỗi bộ dữ liệu, dòng đầu chứa hai số nguyên $n,m$.
- Dòng tiếp theo chứa $n$ số nguyên $a_1,a_2,\ldots,a_n$.
- Dòng tiếp theo chứa $m$ số nguyên $b_1,b_2,\ldots,b_m$.

### Dữ liệu ra

In $T$ dòng. Dòng thứ $k$ chứa số phương án của bộ dữ liệu thứ $k$, lấy phần dư khi chia cho $10^9+7$.

### Ràng buộc

- $1\le T\le3$.
- $1\le n\le m\le10$.
- $1\le a_i,b_j\le10^9$.

### Sample Input 1

```text
1
3 4
1 1 2
1 1 1 2
```

### Sample Output 1

```text
6
```

### Sample Input 2

```text
2
3 3
1 1 1
1 1 1
2 3
3 3
3 3 3
```

### Sample Output 2

```text
6
6
```

### Giải thích

Ở ví dụ 1, công trình thứ ba phải nhận gói thứ tư. Hai công trình đầu lần lượt chọn hai trong ba gói giá trị $1$, nên có $3\cdot2=6$ phương án; gói còn lại không dùng.

Ở ví dụ 2, bộ dữ liệu đầu có $3!=6$ cách cấp ba gói cho ba công trình. Bộ dữ liệu sau có $3\cdot2=6$ cách chọn một gói cho mỗi công trình; một gói không dùng.

### Nguồn

Bài tự biên soạn, phiên bản luyện tập trước BANK3 — Ngân sách, dựa trên `bank3.pdf` do người dùng cung cấp.
