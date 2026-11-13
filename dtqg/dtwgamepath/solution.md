## Ý tưởng và thuật toán

Mọi ô không cấm đều chứa ký tự duy nhất của $S$. Vì vậy mọi đường đi hợp lệ đều tạo xâu đối xứng và chứa $S$. Chỉ cần đếm đường đi tránh ô cấm.

Đặt $f[i][j]$ là số cách đến ô $(i,j)$. Ô cấm có giá trị $0$; ô xuất phát có giá trị $1\bmod D$; các ô còn lại có

$$f[i][j]=(f[i-1][j]+f[i][j-1])\bmod D,$$

coi các vị trí ngoài bảng có giá trị $0$. Đáp án là $f[m][n]$. Duyệt lần lượt từng hàng, chỉ giữ một mảng theo cột. Nếu ô kết thúc bị cấm, đáp án tự bằng $0$.

## Chứng minh tính đúng đắn

Mỗi đường đến một ô không phải ô đầu có bước cuối từ phía trên hoặc từ bên trái. Hai trường hợp rời nhau và bao quát mọi đường đi; truy hồi cộng đúng số đường từ hai ô trước. Ô cấm không thuộc đường hợp lệ nên phải có số cách bằng $0$. Theo quy nạp theo tổng chỉ số hàng và cột, mọi giá trị đều đúng. Điều kiện đồng nhất ký tự bảo đảm mọi đường được đếm đều thắng cuộc.

## Độ phức tạp

Thời gian $O(mn)$, bộ nhớ $O(n)$. Xử lý $D=1$ ngay từ giá trị khởi tạo bằng $1\bmod D$.
