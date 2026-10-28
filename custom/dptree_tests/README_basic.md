# DP trên cây nhập môn, một trạng thái — DPTREE32–DPTREE36

| Mã | Bài | Kiến thức trọng tâm |
| --- | --- | --- |
| [dptree32](../dptree32/task.md) | Kho tài nguyên của một nhánh | Cộng kết quả của tất cả các con |
| [dptree33](../dptree33/task.md) | Nhánh cây dài nhất | Chọn một nhánh bằng phép lấy lớn nhất |
| [dptree34](../dptree34/task.md) | Hành trình thu thập phần thưởng | Cộng giá trị hiện tại với nhánh tốt nhất |
| [dptree35](../dptree35/task.md) | Hoàn thành nhiệm vụ | Cộng các việc phải làm, lấy min giữa hai phương án |
| [dptree36](../dptree36/task.md) | Trang trí một nhánh liên thông | Nhân số cách giữa các nhánh độc lập |

Mọi bài đều cố định gốc $1$, không có truy vấn thay đổi dữ liệu, đổi gốc hoặc ba lô. Mỗi lời giải dùng một giá trị `dp[u]`. Hai bài đầu in kết quả của mọi đỉnh; ba bài cuối in một kết quả tại gốc.

Lời giải được trình bày theo ba câu hỏi: `dp[u]` nghĩa là gì, một lá trả về gì, và cha dùng kết quả của các con thế nào. `solution.md` chỉ chứa thuật toán, minh họa, chứng minh và độ phức tạp; tài liệu kiểm thử nằm riêng ở đây.

### Tệp và giới hạn

Mỗi bài có đề tiếng Việt, hai ví dụ, lời giải, code C++, verifier, checker, bộ sinh, `hash.json` và cấu hình upload. Không thêm mục Subtask. Lời giải dùng $O(N)$ thời gian, $O(N)$ bộ nhớ với $N\le200000$, duyệt không đệ quy và dùng số nguyên 64 bit khi cần.

Cấu hình upload tiếp tục dùng các trường API hỗ trợ của `dptree22` như bộ trước: nhóm `04`, lớp `D`, nhãn `dp_tree`, giới hạn 1 giây, cùng danh sách ngôn ngữ và `partial = true`. Không sao chép cờ `approved`. Việc đóng gói upload được kiểm tra cục bộ, không gửi yêu cầu đến máy chủ.

Phần đọc/ghi có bộ đệm được tách riêng trong `sol/fast_io.h` để code DP trong `sol/correct.cpp` vẫn tập trung vào công thức và thứ tự tính.

### Cách chạy

Chạy cả năm bài từ thư mục gốc:

```sh
python3 custom/dptree_tests/check_basic.py
```

Kiểm tra riêng một bài:

```sh
python3 custom/dptree35/tests/check.py
```

Chỉ ghi lại hash khi chủ động cập nhật dữ liệu:

```sh
python3 custom/dptree_tests/check_basic.py --update-hashes
```

Quy trình gọi riêng các bước sinh, xác thực và chấm dữ liệu, không xuất HTML và không cần thư viện xuất HTML. Các hàm tiện ích dùng lại từ bộ kiểm thử trước; các bài cũ không bị thay đổi.

### Bộ dữ liệu

Mỗi bài có 38 cặp: 2 ví dụ, 12 test biên, 8 test nhỏ, 8 test ngẫu nhiên và 8 test đạt $N=200000$. Tổng cộng 190 cặp.

Các dạng cây gồm dây, sao, nhị phân, chổi, nhiều nhánh dài và ngẫu nhiên. Hoán đổi nhãn đỉnh, thứ tự cạnh và hướng ghi cạnh. Có gốc ở đầu/giữa dây và tâm/lá cây sao để kiểm tra việc xác định cha, con và lá.

