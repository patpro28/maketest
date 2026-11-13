## Kết quả chỉ phụ thuộc các số mũ

Mỗi thừa số của $N$ được biểu diễn bởi một vectơ số mũ của $p_1,\ldots,p_m$. Một cách phân tích là một đa tập các vectơ khác không, có tổng bằng $(k,k,\ldots,k)$. Đổi tên các số nguyên tố không thay đổi các đa tập này.

Vì vậy, đáp án chỉ phụ thuộc cặp $(m,k)$. Phân tích từng $N$ bằng danh sách các số nguyên tố không vượt $10^6$, rồi lưu kết quả đã tính theo cặp $(m,k)$ để dùng lại giữa các bộ dữ liệu.

## Trường hợp không có số mũ lặp

Khi $k=1$, mỗi số nguyên tố chỉ xuất hiện trong đúng một thừa số. Một cách phân tích tương ứng với một cách chia $m$ phần tử phân biệt thành các nhóm không rỗng; mỗi nhóm tạo một thừa số.

Số cách chia là số Bell $B_m$. Đáp án bằng $B_m-1$, bỏ trường hợp chỉ có một nhóm. Có thể tính số Bell bằng tam giác Bell: bắt đầu hàng $[1]$; phần tử đầu của hàng mới là phần tử cuối hàng trước, mỗi phần tử tiếp theo bằng phần tử bên trái cộng phần tử phía trên bên trái. Phần tử đầu hàng $m$ là $B_m$.

## DP trên các ước khi k lớn hơn 1

Chọn số chuẩn $N_0=q_1^k\cdots q_m^k$ với $q_i$ là $m$ số nguyên tố nhỏ nhất. Số này không lớn hơn $N$, nên vẫn không vượt $10^{12}$.

Liệt kê và sắp tăng mọi ước $d_0=1<d_1<\cdots<d_{D-1}=N_0$. Đặt $f[d]$ là số cách tạo tích $d$ bằng các thừa số đã xét. Ban đầu $f[1]=1$.

Duyệt từng thừa số được phép $x$ trong các ước thỏa $2\le x<N_0$, theo thứ tự tăng. Với mỗi ước $d\ge x$ được duyệt tăng, nếu $x\mid d$, cập nhật

$$f[d]\mathrel{+}=f[d/x].$$

Duyệt $d$ tăng cho phép dùng $x$ nhiều lần, còn đặt $x$ ở vòng ngoài đếm theo đa tập thay vì đếm thứ tự. Dùng bảng ánh xạ từ giá trị ước sang chỉ số để truy cập $f[d/x]$.

Không xét $N_0$ làm thừa số, nên $f[N_0]$ tự loại cách phân tích chỉ có một thừa số. Mọi cách còn lại đều có ít nhất hai thừa số từ $2$ trở lên.

## Chứng minh đúng

Trong lượt của thừa số $x$, các cách tạo $d$ được chia thành không dùng $x$ và có dùng $x$. Bỏ một thừa số $x$ trong nhóm thứ hai tạo một cách tạo $d/x$ bằng các thừa số đã xét, kể cả $x$. Đây là song ánh. Vì thế cập nhật tại chỗ theo $d$ tăng đếm chính xác số đa tập thừa số.

Sau khi xét mọi ước thực sự lớn hơn $1$, các cách được đếm chính xác là các phân tích hợp lệ của $N_0$. Song ánh qua các vectơ số mũ đưa chúng về các phân tích của $N$, nên kết quả đúng.

## Độ phức tạp và lưu ý

Sàng số nguyên tố mất $O(10^6\log\log10^6)$. Thử chia mỗi đầu vào qua tối đa $\pi(10^6)=78498$ số nguyên tố; dừng sớm khi bình phương số nguyên tố vượt phần còn lại.

Với mỗi cặp $(m,k)$ khác nhau, DP mất $O(D^2)$ lượt xét với $D=(k+1)^m$; các cặp $k=1$ chỉ cần số Bell. Điều kiện $N\le10^{12}$ hạn chế mạnh các cặp này. Với $k>1$, $D$ lớn nhất bằng $3^7=2187$; tổng số cặp ước cần xét trên tất cả các cặp $(m,k)$ có thể có nhỏ hơn $5\cdot10^6$. Bộ nhớ $O(D)$ ngoài danh sách số nguyên tố.

Dùng số nguyên 64 bit cho $N$ và các ước. Miền cặp $(m,k)$ là hữu hạn: chỉ giữ các cặp thỏa $(2\cdot3\cdots q_m)^k\le10^{12}$. Tính theo truy hồi trên miền này cho chặn giá trị lớn nhất $26908755$, đạt tại $(m,k)=(4,5)$; các giá trị DP đều vừa số nguyên 64 bit không dấu.
