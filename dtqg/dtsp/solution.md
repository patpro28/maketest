## Xếp các nắp vào từng nhóm

Có thể xét một thứ tự lấy từng nắp. Mỗi khi điểm nhóm đang mở đạt ít nhất $s$, đổi ngay một chú gấu và bắt đầu nhóm mới, bỏ phần điểm vượt mức.

Cách biểu diễn này không làm giảm số gấu tối ưu. Với một cách chia thành các nhóm hợp lệ bất kỳ, đặt nắp của từng nhóm cạnh nhau trong thứ tự lấy. Trong mỗi nhóm, lần đầu đạt ngưỡng đã nhận được một chú gấu; những nắp còn lại có thể được dùng cho các nhóm tiếp theo. Lặp lại việc kết thúc nhóm sớm không làm số nhóm nhận được ít hơn. Ngược lại, mỗi nhóm được tạo trong quá trình lấy nắp là một lần đổi hợp lệ.

## Chỉ giữ tiến độ tốt nhất

Gọi một tiến độ gồm $g$ chú gấu đã nhận và $r$ điểm ở nhóm đang mở, $0\le r<s$. Mã hóa thành

$$P=gs+r.$$

Giá trị lớn hơn nghĩa là đã nhận nhiều gấu hơn, hoặc cùng số gấu nhưng còn nhiều điểm hơn. Nếu thêm nắp giá trị $v\in\{1,2,3\}$ thì

$$F_v(P)=\begin{cases}P+v,&P\bmod s+v<s,\\P+s-(P\bmod s),&P\bmod s+v\ge s.\end{cases}$$

Một nắp chỉ tạo tối đa một chú gấu, kể cả khi $v>s$.

Hàm $F_v$ không giảm theo $P$: trong cùng một khoảng $gs\le P<(g+1)s$, nó tăng rồi có thể giữ nguyên khi đã vượt ngưỡng; chuyển sang khoảng tiếp theo cũng không làm giá trị giảm. Vì vậy, với cùng tập nắp đã dùng, chỉ cần giữ tiến độ lớn nhất. Bất kỳ dãy nắp nối thêm nào cũng duy trì quan hệ trội này.

## Công thức DP

Đặt $dp[i][j][k]$ là tiến độ lớn nhất sau khi dùng đúng $i$ nắp loại $1$, $j$ nắp loại $2$ và $k$ nắp loại $3$. Khởi tạo $dp[0][0][0]=0$.

Với mỗi trạng thái, lấy lớn nhất trong các chuyển tồn tại:

$$F_1(dp[i-1][j][k]),\quad F_2(dp[i][j-1][k]),\quad F_3(dp[i][j][k-1]).$$

Duyệt các chỉ số tăng dần. Đáp án là $\lfloor dp[a][b][c]/s\rfloor$. Có thể dùng hết nắp vì thêm nắp không làm số gấu giảm; phần dư cuối không cần đủ ngưỡng.

## Chứng minh đúng

Mọi thứ tự dùng nắp có một nắp cuối thuộc một trong ba loại, nên thuộc một chuyển được DP xét. Thay tiến độ của phần trước bằng tiến độ lớn nhất không làm chuyển cuối kém hơn do tính đơn điệu của $F_v$. Quy nạp theo $i+j+k$ cho thấy DP tìm đúng tiến độ lớn nhất của mọi thứ tự dùng nắp.

Các nhóm tạo ra đều hợp lệ, và biểu diễn bằng thứ tự lấy nắp có thể đạt số nhóm của một cách đổi tối ưu. Do đó phần nguyên của tiến độ cuối chia $s$ là số gấu lớn nhất.

## Độ phức tạp

Có $(a+1)(b+1)(c+1)\le271^3=19902511$ trạng thái, mỗi trạng thái xét tối đa ba chuyển hằng số. Thời gian $O((a+1)(b+1)(c+1))$. Dùng hai lớp theo $i$ để có bộ nhớ $O((b+1)(c+1))$.

Không được lấy ngay $\lfloor(a+2b+3c)/s\rfloor$: các nắp không thể chia nhỏ và điểm vượt mức không chuyển sang nhóm khác.
