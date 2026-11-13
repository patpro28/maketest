## Tổng chữ số và số lần nhớ

Khi cộng hai số $a,b$ theo hệ thập phân, mỗi lần nhớ sang cột tiếp theo làm tổng chữ số giảm $9$. Vì vậy

$$f(a+b)=f(a)+f(b)-9C(a,b),$$

trong đó $C(a,b)$ là tổng số lần nhớ. Nhớ qua ranh giới $p=10^k$ xảy ra khi và chỉ khi

$$(a\bmod p)+(b\bmod p)\ge p.$$

Điều kiện này đã bao gồm ảnh hưởng của mọi cột thấp hơn, nên xử lý đúng cả chuỗi nhớ liên tiếp.

Tổng ban đầu trên tất cả cặp có thứ tự là $2N\sum_i f(A_i)$. Với từng $p=10,100,\ldots,10^{15}$, đếm số cặp thỏa điều kiện trên và trừ $9$ lần số cặp đó. Không có nhớ qua $10^{16}$ vì $A_i+A_j\le2\cdot10^{15}$.

## Đếm cặp bằng hai con trỏ

Sắp xếp các phần dư $b_i=A_i\bmod p$. Với từng $i$ tăng dần, tìm vị trí đầu tiên $j$ sao cho $b_i+b_j\ge p$. Ngưỡng $j$ chỉ giảm nên có thể duy trì trong tổng $O(N)$ thời gian sau sắp xếp. Cộng $N-j$ cho mỗi $i$; không loại $i=j$ và không chia đôi vì đề xét cặp có thứ tự.

## Tính đúng đắn

Đẳng thức tổng chữ số được áp dụng cho từng cặp. Mỗi lần nhớ được đếm đúng tại ranh giới lũy thừa của $10$ tương ứng; phép đếm hai con trỏ xét toàn bộ và chỉ các phần dư đủ lớn. Lấy tổng đẳng thức trên tất cả cặp cho đúng kết quả thuật toán.

## Độ phức tạp

$O(15N\log N)$ thời gian, $O(N)$ bộ nhớ. Mọi tổng và số cặp dùng kiểu 64 bit.
