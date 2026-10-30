# Lời giải LICHTRUC — Lịch công việc tuần hoàn

## Chọn trạng thái đủ thông tin

Tính hợp lệ của ngày tiếp theo chỉ phụ thuộc vào số ngày làm liên tiếp ở cuối lịch và công việc vừa làm. Dùng bảy trạng thái:

- $0$: ngày vừa qua nghỉ; cũng là trạng thái trước ngày đầu tiên.
- $1,2,3$: vừa làm $A,B,C$ và chuỗi làm liên tiếp hiện dài $1$.
- $4,5,6$: vừa làm $A,B,C$ và chuỗi làm liên tiếp hiện dài $2$.

Đặt $f(s)$ là điểm lớn nhất kết thúc ở trạng thái $s$. Ban đầu $f(0)=0$, các trạng thái khác bằng $-\infty$.

## Ma trận của một ngày

Dùng vector hàng và ma trận $T$, trong đó $T[s][t]$ là điểm của lựa chọn chuyển từ trạng thái $s$ sang $t$ trong ngày hiện tại.

- Từ mọi trạng thái, có thể nghỉ để về $0$, nhận $0$ điểm.
- Từ $0$, có thể làm một trong ba việc, tới trạng thái $1,2,3$ và nhận điểm của việc đó.
- Từ trạng thái có chuỗi dài $1$, chỉ được làm một việc khác, tới trạng thái chuỗi dài $2$ tương ứng.
- Từ trạng thái có chuỗi dài $2$, chỉ có thể nghỉ.
- Các chuyển khác bằng $-\infty$.

Với $(B\otimes C)[i][j]=\max_k(B[i][k]+C[k][j])$, DP sau một ngày là $f'=f\otimes T$. Ma trận giữ mọi khả năng về trạng thái cuối, nên có thể ghép nhiều ngày mà vẫn kiểm soát điều kiện nối giữa chúng.

## Gộp một chu kỳ rồi lũy thừa

Gọi $T_1,\ldots,T_P$ là ma trận của các mẫu ngày. Tính theo đúng thứ tự thời gian:

$$B=T_1\otimes T_2\otimes\cdots\otimes T_P.$$

Viết $D=qP+r$, $0\le r<P$. Gọi $H=T_1\otimes\cdots\otimes T_r$; khi $r=0$, $H$ là ma trận đơn vị. Ma trận của toàn bộ lịch là

$$B^{\otimes q}\otimes H.$$

Tính $B^{\otimes q}$ bằng lũy thừa nhị phân. Đáp án là phần tử lớn nhất trên hàng $0$ của tích cuối, vì trạng thái đầu cố định bằng $0$ và trạng thái cuối được tùy chọn.

Không thể tối ưu riêng từng chu kỳ thành một số rồi nhân với $q$: hai lịch tốt nhất của từng chu kỳ có thể ghép thành ba ngày làm liên tiếp hoặc hai công việc giống nhau liên tiếp. Cần giữ cả bảy trạng thái biên trong ma trận.

## Chứng minh đúng

Các trạng thái phân biệt đầy đủ các thông tin ảnh hưởng tới lựa chọn ngày sau. Mỗi lịch hợp lệ ứng với một chuỗi chuyển trạng thái, và mỗi chuỗi chuyển hợp lệ tạo ra đúng một lịch thỏa hai quy tắc. Trọng số của chuỗi bằng tổng điểm lịch.

Tích max-plus lấy tối ưu trên mọi trạng thái ở điểm nối, nên ma trận tích của một đoạn ngày lưu đúng giá trị tốt nhất cho mọi trạng thái đầu/cuối. Chuỗi $q$ chu kỳ đầy đủ rồi $r$ ngày đầu chu kỳ là đúng lịch điểm của $D$ ngày. Lấy max trên trạng thái cuối trả đúng đáp án.

## Độ phức tạp và lưu ý

- Kích thước ma trận cố định $7$. Thời gian $O(7^3(P+\log(D+1)))$; bộ nhớ phụ $O(7^2)$ nếu đọc và ghép các ngày ngay khi nhập.
- Tích một đoạn rỗng là ma trận đơn vị, giúp xử lý $D=0$ và $D<P$.
- Luôn cho phép nghỉ, kể cả khi mọi điểm làm việc âm. Đáp án không âm.
- Dùng số nguyên có dấu $64$ bit và bỏ qua các số hạng chứa $-\infty$ trong phép nhân.
