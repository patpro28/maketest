# Lời giải — Đoạn ngoặc hợp lệ

### Thông tin tại mỗi nút

Đổi `(` thành $1$, `)` thành $-1$. Mỗi nút lưu tổng `sum` và tổng tiền tố nhỏ nhất `minPrefix`, có xét cả tiền tố rỗng với tổng $0$. Một lá chứa $x$ lưu $(x,\min(0,x))$.

### Phép ghép

Ghép đoạn trái $L$ và đoạn phải $R$: `sum = L.sum + R.sum`, `minPrefix = min(L.minPrefix, L.sum + R.minPrefix)`. Nút trung hòa là $(0,0)$.

### Xử lý thao tác

Dựng cây một lần rồi truy vấn các đoạn. Mỗi truy vấn ghép các đoạn con rời nhau theo thứ tự trái sang phải để thu được thông tin của đoạn cần hỏi.

Xâu con là dãy ngoặc đúng khi và chỉ khi `sum == 0` và `minPrefix >= 0`. Phải ghép các đoạn theo thứ tự từ trái sang phải; tổng tiền tố được tính tương đối từ đầu xâu con được hỏi.

### Tính đúng đắn

Thông tin tại mỗi lá đúng theo định nghĩa. Tiền tố của một đoạn ghép nằm hoàn toàn bên trái hoặc gồm cả đoạn trái và một tiền tố bên phải, nên công thức ghép tổng tiền tố nhỏ nhất là đúng. Bằng quy nạp theo chiều cao cây, mọi nút đều đúng sau khi dựng cây. Truy vấn ghép đúng các đoạn con phủ đoạn cần hỏi; kết hợp với công thức tính đáp án ở trên, kết quả được in là đúng.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian; mỗi truy vấn mất $O(\log N)$ thời gian. Tổng thời gian $O(N+Q\log N)$, bộ nhớ $O(N)$.
