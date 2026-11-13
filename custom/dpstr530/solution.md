Xét bài toán trên hai tiền tố như khoảng cách chỉnh sửa. Nếu ký tự đích hiện tại là `?` và được ghép với ký tự nguồn, điền nó bằng chính ký tự nguồn nên chi phí ghép bằng $0$. Nếu chèn vào một dấu hỏi, có thể điền chữ bất kỳ và chi phí vẫn bằng $1$. Với vị trí cố định, phí ghép là $0$ nếu bằng nhau và $1$ nếu khác nhau.

Mỗi vị trí đích được xử lý đúng một lần. Việc điền một dấu hỏi không ràng buộc vị trí nào khác, nên có thể lấy chi phí nhỏ nhất của từng bước một cách độc lập. Một phương án thực hiện được tương ứng với đường đi qua các tiền tố, và mỗi đường đi xác định được cách điền và chuỗi thao tác hợp lệ.

Khởi tạo phí cho tiền tố rỗng bằng số ký tự cần chèn hoặc xóa. Nén theo hàng để có thời gian $O(NM)$ và bộ nhớ $O(M)$.
