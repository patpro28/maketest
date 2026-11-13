## Ý tưởng

Đặt $A_K$ vào vị trí $K$. Tính các phần tử bên trái theo công thức $A_{i-1}=A_i-D_i$ khi duyệt $i=K,K-1,\ldots,2$. Tính bên phải bằng $A_i=A_{i-1}+D_i$ khi duyệt $i=K+1,\ldots,N$.

## Chứng minh tính đúng đắn

Giá trị ở vị trí $K$ đã biết. Nếu $A_i$ đúng, phương trình $D_i=A_i-A_{i-1}$ xác định duy nhất $A_{i-1}=A_i-D_i$. Tương tự, nếu $A_{i-1}$ đúng, $A_i=A_{i-1}+D_i$ cũng được xác định duy nhất. Hai lượt duyệt lần lượt áp dụng các phương trình đó cho mọi vị trí bên trái và bên phải, kể cả khi một phía rỗng.

## Độ phức tạp

Mỗi bộ test cần thời gian $O(N)$ và bộ nhớ phụ $O(N)$.

## Lưu ý cài đặt

Dùng số nguyên 64 bit cho chênh lệch và các giá trị khôi phục. Với $N=1$, đọc trực tiếp giá trị mốc và in ra.
