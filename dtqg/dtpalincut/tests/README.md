# Kiểm thử DTPALINCUT

## Nguồn và cách hiểu đề

Đề được chuyển từ trang duy nhất của tài liệu người dùng cung cấp tại `/Users/patpro28/Downloads/PALINCUT.pdf`. Đã đọc văn bản và đối chiếu trực tiếp bản render, gồm hai bảng ví dụ và ba mức subtask. SHA-256 của PDF nguồn:

```text
9143412e897abd8023f2cb90a0c779c511c9a83fce602890d7434d3ee2c9454c
```

`task.md` giữ nguyên hai ví dụ, tên tệp `PALINCUT.INP`/`PALINCUT.OUT`, giới hạn xâu 10000, tối đa 200 trường hợp và 13 đoạn cần chọn. Giữ các điều kiện subtask gốc, đổi tỉ lệ thành 25%–25%–50% theo yêu cầu.

Các ví dụ nguồn xác nhận hai điểm cần làm rõ trong đề: có thể bỏ hạt thừa, và thứ tự các đoạn trên xâu không phải thứ tự các độ dài trong đầu vào. Độ dài lặp lại vẫn cần được đáp ứng đủ số lần. Không thay bài thành chia toàn bộ xâu thành các đoạn theo thứ tự cho trước.

Nguồn không nêu chặn trên riêng cho các số nguyên dương độ dài. Verifier chấp nhận token số nguyên dương; lời giải chặn giá trị đọc tại $n+1$ để trả `NO` an toàn với số lớn, kể cả vượt phạm vi 64 bit. Không tự thêm một chặn hữu hạn vào đề.

## Thành phần

- `sol/correct.cpp`: Manacher, bảng vị trí kết thúc sớm nhất cho từng độ dài phân biệt và DP mặt nạ. Xử lý riêng $k=1$ bằng độ dài đối xứng lớn nhất theo hai tính chẵn/lẻ. Bảng vị trí dùng `uint16_t` để tiết kiệm bộ nhớ.
- `solution.md`: ba lời giải theo subtask, từ một đoạn đối xứng, DP theo vị trí và mặt nạ, tới DP chỉ giữ vị trí kết thúc sớm nhất.
- `tests/oracle.cpp`: mở rộng từ các tâm để liệt kê đoạn đối xứng, rồi dùng DP theo số lần đã chọn của từng độ dài, xét đoạn được chọn cuối cùng. Không dùng Manacher hoặc DP mặt nạ tiến của lời giải mẫu. Xâu toàn một ký tự và xâu luân phiên hai ký tự được đối chiếu bằng công thức trực tiếp.
- `verifier.cpp`: kiểm tra xâu chữ thường, $T$, $k$, số lượng trường trên từng dòng và tính dương của mọi độ dài, bao gồm token có nhiều chữ số.
- `checker.cpp`: kiểm tra đúng đủ $T$ câu trả lời `YES`/`NO`, cho phép khác khoảng trắng và loại dữ liệu thừa.
- `gen/`: ba bộ sinh theo subtask, seed cố định. Cấu hình upload dựa trên DAYNEN, thêm tổng điểm bài bằng 100.

Lời giải mẫu đọc/ghi `PALINCUT.INP`/`PALINCUT.OUT` khi có tệp đầu vào trong thư mục chạy; nếu không, dùng nhập/xuất chuẩn.

## Điểm từng test

Cấu hình dùng trực tiếp `[[tests]].points`, không dùng manifest `cases` hoặc nhóm chấm tất cả/không được điểm:

| Nhóm | Số test | Trọng số/test | Tổng trọng số | Tỉ lệ |
| --- | ---: | ---: | ---: | ---: |
| `example` | 2 | 0 | 0 | 0% |
| `sub1` | 10 | 1 | 10 | 25% |
| `sub2` | 10 | 1 | 10 | 25% |
| `sub3` | 20 | 1 | 20 | 50% |
| Tổng | 42 | | 40 | 100% |

`[upload].points = 100` đặt thang điểm bài. Tổng trọng số testcase bằng 40; mỗi test được tính điểm độc lập, ba nhóm đóng góp lần lượt 25, 25, 50 điểm khi đạt toàn bộ nhóm.

Mỗi test `sub1` chỉ có yêu cầu $k=1$. Mỗi test `sub2` có xâu không quá 200, tối đa ba yêu cầu và ít nhất một yêu cầu $k>1$. Mỗi test `sub3` nằm ngoài hai nhóm trước: có ít nhất một yêu cầu $k>1$, và xâu dài hơn 200 hoặc số yêu cầu lớn hơn ba.

Chương trình kiểm tra dựng cấu hình bằng `ProblemUpload`, xác nhận điểm từng test, tổng trọng số, tỉ lệ và ràng buộc của mỗi nhóm. Bước này không gửi request lên máy chủ. Không dùng `--testcase-points` khi upload vì tùy chọn đó ghi đè trọng số đã chia.

