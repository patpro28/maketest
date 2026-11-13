## Chia bốn lần đảo thành hai phía

Một lần đột biến là đảo đoạn, và phép đảo tự nghịch: đảo cùng đoạn lần nữa trở về xâu cũ.

Gọi $R_2(A)$ là tập xâu nhận được từ $A$ bằng không quá hai lần đảo đoạn. Hai xâu gần giống nhau khi và chỉ khi

$$R_2(A)\cap R_2(B)\ne\varnothing.$$

Nếu biến $A$ thành $B$ trong tối đa bốn bước, chọn trạng thái giữa sao cho mỗi phía cách nó không quá hai bước. Chiều ngược lại, ghép đường đi từ $A$ tới trạng thái chung với đường đi đảo ngược từ $B$ tới trạng thái chung tạo tối đa bốn lần đảo.

## Sinh hai lớp

Đoạn rỗng hoặc dài một không đổi xâu nên không cần sinh riêng. Có $R=n(n-1)/2$ đoạn dài ít nhất hai.

1. Nếu hai xâu có số lần xuất hiện của một ký tự khác nhau, trả lời `Different`, vì đảo đoạn không thay đổi các số lượng này.
2. Sinh danh sách gồm $A$ và mọi xâu sau một lần đảo. Từ từng xâu trong danh sách, đưa chính nó và mọi kết quả đảo thêm một lần vào tập lưu trữ.
3. Làm tương tự từ $B$, nhưng chỉ cần tra xem từng kết quả có trong tập phía $A$ hay không. Gặp một trạng thái chung thì trả lời `Similar`; nếu hết thì `Different`.

Các đường đi ngắn hơn hai bước đã có trong danh sách nên trường hợp không dùng đủ bốn bước được xử lý đúng.

## Mã hóa chính xác

Mỗi ký tự có bốn giá trị, mã hóa bằng hai bit. Với $n\le45$, toàn bộ xâu chiếm tối đa 90 bit và được lưu trong số nguyên 128 bit không dấu. Đảo đoạn bằng cách hoán đổi từng cặp trường hai bit từ hai đầu vào giữa.

Dùng tập băm với khóa là toàn bộ mã 128 bit. Hàm băm chỉ chọn ô lưu trữ; khi va chạm vẫn so sánh đầy đủ khóa, nên không có sai số do dùng hash xâu.

## Chứng minh đúng

Hai lượt sinh bao phủ mọi chuỗi gồm tối đa hai phép đảo vì thử mọi đoạn ở từng bước; đồng thời không tạo trạng thái vượt quá hai bước. Vì vậy tập phía $A$ và các trạng thái được tra từ phía $B$ đúng là hai tập $R_2$.

Theo điều kiện giao tập đã chứng minh, phát hiện giao tương đương tồn tại đường đi không quá bốn lần đột biến. Các kết luận của thuật toán đều đúng.

## Độ phức tạp

Có $O(R^2)=O(n^4)$ lần sinh trạng thái mỗi phía. Đảo trực tiếp một đoạn mất $O(n)$, nên thời gian kỳ vọng $O(n^5)$ khi dùng tập băm, bộ nhớ $O(n^4)$ mã trạng thái.

Một chặn cụ thể cho tổng số cặp ký tự được hoán đổi trên hai phía là

$$2(R+1)\sum_{L=2}^{n}(n-L+1)\lfloor L/2\rfloor.$$

Tại $n=45$, giá trị bằng $15544826$; số lần sinh/tra trạng thái ở hai phía nhỏ hơn hai triệu. Có thể dừng sớm khi tìm được trạng thái chung.
