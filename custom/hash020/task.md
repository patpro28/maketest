### Đề bài

Cho $N$ xâu ký tự $S_1, S_2, \ldots, S_N$ chỉ gồm các chữ cái thường tiếng Anh.

Bạn cần chọn ra một **chỉnh hợp** (tức là chọn một số xâu và sắp xếp thứ tự của chúng) rồi ghép lại thành một xâu $T$.

Hãy đếm số cách chọn và sắp xếp các xâu sao cho xâu $T$ thu được là **xâu đối xứng** (palindrome).

Hai cách được coi là khác nhau nếu:

- Tập các xâu được chọn khác nhau, hoặc
- Thứ tự sắp xếp khác nhau.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- $N$ dòng tiếp theo, mỗi dòng chứa một xâu $S_i$.

### Dữ liệu ra

- In ra số cách thỏa mãn.

### Ràng buộc

- $1 \le N \le 10$
- $1 \le |S_i| \le 100$

### Sample Input 1

    3
    ab
    ba
    c

### Sample Output 1

    5

### Sample Input 2

    2
    abc
    def

### Sample Output 2

    0

### Giải thích

**Ví dụ 1:**

Các cách hợp lệ:
- Chọn $(ab, ba)$ → "abba"
- Chọn $(ba, ab)$ → "baab"
- Chọn $(c)$ → "c"
- Chọn $(ab, c, ba)$ → "abcba"
- Chọn $(ba, c, ab)$ → "bacab"

Tổng cộng $5$ cách.

**Ví dụ 2:**

Không có cách nào ghép thành xâu đối xứng.