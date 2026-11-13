## Ý tưởng

Gọi $S_i$ là màu đèn thứ $i$. Thêm một màu giả vào hai đầu, với mọi cặp chứa màu giả đều có điểm $0$. Nhờ vậy công thức ở biên cũng dùng được khi đoạn đảo chạm một đầu dải.

Khi đảo $[l,r]$, mỗi cặp bên trong đoạn đổi từ $(S_i,S_{i+1})$ thành $(S_{i+1},S_i)$, với $l\le i<r$. Gọi $P_j$ là tổng mức thay đổi đó trên các cạnh có chỉ số $1$ đến $j$, với $P_0=0$. Phần thay đổi bên trong là $P_{r-1}-P_{l-1}$.

Ở hai biên, bỏ các cặp $(S_{l-1},S_l)$, $(S_r,S_{r+1})$ và thêm $(S_{l-1},S_r)$, $(S_l,S_{r+1})$. Do đó mức tăng tổng điểm là
$$
\bigl(-P_{l-1}-W_{S_{l-1},S_l}\bigr)
+\bigl(P_{r-1}-W_{S_r,S_{r+1}}\bigr)
+W_{S_{l-1},S_r}+W_{S_l,S_{r+1}}.
$$

Quét $r$ từ trái sang phải. Với mỗi cặp màu $(x,y)$, lưu giá trị lớn nhất của $-P_{l-1}-W_{x,y}$ trong các $l\le r$ có $(S_{l-1},S_l)=(x,y)$. Tại $r$, đưa $l=r$ vào bảng rồi thử mọi nhóm đã có đầu trái. Phần còn lại trong công thức chỉ phụ thuộc vào $r$ và cặp màu của nhóm. Khởi tạo mức tăng tốt nhất bằng $0$ để xét lựa chọn giữ nguyên.

## Chứng minh tính đúng đắn

Các cặp kề ngoài đoạn đảo giữ nguyên. Mọi thay đổi nằm ở các cặp bên trong và hai cặp qua biên, nên công thức tính đúng mức tăng điểm. Với một đầu phải và một nhóm màu cố định, mọi đầu trái trong nhóm có cùng phần điểm còn lại. Do đó giữ giá trị tốt nhất của nhóm cho đúng mức tăng lớn nhất. Duyệt mọi đầu phải và mọi nhóm xét đủ các đoạn đảo, còn mức tăng $0$ ứng với giữ nguyên dải.

## Độ phức tạp

Có bốn màu kể cả màu giả, nên số nhóm là hằng số. Thời gian $O(N)$, bộ nhớ phụ $O(1)$ ngoài xâu đầu vào. Dùng số nguyên 64 bit cho các tổng điểm.
