# Test hồi quy DPSTR230

`gen/regression_00.in` được thêm vào danh sách test chính thức:

```text
2 2
ab
ab
-3 5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```

Hai xâu có đoạn chung `ab` dài 2, với điểm chữ `a` là -3 và chữ `b` là 5. Phương án tối ưu chỉ lấy `b`, đáp án **5**. Lấy cả `ab` chỉ được 2 điểm.

Test bắt lỗi luôn cộng điểm vào đoạn khớp trước đó mà không cho phép bắt đầu lại. Bộ kiểm tra mô phỏng phép chuyển sai này, xác nhận nó trả 2 và yêu cầu checker từ chối đáp án đó.

Chạy từ thư mục gốc:

```sh
python3 custom/dpstr230/tests/check.py
```

Bài có 35 cặp test. Lời giải, oracle độc lập, vét cạn, verifier, checker và mã băm được kiểm tra theo quy trình chung, không xuất HTML.
