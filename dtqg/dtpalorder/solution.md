## Ý tưởng

Vì thứ tự các độ dài đã cố định, với mỗi yêu cầu ta chọn đoạn phù hợp kết thúc sớm nhất sau những đoạn đã chọn. Giữ lại càng nhiều phần đuôi càng tốt.

Đánh số ký tự từ $0$. Dùng Manacher để tính hai mảng:

- $odd[c]$: bán kính đoạn đối xứng lẻ lớn nhất tại tâm $c$, bao gồm ký tự ở tâm.
- $even[c]$: bán kính đoạn đối xứng chẵn lớn nhất có tâm giữa $c-1$ và $c$.

Đoạn bắt đầu tại $p$, dài $L$, tồn tại khi $p+L\le n$. Nếu $L$ lẻ, nó đối xứng khi $odd[p+L/2]\ge L/2+1$; nếu $L$ chẵn, cần $even[p+L/2]\ge L/2$. Các phép chia trong công thức là chia nguyên.

Manacher duy trì đoạn đối xứng có biên phải xa nhất. Với tâm nằm trong đoạn này, lấy bán kính từ tâm đối xứng, chặn ở biên phải, rồi mở rộng. Tổng các lần mở rộng vượt biên phải là $O(n)$, nên tính hai mảng trong $O(n)$.

## Thuật toán và truy vết

Nếu $\sum l_i>n$, trả lời `NO`. Dùng số nguyên 64 bit để tính tổng.

Đặt $p=0$. Với từng độ dài $L$ theo thứ tự đầu vào, tăng $p$ cho đến khi đoạn $[p,p+L)$ đối xứng hoặc vượt cuối xâu. Nếu không có đoạn, trả lời `NO`. Nếu có, lưu cặp chỉ số $p+1,p+L$ rồi đặt $p\leftarrow p+L$.

Chỉ in `YES` và toàn bộ các cặp sau khi đã chọn đủ đoạn.

## Chứng minh đúng

Giả sử các yêu cầu trước đã được chọn kết thúc không muộn hơn một phương án hợp lệ bất kỳ. Đoạn tiếp theo của phương án đó vẫn nằm trong phần xâu còn được xét. Thuật toán lấy đoạn cùng độ dài kết thúc sớm nhất, nên cũng không kết thúc muộn hơn đoạn của phương án đó. Thay đoạn này không ảnh hưởng các lựa chọn phía sau.

Quy nạp cho mọi yêu cầu cho thấy nếu có phương án hợp lệ thì thuật toán tìm được. Ngược lại, mỗi đoạn thuật toán chọn có đúng độ dài, đối xứng và bắt đầu sau đoạn trước, nên kết quả luôn hợp lệ.

## Độ phức tạp

Mỗi lần tìm thất bại tại một vị trí làm $p$ tăng. Khi chọn được đoạn, $p$ cũng chỉ tăng. Vì vậy tổng số vị trí được xét qua các yêu cầu là $O(n+k)$, không phải $O(nk)$.

Tổng thời gian $O(n+k)$, bộ nhớ $O(n+k)$ kể cả các đoạn cần in.
