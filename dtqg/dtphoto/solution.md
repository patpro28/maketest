## Subtask 1 — Duyệt ảnh rời hàng của từng người

**Giới hạn:** $n\le8$, chiếm 30% số điểm.

Ở phần này, chỉ dùng trực tiếp mô tả của đề, chưa cần nhận xét về ba trong năm bức ảnh. Ta không duyệt hoán vị chuẩn mà quay lui chọn ảnh rời hàng của từng người, rồi khôi phục thứ tự chuẩn từ các ràng buộc trước/sau.

### Vì sao chỉ cần năm lựa chọn cho mỗi người?

Đặt $moved[x]\in\{1,2,3,4,5\}$ là ảnh mà người $x$ được phép rời hàng. Có đúng $5^n$ cách gán cho toàn bộ vận động viên.

Đề chỉ yêu cầu mỗi người rời hàng **nhiều nhất một lần**. Tuy nhiên, không cần thêm lựa chọn thứ sáu cho người không rời hàng: có thể coi người đó rời hàng trong một ảnh bất kỳ rồi chèn lại chỗ cũ. Chính xác hơn, khi xóa nhóm được gán rời hàng khỏi cả ảnh và thứ tự chuẩn, xóa thêm một người vốn đứng yên vẫn giữ hai dãy còn lại giống nhau. Vì vậy gán mọi người vào đúng một nhóm không làm mất phương án hợp lệ.

Không đánh dấu theo chỉ số vị trí: từ $(1,2,3)$ thành $(3,1,2)$ chỉ cần người $3$ rời hàng; người $1,2$ bị dịch chỉ số dù không rời hàng.

### Khôi phục thứ tự bằng sắp xếp tô pô

Với một cách gán $moved$ đã cố định, dựng đồ thị có $n$ đỉnh tương ứng với các vận động viên:

1. Trong ảnh $k$, xóa mọi người $x$ có $moved[x]=k$.
2. Gọi dãy còn lại là $(v_1,v_2,\ldots,v_t)$. Những người này không rời hàng ở ảnh $k$, nên thứ tự chuẩn phải giữ nguyên thứ tự của dãy. Thêm cạnh $v_i\to v_{i+1}$ với mọi $1\le i<t$.
3. Gộp các cạnh của cả năm ảnh rồi sắp xếp tô pô bằng thuật toán Kahn.

Chỉ cần nối các phần tử liên tiếp: đường đi từ $v_i$ đến $v_j$ đã buộc $v_i$ đứng trước $v_j$ với mọi $i<j$.

Nếu lấy được đủ $n$ đỉnh, thứ tự tô pô là đáp án và có thể dừng. Nếu đồ thị có chu trình, cách gán hiện tại không phù hợp; thử cách gán tiếp theo. Đề bảo đảm tồn tại thứ tự chuẩn nên sẽ có một cách gán thành công.

Khi cài đặt, có thể giữ các cạnh trùng nhau giữa nhiều ảnh, nhưng phải tăng và giảm bậc vào tương ứng với từng cạnh.

### Chứng minh tính đúng đắn

**Mọi kết quả tìm được đều hợp lệ.** Gọi $P$ là một thứ tự tô pô tìm được. Trong ảnh $k$, các cạnh buộc dãy những người không thuộc nhóm $k$ xuất hiện trong $P$ đúng thứ tự của ảnh. Vì vậy xóa nhóm $k$ khỏi cả $P$ và ảnh $k$ cho hai dãy giống nhau. Từ $P$, cho nhóm $k$ rời hàng rồi chèn lại theo ảnh sẽ tạo đúng bức ảnh đó. Các nhóm không giao nhau, nên mỗi người được phép rời hàng nhiều nhất một lần.

**Không bỏ sót đáp án.** Xét thứ tự chuẩn thực sự và các nhóm rời hàng hợp lệ. Gán những người không rời hàng vào một nhóm tùy ý như lập luận trên, ta được một cách gán nằm trong $5^n$ trường hợp đã duyệt. Mọi cạnh sinh ra ở cách gán này đều đi từ người đứng trước đến người đứng sau trong thứ tự chuẩn. Đồ thị không có chu trình, nên sắp xếp tô pô sẽ thành công.

Hai lập luận trên bảo đảm thuật toán tìm được một thứ tự chuẩn hợp lệ mà không cần dùng phép so sánh đa số.

### Độ phức tạp

Mỗi cách gán duyệt năm ảnh trong $O(5n)$, tạo không quá $5(n-1)$ cạnh và sắp xếp tô pô trong $O(5n)$. Tổng thời gian là $O(5^n\cdot5n)$, bộ nhớ $O(5n)$, kể cả đồ thị, các ảnh và ngăn xếp quay lui. Với $n=8$, có $5^8=390\,625$ cách gán.

## Subtask 2 — Dùng phép so sánh theo đa số để sắp xếp

**Giới hạn:** toàn bộ đề bài, chiếm 70% số điểm.

