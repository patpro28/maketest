# Lời giải DUONGMIN — Các hậu tố trên đường tổ tiên

## Các nhóm điểm bắt đầu trên một đường đi

Với một đỉnh cuối cố định $v$, xét cực tiểu của các đoạn từ từng độ sâu bắt đầu tới $v$. Những điểm bắt đầu liên tiếp có thể có cùng cực tiểu; stack đơn điệu biểu diễn các nhóm này.

Khi thêm một giá trị mới $A_v$ sau đường tới cha của $v$, mọi nhóm ở đỉnh stack có giá trị không nhỏ hơn $A_v$ được gộp vào nhóm mới. Các nhóm còn lại giữ nguyên.

Trên một dãy, pop thông thường có tổng chi phí tuyến tính. Trên cây, nếu pop rồi rollback thì một nhóm có thể bị lấy ra lại ở rất nhiều nhánh. Một đường tăng dài $m$ nối với $m$ đỉnh con mang giá trị nhỏ hơn cả đường đi sẽ buộc $m^2$ lần pop. Vì vậy cần một phiên bản stack riêng cho mỗi đỉnh và nhảy qua các nhóm bị loại.

## Con trỏ phiên bản và tổng đóng góp

Gọi $P(v)$ là nút còn ở đỉnh stack sau khi loại các nhóm có giá trị ít nhất $A_v$ khỏi phiên bản của cha cây. Tương đương, đó là tổ tiên gần nhất của $v$ có giá trị nhỏ hơn $A_v$; nếu không có thì dùng đỉnh giả $0$, độ sâu bằng $0$.

Nút stack mới $v$ đại diện cho các điểm bắt đầu có độ sâu từ $\operatorname{depth}(P(v))+1$ tới $\operatorname{depth}(v)$, tất cả đều có cực tiểu $A_v$.

Giữ

$$T(v)=T(P(v))+A_v\big(\operatorname{depth}(v)-\operatorname{depth}(P(v))\big),\qquad T(0)=0.$$

Đây là tổng cực tiểu của mọi hậu tố của toàn bộ đường gốc–$v$. Những nút stack cũ không bị sửa, nên các nhánh cùng dùng lại phiên bản tổ tiên một cách an toàn.

## Dựng phiên bản bằng binary lifting

Xây bảng `jump[v][j]` là tổ tiên cách $2^j$ cạnh **trong stack**, không phải trong cây đầu vào. Giá trị trên chuỗi con trỏ stack giảm nghiêm ngặt khi đi ngược.

Bắt đầu tại cha cây của $v$. Nếu giá trị tại đó nhỏ hơn $A_v$, nó chính là $P(v)$. Nếu không, thử các bước nhảy lớn xuống nhỏ, nhảy khi đích vẫn có giá trị ít nhất $A_v$. Sau cùng đi thêm một con trỏ để tới giá trị nhỏ hơn đầu tiên hoặc đỉnh giả $0$.

Mỗi đỉnh được dựng trong $O(\log N)$, không duyệt lần lượt từng nút bị loại. Xử lý các đỉnh theo thứ tự cha trước con bằng một lượt duyệt cây không đệ quy.

## Trả lời truy vấn và nhóm bị cắt một phần

Với truy vấn $(v,k)$, đặt $L=\operatorname{depth}(v)-k+1$. Trên chuỗi stack của phiên bản $v$, tìm nút $w$ sâu nhất về phía tổ tiên sao cho

$$\operatorname{depth}(w)\ge L,\qquad\operatorname{depth}(P(w))<L.$$

Dùng binary lifting theo độ sâu để tìm $w$. Các nhóm ở sau $w$ được lấy trọn vẹn và có tổng $T(v)-T(w)$. Nhóm $w$ chỉ lấy các điểm bắt đầu từ $L$ tới $\operatorname{depth}(w)$, nên đáp án là

$$T(v)-T(w)+A_w\big(\operatorname{depth}(w)-L+1\big).$$

Không được lấy trọn nhóm $w$ nếu biên truy vấn cắt ở giữa nhóm.

## Chứng minh đúng và độ phức tạp

Theo tính chất stack đơn điệu, các nhóm của mỗi phiên bản biểu diễn đúng cực tiểu theo mọi độ sâu bắt đầu. Nhảy qua một chuỗi nhóm có giá trị không nhỏ hơn $A_v$ tương đương pop lần lượt, nhưng không thay đổi dữ liệu đã có. Công thức $T$ cộng đúng số điểm bắt đầu của từng nhóm. Truy vấn lấy toàn bộ các nhóm nằm trong cửa sổ và phần hợp lệ của nhóm biên, nên tính đúng tổng yêu cầu.

- Thời gian $O((N+Q)\log N)$, bộ nhớ $O(N\log N)$.
- $0\le T(v)\le10^9\operatorname{depth}(v)\le2\cdot10^{14}$, dùng `long long` cho các tổng và phép nhân.
- Giá trị trùng nhau phải được xử lý nhất quán. Lời giải mẫu gộp các nhóm bằng nhau bằng điều kiện `>=`.
- Phân biệt bảng nhảy theo stack với cha của cây; chúng không phải cùng một quan hệ.
- Với mỗi truy vấn, có lời giải chậm $O(k)$: đi từ $v$ lên $k$ đỉnh, cập nhật cực tiểu đang có và cộng vào đáp án.

## Kiểm chứng độc lập

Oracle dùng binary lifting trên **cây thật**, kèm min của các khối tổ tiên, để tìm tổ tiên nhỏ hơn gần nhất. Mỗi phiên bản cây phân đoạn lưu các cực tiểu theo độ sâu bắt đầu; nó gán một đoạn khi thêm đỉnh và lấy tổng đoạn cho truy vấn. Oracle không dùng stack phiên bản hay công thức tổng nhóm $T$. Nếu tổng $k$ của các truy vấn không quá ba triệu, còn kiểm tra trực tiếp bằng cách đi lên cây cho từng truy vấn.
