# Kiểm thử DTPHOTO

## Nguồn và cấu trúc gói

Đề được chuyển từ trang duy nhất của tài liệu người dùng cung cấp tại `/Users/patpro28/Downloads/PHOTO.pdf`, mục **303. CHỤP ẢNH**. Đã đối chiếu trực tiếp bản render để xác nhận các ký hiệu không trích xuất được thành văn bản: $n\le10^5$, năm bức ảnh, tên tệp và ví dụ. SHA-256 của PDF nguồn:

```text
4a692ed6fc8b446881d30a9c045a3fb35776485a289540aca3405fd62a2e0a57
```

`task.md` giữ ý nghĩa, giới hạn, ví dụ gốc và tên tệp `PHOTO.INP`/`PHOTO.OUT`, chuyển sang cấu trúc đề của dự án với mã `DTPHOTO`. Theo yêu cầu bổ sung, có nhóm 30% điểm với $n\le8$ để duyệt ảnh rời hàng của từng người và khôi phục thứ tự bằng sắp xếp tô pô; 70% còn lại áp dụng toàn bộ giới hạn. Lời giải nằm trong `solution.md`; các nội dung kiểm thử chỉ ghi tại tài liệu này.

- `sol/correct.cpp`: dựng năm bảng vị trí, dùng `std::sort` với so sánh theo đa số ít nhất ba ảnh. Tự đọc/ghi `PHOTO.INP` và `PHOTO.OUT` nếu có tệp đầu vào; nếu không, dùng nhập/xuất chuẩn.
- `tests/oracle.cpp`: merge sort lặp, triển khai độc lập với `std::sort`. Kết quả còn được so với thứ tự chuẩn đã biết của bộ sinh.
- `tests/brute_assignment.cpp`: duyệt đủ $5^n$ cách gán ảnh rời hàng cho từng người khi $n\le8$, rồi sắp xếp tô pô các ràng buộc thứ tự còn lại. Không sử dụng quy tắc đa số 3/5 và không duyệt hoán vị. Các phép kiểm tra tại nhóm nhỏ dùng bản này để xác nhận lời giải subtask 1 chạy được.
- `verifier.cpp`: kiểm tra $n$, định dạng năm dòng, miền số hiệu và tính hoán vị của từng bức ảnh. Chấp nhận nhiều dấu cách giữa hai số như đề nguồn.
- `checker.cpp`: kiểm tra đủ và đúng $n$ vận động viên theo thứ tự chuẩn, cho phép khác khoảng trắng, loại dữ liệu thiếu/thừa hoặc số hiệu không hợp lệ.
- `gen/`: bộ sinh có seed cố định. `info.toml` có mục upload dựa trên DAYNEN, giới hạn upload 1 giây và tổng điểm bài bằng 100.

## Kiểm tra điều kiện mỗi người rời hàng nhiều nhất một lần

Tính hoán vị của từng dòng chưa đủ để bảo đảm điều kiện chung của năm ảnh. Bộ sinh bắt đầu từ một thứ tự chuẩn đã biết và gán mỗi vận động viên một giá trị trong đoạn $[0,5]$: $0$ nghĩa là không rời hàng; $k>0$ nghĩa là chỉ được rời hàng trong ảnh thứ $k$.

Khi tạo ảnh $k$, giữ nguyên thứ tự tương đối của các vận động viên không thuộc nhóm $k$, rồi chèn các vận động viên nhóm $k$ vào các khoảng tùy ý, có thể đổi thứ tự giữa những người cùng rời hàng. Do các nhóm không giao nhau, dữ liệu sinh ra thỏa điều kiện đề bài.

Chạy bộ sinh với đối số thứ hai `witness` để lấy ba dòng: $n$, thứ tự chuẩn và nhóm rời hàng của các vận động viên theo mã từ $1$ tới $n$. Chương trình kiểm tra gọi chế độ này cho mọi seed chính thức. Với mỗi ảnh, nó xóa nhóm được phép rời hàng khỏi cả ảnh lẫn thứ tự chuẩn và yêu cầu hai dãy còn lại bằng nhau. Đây là chứng cứ trực tiếp cho tính hợp lệ của dữ liệu, không phụ thuộc thuật toán sắp xếp đáp án.

