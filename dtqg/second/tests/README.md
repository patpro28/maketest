# Kiểm thử SECOND

## Test bắt việc nhảy lặp lại khi tìm phần tử lớn hơn thứ hai

`gen/jump.cpp` sinh hai test chính thức với $N=200000$, $m=N/2=100000$:

- `jump_00.in`: hoán vị $[2m-1,2m-2,\ldots,m,2m,1,2,\ldots,m-1]$.
- `jump_01.in`: đảo ngược hoán vị trên, gây cùng vấn đề khi tìm về bên trái.

Trong test đầu, $m$ phần tử đầu đều có phần tử lớn hơn đầu tiên tại vị trí $m+1$. Khi tìm phần tử lớn hơn thứ hai, thuật toán bắt đầu ở vị trí $m+2$ và nhảy theo `r[]` qua toàn bộ đuôi tăng $[1,2,\ldots,m-1]$. Mỗi lần tìm có $m-1$ bước nhảy, tổng cộng $m(m-1)=9\,999\,900\,000$ bước chỉ cho phần tìm bên phải. Test đảo ngược buộc số bước tương tự ở bên trái.

Hai test là hoán vị hợp lệ, được verifier kiểm tra. Đáp án được tính bằng lời giải hai stack $O(N)$ và đối chiếu với oracle dùng tập có thứ tự $O(N\log N)$. Hai test có cùng đáp án vì phép đảo dãy bảo toàn tập giá trị của các đoạn con tương ứng.

## Chạy lại

```sh
python3 dtqg/second/tests/check.py --check-slow
```

Chương trình kiểm tra toàn bộ 47 test chính thức, 1123 trường hợp nhỏ, 9 trường hợp dữ liệu sai và 27 phép thử checker; đồng thời đối chiếu 94 mục trong `hash.json`.

Bản `dtqg/stack_tests/slow_second.cpp` giữ nguyên thuật toán nhảy của đoạn code cần bắt. Trước khi đo, bản này được kiểm tra tính đúng trên 29 trường hợp: 3 ví dụ, 20 test nhỏ và 6 test cấu trúc đặc biệt với $N=8,10,1000$ theo cả hai hướng. Sau đó mỗi test `jump` phải khiến bản này vượt giới hạn 3 giây. Kết quả thời gian phụ thuộc máy chạy.

Khi thay đổi bộ sinh và cần cập nhật hash:

```sh
python3 dtqg/second/tests/check.py --update-hashes --check-slow
```

## Kết quả chạy

Toàn bộ 47 test chính thức, 1123 trường hợp nhỏ, kiểm tra verifier, checker và hash đều đạt. Bản nhảy liên kết khớp 29 trường hợp kiểm tra tính đúng và vượt 3 giây trên cả hai test `jump`.

| Test | Lời giải hai stack | Bản nhảy liên kết |
| --- | ---: | ---: |
| `jump_00.in` | 0,168 giây | Vượt 3 giây |
| `jump_01.in` | 0,154 giây | Vượt 3 giây |

Thời gian trên được đo ở máy kiểm tra hiện tại. Cả hai đáp án đều bằng `2666636666899999`.

Quy trình kiểm tra đầy đủ của bốn bài được mô tả ở [README dùng chung](../../stack_tests/README.md).
