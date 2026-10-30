# Lời giải DTTOPMAU — Những màu phổ biến nhất

## Chọn theo tần suất, không theo mã màu

Với một cây con cố định, gọi các tần suất màu dương là $f_1,\ldots,f_D$. Truy vấn chọn tối đa $k$ màu cần tổng $\min(k,D)$ tần suất lớn nhất. Vì mọi tần suất dương, luôn chọn đủ số màu này.

Ta cần duy trì phân bố các tần suất khi thêm hoặc xóa từng đỉnh. Nén màu và giữ mảng $cnt_c$. Dùng hai Fenwick trên chỉ số tần suất $1,\ldots,N$:

- `frequency[f]`: số màu đang có đúng $f$ đỉnh.
- `mass[f]`: tổng số đỉnh của các màu đó, bằng $f\cdot frequency[f]$.

Fenwick thứ nhất trả số màu trong một khoảng tần suất; Fenwick thứ hai trả tổng số đỉnh thuộc các màu trong khoảng đó. Màu có tần suất $0$ không được đưa vào hai cây.

## Thêm và xóa một đỉnh

Nếu tần suất màu đổi từ $x$ sang $y=x\pm1$:

1. Nếu $x>0$, trừ $1$ ở vị trí $x$ của Fenwick số màu và trừ $x$ ở Fenwick số đỉnh.
2. Đổi tần suất thành $y$.
3. Nếu $y>0$, thêm $1$ ở vị trí $y$ của Fenwick số màu và thêm $y$ ở Fenwick số đỉnh.

Đồng thời giữ số đỉnh $T$ và số màu xuất hiện $D$. Mỗi thay đổi mất $O(\log N)$.

## Trả lời top k bằng phần bị loại

Thay vì lấy các màu phổ biến nhất, bỏ $m=D-\min(k,D)$ màu ít xuất hiện nhất. Nếu $m=0$, đáp án là $T$.

Nếu $m>0$, dùng tìm kiếm theo thứ hạng trên Fenwick số màu để tìm tần suất nhỏ nhất $f$ sao cho số màu có tần suất không quá $f$ đạt ít nhất $m$. Đặt

$$d=\sum_{j<f}frequency[j],\qquad s=\sum_{j<f}mass[j].$$

Ta bỏ trọn các màu có tần suất nhỏ hơn $f$, rồi bỏ thêm $m-d$ màu tần suất $f$. Số đỉnh bị bỏ là

$$s+(m-d)f.$$

Đáp án bằng $T-s-(m-d)f$. Các màu đồng hạng có thể chọn tùy ý vì đóng góp bằng nhau. Tìm thứ hạng bằng binary lifting trực tiếp trên Fenwick mất $O(\log N)$.

## Gom truy vấn bằng Sack

Gắn mỗi truy vấn vào đỉnh được hỏi. Dùng Sack để duy trì đúng dữ liệu của từng cây con: xử lý và dọn các con nhẹ, giữ con nặng, thêm lại các con nhẹ và đỉnh cha, rồi trả lời toàn bộ truy vấn tại cha. Mỗi cây con là một đoạn Euler nên thao tác thêm/xóa một cây con chỉ là duyệt các đỉnh trên đoạn đó.

Lưu đáp án theo số thứ tự truy vấn để in đúng thứ tự đầu vào.

## Chứng minh đúng và độ phức tạp

Sau mỗi thao tác thêm/xóa, hai Fenwick mô tả đúng số màu và số đỉnh theo tần suất. Tính chất Sack bảo đảm dữ liệu tại thời điểm trả lời đúng bằng cây con được hỏi. Bỏ các tần suất nhỏ nhất là tối ưu: nếu phần bỏ chứa một tần suất lớn hơn một tần suất được giữ, đổi chỗ chúng không làm đáp án giảm. Công thức theo ngưỡng $f$ thực hiện chính xác lựa chọn đó, kể cả khi đồng hạng.

Mỗi đỉnh được thêm/xóa $O(\log N)$ lần, mỗi lần mất $O(\log N)$. Mỗi truy vấn mất $O(\log N)$. Tổng thời gian $O(N\log^2N+Q\log N)$, bộ nhớ $O(N+Q)$. Các trường hợp $k=0$ và $k>D$ được xử lý bởi cùng công thức. Lời giải mẫu duyệt cây và các pha Sack không đệ quy.
