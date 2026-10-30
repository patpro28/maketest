# Lời giải DTCANBANG — Điểm tập kết tối ưu

## Vị trí tối ưu là trung vị có trọng số

Với tập đỉnh đang xét, đặt $W=\sum_v W_v$ và

$$F(X)=\sum_v W_v|A_v-X|.$$

Giữa hai tọa độ liên tiếp, khi $X$ tăng, các đỉnh bên trái làm chi phí tăng theo tổng trọng số của chúng, còn các đỉnh bên phải làm chi phí giảm theo tổng trọng số của chúng. Vì vậy một vị trí tối ưu là tọa độ đầu tiên $m$ sao cho tổng trọng số tại các tọa độ không lớn hơn $m$ đạt ít nhất $\lceil W/2\rceil$.

Đây là trung vị có trọng số. Nếu tổng trọng số chẵn và có cả một khoảng vị trí tối ưu, chọn đầu trái của khoảng vẫn đúng. Không dùng trung bình có trọng số: trung bình tối ưu cho bình phương khoảng cách, không phải tổng khoảng cách tuyệt đối.

## Hai Fenwick trên tọa độ đã nén

Nén các tọa độ $A_v$ theo thứ tự tăng dần. Duy trì hai Fenwick:

- Tổng trọng số $W_v$ tại mỗi tọa độ.
- Tổng tích $W_vA_v$ tại mỗi tọa độ.

Khi thêm hoặc xóa một đỉnh, cộng hoặc trừ hai lượng tương ứng. Đồng thời giữ $W=\sum W_v$ và $S=\sum W_vA_v$ của tập hiện tại.

Tìm tọa độ trung vị bằng binary lifting trên Fenwick trọng số, với thứ hạng $(W+1)/2$. Các trọng số đang giữ luôn không âm, nên tổng tiền tố đơn điệu và tìm kiếm này hợp lệ.

## Tính chi phí từ các tổng tiền tố

Sau khi tìm được trung vị $m$, gọi $W_L,S_L$ là tổng trọng số và tổng tích của các đỉnh có tọa độ không lớn hơn $m$. Chi phí bên trái bằng $mW_L-S_L$; bên phải bằng $(S-S_L)-m(W-W_L)$. Do đó

$$\boxed{F(m)=mW_L-S_L+(S-S_L)-m(W-W_L)}.$$

Đỉnh ở đúng trung vị đóng góp $0$, nên đưa các đỉnh bằng trung vị vào phía trái không gây sai lệch. Mỗi lần lấy đáp án cần một lần tìm thứ hạng và hai tổng tiền tố, đều mất $O(\log N)$.

## Duy trì từng cây con bằng Sack

Tính thứ tự Euler, kích thước cây con và con nặng. Xử lý, lấy đáp án và dọn dữ liệu của các con nhẹ; giữ dữ liệu của con nặng. Thêm lại mọi đỉnh thuộc các con nhẹ, rồi thêm đỉnh cha. Lúc này hai Fenwick chứa đúng cây con đang xét; tìm trung vị và chi phí bằng công thức trên.

Khi không giữ kết quả của một lời gọi Sack, xóa các đỉnh trong đoạn Euler của nó. Trọng số ảnh hưởng tới lựa chọn trung vị, nhưng việc chọn con nặng vẫn dựa trên **số đỉnh**, vì đó là đại lượng chặn số lần thêm/xóa.

## Chứng minh đúng và độ phức tạp

Tính chất thay đổi chi phí theo hai phía chứng minh trung vị có trọng số là một vị trí tối ưu. Hai Fenwick giữ chính xác các tổng cần thiết sau từng thao tác, nên công thức tính đúng chi phí ở vị trí đó. Bất biến của Sack bảo đảm tập đang giữ tại mỗi lần lấy đáp án chính là cây con tương ứng. Kết hợp hai điều này, mọi đáp án đều là chi phí nhỏ nhất cần tìm.

Mỗi đỉnh được thêm/xóa $O(\log N)$ lần, mỗi lần mất $O(\log N)$. Việc lấy đáp án tại mỗi đỉnh mất $O(\log N)$. Tổng thời gian $O(N\log^2N)$, bộ nhớ $O(N)$. Tích tọa độ với trọng số và các tổng phải dùng `long long`. Với cây con một đỉnh, chọn đúng tọa độ của nó cho chi phí $0$. Lời giải mẫu xử lý cây bằng ngăn xếp thay cho đệ quy.
