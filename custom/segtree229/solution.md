## Tách các nhóm độ cao

Xét một truy vấn. Gọi $m_1,M_1$ và $m_2,M_2$ lần lượt là cực tiểu và cực đại của hai khu vực được phép tăng. Gọi $M$ là độ cao lớn nhất hiện tại của toàn đoạn được hỏi. Nếu còn vị trí nằm ngoài hai khu vực, gọi $m_0$ là độ cao nhỏ nhất trong các vị trí đó. Đặt $d_1=M-m_1$ và $d_2=M-m_2$.

Cộng đều vào một khu vực giữ nguyên biên độ của riêng khu vực đó. Phần nằm ngoài hai khu vực cũng giữ nguyên mọi độ cao.

## Điều kiện đạt biên độ không quá $W$

Vì các mức tăng đều không âm, độ cao lớn nhất sau hai lần tăng ít nhất là $M$. Nếu biên độ mới không quá $W$, mọi vị trí phải cao ít nhất $M-W$. Do đó cần có:

- $W\ge M_1-m_1$ và $W\ge M_2-m_2$ để mỗi khu vực tự nằm vừa trong một khoảng rộng $W$.
- $W\ge M-m_0$ nếu phần nằm ngoài hai khu vực khác rỗng.
- $\max(0,d_1-W)+\max(0,d_2-W)\le B$ để ngân sách đủ đưa cực tiểu của hai khu vực lên ít nhất $M-W$.

Các điều kiện trên cũng đủ. Chọn $h_i=\max(0,d_i-W)$ cho từng khu vực. Nếu $h_i=0$, cực tiểu của khu vực vốn đã đạt ít nhất $M-W$, còn cực đại vốn không quá $M$. Nếu $h_i>0$, sau khi tăng, cực tiểu bằng $M-W$. Do biên độ trong khu vực không quá $W$, cực đại mới không vượt $M$. Các vị trí ở ngoài cũng nằm trong $[M-W,M]$. Tổng hai mức tăng không quá $B$ theo điều kiện ngân sách.

## Tính trực tiếp đáp án

Với $a=d_1-W$ và $b=d_2-W$, ta có $\max(0,a)+\max(0,b)=\max(0,a,b,a+b)$. Vì $B\ge 0$, điều kiện ngân sách tương đương với ba cận dưới cho $W$:

$$W\ge d_1-B,\qquad W\ge d_2-B,\qquad W\ge\left\lceil\frac{d_1+d_2-B}{2}\right\rceil.$$

Lấy max của ba cận này, $0$, biên độ hai khu vực và cận $M-m_0$ nếu có. Có thể chặn tử số $d_1+d_2-B$ dưới bởi $0$ trước khi chia lấy trần, vì đáp án vốn không âm.

## Cây đoạn và độ phức tạp

Dùng cây đoạn lưu min, max và nhãn cộng chờ để thực hiện các cập nhật thật. Mỗi truy vấn lấy max toàn đoạn, min và max của hai khu vực, cùng min trên tối đa ba đoạn nằm ngoài hai khu vực. Bỏ qua các đoạn ngoài rỗng. Sau khi lấy cực trị, tính đáp án bằng công thức trên. Các phép tăng giả định chỉ xuất hiện trong lập luận và không được áp dụng lên cây.

Dựng cây trong $O(N)$. Mỗi thao tác dùng một số lần cập nhật hoặc truy vấn cây cố định, tốn $O(\log(N+1))$ thời gian. Bộ nhớ là $O(N)$. Dùng số nguyên 64 bit cho độ cao, nhãn cộng, ngân sách và mọi hiệu trong công thức.
