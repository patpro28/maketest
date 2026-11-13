## Chạy kiểm thử

Từ thư mục gốc dự án, chạy lệnh sau để biên dịch, sinh lại dữ liệu, kiểm tra đầu vào và chạy lời giải với giới hạn 1 giây.

```sh
python3 dtqg/dtdochoi/tests/check.py
```

Lệnh kiểm tra đầu ra bằng checker và đối chiếu `hash.json`. Phép vét cạn mọi cách chia được dùng cho các trường hợp nhỏ. Các test sinh với $n\le 2\,000$ được kiểm tra thêm bằng cách duyệt mọi đoạn của Alice trong $O(n^2)$. Hai ví dụ và điểm của sáu subtask được đối chiếu với dữ liệu chấm.

Ba test cuối đều có $n=2\,000\,000$. Chúng lần lượt dùng dữ liệu ngẫu nhiên trên toàn miền giá trị, các cực trị tiền tố và hậu tố thay đổi theo vị trí, và một cách chia tối ưu mà đoạn của Alice nằm giữa dãy đã sắp xếp. Trong test cuối, hai màu ở giữa chênh nhau $1$ và hai kích thước ở ngoài chênh nhau $1$. Chi phí $2$ đạt được bằng cách giao cả hai màu ở giữa cho Alice. Để đạt chi phí nhỏ hơn, Alice phải giữ cùng một màu hoặc Bob phải giữ cùng một kích thước. Cả hai trường hợp đều buộc một trong hai bạn giữ hai giá trị cách nhau hơn $1$.
