# Lời giải SECOND — Tổng giá trị lớn thứ hai

## Đếm đóng góp của một phần tử

Giá trị $A_i$ là lớn thứ hai trong một đoạn chứa $i$ khi và chỉ khi đoạn đó chứa đúng một phần tử lớn hơn $A_i$.

Gọi $L_1,L_2$ là vị trí lớn hơn $A_i$ thứ nhất và thứ hai khi đi từ $i$ sang trái; $R_1,R_2$ tương tự bên phải. Không tồn tại thì dùng biên $0$ cho bên trái, $N+1$ cho bên phải.

- Phần tử lớn hơn duy nhất ở bên trái: đầu trái thuộc $[L_2+1,L_1]$, đầu phải thuộc $[i,R_1-1]$. Có $(L_1-L_2)(R_1-i)$ đoạn.
- Phần tử lớn hơn duy nhất ở bên phải: đầu trái thuộc $[L_1+1,i]$, đầu phải thuộc $[R_1,R_2-1]$. Có $(i-L_1)(R_2-R_1)$ đoạn.

Vì vậy đóng góp của $A_i$ là

$$A_i\big((L_1-L_2)(R_1-i)+(i-L_1)(R_2-R_1)\big).$$

Hai nhóm không giao nhau và bao phủ đúng mọi đoạn mà $A_i$ là lớn thứ hai. Giá trị lớn nhất toàn dãy không đóng góp; các biên giả khiến công thức tự trả số đoạn bằng $0$ khi thiếu phần tử lớn hơn.

## Hai stack tìm hai vị trí lớn hơn bên phải

Quét từ trái sang phải, dùng:

- Stack thứ nhất chứa các chỉ số chưa gặp phần tử lớn hơn lần nào.
- Stack thứ hai chứa các chỉ số đã gặp đúng một phần tử lớn hơn, đang chờ lần thứ hai.

Khi gặp $A_i$:

1. Trong stack thứ hai, lấy ra mọi đỉnh có giá trị nhỏ hơn $A_i$ và ghi $i$ là vị trí lớn hơn thứ hai của chúng.
2. Trong stack thứ nhất, lấy ra các đỉnh nhỏ hơn $A_i$, ghi $i$ là vị trí lớn hơn thứ nhất.
3. Chuyển nhóm vừa lấy từ stack thứ nhất sang stack thứ hai **theo thứ tự ngược với thứ tự pop**, để stack thứ hai giữ tính đơn điệu.
4. Thêm $i$ vào stack thứ nhất.

Phải xử lý stack thứ hai trước, để phần tử mới không bị tính hai lần cho cùng một chỉ số. Cả hai stack có giá trị giảm từ đáy tới đỉnh, nên chỉ cần xét đỉnh để biết các phần tử đã tìm được câu trả lời.

Mỗi chỉ số vào/ra mỗi stack nhiều nhất một lần, tổng thời gian $O(N)$. Đảo dãy rồi thực hiện lại để suy ra hai vị trí bên trái.

## Đúng đắn và độ phức tạp

Khi một chỉ số rời stack thứ nhất, phần tử hiện tại là phần tử đầu tiên lớn hơn nó trong thứ tự quét. Nó chỉ được chuyển sang stack chờ lần hai sau khi hoàn tất bước xử lý hiện tại. Khi rời stack thứ hai, nó đã gặp đúng một phần tử lớn hơn trước đó, nên phần tử hiện tại là lần thứ hai. Hai lượt quét tính đúng bốn biên; công thức đóng góp tính đúng đáp án.

- Thời gian $O(N)$, bộ nhớ $O(N)$.
- Dùng `long long` ngay từ phép nhân số lựa chọn; đáp án không vượt $N\binom N2<4\cdot10^{15}$.
- Trong code dùng chỉ số $0$ đến $N-1$, nên biên giả trái là $-1$, biên phải là $N$.
- Với $N=1$, tổng bằng $0$.

## Phương án vét cạn

Thử mọi đoạn và duy trì hai giá trị lớn nhất cho lời giải $O(N^2)$, phù hợp khi $N$ nhỏ.