## Dữ liệu chính thức

Có 42 test, trong đó 20 test toàn bộ giới hạn đều có $T=200$; phần lớn có $n=10000$. Các trường hợp trọng tâm:

- Xâu một ký tự, ký tự khác nhau hoàn toàn, xâu toàn một chữ, xâu luân phiên và xâu nhiều khối đồng nhất.
- Đối xứng chẵn/lẻ, xâu đối xứng toàn bộ, đối xứng dài ở giữa và các tâm bị chặn gần biên.
- Yêu cầu đơn, nhiều độ dài trùng nhau, 13 độ dài phân biệt, tổng bằng đúng $n$ hoặc lớn hơn $n$ một đơn vị.
- Các đoạn đứng sát nhau, có khoảng trống giữa chúng, kết thúc trước cuối xâu hoặc cần đổi thứ tự độ dài mới chọn được.
- Có nhiều đoạn đối xứng phù hợp từng độ dài nhưng chúng chồng nhau; một đoạn không được dùng lại cho hai yêu cầu.
- Token độ dài rất lớn và token có các số 0 ở đầu, vẫn là số nguyên dương.
- Các chuỗi có điều kiện trực tiếp để xác nhận đáp án: trên xâu toàn một chữ, đáp án là tổng độ dài không vượt $n$; trên xâu luân phiên hai chữ khác nhau, còn cần tất cả độ dài đều lẻ.
- Test `sub3_19` có 13 đoạn đối xứng được chủ động ghép vào xâu và các yêu cầu hoán vị độ dài của chúng, bảo đảm có các đáp án `YES` đã biết.

`sub3_17` kiểm tra bộ nhớ tiền xử lý: $n=10000$, 200 yêu cầu và **1990 độ dài phân biệt** cần lập bảng. Các bảng 16 bit dùng khoảng 39,8 MB, trong khi bảng 32 bit sẽ cần khoảng 79,6 MB riêng cho phần này. Chương trình kiểm tra xác nhận đúng số độ dài, không chỉ tin kích thước đầu vào.

`hash.json` có 84 mục cho 42 đầu vào và 42 đáp án. Các ví dụ trong đề được đối chiếu nguyên văn với các tệp mẫu.

## Dữ liệu nhỏ và kiểm tra bổ sung

Có 438 bộ dữ liệu nhỏ: mọi xâu nhị phân dài từ 1 tới 7, với các đa tập độ dài cho tối đa bốn đoạn; 180 bộ ngẫu nhiên tới 35 ký tự; và bốn bộ đặc biệt về số lần lặp độ dài, đoạn chồng nhau, dãy con không liên tiếp, số có nhiều chữ số.

Python tính độc lập bằng DP boolean theo vị trí và mặt nạ, kiểm tra đoạn đối xứng bằng cách đảo trực tiếp chuỗi con. Cả lời giải mẫu và oracle phải khớp kết quả này.

Có thêm 60 phép kiểm tra tính bất biến khi hoán vị các độ dài yêu cầu hoặc đảo ngược xâu. Sáu cách làm sai bị các ví dụ nguồn loại: đặt theo thứ tự đầu vào, sắp độ dài tăng rồi tham lam, sắp giảm rồi tham lam, bỏ qua điều kiện không giao nhau, bỏ các yêu cầu độ dài trùng và ép dùng hết xâu.

## Chạy lại

Từ thư mục gốc dự án:

```sh
python3 dtqg/dtpalincut/tests/check.py
```

Sau khi chủ động sửa bộ sinh hoặc dữ liệu và cần cập nhật hash:

```sh
python3 dtqg/dtpalincut/tests/check.py --update-hashes
```

Quy trình biên dịch, sinh dữ liệu, chạy verifier, tạo đáp án, chạy checker, kiểm tra thời gian lời giải mẫu, đối chiếu oracle và các cách tính trực tiếp. Nó còn xác nhận tính tái lập của mọi seed, cấu trúc đề, lời giải không chứa nội dung kiểm thử, chế độ tệp vào/ra, điểm và toàn bộ hash. Không xuất HTML.

## Kết quả

Đã đạt toàn bộ 42 test chính thức, 438 bộ nhỏ, 60 phép kiểm tra tính bất biến, ba phép kiểm tra chế độ tệp, 19 đầu vào sai và 33 phép thử checker. Sáu cách làm sai đều bị loại. Verifier chấp nhận nhiều dấu cách giữa các số, độ dài có số 0 ở đầu và độ dài rất lớn.

Cấu hình điểm đạt chính xác 25%–25%–50%; toàn bộ 84 mục hash đã được đối chiếu. Thời gian lớn nhất của một lần chạy lời giải mẫu trong lượt đo hiện tại khoảng 0,036 giây, dưới giới hạn upload 1 giây; thời gian phụ thuộc máy chạy.
