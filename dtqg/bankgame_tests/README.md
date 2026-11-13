# Lộ trình luyện tập trước BANK3 và WGAMEPN

Mỗi bài nguồn có ba phiên bản từ dễ đến khó rồi đến bài gốc. Tất cả nằm trong `dtqg/`, dùng mã bắt đầu bằng `DT`, giữ đề trong `task.md` và không xuất HTML. Các phiên bản có cùng định dạng dữ liệu với bài gốc, nhưng thu hẹp điều kiện để tách từng bước kiến thức.

## Ngân sách

| Thứ tự | Bài | Điều kiện chính | Trọng tâm | Độ phức tạp mỗi bộ dữ liệu |
| --- | --- | --- | --- | --- |
| 1 | [DTBANKONE — Một công trình](../dtbankone/task.md) | n = 1, m ≤ 20, giá trị ≤ 10^9 | Liệt kê tập con, tổng tập con | O(2^m) |
| 2 | [DTBANKTWO — Hai công trình](../dtbanktwo/task.md) | n ≤ 2, m ≤ 20, giá trị ≤ 1000 | Đếm bằng DP hai tổng, ba lựa chọn cho mỗi gói | O(m(A+1)(B+1)) |
| 3 | [DTBANKSMALL — Phân bổ ít gói kích cầu](../dtbanksmall/task.md) | n ≤ m ≤ 10, giá trị ≤ 10^9 | DP tập đã dùng, duyệt tập con rời nhau | O(n·3^m) |
| 4 | [DTBANK3 — Ngân sách](../dtbank3/task.md) | n ≤ m ≤ 20, giá trị ≤ 10^9 | DP chọn/bỏ qua từng gói, ghi nhớ mặt nạ và chỉ số tiếp theo | O(m·2^m) |

Ở mức 3, giới hạn số tiền trở lại 10^9 nên DP theo tổng tiền không còn phù hợp; cần chuyển sang tập con. Ở bài gốc, tăng số gói lên 20 buộc tránh truy hồi duyệt mọi cặp tập con rời nhau. Các công trình và gói đều có nhãn; những giá trị bằng nhau không được gộp thành một đối tượng. Gói chưa sử dụng được phép bỏ lại. Cả bốn bài có 1 ≤ T ≤ 3 và lấy dư theo 10^9+7.

## Trò chơi trên bảng chữ

Cả bốn bài có kích thước bảng tối đa 150 × 150, mô tả ô cấm bằng `#`, chỉ đi xuống/phải và lấy dư theo D với 1 ≤ D ≤ 10^9.

| Thứ tự | Bài | Điều kiện riêng | Trọng tâm | Độ phức tạp chính |
| --- | --- | --- | --- | --- |
| 1 | [DTWGAMEPATH — Bảng chữ đồng nhất](../dtwgamepath/task.md) | S là một ký tự, mọi ô không cấm bằng S, ô đầu không cấm | Đếm đường đi trên lưới | O(mn) |
| 2 | [DTWGAMEPAL — Đường đi đối xứng](../dtwgamepal/task.md) | S là một ký tự trùng ký tự ở ô đầu | DP đi từ hai đầu vào giữa | O((m+n)r²) |
| 3 | [DTWGAMECHAR — Đường đi đối xứng chứa một ký tự](../dtwgamechar/task.md) | S là một ký tự bất kỳ | Thêm bit đã gặp ký tự bắt buộc | O((m+n)r²) |
| 4 | [DTWGAMEPN — Trò chơi trên bảng chữ](../dtwgamepn/task.md) | 1 ≤ độ dài S ≤ 20 | Bộ tự động hai mẫu S và đảo S, xử lý mẫu qua tâm | O((m+n)r²·độ dài S) |

Trong bảng, r = min(m,n). Lời giải dùng hai lớp theo bước đi, chuyển vị để giảm số hàng. Bài gốc dùng không quá hai lần độ dài S trạng thái tự động, thay cho việc giữ độc lập hai độ dài khớp. Chi tiết xây bộ tự động và chứng minh xử lý tâm nằm trong [lời giải](../dtwgamepn/solution.md).

