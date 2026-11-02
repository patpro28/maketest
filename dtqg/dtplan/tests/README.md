# Kiểm thử DTPLAN

## Thành phần

- `task.md`: phiên bản nâng giới hạn lên $m\le20$, giữ ví dụ gốc, giới hạn nguyên liệu/hệ số và tên tệp `PLAN.INP`/`PLAN.OUT`; mã trong dự án là `DTPLAN`. Bốn subtask lần lượt là $A,B\le1000$ (10%), $m\le3$ (20%), $m\le10$ (30%) và toàn bộ giới hạn (40%).
- `solution.md`, `sol/correct.cpp`: DP theo 30 bit, trạng thái là hai số nhớ; tính bảng `ways` bằng ba lô $0/1$ hai chiều rồi chia nhóm chẵn/lẻ. Không liệt kê $2^{20}$ tập con.
- `tests/oracle.cpp`: thực hiện từng lựa chọn bit của từng loại sản phẩm bằng các phép cộng dịch trên bảng hai chiều, rồi lọc chẵn/lẻ và chuyển số nhớ. Không dùng bảng tập con hoặc danh sách chuyển theo cặp tổng của lời giải mẫu.
- `verifier.cpp`, `checker.cpp`: kiểm tra đầu vào đúng giới hạn và đáp án là một số nguyên trong đoạn từ $0$ tới $10^9-1$; không chấp nhận đáp án thừa dữ liệu.
- `gen/`: bộ sinh có seed cố định; `info.toml` khai báo bốn nhóm test theo subtask, điểm từng test và cấu hình upload dựa trên DAYNEN. Tổng điểm bài được đặt bằng 100.

Lời giải mẫu dùng nhập/xuất chuẩn nếu không có `PLAN.INP` trong thư mục chạy. Nếu có tệp đó, nó đọc tệp và ghi kết quả vào `PLAN.OUT`. Cơ chế này giữ tương thích với đề gốc và hệ thống chấm qua nhập/xuất chuẩn.

## Dữ liệu chính thức

Có 86 test: 1 ví dụ gốc và 85 test được chấm điểm. Toàn bộ 55 test trước khi chia điểm được giữ nguyên dữ liệu và đáp án, chuyển sang tên nhóm mới; bổ sung 31 test để củng cố các subtask và chia đều điểm trong từng nhóm. Dữ liệu và đáp án được tạo trong `in/`, `out/`; `hash.json` có 172 mục tương ứng.

Các test được phân vào nhóm đầu tiên thỏa điều kiện: nhóm 1 có $A,B\le1000$; nhóm 2 có $m\le3$ và ít nhất một lượng nguyên liệu lớn hơn 1000; nhóm 3 có $4\le m\le10$ và ít nhất một lượng nguyên liệu lớn hơn 1000; nhóm 4 có $11\le m\le20$ và ít nhất một lượng nguyên liệu lớn hơn 1000. Như vậy các nhóm chấm điểm không bị tính trùng.

Các test lớn vẫn có đủ 20 loại; các test trung gian có các mốc 11, 15 và 19 loại. Test sát giới hạn từng nhóm gồm 20 loại với nguyên liệu tới 1000, 3 loại với nguyên liệu tới $10^9$, và 10 loại với nguyên liệu lớn. Bảng ánh xạ trong `tests/check.py::legacy_cases` xác định tên mới của từng test cũ.

## Điểm từng testcase

Cấu hình dùng trực tiếp `[[tests]].points` theo hướng dẫn tại README gốc, không đặt `[upload].manifest`. Mỗi test trong một nhóm nhận cùng trọng số nguyên:

| Nhóm | Số test | `points` mỗi test | Tổng trọng số | Tỉ lệ |
| --- | ---: | ---: | ---: | ---: |
| `example` | 1 | 0 | 0 | 0% |
| `sub1` | 25 | 4 | 100 | 10% |
| `sub2` | 10 | 20 | 200 | 20% |
| `sub3` | 10 | 30 | 300 | 30% |
| `sub4` | 40 | 10 | 400 | 40% |
| Tổng | 86 | | 1000 | 100% |

Tổng trọng số testcase là 1000, trong khi `[upload].points = 100` đặt thang điểm bài là 100. Điểm được cộng theo từng testcase, không dùng nhóm chấm tất cả hoặc không được điểm. Không dùng `--testcase-points` khi upload bài này vì tùy chọn đó ghi đè toàn bộ trọng số đã chia.

Quy trình kiểm tra dựng cấu hình upload bằng chính `ProblemUpload`, xác nhận tổng trọng số, điểm từng test, tỉ lệ 10/20/30/40 và điều kiện dữ liệu của từng nhóm. Bước này không kết nối hoặc gửi dữ liệu lên máy chủ.

Các trường hợp trọng tâm:

