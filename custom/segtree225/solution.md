### Tách đoạn vòng

Dựng segment tree trên dãy thẳng theo thứ tự từ $1$ đến $n$.

- Nếu $l\le r$, đoạn vòng là đoạn thẳng $[l,r]$.
- Nếu $l>r$, đoạn vòng là hợp của hai đoạn rời nhau $[l,n]$ và $[1,r]$.

Một cập nhật qua biên cần cộng cùng lượng $x$ vào cả hai đoạn. Một truy vấn qua biên lấy max của hai kết quả.

### Cộng và lấy max trên một đoạn thẳng

Mỗi nút lưu tải lớn nhất của đoạn và nhãn cộng đang chờ. Khi toàn nút được cộng thêm $x$, tăng cả giá trị lớn nhất và nhãn chờ thêm $x$. Trước khi xử lý một phần đoạn, đẩy nhãn xuống hai nút con. Sau khi cập nhật một phần, lấy max của hai nút con để khôi phục giá trị của nút cha. Truy vấn lấy max của các nút phủ đúng đoạn thẳng cần hỏi.

### Chứng minh tính đúng đắn

Với một đoạn thẳng, lấy max của hai nút con cho đúng tải lớn nhất của đoạn ghép. Khi mọi tải trong đoạn cùng tăng $x$, tải lớn nhất tăng đúng $x$. Nhãn chờ bảo đảm các nút con nhận được lượng cộng trước khi được sử dụng. Vì thế cây trả về đúng max của từng đoạn thẳng.

Khi đoạn vòng qua biên, hai đoạn thẳng phủ đúng các trạm cần xét và không chung vị trí. Cập nhật hai đoạn làm mỗi trạm trên đoạn vòng nhận $x$ đúng một lần. Tải lớn nhất trên đoạn vòng là max của tải lớn nhất trên hai đoạn thẳng. Trường hợp $l=r$ được xử lý bằng một đoạn thẳng gồm đúng một vị trí.

### Độ phức tạp

Dựng cây tốn $O(n)$ thời gian. Mỗi thao tác trên vành đai dùng tối đa hai thao tác trên cây và tốn $O(\log(n+1))$ thời gian. Bộ nhớ là $O(n)$. Dùng số nguyên 64 bit cho tải và nhãn cộng.
