# SEGTREE220 — Cộng đoạn và lấy lớn nhất

### Đề bài

Cho dãy số nguyên $a_1,a_2,\dots,a_n$. Bạn cần thực hiện lần lượt $m$ thao tác thuộc một trong hai loại:

- `1 u v`: tìm và in giá trị lớn nhất trong các phần tử $a_u,a_{u+1},\dots,a_v$ của dãy hiện tại.
- `0 u v k`: cộng $k$ vào **từng phần tử** trong đoạn $[u,v]$. Nói cách khác, gán $a_i\leftarrow a_i+k$ với mọi $u\le i\le v$.

Giá trị $k$ có thể dương, âm hoặc bằng $0$. Nếu $k$ âm, thao tác làm giảm các phần tử trong đoạn. Mỗi thay đổi có hiệu lực đối với tất cả thao tác tiếp theo.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $n,m$.
- Dòng thứ hai chứa $n$ số nguyên $a_1,a_2,\dots,a_n$.
- Mỗi dòng trong $m$ dòng tiếp theo mô tả một thao tác theo định dạng `1 u v` hoặc `0 u v k`.

### Dữ liệu ra

Với mỗi thao tác loại `1`, in một số nguyên trên một dòng: giá trị phần tử lớn nhất trong đoạn được hỏi tại thời điểm đó.

Thao tác loại `0` không yêu cầu in kết quả.

### Ràng buộc

- $1\le n,m\le100000$.
- $-10000\le a_i\le10000$ ở thời điểm ban đầu.
- Với mọi thao tác: $1\le u\le v\le n$.
- Với thao tác loại `0`: $-10000\le k\le10000$.
- Giá trị các phần tử sau cập nhật có thể nằm ngoài khoảng $[-10000,10000]$.

### Sample Input 1

```text
6 3
0 0 0 0 0 0
0 1 3 3
0 4 6 4
1 1 6
```

### Sample Output 1

```text
4
```

### Sample Input 2

```text
4 7
-5 -2 -7 -4
1 1 4
0 1 2 -3
1 1 3
0 2 4 10
1 1 4
1 1 1
1 2 3
```

### Sample Output 2

```text
-2
-5
6
-8
5
```

### Giải thích

Ở ví dụ 1, sau hai thao tác cập nhật, dãy trở thành $[3,3,3,4,4,4]$. Giá trị lớn nhất trên đoạn $[1,6]$ là $4$.

Ở ví dụ 2:

- Ban đầu, giá trị lớn nhất trên đoạn $[1,4]$ là $-2$.
- Sau khi cộng $-3$ vào đoạn $[1,2]$, dãy là $[-8,-5,-7,-4]$. Giá trị lớn nhất trên đoạn $[1,3]$ là $-5$.
- Sau khi cộng $10$ vào đoạn $[2,4]$, dãy là $[-8,5,3,6]$. Ba truy vấn cuối lần lượt trả lời $6,-8,5$.
