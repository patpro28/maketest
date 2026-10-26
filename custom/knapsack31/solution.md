# Lời giải — Phá khiên trong đúng K lượt

## Trạng thái

Gọi `dp[k][s]` là tổng năng lượng ít nhất sau **đúng** $k$ lần dùng phép, trong đó sát thương thực tế đã được chặn ở $X$:

- $s<X$: tổng sát thương đúng bằng $s$.
- $s=X$: tổng sát thương ít nhất $X$.

Khởi tạo `dp[0][0]=0`, các trạng thái khác bằng vô cùng. Chỉ giữ hai lớp theo số lần dùng phép để tiết kiệm bộ nhớ.

## Chuyển trạng thái

Từ một trạng thái đạt được ở lớp $k$, thử mỗi phép $i$:

$$dp[k+1][\min(X,s+D_i)]=\min\bigl(dp[k+1][\min(X,s+D_i)],dp[k][s]+C_i\bigr).$$

Trước mỗi lượt, phải đặt lớp mới về vô cùng. Không giữ nguyên lớp cũ như một lựa chọn bỏ lượt, vì như vậy sẽ chấp nhận ít hơn $K$ lần dùng phép. Cũng không cập nhật ngay vào lớp đang đọc, vì có thể dùng nhiều phép trong một lượt.

Đặc biệt, vẫn chuyển từ `dp[k][X]` sang `dp[k+1][X]`. Khi đã đủ sát thương, các lượt còn lại vẫn bắt buộc và vẫn phải trả năng lượng. Không trả lời sớm khi lần đầu đạt trạng thái $X$.

Đáp án là `dp[K][X]`, hoặc `-1` nếu không đạt được.

## Vì sao được gộp vào X?

Với cùng số lượt đã dùng, hai tổng sát thương bất kỳ cùng không nhỏ hơn $X$ có khả năng hoàn thành yêu cầu giống nhau: mọi chuỗi phép ở các lượt còn lại đều giữ tổng sát thương không nhỏ hơn $X$ vì sát thương dương. Do đó, chỉ cần giữ phương án ít năng lượng nhất của toàn bộ nhóm này.

Chứng minh bất biến bằng quy nạp: lớp $0$ chỉ có một phương án rỗng. Mỗi phương án sau $k+1$ lượt tách được phép cuối cùng, để lại phương án sau đúng $k$ lượt. Chuyển trạng thái thử mọi loại phép cuối và cộng đúng chi phí; chiều ngược lại, mọi chuyển đều dùng thêm đúng một phép và giữ đúng sát thương đã chặn. Việc lấy nhỏ nhất bảo toàn tối ưu cho từng trạng thái. Kết quả ở lớp $K$, trạng thái $X$ vì vậy là đáp án cần tìm.

Có thể chặn riêng $D_i$ thành $\min(D_i,X)$ trước khi chuyển, nhưng vẫn phải gộp **tổng** vượt $X$ vào trạng thái $X$.

## Vì sao bỏ tổng lớn hơn 2X là sai?

Xét một loại phép có $C=2,D=10$, yêu cầu $K=3,X=10$. Sau ba lượt, tổng sát thương chính xác là $30>2X$, năng lượng bằng $6$. Nếu chỉ lưu các tổng chính xác trong $[0,2X]$ và bỏ phần vượt, toàn bộ nghiệm bị mất.

Trong bài không giới hạn số lượt, có thể bỏ bớt phép để giảm tổng sát thương và giảm chi phí. Ở đây, bỏ một phép vi phạm điều kiện đúng $K$ lần. Ngay cả sau khi chặn từng $D_i$ ở $X$, tổng sát thương chính xác vẫn có thể tới $KX$.

Không bắt buộc mọi cài đặt phải có câu lệnh gộp giống nhau: cách lưu sát thương còn thiếu, chặn về $0$, là một mô hình tương đương. Điểm quan trọng là giữ thông tin "đã đủ sát thương" qua các lượt tiếp theo, thay vì vứt các tổng vượt ngưỡng.

## Độ phức tạp

Thời gian $O(NK(X+1))$, không quá khoảng $2\cdot10^7$ lần thử chuyển. Bộ nhớ $O(N+X)$ khi dùng hai lớp. Mỗi phương án có đúng $K$ phép nên tổng năng lượng không vượt $K\cdot10^9\le2\cdot10^{11}$; dùng số nguyên 64 bit. Cộng sát thương sau khi đã chặn từng $D_i$ tránh phải lưu tổng thực tế tới $2\cdot10^{11}$.

Nếu $K\max_i D_i<X$ thì không có nghiệm; đây cũng là điều kiện cần và đủ cho sự tồn tại, vì có thể lặp phép mạnh nhất $K$ lần. Điều kiện này không giải quyết phần tối ưu năng lượng khi có nhiều lựa chọn.
