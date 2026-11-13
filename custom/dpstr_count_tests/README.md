# DPSTR3xx — Nhóm 4: Đếm cách tạo dãy con

Bộ bài đếm **cách chọn vị trí trong xâu nguồn** để tạo mẫu hoặc xâu đích. Hai bộ vị trí khác nhau được tính riêng dù cho cùng nội dung; không đếm số nội dung dãy con phân biệt. Những bài đầu dành cho học sinh THCS mới học DP đếm; các bài cuối bổ sung trạng thái hoặc tối ưu tổng đoạn.

## Phân mức và danh sách

| Dải mã | Mức độ |
| --- | --- |
| dpstr300–329 | Dễ / nhập môn |
| dpstr330–349 | Trung bình |
| dpstr350–399 | Khó |

| Mã | Tên bài | Nội dung | Giới hạn | Quy mô chính |
| --- | --- | --- | --- | --- |
| [dpstr300](../dpstr300/task.md) | Những cặp ab | Đếm mẫu `ab` | N ≤ 200000 | O(N) |
| [dpstr301](../dpstr301/task.md) | Thông điệp abc | Đếm mẫu `abc` | N ≤ 200000 | O(N) |
| [dpstr302](../dpstr302/task.md) | Mẫu có chữ lặp | Đếm mẫu `aba`, không dùng lại vị trí | N ≤ 200000 | O(N) |
| [dpstr303](../dpstr303/task.md) | Tạo xâu đích | Mẫu bất kỳ, chọn/bỏ vị trí | N, M ≤ 5000 | 25 triệu cặp chỉ số |
| [dpstr330](../dpstr330/task.md) | Dấu hỏi trong bản tin | Đếm cả cách thay mọi dấu `?` và bộ vị trí | N, M ≤ 5000 | 25 triệu cặp chỉ số |
| [dpstr331](../dpstr331/task.md) | Chọn đủ vị trí đánh dấu | Đúng K vị trí được chọn có đánh dấu | N, M ≤ 2500; K ≤ 5 | 37,5 triệu trạng thái |
| [dpstr332](../dpstr332/task.md) | Các ký tự cách nhau | Không chọn hai vị trí kề nhau | N, M ≤ 5000 | 25 triệu cặp chỉ số |
| [dpstr350](../dpstr350/task.md) | Đúng số nhóm được chọn | Đúng K nhóm vị trí liên tiếp tối đại | N, M ≤ 2000; K ≤ 5 | 48 triệu trạng thái, gồm hai trạng thái cuối |
| [dpstr351](../dpstr351/task.md) | Bản tin có sai lệch | Không quá K chữ khác xâu đích | N, M ≤ 2500; K ≤ 5 | 37,5 triệu trạng thái |
| [dpstr352](../dpstr352/task.md) | Khoảng cách giữa hai ký tự | Hiệu chỉ số liên tiếp thuộc [L, R] | N, M ≤ 5000 | 25 triệu cặp chỉ số |

Mọi bài có cận thiết kế không vượt $5\cdot10^7$ ô hoặc lượt duyệt chính, không phải số lệnh CPU. Không bắt buộc $M\le N$; khi không chọn đủ ký tự, đáp án bằng 0. Ba bài đầu in chính xác bằng số nguyên 64 bit; các bài còn lại lấy modulo $10^9+7$.

## Quy ước cần chú ý

- `dpstr330`: thay **mọi** dấu hỏi bằng một trong 26 chữ cái thường. Dấu hỏi không được chọn vẫn đóng góp 26 cách thay. Một cách được xác định bởi cả cách thay toàn bộ nguồn lẫn bộ vị trí.
- `dpstr331`: đếm đúng K **vị trí được chọn** có đánh dấu, không yêu cầu chọn hết các vị trí đánh dấu trong nguồn.
- `dpstr350`: một nhóm là dãy vị trí được chọn liên tiếp tối đại. Hai nhóm phải có ít nhất một vị trí không chọn ở giữa. K = 0 cho đáp án 0 vì xâu đích không rỗng.
- `dpstr351`: chỉ đếm bộ vị trí; không nhân thêm số cách sửa chữ, không chèn/xóa trong xâu đích. Các lớp sai lệch phải cộng từ 0 đến K.
- `dpstr352`: khoảng cách là hiệu hai chỉ số. Không áp điều kiện cho khoảng từ đầu/cuối nguồn tới ký tự được chọn; M = 1 không có cặp khoảng cách cần kiểm tra.