Verifier kiểm tra cấu trúc đầu vào; điều kiện rời hàng của toàn bộ bộ test được kiểm tra bằng các witness nói trên. Với ví dụ gốc, witness được chép từ phần giải thích nguồn: nhóm lần lượt là $\{3,8\}$, $\{2,4,6\}$, $\{1\}$, $\{5\}$, $\{7\}$; vận động viên $9$ không rời hàng.

## Dữ liệu chính thức

Có 45 test: 1 ví dụ nguồn, 11 test `tiny` với $n\le8$, 5 test biên, 8 test nhỏ, 8 test ngẫu nhiên và 12 test lớn. Mỗi test lớn có $n=100000$. `hash.json` có 90 mục cho đầu vào và đáp án.

Cả 41 test cũ được giữ nguyên nội dung: `edge_00` tới `edge_06` chuyển thành `tiny_00` tới `tiny_06`; `edge_07` tới `edge_11` chuyển thành `edge_00` tới `edge_04`; các test khác giữ tên. Bổ sung bốn test mới `tiny_07` tới `tiny_10`, gồm một test $n=7$ và ba test $n=8$. Đầu vào và đáp án trước/sau được đối chiếu SHA-256 để xác nhận không mất dữ liệu cũ.

## Điểm từng testcase

Điểm được đặt trực tiếp bằng `[[tests]].points`, không dùng manifest `cases`:

| Nhóm | Số test | Trọng số/test | Tổng trọng số | Tỉ lệ |
| --- | ---: | ---: | ---: | ---: |
| Ví dụ | 1 | 0 | 0 | 0% |
| `tiny`, $n\le8$ | 11 | 9 | 99 | 30% |
| Các nhóm còn lại, $n>8$ | 33 | 7 | 231 | 70% |
| Tổng | 45 | | 330 | 100% |

`[upload].points = 100` đặt thang điểm bài. Tổng trọng số testcase là 330, nên nhóm nhỏ nhận đúng 30 điểm khi đạt toàn bộ nhóm, các nhóm còn lại nhận 70 điểm. Không dùng `--testcase-points` khi upload vì tùy chọn này ghi đè trọng số đã chia.

Chương trình kiểm tra dùng `ProblemUpload` để dựng cấu hình thực tế, đối chiếu số lượng test, trọng số và giới hạn $n$ của từng nhóm. Không có request nào được gửi lên máy chủ trong quá trình này.

Các trường hợp gồm:

- Một vận động viên; năm ảnh giống nhau; không có ai rời hàng.
- Chỉ một ảnh bị đảo mạnh, các ảnh còn lại giữ thứ tự chuẩn.
- Hai nhóm gây sai thứ tự cùng nằm trong ba ảnh đầu, bắt cách chỉ bỏ phiếu trên ba ảnh.
- Mọi vận động viên đều rời hàng đúng một lần; cả năm ảnh đều thay đổi.
- Mỗi lần chỉ một người rời hàng, hoặc các nhóm rời hàng có kích thước rất lệch nhau.
- Chèn ra đầu, ra cuối, vào giữa, vào khoảng ngẫu nhiên; đổi thứ tự giữa các vận động viên cùng rời hàng.
- Thứ tự chuẩn tăng, giảm, xen kẽ lớn/nhỏ, quay vòng, đảo từng khối và hoán vị ngẫu nhiên.

Các test biên có trường hợp mà sắp theo trung vị hoặc tổng năm vị trí cho thứ tự sai. Chương trình yêu cầu bộ test thực sự loại được cả bốn cách: lấy ảnh đầu, lấy trung vị vị trí, lấy trung bình vị trí và chỉ bỏ phiếu theo ba ảnh đầu.

## Kiểm tra dữ liệu nhỏ

Ngoài bộ chính thức, có 988 trường hợp nhỏ sau khi loại các đầu vào trùng nhau:

- Liệt kê mọi cách gán nhóm rời hàng từ $0$ tới $5$ cho tối đa bốn vận động viên, với hai cách chèn nhóm vào đầu hoặc cuối.
- Xét toàn bộ 32 bộ năm ảnh cho hai vận động viên.
- Các trường hợp ngẫu nhiên tới 40 vận động viên, thay đổi cả thứ tự chuẩn, nhóm rời hàng và cách chèn.

