# Bộ 20 test cho ctdlmap012

Có 8 test thuộc subtask 1 (N ≤ 100) và 12 test thuộc subtask 2 (N > 100), tương ứng tỷ lệ 40%/60% trong đề. Input nằm trong `in/`, đáp án sinh từ code có sẵn `sol/correct.cpp` nằm trong `out/`. Mỗi test được sinh xác định theo seed; `hash.json` lưu SHA-256 của cả 40 tệp.

| Test | N | Dữ liệu / mục tiêu |
| --- | ---: | --- |
| small_00 | 5 | Ví dụ trong đề, đáp án 2 |
| small_01 | 4 | Bốn số 0, đáp án 1 |
| small_02 | 4 | `1 2 3 2`: hai cặp đan xen có tổng bằng nhau nhưng không có a < b < c < d, đáp án 0 |
| small_03 | 4 | `10^9 -10^9 -10^9 10^9`, đáp án 1 |
| small_04 | 7 | Tất cả bằng 10^9, đếm theo vị trí, đáp án 35 |
| small_05 | 100 | Tăng nghiêm ngặt, đáp án 0; bắt lỗi bỏ điều kiện thứ tự |
| small_06 | 100 | Ngẫu nhiên trong [-3, 3], nhiều giá trị và tổng trùng nhau |
| small_07 | 100 | Ngẫu nhiên trong [-10^9, 10^9], cài một phương án ở hai đầu |
| random_00 | 101 | Tất cả bằng 0, sát ranh giới subtask, đáp án C(101,4) |
| random_01 | 1000 | Tất cả bằng 10^9, đáp án 41417124750, vượt 32 bit |
| random_02 | 1000 | Tất cả bằng -10^9, đáp án 41417124750 |
| random_03 | 1000 | Tăng nghiêm ngặt, đáp án 0 |
| random_04 | 1000 | Giảm nghiêm ngặt, đáp án 0 |
| random_05 | 1000 | 500 số -10^9 rồi 500 số 10^9, đáp án 2·C(500,4) |
| random_06 | 1000 | Xen kẽ -10^9 và 10^9, nhiều tổng 0 |
| random_07 | 1000 | Lặp chu kỳ -10^9, -10^9+1, 0, 10^9-1, 10^9 |
| random_08 | 1000 | Ngẫu nhiên trong [-5, 5], nhiều phương án |
| random_09 | 1000 | Ngẫu nhiên trên toàn miền giá trị, nhiều tổng khác nhau |
| random_10 | 1000 | Hai nửa có cùng đa tập giá trị, nửa sau đảo ngẫu nhiên |
| random_11 | 1000 | Ngẫu nhiên trong [10^9-1000, 10^9], tổng lớn và có trùng lặp |

## Sinh và kiểm tra, bỏ qua HTML

Chạy từ thư mục gốc dự án:

```sh
python3 - <<'PY'
from pathlib import Path
from problem import Problem
root = Path.cwd()
p = Problem(root, root / 'custom/ctdlmap012')
p.health_check()
p.generate_params_h()
p.compile_correct()
p.compile_gens()
p.compile_verifier()
p.compile_checker()
p.make_inputs()
p.verify_inputs()
p.make_outputs(True)
p.judge(p.get_correct_filename(), p.config['solutions'][0])
assert p.check_all_solutions_used()
p.assert_hashes()
p.zip()
PY
```

Sau khi chủ động đổi generator hoặc lời giải, cập nhật hash bằng `p.ignore_warning = True; p.write_hashes()` trước bước đối chiếu. Không dùng `generate.py --dev` hoặc `--test` vì các chế độ này tự xuất HTML.

## Kiểm chứng bộ test

- Verifier kiểm tra đầy đủ giới hạn N, A_i, số lượng phần tử và định dạng input.
- Code đúng được chấm bằng checker với giới hạn 2 giây trên cả 20 test.
- Tất cả 20 đáp án được đối chiếu bằng cách độc lập: liệt kê mọi cặp, nhóm theo tổng, rồi đếm các cặp có chỉ số cuối nhỏ hơn chỉ số đầu của cặp còn lại.
- Các test N ≤ 100 được kiểm tra thêm bằng duyệt mọi bộ bốn chỉ số. Code đúng và cách tính độc lập cũng được đối chiếu với duyệt vét cạn trên 81 mảng độ dài 4 thuộc {-1,0,1} và 400 mảng ngẫu nhiên độ dài 4–12.
- Checker được kiểm tra với đáp án đúng, sai, rỗng, dư token, token không hợp lệ và khoảng trắng. Verifier được kiểm tra với N ngoài giới hạn, A_i ngoài giới hạn, thiếu hoặc dư phần tử.
- Sinh lại toàn bộ input/output và đối chiếu đủ 40 hash để xác nhận khả năng tái tạo.
