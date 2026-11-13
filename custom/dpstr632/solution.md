## Trạng thái và chuyển

Đặt $F[L][R]$ là số cách chọn dãy con đối xứng **không rỗng** theo vị trí trong đoạn $S[L\ldots R]$. Đoạn rỗng có giá trị $0$; đoạn một ký tự có giá trị $1$.

Nếu $S_L\ne S_R$:

$$F[L][R]=F[L+1][R]+F[L][R-1]-F[L+1][R-1].$$

Nếu $S_L=S_R$:

$$F[L][R]=F[L+1][R]+F[L][R-1]+1.$$

Mọi phép tính lấy modulo $10^9+7$; đáp án là $F[1][N]$.

## Tính đúng đắn

Các cách không dùng đồng thời hai đầu là hợp của các cách bỏ đầu trái và bỏ đầu phải. Cách bỏ cả hai bị đếm hai lần, nên trừ số cách của đoạn trong. Nếu hai đầu khác nhau thì không thể giữ cả hai, công thức thứ nhất là đủ. Nếu hai đầu bằng nhau, giữ cả hai cho $F[L+1][R-1]+1$ cách mới: ghép với mỗi dãy con đối xứng không rỗng ở trong, hoặc chỉ chọn hai đầu. Cộng số này vào hợp vừa tính sẽ triệt tiêu số hạng trừ, cho công thức thứ hai. Mỗi cách ở đây được xác định bởi bộ vị trí, nên không gộp các nội dung trùng nhau.

## Độ phức tạp và cài đặt

Thời gian $O(N^2)$, bộ nhớ $O(N)$ với một hàng và ô chéo tạm; tối đa $12502500$ ô. Chuẩn hóa số dư sau phép trừ. Không cộng cách chọn rỗng vào đáp án.
