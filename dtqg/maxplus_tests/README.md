# Năm bài DP với ma trận max-plus

## Thứ tự luyện tập

| Thứ tự | Bài | Mục tiêu chính | Kích thước ma trận | Độ phức tạp lời giải mẫu |
| --- | --- | --- | --- | --- |
| 1 | [HANHTRINH — Hành trình đúng số chặng](../hanhtrinh/task.md) | Chuyển DP theo số bước sang lũy thừa max-plus | $N\le30$ | $O(M+N^3\log(K+1))$ |
| 2 | [LICHTRUC — Lịch công việc tuần hoàn](../lichtruc/task.md) | Tự thiết kế trạng thái, ghép chu kỳ và xử lý phần dư | $7$ | $O(7^3(P+\log(D+1)))$ |
| 3 | [DAYNEN — Dãy số nén](../daynen/task.md) | Lưu phép biến đổi DP cho từng khối; ghép và lặp các dãy đã tạo | $C+1\le6$ | $O(N(C+1)^3\log(10^{12}+1))$ |
| 4 | [CACHBA — Chọn các vị trí cách ba](../cachba/task.md) | DP trên đoạn có cập nhật; segment tree lưu tích theo thứ tự | $3$ | Xây $O(N)$; mỗi thao tác $O(\log N)$ với ma trận kích thước cố định |
| 5 | [CHONCAY — Chọn đỉnh trên cây động](../choncay/task.md) | Dynamic DP trên cây; tách đóng góp con nhẹ và truyền DP trên chuỗi nặng | $2$ | Tiền xử lý $O(N)$; mỗi cập nhật $O(\log^2N)$ |

Độ khó tăng theo phần mô hình hóa và cách tổ chức phép ghép. Bài đầu làm rõ ý nghĩa của lũy thừa, hai bài giữa yêu cầu giữ đầy đủ trạng thái của một khối, hai bài cuối dùng tính kết hợp để hỗ trợ cập nhật. Bài cuối cần biết DP tập độc lập trên cây, heavy-light decomposition và segment tree.

Mỗi bài có ba ví dụ, đề `task.md`, lời giải `solution.md`, code C++17 `sol/correct.cpp`, bộ sinh, verifier, checker, cấu hình `info.toml` và `hash.json`. Bộ bài này không chia subtask. Các lời giải trình bày thuật toán, chứng minh và độ phức tạp; tài liệu kiểm thử được lưu riêng tại đây.

## Kiến thức cần nắm trước khi chuyển bài

Trong max-plus, phép lấy tổng các phương án được thay bằng lấy max, còn điểm của các phần được ghép được cộng lại:

$$ (A\otimes B)[i][j]=\max_k(A[i][k]+B[k][j]). $$

Ma trận đơn vị có đường chéo bằng $0$, các ô khác bằng $-\infty$. Ma trận toàn số $0$ cho phép chuyển miễn phí giữa mọi trạng thái, nên không biểu diễn một khối rỗng.

Với mỗi bài, nên tự trả lời được bốn câu trước khi cài đặt:

1. Một trạng thái lưu thông tin gì và vì sao đủ để quyết định phần tiếp theo?
2. Ô $M[i][j]$ có ý nghĩa gì; đang dùng vector hàng hay vector cột?
3. Khi nối hai khối, ma trận nào đứng trước? Trạng thái ở điểm nối có được giữ đầy đủ không?
4. Vector đầu là gì, trạng thái cuối nào được phép và số $-\infty$ được xử lý ra sao?

HANHTRINH, LICHTRUC, DAYNEN và CACHBA dùng vector hàng: đọc khối trái trước rồi khối phải ứng với $M_{\text{trái}}\otimes M_{\text{phải}}$. CHONCAY dùng vector cột để viết quan hệ DP từ con nặng lên cha; tích trên chuỗi được lưu theo thứ tự từ đầu chuỗi xuống cuối chuỗi. Hai quy ước đều hợp lệ, nhưng phải nhất quán trong từng lời giải.

## Bộ dữ liệu

Mỗi bài có 30 test chính thức: 3 ví dụ, 7 trường hợp biên, 6 test nhỏ, 6 test ngẫu nhiên và 8 test lớn. Tổng cộng 150 test, với 300 mục hash cho đầu vào và đáp án. Dữ liệu được sinh trong `in/`, đáp án trong `out/`; bộ sinh và cấu hình là nguồn để tái tạo chúng.

