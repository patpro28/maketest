## Ý tưởng và thuật toán

Gọi nhu cầu hai công trình là $A,B$. Nếu chỉ có một công trình, đặt $B=0$ và không cấp gói nào cho công trình giả thứ hai.

Sau khi xử lý một số gói, đặt $dp[x][y]$ là số cách cấp tổng $x$ cho công trình thứ nhất và tổng $y$ cho công trình thứ hai. Ban đầu $dp[0][0]=1$.

Với gói có giá trị $b$, có ba lựa chọn: không dùng, cấp cho công trình thứ nhất, hoặc cấp cho công trình thứ hai. Do đó

$$dp_{new}[x][y]=dp_{old}[x][y]+[x\ge b]dp_{old}[x-b][y]+[y\ge b]dp_{old}[x][y-b].$$

Có thể cập nhật ngay trên một bảng khi duyệt cả $x$ và $y$ giảm dần: các ô nguồn có một tọa độ nhỏ hơn và chưa được cập nhật ở lượt hiện tại. Mọi phép cộng lấy modulo $10^9+7$. Đáp án là $dp[A][B]$.

## Chứng minh tính đúng đắn

Bất biến của bảng đúng khi chưa xét gói nào. Khi xét gói mới, mỗi phương án thuộc đúng một trong ba trường hợp tùy nơi gói được cấp. Bỏ quyết định của gói này cho ra một phương án ở trạng thái nguồn tương ứng, và ngược lại mỗi phương án nguồn mở rộng duy nhất thành phương án của trường hợp đó. Ba trường hợp rời nhau và đầy đủ, nên truy hồi bảo toàn bất biến. Ô cuối cùng đếm chính xác các phương án đủ cả hai nhu cầu.

## Độ phức tạp

Mỗi bộ dữ liệu tốn $O(m(A+1)(B+1))$ thời gian và $O((A+1)(B+1))$ bộ nhớ. Mỗi lần cộng hai số đã lấy dư không vượt $2\cdot10^9+12$, vẫn nằm trong số nguyên có dấu 32 bit.
