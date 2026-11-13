## Thuật toán

Dựng segment tree theo thứ tự các vị trí từ $1$ đến $N$. Lá thứ $i$ lưu $A_i$. Mỗi nút trong lưu tổng hai nút con. Khi cộng $x$ vào một vị trí, sửa lá tương ứng rồi tính lại các tổng trên đường đến gốc.

Với truy vấn từ $l$ đến $r$:

- Nếu $lle r$, lấy tổng đoạn $[l,r]$.
- Nếu $l>r$, lấy tổng hai đoạn $[l,N]$ và $[1,r]$ rồi cộng lại.

## Chứng minh tính đúng đắn

Sau khi dựng cây hoặc cập nhật một lá, tổng của mỗi nút đúng bằng tổng các lá thuộc nút đó. Một truy vấn trên đoạn thẳng trả về đúng tổng vì các nút dùng để trả lời có các đoạn đôi một rời nhau và phủ kín đoạn hỏi.

Khi $lle r$, đường đi chỉ chứa các vị trí $l,l+1,\ldots,r$, trong đó $l=r$ cho đúng một vị trí. Khi $l>r$, đường đi qua các vị trí từ $l$ đến $N$, rồi từ $1$ đến $r$. Hai đoạn này rời nhau, nên cộng hai tổng sẽ tính mỗi vị trí đúng một lần.

## Độ phức tạp

Dựng cây trong $O(N)$. Mỗi thao tác dùng tối đa hai thao tác trên cây, tốn $O(log(N+1))$ thời gian. Bộ nhớ là $O(N)$. Tổng có trị tuyệt đối tối đa $(N+Q)10^9$, nên dùng số nguyên 64 bit.
