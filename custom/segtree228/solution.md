## Đánh chỉ số các cặp đối xứng

Đặt $K=\lfloor N/2\rfloor$. Mỗi cặp có duy nhất một đầu mang chỉ số $i$ trong $[1,K]$. Đầu còn lại là $N+1-i$. Dựng dãy chênh lệch có dấu

$$D_i=A_i-A_{N+1-i}\qquad (1\le i\le K).$$

Nếu $N=1$ thì $K=0$. Mọi truy vấn trả lời $0$ vì không có cặp đối xứng.

## Chuyển các thao tác sang dãy chênh lệch

Khi cộng $x$ trên đoạn $[L,R]$ của dãy gốc, đầu thứ nhất của cặp được cập nhật nếu $i\in[L,R]$. Đầu thứ hai được cập nhật nếu $N+1-i\in[L,R]$, tức là $i\in[N+1-R,N+1-L]$. Vì vậy, cộng $x$ lên giao của đoạn thứ nhất với $[1,K]$, rồi cộng $-x$ lên giao của đoạn thứ hai với $[1,K]$. Nếu hai giao chồng nhau, phần chồng nhận cả $x$ và $-x$, đúng với trường hợp hai đầu cặp cùng tăng một lượng.

Với truy vấn $[L,R]$, cả hai đầu của một cặp nằm trong đoạn khi và chỉ khi chỉ số cặp thuộc giao

$$[1,K]\cap[L,R]\cap[N+1-R,N+1-L].$$

Cụ thể, cận trái là $\max(1,L,N+1-R)$ và cận phải là $\min(K,R,N+1-L)$. Nếu cận trái vượt cận phải, trả lời $0$. Nếu giao khác rỗng, đáp án là $\max(\max D_i,-\min D_i)$ trên giao đó, vì $|D_i|=\max(D_i,-D_i)$.

## Cây đoạn có cập nhật lười

Mỗi nút lưu min và max của đoạn trong dãy $D$, cùng nhãn cộng chờ. Khi một phép cộng phủ kín đoạn của nút, cộng vào cả hai cực trị và nhãn. Khi phải đi xuống cây, truyền nhãn trước. Ghép kết quả của hai đoạn bằng cách lấy min của hai cực tiểu và max của hai cực đại.

Hai phép cộng trên dãy $D$ mô tả đúng mức thay đổi ở từng đầu cặp. Cây vì vậy duy trì đúng các chênh lệch có dấu qua mọi thao tác, còn giao ba đoạn chọn chính xác các cặp cần xét.

## Độ phức tạp

Dựng dãy $D$ và cây trong $O(N)$. Mỗi thao tác tốn $O(\log(N+1))$ thời gian. Bộ nhớ là $O(N)$. Dùng số nguyên 64 bit cho chênh lệch và nhãn cộng.
