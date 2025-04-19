## Đề bài

Byteotian Interstellar Union (BIU) vừa phát hiện một hành tinh mới trong một thiên hà gần đó. Hành tinh này không thích hợp để định cư do các trận mưa thiên thạch kỳ lạ, nhưng điều này lại khiến nó trở thành một đối tượng nghiên cứu vô cùng thú vị.

Các thành viên của BIU đã đặt các trạm không gian gần quỹ đạo của hành tinh này. Mục tiêu của các trạm là thu thập các mẫu thiên thạch bay ngang qua. BIU đã chia quỹ đạo thành $m$ khu vực được đánh số từ $1$ đến $m$, trong đó các khu vực $1$ và $m$ được coi là liền kề nhau. Mỗi khu vực có duy nhất một trạm không gian, thuộc về một trong $n$ quốc gia thành viên.

Mỗi quốc gia đã công bố số lượng mẫu thiên thạch mà họ muốn thu thập trước khi nhiệm vụ kết thúc. Nhiệm vụ của bạn là xác định, đối với mỗi quốc gia, khi nào họ có thể dừng việc thu thập mẫu, dựa trên dự đoán về các trận mưa thiên thạch trong các năm tới.

## Dữ liệu vào

Dòng đầu tiên chứa hai số nguyên $n$ và $m$ $(1 \leq n, m \leq 300\,000)$, lần lượt là số quốc gia thành viên và số khu vực mà quỹ đạo đã được chia.

Dòng thứ hai chứa $n$ số nguyên $o_i$ $(1 \leq o_i \leq n)$, được phân tách bởi dấu cách, biểu thị các quốc gia sở hữu các trạm tại các khu vực liên tiếp.

Dòng thứ ba chứa $n$ số nguyên $p_i$ $(1 \leq p_i \leq 10^9)$, được phân tách bởi dấu cách, biểu thị số lượng mẫu mà các quốc gia tương ứng muốn thu thập.

Dòng thứ tư chứa một số nguyên $k$ $(1 \leq k \leq 300\,000)$, biểu thị số lượng dự đoán về các trận mưa thiên thạch.

$k$ dòng tiếp theo, mỗi dòng chứa ba số nguyên $l_i, r_i, a_i$ $(1 \leq l_i, r_i \leq m, 1 \leq a_i \leq 10^9)$, biểu thị một trận mưa thiên thạch được dự đoán xảy ra trong các khu vực $l_i, l_i + 1, \dots, r_i$ (nếu $l_i \leq r_i$), hoặc trong các khu vực $l_i, l_i + 1, \dots, m, 1, \dots, r_i$ (nếu $l_i > r_i$). Mỗi trạm trong các khu vực này sẽ nhận được $a_i$ mẫu thiên thạch.

## Dữ liệu ra

Chương trình của bạn cần in $n$ dòng. Dòng thứ $i$ phải chứa một số nguyên $w_i$, biểu thị số thứ tự của trận mưa thiên thạch sau đó các trạm thuộc quốc gia thứ $i$ dự kiến thu thập đủ ít nhất $p_i$ mẫu, hoặc in từ `NIE` (tiếng Ba Lan nghĩa là "không") nếu quốc gia đó không thể thu thập đủ mẫu trong tương lai.

## Giới hạn

- $1 \leq n, m \leq 300\,000$
- $1 \leq k \leq 300\,000$
- $1 \leq p_i, a_i \leq 10^9$
- $1 \leq o_i \leq n$
- $1 \leq l_i, r_i \leq m$

## Sample Input

    3 5
    1 3 2 1 3
    10 5 7
    3
    4 2 4
    1 3 1
    3 5 2

## Sample Output

    3
    NIE
    2

## Giải thích

- Trong ví dụ trên:

  - Quốc gia $1$ sở hữu các trạm trong khu vực $1$ và $4$.
  - Quốc gia $2$ sở hữu trạm trong khu vực $3$.
  - Quốc gia $3$ sở hữu các trạm trong khu vực $2$ và $5$.
  
  **Dự đoán mưa thiên thạch:**
  - Trận thứ $1$: ảnh hưởng các khu vực $4, 5, 1, 2$ (theo thứ tự vòng tròn), mỗi trạm nhận được $4$ mẫu.
  - Trận thứ $2$: ảnh hưởng các khu vực $1, 2, 3$, mỗi trạm nhận được $1$ mẫu.
  - Trận thứ $3$: ảnh hưởng các khu vực $3, 4, 5$, mỗi trạm nhận được $2$ mẫu.
  
  **Quốc gia $1$:**
  - Trận thứ $1$: các trạm $1$ và $4$ thu thập được $4 + 4 = 8$ mẫu.
  - Trận thứ $2$: thu thập thêm $1$ mẫu từ trạm $1$, tổng $9$ mẫu.
  - Trận thứ $3$: thu thập thêm $2$ mẫu từ trạm $4$, tổng $11$ mẫu. Đủ ít nhất $10$ mẫu, dừng lại ở trận thứ $3$.

  **Quốc gia $2$:**
  - Trận thứ $1$: trạm $3$ thu thập được $4$ mẫu.
  - Trận thứ $2$: thu thập thêm $1$ mẫu từ trạm $3$, tổng $5$ mẫu. Không có thêm trận nào để đạt $7$ mẫu. Kết quả là `NIE`.

  **Quốc gia $3$:**
  - Trận thứ $1$: các trạm $2$ và $5$ thu thập được $4 + 4 = 8$ mẫu.
  - Trận thứ $2$: thu thập thêm $1$ mẫu từ trạm $2$, tổng $9$ mẫu.
  - Trận thứ $3$: thu thập thêm $2$ mẫu từ trạm $5$, tổng $11$ mẫu. Đủ ít nhất $7$ mẫu, dừng lại ở trận thứ $2$.