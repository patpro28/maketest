## Chỉ cần xét hai đầu của dãy đã sắp xếp

Xét một truy vấn có $k\ge 2$ số đo. Gọi $b_1\le b_2\le\cdots\le b_k$ là các giá trị sau khi sắp xếp. Mỗi lần xuất hiện chiếm một vị trí riêng trong thứ tự này.

- Bỏ lần xuất hiện ở đầu cho biên độ $b_k-b_2$.
- Bỏ lần xuất hiện ở cuối cho biên độ $b_{k-1}-b_1$.
- Bỏ ở giữa giữ lại cả $b_1$ và $b_k$, nên biên độ vẫn là $b_k-b_1$.

Hai lựa chọn đầu đã bao quát phương án tối ưu. Vì vậy, chỉ cần biết hai giá trị nhỏ nhất và hai giá trị lớn nhất theo số lần xuất hiện.

## Cây đoạn có cập nhật lười

Mỗi nút lưu tối đa hai giá trị nhỏ nhất theo thứ tự tăng dần và tối đa hai giá trị lớn nhất theo thứ tự giảm dần. Lá có một giá trị trong mỗi danh sách. Để ghép hai nút, lấy hai phần tử nhỏ nhất từ hai danh sách nhỏ nhất và hai phần tử lớn nhất từ hai danh sách lớn nhất. Giữ cả hai phần tử khi chúng bằng nhau.

Các giá trị bị loại khỏi danh sách nhỏ nhất của nút con đã có ít nhất hai lần xuất hiện trong nút con đó đứng trước hoặc bằng chúng. Do đó, chúng không cần thiết để tìm hai giá trị nhỏ nhất của nút cha. Lập luận tương tự áp dụng cho danh sách lớn nhất. Phép ghép vì vậy cho đúng thông tin cực trị của hợp hai đoạn.

Cộng cùng $x$ lên toàn bộ một nút dịch các cực trị của nút thêm $x$ và giữ nguyên thứ tự giữa các phần tử. Cộng $x$ vào nhãn lười, rồi truyền nhãn xuống các nút con trước khi đi vào một phần của đoạn. Khi hỏi $[L,R]$, ghép các nút nằm trong đoạn và áp dụng công thức ở trên. Nếu $L=R$, trả lời $0$ ngay.

## Độ phức tạp

Dựng cây trong $O(N)$. Mỗi cập nhật và truy vấn tốn $O(\log(N+1))$ thời gian. Bộ nhớ là $O(N)$. Dùng số nguyên 64 bit vì mỗi giá trị có thể tích lũy nhiều lần cộng.
