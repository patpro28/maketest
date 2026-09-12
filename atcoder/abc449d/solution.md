### Ý tưởng giải

Xét bài toán con khi $L = D = 0$ (và $R, U \ge 0$). Khi đó, ta cần đếm số điểm nguyên $(x, y)$ thỏa mãn:
$$
0 \le x \le R,\quad 0 \le y \le U
$$
mà được tô màu đen.

Không mất tính tổng quát, giả sử $R \le U$. Trường hợp $R > U$ xử lý tương tự nhờ đối xứng.

Ta chia bài toán thành hai phần:
- $0 \le y \le R$
- $R < y \le U$

### Trường hợp $0 \le y \le R$

Một điểm $(x, y)$ là màu đen khi $\max(x, y)$ là số chẵn.

Xét một số chẵn $k$ với $0 \le k \le R$. Các điểm có $\max(x, y) = k$ thỏa:
- $x = k$, khi đó $y$ có thể nhận $k+1$ giá trị từ $0$ đến $k$
- $y = k$, khi đó $x$ có thể nhận $k+1$ giá trị từ $0$ đến $k$

Tổng cộng là $2(k+1)$ điểm, nhưng trừ đi điểm trùng $(k, k)$:
$$
2(k+1) - 1 = 2k + 1
$$

Gọi $p$ là số chẵn lớn nhất không vượt quá $R$. Khi đó tổng số điểm đen là:
$$
(2\cdot 0 + 1) + (2\cdot 2 + 1) + \cdots + (2p + 1)
$$

Đây là cấp số cộng:
$$
= \left(\frac{p}{2} + 1\right)(p + 1)
$$

### Trường hợp $R < y \le U$

Vì $0 \le x \le R < y$, nên:
$$
\max(x, y) = y
$$

Do đó màu của điểm chỉ phụ thuộc vào tính chẵn lẻ của $y$.

Với mỗi giá trị $y$, có $R+1$ điểm tương ứng.

Gọi $q$ là số lượng số chẵn trong đoạn $(R, U]$. Khi đó số điểm đen là:
$$
q \cdot (R + 1)
$$

### Kết luận

Ta thu được công thức tính số điểm đen cho bài toán con $L = D = 0$.

Bài toán tổng quát có thể đưa về bài toán này bằng cách:
- Dùng đối xứng
- Áp dụng nguyên lý bao hàm - loại trừ

### Độ phức tạp

$$
O(1)
$$