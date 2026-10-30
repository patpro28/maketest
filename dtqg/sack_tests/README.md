# Năm bài luyện Sack / DSU on tree

## Thứ tự luyện tập

| Thứ tự | Bài | Trọng tâm | Thời gian lời giải mẫu |
| --- | --- | --- | --- |
| 1 | [DTBASAC — Bộ ba khác màu](../dtbasac/task.md) | Giữ/xóa dữ liệu cây con; duy trì các tổng lũy thừa tần suất | $O(N\log N)$ |
| 2 | [DTTOPMAU — Những màu phổ biến nhất](../dttopmau/task.md) | Thống kê theo tần suất, hai Fenwick và truy vấn thứ hạng | $O(N\log^2N+Q\log N)$ |
| 3 | [DTHENGAP — Khoảng cách tại điểm gặp](../dthengap/task.md) | Đếm cặp có LCA chính xác; truy vấn trước khi thêm một nhánh | $O(N\log N)$ |
| 4 | [DTCANBANG — Điểm tập kết tối ưu](../dtcanbang/task.md) | Trung vị có trọng số, tìm thứ hạng và tổng mômen trên Fenwick | $O(N\log^2N)$ |
| 5 | [DTMATKHAU — Đường đi có thể đối xứng](../dtmatkhau/task.md) | LCA, mặt nạ chẵn/lẻ và giới hạn độ sâu; Fenwick nén riêng theo mặt nạ | $O(11N\log^2N)$ |

Mỗi bài có đề `task.md` với ba ví dụ, lời giải `solution.md`, code C++17, bộ sinh, verifier, checker và `hash.json`. Bộ này không chia subtask. Tài liệu kiểm thử được lưu tại đây, tách khỏi các lời giải.

Mã và tên thư mục của năm bài đều có tiền tố `dt`. Mục `[upload]` trong mỗi `info.toml` được sao chép từ DAYNEN: giới hạn upload $1$ giây, nhóm `04`, lớp `E`, loại `doituyen`, cùng danh sách ngôn ngữ và `partial = true`.

