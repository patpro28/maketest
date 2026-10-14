# Lời giải

## Trạng thái

Mỗi trạng thái lưu `(best, ways)`: trọng số tốt nhất và số cách đạt được, modulo $10^9+7$. Khi cập nhật, thay cả cặp nếu trọng số lớn hơn; cộng số cách nếu trọng số bằng nhau. Trạng thái không đạt được có `best = -INF`. Không dùng `ways == 0` để kiểm tra khả năng đạt được vì số cách có thể chia hết cho modulo.

Duyệt dãy $x$ từ trái sang phải, duy trì:

- `keep[j]`: chọn $j$ chỉ số và ghép với $a_1,\ldots,a_j$, chưa bỏ hệ số nào.
- `drop[j]`: chọn $j$ chỉ số và ghép với $j$ hệ số trong $a_1,\ldots,a_{j+1}$, bỏ đúng một hệ số thuộc **$j$ vị trí đầu tiên**. Hệ số $a_{j+1}$ đã được ghép với chỉ số cuối cùng.

Khởi tạo `keep[0] = (0,1)`, các trạng thái khác không đạt được. Đặc biệt `drop[0]` không đạt được.

## Chuyển trạng thái

Với phần tử mới $x_i$, duyệt $j$ giảm dần từ $\min(k-1,i)$ về $1$. Giữ nguyên các trạng thái để biểu diễn không chọn $x_i$, đồng thời xét:

1. Từ `keep[j-1]`, ghép $a_j$ với $x_i$ để cập nhật `keep[j]`.
2. Từ `drop[j-1]`, ghép $a_{j+1}$ với $x_i$ để cập nhật `drop[j]`.
3. Từ `keep[j-1]`, bỏ $a_j$ rồi ghép $a_{j+1}$ với $x_i$ để cập nhật `drop[j]`.

Duyệt giảm bảo đảm các trạng thái nguồn chưa sử dụng $x_i$, nên mỗi chỉ số chỉ được chọn một lần.

Kết quả là cặp tối ưu khi gộp `drop[k-1]` và `keep[k-1]`. Nhánh thứ hai tương ứng với bỏ $a_k$.

Không thêm phép bỏ một hệ số vào trạng thái sau mỗi lần duyệt $x_i$: làm như vậy có thể đếm một phương án nhiều lần, tùy thời điểm thực hiện phép bỏ. Trong cách trên, việc bỏ $a_j$ luôn xảy ra cùng lần ghép $a_{j+1}$, hoặc sau cùng nếu bỏ $a_k$.

## Chứng minh

Bất biến của `keep` là quy hoạch động chọn dãy con thông thường: một phương án hoặc không dùng chỉ số mới, hoặc dùng nó để ghép hệ số cuối.

Với `drop[j]`, phương án không dùng chỉ số mới đã nằm trong trạng thái cũ. Nếu dùng chỉ số mới, hệ số cuối bắt buộc là $a_{j+1}$. Vị trí bị bỏ hoặc nhỏ hơn $j$ (chuyển từ `drop[j-1]`), hoặc đúng bằng $j$ (chuyển từ `keep[j-1]`). Hai trường hợp rời nhau và bao phủ mọi vị trí được phép bỏ. Mỗi phương án có đúng một trạng thái nguồn và một lần chuyển tương ứng với chỉ số cuối, nên không bị đếm lặp, ngay cả khi các hệ số bằng nhau.

Cuối cùng, các vị trí bỏ từ $1$ đến $k-1$ nằm trong `drop[k-1]`, vị trí bỏ $k$ nằm trong `keep[k-1]`. Hai tập này rời nhau và chứa toàn bộ phương án. Phép gộp cho đúng trọng số tối ưu và số phương án đạt nó.

Nếu $k=1$, không có chuyển trạng thái; đáp án là `keep[0] = (0,1)`.

## Độ phức tạp

Thời gian $O(nk)$, bộ nhớ $O(k)$; không cần lưu dãy $x$. Trị tuyệt đối trọng số không vượt $99\cdot100\cdot10^9=9.9\cdot10^{12}$, nên dùng số nguyên 64 bit.

## Kiểm thử

50 file, mỗi subtask có 10 file (ví dụ thuộc subtask 1). Bao gồm $k=1$, $k=2$, $k=n$, hệ số trùng nhau, toàn hệ số hoặc phần tử bằng $0$, trọng số âm, trọng số cực đại, nhiều nghiệm vượt modulo, và $n=200000,k=100$.

Chạy `python3 custom/dpkset/tests/check.py` từ thư mục gốc để sinh và kiểm tra dữ liệu, kiểm thử lời giải, validator/checker và đối chiếu hash. Khi chủ động thay bộ test, thêm `--update-hashes`. Quy trình này không xuất HTML.
