# Các test bắt quá thời gian của Dijkstra theo chặng cuối

Các phiên bản code được hỏi dùng mỗi chặng làm một trạng thái. Mô hình cho đáp án đúng, nhưng mỗi lần chốt một chặng tới thành phố $u$, code lại duyệt toàn bộ chặng đi ra khỏi $u$.

Tổng số lần xét chuyển tiếp là

$$\sum_u \deg^-(u)\deg^+(u),$$

có thể đạt $\Theta(M^2)$. Phần này chưa tính các thao tác trên hàng đợi ưu tiên. Không có phản ví dụ sai đáp án cho mô hình này dưới ràng buộc của đề; các test ở đây bắt giới hạn thời gian.

| Tệp | Cấu trúc | Đáp án | Số lượt chạy thân vòng lặp chuyển tiếp |
| --- | --- | ---: | ---: |
| `different_lines.in` | 100000 chặng từ 1 tới 2 và 100000 chặng từ 2 tới 3; mã tuyến hai phía rời nhau | 1000000002 | 10000000000 |
| `same_line.in` | Cùng cấu trúc trên, mọi chặng cùng tuyến 1 | 2 | 10000000000 |
| `self_loops.in` | 199999 chặng tự khép ở 1 và một chặng từ 1 tới đích 2; mọi thời gian bằng 1 | 1 | 39999800000 |

Ba test trên đều có $M=200000$, hợp lệ theo đề. Chặng trùng và chặng tự khép đều được phép. Các tệp `.out` chứa đáp án tương ứng. Chúng cùng test self-loop tại trung gian đã được đưa vào bộ sinh chính thức `gen/stress.cpp`, khai báo trong `info.toml` và cập nhật vào `hash.json`:

| Phản ví dụ | Test chính thức |
| --- | --- |
| `different_lines.in` | `stress_00.in` |
| `same_line.in` | `stress_01.in` |
| `self_loops.in` | `stress_02.in` |
| `hub_self_loops.in` | `stress_05.in` |

Quy trình kiểm tra chính thức sinh lại cả bốn test và đối chiếu từng byte với các bản lưu ở đây.

Tạo lại dữ liệu từ thư mục gốc dự án:

```sh
python3 custom/doituyen/tests/counterexamples/generate.py
```

Với test đầu, bất kỳ hành trình nào cũng phải đi 1 → 2 → 3 và đổi tuyến tại 2, nên tốn $1+10^9+1$. Ở test thứ hai không đổi tuyến, nên tốn $2$. Ở test thứ ba đi trực tiếp từ 1 đến 2 tốn $1$; không hành trình nào có chi phí nhỏ hơn vì thời gian mỗi chặng là số nguyên dương.

Với bản code nguyên thủy, trong test thứ ba các trạng thái chặng tự khép đều có khoảng cách ban đầu là 1. Chặng tới đích có chỉ số lớn nhất, nên bị lấy ra sau toàn bộ các chặng tự khép khi dùng `pair<distance, edge_id>`. Chỉ thêm lệnh dừng khi lấy được đích vẫn không tránh được số phép duyệt bậc hai trên test này.

## Giới hạn của test self-loop và bộ test bổ sung

Bản code mới lọc `edge[i].v != s` ngay khi đọc cạnh, nên loại hết các self-loop tại nguồn của `stress_02`. Vì vậy test này không bắt được bản mới và không thể dùng để kết luận thời gian chạy của bản mới.

Việc loại self-loop là hợp lệ với đề này. Nếu một hành trình đi vào thành phố bằng tuyến $a$, đi self-loop tuyến $b$ rồi đi tiếp bằng tuyến $c$, bỏ self-loop sẽ bỏ một thời gian di chuyển dương, còn số lần đổi tuyến không tăng vì

$$[a\ne c]\le[a\ne b]+[b\ne c].$$

Self-loop ở đầu hoặc cuối hành trình cũng có thể bỏ. Bộ test chính vì vậy cần kiểm tra chuyển tiếp bậc hai trên các cạnh không thể loại theo cách này.

Đã thêm hai test chính thức sau vào `gen/stress.cpp` và `info.toml`:

| Test | Cấu trúc | Đáp án |
| --- | --- | ---: |
| `stress_03` | $S\to A_i\to H\to B_j$, $K=66666$ nhánh vào và ra; hai cạnh đầu dài 1, cạnh ra dài 100 | 1000000102 |
| `stress_04` | Cùng dạng, xáo nhãn đỉnh và thứ tự cạnh; cạnh $S\to A_i$ dài $i+1$, cạnh $A_i\to H$ dài 1, cạnh ra dài $10^9$ | 2000000002 |

