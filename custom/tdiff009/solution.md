## Ý tưởng

Đặt $C_i=B_i-A_i$ cho $1\le i\le N$ và thêm $C_0=C_{N+1}=0$. Duyệt các hiệu $E_i=C_i-C_{i-1}$ theo thứ tự từ $1$ đến $N+1$.

Một đoạn $[L,R]$ được cộng $X\ne0$ tạo ra đúng hai hiệu khác $0$, là $X$ ở $L$ và $-X$ ở $R+1$. Ghi lại hai mốc khác $0$ đầu tiên và đếm số mốc. Nếu có đúng hai mốc và hai hiệu đối nhau, trả về đoạn từ mốc thứ nhất đến ngay trước mốc thứ hai cùng với hiệu tại mốc thứ nhất. Trong các trường hợp còn lại, in `-1`. Mốc $N+1$ cho phép nhận diện đoạn kết thúc ở vị trí $N$.

## Chứng minh tính đúng đắn

Nếu một phép cập nhật hợp lệ biến $A$ thành $B$, thì $C_i=X$ trên $[L,R]$ và $C_i=0$ bên ngoài. Khi lấy hiệu kề nhau, chỉ hai biên $L$ và $R+1$ có hiệu khác $0$, và hai hiệu đối nhau.

Ngược lại, nếu hai mốc khác $0$ duy nhất là $p<q$, với $E_p=X$ và $E_q=-X$, tổng tiền tố của $E$ bằng $0$ trước $p$, bằng $X$ từ $p$ đến $q-1$ và bằng $0$ từ $q$ trở đi. Tổng tiền tố đó chính là $C$. Vì vậy phép cộng $X$ vào $[p,q-1]$ biến $A$ thành $B$. Hai mốc xác định duy nhất đoạn cần cộng và hiệu tại mốc đầu tiên xác định duy nhất $X$.

## Độ phức tạp

Mỗi bộ test cần thời gian $O(N)$ và bộ nhớ phụ $O(N)$.

## Lưu ý cài đặt

Dùng số nguyên 64 bit cho các hiệu. Hai dãy bằng nhau tạo ra không có mốc khác $0$ và được trả lời bằng `-1`.
