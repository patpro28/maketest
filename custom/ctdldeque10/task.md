### Đề bài

Kỳ học kéo dài $n$ ngày. Cô giáo của Long giao bài tập về nhà hằng ngày và bắt buộc phải nộp bài tập vào ngày hôm sau. Long biết rằng số phút cần thiết để hoàn thành bài tập vào ngày thứ $i$ là $H_i$.

Long ghét bài tập và muốn dành ít thời gian nhất có thể để làm. May mắn thay, Long có thể hack hồ sơ của trường vào bất kỳ ngày nào để làm bài tập được giao. Tuy nhiên, để tránh bị nghi ngờ, Long sẽ không hack hồ sơ quá $k$ ngày liên tục.

Bạn có thể giúp Long tìm tổng số phút nhỏ nhất mà Long cần để làm bài tập không?

### Dữ liệu vào

- Dòng đầu tiên chứa số nguyên $T$ — số lượng bộ test.
- Mỗi bộ test bao gồm:
  - Dòng đầu tiên chứa hai số nguyên $n$ và $k$ — số ngày trong kỳ học và số ngày liên tiếp tối đa Long có thể hack.
  - Dòng tiếp theo chứa $n$ số nguyên $H_1, H_2, \dots, H_n$ — thời gian làm bài tập mỗi ngày.

### Dữ liệu ra

- Với mỗi bộ test, in ra một dòng chứa một số nguyên là tổng số phút nhỏ nhất Long cần để làm bài tập.

### Giới hạn

- $1 \leq T \leq 10^5$
- $1 \leq n \leq 10^6$
- $1 \leq k \leq n$
- $0 \leq H_i \leq 10^3$ với mọi $1 \leq i \leq n$
- Tổng của $n$ trong tất cả các bộ test không vượt quá $10^6$

### Sample Input

    3
    7 3
    213 124 156 263 149 6 62
    7 1
    476 457 232 130 849 95 749
    7 2
    601 35 45 304 449 452 190

### Sample Output

    130
    682
    484

### Giải thích

- **Test 1**: Long làm bài tập vào ngày $2$ và $6$, tổng thời gian là $H_2 + H_6 = 124 + 6 = 130$ phút. Số ngày liên tiếp nhiều nhất Long hack là $3$ (ngày $3$, $4$, $5$), không vượt quá $k = 3$.
- **Test 2**: Long làm bài tập vào ngày $2$, $4$ và $6$, tổng thời gian là $H_2 + H_4 + H_6 = 457 + 130 + 95 = 682$ phút.
- **Test 3**: Long làm bài tập vào ngày $2$ và $5$, tổng thời gian là $H_2 + H_5 = 35 + 449 = 484$ phút.
