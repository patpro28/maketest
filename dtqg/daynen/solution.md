# Lời giải DAYNEN — Dãy số nén

## DP khi đọc một dãy thông thường

Dùng $C+1$ trạng thái $0,1,\ldots,C$. Trạng thái $0$ biểu diễn chưa chọn phần tử nào; trạng thái $j>0$ biểu diễn giá trị cuối của dãy con đã chọn bằng $j$. Giá trị DP là độ dài lớn nhất của dãy con tương ứng.

Khi đọc phần tử $x$:

- Có thể bỏ qua nó, giữ nguyên trạng thái và độ dài.
- Có thể chọn nó từ một trạng thái $j\le x$, chuyển tới $x$ và cộng $1$.

Điều kiện là $j\le x$, không phải $j<x$, vì dãy cần không giảm. Phải hiểu các chuyển là đồng thời từ DP cũ sang DP mới; một phần tử chỉ được chọn một lần.

## Ma trận biến đổi của một khối

Dùng vector hàng. Ma trận của một phần tử $x$ ban đầu là ma trận đơn vị max-plus; sau đó đặt $T_x[j][x]=1$ với mọi $0\le j\le x$. Đường chéo ở $(x,x)$ trở thành $1$, biểu diễn chọn thêm một phần tử bằng giá trị cuối.

Tích max-plus được định nghĩa bởi

$$ (B\otimes C)[i][j]=\max_k(B[i][k]+C[k][j]). $$

Với mỗi dãy $S$, lưu ma trận $M_S$ biểu diễn toàn bộ phép biến đổi DP sau khi đọc $S$. Đừng chỉ lưu đáp án của $S$: khi ghép sau một dãy khác, giá trị cuối đã chọn từ trước sẽ ảnh hưởng đến phần được chọn trong $S$.

Ba chỉ dẫn được xử lý như sau:

1. Dãy một phần tử $x$: $M_i=T_x$.
2. Nối $S_u$ rồi $S_v$: $M_i=M_u\otimes M_v$.
3. Lặp $S_u$ đúng $k$ lần: $M_i=M_u^{\otimes k}$, tính bằng lũy thừa nhị phân. Nếu $k=0$, kết quả là ma trận đơn vị.

Ban đầu chưa chọn phần tử, nên vector đầu có giá trị $0$ ở trạng thái $0$, còn lại $-\infty$. Đáp án của $S_i$ là $\max_j M_i[0][j]$.

## Vì sao không thể chỉ nhân đáp án với số lần lặp?

Dãy $[2,1]$ có đáp án $1$. Lặp hai lần thành $[2,1,2,1]$ có đáp án $2$. Nhưng với $[1,2]$, đáp án một bản là $2$, còn hai bản $[1,2,1,2]$ chỉ có đáp án $3$, không phải $4$. Trạng thái giá trị cuối tại ranh giới hai bản quyết định cách nối dãy con.

## Chứng minh đúng

Ma trận một phần tử mô tả đầy đủ và chính xác hai lựa chọn bỏ hoặc lấy. Khi nối hai khối, mọi dãy con hợp lệ có một trạng thái trung gian là giá trị cuối sau khối thứ nhất. Tối ưu trên các trạng thái này chính là tích max-plus. Ngược lại, ghép hai phương án theo cùng trạng thái trung gian luôn tạo một dãy con hợp lệ.

Theo quy nạp trên thứ tự chỉ dẫn, mỗi ma trận được lưu là phép biến đổi đúng của dãy tương ứng. Lũy thừa là phép nối nhiều bản, nên cũng đúng. Khởi đầu ở trạng thái rỗng và tối ưu trên trạng thái cuối cho đáp án cần tìm.

## Độ phức tạp và lưu ý

Đặt $d=C+1\le6$. Mỗi phép nối mất $O(d^3)$; một phép lặp có $k>0$ mất $O(d^3\log(k+1))$. Tổng thời gian chặn trên bởi $O(Nd^3\log(10^{12}+1))$, bộ nhớ $O(Nd^2)$.

Chuyển trạng thái không giảm chỉ số, nên các ma trận đều tam giác trên. Lời giải mẫu chỉ duyệt các bộ chỉ số $i\le k\le j$ khi nhân, giúp giảm hằng số.

Độ dài dãy có thể rất lớn, nên không giải nén dãy. Các tham chiếu có thể trùng nhau, các khối có thể rỗng và phép nối không giao hoán. Dùng `long long` cho giá trị ma trận và số lần lặp.
