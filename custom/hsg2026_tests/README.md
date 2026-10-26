# Bộ luyện ba bài theo báo cáo kiến thức

Ba bài tự biên soạn, xếp từ dễ đến khó dựa trên các vùng kiến thức nổi bật trong `bao-cao.md`.

| Thứ tự | Mã bài | Trọng tâm | Thuật toán mẫu | Giới hạn thời gian |
| --- | --- | --- | --- | --- |
| 1 | TRAMTIEPTE | DP trên cây, chuyển gốc | $O(N)$ | 2 giây |
| 2 | DOITUYEN | Đồ thị trạng thái, Dijkstra | $O((N+M)\log(N+M))$ | 3 giây |
| 3 | CHIACHUYEN | DP, stack đơn điệu, segment tree với lazy propagation | $O(N\log N)$ | 3 giây |

Mỗi bài nằm trong thư mục cùng mã viết thường, có `task.md`, `solution.md`, lời giải C++17, bộ sinh, verifier, checker và `hash.json`. Đề có ba ví dụ, không chia subtask. Bài CHIACHUYEN dùng lazy propagation nên dùng mã riêng, không đưa vào dải SEG0.

## Chạy kiểm tra

Từ thư mục gốc dự án:

```sh
python3 custom/hsg2026_tests/check.py
```

Tạo lại bộ test và cập nhật hash sau khi chủ động thay đổi dữ liệu:

```sh
python3 custom/hsg2026_tests/check.py --update-hashes
```

Có thể chỉ kiểm tra một bài:

```sh
python3 custom/tramtiepte/tests/check.py
python3 custom/doituyen/tests/check.py
python3 custom/chiachuyen/tests/check.py
```

Các lệnh này gọi riêng các bước cần thiết của quy trình dự án, không xuất HTML. Dữ liệu được tạo tại `in/`, `out/` của từng bài; hash được so sánh theo chuẩn `Problem.calc_hashes()` của dự án. Không cần cài thêm thư viện.

## Nội dung kiểm tra

- Mỗi bài có 45 test: 3 ví dụ, 12 biên, 12 nhỏ, 8 vừa/ngẫu nhiên và 10 test lớn. Mọi test lớn có $N=200000$; DOITUYEN còn có $M=200000$.
- Biên dịch với C++17, bật cảnh báo và coi cảnh báo là lỗi; lời giải mẫu chạy lại với giới hạn thời gian trong `info.toml`.
- Tất cả test sinh được đều được verifier kiểm tra và đối chiếu đáp án với oracle riêng. Bộ sinh được kiểm tra tính xác định ở seed đầu của mỗi nhóm.
- TRAMTIEPTE: vét mọi vị trí trạm bằng duyệt cây trên test nhỏ/vừa; test lớn tính đóng góp từng cạnh vào các khoảng Euler bằng mảng hiệu, không dùng truy hồi chuyển gốc. Bao gồm mọi cây gán nhãn tới 5 đỉnh và thêm 200 trường hợp ngẫu nhiên.
- DOITUYEN: Dijkstra chậm với trạng thái là chặng vừa đi, thử trực tiếp mọi chặng tiếp theo. Các test lớn có cấu trúc hai chặng qua một trung tâm dùng công thức riêng theo các mã tuyến; bao gồm test có $100000$ tuyến vào và $100000$ tuyến ra để loại cách mở chuyển tiếp bậc hai. Test nhỏ bổ sung duyệt mọi tập cung có hai mã tuyến trên 2 thành phố, cùng 250 trường hợp ngẫu nhiên.
- CHIACHUYEN: DP trực tiếp xét mọi chuyến cuối cho test nhỏ/vừa và test lớn có $R\le1500$. Các test lớn còn lại dùng công thức cho trường hợp đặc biệt hoặc DP với multiset khi dãy đơn điệu. Test nhỏ bổ sung duyệt mọi dãy hai giá trị tới độ dài 5, mọi cặp $L,R$, hai phí mở chuyến, và 250 trường hợp ngẫu nhiên.
- Thử dữ liệu đầu vào sai, đáp án sai từng thành phần, thiếu/thừa dữ liệu, kiểu số sai và số quá lớn để kiểm tra verifier/checker.
- Đối chiếu cấu trúc đề với mẫu knapsack: tiêu đề, thứ tự heading, khối `text`, toàn bộ ví dụ và không có mục Subtask.

Các oracle đặc biệt cho test lớn chỉ áp dụng khi dữ liệu thỏa điều kiện được kiểm tra trong mã. Nếu xuất hiện test lớn chưa có cách kiểm chứng độc lập, chương trình dừng với lỗi thay vì bỏ qua.

## Kết quả kiểm tra khi tạo bộ bài

| Bài | Test chính thức | Đối chiếu dữ liệu nhỏ | Đầu vào sai bị từ chối | Kiểm tra checker | Kết quả |
| --- | ---: | ---: | ---: | ---: | --- |
| TRAMTIEPTE | 45 | 492 | 15 | 33 | Đạt |
| DOITUYEN | 45 | 762 | 16 | 27 | Đạt |
| CHIACHUYEN | 45 | 1654 | 12 | 27 | Đạt |
| Tổng | 135 | 2908 | 43 | 87 | Đạt |

Các lời giải mẫu đều qua giới hạn thời gian đã cấu hình; toàn bộ ví dụ khớp đề; các tệp `hash.json` đã được tạo và đối chiếu thành công. Những số liệu này ghi lại lần kiểm tra bộ bài hiện tại, không thay thế việc chạy lại sau khi sửa nguồn.
