### Tiền xử lý bằng mảng hiệu

Tất cả phép cộng được thực hiện trước mọi câu hỏi. Vì vậy có thể tính dãy cuối cùng trước, rồi xử lý các câu hỏi trên một dãy cố định.

Khởi tạo mảng hiệu $D$ bằng $0$. Với phép cộng $k$ vào đoạn $[u,v]$, thực hiện:

$$D_u\mathrel{+}=k,\qquad D_{v+1}\mathrel{-}=k.$$

Sau khi đọc hết các phép biến đổi, tính tổng tiền tố:

$$A_i=D_1+D_2+\dots+D_i.$$

Một phép cộng đóng góp $k$ vào tổng tiền tố từ vị trí $u$ đến vị trí $v$, rồi bị triệt tiêu từ vị trí $v+1$. Vì vậy $A$ chính là dãy sau toàn bộ phép biến đổi.

### Thông tin lưu trên segment tree

Mỗi nút lưu hai trường:

- `maximum`: giá trị lớn nhất trong đoạn của nút.
- `count`: số phần tử trong đoạn có giá trị bằng `maximum`.

Lá chứa phần tử $x$ có thông tin $(x,1)$.

Để ghép hai nút $A,B$:

- Nếu $A.maximum>B.maximum$, lấy thông tin của $A$.
- Nếu $A.maximum<B.maximum$, lấy thông tin của $B$.
- Nếu hai giá trị lớn nhất bằng nhau, giữ giá trị đó và cộng hai trường `count`.

Dựng cây trên dãy đã tiền xử lý. Với mỗi câu hỏi, ghép các nút phủ đoạn $[u,v]$ và in hai trường của kết quả. Không có cập nhật trong giai đoạn này.

### Chứng minh tính đúng đắn

Với mỗi phép biến đổi, hai thay đổi ở mảng hiệu làm đúng các phần tử trong đoạn được tăng thêm $k$, như đã giải thích ở trên. Do các lượng cộng được cộng dồn, tổng tiền tố sau cùng cho đúng giá trị của mọi phần tử sau tất cả phép biến đổi.

Tại lá, giá trị lớn nhất là chính phần tử đó và xuất hiện một lần. Giả sử thông tin của hai đoạn con đúng. Giá trị lớn nhất của đoạn hợp là giá trị lớn hơn trong hai cực đại. Nếu chúng khác nhau, mọi phần tử đạt cực đại của đoạn hợp đều thuộc phía có cực đại lớn hơn. Nếu chúng bằng nhau, số lần xuất hiện bằng tổng số lần xuất hiện ở hai phía. Phép ghép vì thế tính đúng cả hai trường.

Theo quy nạp, mọi nút và kết quả ghép trong một truy vấn đều đúng. Cặp được in chính là giá trị lớn nhất và số lần xuất hiện của nó trong đoạn được hỏi.

### Độ phức tạp

Tiền xử lý mảng hiệu và dựng cây mất $O(m+n)$ thời gian. Mỗi câu hỏi mất $O(\log n)$ thời gian. Tổng thời gian là $O(n+m+q\log n)$ và bộ nhớ là $O(n)$.

### Lưu ý cài đặt

Dùng số nguyên 64 bit cho mảng hiệu và giá trị lớn nhất, vì một phần tử có thể đạt $m\cdot10^9\le2\cdot10^{14}$. Dành vị trí $n+1$ cho mảng hiệu để xử lý phép cộng kết thúc ở $n$.

Mọi giá trị cuối cùng đều không âm. Có thể dùng $(0,0)$ cho nút rỗng khi truy vấn hoặc lá đệm: giá trị $0$ ở nút rỗng không làm tăng số lần xuất hiện vì trường `count` bằng $0$. Các vị trí thật chưa được cộng vẫn phải có nút lá $(0,1)$.
