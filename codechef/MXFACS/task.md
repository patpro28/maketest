### Đề bài

Cho một số nguyên dương $N$. Gọi $K$ là một ước của $N$ thỏa mãn $K > 1$, và đặt $M = \dfrac{N}{K}$.
Nhiệm vụ của bạn là **tìm giá trị nhỏ nhất của $K$** sao cho **$M$ có số lượng ước số là lớn nhất có thể**.

### Dữ liệu vào

* Dòng đầu tiên chứa số nguyên $T$ — số lượng bộ test.
* Mỗi bộ test gồm một dòng duy nhất chứa số nguyên $N$.

### Dữ liệu ra

* Với mỗi test, in ra **một số nguyên duy nhất** — giá trị nhỏ nhất của $K$ sao cho $M$ có nhiều ước nhất.

### Giới hạn

* $1 \le T \le 3000$
* $2 \le N \le 10^9$

### Sample Input

```
3
3
4
6
```

### Sample Output

```
3
2
2
```

### Giải thích

* **Test case 1**: Chỉ có duy nhất một số $K$ thỏa mãn là $3$.
* **Test case 2**: Có $2$ giá trị $K > 1$ là $2,4\to M=2,1$ có số ước lần lượt là $2,1$ do đó kết quả là $K=2$.
* **Test case 3**: Có $3$ giá trị $K > 1$ là $2,3,6\to M=3,2,1$ có số ước lần lượt là $2,2,1$ chọn $K$ nhỏ nhất là $2$.
