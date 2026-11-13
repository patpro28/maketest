Dùng DP khoảng cách chỉnh sửa với ba bước chèn, xóa và ghép. Mỗi đường đi có chi phí không quá $K$ chỉ ghé những ô $(i,j)$ thỏa $|i-j|\le K$, vì chênh lệch này cần ít nhất từng đó bước chèn hoặc xóa. Nếu $|N-M|>K$ có thể trả lời ngay.

Chỉ tính các ô trong dải, và xem giá trị ngoài dải hoặc lớn hơn $K$ là $K+1$. Truy hồi trong dải không bỏ bất kỳ tiền tố nào của đường đi hợp lệ, vì chi phí các bước không âm. Mỗi giá trị không vượt $K$ vẫn đến từ các thao tác hợp lệ. Vì vậy ô cuối cho khoảng cách chính xác khi khoảng cách nằm trong ngân sách.

Mỗi hàng có tối đa $2K+1$ ô cần tính. Dùng hai hàng và đặt ô giáp biên về $K+1$ khi đổi hàng để không đọc dữ liệu cũ. Thời gian $O(N(K+1)+M)$, bộ nhớ $O(M)$ cho DP.
