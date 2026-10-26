# Lời giải — Mã kiểm tra

### Thông tin tại mỗi nút

Mỗi nút lưu XOR của tất cả phần tử trên đoạn. Một lá chứa $x$ lưu chính $x$.

### Phép ghép

Ghép hai nút bằng XOR. Giá trị trung hòa là $0$, vì $x\oplus0=x$.

### Xử lý thao tác

Dựng cây một lần rồi truy vấn các đoạn. Mỗi truy vấn ghép các đoạn con rời nhau theo thứ tự trái sang phải để thu được thông tin của đoạn cần hỏi.

Dựng cây một lần rồi trả lời truy vấn đoạn. Phép XOR có tính kết hợp, nên XOR các kết quả trên các đoạn con rời nhau bằng XOR của cả đoạn.

### Tính đúng đắn

Thông tin tại mỗi lá đúng theo định nghĩa. Phép ghép cho đúng thông tin của đoạn cha khi hai nút con đúng. Bằng quy nạp theo chiều cao cây, mọi nút đều đúng sau khi dựng cây. Truy vấn ghép đúng các đoạn con phủ đoạn cần hỏi; kết hợp với công thức tính đáp án ở trên, kết quả được in là đúng.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian; mỗi truy vấn mất $O(\log N)$ thời gian. Tổng thời gian $O(N+Q\log N)$, bộ nhớ $O(N)$.
