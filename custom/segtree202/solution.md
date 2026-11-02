### Ý tưởng

Một cập nhật mức tối thiểu $x$ biến giá trị $v$ thành $\max(v,x)$. Hai mức tối thiểu gộp thành mức lớn hơn trong hai mức. Do các giá trị đều không âm, dùng $0$ làm nhãn rỗng.

$$F_y(F_x(v))=\max(\max(v,x),y)=\max(v,\max(x,y)).$$

### Lưu và đẩy nhãn

Xây segment tree theo các vị trí. Vì chỉ hỏi một phần tử, mỗi nút chỉ cần lưu nhãn của những cập nhật phủ toàn bộ đoạn tại nút nhưng chưa được truyền xuống. Giữ riêng dãy giá trị ban đầu; không cần lưu tổng, min hay max của đoạn.

Định nghĩa `compose(older, newer)` là nhãn tương đương với áp dụng nhãn cũ trước, nhãn mới sau. Khi một cập nhật phủ toàn bộ nút, ghép nhãn cập nhật vào sau nhãn đang có ở nút.

Trước khi đi xuống con để cập nhật một phần hoặc hỏi một vị trí, đẩy nhãn của cha xuống cả hai con theo cùng quy tắc, rồi đưa nhãn của cha về nhãn rỗng. Việc đẩy trước khi cập nhật một phần bảo đảm giữ đúng thứ tự thời gian.

Để hỏi vị trí $p$, đi từ gốc xuống lá $p$, đẩy nhãn trên đường đi. Tại lá, áp dụng nhãn còn lưu lên giá trị ban đầu của phần tử rồi in kết quả. Có thể giữ nguyên nhãn tại lá sau khi hỏi vì dãy ban đầu vẫn được lưu riêng.

### Chứng minh tính đúng đắn

Công thức ghép ở trên chứng minh rằng nhãn gộp tác động lên một giá trị giống hệt hai nhãn được áp dụng lần lượt. Nhãn rỗng không làm thay đổi giá trị.

Ban đầu mọi nhãn đều rỗng, nên thông tin biểu diễn đúng dãy ban đầu. Với một cập nhật phủ toàn bộ nút, thêm nhãn mới vào sau nhãn cũ bổ sung đúng phép biến đổi cho mọi phần tử của đoạn đó.

Khi đẩy nhãn cha xuống con, mỗi phần tử vẫn nhận cùng các phép biến đổi theo cùng thứ tự; chỉ nơi lưu nhãn thay đổi. Nhờ đẩy trước khi đi xuống, một cập nhật cũ ở cha luôn được chuyển xuống trước cập nhật mới tác động riêng lên con. Bất biến về các phép biến đổi được duy trì sau mọi cập nhật và mọi lần đẩy.

Khi đến lá được hỏi, các nhãn của tổ tiên đã được truyền xuống. Nhãn tại lá vì thế biểu diễn đúng toàn bộ cập nhật tác động lên vị trí này theo thứ tự. Áp dụng nó lên giá trị ban đầu cho đúng giá trị hiện tại cần in.

### Độ phức tạp

Dựng các mảng cần $O(N)$ thời gian. Mỗi cập nhật đoạn hoặc hỏi một vị trí mất $O(\log N)$ thời gian, tổng cộng $O(N+Q\log N)$. Bộ nhớ là $O(N)$.

### Lưu ý cài đặt

Chỉ cần gộp các ngưỡng trên từng nút; khi hỏi mới áp dụng ngưỡng vào giá trị ban đầu ở lá. Bài chỉ hỏi từng vị trí, nên không cần lưu tổng hay cực trị trên đoạn.
