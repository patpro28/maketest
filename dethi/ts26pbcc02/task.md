### Đề bài

Trong một trò chơi tìm "Hộp quà may mắn", mỗi đội chơi được cung cấp một xâu $S$ gồm các ký tự số. Nhiệm vụ là tìm các xâu con liên tiếp tạo thành **số đặc biệt**.

**Định nghĩa số đặc biệt**:

- Là số chia hết cho $97$
- Và tổng các chữ số chia hết cho $3$
- Cho phép các số có chữ số $0$ đứng đầu.

Hãy viết chương trình đếm có bao nhiêu xâu con liên tiếp trong $S$ tạo thành một số đặc biệt.

### Dữ liệu vào

- Một dòng duy nhất chứa xâu ký tự số $S$, độ dài $|S| \leq 10^5$

### Dữ liệu ra

- Một dòng duy nhất là số lượng xâu con liên tiếp tạo thành số đặc biệt.

### Sample Input

```

2910

```

### Sample Output

```

3

```

### Giải thích

Có 3 xâu con tạo thành số đặc biệt:
- `291` (chia hết 97, tổng chữ số 2+9+1=12 chia hết 3)
- `2910` (chia hết 97, tổng 2+9+1+0=12 chia hết 3)
- `0` (0 chia hết 97, tổng 0 chia hết 3)

### Giới hạn

- 50% số test ứng với $|S| \leq 300$
- 30% số test ứng với $|S| \leq 10^3$
- 20% số test ứng với $|S| \leq 10^5$