Kỹ thuật nền có thể đọc tại [Sack / DSU on tree của Arpa](https://codeforces.com/blog/entry/44351). Các đề trong bộ này được biên soạn theo năm ý tưởng đã thống nhất trong cuộc trò chuyện.

## Những bất biến cần hiểu

Các lời giải mẫu dùng cùng khung Sack trong `sol/tree.h`, có một bản riêng trong từng thư mục bài để mỗi gói tự chứa đủ mã nguồn:

1. Con nhẹ được xử lý, lấy đáp án rồi dọn sạch.
2. Con nặng được xử lý sau các con nhẹ và được giữ dữ liệu.
3. Khi bắt đầu bước gộp tại cha, cấu trúc chỉ chứa cây con của con nặng.
4. Sau khi thêm các con nhẹ và đỉnh cha, cấu trúc chứa đúng toàn bộ cây con cha.
5. Pha không giữ kết quả phải xóa đúng dữ liệu đã thêm, để lời gọi khác không bị lẫn đỉnh.

Với DTHENGAP và DTMATKHAU, phải truy vấn xong **toàn bộ một nhánh nhỏ** rồi mới đưa nhánh đó vào cấu trúc. Thêm xen kẽ từng đỉnh sẽ đếm nhầm cặp nằm trong cùng nhánh. Đỉnh cha được truy vấn trước khi thêm, để tính các cặp có một đầu mút là cha mà không tạo cặp trùng hai đầu mút.

Khung duyệt cây và các pha Sack được mô phỏng bằng ngăn xếp sự kiện, nên các lời giải mẫu xử lý được cây dây dài tới giới hạn mà không phụ thuộc độ sâu ngăn xếp đệ quy.

## Bộ dữ liệu

Mỗi bài có 30 test chính thức: 3 ví dụ, 7 trường hợp biên, 6 test nhỏ, 6 test ngẫu nhiên và 8 test lớn. Tổng cộng 150 test. Bộ sinh nằm trong `gen/`; dữ liệu đầu vào và đáp án được tạo trong `in/` và `out/`. Mỗi bài có 60 mục trong `hash.json`.

Các test lớn gồm cây dây, cây sao, cây cân bằng, cây ngẫu nhiên, cây chổi, cây lược, nhiều nhánh dài và cây cân bằng đổi nhãn. Bộ sinh đảo hướng mô tả cạnh và xáo trộn thứ tự cạnh, đồng thời giữ gốc bằng đỉnh $1$.

- **DTBASAC:** màu trùng hoàn toàn, toàn bộ khác nhau, chỉ ba màu, màu rất lớn và nhiều nhóm tần suất chênh lệch. Trường hợp cây dây khác màu được đối chiếu thêm với $\binom{|subtree(u)|}{3}$ cho mọi đỉnh.
- **DTTOPMAU:** $k=0$, $k=1$, $k$ lớn hơn số màu xuất hiện, nhiều màu đồng hạng và nhiều truy vấn tại gốc. Test lớn đạt $N=Q=200000$. Cây dây khác màu có đáp án trực tiếp $\min(k,N-u+1)$.
- **DTHENGAP:** ngưỡng bằng $0$, khoảng cách không thể đạt tới, cặp có đầu mút là LCA, cặp cùng nhánh và cặp khác nhánh. Cây sao tại gốc có thể đạt $\binom{N-1}{2}$ cặp, vượt $32$ bit.
- **DTCANBANG:** tọa độ bằng nhau, tọa độ ở hai đầu miền giá trị, trọng số lớn, nhiều trung vị tối ưu và trường hợp trung vị thường khác trung vị có trọng số. Trên cây dây có tọa độ liên tiếp và trọng số $1$, chi phí cây con dài $s$ bằng $\lfloor s^2/4\rfloor$.
- **DTMATKHAU:** đủ 10 chữ, chữ `j`, nhiều đỉnh cùng mặt nạ và độ sâu, ngưỡng bằng $0$, ngưỡng cắt đúng biên độ dài và ngưỡng lớn bao hết cây. Có đường được hoán vị thành đối xứng dù thứ tự ban đầu không đối xứng. Cây sao toàn chữ `a` và ngưỡng gốc bằng $2$ có $\binom N2$ cặp tại gốc, vượt $32$ bit khi $N=100000$.

Các bài DTBASAC, DTTOPMAU, DTHENGAP, DTCANBANG có test lớn đạt $N=200000$; DTMATKHAU đạt $N=100000$.

## Đối chiếu độc lập

`oracle.cpp` dùng các cách triển khai khác với cấu trúc Sack toàn cục của lời giải mẫu:

- **DTBASAC:** gộp các `map` tần suất từ dưới lên, tái sử dụng bảng lớn. Duy trì trực tiếp số cặp khác màu và số bộ ba khác màu bằng cách thêm từng nhóm màu; không dùng công thức ba tổng lũy thừa.
- **DTTOPMAU:** chuyển cây con thành đoạn Euler và xử lý bằng Mo. Tần suất được quản lý bằng mảng và chia khối trên miền tần suất; không dùng Sack hoặc Fenwick.
- **DTHENGAP:** DP từ dưới lên, mỗi cây con giữ `map` số đỉnh theo độ sâu. Gộp các nhóm độ sâu bằng số lượng, thay vì duyệt lại từng đỉnh trong một cấu trúc toàn cục.
- **DTCANBANG:** cây phân đoạn có phiên bản theo tiền tố Euler, lưu tổng trọng số và tổng tích tọa độ. Dữ liệu của một cây con được lấy bằng hiệu hai phiên bản. Không dùng Sack hoặc Fenwick.
- **DTMATKHAU:** mỗi cây con giữ một tập dữ liệu riêng; gộp nhỏ vào lớn từ dưới lên. Mỗi mặt nạ có một treap theo cặp `(độ sâu, mã đỉnh)` để đếm theo ngưỡng. Không dùng các Fenwick nén theo mặt nạ hoặc cơ chế xóa dữ liệu của lời giải mẫu.

Ngoài oracle C++, Python kiểm tra các trường hợp nhỏ bằng cách liệt kê bộ ba, sắp tần suất, thử mọi tọa độ ứng viên hoặc liệt kê mọi cặp đỉnh. Với DTMATKHAU, Python đi trực tiếp lên tổ tiên để lấy các chữ trên đường, kiểm tra số chữ có tần suất lẻ và LCA của cặp.

Các họ nhỏ có liệt kê toàn bộ cây gán nhãn tới 4 đỉnh cùng các cấu hình màu, tọa độ/trọng số hoặc nhãn cạnh tương ứng. Các cấu hình ngẫu nhiên còn kiểm tra ngưỡng khác nhau tại từng đỉnh.

## Chạy kiểm tra

Từ thư mục gốc dự án:

```sh
python3 dtqg/sack_tests/check.py
```

Chạy riêng một bài:

```sh
python3 dtqg/dtmatkhau/tests/check.py
```

Sau khi sửa bộ sinh và cần cập nhật hash:

```sh
python3 dtqg/sack_tests/check.py --update-hashes
```

Có thể chọn một hoặc nhiều bài bằng `--problem`. Quy trình biên dịch các thành phần, sinh dữ liệu, chạy verifier, tạo đáp án, kiểm tra thời gian lời giải mẫu, chạy checker và đối chiếu oracle. Nó còn kiểm tra ví dụ trong đề, thứ tự heading, quy tắc nội dung lời giải, tính tái lập của bộ sinh, kích thước test lớn, các trường hợp có công thức trực tiếp, đầu vào sai và các đáp án sai/thiếu/thừa.

Quy trình không xuất HTML và không cần cài thêm thư viện Python.

## Kết quả kiểm tra

| Bài | Test chính thức | Trường hợp nhỏ | Dữ liệu sai bị loại | Phép thử checker |
| --- | ---: | ---: | ---: | ---: |
| DTBASAC | 30 | 1539 | 13 | 33 |
| DTTOPMAU | 30 | 446 | 19 | 33 |
| DTHENGAP | 30 | 316 | 12 | 33 |
| DTCANBANG | 30 | 1539 | 15 | 33 |
| DTMATKHAU | 30 | 901 | 16 | 33 |
| Tổng | 150 | 4741 | 75 | 165 |

Toàn bộ các kiểm tra trên đã đạt. Mỗi bài có 60 mục hash cho 30 đầu vào và 30 đáp án. Lời giải mẫu của cả năm bài đạt giới hạn thời gian trong cấu hình trên máy kiểm tra hiện tại. Các mục kiểm thử không được đưa vào `solution.md`.
