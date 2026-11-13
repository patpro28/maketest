## Ý tưởng

Tại trạng thái $(i,d)$, lưu phí nhỏ nhất và số cách đạt phí đó khi đứng ở bậc $i$ và cú nhảy cuối dài $d$. Trạng thái ban đầu $(0,0)$ có phí $0$ và một cách. Giá trị $d=0$ chỉ xuất hiện ở vị trí xuất phát.

Từ $(i,d)$, thử cú nhảy dài $e\in\{1,2,3\}$ khác $d$ và không vượt quá $N$. Ứng viên cho $(i+e,e)$ có phí tăng thêm $A_{i+e}$. Nếu ứng viên có phí thấp hơn, thay cả phí và số cách. Nếu phí bằng nhau, cộng số cách modulo $10^9+7$.

Ở bậc $N$, lấy phí nhỏ nhất trong ba trạng thái kết thúc và cộng số cách của những trạng thái đạt phí đó.

## Chứng minh tính đúng đắn

Vị trí và độ dài cú nhảy cuối xác định đầy đủ các cú nhảy tiếp theo có thể thực hiện. Vì vậy, ở một trạng thái, lộ trình có phí cao hơn không thể cho kết quả tốt hơn khi nối cùng một phần đường còn lại. Mỗi lộ trình có đúng một trạng thái trước cú nhảy cuối, nên khi gộp các chuyển có cùng phí nhỏ nhất, mỗi lộ trình được đếm đúng một lần. Mọi cú nhảy tăng vị trí, do đó xử lý theo thứ tự bậc tăng dần sẽ tính đầy đủ các trạng thái.

## Độ phức tạp

Thời gian và bộ nhớ đều $O(N)$. Dùng số nguyên 64 bit cho tổng phí. Dùng trạng thái phí để kiểm tra khả năng đến bậc, vì số cách của một trạng thái đạt được có thể bằng $0$ sau khi lấy modulo.
