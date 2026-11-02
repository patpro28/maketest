### Ý tưởng

Mỗi nút lưu BCNN của đoạn, nhưng chặn các giá trị vượt ngưỡng $B=10^{18}$ bằng một ký hiệu riêng $OVER=B+1$. Lá chứa $x$ lưu $x$.

Với hai giá trị chưa vượt ngưỡng $u,v$, đặt $t=u/\gcd(u,v)$. Ta cần tính $t\cdot v$. Trước khi nhân, kiểm tra:

- Nếu $t>\lfloor B/v\rfloor$, trả về $OVER$.
- Nếu không, trả về $t\cdot v$.

Nếu một nút con đã là $OVER$, nút cha cũng là $OVER$, vì BCNN của một đoạn chứa đoạn con luôn là bội của BCNN đoạn con. Giá trị trung hòa cho đoạn rỗng là $1$.

Dựng segment tree theo phép ghép trên. Với mỗi truy vấn, in BCNN nhận được; nếu kết quả là $OVER$ thì in $-1$.

### Chứng minh tính đúng đắn

Với số dương $u,v$, công thức $\operatorname{lcm}(u,v)=(u/\gcd(u,v))v$ đúng. Điều kiện chia trước khi nhân xác định chính xác việc tích vượt $B$, đồng thời tránh tràn số.

Nếu BCNN của một đoạn con lớn hơn $B$, mọi bội chung của đoạn hợp cũng phải là bội của BCNN này, nên chắc chắn vượt $B$. Vì vậy có thể thay mọi giá trị vượt ngưỡng bằng cùng ký hiệu $OVER$ mà không làm mất thông tin cần trả lời.

Các lá lưu đúng BCNN của một phần tử. Theo quy nạp, phép ghép luôn cho BCNN chính xác khi không vượt $B$, hoặc ký hiệu $OVER$ khi vượt ngưỡng. Truy vấn ghép các đoạn phủ $[L,R]$, nên trả lời đúng theo yêu cầu.

### Độ phức tạp

Nếu coi phép GCD là thao tác cơ bản: dựng cây $O(N)$, mỗi truy vấn $O(\log N)$, bộ nhớ $O(N)$. Tính thêm chi phí thuật toán Euclid cho các giá trị không quá $B$, cận trên thời gian là $O((N+Q\log N)\log B)$.

### Lưu ý cài đặt

Dùng số nguyên 64 bit. Kiểm tra trước khi nhân; không nhân rồi mới so với ngưỡng vì tích có thể tràn số. Phần tử $1$ không làm thay đổi BCNN. Kết quả một phần tử luôn bằng chính phần tử đó.

### Vì sao không dùng hiệu tổng tiền tố

Hai đoạn $[2,6]$ và $[3,5]$ cùng có độ dài $2$ và tổng $8$, nhưng BCNN lần lượt là $6$ và $15$. BCNN tiền tố cũng không có phép khử tương tự phép trừ tổng: một thừa số đã xuất hiện trước $L$ có thể che khuất thông tin của đoạn $[L,R]$.