- Chỉ một loại sản phẩm, có nghiệm hoặc không có nghiệm.
- Hệ số lớn hơn lượng nguyên liệu; không thể sản xuất dù các ràng buộc vẫn hợp lệ.
- Nhiều loại trùng cặp hệ số, cần phân biệt số lượng ở từng loại.
- Hai phương trình tỉ lệ nhau hoặc mâu thuẫn, thiếu điều kiện chia hết và lượng nguyên liệu rất lệch nhau.
- Hệ số $1$ và $5$, cả hai lượng nguyên liệu đạt $10^9$, mục tiêu sát các mốc lũy thừa hai.
- Bộ hệ số đa dạng làm nhiều cặp số nhớ có thể đạt tới.
- Với 20 loại, bảng `ways` có thể có rất nhiều tập chung một cặp tổng; cần cộng đúng số lượng, không chỉ đánh dấu cặp tổng có thể đạt tới.
- Đáp án lớn cần lấy modulo đúng $10^9$, bao gồm trường hợp hai phương trình thực chất chỉ còn một ràng buộc.

Với $m$ loại trùng hệ số $(a,b)$, nếu $A/a=B/b=t$ là số nguyên không âm, số phương án chính xác là $\binom{t+m-1}{m-1}$; nếu không, số phương án bằng $0$. Python tính tổ hợp bằng số nguyên tùy ý rồi lấy modulo để kiểm tra độc lập các test thuộc dạng này.

## Các bước kiểm tra

Chạy từ thư mục gốc dự án:

```sh
python3 dtqg/dtplan/tests/check.py
```

Sau khi chủ động thay bộ sinh hoặc dữ liệu và cần cập nhật hash:

```sh
python3 dtqg/dtplan/tests/check.py --update-hashes
```

Quy trình biên dịch các thành phần, sinh và xác thực toàn bộ dữ liệu, tạo đáp án, chạy lời giải mẫu qua checker và đối chiếu với oracle. Trên mỗi test chính thức, còn yêu cầu lời giải mẫu chạy trong 1 giây, tương ứng giới hạn upload. Giới hạn chạy cục bộ trong `info.toml` là 4 giây.

Ngoài các test chính thức, quy trình kiểm tra 2500 trường hợp nhỏ:

- 25 cặp hệ số của một loại sản phẩm, với mọi $1\le A,B\le7$: 1225 trường hợp.
- 325 bộ gồm hai cặp hệ số, cho phép hai loại trùng nhau, với ba cặp mục tiêu: 975 trường hợp.
- 300 trường hợp ngẫu nhiên với tối đa 20 loại và mục tiêu tới 45.

Mỗi trường hợp nhỏ được đối chiếu với DP ba lô hai chiều theo thứ tự loại sản phẩm. Những trường hợp có không quá hai loại còn được kiểm tra bằng liệt kê trực tiếp số lượng sản phẩm. Các kiểm tra bổ sung gồm hoán vị thứ tự loại, đổi chỗ hai nguyên liệu, chế độ đọc/ghi tệp, dữ liệu sai và checker với đầu ra sai/thiếu/thừa.

Quy trình còn kiểm tra cấu trúc đề, ví dụ khớp tệp mẫu, nội dung lời giải tách khỏi kiểm thử, khả năng tái tạo mọi test theo seed và toàn bộ hash. Không xuất HTML.

## Kết quả

Đã đạt toàn bộ 86 test chính thức, 2500 trường hợp nhỏ, 2233 phép đối chiếu bằng liệt kê số lượng, 40 phép kiểm tra tính bất biến khi hoán vị loại hoặc đổi chỗ nguyên liệu, 3 phép kiểm tra tệp vào/ra, 16 đầu vào sai và 33 phép thử checker. Verifier cũng chấp nhận nhiều dấu cách giữa các số. Cấu hình điểm qua `ProblemUpload` khớp chính xác tỉ lệ đã yêu cầu.

Toàn bộ 172 mục hash đã được đối chiếu. Dữ liệu và đáp án của cả 55 test cũ được so sánh bằng SHA-256 trước và sau khi đổi nhóm, xác nhận không thay đổi nội dung. Thời gian lớn nhất của một lần chạy lời giải mẫu trong lượt đo hiện tại khoảng 0,035 giây, dưới giới hạn upload 1 giây. Thời gian phụ thuộc máy chạy.

## Đo số phép chuyển

`sub4_19.in` (trước đây là `stress_00.in`) dùng $m=20$, $A=999999937$, $B=999999929$. Hệ số được tạo từ dãy $(5,1),(2,5),(5,3),(4,5),(5,5),(1,5),(5,2),(3,5),(5,4),(5,5)$ lặp tới đủ 20 loại. Với dữ liệu này, $s_a=80$, $s_b=80$ và có 1973 cặp tổng hệ số khác nhau.

Quy trình kiểm tra biên dịch thêm bản có `COUNT_TRANSITIONS`, đếm số lần duyệt một cặp tổng hợp lệ về chẵn/lẻ từ một trạng thái DP có số cách khác 0. Kết quả phải bằng **32003440 lượt chuyển**, khoảng $3,2\cdot10^7$. Đáp án của bản có bộ đếm vẫn phải khớp đáp án chính thức. `sub4_20` đổi chỗ hai nguyên liệu; `sub4_21` hoán vị các loại; `sub4_22` dùng một họ hệ số khác có nhiều trạng thái.

Đây là số phép chuyển thực tế trên một test nặng cụ thể, không phải chặn trên tuyệt đối cho mọi đầu vào. Một lượt chuyển gồm nhiều phép toán máy. Không thể khẳng định mọi lời giải toàn bộ đều cần từng ấy bước: oracle thực hiện lựa chọn bit từng biến bằng phép dịch bảng có thể nhanh hơn cách gộp `ways`.
