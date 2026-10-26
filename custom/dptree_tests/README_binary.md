# DP trên cây với hai trạng thái — DPTREE23–DPTREE26

| Mã | Bài | Hai trạng thái tại đỉnh $u$ |
| --- | --- | --- |
| [dptree23](../dptree23/task.md) | Bảo vệ các con đường | Không đặt / có đặt chốt tại $u$ |
| [dptree24](../dptree24/task.md) | Sơn các ngôi làng | Sơn $u$ màu $0$ / màu $1$ |
| [dptree25](../dptree25/task.md) | Chọn người đại diện | Không chọn / có chọn $u$ |
| [dptree26](../dptree26/task.md) | Đếm cách ghép đôi | $u$ ghép với không / đúng một người con |

Bài `dptree22` vẫn là Phủ sóng các ngôi làng thuộc bộ trước. Bốn bài mới dùng đúng các mã từ `dptree23` đến `dptree26`.

Mỗi bài có `task.md`, hai ví dụ, `solution.md` với công thức và chứng minh, lời giải C++, verifier, checker, bộ sinh và `hash.json`. Theo quy tắc hiện tại, các đề không có mục Subtask. Mỗi lời giải dùng $O(N)$ thời gian, $O(N)$ bộ nhớ, số nguyên 64 bit và duyệt cây không đệ quy.

### Chạy kiểm thử

Từ thư mục gốc dự án, chạy cả bốn bài:

```sh
python3 custom/dptree_tests/check_binary.py
```

Kiểm tra riêng một bài:

```sh
python3 custom/dptree24/tests/check.py
```

Chỉ ghi lại hash khi chủ động cập nhật dữ liệu:

```sh
python3 custom/dptree_tests/check_binary.py --update-hashes
```

Quy trình gọi riêng các bước sinh test và kiểm tra, không xuất HTML. Không cần cài thêm thư viện. Các hàm tiện ích biên dịch, chạy chương trình, dựng cây từ mã Prüfer và thử checker được dùng lại từ `check.py`; dữ liệu và chương trình của các bài cũ không bị thay đổi.

### Bộ dữ liệu

Mỗi bài có 38 cặp đầu vào/đầu ra: 2 ví dụ, 12 test biên, 8 test nhỏ, 8 test ngẫu nhiên và 8 test đạt $N=200000$. Tổng cộng 152 cặp.

Có cây dây, cây sao, cây nhị phân, cây chổi, cây nhiều nhánh dài và cây ngẫu nhiên. Hoán đổi nhãn đỉnh, thứ tự cạnh và hướng ghi cạnh; bài đại diện có cả gốc ở đầu và giữa dây, tâm và lá của cây sao.

- Bảo vệ đường: không có cạnh, chốt tại tâm quá đắt, chọn các lá, chi phí đồng nhất và tổng vượt 32 bit.
- Sơn làng: phí sơn bằng $0$, phụ phí bằng $0$, chọn hai màu khác nhau dù chịu phụ phí, chọn cùng màu dù từng làng thích màu khác, tổng tới $2\cdot10^{14}$.
- Đại diện: tập rỗng, một người, tổ tiên cách nhiều cấp, nhiều nhánh độc lập và lấy dư khi số cách lớn.
- Ghép đôi: tập rỗng, cạnh chung đầu mút, hai cạnh rời nhau, đỉnh bậc lớn và đếm mọi cách thay vì chỉ cặp ghép lớn nhất.

### Đối chiếu độc lập

`oracle_binary.cpp` chỉ phục vụ cây nhỏ và không dùng công thức DP:

- Bài 23 liệt kê tập đỉnh đặt chốt, kiểm tra từng cạnh có đầu mút được chọn.
- Bài 24 liệt kê mọi cách sơn, tính trực tiếp tổng phí sơn và phụ phí.
- Bài 25 liệt kê tập người được chọn, kiểm tra với tập tổ tiên của từng người.
- Bài 26 liệt kê tập cạnh, kiểm tra xem có đầu mút nào xuất hiện hai lần.

Cả 22 test ví dụ/biên/nhỏ của mỗi bài được đối chiếu bằng oracle này. Thêm 2.736 trường hợp được kiểm tra: mọi cây gán nhãn có tối đa 5 đỉnh, mọi bộ trọng số trên bảng nhỏ với tối đa 3 đỉnh cho hai bài có chi phí, và 240 cây ngẫu nhiên mỗi bài. Bài 25 có thêm ba cây được dựng để số cách trước khi lấy dư lần lượt bằng $10^9+6$, $10^9+7$, $10^9+8$. Số trường hợp bổ sung của các bài lần lượt là 625, 1.336, 389 và 386.

Các test lớn có đáp án độc lập được đối chiếu bằng công thức cây dây/cây sao, ghép cặp tham lam khi chốt có giá đồng nhất, tổng chi phí sơn nhỏ nhất khi phụ phí bằng $0$, chi phí bằng nhau ở hai màu và trường hợp đổi màu tốn nhiều hơn tổng phụ phí.

Quy trình còn kiểm tra verifier từ chối cạnh khuyên, cạnh trùng, chu trình, đỉnh ngoài giới hạn, chi phí sai, thiếu/thừa dữ liệu; thử checker với 27 trường hợp đầu ra đúng/sai mỗi bài; kiểm tra cấu trúc đề, ví dụ, tính tái lập của toàn bộ bộ sinh, mã băm SHA-256 và tính toàn vẹn của ZIP.

### Sản phẩm sinh tự động

Đầu vào nằm trong `in/`, đầu ra nằm trong `out/`. Tệp ZIP cùng mã bài chứa 76 tệp `.in`/`.out` ở cấp ngoài cùng, để tiện tải lên hệ thống chấm. `params.h`, chương trình đã biên dịch, dữ liệu và ZIP được bỏ qua bởi Git theo cấu hình của dự án; mã nguồn và `hash.json` đủ để tái tạo.
