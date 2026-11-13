## Đổi thứ tự các phần tử

Gom các vị trí có cùng phần dư $(i-1)\bmod K$ vào một nhóm. Nối các nhóm theo thứ tự phần dư tăng dần và giữ thứ tự chỉ số trong mỗi nhóm. Các vị trí cách nhau đúng $K$ trong dãy gốc sẽ đứng cạnh nhau trong nhóm của chúng.

Đặt $d=\lfloor N/K\rfloor$ và $t=N\bmod K$. Các nhóm có phần dư từ $0$ đến $t-1$ chứa $d+1$ vị trí, các nhóm còn lại chứa $d$ vị trí. Vì vậy, với $s=(i-1)\bmod K$, chỉ số mới của vị trí $i$ là

$$p(i)=s\cdot d+\min(s,t)+\left\lfloor\frac{i-1}{K}\right\rfloor+1.$$

Hai hạng đầu đếm số vị trí thuộc các nhóm trước nhóm $s$. Hạng tiếp theo là vị trí trong nhóm, tính từ $0$.

## Thuật toán và chứng minh

Dựng segment tree tính tổng trên thứ tự mới. Khi gán $A_i=x$, gán lá thứ $p(i)$ bằng $x$ và tính lại các tổng trên đường lên gốc. Mỗi giá trị trong thứ tự mới luôn bằng giá trị của vị trí gốc tương ứng.

Truy vấn từ $l$ đến $r$ chọn đúng $h=\lfloor(r-l)/K\rfloor+1$ vị trí. Chúng nằm trong cùng nhóm và đứng liên tiếp theo thứ tự mới, bắt đầu ở $p(l)$. Vì vậy truy vấn tổng $[p(l),p(l)+h-1]$ trên cây trả về đúng tổng của các phần tử được chọn.

## Độ phức tạp

Tính mỗi chỉ số mới trong $O(1)$ và dựng cây trong $O(N)$. Mỗi thao tác tốn $O(log(N+1))$ thời gian. Bộ nhớ là $O(N)$. Dùng số nguyên 64 bit vì trị tuyệt đối của tổng có thể lên tới $N\cdot10^9$.
