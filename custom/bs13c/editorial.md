# BS13C — Hướng dẫn giải

Sắp xếp mảng sức chứa không giảm. Với đoàn $X$ người, dùng `lower_bound` tìm phòng đầu tiên có sức chứa không dưới $X$.

Nếu không tìm được, in `-1 0`. Nếu tìm được giá trị $V$, số chỗ trống tối ưu là $V-X$, vì mọi sức chứa hợp lệ khác đều không nhỏ hơn $V$. Tất cả và chỉ các phòng có sức chứa $V$ đạt mức tối ưu này. Dùng `upper_bound(V)-lower_bound(V)` để đếm chúng.

Sắp xếp không làm thay đổi số lượng phòng có mỗi sức chứa; các truy vấn độc lập nên không xóa phòng sau khi trả lời.

Độ phức tạp $O(N\log N+Q\log N)$, bộ nhớ $O(N)$.

Lời giải đối chiếu dùng bảng ánh xạ có thứ tự từ sức chứa sang số lượng, rồi tìm khóa nhỏ nhất không dưới $X$.

### Theo subtask

- Subtask 1 (50%): $N\cdot Q\le10^6$, duyệt tất cả phòng cho mỗi đoàn; vừa tìm số chỗ trống nhỏ nhất vừa đếm số phòng đạt mức đó. Độ phức tạp $O(NQ)$.
- Subtask 2 (50%): sắp xếp và tìm kiếm nhị phân như lời giải tổng quát.