- **HANHTRINH:** không có cạnh, số bước bằng 0, hai đầu khác nhau, cạnh song song, tự khuyên, đồ thị không liên thông, hạn chế tính chẵn lẻ, trọng số âm và số bước tới $10^{12}$. Có test đạt đúng $10^{18}$ và $-10^{18}$ để bắt tràn số hoặc dùng sentinel sai.
- **LICHTRUC:** số ngày bằng 0, ít hơn một chu kỳ, bội và không phải bội của chu kỳ, toàn điểm âm, chỉ một việc có lợi, điểm bằng nhau và chu kỳ dài $10^5$. Các ràng buộc liên tiếp phải được giữ qua ranh giới chu kỳ.
- **DAYNEN:** bảng chữ chỉ có một giá trị, phần tử bằng nhau, thứ tự nối khác nhau, tham chiếu dùng chung, nối một dãy với chính nó, lặp 0 hoặc 1 lần, dãy rỗng, độ dài tới $10^{12}$ và $20000$ chỉ dẫn. Test lớn có nhiều phép lặp với số mũ lớn.
- **CACHBA:** đoạn dài 1, 2, 3, 4, chọn sát biên phải, toàn số âm, toàn số dương, tổng vượt 32 bit, cập nhật lặp một vị trí, nhiều truy vấn toàn đoạn và nhiều cập nhật xen kẽ truy vấn. Các test lớn đạt $N=Q=10^5$.
- **CHONCAY:** cây một đỉnh, cây dây, cây sao, cây cân bằng, cây ngẫu nhiên, cây chổi, cây lược và nhiều nhánh dài. Có trọng số âm, 0, đổi dấu nhiều lần, cập nhật gần gốc và ở lá, đổi nhãn đỉnh và đảo thứ tự cạnh. Các test lớn đạt $N=Q=10^5$.

## Đối chiếu độc lập

`oracle.cpp` chứa các cách tính riêng để đối chiếu toàn bộ dữ liệu chính thức:

- **HANHTRINH:** các khối chuyển có độ dài lũy thừa hai tác động lên một vector xuất phát; với số bước nhỏ, đối chiếu thêm bằng DP trực tiếp qua danh sách cạnh.
- **LICHTRUC:** mô hình 16 trạng thái lưu hành động trong hai ngày vừa qua, thay cho mô hình 7 trạng thái của lời giải mẫu. Ma trận chu kỳ được dựng bằng các bước DP thưa theo từng ngày. Với số ngày nhỏ, chạy trực tiếp toàn lịch.
- **DAYNEN:** lưu độ dài LNDS khi chỉ được dùng các giá trị trong từng khoảng $[l,r]$ của bảng chữ. Khi ghép hai khối, thử giá trị chia giữa phần chọn từ khối trái và khối phải. Với các dãy có thể giải nén trong ngân sách nhỏ, đối chiếu thêm bằng thuật toán patience sorting dùng `upper_bound`.
- **CACHBA:** chia khối, dùng truy hồi $F_i=\max(F_{i-1},F_{i-3}+A_i)$ và cache ảnh hưởng của mỗi khối lên ba giá trị DP liên tiếp. Không dùng segment tree hoặc mô hình thời gian chờ của lời giải mẫu. Với đoạn ngắn, còn liệt kê mọi tập vị trí hợp lệ.
- **CHONCAY:** đặt gốc tại đỉnh $N$, chia các đường nặng thành khối và dựng phép truyền của từng khối bằng DP trực tiếp. Không dùng segment tree của lời giải mẫu. Với cây nhỏ, liệt kê mọi tập đỉnh để đối chiếu.

Ngoài oracle C++, chương trình Python kiểm tra các trường hợp nhỏ bằng DP trực tiếp hoặc giải nén. Nó liệt kê toàn bộ một số họ đồ thị, lịch điểm, dãy nhị phân, dãy trọng số và cây gán nhãn nhỏ; các bài chọn tập còn được đối chiếu bằng vét cạn tập con.

## Chạy kiểm tra

Chạy từ thư mục gốc dự án:

```sh
python3 dtqg/maxplus_tests/check.py
```

Kiểm tra riêng một bài:

```sh
python3 dtqg/choncay/tests/check.py
```

Sau khi sửa bộ sinh hoặc dữ liệu, tạo lại đáp án và cập nhật hash cùng toàn bộ kiểm tra:

```sh
python3 dtqg/maxplus_tests/check.py --update-hashes
```

Có thể dùng `--problem` để chọn một hoặc nhiều bài. Quy trình gọi riêng các bước sinh dữ liệu, verifier, lời giải và checker; không xuất HTML. Nó còn kiểm tra thời gian lời giải mẫu, cấu trúc đề, độ khớp của ví dụ, tính tái lập của bộ sinh, giới hạn test lớn, đầu vào sai, checker với đáp án sai/thiếu/thừa và hash của toàn bộ dữ liệu.

## Kết quả kiểm tra

| Bài | Test chính thức | Trường hợp nhỏ | Dữ liệu sai bị loại | Phép thử checker |
| --- | ---: | ---: | ---: | ---: |
| HANHTRINH | 30 | 970 | 14 | 30 |
| LICHTRUC | 30 | 423 | 11 | 27 |
| DAYNEN | 30 | 347 | 17 | 33 |
| CACHBA | 30 | 523 | 15 | 33 |
| CHONCAY | 30 | 446 | 15 | 33 |
| Tổng | 150 | 2709 | 72 | 156 |

Toàn bộ các kiểm tra trên đã đạt. Mỗi bài có 60 mục hash cho 30 đầu vào và 30 đáp án. Lời giải mẫu của cả năm bài đạt giới hạn thời gian trong cấu hình trên máy kiểm tra hiện tại.
