# Năm bài DP trên cây với ba trạng thái — DPTREE27–DPTREE31

| Mã | Bài | Ý nghĩa ba trạng thái |
| --- | --- | --- |
| [dptree27](../dptree27/task.md) | Không chọn ba người liên tiếp | Số tổ tiên liên tiếp đã chọn trước $u$: $0,1,2$ |
| [dptree28](../dptree28/task.md) | Điều chỉnh cây biểu thức | Giá trị tại $u$ lấy dư cho $3$ |
| [dptree29](../dptree29/task.md) | Tách hai nhóm đối địch | Thành phần chứa $u$: không màu, đỏ hoặc xanh |
| [dptree30](../dptree30/task.md) | Giữ lại các tuyến đường | Số cạnh được giữ nối $u$ với các con: $0,1,2$ |
| [dptree31](../dptree31/task.md) | Nhóm liên thông chia hết cho ba | Kích thước tập liên thông chứa $u$ lấy dư cho $3$ |

Mỗi bài có đề tiếng Việt, hai ví dụ, lời giải và chứng minh, code C++, verifier, checker, bộ sinh và `hash.json`. Không thêm mục Subtask. Lời giải dùng $O(N)$ thời gian, $O(N)$ bộ nhớ, số nguyên 64 bit và duyệt cây bằng vòng lặp.

Các bài 27, 29, 30, 31 có $N\le200000$. Bài 28 có $N\le199999$ và $N$ lẻ, vì mỗi đỉnh trong có đúng hai người con; test lớn bao gồm cây sâu gần $100000$.

### Cấu hình upload

Mục `[upload]` dùng các thiết lập của `dptree22`:

- `time_limit = 1.0`, cũng là giới hạn trong kiểm thử cục bộ.
- `group = '04'`, `classes = 'D'`, `types = ['dp_tree']`.
- Cùng danh sách tám ngôn ngữ và `partial = true`.
- Không sao chép `approved`: trường này không được `problem_upload.py` chấp nhận và API không tự duyệt đề.

Kiểm thử gọi bộ đóng gói upload thật với một client kiểm tra cục bộ. Nó đối chiếu tên, metadata, editorial, manifest 38 test và mã băm của 76 tệp trong ZIP. Không gửi yêu cầu đến máy chủ.

### Chạy kiểm thử

Từ thư mục gốc:

```sh
python3 custom/dptree_tests/check_ternary.py
```

Chạy riêng một bài:

```sh
python3 custom/dptree28/tests/check.py
```

Chỉ cập nhật hash khi chủ động thay đổi dữ liệu:

```sh
python3 custom/dptree_tests/check_ternary.py --update-hashes
```

Quy trình gọi riêng các bước sinh dữ liệu, xác thực, chấm và đóng gói; không xuất HTML và không cần thư viện xuất HTML. Các hàm tiện ích được dùng lại từ bộ kiểm thử trước; bài cũ không bị thay đổi.

### Dữ liệu chính thức

Mỗi bài có 38 cặp: 2 ví dụ, 12 test biên, 8 test nhỏ, 8 test ngẫu nhiên và 8 test đạt giới hạn số đỉnh. Tổng cộng 190 cặp.

Cây tổng quát bao gồm cây dây, sao, nhị phân, chổi, nhiều nhánh dài và ngẫu nhiên. Nhãn đỉnh, thứ tự cạnh và hướng ghi cạnh được hoán đổi. Bài 28 có cây nhị phân đầy đủ dạng cân bằng, lệch sâu và ngẫu nhiên; nhãn con có thể nhỏ hơn nhãn cha.

Các trường hợp chuyên biệt gồm:

- Bài 27: chuỗi ba đỉnh, chọn các đỉnh ở hai nhánh khác nhau, gốc ở tâm/lá cây sao, giá trị âm, không và cực đại.
- Bài 28: một lá, cả hai phép toán, mọi số dư đích, lá có lựa chọn rẻ bằng $0$, chi phí lớn và cây biểu thức sâu.
- Bài 29: không có màu, chỉ một màu, đỏ/xanh xen kẽ, đỉnh trung gian không màu, cạnh miễn phí và nhiều thành phần cùng màu.
- Bài 30: không có cạnh, giá trị âm/không, cây sao chỉ được giữ tối đa hai cạnh, ràng buộc bậc tại cả hai đầu và tổng vượt 32 bit.
- Bài 31: ít hơn ba đỉnh, tập rỗng bị loại, ba đỉnh không liên thông, nhiều kích thước chia hết cho ba và số cách cần lấy modulo.

### Đối chiếu độc lập

`oracle_ternary.cpp` không dùng các công thức DP của lời giải:

- Bài 27 liệt kê mọi tập đỉnh và kiểm tra trực tiếp từng bộ đỉnh–cha–ông.
- Bài 28 liệt kê mọi cách gán ba giá trị cho các lá rồi tính trực tiếp toàn bộ biểu thức.
- Bài 29 liệt kê mọi tập cạnh bị cắt, dựng lại các thành phần liên thông và kiểm tra màu.
- Bài 30 liệt kê mọi tập cạnh giữ lại, kiểm tra bậc và cộng giá trị.
- Bài 31 liệt kê mọi tập đỉnh, kiểm tra kích thước và tính liên thông bằng số cạnh trong rừng cảm sinh.

Cả 22 test ví dụ/biên/nhỏ của mỗi bài được đối chiếu bằng oracle. Thêm 4.881 trường hợp:

| Bài | Số trường hợp bổ sung |
| --- | --- |
| DPTREE27 | 625 |
| DPTREE28 | 954 |
| DPTREE29 | 1.921 |
| DPTREE30 | 995 |
| DPTREE31 | 386 |

Các trường hợp gồm mọi cây gán nhãn có tối đa 5 đỉnh đối với cây tổng quát, liệt kê các bộ trọng số/màu trên bảng nhỏ và 240 cây ngẫu nhiên mỗi bài. Bài biểu thức duyệt mọi hình dạng cây với tối đa 3 đỉnh trong, mọi phép toán trên chúng, cả ba đích và hai mẫu chi phí; thêm mọi bảng chi phí nhị phân ở cây một lá/hai lá và cây biểu thức ngẫu nhiên.

Các test lớn có dạng đặc biệt được đối chiếu bằng công thức độc lập: cây dây/sao, các giá trị đồng dấu, tổng chi phí lá khi mọi lựa chọn cùng giá, gộp tuyến tính các lá khi mọi phép toán giống nhau, tổng cạnh buộc cắt khi mọi đỉnh được đánh dấu và tổng các khoảng liên tiếp có độ dài chia hết cho ba.

Quy trình còn kiểm tra verifier từ chối cạnh khuyên, cạnh trùng, chu trình, chỉ số sai, giá trị vượt giới hạn, thiếu/thừa dữ liệu. Riêng bài 28 thử sai số dư, sai loại đỉnh, cây có số đỉnh chẵn, trùng con, nhiều cha, gốc có cha và chu trình không nối tới gốc. Checker được thử với 27 đầu ra đúng/sai mỗi bài. Cấu trúc đề, ví dụ, tính tái lập, SHA-256, ZIP và cấu hình upload đều được kiểm tra.

Dữ liệu nằm trong `in/`, `out/`; mỗi bài có ZIP cùng mã, chứa 76 tệp đầu vào/đầu ra ở cấp ngoài cùng. Dữ liệu sinh tự động, chương trình đã biên dịch, `params.h` và ZIP được Git bỏ qua theo cấu hình hiện có.
