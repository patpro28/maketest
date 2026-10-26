# Lời giải — DPSTRING08

Theo dõi phần đuôi có thể tiếp tục tạo thành `aba`. Có ba trạng thái: $0$ (không có phần đuôi liên quan), $1$ (đuôi là `a`), $2$ (đuôi là `ab`). Lưu chi phí xóa nhỏ nhất cho từng trạng thái.

| Trạng thái cũ | Giữ `a` | Giữ `b` |
| --- | --- | --- |
| 0 | 1 | 0 |
| 1 | 1 | 2 |
| 2 | Không được phép | 0 |

Ở mỗi vị trí, xóa ký tự thì cộng chi phí và giữ nguyên trạng thái; giữ ký tự thì chuyển theo bảng mà không cộng chi phí. Khởi tạo trạng thái $0$ bằng $0$, hai trạng thái khác bằng vô cùng.

Ba trạng thái lưu đúng phần đuôi cần biết để quyết định việc giữ ký tự kế tiếp có tạo ra mẫu cấm hay không. Đáp án là chi phí nhỏ nhất trong ba trạng thái sau cùng. Bài chỉ cần bảng chuyển ba trạng thái viết trực tiếp.

Độ phức tạp thời gian: $O(N)$. Bộ nhớ phụ của phần DP: $O(1)$; mã C++ lưu thêm mảng điểm/chi phí đầu vào ở các bài có mảng này.

Dùng số nguyên 64 bit cho điểm và chi phí. Khi cập nhật nhiều trạng thái, chỉ sử dụng giá trị của tiền tố trước đó.
