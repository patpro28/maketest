## Trạng thái và chuyển

Đặt $F[L][R]$ là tổng chi phí xóa nhỏ nhất để đoạn $S[L\ldots R]$ trở thành đối xứng. Đoạn rỗng hoặc một ký tự có giá trị $0$. Luôn xét hai lựa chọn:

$$F[L][R]=\min\bigl(D_L+F[L+1][R],\ D_R+F[L][R-1]\bigr).$$

Nếu $S_L=S_R$, còn có lựa chọn giữ cả hai đầu:

$$F[L][R]\leftarrow\min(F[L][R],F[L+1][R-1]).$$

Đáp án là $F[1][N]$.

## Tính đúng đắn

Mọi phương án hợp lệ hoặc xóa đầu trái, hoặc xóa đầu phải, hoặc giữ cả hai. Trong trường hợp cuối, hai đầu trở thành hai ký tự ngoài cùng của xâu còn lại, nên phải bằng nhau và phần ở giữa phải đối xứng. Mỗi lựa chọn dẫn tới đúng bài toán con đã nêu; ngược lại mọi chuyển đều tạo phương án hợp lệ. Do xét đủ các trường hợp, lấy chi phí nhỏ nhất cho lời giải tối ưu theo quy nạp.

## Lưu ý về chi phí theo vị trí

**Không được bỏ hai chuyển xóa khi hai đầu bằng nhau.** Chẳng hạn `aaba` có chi phí $1,100,1000,1$: xóa chữ đầu tốn $1$ và giữ `aba`; cố giữ cả hai đầu sẽ tốn ít nhất $100$. Lập luận đổi vị trí của LPS thông thường không bảo toàn chi phí ở bài này.

## Độ phức tạp

Thời gian $O(N^2)$, bộ nhớ $O(N)$ khi nén theo đầu trái; dùng 64 bit cho chi phí, vì tổng có thể tới $5\cdot10^{12}$. Có tối đa ba lựa chọn trên mỗi đoạn, không quá $37507500$ lượt xét chính.
