## Ý tưởng

Gọi một vị trí bắt đầu $i$ là tốt nếu $S_iS_{i+1}S_{i+2}=\texttt{ABC}$. Duy trì tổng số vị trí tốt. Khi gán ký tự tại $x$, chỉ ba vị trí bắt đầu $x-2,x-1,x$ có thể thay đổi trạng thái.

Trước phép gán, trừ đóng góp của ba vị trí hợp lệ này; thực hiện phép gán; sau đó cộng đóng góp mới. Một vị trí hợp lệ phải nằm trong $[1,N-2]$.

## Tính đúng đắn

Mọi xâu con dài ba không chứa vị trí $x$ giữ nguyên. Những xâu con chứa $x$ chính xác là ba vị trí bắt đầu đã xét, sau khi loại vị trí vượt biên. Vì vậy việc thay thế đóng góp cũ bằng đóng góp mới duy trì đúng tổng số lần xuất hiện sau mỗi truy vấn.

## Độ phức tạp

Khởi tạo $O(N)$; mỗi truy vấn $O(1)$. Tổng thời gian $O(N+Q)$, bộ nhớ $O(N)$.
