# BS13A — Hướng dẫn giải

## Đọc điều kiện và xác định khoảng

Điều kiện để chọn phần tử thứ $i$ là $0\le X-A_i\le K$, tương đương với $X-K\le A_i\le X$.

Mỗi truy vấn vì vậy yêu cầu đếm phần tử trong một đoạn đóng $[L,R]$. Hai đầu mút đều được tính, vì phần thừa có thể bằng $0$ hoặc đúng bằng $K$. Những phần tử bằng nhau vẫn là các lựa chọn riêng biệt.

## Theo từng subtask

- Subtask 1 (50%): $N\cdot Q\le10^6$. Với mỗi truy vấn, duyệt toàn bộ $N$ phần tử và đếm những phần tử thỏa mãn điều kiện. Tổng thời gian $O(NQ)$, phù hợp với giới hạn một triệu lượt kiểm tra.
- Subtask 2 (50%): không có ràng buộc bổ sung. Sắp xếp và tìm kiếm nhị phân như trình bày dưới đây để tránh duyệt lại toàn bộ dãy cho mỗi truy vấn.

## Sắp xếp và tìm kiếm nhị phân

Sắp xếp dãy $A$ tăng dần một lần. Với mỗi truy vấn:

- Dùng `lower_bound(A.begin(), A.end(), L)` để tìm vị trí đầu tiên có giá trị không nhỏ hơn $L$.
- Dùng `upper_bound(A.begin(), A.end(), R)` để tìm vị trí đầu tiên có giá trị lớn hơn $R$.
- Hiệu hai vị trí là số phần tử thuộc đoạn $[L,R]$.

Nếu không có phần tử hợp lệ, hai vị trí bằng nhau và đáp án là $0$. Khi $K=0$, cách làm đếm đúng tất cả phần tử có giá trị bằng $X$. Các truy vấn độc lập nên không xóa hoặc thay đổi phần tử sau khi trả lời.

Lời giải `sol/correct.cpp` sử dụng các hàm thư viện. Lời giải `sol/binary_search.cpp` tự viết tìm kiếm nhị phân để đếm số phần tử nhỏ hơn một ngưỡng, rồi lấy $C(R+1)-C(L)$.

## Chứng minh

Sau khi sắp xếp, mọi phần tử thuộc $[L,R]$ nằm liên tiếp. `lower_bound` loại đúng các phần tử nhỏ hơn $L$; `upper_bound` đứng ngay sau mọi phần tử không lớn hơn $R$. Vì vậy, đoạn giữa hai vị trí chứa đúng và đủ các lựa chọn hợp lệ.

## Độ phức tạp

Sắp xếp mất $O(N\log N)$. Mỗi truy vấn dùng hai lần tìm kiếm nhị phân, mất $O(\log N)$. Tổng thời gian là $O(N\log N+Q\log N)$, bộ nhớ lưu dãy là $O(N)$.

Dùng kiểu số nguyên có dấu khi tính các đầu mút; có thể dùng `long long` thống nhất cho $A_i,X,K,L,R$.
