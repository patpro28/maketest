# Hướng dẫn giải

Xét lần lượt từng dòng làm cạnh dưới của hình chữ nhật. Với mỗi cột $j$, gọi $h_j$ là số ô $1$ liên tiếp đi lên từ dòng hiện tại. Nếu ô hiện tại là $0$, đặt $h_j=0$; nếu là $1$, tăng $h_j$ thêm một.

Với đoạn cột $[l,r]$, số hình chữ nhật có cạnh dưới ở dòng hiện tại và chiếm đúng đoạn cột đó là $\min(h_l,\ldots,h_r)$: chiều cao có thể là bất kỳ số nguyên từ $1$ đến giá trị nhỏ nhất này. Vì vậy cần tính tổng giá trị nhỏ nhất trên mọi đoạn con của mảng $h$.

Duyệt đầu phải $r$ từ trái sang phải. Dùng ngăn xếp lưu các cặp `(height, count)`, trong đó `count` là số đầu trái có cùng giá trị nhỏ nhất `height`. Các độ cao trong ngăn xếp tăng nghiêm ngặt.

Khi thêm độ cao $h_r$, lấy khỏi ngăn xếp các nhóm có độ cao lớn hơn hoặc bằng $h_r$. Tất cả các đoạn thuộc những nhóm này có giá trị nhỏ nhất mới là $h_r$, nên gộp chúng cùng đoạn chỉ chứa cột $r$. Duy trì tổng `height * count` của các nhóm. Tổng này chính là số hình chữ nhật kết thúc ở cột $r$ và dòng hiện tại; cộng nó vào đáp án.

Mỗi đoạn cột được tính đúng giá trị nhỏ nhất của nó, và mỗi hình chữ nhật có duy nhất một dòng dưới cùng cùng một đoạn cột. Do đó thuật toán đếm đủ và không trùng.

Mỗi phần tử được đưa vào và lấy khỏi ngăn xếp tối đa một lần trên mỗi dòng. Độ phức tạp là $O(MN)$ thời gian và $O(N)$ bộ nhớ.

Dùng số nguyên 64 bit: khi bảng $1000\times1000$ toàn số $1$, đáp án là

$$\frac{M(M+1)}2\cdot\frac{N(N+1)}2=250500250000.$$

Lời giải đối chiếu tính đóng góp của mỗi vị trí nhỏ nhất bằng hai biên: phần tử nhỏ hơn gần nhất bên trái và phần tử nhỏ hơn hoặc bằng gần nhất bên phải. Hai quy tắc khác nhau cho trường hợp bằng nhau giúp mỗi đoạn chỉ được đếm một lần.

Ví dụ trong đề có 1039 hình chữ nhật toàn số 1. Giá trị 49 là diện tích lớn nhất, không phải số lượng hình chữ nhật.
