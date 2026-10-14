### Đề bài

Trong một phòng thí nghiệm nghiên cứu năng lượng, các nhà khoa học đang thử nghiệm một hệ thống gồm $N$ lõi năng lượng được sắp xếp thành một hàng. Lõi năng lượng thứ $i$ có mức năng lượng là $A_i$.

Để duy trì sự ổn định của hệ thống, các nhà khoa học cần tìm ra **hai cặp lõi năng lượng có tổng năng lượng bằng nhau**.

Cụ thể, họ cần chọn bốn lõi năng lượng tại các vị trí $a,b,c,d$ thỏa mãn:

$$1\le a<b<c<d\le N$$

Đồng thời, tổng năng lượng của hai lõi đầu tiên phải bằng tổng năng lượng của hai lõi cuối cùng:

$$A_a+A_b=A_c+A_d$$

Mỗi cách chọn bốn vị trí khác nhau được tính là một phương án, ngay cả khi các lõi năng lượng có giá trị giống nhau.

Hãy giúp các nhà khoa học **đếm số phương án** thỏa mãn yêu cầu trên.

### Dữ liệu vào

- Dòng đầu tiên chứa số nguyên $N$ $(4\le N\le1000)$, là số lượng lõi năng lượng.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$ $(|A_i|\le10^9)$, trong đó $A_i$ là mức năng lượng của lõi thứ $i$.

### Dữ liệu ra

In ra một số nguyên duy nhất là **số cách chọn bốn vị trí** $a<b<c<d$ sao cho:

$$A_a+A_b=A_c+A_d$$

### Ví dụ

:::samples

:::sample
```input
5
1 6 2 5 3
```

```output
2
```
:::

:::

### Giải thích

Có hai cách chọn bốn lõi năng lượng thỏa mãn yêu cầu:

- **Cách 1:** Chọn các vị trí $(a,b,c,d)=(1,2,3,4)$.

    Khi đó:

    $$A_1+A_2=1+6=7$$

    $$A_3+A_4=2+5=7$$

- **Cách 2:** Chọn các vị trí $(a,b,c,d)=(2,3,4,5)$.

    Khi đó:

    $$A_2+A_3=6+2=8$$

    $$A_4+A_5=5+3=8$$

Vậy có tất cả $2$ phương án thỏa mãn.

### Giới hạn

Trong tất cả các bộ dữ liệu:

- $4\le N\le1000$.
- $|A_i|\le10^9$.

**Các nhóm test:**

- **Subtask 1 (40% số điểm):** $4\le N\le100$.
- **Subtask 2 (60% số điểm):** $4\le N\le1000$.
