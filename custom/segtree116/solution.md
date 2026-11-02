### Ý tưởng

Đặt $b_i=[e_i>s_{i+1}]$ với $i<N$, và $b_N=0$. Dấu ngoặc vuông có giá trị $1$ khi mệnh đề đúng, ngược lại bằng $0$. Xây segment tree lưu tổng $b_i$ trên mỗi đoạn. Do các thời điểm bắt đầu cố định, đổi $e_i$ chỉ có thể làm thay đổi $b_i$; nếu $i=N$ thì không có dấu nào thay đổi.

Nếu tổng tại gốc bằng $0$, không có cặp bị chồng. Ngược lại, đi xuống cây: chọn con trái nếu tổng con trái dương; nếu không, chọn con phải. Chỉ số ở lá là câu trả lời.

### Chứng minh tính đúng đắn

Ban đầu, mỗi dấu $b_i$ biểu diễn đúng việc cặp $i,i+1$ bị chồng. Một cập nhật chỉ đổi thời điểm kết thúc của cuộc hẹn $i$, nên chỉ phép so sánh $e_i>s_{i+1}$ có thể đổi; cập nhật dấu này duy trì ý nghĩa của toàn bộ dãy dấu. Tổng trên mỗi nút vì thế luôn bằng số cặp bị chồng trong miền của nút.

Nếu tổng tại gốc bằng $0$ thì không tồn tại cặp cần tìm. Khi tổng dương, nếu con trái có dấu thì chỉ số nhỏ nhất phải nằm trong con trái; nếu không thì phải nằm trong con phải. Lặp lại lựa chọn này đưa đến đúng lá có dấu nhỏ nhất.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian. Mỗi cập nhật hoặc truy vấn mất $O(\log N)$ thời gian; tổng là $O(N+Q\log N)$. Bộ nhớ $O(N)$.

### Lưu ý cài đặt

Dùng so sánh nghiêm ngặt $>$: hai cuộc hẹn tiếp giáp không bị chồng. Khi $N=1$, mọi truy vấn đều trả lời $-1$.