Mỗi bài có `task.md` theo mẫu knapsack, hai ví dụ, `solution.md` gồm thuật toán/chứng minh/độ phức tạp, lời giải C++11, bộ sinh, verifier, checker, `hash.json` và lệnh kiểm tra riêng. Không thêm Subtask, không xuất HTML.

## Cấu hình upload

```toml
[upload]
time_limit = 1
group = '03'
classes = 'C'
types = ['dp_string']
allowed_languages = ['PY3', 'CPP11', 'CPP14', 'CPP17', 'CPP20', 'JAVA8', 'C', 'PAS']
partial = true
```

Giới hạn thời gian được cố định ở 1 giây trong cả `timelimit` và `[upload].time_limit` của toàn bộ 10 bài.

Đáp án của mọi bài là một số nguyên nên dùng checker `standard` khi upload. Việc tạo và kiểm tra bộ bài không gửi dữ liệu lên máy chủ. Hiệu năng được đo bằng lời giải C++11 trên máy cục bộ; không suy ra rằng mọi cách cài đặt ở mọi ngôn ngữ được phép đều đạt 1 giây.

## Sinh và kiểm tra

Từ thư mục gốc dự án:

```sh
python3 custom/dpstr_count_tests/check.py
python3 custom/dpstr_count_tests/check.py --problem dpstr330 dpstr350
python3 custom/dpstr352/tests/check.py
```

Chỉ khi chủ động thay dữ liệu và cần ghi lại mã băm:

```sh
python3 custom/dpstr_count_tests/check.py --update-hashes
```

Mỗi bài có **34 cặp test**: 2 ví dụ, 12 biên, 8 nhỏ, 6 ngẫu nhiên và 6 lớn. Cả bộ có **340 cặp**, tương ứng 680 mục trong các file `hash.json`. Quy trình gọi trực tiếp các bước cần thiết của `Problem` để bỏ bước HTML, không cài thư viện và không upload.

Kiểm tra gồm:

- Biên dịch lời giải theo C++11, các công cụ theo C++17; cảnh báo được coi là lỗi.
- Sinh, xác thực toàn bộ đầu vào, tạo đáp án và kiểm tra bằng checker. Chạy lại lời giải trong giới hạn 1 giây mỗi test.
- Đối chiếu toàn bộ đáp án với `oracle.cpp`: đếm theo vị trí giữa/cuối cho các mẫu cố định; đổi thứ tự xử lý theo ký tự đích cho mẫu tổng quát, dấu hỏi, đánh dấu và sai lệch; tổng tiền tố theo vị trí kết thúc cho giới hạn khoảng cách; kết thúc tại vị trí trước hoặc mở nhóm mới bằng tổng tiền tố cho số nhóm.
- Liệt kê trực tiếp mọi bộ chỉ số trên 22 test ví dụ/biên/nhỏ mỗi bài. Với dấu hỏi, nhân số cách gán các dấu hỏi không chọn; không dùng lại DP của lời giải.
- Bổ sung mọi xâu ba chữ ngắn cho các mẫu cố định; mọi cặp xâu nhị phân ngắn và các lớp K cho bài tổng quát; 120 trường hợp ngẫu nhiên mỗi bài. Riêng dấu hỏi có thêm các trường hợp mọi chữ là `?`; riêng khoảng cách có đủ các biên L = R, L = 1, R = N và mẫu dài 1.
- So với công thức tổ hợp trên nguồn đồng nhất, gồm công thức nhóm $\binom{M-1}{K-1}\binom{N-M+1}{K}$ và không kề nhau $\binom{N-M+1}{M}$. Có test đáp án vượt 32 bit và test buộc lấy modulo.
- Thử verifier với sai kích thước, sai chữ cái, sai bảng đánh dấu, K hoặc khoảng cách ngoài cận, thiếu/thừa dữ liệu. Thử checker với đáp án đúng/sai, rỗng, dư token và đáp án lớn.
- Kiểm tra kích thước tối đa, tính tái lập từng seed, mã băm, ví dụ, cấu trúc đề và toàn bộ cấu hình upload.

Các test có nguồn ngắn hơn đích, chữ lặp, không có ký tự cần tìm, nhiều cách cho cùng nội dung, vị trí đầu/cuối, chữ ngoài mẫu, K = 0/5, không đủ nhóm, các nhóm sát giới hạn và dấu hỏi không được chọn. Kết quả lần chạy gần nhất được ghi trong `results.md`; nếu chỉ kiểm tra một phần, báo cáo được ghi tại `tests/results.md` của bài đầu tiên được chọn.
