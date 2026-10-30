# Lời giải DTMATKHAU — Đường đi có thể đối xứng

## Điều kiện hoán vị thành đối xứng

Một tập chữ có thể sắp thành xâu đối xứng khi và chỉ khi có không quá một chữ xuất hiện số lần lẻ. Đặt $mask(v)$ là mặt nạ $10$ bit biểu diễn tính chẵn/lẻ số lần xuất hiện các chữ trên đường từ gốc tới $v$.

Mặt nạ của đường $x\leftrightarrow y$ là $mask(x)\oplus mask(y)$: phần đường chung từ gốc tới LCA xuất hiện hai lần nên tự triệt tiêu. Vì chữ nằm trên **cạnh**, không cần thêm chữ tại LCA.

Với một đầu mút $x$, mặt nạ đầu mút còn lại $y$ chỉ có thể là

$$mask(x),\quad mask(x)\oplus2^0,\quad\ldots,\quad mask(x)\oplus2^9.$$

Mười một mặt nạ này khác nhau, nên không làm một đầu mút bị đếm nhiều lần.

## Kết hợp giới hạn độ dài và LCA

Nếu LCA của $x,y$ bằng $u$, ta có

$$\operatorname{dist}(x,y)=depth(x)+depth(y)-2depth(u).$$

Điều kiện độ dài tương đương

$$depth(y)\le 2depth(u)+K_u-depth(x).$$

Do đó cần một cấu trúc cho từng mặt nạ: thêm/xóa một đỉnh tại độ sâu cho trước và đếm số đỉnh có độ sâu không vượt một ngưỡng.

## Fenwick riêng cho từng mặt nạ

Trước khi chạy Sack, gom các độ sâu của những đỉnh có cùng mặt nạ, sắp xếp và loại trùng trong từng nhóm. Mỗi mặt nạ có một Fenwick trên danh sách tọa độ riêng. Tổng số tọa độ của mọi nhóm không vượt $N$.

Khi thêm/xóa đỉnh $v$, chỉ sửa Fenwick của $mask(v)$ tại tọa độ tương ứng với $depth(v)$. Nhiều đỉnh có cùng mặt nạ và độ sâu vẫn được đếm đủ bằng số lượng tại cùng một tọa độ.

Để truy vấn cho $x$ tại LCA $u$, xét 11 mặt nạ nêu trên. Với mỗi mặt nạ, dùng `upper_bound` tìm số tọa độ không vượt ngưỡng rồi lấy tổng tiền tố Fenwick. Nhóm rỗng hoặc ngưỡng âm cho kết quả $0$.

## Sack để chỉ đếm các cặp có LCA chính xác

Xử lý các con nhẹ và dọn dữ liệu của chúng, sau đó xử lý con nặng và giữ dữ liệu. Tại đỉnh $u$, với mỗi cây con nhẹ $v$:

1. Duyệt mọi đỉnh $x$ trong cây con $v$, truy vấn 11 mặt nạ với giới hạn độ sâu và cộng vào đáp án tại $u$.
2. Sau khi truy vấn xong cả cây con $v$, mới đưa các đỉnh của nó vào cấu trúc.

Bảng đang giữ chứa con nặng và các con nhẹ đã gộp trước đó. Do đó hai đầu mút ở hai nhánh khác nhau, và LCA đúng bằng $u$. Không cộng đáp án của các đỉnh con vào đáp án của $u$.

Sau khi gộp hết các con, dùng chính $x=u$ để truy vấn một lần nữa, rồi mới thêm $u$. Bước này tính các cặp có một đầu mút bằng $u$. Vì $u$ chưa được thêm, không tính cặp trùng hai đầu mút, kể cả khi $K_u=0$.

Nếu không giữ dữ liệu của cây con $u$, duyệt đoạn Euler của nó và xóa từng đỉnh khỏi Fenwick tương ứng.

## Chứng minh đúng

Mỗi cặp có LCA bằng $u$ hoặc nối hai nhánh con khác nhau, hoặc có một đầu mút là $u$. Với loại thứ nhất, cặp được xét đúng một lần khi nhánh gộp sau truy vấn nhánh gộp trước. Với loại thứ hai, cặp được xét ở bước cuối trước khi thêm $u$.

Ở mỗi lần xét, điều kiện mặt nạ tương đương khả năng hoán vị thành đối xứng, còn điều kiện độ sâu tương đương giới hạn độ dài. Vì vậy mọi cặp được tính đều hợp lệ và mọi cặp hợp lệ đều được tính đúng một lần. Quy trình giữ/xóa của Sack bảo đảm không có đỉnh ngoài các nhánh cần xét lọt vào cấu trúc.

## Độ phức tạp và lưu ý

Mỗi đỉnh được duyệt qua $O(\log N)$ cây con nhẹ. Mỗi lần truy vấn cần 11 tổng tiền tố với tìm tọa độ trong $O(\log N)$; mỗi lần thêm/xóa mất $O(\log N)$. Tổng thời gian $O(11N\log^2N)$, bộ nhớ $O(N+2^{10})$.

Không cấp một Fenwick độ dài $N$ cho từng mặt nạ; phải nén riêng để giữ bộ nhớ tuyến tính. Dùng `long long` cho tổng số cặp. Lời giải mẫu xây mặt nạ, thứ tự Euler và các pha Sack không đệ quy, xử lý được cây dây dài $10^5$.
