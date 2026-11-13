## Thêm một vị trí phụ

Thêm vào cuối $A$ giá trị $a_*=A_1\oplus\cdots\oplus A_N$, và tương tự thêm $b_*$ vào $B$. Khi thay $A_i$ bằng XOR hiện tại, XOR mới chính là giá trị cũ của $A_i$. Vì vậy một thao tác tương đương đổi chỗ vị trí $i$ với vị trí phụ.

Các phép đổi chỗ với vị trí phụ sinh được mọi hoán vị của $N+1$ vị trí. Do đó hai dãy mở rộng có thể biến đổi thành nhau khi và chỉ khi hai đa tập giá trị bằng nhau. Nếu khác, đáp án là $-1$.

## Đồ thị của các vị trí sai

Với mỗi vị trí sai trong hai dãy mở rộng, tạo cạnh có hướng từ giá trị hiện tại sang giá trị cần có. Bỏ các vị trí đã đúng. Mỗi đỉnh là một giá trị phân biệt. Hai đa tập bằng nhau bảo đảm bậc vào bằng bậc ra tại mọi đỉnh.

Gọi $m$ là số vị trí sai trong $N$ vị trí thật, $c$ là số thành phần liên thông có cạnh của đồ thị khi bỏ hướng, và $h=1$ nếu giá trị $a_*$ thuộc một thành phần có cạnh, ngược lại $h=0$. Đáp án là

$$m+c-h.$$

Nén tọa độ các giá trị, dùng DSU để nối hai đầu từng cạnh sai và đếm các thành phần.

## Chứng minh số thao tác

Mỗi vị trí thật đang sai phải được thay ít nhất một lần, đóng góp cận dưới $m$. Với mỗi thành phần không chứa giá trị ban đầu ở vị trí phụ, thao tác đầu tiên đi vào thành phần đưa một giá trị bên ngoài vào một vị trí thật. Vị trí đó chưa thể đúng và phải được thay thêm ít nhất một lần. Có $c-h$ thành phần như vậy, suy ra cận dưới $m+c-h$.

Mỗi thành phần có cạnh là một đồ thị có hướng cân bằng và liên thông yếu, nên các cạnh của nó có thể đi theo một chu trình Euler. Đọc chu trình theo chiều ngược: khi vị trí phụ đang giữ giá trị đích của cạnh tiếp theo, đổi nó với vị trí thật của cạnh đó; vị trí thật được sửa đúng, còn vị trí phụ nhận giá trị cần cho cạnh kế tiếp. Nhờ đó xử lý toàn bộ thành phần chứa giá trị phụ mà mỗi vị trí thật chỉ bị thay một lần. Nếu vị trí phụ cũng sai, cạnh phụ nối $a_*$ tới $b_*$ được bỏ khỏi chu trình, tạo đường xử lý kết thúc với giá trị phụ đúng.

Với một thành phần khác, chọn một vị trí để đổi với vị trí phụ trước, đi vòng qua các cạnh còn lại rồi đổi lại vị trí mở đầu. Mỗi vị trí sai được sửa và chỉ vị trí mở đầu cần thêm một lần. Sau đó vị trí phụ trở về giá trị trước khi vào thành phần. Tổng số thao tác đạt cận dưới trên.

## Độ phức tạp

$O(N\log N)$ thời gian do sắp xếp, nén tọa độ; $O(N)$ bộ nhớ. Giá trị trùng nhau phải được xem là cùng một đỉnh, không gán tùy tiện thành các hoán vị khác nhau.
