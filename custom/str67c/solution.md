## Ý tưởng

Chia $S$ thành các đoạn liên tiếp cực đại gồm cùng một ký tự. Vì An không nhấn cùng một phím hai lần liên tiếp, mỗi đoạn như vậy tương ứng với đúng một lần nhấn phím:

- Đoạn dài $1$: phím tương ứng hoạt động bình thường.
- Đoạn dài $2$: phím tương ứng bị hỏng.

Dùng mảng đánh dấu gồm $26$ phần tử, ban đầu đều bằng `false`. Duyệt các đoạn; nếu đoạn dài $1$, đánh dấu ký tự của đoạn. Cuối cùng duyệt từ `a` đến `z` và in các ký tự đã đánh dấu, sau đó xuống dòng, kể cả khi không có ký tự nào được in.

Không thể chỉ dựa vào tổng số lần xuất hiện của một ký tự: trong `cbddb`, phím `b` hoạt động bình thường dù xuất hiện hai lần.

## Chứng minh tính đúng đắn

Hai lần nhấn phím liên tiếp luôn ứng với hai ký tự khác nhau. Vì vậy, các ký tự sinh ra bởi hai lần nhấn liên tiếp không thể nằm trong cùng một đoạn ký tự giống nhau. Mỗi lần nhấn phím sinh ra một hoặc hai ký tự giống nhau, nên mỗi đoạn cực đại tương ứng với đúng một lần nhấn.

Nếu thuật toán đánh dấu ký tự $c$, tồn tại một đoạn dài $1$ gồm ký tự $c$. Lần nhấn tương ứng chỉ sinh ra một ký tự, nên phím $c$ hoạt động bình thường.

Ngược lại, nếu phím $c$ hoạt động bình thường và xuất hiện trong $S$, mỗi lần nhấn phím đó tạo một đoạn dài $1$, nên thuật toán đánh dấu $c$. Những ký tự không xuất hiện không được đánh dấu, đúng với quy ước của đề bài.

Do đó, mảng đánh dấu chứa chính xác các phím cần tìm. Duyệt mảng theo thứ tự bảng chữ cái in mỗi phím đúng một lần và theo đúng thứ tự yêu cầu.

## Độ phức tạp

Với mỗi bộ dữ liệu, thời gian là $O(|S|+26)$ và bộ nhớ phụ là $O(26)$.

## Cài đặt tham khảo

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        bool good[26] = {};
        for (int i = 0; i < (int)s.size();) {
            int j = i + 1;
            while (j < (int)s.size() && s[j] == s[i]) ++j;
            if (j - i == 1) good[s[i] - 'a'] = true;
            i = j;
        }
        for (int c = 0; c < 26; ++c)
            if (good[c]) cout << char('a' + c);
        cout << '\n';
    }
}
```
