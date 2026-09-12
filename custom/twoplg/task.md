### Đề bài

**Trò chơi Hai Kho Vật Phẩm**

Trong một trò chơi chiến thuật theo lượt, có hai người chơi là Alice và Bob cùng tham gia. Trên bàn ban đầu có hai loại vật phẩm:

- $X$ chiếc **bánh quy**,
- $Y$ chiếc **bánh kem**.

Alice là người đi trước, sau đó hai người luân phiên thực hiện lượt chơi của mình.

Ở mỗi lượt, người chơi **bắt buộc** phải thực hiện **đúng một** trong ba hành động sau (nếu hợp lệ):

1. Ăn một bánh quy  
   Khi đó số bánh quy giảm đi $1$, số bánh kem không đổi.

2. Ăn một bánh quy và một bánh kem  
   Khi đó cả số bánh quy và số bánh kem đều giảm đi $1$.

3. Ăn một bánh kem và đặt thêm một bánh quy lên bàn  
   Khi đó số bánh kem giảm đi $1$ và số bánh quy tăng lên $1$.

Tại mọi thời điểm, số lượng bánh quy và bánh kem trên bàn **không được âm**. Vì vậy, một hành động chỉ được phép thực hiện nếu các vật phẩm cần thiết còn tồn tại.

Người chơi **ăn miếng cuối cùng** (tức là sau lượt đó không còn bánh quy hay bánh kem nào trên bàn) sẽ là người chiến thắng.  
Cả Alice và Bob đều chơi tối ưu nhằm giành chiến thắng.

Với trạng thái ban đầu của bàn, hãy xác định **ai sẽ là người chiến thắng**.

### Dữ liệu vào

- Dòng đầu tiên chứa số nguyên $T$ — số lượng test.
- Mỗi test gồm một dòng chứa hai số nguyên $X$ và $Y$ — số bánh quy và bánh kem ban đầu.

### Dữ liệu ra

Với mỗi test, in ra trên một dòng:

- `Alice` nếu Alice là người chiến thắng khi cả hai chơi tối ưu.
- `Bob` nếu Bob là người chiến thắng khi cả hai chơi tối ưu.

### Ràng buộc

- $1 \le T \le 10^4$
- $0 \le X, Y \le 10^9$
- $X + Y \ge 1$

### Sample Input 1
    5
    2 0
    3 0
    0 1
    1 2
    4 8

### Sample Output 1
    Bob
    Alice
    Bob
    Alice
    Bob

### Giải thích

- **Test 1:**  
  Không có bánh kem nên mỗi lượt chỉ có thể ăn đúng một bánh quy. Với $X = 2$, Bob là người ăn miếng cuối cùng.

- **Test 2:**  
  Tương tự trường hợp trên nhưng với $X = 3$, Alice là người ăn miếng cuối cùng.

- **Test 3:**  
  Ban đầu chỉ có một bánh kem. Alice buộc phải ăn bánh kem và tạo ra một bánh quy. Bob ăn bánh quy đó ở lượt sau và chiến thắng.

- **Test 4:**  
  Alice có thể ăn đồng thời một bánh quy và một bánh kem, đưa trò chơi về trạng thái tương tự test 3 nhưng đến lượt Bob. Khi đó Bob không thể giành chiến thắng, nên Alice thắng.

- **Test 5:**  
  Với cấu hình ban đầu này, nếu cả hai chơi tối ưu thì Bob là người giành chiến thắng.
