# Kiểm thử hồi quy — DPSTR150

Chạy từ thư mục gốc dự án:

```sh
python3 custom/dpstr150/tests/check.py
```

Khi chủ động thay đổi dữ liệu test và cần cập nhật mã băm:

```sh
python3 custom/dpstr150/tests/check.py --update-hashes
```

## Lỗi kiểm tra ký tự bắt buộc chỉ trên tiền tố

Đoạn code được cung cấp tính LCS thông thường rồi cập nhật đáp án nếu `ch1[i-1] > 0`. Điều kiện này chỉ cho biết tiền tố của xâu thứ nhất chứa ký tự bắt buộc. Phương án LCS đang lưu trong `dp[i][j]` có thể đã bỏ ký tự ấy, thậm chí xâu thứ hai không chứa ký tự bắt buộc.

Đã bổ sung tám cặp test `regression_00` đến `regression_07` vào danh sách test chính thức trong `info.toml`:

| Test | Xâu A | Xâu B | Ký tự bắt buộc | Đáp án đúng | Thuật toán sai |
| --- | --- | --- | --- | --- | --- |
| regression_00 | `xa` | `a` | `x` | -1 | 1 |
| regression_01 | `xab` | `abx` | `x` | 1 | 2 |
| regression_02 | `xabc` | `abcx` | `x` | 1 | 3 |
| regression_03 | `xabb` | `abbx` | `x` | 1 | 3 |
| regression_04 | `pxabc` | `pabcx` | `x` | 2 | 4 |
| regression_05 | `xabcy` | `abcxy` | `x` | 2 | 4 |
| regression_06 | `x` + 299 chữ `a` | 299 chữ `a` + `x` | `x` | 1 | 299 |
| regression_07 | `zx` + 297 chữ `a` + `y` | `z` + 297 chữ `a` + `xy` | `x` | 3 | 299 |

Các test bao gồm trường hợp không có lời giải, ký tự bắt buộc xuất hiện ở cả hai phía nhưng bị LCS bỏ qua, ký tự lặp, tiền tố/hậu tố chung và hai xâu cùng đạt độ dài tối đa 300.

Ngoài lỗi thuật toán, code gốc còn đọc `ch1[-1]` khi `i=0`. Mô hình sai trong `tests/prefix_only_wrong.cpp` chặn riêng truy cập này và dùng các header C++ chuẩn để chạy được trên nhiều trình biên dịch. Phần DP và điều kiện cập nhật đáp án giữ nguyên. Vì vậy việc bị bắt trên cả tám test không phụ thuộc vào hành vi không xác định của truy cập mảng ngoài giới hạn.

## Kiểm tra tự động

Bộ kiểm tra dùng chung sẽ biên dịch mô hình sai và yêu cầu checker từ chối đáp án của mô hình trên **cả tám** test hồi quy. Sáu test mới có xâu ngắn được đối chiếu thêm bằng vét cạn; hai test dài có đáp án theo cấu trúc ở bảng trên, đồng thời được đối chiếu giữa lời giải C++ và Python.

DPSTR150 hiện có **40 cặp test**, gồm 32 cặp ban đầu và 8 cặp hồi quy. Quy trình vẫn kiểm tra verifier, checker, hai lời giải theo giới hạn 0,5 giây, cấu trúc đề, tính tái lập của bộ sinh và `hash.json`, không xuất HTML và không upload.
