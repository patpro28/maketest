# Lời giải ONDINH — Hiệu chỉnh tín hiệu có quán tính

## Quy hoạch động và phép chặn độ dốc

Gọi $F_i(x)$ là chi phí nhỏ nhất cho $i$ vị trí đầu khi $X_i=x$. Có

$$F_1(x)=W_1|x-A_1|,$$

$$F_i(x)=W_i|x-A_i|+\min_y\left(F_{i-1}(y)+C_{i-1}|x-y|\right).$$

Các hàm này lồi và tuyến tính từng đoạn. Với hàm lồi $F$, phép biến đổi

$$G(x)=\min_y(F(y)+c|x-y|)$$

tương đương chặn độ dốc của $F$ vào $[-c,c]$: giữ phần giữa có độ dốc trong khoảng đó, rồi kéo dài hai đầu bằng các đường có độ dốc $-c$ và $c$.

Một cách giải thích: $G$ là hàm lớn nhất không vượt $F$ và có hệ số Lipschitz không quá $c$. Thật vậy, chọn $y=x$ cho $G\le F$, còn bất đẳng thức tam giác cho tính Lipschitz. Nếu $H\le F$ có cùng giới hạn Lipschitz thì $H(x)\le H(y)+c|x-y|\le F(y)+c|x-y|$ với mọi $y$, nên $H\le G$. Tính lồi xác định đúng hai nhánh kéo dài như mô tả.

## Vì sao cần lưu khối lượng của điểm gãy?

Trọng số tới $10^6$, nên không nhân bản mỗi bước nhảy thành hàng triệu phần tử heap. Việc chuyển từng điểm qua hai heap cũng không tự bảo đảm cận $O(N\log N)$ cho dữ liệu có trọng số. Lời giải mẫu dùng treap có tổng khối lượng và tổng tọa độ nhân khối lượng, hỗ trợ tách cả một nhóm điểm bằng một thao tác trên cây.

Biểu diễn hàm bằng

$$F(x)=B-Sx+\sum_j d_j\max(x-a_j,0),$$

trong đó $d_j>0$ là độ tăng của đạo hàm tại $a_j$, và $\sum_jd_j=2S$. Hai đuôi có độ dốc $-S,+S$. Các tọa độ $a_j$ nằm trong tập giá trị đo đã xuất hiện.

Treap sắp theo $a_j$, mỗi nút lưu:

- Khối lượng $d_j$ và tổng khối lượng cây con.
- Tổng $a_jd_j$ của cây con.
- Ưu tiên ngẫu nhiên để giữ chiều cao kỳ vọng logarithm.

## Hai thao tác cập nhật

**Cộng $w|x-a|$:** từ đẳng thức $|x-a|=a-x+2\max(x-a,0)$, cập nhật

$$B\gets B+wa,\quad S\gets S+w,$$

và tăng khối lượng ở tọa độ $a$ thêm $2w$. Các điểm trùng tọa độ được gộp.

**Chặn độ dốc vào $[-c,c]$:** nếu $S\le c$ thì không đổi. Nếu $S>c$, đặt $d=S-c$:

1. Bỏ $d$ đơn vị khối lượng nhỏ nhất ở đầu trái.
2. Giữ $2c$ đơn vị khối lượng tiếp theo; bỏ phần còn lại ở đầu phải.
3. Nếu ranh giới cắt nằm trong một điểm gãy, tách khối lượng của nút đó, không xóa cả nút.
4. Giảm $B$ đi tổng $a_jd_j$ của phần bị bỏ ở đầu trái; đặt $S=c$.

Sau khi bỏ phần trái, trên vùng giữa số hạng bị bỏ có dạng $dx-\sum a_jd_j$. Việc giảm độ lớn của dốc trái từ $S$ xuống $c=S-d$ triệt tiêu số hạng $dx$; vì vậy phép cập nhật $B$ giữ nguyên giá trị trên vùng giữa. Phần bỏ ở bên phải chưa đóng góp tại đây. Hai đuôi còn lại chính là các độ dốc bị chặn.

Mỗi bước xử lý một vị trí thực hiện chặn theo $C_{i-1}$ trước, rồi cộng $W_i|x-A_i|$.

## Lấy giá trị nhỏ nhất

Từ dốc ban đầu $-S$, đi qua các bước nhảy cho tới khi tổng khối lượng đạt $S$. Tọa độ đó là một điểm cực tiểu. Dùng tổng khối lượng để tìm tọa độ $x$ này, rồi dùng hai tổng tiền tố $P=\sum_{a_j\le x}d_j$ và $Q=\sum_{a_j\le x}a_jd_j$:

$$\min F=B-Sx+xP-Q.$$

Tất cả đều được tính trong thời gian kỳ vọng $O(\log N)$ bằng treap.

## Đúng đắn và độ phức tạp

Truy hồi DP đúng theo giá trị cuối. Hai phép cập nhật giữ đúng biểu diễn hàm và thực hiện chính xác phép chuyển DP. Do đó sau vị trí cuối, giá trị nhỏ nhất lấy từ mức đạo hàm $0$ là đáp án.

- Thời gian kỳ vọng $O(N\log N)$, bộ nhớ $O(N)$.
- Mỗi bước thêm tối đa một nút cho giá trị đo và hai nút do cắt một phần khối lượng. Các nhóm bị bỏ được tách cả cây, không duyệt từng phần tử; tổng số nút cấp phát là $O(N)$.
- Dùng số nguyên 64 bit. Chọn mọi $X_i=0$ cho cận đáp án $\sum W_iA_i\le2\cdot10^{17}$.
- Phép chiếu mọi $X_i$ vào $[\min A_i,\max A_i]$ không tăng chi phí. Khi miền này nhỏ, có thể DP trên tọa độ; chuyển $\min_y(F(y)+c|x-y|)$ được tính bằng hai lượt quét trái/phải.

## Oracle độc lập không dùng slope trick

Phân tách chi phí theo các ngưỡng nguyên $t$. Đặt nhãn nhị phân $b_i=[X_i\ge t]$ và mẫu $s_i=[A_i\ge t]$. Ở mỗi ngưỡng, bài toán là tối thiểu hóa $\sum W_i[b_i\ne s_i]+\sum C_i[b_i\ne b_{i+1}]$ trên một đường thẳng.

Chi phí nhị phân được tính bằng tích các ma trận min-plus $2\times2$. Khi quét ngưỡng qua một giá trị $A_i$, chỉ chi phí tại vị trí $i$ đổi; segment tree cập nhật một lá. Giữa hai giá trị đo liên tiếp, chi phí nhị phân không đổi, nên nhân với khoảng cách hai giá trị.

Các bài toán nhị phân là bài toán cắt dưới mô-đun với sở thích đổi đơn điệu từ 1 về 0; có thể chọn các tập nhãn 1 tối ưu lồng nhau khi tăng ngưỡng. Chúng ghép thành một nghiệm nguyên $X_i$, nên tổng các giá trị tối ưu theo ngưỡng bằng đáp án gốc. Oracle này không dùng treap hay thao tác chặn độ dốc. Với miền tọa độ nhỏ, oracle còn tự đối chiếu với DP trực tiếp.
