### Đề bài

Bố bạn Hùng là một nhà đầu tư tài chính. Ông có chiến lược đầu tư bằng cách chọn đúng $k$ thời điểm trong chuỗi số liệu thị trường gồm $n$ ngày. Mỗi ngày có chỉ số thị trường $a_i$.

Ông đã thiết lập chiến lược với các trọng số đầu tư $w_1, w_2, ..., w_k$ tương ứng với thứ tự các ngày đầu tư (tức là ngày được chọn thứ nhất sẽ nhân với $w_1$, ngày được chọn thứ hai nhân với $w_2$, ...).

Hãy chọn ra $k$ ngày khác nhau (theo thứ tự thời gian) sao cho lợi nhuận tổng $S$ là lớn nhất, với công thức:

$$
S = w_1 \times a_{i_1} + w_2 \times a_{i_2} + \dots + w_k \times a_{i_k}
$$

Biết rằng $i_1 < i_2 < \dots < i_k$

Ngoài ra, cũng cần đếm số cách chọn $k$ ngày để đạt lợi nhuận lớn nhất.

### Dữ liệu vào

- Dòng đầu tiên: hai số nguyên $n, k$ $(n \leq 10^5, k \leq 100, k \leq n)$
- Dòng thứ hai: $n$ số nguyên $a_1, a_2, ..., a_n$ $(a_i \leq 10^9)$ — chỉ số thị trường mỗi ngày
- Dòng thứ ba: $k$ số nguyên $w_1, w_2, ..., w_k$ $(w_i \leq 10^6)$ — trọng số đầu tư

### Dữ liệu ra

Ghi ra 2 dòng:

- Dòng đầu: tổng lợi nhuận lớn nhất có thể đạt được
- Dòng thứ hai: số cách chọn $k$ ngày để đạt tổng lợi nhuận lớn nhất đó.
- Các kết quả được lấy dư cho $10^9 + 7$.

### Sample Input

```
5 3
2 8 6 3 3
5 2 6
```

### Sample Output

```
70
2
```

### Giải thích

Có 2 cách chọn 3 ngày:
- Ngày thứ 2, 3, 4 → $5×8 + 2×6 + 6×3 = 70$
- Ngày thứ 2, 3, 5 → $5×8 + 2×6 + 6×3 = 70$

### Giới hạn

- 20% số test: $n \leq 10^2, k = 1$
- 40% số test: $n \leq 10^3, k \leq 100$
- 40% số test: $n \leq 10^5, k \leq 100$
