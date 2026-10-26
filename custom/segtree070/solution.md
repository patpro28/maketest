# Lời giải — Tổng có trọng số

### Thông tin tại mỗi nút

Mỗi nút lưu hai tổng $S=\sum A_i$ và $T=\sum iA_i$, với $i$ là chỉ số trong dãy ban đầu. Lá ở vị trí $i$ chứa $x$ lưu $(x,i\cdot x)$.

### Phép ghép

Cộng riêng hai tổng. Nút trung hòa là $(0,0)$.

### Xử lý thao tác

Mỗi lần gán sửa lá tương ứng và tính lại các nút trên đường lên gốc. Mỗi truy vấn ghép các đoạn con rời nhau theo thứ tự trái sang phải để thu được thông tin của đoạn cần hỏi.

Với truy vấn $[l,r]$, đáp án là $T-(l-1)S$ vì trọng số của $A_i$ là $i-l+1$. Dùng số nguyên 64 bit: với giới hạn đề bài, các tổng và các tích trung gian trong công thức đều nằm trong phạm vi số nguyên có dấu 64 bit.

### Tính đúng đắn

Thông tin tại mỗi lá đúng theo định nghĩa. Phép ghép cho đúng thông tin của đoạn cha khi hai nút con đúng. Bằng quy nạp theo chiều cao cây, mọi nút đều đúng sau khi dựng cây. Cập nhật tính lại tất cả nút bị ảnh hưởng nên duy trì tính chất đó. Truy vấn ghép đúng các đoạn con phủ đoạn cần hỏi; kết hợp với công thức tính đáp án ở trên, kết quả được in là đúng.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian; mỗi cập nhật hoặc truy vấn mất $O(\log N)$ thời gian. Tổng thời gian $O(N+Q\log N)$, bộ nhớ $O(N)$.