Cả hai có $N=133334$, $M=199998$. Chọn $T=B_0$, phí đổi tuyến tại $H$ là $10^9$, tại các đỉnh khác là 0. Hai cạnh đi qua $A_i$ cùng tuyến $i+1$; các cạnh ra từ $H$ dùng các tuyến $K+1,\ldots,2K$, khác toàn bộ tuyến vào.

Không có self-loop, cạnh trùng, cạnh đi vào $S$ hay cạnh đi ra từ $T$. Do đó những phép lọc trong code mới không loại được cạnh nào. Tại $H$, code vẫn phải xét $K^2=4444355556$ chuyển tiếp. Mọi trạng thái đi vào $H$ đều có khoảng cách nhỏ hơn trạng thái tới đích, nên dừng sớm khi lấy đích cũng không tránh được bước này. Đáp án còn được đối chiếu bằng DP trên DAG và các giá trị tính trực tiếp ở bảng trên.

## Test self-loop tại trung gian: stress_05

`hub_self_loops.in` có 3 thành phố, nguồn 1, đích 3 và 200000 chặng:

- 99999 chặng từ 1 tới 2, thời gian 1, dùng các tuyến 1 đến 99999.
- 100000 self-loop tại thành phố 2, thời gian 1, dùng các tuyến 100000 đến 199999.
- Một chặng từ 2 tới 3, tuyến $10^9$, thời gian $10^9$.
- Phí đổi tuyến tại 2 là $10^9$, hai thành phố còn lại là 0.

Đáp án là $1+10^9+10^9=2000000001$. Điều kiện lọc cạnh về nguồn hoặc cạnh ra khỏi đích không loại được cạnh nào. Bản code mới không đưa các self-loop vào hàng đợi, nhưng vẫn duyệt qua chúng trong danh sách `matout[2]` cho mỗi trong 99999 trạng thái đi vào 2. Tổng số lượt duyệt ở đây là $99999\cdot100001=9999999999$, dù phần lớn kết thúc ngay bằng `continue`.

Mọi trạng thái đi vào 2 có khoảng cách 1, nhỏ hơn khoảng cách tới đích, nên thêm dừng sớm cũng không tránh được bước duyệt này. Xóa self-loop ngay khi đọc dữ liệu là tối ưu hợp lệ và vượt được test này; `stress_03`–`stress_04` kiểm tra tiếp trường hợp không có self-loop để xóa.

## Kết quả chạy kiểm chứng

Code nguyên thủy được gửi đã được biên dịch bằng GCC với C++17 và tối ưu `-O2`. Code khớp lời giải mẫu trên 762 trường hợp nhỏ đối chiếu. Cả ba test cũ đều hợp lệ theo verifier, đáp án đã khớp lời giải mẫu và qua checker. Bảng này ghi nhận bản nguyên thủy, không phải bản mới có lọc cạnh:

| Test | Đáp án | Lời giải mẫu | Code được hỏi |
| --- | ---: | ---: | --- |
| different_lines | 1000000002 | 0.064 giây | Quá 3 giây, đã dừng |
| same_line | 2 | 0.024 giây | Quá 3 giây, đã dừng |
| self_loops | 1 | 0.054 giây | Quá 3 giây, đã dừng |

Ngưỡng đo là 3 giây theo `timelimit` cục bộ trong `info.toml`; cấu hình upload hiện đặt 1 giây. Thời gian thực tế phụ thuộc máy, nhưng số lần duyệt bậc hai không phụ thuộc cách đo. Sau khi tích hợp ba test, `hash.json` chính thức được cập nhật và đối chiếu lại bằng quy trình kiểm tra của bài.

## Kiểm chứng bản code mới

Bản mới có lọc cạnh về nguồn, cạnh ra khỏi đích và bỏ self-loop đã được đối chiếu đúng trên 762 trường hợp nhỏ. Cả hai biến thể được biên dịch C++17 với GCC `-O2`; biến thể thứ hai còn dừng khi lần đầu chốt một chặng tới đích. Kết quả trên máy hiện tại:

| Test | Bản code mới | Thêm dừng sớm ở đích | Lời giải mẫu |
| --- | --- | --- | --- |
| stress_02 | AC (0.423s) | AC (0.286s) | AC (0.440s) |
| stress_03 | TLE (>3s) | TLE (>3s) | AC (0.580s) |
| stress_04 | TLE (>3s) | TLE (>3s) | AC (0.757s) |

Bộ chính thức hiện có 51 test. Đã sinh lại toàn bộ, kiểm tra verifier/checker, đối chiếu oracle, kiểm tra giới hạn thời gian của lời giải mẫu và cập nhật `hash.json`.

## Đo stress_05 với bản code mới

Biên dịch GCC C++17 `-O2`, ngưỡng dừng 3 giây:

| Chương trình | Kết quả |
| --- | --- |
| Bản code mới | TLE (>3s) |
| Thêm dừng sớm | TLE (>3s) |
| Lời giải mẫu | AC (0.441s) |
