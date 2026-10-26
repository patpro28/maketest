# Lời giải — HASHING001

Nếu $m>n$, trả về $0$. Nếu $m=1$, mọi vị trí của $A$ đều phù hợp vì có thể chọn $c=A_i-B_1$, nên đáp án bằng $n$.

Với $m\ge2$, đặt $D_i=A_{i+1}-A_i$ và $E_j=B_{j+1}-B_j$. Một đoạn của $A$ là bản chuyển tông của $B$ khi và chỉ khi dãy hiệu tương ứng bằng toàn bộ $E$. Chiều thuận có được bằng cách trừ hai đẳng thức kề nhau; chiều ngược có được bằng cách chọn $c$ từ phần tử đầu rồi cộng dồn các hiệu.

Tính hash kép của các dãy hiệu và so sánh từng cửa sổ dài $m-1$. Dùng số nguyên 64 bit khi tính hiệu; chuẩn hóa số âm trước khi lấy modulo.

Độ phức tạp $O(n+m)$, bộ nhớ $O(n+m)$.

Lời giải tham khảo dùng hai modulo khác nhau để giảm xác suất va chạm hash. Hash là kỹ thuật xác suất; chứng minh tính đúng đắn ở trên giả sử các đoạn được so sánh không va chạm.
