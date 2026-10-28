# Bộ bốn bài luyện stack nâng cao

| Bài | Nội dung | Kỹ thuật của lời giải mẫu | Thời gian | Giới hạn chạy |
| --- | --- | --- | --- | --- |
| [SECOND](../second/task.md) | Tổng phần tử lớn thứ hai của mọi đoạn con | Hai stack tìm phần tử lớn hơn thứ nhất/thứ hai, đếm đóng góp | $O(N)$ | 3 giây |
| [KHUNGSANG](../khungsang/task.md) | Tổng diện tích mọi hình chữ nhật toàn ô 1 | Histogram, stack gộp nhóm và tổng có trọng số | $O(RC)$ | 4 giây |
| [CUASOMIN](../cuasomin/task.md) | Tổng cực tiểu mọi đoạn con nằm trong cửa sổ truy vấn | Offline theo đầu phải, stack, hệ số bậc nhất và bốn Fenwick | $O((N+Q)\log N)$ | 5 giây |
| [DUONGMIN](../duongmin/task.md) | Tổng cực tiểu các hậu tố trên đường tổ tiên | Stack có phiên bản, binary lifting và tổng đóng góp nhóm | $O((N+Q)\log N)$ | 5 giây |

Mỗi thư mục bài có `task.md`, `solution.md`, lời giải C++17 `sol/correct.cpp`, `verifier.cpp`, `checker.cpp`, các bộ sinh trong `gen/`, cấu hình `info.toml` và `hash.json`. Mỗi đề có ba ví dụ. Không chia subtask cho bộ bài này.

Mỗi bài có 45 test nền: 3 ví dụ, 12 trường hợp biên, 10 test nhỏ, 8 test ngẫu nhiên và 12 test kích thước tối đa. SECOND có thêm 2 test `jump` bắt trường hợp tìm phần tử lớn hơn thứ hai bằng cách nhảy lặp lại trên các con trỏ cố định. Tổng cộng 182 test chính thức. Đầu vào và đáp án được sinh trong `in/` và `out/`.

## Chạy kiểm tra

Chạy từ thư mục gốc dự án:

```sh
python3 dtqg/stack_tests/check.py
```

Chương trình biên dịch các thành phần, sinh dữ liệu, chạy verifier, tạo đáp án, kiểm tra thời gian lời giải mẫu và đối chiếu đáp án với oracle độc lập. Sau đó nó chạy các trường hợp nhỏ, thử dữ liệu không hợp lệ, thử checker, kiểm tra cấu trúc đề và đối chiếu hash. Quy trình không xuất HTML và không cần cài thêm thư viện Python.

Chỉ kiểm tra một bài:

```sh
python3 dtqg/duongmin/tests/check.py
```

Sau khi chủ động sửa dữ liệu hoặc bộ sinh, cập nhật hash cùng toàn bộ kiểm tra:

```sh
python3 dtqg/stack_tests/check.py --update-hashes
```

Kiểm tra thêm khả năng loại lời giải DFS pop/rollback có độ phức tạp bậc hai:

```sh
python3 dtqg/stack_tests/check.py --problem duongmin --check-slow
```

`--check-slow` trước hết kiểm tra tính đúng của `slow_duongmin.cpp` trên 3 ví dụ và 20 trường hợp nhỏ. Sau đó yêu cầu chương trình này vượt giới hạn 5 giây trên cả `max_03.in` và `max_04.in`. Kết quả đo phụ thuộc máy chạy.

Kiểm tra khả năng loại lời giải SECOND tìm phần tử lớn hơn thứ hai bằng cách nhảy lặp lại trên các liên kết `l[]`, `r[]` cố định:

```sh
python3 dtqg/second/tests/check.py --check-slow
```

Tùy chọn này kiểm tra `slow_second.cpp` trên 3 ví dụ, 20 trường hợp nhỏ và 6 trường hợp có cùng cấu trúc với test gây chậm. Sau đó yêu cầu chương trình vượt giới hạn 3 giây trên cả `jump_00.in` và `jump_01.in`. Xem [mô tả test SECOND](../second/tests/README.md).

## Đối chiếu độc lập

- **SECOND:** oracle dùng tập có thứ tự của các vị trí đã xét, theo giá trị giảm dần, tìm hai vị trí lớn hơn ở mỗi phía. Với $N\le3000$, còn kiểm tra bằng cách duyệt mọi đoạn con và giữ hai phần tử lớn nhất.
- **KHUNGSANG:** oracle dùng biên cực tiểu của histogram để tính đóng góp từng cột. Với bảng đủ nhỏ, còn duyệt các cặp hàng, tìm các đoạn cột hợp lệ và tính tổng diện tích trực tiếp.
- **CUASOMIN:** oracle dùng cây min tìm phần tử nhỏ hơn gần nhất ở bên trái, cùng một cây lazy lưu cực tiểu hiện tại và tổng lịch sử. Oracle này không dùng stack hoặc Fenwick. Với dữ liệu nhỏ, còn duyệt mọi đoạn con trong từng truy vấn.
- **DUONGMIN:** oracle dùng binary lifting có min trên cây đầu vào, kết hợp cây phân đoạn có phiên bản hỗ trợ gán đoạn và tổng đoạn theo độ sâu. Với tổng độ dài truy vấn không quá ba triệu, còn đi trực tiếp lên tổ tiên để kiểm tra.

Các bộ dữ liệu có hoán vị tăng/giảm, thứ tự xen kẽ, nhiều phần tử bằng nhau, giá trị 0, kết quả vượt 32 bit, bảng rất dài hoặc rất cao, cửa sổ lặp lại, cây dây, cây sao, cây cân bằng và cây nhiều nhánh chung một đoạn tổ tiên dài. Trong DUONGMIN, `max_03` gây pop toàn bộ đoạn chung ở mỗi nhánh; `max_04` gây pop các phần khác nhau của đoạn chung. Bộ sinh còn đổi nhãn đỉnh và thứ tự cạnh để kiểm tra lời giải có vô tình dựa vào thứ tự đầu vào hay không.

## Kết quả kiểm tra

| Bài | Test chính thức | Trường hợp nhỏ đối chiếu | Dữ liệu sai bị verifier loại | Phép thử checker |
| --- | ---: | ---: | ---: | ---: |
| SECOND | 47 | 1123 | 9 | 27 |
| KHUNGSANG | 45 | 862 | 11 | 27 |
| CUASOMIN | 45 | 613 | 12 | 33 |
| DUONGMIN | 45 | 514 | 16 | 33 |
| Tổng | 182 | 3112 | 48 | 120 |

Toàn bộ các kiểm tra trên đã đạt. SECOND có 94 mục hash cho 47 đầu vào và 47 đáp án; mỗi bài còn lại có 90 mục hash. Bản DFS pop/rollback của DUONGMIN đã khớp 23 trường hợp kiểm tra tính đúng và vượt 5 giây trên cả hai test hiệu năng nêu trên ở máy kiểm tra hiện tại.
