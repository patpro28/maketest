# Lời giải CUASOMIN — Tổng cực tiểu trong cửa sổ

## Xử lý truy vấn theo đầu phải

Đặt

$$M_i(t)=\min(A_i,\ldots,A_t),\qquad H_i(t)=\sum_{j=i}^{t}M_i(j).$$

Truy vấn $[L,R]$ có đáp án $\sum_{i=L}^{R}H_i(R)$. Gom các truy vấn theo đầu phải và lần lượt xử lý $t=1,\ldots,N$.

Với một điểm bắt đầu $i$, giữa hai lần cực tiểu $M_i$ thay đổi, $H_i(t)$ là hàm bậc nhất theo $t$:

$$H_i(t)=b_i t+c_i,$$

trong đó $b_i$ là cực tiểu hiện tại. Ta duy trì hai dãy hệ số $b_i,c_i$, hỗ trợ cộng một đoạn và lấy tổng một đoạn.

## Cập nhật hệ số khi cực tiểu giảm

Giả sử thêm phần tử tại vị trí $t$ làm cực tiểu của một nhóm điểm bắt đầu giảm từ $v$ xuống $x=A_t$. Trước khi thêm:

$$H_i(t-1)=b_i(t-1)+c_i.$$

Sau khi thêm, phải có $H_i(t)=H_i(t-1)+x$. Vì $b_i=v$, hệ số mới là

$$b_i\gets b_i+x-v,\qquad c_i\gets c_i+(v-x)(t-1).$$

Với điểm bắt đầu mới $i=t$, chỉ có một đoạn $[t,t]$, nên đặt

$$b_t=A_t,\qquad c_t=A_t(1-t).$$

Như vậy $b_tt+c_t=A_t$ như yêu cầu.

## Stack tìm nhóm thay đổi

Stack lưu các chỉ số có giá trị tăng nghiêm ngặt. Khi thêm $A_t$, bỏ các đỉnh $p$ với $A_p\ge A_t$. Sau khi bỏ $p$, nếu đỉnh trước đó là $q$ (hoặc $q=0$ khi stack rỗng), nhóm điểm bắt đầu $[q+1,p]$ đang có cực tiểu $A_p$ và cần đổi thành $A_t$.

Áp dụng hai phép cộng đoạn ở trên cho nhóm này, rồi tiếp tục bỏ đỉnh nếu cần. Cuối cùng đưa $t$ vào stack và khởi tạo hệ số của điểm bắt đầu mới.

Các nhóm bị bỏ rời nhau; các nhóm còn lại có cực tiểu nhỏ hơn $A_t$, nên không đổi. Trường hợp giá trị bằng nhau vẫn có thể gộp; lượng cộng hệ số khi đó bằng $0$.

## Fenwick cộng đoạn, tổng đoạn

Mỗi dãy hệ số dùng một cặp Fenwick để hỗ trợ cộng đoạn và lấy tổng đoạn, tổng cộng bốn Fenwick. Khi đã xử lý tới $R$, trả lời:

$$R\cdot\sum_{i=L}^{R}b_i+\sum_{i=L}^{R}c_i.$$

Lưu đáp án theo mã truy vấn và in theo thứ tự đầu vào. Không cần các đầu phải vốn đã được sắp xếp.

## Chứng minh đúng

Ban đầu chưa có điểm bắt đầu nào và các hệ số đều bằng $0$. Khi thêm một phần tử, stack phân nhóm đúng những cực tiểu thay đổi; công thức cập nhật bảo toàn đẳng thức $H_i(t)=b_it+c_i$. Điểm bắt đầu mới cũng được khởi tạo đúng. Theo quy nạp, mọi $H_i(t)$ đều đúng. Mỗi đoạn con trong $[L,R]$ có đúng một điểm bắt đầu $i\ge L$ và một điểm kết thúc không vượt $R$, nên tổng các $H_i(R)$ chính là đáp án.

## Độ phức tạp và lưu ý

- Mỗi chỉ số vào/ra stack một lần, có $O(N)$ lần cập nhật nhóm.
- Thời gian $O((N+Q)\log N)$, bộ nhớ $O(N+Q)$.
- Đáp án không vượt $10^6N(N+1)/2<2.1\cdot10^{16}$.
- Hệ số $c_i$ có thể âm dù mọi $A_i$ không âm. Dùng `long long` cho mọi Fenwick, tích tọa độ và phép cộng.
- Không chỉ cộng các cực tiểu hiện tại: truy vấn cần lịch sử của tất cả đầu phải trước đó, chính là $H_i$.
- Với dữ liệu nhỏ, liệt kê mọi đoạn con trong mỗi truy vấn và kéo dài đoạn để cập nhật min, mất $O(QN^2)$.

## Kiểm chứng độc lập

Oracle không dùng stack hay Fenwick. Một cây min tìm chỉ số gần nhất bên trái có giá trị nhỏ hơn phần tử mới. Một cây lazy khác giữ hai tổng: cực tiểu hiện tại và tổng cực tiểu tích lũy. Nó gán một đoạn cực tiểu, rồi cộng tổng hiện tại vào tổng lịch sử. Tag lazy biểu diễn biến đổi $(x,h)\mapsto(ax+b,h+cx+d)$, nên xử lý chính xác cả các lần gán xen kẽ bước thời gian. Với dữ liệu nhỏ, oracle còn đối chiếu mọi đáp án với vét cạn.
