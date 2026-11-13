## Ý tưởng

Duyệt $A$ từ trái sang phải. Đặt giá trị đứng trước phần tử đầu tiên là $A_0=0$. Tại mỗi vị trí $i$, in hiệu giữa giá trị vừa đọc và giá trị trước đó, rồi lưu lại giá trị vừa đọc.

## Chứng minh tính đúng đắn

Trước khi xử lý vị trí $i$, giá trị được lưu là $A_{i-1}$, với $A_0=0$. Do đó hiệu được in là $A_i-A_{i-1}$, bằng $D_1$ khi $i=1$ và bằng $D_i$ ở mọi vị trí còn lại. Cập nhật giá trị lưu thành $A_i$ duy trì tính chất này cho bước kế tiếp.

## Độ phức tạp

Mỗi bộ test cần thời gian $O(N)$ và bộ nhớ phụ $O(1)$.

## Lưu ý cài đặt

Dùng số nguyên 64 bit cho giá trị và chênh lệch.
