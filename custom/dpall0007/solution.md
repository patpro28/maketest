## Ý tưởng

Cố định đầu phải $r$. Chỉ các đoạn cấm có $R_i\le r$ có thể nằm trong $[l,r]$. Gọi $B_r$ là giá trị lớn nhất của $L_i$ trong số các đoạn này, mặc định bằng $0$ nếu chưa có đoạn nào.

Nếu $l>B_r$, mọi đoạn cấm kết thúc tại hoặc trước $r$ đều có đầu trái nhỏ hơn $l$. Nếu $1\le l\le B_r$, đoạn đạt cực đại $B_r$ nằm trọn trong $[l,r]$. Vậy có đúng $r-B_r$ đầu trái hợp lệ.

Gom các đoạn cấm theo đầu phải. Đặt $A_r$ bằng đầu trái lớn nhất của những đoạn kết thúc đúng ở $r$, hoặc bằng $0$ nếu không có đoạn nào. Khi quét $r$ từ $1$ đến $M$, cập nhật $B_r=\max(B_{r-1},A_r)$ rồi cộng $r-B_r$ vào đáp án.

## Chứng minh tính đúng đắn

Phép cập nhật cực đại đưa vào đúng những đoạn cấm mới kết thúc tại $r$, nên $B_r$ bằng đầu trái lớn nhất của mọi đoạn đã kết thúc. Điều kiện $l>B_r$ là cần và đủ theo lập luận trên. Các cặp được chia theo đầu phải $r$, do đó phép cộng không đếm trùng và không bỏ sót.

## Độ phức tạp

Thời gian $O(N+M)$, bộ nhớ $O(M)$. Dùng số nguyên 64 bit cho đáp án.