## Thành phần và nguồn

Mỗi thư mục bài có `task.md`, `solution.md`, `info.toml`, `sol/correct.cpp`, `verifier.cpp`, `checker.cpp`, `gen/cases.cpp`, ví dụ trong `gen/`, `hash.json` và `tests/README.md`. Bộ sinh và phần kiểm tra đầu vào dùng hai tệp chung `generator.h` và `validator.h` trong thư mục này. Khi chuyển bài sang môi trường khác cần giữ các đường dẫn tương đối này.

Hai bài gốc chuyển từ `/Users/Shared/bank3.pdf` và `/Users/Shared/wgamepn.pdf` do người dùng cung cấp; đã xem trực tiếp trang đề để đọc các công thức bị thiếu trong lớp văn bản PDF. Ví dụ và giới hạn tổng quát được giữ nguyên. Không thêm mục Subtask vào bất kỳ bài nào. Sáu bài luyện tập tự biên soạn có ít nhất hai ví dụ; DTBANK3 giữ nguyên một ví dụ chứa hai bộ dữ liệu của nguồn, DTWGAMEPN giữ nguyên hai ví dụ theo thứ tự nguồn.

Hai mã nguồn người dùng cung cấp được sao chép nguyên vẹn tại [sources/bank3.cpp](sources/bank3.cpp) và [sources/wgamepn.cpp](sources/wgamepn.cpp) để đối chiếu. Tệp `compat/bits/stdc++.h` chỉ hỗ trợ biên dịch các bản nguồn nguyên vẹn trên macOS. Các lời giải mới dùng header C++ chuẩn và không phụ thuộc tệp tương thích này.

Một trường hợp biên của mã WGAMEPN nguồn là bảng 1 × 1, S = `a`, ô duy nhất là `a`, D = 1: mã nguồn trả 1 ở điều kiện dừng, trong khi đáp án theo đề phải là 0. Quy trình có ghi nhận trường hợp này; lời giải mới khởi tạo bằng 1 mod D và cho đúng 0. Không chạy bản nguồn khi đầu mút là `#` vì mã nguồn không chặn trường hợp này trước khi đánh chỉ số ký tự; các trường hợp đó được đối chiếu bằng liệt kê trực tiếp. Điều kiện ô cấm và phép lấy dư trong các đề mới tuân theo ý nghĩa đề nguồn.

Cấu hình upload dùng nhóm `04`, lớp `E`, loại `doituyen`, bộ nhớ 256 MiB. Cả tám bài đều có giới hạn thời gian 1 giây, thống nhất `timelimit` và `[upload].time_limit` trong `info.toml`. Mỗi bài có tổng điểm 100; ví dụ trọng số 0, các test sinh trọng số 1, không chia subtask.

## Chạy lại kiểm tra

Tại thư mục gốc dự án:

```sh
python3 dtqg/bankgame_tests/check.py
```

Chạy một bài:

```sh
python3 dtqg/bankgame_tests/check.py --problem dtwgamepn
```

Chỉ khi chủ động thay đổi dữ liệu, thêm `--update-hashes`. Có thể chọn trình biên dịch bằng `CXX` và cờ bằng `CXXFLAGS`. Quy trình gọi riêng các bước sinh, xác thực đầu vào, sinh đáp án, chạy checker và đối chiếu hash; không dùng các chế độ tự xuất HTML.

## Nội dung kiểm tra

