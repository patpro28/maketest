## Thuật toán

Dựng segment tree trên dãy lượng hàng. Lá thứ $i$ lưu $A_i$. Mỗi nút trong lưu tổng hai nút con.

- Khi chuyển $x$ từ kho $u$ sang kho $v$, nếu $u=v$ thì bỏ qua. Nếu hai kho khác nhau, cộng $-x$ ở lá $u$ và $x$ ở lá $v$. Sau mỗi lần sửa lá, tính lại tổng trên đường tới gốc.
- Khi hỏi đoạn $[l,r]$, chia đoạn thành các đoạn rời nhau do các nút của cây quản lý, rồi cộng các tổng lưu ở những nút đó.

## Chứng minh tính đúng đắn

Ban đầu, các lá chứa đúng lượng hàng và mỗi nút chứa tổng của đoạn tương ứng. Mỗi lần chuyển chỉ làm thay đổi lượng hàng ở hai đầu. Sửa hai lá rồi tính lại các nút tổ tiên khôi phục tính chất tổng của mọi nút. Trường hợp hai đầu trùng nhau có thay đổi ròng bằng $0$.

Các đoạn được chọn khi truy vấn phủ đúng $[l,r]$ và đôi một rời nhau. Do đó cộng tổng của chúng tính đúng lượng hàng cần hỏi.

## Độ phức tạp

Dựng cây trong $O(N)$. Mỗi thao tác tốn $O(log(N+1))$ thời gian. Cây dùng $O(N)$ bộ nhớ.

Mỗi lần chuyển làm tổng của một đoạn thay đổi nhiều nhất $10^9$ về trị tuyệt đối. Mọi tổng có trị tuyệt đối không vượt $(N+Q)10^9$, nên dùng số nguyên 64 bit.
