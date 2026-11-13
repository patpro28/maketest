## Cố định dấu theo chỉ số

Đặt $B_i=(-1)^{i-1}A_i$. Dãy $B$ giữ nguyên dấu tại chỉ số lẻ và đảo dấu tại chỉ số chẵn. Khi gán $A_i=x$, gán $B_i=x$ nếu $i$ lẻ và $B_i=-x$ nếu $i$ chẵn.

Trong đoạn $[l,r]$, giá trị cần xét ở vị trí $i$ là

$$(-1)^{i-l}A_i=(-1)^{l-1}B_i.$$

Hệ số $(-1)^{l-1}$ giống nhau ở mọi vị trí trong đoạn. Nếu $l$ lẻ, đáp án là max của $B$ trên $[l,r]$. Nếu $l$ chẵn, đáp án là max của $-B$ trên đoạn, bằng số đối của min của $B$.

## Cây đoạn

Dựng cây đoạn lưu min và max của $B$. Nút cha lấy min của hai cực tiểu và max của hai cực đại. Mỗi lần gán chỉ thay đổi một lá nên chỉ cần tính lại các nút trên đường từ lá đến gốc.

Các nút phủ một đoạn truy vấn cho đúng min và max của $B$ trên đoạn. Sau khi chọn cực trị theo tính chẵn lẻ của $l$, công thức biến đổi bảo đảm đáp án đúng với dãy dấu bắt đầu bằng dấu cộng tại $l$.

## Độ phức tạp

Dựng cây trong $O(N)$. Mỗi lần gán hoặc truy vấn mất $O(\log(N+1))$. Bộ nhớ là $O(N)$.
