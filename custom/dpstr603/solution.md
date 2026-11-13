## Trạng thái và chuyển

Đặt $F[L][R]$ là độ dài dãy con đối xứng dài nhất trong $S[L\ldots R]$. Đoạn rỗng có giá trị $0$, đoạn một ký tự có giá trị $1$.

- Nếu $S_L=S_R$, lấy $F[L][R]=F[L+1][R-1]+2$.
- Nếu hai chữ khác nhau, lấy $F[L][R]=\max(F[L+1][R],F[L][R-1])$.

Đáp án là $F[1][N]$.

## Tính đúng đắn

Nếu hai đầu khác nhau, một dãy con đối xứng không thể dùng cả hai làm ký tự ngoài cùng, nên phải bỏ ít nhất một đầu. Nếu hai đầu bằng nhau, có thể thêm cả hai vào một dãy con tối ưu ở trong. Luôn tồn tại một phương án tối ưu dùng cả hai: nếu phương án cũ không dùng đầu nào, thêm hai đầu chỉ có lợi; nếu chỉ dùng một đầu, thay vị trí ghép với đầu ấy bằng đầu còn lại giữ được độ dài; nếu chỉ có một ký tự thì chọn cả hai không kém hơn. Vì vậy công thức xét một lựa chọn tối ưu trong mọi trường hợp. Quy nạp theo độ dài đoạn chứng minh kết quả.

## Độ phức tạp và cài đặt

Duyệt $L$ giảm dần, $R$ tăng dần; nén thành một hàng, giữ ô chéo cũ trong biến tạm. Thời gian $O(N^2)$, bộ nhớ $O(N)$, tối đa $12502500$ ô. Cần phân biệt dãy con có thể bỏ ký tự với đoạn liên tiếp.
