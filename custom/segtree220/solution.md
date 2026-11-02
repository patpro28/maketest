### Ý tưởng

Segment tree thông thường lưu giá trị lớn nhất trên mỗi đoạn. Nếu cập nhật từng phần tử khi cộng một đoạn dài, một thao tác có thể mất $O(n)$ thời gian.

Nhận xét quan trọng là khi mọi phần tử trong một đoạn cùng được cộng $k$, giá trị lớn nhất của đoạn cũng tăng đúng $k$:

$$\max(a_l+k,\dots,a_r+k)=\max(a_l,\dots,a_r)+k.$$

Do đó, khi đoạn cập nhật phủ toàn bộ một nút, ta có thể sửa ngay giá trị lớn nhất của nút mà chưa cần đi xuống từng lá. Dùng lazy propagation để ghi nhớ phần cộng còn chờ truyền xuống các nút con.

### Thông tin lưu trên nút

Mỗi nút $p$ lưu:

- `maximum[p]`: giá trị lớn nhất của đoạn tại nút, đã tính các lần cộng được áp dụng trực tiếp lên nút đó.
- `lazy[p]`: tổng lượng cộng đã tính vào `maximum[p]` nhưng chưa truyền xuống hai nút con.

Ban đầu, mọi `lazy` bằng $0$. Giá trị lớn nhất của nút trong được tính bằng giá trị lớn hơn giữa hai nút con.

Áp dụng một lượng cộng $k$ lên toàn bộ nút $p$:

```text
maximum[p] += k
lazy[p] += k
```

Các lần cộng chồng lên nhau được gộp bằng phép cộng, kể cả khi $k$ âm.

### Đẩy cập nhật chờ

Trước khi đi từ nút $p$ xuống các nút con, nếu `lazy[p]` khác $0$, áp dụng lượng cộng này lên cả hai nút con rồi đặt `lazy[p]` về $0$.

Sau bước đẩy, các nút con đã nhận toàn bộ phần cộng đang chờ ở cha, nên có thể tiếp tục cập nhật hoặc truy vấn bên dưới.

### Cập nhật đoạn

Với thao tác `0 u v k`:

- Nếu đoạn tại nút nằm hoàn toàn trong $[u,v]$, áp dụng lượng cộng $k$ lên nút và dừng tại đó.
- Nếu chỉ giao một phần, đẩy cập nhật chờ xuống; tiếp tục cập nhật các nút con có giao với $[u,v]$.
- Sau khi cập nhật con, tính lại `maximum` của cha bằng giá trị lớn nhất của hai con.

### Truy vấn đoạn

Với thao tác `1 u v`:

- Nếu đoạn tại nút nằm hoàn toàn trong $[u,v]$, trả về `maximum` của nút.
- Nếu chỉ giao một phần, đẩy cập nhật chờ xuống rồi truy vấn các nút con có giao.
- Nếu truy vấn cả hai bên, lấy giá trị lớn hơn trong hai kết quả.

Cách cài đặt chỉ gọi đệ quy vào các đoạn có giao, nên không cần lấy $0$ làm kết quả của đoạn rỗng. Điều này tránh trả lời sai khi mọi phần tử đều âm.

### Chứng minh tính đúng đắn

Sau khi dựng cây, mỗi lá lưu đúng phần tử tương ứng; mỗi nút trong lấy lớn nhất của hai con, nên thông tin của mọi đoạn đều đúng.

Cộng cùng $k$ vào toàn bộ một đoạn làm giá trị lớn nhất tăng đúng $k$. Vì vậy thao tác áp dụng lên nút cập nhật đúng `maximum`, còn `lazy` ghi lại chính xác lượng cộng cần truyền cho từng phần tử bên dưới. Nhiều lần cộng được gộp đúng bằng tổng các lượng cộng.

Khi đi xuống, đẩy `lazy` sang cả hai con không thay đổi giá trị thực của dãy; nó chỉ đưa phần cộng đã ghi ở cha vào thông tin của các con. Do đó các con có thông tin đúng để tiếp tục xử lý. Sau một cập nhật giao một phần, lấy lớn nhất của hai con khôi phục đúng thông tin ở cha.

Truy vấn lấy thông tin từ các nút phủ đoạn được hỏi, sau khi đã đẩy các lượng cộng cần thiết. Giá trị lớn nhất trong các đoạn con này chính là giá trị lớn nhất trên toàn đoạn truy vấn. Theo quy nạp qua từng thao tác, mọi kết quả được in đều đúng với dãy hiện tại.

### Độ phức tạp

Dựng cây mất $O(n)$ thời gian. Mỗi cập nhật đoạn và truy vấn đoạn mất $O(\log n)$ thời gian. Tổng thời gian là $O(n+m\log n)$; bộ nhớ là $O(n)$.

### Lưu ý cài đặt

Dùng `lazy += k`, không gán `lazy = k`, vì các cập nhật cộng dồn. Chỉ số đầu/cuối đoạn đều được tính vào thao tác. Giới hạn $|a_i|\le10000$ chỉ áp dụng cho dãy ban đầu; các giá trị sau nhiều cập nhật có thể lớn hơn giới hạn này. Có thể dùng số nguyên 64 bit cho giá trị và lượng cộng tích lũy để thuận tiện cài đặt.