Khi $n$ lớn, không thể duyệt $5^n$ cách gán người rời hàng. Ta cần suy ra trực tiếp quan hệ trước/sau của từng cặp.

### Khôi phục thứ tự của một cặp

Gọi $pos_k[x]$ là vị trí của vận động viên $x$ trong bức ảnh thứ $k$.

Xét hai vận động viên khác nhau $x,y$. Mỗi người rời hàng trong nhiều nhất một lần chụp, nên có nhiều nhất hai bức ảnh mà ít nhất một trong hai người rời hàng. Trong ít nhất ba bức còn lại, cả hai đều không rời hàng, nên thứ tự tương đối của họ giống thứ tự chuẩn.

Nếu $x$ đứng trước $y$ trong thứ tự chuẩn thì

$$\#\{k:pos_k[x]<pos_k[y]\}\ge3.$$

Ngược lại, nếu $y$ đứng trước $x$ thì nhiều nhất hai bức ảnh có $x$ đứng trước $y$. Vì vậy:

$$\boxed{x\text{ đứng trước }y\text{ trong thứ tự chuẩn}\iff
\#\{k:pos_k[x]<pos_k[y]\}\ge3.}$$

Hai người có thể cùng rời hàng trong một lần, hoặc việc chèn lại không làm đổi thứ tự của họ; khi đó số ảnh sai còn ít hơn. Ta chỉ cần chặn trên bằng hai.

### Sắp xếp theo quan hệ đã khôi phục

Đọc năm hoán vị và dựng các mảng vị trí. Khởi tạo dãy $1,2,\ldots,n$, rồi sắp xếp bằng hàm so sánh:

```cpp
bool before(int x, int y) {
    int votes = 0;
    for (int k = 0; k < 5; ++k)
        votes += pos[x][k] < pos[y][k];
    return votes >= 3;
}
```

Sau khi sắp xếp, in dãy số hiệu thu được.

Không sắp xếp theo số hiệu, vị trí trung bình hoặc trung vị của năm vị trí. Những vận động viên khác chèn vào hàng có thể làm vị trí tuyệt đối của một người dịch đi trong nhiều ảnh, kể cả khi người đó không rời hàng. Lập luận đa số chỉ khôi phục chắc chắn **thứ tự tương đối của từng cặp**.

## Vì sao hàm so sánh hợp lệ?

Phép so sánh đa số giữa các thứ tự tùy ý không nhất thiết bắc cầu: có thể xuất hiện chu trình. Không được mặc nhiên dùng nó để sắp xếp mọi bộ năm hoán vị.

Trong bài này, điều kiện mỗi vận động viên rời hàng nhiều nhất một lần đã chứng minh rằng phép so sánh đa số trùng chính xác với thứ tự chuẩn của mọi cặp. Do đó nó có các tính chất cần thiết:

- Không có $x$ đứng trước chính $x$.
- Với $x\ne y$, đúng một trong hai quan hệ $x$ trước $y$ hoặc $y$ trước $x$ xảy ra.
- Nếu $x$ trước $y$ và $y$ trước $z$, thì $x$ trước $z$, vì cả ba quan hệ đều là quan hệ trong cùng thứ tự chuẩn.

Vì thế có thể dùng `std::sort` với hàm so sánh trên. Sử dụng ngưỡng $3$, không dùng ngưỡng $2$; cũng không chỉ xét ba bức ảnh đầu vì cả hai ảnh sai của một cặp có thể cùng nằm trong ba bức đó.

## Chứng minh đúng và tính duy nhất

Với mọi cặp vận động viên, hàm so sánh trả đúng quan hệ trước/sau trong thứ tự chuẩn. Thuật toán sắp xếp đưa mọi cặp về đúng quan hệ đó, nên dãy kết quả chính là thứ tự chuẩn.

Nếu có hai thứ tự chuẩn khác nhau cùng phù hợp với dữ liệu, phải tồn tại một cặp có quan hệ trước/sau khác nhau giữa hai thứ tự. Nhưng quan hệ của cặp đó đã được xác định duy nhất bởi ít nhất ba trong năm bức ảnh. Mâu thuẫn. Vì vậy thứ tự cần tìm là duy nhất.

## Độ phức tạp và lưu ý cài đặt

Đọc và lập bảng vị trí mất $O(5n)$. Mỗi phép so sánh xét năm vị trí, mất $O(5)$. Dùng `std::sort` có $O(n\log n)$ phép so sánh, nên tổng thời gian $O(5n\log n)$, bộ nhớ $O(5n)$.

Nếu tự viết Quick Sort, cần chú ý cách chọn chốt và độ phức tạp trường hợp xấu. Lời giải mẫu dùng `std::sort` để có bảo đảm số phép so sánh $O(n\log n)$.

Chỉ cần kiểu `int` cho vị trí và số hiệu. Với $n=1$, kết quả là số hiệu duy nhất. Lời giải mẫu đọc `PHOTO.INP` và ghi `PHOTO.OUT` nếu tệp đầu vào có trong thư mục chạy; nếu không, dùng nhập/xuất chuẩn để tương thích hệ thống chấm.
