# DPSTR153 — Thông điệp chung của nhiều bản ghi

### Đề bài

Cho $K$ xâu chữ thường $S_1,S_2,\ldots,S_K$. Hãy tìm độ dài lớn nhất của một xâu $T$ là dãy con của **tất cả** $K$ xâu đã cho.

Một xâu $T$ là **dãy con** của xâu $S$ nếu có thể thu được $T$ bằng cách xóa một số ký tự của $S$ và giữ nguyên thứ tự các ký tự còn lại. Các ký tự được giữ **không bắt buộc liên tiếp**. Mỗi lần xuất hiện chỉ được sử dụng một lần; các chữ giống nhau ở những vị trí khác nhau vẫn là các lần xuất hiện riêng biệt.

Đề bảo đảm có ít nhất một xâu dài không quá $20$ ký tự; xâu đó có thể nằm ở vị trí bất kỳ trong dữ liệu vào. Các xâu còn lại có thể dài hơn. Không có điều kiện về số lần xuất hiện của mỗi chữ cái.

Xâu rỗng là dãy con của mọi xâu và có độ dài $0$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $K$.
- Trong $K$ dòng tiếp theo, dòng thứ $i$ chứa xâu $S_i$.

### Dữ liệu ra

In độ dài dãy con chung dài nhất của tất cả $K$ xâu.

### Ràng buộc

- $2\le K\le40$.
- $1\le |S_i|\le100000$ với mọi $1\le i\le K$.
- $\sum_{i=1}^{K}|S_i|\le100000$.
- $\min_{1\le i\le K}|S_i|\le20$.
- Mỗi xâu chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
3
abcde
acebd
azced
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
3
aaaa
bbbb
abab
```

### Sample Output 2

```text
0
```

### Sample Input 3

```text
3
ab
ba
a
```

### Sample Output 3

```text
1
```

### Giải thích

Ở ví dụ 1, có thể chọn `ace`, là dãy con của cả ba xâu và có độ dài $3$; không có dãy con chung dài hơn.

Ở ví dụ 2, hai xâu đầu không có ký tự chung nên đáp án của cả ba xâu là $0$.

Ở ví dụ 3, chọn `a` được độ dài $1$. Xâu ngắn nhất nằm ở dòng cuối, không phải xâu đầu tiên. Không thể lấy độ dài lớn hơn $1$ vì xâu cuối chỉ có một ký tự.
