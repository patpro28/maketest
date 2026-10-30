# Lời giải HANHTRINH — Hành trình đúng số chặng

## Từ quy hoạch động tới phép nhân max-plus

Đặt $f_d(v)$ là tổng điểm lớn nhất khi xuất phát tại $S$, đi đúng $d$ chặng và dừng ở $v$. Khởi tạo $f_0(S)=0$, các trạng thái còn lại không thể đạt tới, ký hiệu $-\infty$.

Với mỗi tuyến $u\to v$ có điểm $w$:

$$f_{d+1}(v)=\max_{u\to v}\big(f_d(u)+w(u,v)\big).$$

Nếu có nhiều tuyến cùng đầu mút, chỉ cần giữ tuyến có điểm lớn nhất. Gọi $A[u][v]$ là điểm đó; nếu không có tuyến thì đặt $A[u][v]=-\infty$.

Ta dùng vector hàng $f_d$. Định nghĩa tích max-plus:

$$ (B\otimes C)[i][j]=\max_k\big(B[i][k]+C[k][j]\big). $$

Phép cộng thông thường trong nhân ma trận được thay bằng lấy max; phép nhân được thay bằng cộng. Khi một trong hai số hạng là $-\infty$, bỏ qua phương án đó. Công thức DP trở thành $f_{d+1}=f_d\otimes A$.

## Ý nghĩa của lũy thừa

Khẳng định $A^{\otimes d}[u][v]$ là điểm lớn nhất của hành trình đúng $d$ chặng từ $u$ tới $v$.

- Với $d=1$, đúng theo cách dựng $A$.
- Khi ghép hành trình $p$ chặng từ $u$ tới $k$ và hành trình $q$ chặng từ $k$ tới $v$, tổng điểm là tổng hai phần. Chọn tốt nhất trên mọi $k$ chính là phép nhân max-plus.

Do đó $A^{\otimes(p+q)}=A^{\otimes p}\otimes A^{\otimes q}$. Phép nhân có tính kết hợp vì cả hai cách đặt ngoặc đều tối ưu trên cùng các trạng thái trung gian và cộng cùng các trọng số. Có thể áp dụng lũy thừa nhị phân như ma trận thông thường.

Ma trận đơn vị là:

$$I[i][j]=\begin{cases}0&i=j,\\-\infty&i\ne j.\end{cases}$$

Nó biểu diễn một đoạn hành trình có không chặng. Đáp án là $A^{\otimes K}[S][T]$; nếu bằng $-\infty$ thì in `IMPOSSIBLE`.

## Những điểm dễ nhầm

- Cần **đúng** $K$ chặng. Không tự thêm số $0$ lên đường chéo của $A$; làm vậy tạo ra quyền đứng yên mà đề không cho phép.
- Trọng số âm vẫn là trạng thái hợp lệ. Chỉ $-\infty$ mới có nghĩa không thể đạt tới.
- Với $K=0$, dùng ma trận đơn vị: đáp án bằng $0$ nếu $S=T$, ngược lại không tồn tại.
- Trong chương trình dùng `NEG = -4e18`, khác mọi đáp án hợp lệ. Không cộng một phần tử bằng `NEG` với phần tử khác.
- Với phép ghép $B\otimes C$, hành trình trong $B$ được thực hiện trước hành trình trong $C$.

## Độ phức tạp

Mỗi phép nhân mất $O(N^3)$, có $O(\log(K+1))$ phép nhân. Tổng thời gian $O(M+N^3\log(K+1))$, bộ nhớ $O(N^2)$. Nếu $K$ nhỏ, có thể dùng DP theo số chặng trong $O(KM)$.