- Mỗi bài có 28 test sinh bằng seed cố định: 10 test biên, 8 test nhỏ và 10 test lớn. Cộng với ví dụ, DTBANK3 có 29 test; bảy bài còn lại có 30 test mỗi bài. Mỗi test sinh được sinh lại và so sánh nội dung để xác nhận tính tái lập.
- Mỗi bài có thêm 120 đầu vào nhỏ độc lập. Ngân sách được đối chiếu bằng cách duyệt lần lượt các gói và chọn nơi cấp hoặc bỏ lại, ghi nhớ các nhu cầu còn thiếu. Bảng chữ được duyệt toàn bộ đường đi rồi kiểm tra đối xứng và xâu con trực tiếp.
- Mọi test chính thức Ngân sách đều đối chiếu thêm với mã nguồn người dùng cung cấp. Trường hợp một/hai công trình còn dùng cách chia đôi các gói, đếm các cặp tổng và ghép hai nửa. Trường hợp nhiều công trình với m ≤ 10 dùng phép duyệt theo từng gói độc lập; dữ liệu đồng giá trị lớn dùng công thức hệ số đa thức tính bằng số nguyên chính xác.
- Với bảng chữ, mọi test chính thức có hai đầu mút là chữ và D > 1 đều đối chiếu với mã nguồn người dùng cung cấp. Dữ liệu bảng nhỏ còn được liệt kê toàn bộ đường. Trên bảng lớn có ký tự đồng nhất theo từng đường chéo phụ, mọi đường đọc cùng một xâu; kiểm tra xâu đó trực tiếp rồi đếm đường tránh ô cấm bằng DP lưới thông thường.
- DTWGAMEPN có thêm 67 trường hợp tập trung vào mẫu dài 20, mẫu qua tâm chẵn/lẻ, mẫu đảo xuất hiện ở nửa phản chiếu, mẫu có tiền tố/hậu tố chồng lấn, đường chỉ một hàng/cột, ô đầu/cuối cấm, D = 1, mẫu dài hơn đường và phân biệt xâu con với dãy con. Nhiều lần xuất hiện mẫu trên cùng đường vẫn chỉ tính một đường.
- Validator bị thử bằng đầu vào thiếu/thừa dữ liệu, số ngoài miền, kích thước sai, ký tự sai và điều kiện riêng của từng phiên bản. Checker bị thử bằng đáp án sai, thiếu/thừa token, token không phải số, tràn số và đáp án đúng có khoảng trắng khác nhau.
- Đối chiếu tiêu đề, mã thư mục, thứ tự heading, khối ví dụ `text`, cấu hình upload, trọng số và số hash. Lời giải không có heading cấp 1 hoặc nội dung kiểm thử. Toàn bộ 32 chương trình C++ mới được kiểm tra với `-Wall -Wextra -Werror`.

## Kết quả hoàn tất

Toàn bộ **239 test chính thức**, **960 đầu vào nhỏ độc lập** và **67 trường hợp bổ sung cho DTWGAMEPN** đều đạt. Có **243 lượt đối chiếu bổ sung** các bộ dữ liệu chính thức bằng phương pháp độc lập và **226 tệp chính thức** được so với mã nguồn do người dùng cung cấp. Validator loại đúng **98 đầu vào sai**, checker đạt **150 tình huống**, toàn bộ **478 mục hash** khớp. Kiểm tra cảnh báo nghiêm ngặt đạt cho cả 32 chương trình C++ mới.

| Mã bài | Test chính thức | Thời gian lớn nhất đo được | Giới hạn |
| --- | ---: | ---: | ---: |
| DTBANKONE | 30 | 0.0073 giây | 1 giây |
| DTBANKTWO | 30 | 0.0152 giây | 1 giây |
| DTBANKSMALL | 30 | 0.0024 giây | 1 giây |
| DTBANK3 | 29 | 0.1140 giây | 1 giây |
| DTWGAMEPATH | 30 | 0.0041 giây | 1 giây |
| DTWGAMEPAL | 30 | 0.0092 giây | 1 giây |
| DTWGAMECHAR | 30 | 0.0102 giây | 1 giây |
| DTWGAMEPN | 30 | 0.0210 giây | 1 giây |

Thời gian phụ thuộc máy chạy. Số liệu chi tiết được lưu tại `results.json` sau mỗi lần kiểm tra; các kết quả trên cũng được ghi trong `tests/README.md` của từng bài.