Mọi trường hợp có witness được kiểm tra độc lập. Đáp án nhỏ còn được xác định bằng cách xét toàn bộ cặp vận động viên, đếm số phần tử đứng trước từng người theo đa số, rồi kiểm tra các hạng là đúng $0,1,\ldots,n-1$. Kết quả này phải trùng thứ tự chuẩn, lời giải mẫu và merge sort.

## Duyệt $5^n$ cách gán và sắp xếp tô pô

Bản `brute_assignment.cpp` quay lui gán mỗi người vào đúng một trong năm ảnh. Người không cần rời hàng có thể được gán một ảnh tùy ý rồi coi như chèn lại chỗ cũ; xóa thêm người này khỏi cả ảnh lẫn thứ tự chuẩn không làm mất tính tương thích.

Với mỗi cách gán, xóa nhóm tương ứng khỏi từng ảnh rồi nối cạnh giữa các phần tử liên tiếp của dãy còn lại. Sắp xếp tô pô đồ thị gộp: nếu không có chu trình thì thu được thứ tự chuẩn phù hợp cách gán. Giữ nguyên các cạnh trùng nhau và cập nhật bậc vào cho từng cạnh. Không dùng đa số hay đánh dấu theo vị trí tuyệt đối.

Bản dùng trong kiểm tra duyệt đủ $5^n$ cách gán, xác nhận mọi cách gán thành công đều cho cùng đáp án và đối chiếu với witness cho cả 11 test `tiny`. Như vậy thời gian đo bao gồm toàn bộ không gian tìm kiếm; lời giải dự thi có thể dừng ở cách gán thành công đầu tiên. Trong 988 trường hợp nhỏ ngoài bộ chính thức, 606 trường hợp có $n\le8$ cũng được đối chiếu bằng bản này.

Có thêm phản ví dụ ngữ nghĩa chỉ dùng trong kiểm tra nội bộ: hai ảnh `3 2 1` và ba ảnh `1 2 3`. Đa số vẫn xác định thứ tự `1 2 3`, nhưng mỗi ảnh đảo cần ít nhất hai trong ba người rời hàng, không thể chọn hai tập không giao nhau. Bản kiểm tra trực tiếp trả `IMPOSSIBLE`, xác nhận nó kiểm tra điều kiện rời hàng thực sự. Dữ liệu không hợp lệ này không được đưa vào bộ test chính thức.

## Chạy lại

Từ thư mục gốc dự án:

```sh
python3 dtqg/dtphoto/tests/check.py
```

Sau khi chủ động sửa bộ sinh hoặc dữ liệu và cần cập nhật hash:

```sh
python3 dtqg/dtphoto/tests/check.py --update-hashes
```

Quy trình biên dịch các thành phần, sinh và xác thực dữ liệu, tạo đáp án qua checker, chạy lời giải mẫu, kiểm tra witness và đối chiếu oracle. Mỗi test chính thức còn được đo riêng với giới hạn 1 giây; mỗi test `tiny` phải chạy được bản duyệt $5^n$ cách gán trong cùng giới hạn. Chương trình kiểm tra cả tính tái lập của mọi seed, cấu trúc đề, ví dụ, tỉ lệ điểm, quy tắc nội dung lời giải, chế độ tệp và toàn bộ hash. Không xuất HTML.

## Kết quả

Lượt chạy đầy đủ đạt: 45 test chính thức có witness hợp lệ, cả 11 test `tiny` được đối chiếu bằng duyệt đủ $5^n$ cách gán và sắp xếp tô pô; 988 trường hợp nhỏ, trong đó 606 trường hợp được đối chiếu thêm bằng bản duyệt này. Trường hợp không thể gán người rời hàng bị loại; bốn cách giải sai bị bắt. Ba lượt nhập/xuất tệp, 16 đầu vào sai cấu trúc và 39 tình huống checker đều đạt yêu cầu.

Toàn bộ 90 mục hash khớp. Thời gian lớn nhất đo được là 0,4715 giây cho lời giải mẫu và 0,2734 giây cho bản duyệt đủ các cách gán trên nhóm `tiny`. Thời gian đo phụ thuộc máy chạy; giới hạn upload là 1 giây.

Đã đối chiếu lại cấu hình điểm sau khi đổi sang 30%/70%: 11 test `tiny` có trọng số 9/test, 33 test còn lại có trọng số 7/test; ví dụ vẫn có trọng số 0. Dữ liệu và đáp án giữ nguyên, toàn bộ hash được đối chiếu lại.