- Bài 32: một đỉnh, mọi giá trị bằng $0$, tài nguyên tại gốc, nhánh sâu và tổng tới $2\cdot10^{14}$.
- Bài 33: lá có kết quả $0$, tính số cạnh thay vì số đỉnh, phân biệt chiều cao cây con với độ sâu và không cộng các nhánh.
- Bài 34: giá trị âm, hành trình bắt buộc tới lá, không bỏ gốc, chỉ chọn một nhánh và tổng âm vượt miền 32 bit.
- Bài 35: lá bắt buộc trả chi phí, chọn làm trọn gói hoặc giao tất cả các con, chi phí bằng $0$ và tổng trung gian vượt 32 bit.
- Bài 36: bắt buộc chứa gốc, không đếm tập rỗng, nhánh độc lập, cây dây/sao và số cách có thể bằng $0$ sau modulo.

### Đối chiếu độc lập

`oracle_basic.cpp` có các cách tính trực tiếp cho dữ liệu nhỏ:

- Bài 32 duyệt lại từng cây con và cộng trực tiếp mọi giá trị.
- Bài 33 duyệt lại từng cây con và tìm độ sâu lớn nhất so với gốc cây con.
- Bài 34 tính tổng từ gốc tới mọi đỉnh, chỉ so sánh các lá.
- Bài 35 liệt kê mọi tập nhiệm vụ được thuê, kiểm tra mỗi đường gốc–lá có ít nhất một nhiệm vụ được thuê. Chi phí không âm cho phép bỏ các khoản thuê thừa dưới một tổ tiên đã thuê, nên giá trị nhỏ nhất đúng với quy tắc đề.
- Bài 36 liệt kê tập đỉnh chứa gốc, kiểm tra mọi đỉnh được chọn khác gốc đều có cha được chọn.

Mọi test của bốn bài 32–35 còn được đối chiếu bằng thuật toán độc lập ở đầy đủ giới hạn:

- Bài 32 dùng thứ tự Euler, tổng tiền tố và hiệu tổng trên đoạn cây con.
- Bài 33 dùng thứ tự Euler và truy vấn cực đại độ sâu trên đoạn, trừ độ sâu gốc cây con.
- Bài 34 dùng tổng tiền tố trên đường từ gốc tới từng lá.
- Bài 35 biến mỗi nhiệm vụ thành một đoạn các lá theo thứ tự DFS. Thuê các nhiệm vụ ở những cây con rời nhau tương ứng với chia toàn bộ dãy lá thành các đoạn. Một cạnh từ đầu đến cuối đoạn có trọng số là chi phí thuê; đường đi ngắn nhất trên DAG các vị trí tiền tố lá cho chi phí nhỏ nhất. Cách này không dùng công thức min giữa cha và tổng các con.

Thuật toán Euler/DAG được đối chiếu lại với cách tính trực tiếp trên mọi trường hợp nhỏ. Bài 36 có công thức độc lập trên cây dây và sao, cùng ba cây được dựng có số tập chứa gốc chính xác bằng $10^9+6$, $10^9+7$, $10^9+8$ trước khi lấy dư.

Ngoài dữ liệu chính thức, có 2.650 trường hợp bổ sung:

| Bài | Số trường hợp |
| --- | --- |
| DPTREE32 | 625 |
| DPTREE33 | 386 |
| DPTREE34 | 625 |
| DPTREE35 | 625 |
| DPTREE36 | 389 |

Chúng bao gồm mọi cây gán nhãn có tối đa 5 đỉnh, mọi bộ giá trị trên bảng nhỏ với tối đa 3 đỉnh cho các bài có giá trị, 240 cây ngẫu nhiên mỗi bài và ba trường hợp modulo của bài 36.

Verifier được thử với cạnh khuyên, cạnh trùng, chu trình kèm đỉnh cô lập, chỉ số sai, giá trị vượt giới hạn, thiếu/thừa dữ liệu. Checker được thử với khoảng trắng khác nhau, sai giá trị đầu/cuối/giữa, đảo thứ tự kết quả, thiếu hoặc thừa token, số thập phân và số vượt miền 64 bit; đặc biệt kiểm tra đủ mọi kết quả trong hai bài in cả mảng.

Quy trình còn đối chiếu cấu trúc đề, ví dụ, nội dung lời giải, tính tái lập của tất cả bộ sinh, SHA-256, ZIP và gói dữ liệu upload. Đầu vào nằm trong `in/`, đầu ra trong `out/`; mỗi ZIP chứa 76 tệp phẳng. Các sản phẩm sinh tự động được Git bỏ qua theo cấu hình dự án.
