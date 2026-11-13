## Dùng hai đầu mút của khoảng giá trị

Gọi $m$ và $M$ là giá trị nhỏ nhất và lớn nhất trong đoạn được hỏi. Với mọi $A_i$ thuộc đoạn, ta có $A_i-h\le M-h$ và $h-A_i\le h-m$. Do $|A_i-h|=\max(A_i-h,h-A_i)$, độ lệch của mọi phần tử đều không vượt quá $\max(M-h,h-m)$.

Hai giá trị $m,M$ đều xuất hiện trong đoạn. Tại vị trí có giá trị $M$, độ lệch ít nhất bằng $M-h$. Tại vị trí có giá trị $m$, độ lệch ít nhất bằng $h-m$. Vì vậy đáp án đúng bằng $\max(M-h,h-m)$.

## Cây đoạn

Mỗi nút lưu cặp min và max của đoạn nó quản lý. Lá tại vị trí $i$ lưu $(A_i,A_i)$. Nút cha lấy min của hai cực tiểu và max của hai cực đại. Khi gán $A_i=x$, sửa lá tương ứng rồi tính lại các nút trên đường đến gốc.

Mỗi truy vấn ghép các nút phủ kín $[l,r]$ để lấy $m,M$. Khi cài đặt có đoạn rỗng, dùng cặp $(+\infty,-\infty)$ làm giá trị trung hòa. Chỉ áp dụng công thức độ lệch sau khi lấy cực trị của đoạn được hỏi.

## Độ phức tạp

Dựng cây trong $O(N)$. Mỗi lần gán hoặc truy vấn mất $O(\log(N+1))$. Bộ nhớ là $O(N)$.
