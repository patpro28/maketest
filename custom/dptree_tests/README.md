# Bốn bài DP trên cây cơ bản

| Mã | Bài | Kỹ thuật |
| --- | --- | --- |
| [dptree17](../dptree17/task.md) | Đếm tập độc lập | Hai trạng thái, cộng và nhân số cách |
| [dptree18](../dptree18/task.md) | Khu vườn có lợi nhuận lớn nhất | Tập đỉnh liên thông có tổng lớn nhất |
| [dptree19](../dptree19/task.md) | Ngăn dòng nước | Chọn cắt cạnh hoặc xử lý nhánh con |
| [dptree22](../dptree22/task.md) | Phủ sóng các ngôi làng | Ba trạng thái, ép ít nhất một con có trạm |

Mỗi bài có đề tiếng Việt trong `task.md`, hai ví dụ, một subtask 100%, lời giải và chứng minh trong `solution.md`, chương trình chuẩn, checker, verifier, bộ sinh và `hash.json`. Các chương trình chuẩn duyệt cây bằng vòng lặp, không dùng đệ quy; thời gian và bộ nhớ đều $O(N)$ với $N\le200000$.

Bộ sinh và chương trình chấm của từng bài chỉ phụ thuộc các tệp trong chính bài đó cùng thư viện có sẵn ở `common/`. Thư mục dùng chung này chỉ phục vụ kiểm thử.

Chạy cả bốn bài từ thư mục gốc:

```sh
python3 custom/dptree_tests/check.py
```

Hoặc kiểm tra riêng một bài:

```sh
python3 custom/dptree19/tests/check.py
```

Khi chủ động thay đổi dữ liệu và cần ghi lại hash:

```sh
python3 custom/dptree_tests/check.py --update-hashes
```

Quy trình gọi riêng các bước sinh và kiểm tra, không gọi chế độ xuất HTML và không cần thư viện xuất HTML. Lần chạy thông thường đối chiếu hash đã lưu; chỉ tùy chọn `--update-hashes` mới ghi lại hash.

Mỗi bài có 38 cặp dữ liệu: 2 ví dụ, 12 test biên, 8 test nhỏ, 8 test ngẫu nhiên và 8 test đạt $N=200000$. Tổng cộng 152 cặp. Có cây dây, cây sao, cây nhị phân, cây chổi, cây có nhiều nhánh dài và cây ngẫu nhiên; nhãn đỉnh, hướng ghi cạnh và thứ tự cạnh được hoán đổi. Test bao phủ gốc ở đầu dây, giữa dây, tâm sao và lá sao.

Các trường hợp chuyên biệt gồm tập rỗng trong bài đếm; mọi giá trị âm, bằng 0, dương hoặc các vùng dương bị ngăn bởi đỉnh âm trong bài khu vườn; gốc có bậc một và chi phí cắt nhánh so với cắt các cạnh phía dưới trong bài dòng nước; lá không thể được con phủ, một đỉnh duy nhất và chọn nhiều trạm rẻ thay cho một trạm đắt trong bài phủ sóng. Có các đáp án vượt giới hạn số nguyên 32 bit.

Ngoài xác thực đầu vào và chạy chương trình chuẩn qua checker trong giới hạn thời gian, bộ kiểm thử còn:

- Đối chiếu cả 22 test nhỏ/biên/ví dụ của mỗi bài với `oracle.cpp`. Oracle liệt kê trực tiếp mọi tập đỉnh hoặc mọi tập cạnh bị cắt, không sử dụng công thức DP của lời giải.
- Kiểm tra thêm 2.196 trường hợp: mọi cây gán nhãn có tối đa 5 đỉnh, mọi bộ giá trị trên bảng nhỏ với tối đa 3 đỉnh cho các bài có trọng số, và 240 cây ngẫu nhiên mỗi bài. Số trường hợp lần lượt là 386, 625, 560 và 625.
- Đối chiếu các trường hợp đặc biệt bằng công thức độc lập: Fibonacci trên cây dây và công thức cây sao cho bài đếm, tổng/giá trị lớn nhất khi lợi nhuận đồng dấu, chi phí cắt đồng nhất, và thuật toán tham lam phủ cây khi mọi trạm có cùng chi phí.
- Kiểm tra verifier từ chối cạnh khuyên, cạnh trùng, chu trình kèm đỉnh cô lập, chỉ số sai, trọng số vượt giới hạn, thiếu hoặc thừa dữ liệu.
- Thử checker với đáp án đúng, khoảng trắng khác nhau, số sai, đầu ra rỗng, thừa dữ liệu, ký tự sai, số thập phân và số nguyên vượt miền 64 bit.
- Đối chiếu cấu trúc đề với mẫu knapsack, bảng subtask, nội dung ví dụ, tính tái lập của tất cả bộ sinh và SHA-256 của mọi đầu vào/đầu ra.

Dữ liệu được sinh vào `in/`, `out/`; mỗi bài có tệp ZIP cùng mã bài, chứa các cặp `.in`/`.out` ở cấp ngoài cùng để tiện tải lên hệ thống chấm. ZIP, chương trình đã biên dịch, `params.h` và dữ liệu sinh tự động không được Git theo dõi theo cấu hình hiện có.
