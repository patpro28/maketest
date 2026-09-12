Để xử lý thuận tiện biểu thức $\max(|x|, |y|)$, ta chia các điểm thành hai nhóm:
- $|x| > |y|$
- $|x| \le |y|$

Sau đó tính riêng từng nhóm và cộng lại để được kết quả cuối cùng.

Ở đây, ta mô tả cách đếm các điểm thỏa mãn $|x| > |y|$. Trường hợp còn lại làm tương tự.

### Trường hợp $|x| > |y|$

Khi đó:
$$
\max(|x|, |y|) = |x|
$$

Do đó, điểm $(x, y)$ là màu đen khi $|x|$ là số chẵn.

Ta duyệt tất cả các giá trị $x$ chẵn trong đoạn $L \le x \le R$.

Với mỗi $x$, ta cần đếm số $y$ thỏa:
- $|x| > |y|$
- $D \le y \le U$

Điều kiện $|x| > |y|$ tương đương:
$$
-|x| < y < |x|
$$

Kết hợp với điều kiện biên, ta có:
$$
\max(-|x| + 1, D) \le y \le \min(|x| - 1, U)
$$

Số lượng giá trị $y$ thỏa mãn là:
$$
\max\Big(0,\ \min(|x| - 1, U) - \max(-|x| + 1, D) + 1\Big)
$$

Biểu thức này có thể tính trong $O(1)$ cho mỗi $x$.

### Độ phức tạp

Vì ta duyệt qua các giá trị $x$ trong đoạn $[L, R]$, nên độ phức tạp là:
$$
O(R - L)
$$

Tương tự, ta xử lý phần $|x| \le |y|$ và cộng hai kết quả lại để được đáp án.