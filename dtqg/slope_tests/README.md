# Bộ luyện slope trick

| Thứ tự | Bài | Trọng tâm | Lời giải mẫu | Giới hạn thời gian |
| --- | --- | --- | --- | --- |
| 1 | DIEUPHOI | Đổi tọa độ, min tiền tố | Một max-heap, $O(N\log N)$ | 3 giây |
| 2 | BAMTIN | Min trên cửa sổ, hai lazy độc lập | Hai heap, $O(N\log N)$ | 4 giây |
| 3 | ONDINH | Trọng số, chặn độ dốc, tách khối lượng | Treap tăng cường, kỳ vọng $O(N\log N)$ | 5 giây |
| 4 | CANMANG | DP hàm trên cây, gộp nhỏ vào lớn | Hai heap cho mỗi hàm, $O(N\log^2N)$ | 6 giây |

Các thư mục bài nằm cạnh thư mục này trong `dtqg/`. Mỗi bài có `task.md`, `solution.md`, lời giải C++17, checker, verifier, bộ sinh, ba ví dụ và `hash.json`. Các lời giải BAMTIN/CANMANG có header cục bộ `sol/slope.h`, để thư mục bài chứa đủ mã nguồn lời giải của chính nó.

## Chạy kiểm tra

Từ thư mục gốc dự án:

```sh
python3 dtqg/slope_tests/check.py
```

Sau khi chủ động sửa dữ liệu, sinh lại và cập nhật hash:

```sh
python3 dtqg/slope_tests/check.py --update-hashes
```

Có thể chạy từng bài:

```sh
python3 dtqg/dieuphoi/tests/check.py
python3 dtqg/bamtin/tests/check.py
python3 dtqg/ondinh/tests/check.py
python3 dtqg/canmang/tests/check.py
```

Quy trình gọi riêng các bước biên dịch, sinh, xác minh dữ liệu, tạo đáp án, chấm lại và đối chiếu hash của dự án; không xuất HTML và không cần thư viện bổ sung. `CXX` và `CXXFLAGS` có thể ghi đè trình biên dịch và cờ biên dịch. Mặc định dùng C++17 với cảnh báo là lỗi.

## Bộ test

Mỗi bài có 45 test chính thức:

- 3 ví dụ.
- 12 test biên.
- 10 test nhỏ.
- 8 test vừa/ngẫu nhiên.
- 12 test lớn; toàn bộ nhóm này có $N=200000$ với ba bài đầu, $N=100000$ với CANMANG.

Các trường hợp quan trọng:

- **DIEUPHOI:** tọa độ âm, không được đổi thứ tự xe, khoảng cách an toàn khác 0, dãy đã hợp lệ, mục tiêu đổi biến giảm mạnh, nhiều điểm trùng, tổng chiều dài vượt 32 bit và mẫu phi đơn điệu sau đổi biến.
- **BAMTIN:** vùng tín hiệu là đoạn hoặc một điểm, đứng yên, chỉ đi trái/phải, giới hạn bất đối xứng, vị trí đầu tự do, đoạn giao nhau, lazy tích lũy lớn và miền tọa độ nhỏ để kiểm chứng trực tiếp cả ở $N$ lớn.
- **ONDINH:** hệ số tới $10^6$, nhiều giá trị trùng, cắt một phần khối lượng của nút, hệ số chuyển đổi nhỏ/lớn luân phiên, nhiều điểm nhỏ rồi thêm các quan sát nặng, tổng chi phí vượt 32 bit. Cấu trúc treap tách cả nhóm theo khối lượng; không nhân bản trọng số và không di chuyển từng điểm khi chặn độ dốc.
- **CANMANG:** cây đường thẳng, sao, nhị phân, chổi, lược, nhiều nhánh dài và cây ngẫu nhiên; đảo nhãn đỉnh, xáo cạnh; $D=0$, $D$ lớn, các cây con có lazy khác nhau, mọi mục tiêu đã khả thi và các trường hợp cần nhiều lần gộp hàm.

## Oracle độc lập

**DIEUPHOI:** PAVA theo các khối trung vị, dùng hai heap cho từng khối và gộp khối khi thứ tự trung vị bị vi phạm. Với $N\le3000$, oracle tự so sánh thêm với DP nén tọa độ $O(N^2)$. Cách này khác quy tắc cập nhật một heap của lời giải mẫu.

**BAMTIN:** treap lưu toàn bộ các bước nhảy của đạo hàm dưới dạng $B-Sx+\sum w(x-a)_+$. Min trên cửa sổ được tính bằng tách khối lượng ở đạo hàm 0 và dịch cả hai cây. Với miền nhỏ, oracle còn tự so sánh với DP trên từng tọa độ và deque. Các tổng trung gian dùng số nguyên 128 bit, vì lazy lớn có thể làm hệ số chặn và moment vượt 64 bit dù đáp án vẫn nhỏ.

**ONDINH:** quét các ngưỡng giá trị để đưa bài toán về gán nhãn nhị phân trên đường thẳng. Một segment tree lưu tích ma trận min-plus $2\times2$, mỗi lần qua một mức đo chỉ cập nhật một vị trí. Cách này không dùng slope trick hoặc treap. Với miền nhỏ, oracle tự so sánh thêm với DP trực tiếp dùng hai lượt quét cho chi phí chuyển trạng thái.

**CANMANG:** dùng treap bước nhảy đạo hàm để dịch và cộng hàm, thay cho hai heap và phép thêm hàm một phía của lời giải mẫu. Miền nhỏ được kiểm tra thêm bằng DP cây trên mọi tọa độ, lấy min cửa sổ bằng deque. Duyệt cây không đệ quy theo chiều cao.

## Kiểm tra bổ sung

- Đối chiếu tất cả test chính thức với oracle, không bỏ qua các test lớn.
- Chạy lại lời giải mẫu với giới hạn thời gian trong `info.toml`.
- Kiểm tra mọi dữ liệu bằng verifier; thử thêm dữ liệu sai giới hạn, thiếu/thừa dòng, đoạn đảo đầu, hệ số không hợp lệ và đồ thị không phải cây.
- Thử checker với đáp án đúng có khoảng trắng, đáp án sai, rỗng, thừa số, số thực, ký tự lạ và số vượt 64 bit.
- Kiểm tra tính xác định của seed đầu mỗi nhóm sinh và kích thước mọi test lớn.
- Đối chiếu định dạng đề với mẫu knapsack, toàn bộ ví dụ và phần giải thích ở cuối; không sinh HTML.

## Kết quả kiểm tra bộ bài

| Bài | Test chính thức | Đối chiếu nhỏ | Đầu vào sai bị từ chối | Kiểm tra checker | Kết quả |
| --- | ---: | ---: | ---: | ---: | --- |
| DIEUPHOI | 45 | 490 | 11 | 27 | Đạt |
| BAMTIN | 45 | 536 | 10 | 27 | Đạt |
| ONDINH | 45 | 753 | 11 | 27 | Đạt |
| CANMANG | 45 | 1058 | 13 | 27 | Đạt |
| Tổng | 180 | 2837 | 45 | 108 | Đạt |

Tất cả ví dụ khớp đề; lời giải mẫu qua giới hạn thời gian; `hash.json` được tạo và đối chiếu. Bảng ghi nhận lần kiểm tra bộ bài hiện tại; chạy lại quy trình sau khi sửa nguồn hoặc dữ liệu.
