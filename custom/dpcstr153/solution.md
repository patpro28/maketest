## 1. Chọn xâu làm mốc

Chọn một xâu ngắn nhất $R$, gọi độ dài là $L\le20$. Mọi đáp án đều là dãy con của $R$, nên có thể biểu diễn bằng một tập vị trí được giữ trong $R$.

Dùng mặt nạ $mask$ có $L$ bit. Các bit $1$ chỉ các vị trí được chọn; đọc chúng theo thứ tự tăng dần tạo thành xâu ứng viên $T(mask)$. Có $2^L$ mặt nạ. Các mặt nạ khác nhau có thể tạo cùng nội dung khi $R$ chứa chữ lặp, nhưng vẫn cho cùng độ dài và tính khả thi; việc xét trùng không làm sai đáp án.

Không dựng riêng xâu của từng mặt nạ rồi quét toàn bộ mỗi bản ghi, vì sẽ phải lặp lại nhiều lần việc khớp cùng một tiền tố.

## 2. Đảo biến: từ độ dài sang vị trí khớp sớm nhất

Xét một xâu $S$ khác $R$, có độ dài $N$. Thay vì lưu độ dài tốt nhất với từng tiền tố của $S$, cố định ứng viên bằng $mask$ và lưu:

$$pos[mask]=\text{độ dài tiền tố ngắn nhất của }S\text{ chứa }T(mask)\text{ như một dãy con}.$$

Giá trị $N+1$ biểu diễn không thể khớp. Khởi tạo $pos[0]=0$. Đây là phép đảo biến trạng thái: ứng viên trở thành chỉ số, còn vị trí kết thúc nhỏ nhất trở thành giá trị DP.

Đánh số ký tự của $S$ từ $0$. Tiền xử lý $next[p][c]$: độ dài tiền tố sau khi lấy lần xuất hiện đầu tiên của chữ $c$ ở vị trí không nhỏ hơn $p$. Nếu không có, giá trị là $N+1$. Vì vậy $next[p][c]$ bằng vị trí ký tự tìm được cộng $1$. Bảng được dựng từ phải sang trái trong $O(26N)$; hàng $next[N]$ chỉ chứa giá trị không thể khớp.

Với $mask>0$, gọi $h$ là vị trí bit $1$ cao nhất và $parent$ là mặt nạ sau khi xóa bit này. Khi đó:

$$T(mask)=T(parent)+R_h.$$

Nếu $pos[parent]\le N$, đặt:

$$pos[mask]=next[pos[parent]][R_h].$$

Ngược lại, đặt $pos[mask]=N+1$. Vì $parent<mask$, duyệt mặt nạ theo giá trị tăng dần là đủ. Phải xóa bit cao nhất: ký tự bị xóa là ký tự cuối theo thứ tự vị trí, không phải một ký tự bất kỳ.

## 3. Kết hợp tất cả bản ghi

Duy trì $valid[mask]$, ban đầu đúng với mọi mặt nạ. Sau khi xét một xâu $S$, nếu $pos[mask]>|S|$ thì gán $valid[mask]$ thành sai. Một ứng viên chỉ hợp lệ khi nó khớp được trong mọi xâu.

Các mảng $pos$ được dùng lại sau mỗi xâu; không cần lưu bảng riêng cho từng bản ghi. Có thể bỏ qua mặt nạ đã không hợp lệ, nhưng phải gán $pos[mask]$ thành giá trị không thể khớp để không dùng nhầm kết quả còn sót từ xâu trước. Nếu một mặt nạ hợp lệ thì mặt nạ tiền tố $parent$ của nó cũng hợp lệ, nên cách bỏ qua này không làm mất phương án.

Cuối cùng lấy số bit $1$ lớn nhất trong các mặt nạ còn hợp lệ. Mặt nạ $0$ luôn hợp lệ và bảo đảm đáp án ít nhất bằng $0$.

## 4. Chứng minh tính đúng đắn

**Bổ đề 1.** Với một ứng viên cố định, cách khớp mỗi ký tự tại vị trí sớm nhất có thể cho vị trí kết thúc nhỏ nhất.

Chứng minh bằng quy nạp theo độ dài ứng viên. Xâu rỗng kết thúc trước mọi ký tự. Giả sử phần trước đã kết thúc sớm nhất tại tiền tố dài $p$. Bất kỳ cách khớp nào khác của phần trước đều kết thúc không sớm hơn $p$, nên lần xuất hiện tiếp theo dùng để khớp ký tự mới không thể sớm hơn lần xuất hiện đầu tiên tính từ $p$. Chuyển bằng bảng $next$ đạt được chính vị trí đó.

**Bổ đề 2.** Sau khi xử lý một bản ghi, DP xác định đúng mọi mặt nạ có khớp được trong bản ghi ấy hay không.

Mỗi chuyển nối ký tự cuối $R_h$ vào đúng phần ứng viên trước đó. Theo bổ đề 1, nếu vị trí kết thúc sớm nhất vẫn vượt xâu thì không có cách khớp khác; nếu nằm trong xâu thì tồn tại cách khớp hợp lệ. Thứ tự tăng dần của mặt nạ bảo đảm đã tính đúng trạng thái tiền tố.

**Kết luận.** Sau mọi bản ghi, $valid[mask]$ đúng khi và chỉ khi $T(mask)$ là dãy con của tất cả các xâu. Mọi dãy con chung đều xuất phát từ một tập vị trí của $R$, nên được xét bởi ít nhất một mặt nạ. Lấy số bit lớn nhất trong các mặt nạ hợp lệ do đó cho đúng độ dài tối ưu.

Không thay tập ứng viên bằng một LCS duy nhất của hai xâu đầu rồi tiếp tục ghép với xâu thứ ba: một lựa chọn tối ưu cho hai xâu có thể làm mất phương án chung tốt nhất của cả nhóm.

## 5. Độ phức tạp và cài đặt

Gọi $T=\sum_i|S_i|$ và $N_{max}=\max_i|S_i|$.

- Thời gian: $O(26T+K2^L)$.
- Bộ nhớ: $O(T+26N_{max}+2^L)$, bao gồm các xâu đầu vào.

Với $K\le40,L\le20,T\le100000$, có tối đa khoảng $26\cdot100000+39\cdot2^{20}+2\cdot2^{20}<5\cdot10^7$ lượt xử lý chính, kể cả tiền xử lý mặt nạ và tìm đáp án.

Chỉ số sau khi khớp ký tự phải tăng lên một đơn vị; nếu giữ nguyên chỉ số, một lần xuất hiện có thể bị dùng nhiều lần. Chọn xâu ngắn nhất ở vị trí bất kỳ, không giả sử xâu đầu là xâu mốc. Số nguyên 32 bit đủ cho các vị trí, mặt nạ và đáp án.
