# Lời giải DTHENGAP — Khoảng cách tại điểm gặp

## Những cặp có LCA chính xác bằng u

Với hai đầu mút đều khác $u$, LCA bằng $u$ khi và chỉ khi chúng thuộc hai cây con của hai con khác nhau của $u$. Nếu một đầu mút là $u$, đầu mút còn lại có thể là bất kỳ hậu duệ thực sự nào.

Hai đỉnh cùng nằm trong một cây con của một con sẽ có LCA sâu hơn $u$, nên không được tính tại $u$. Đây là lý do không thể chỉ đưa toàn bộ cây con vào một bảng rồi đếm tất cả các cặp khoảng cách phù hợp.

Đặt độ sâu gốc bằng $0$. Khi LCA của $x,y$ là $u$:

$$\operatorname{dist}(x,y)=depth(x)+depth(y)-2depth(u).$$

Với $x$ cố định, cần tìm các $y$ có

$$\boxed{depth(y)=2depth(u)+K_u-depth(x)}.$$

## Sack và bước truy vấn trước khi thêm

Duy trì mảng $cnt[d]$ là số đỉnh đang giữ ở độ sâu $d$. Chọn con nặng theo kích thước cây con và xử lý các pha Sack như thông thường: con nhẹ được xử lý rồi xóa, con nặng được xử lý và giữ lại.

Khi bắt đầu gộp tại $u$, bảng chỉ chứa cây con của con nặng. Với từng con nhẹ $v$:

1. Duyệt **mọi** đỉnh $x$ trong cây con $v$, cộng $cnt[2depth(u)+K_u-depth(x)]$ vào đáp án tại $u$.
2. Sau khi truy vấn xong toàn bộ cây con $v$, mới thêm các đỉnh của nó vào bảng.

Nhờ vậy, một đỉnh của nhánh đang xét chỉ được ghép với các nhánh đã giữ. Mỗi cặp giữa hai nhánh được tính đúng một lần, tại lúc nhánh được gộp sau đang được truy vấn. Nếu vừa truy vấn vừa thêm từng đỉnh trong cùng một nhánh, sẽ đếm nhầm các cặp có LCA sâu hơn $u$.

Các chỉ số độ sâu nằm ngoài đoạn $[0,N-1]$ có số lượng bằng $0$.

## Đầu mút bằng chính u

Sau khi gộp mọi cây con, bảng chứa tất cả hậu duệ thực sự của $u$, chưa chứa $u$. Cộng thêm

$$cnt[depth(u)+K_u]$$

để tính các cặp $\{u,y\}$. Sau đó mới đưa $u$ vào bảng. Cách này không tính cặp $\{u,u\}$ khi $K_u=0$. Đỉnh lá tự có đáp án bằng $0$.

Nếu pha Sack không yêu cầu giữ dữ liệu, duyệt đoạn Euler của cây con $u$ và giảm bộ đếm của mọi đỉnh trên đoạn đó.

## Chứng minh đúng

Mọi cặp có LCA bằng $u$ thuộc đúng một trong hai loại: hai nhánh con khác nhau hoặc có đầu mút $u$. Với loại thứ nhất, một nhánh được giữ trước nhánh kia; truy vấn trước khi thêm đếm cặp đúng một lần và công thức độ sâu tương đương điều kiện khoảng cách. Với loại thứ hai, bước cuối đếm đúng tất cả hậu duệ ở khoảng cách yêu cầu. Hai loại không giao nhau. Các cặp trong một nhánh không thể xuất hiện trong truy vấn chéo nhánh, nên không có cặp không hợp lệ được tính.

## Độ phức tạp

Mỗi đỉnh chỉ được duyệt lại khi nằm trong một cây con nhẹ ở một mức tổ tiên, có $O(\log N)$ mức như vậy. Truy vấn độ sâu và cập nhật bộ đếm đều mất $O(1)$, nên tổng thời gian $O(N\log N)$ và bộ nhớ $O(N)$. Lời giải mẫu mô phỏng các pha bằng ngăn xếp để tránh đệ quy sâu. Dùng `long long` cho đáp án vì tại gốc cây sao có thể có $\binom{N-1}{2}$ cặp.
