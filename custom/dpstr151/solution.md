# Lời giải — DPSTR151

Đặt $dp[i][j][t]$ là độ dài lớn nhất của một dãy chung của hai tiền tố dùng không quá $t$ nguyên âm, với $0\le t\le K$. Mọi biên có một tiền tố rỗng đều bằng $0$.

Luôn thử bỏ ký tự cuối của một trong hai tiền tố. Khi $A_i=B_j$, đặt $v=1$ nếu chữ này là nguyên âm, ngược lại $v=0$. Nếu $t\ge v$, có thể ghép hai ký tự cuối để cập nhật bằng $dp[i-1][j-1][t-v]+1$.

Một dãy chung hợp lệ hoặc bỏ một trong hai vị trí cuối, hoặc dùng cả hai như một cặp ghép. Trường hợp ghép tiêu thụ đúng $v$ đơn vị giới hạn; phần trước còn tối đa $t-v$. Do đó phép chuyển xét đủ mọi dãy hợp lệ và không tạo ra dãy vượt giới hạn. Quy nạp chứng minh trạng thái đúng; đáp án là $dp[N][M][K]$.

Chỉ cần hai lớp theo chỉ số $i$. Khi $K=0$, không được chọn bất kỳ nguyên âm nào; một nguyên âm lặp nhiều lần vẫn tiêu thụ giới hạn ở từng lần chọn.

Độ phức tạp thời gian $O(NM(K+1))$, bộ nhớ của phần DP $O((K+1)M)$.
