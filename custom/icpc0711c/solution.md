## Thuật toán

Vì $N\le10^{18}$, căn bậc ba nguyên của $N$ không vượt quá $10^6$. Duyệt các số nguyên dương $x$ trong phạm vi này khi $x^3\le N$. Đảo các chữ số của $x^3$ bằng phép chia và lấy dư cho $10$; nếu số đảo bằng chính nó thì cập nhật đáp án.

## Tính đúng đắn

Mọi số lập phương dương không vượt $N$ có duy nhất một căn nguyên thuộc phạm vi đã duyệt. Phép đảo chữ số nhận biết chính xác số đối xứng. Lấy giá trị lớn nhất trong các ứng viên phù hợp vì thế cho kết quả cần tìm. Số $1$ luôn là ứng viên hợp lệ.

## Độ phức tạp

$O(\sqrt[3]{N}\log N)$ thời gian, $O(1)$ bộ nhớ. Dùng số nguyên 64 bit cho $x$ và phép nhân; tránh dùng căn bậc ba dấu phẩy động làm cận duy nhất.
