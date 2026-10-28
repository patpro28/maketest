# Lời giải CANMANG — Cân chỉnh mạng cảm biến

## DP hàm trên cây

Chọn một gốc bất kỳ. Gọi $F_u(x)$ là chi phí nhỏ nhất của cây con $u$ khi cảm biến $u$ nhận giá trị $x$.

Nếu $v$ là con của $u$, giới hạn cạnh yêu cầu giá trị $y$ tại $v$ thuộc $[x-D_{uv},x+D_{uv}]$. Vì các cây con độc lập khi cố định $x$:

$$F_u(x)=|x-A_u|+\sum_{v\text{ là con của }u}\min_{x-D_{uv}\le y\le x+D_{uv}}F_v(y).$$

Ở lá, $F_u(x)=|x-A_u|$. Đáp án là $\min_xF_{\text{root}}(x)$; giá trị tại gốc không được cố định bằng $0$ hay bằng $A_{\text{root}}$.

## Slope trick cho từng cây con

Dùng biểu diễn hai heap như BAMTIN:

$$F(x)=M+\sum_{a\in Q_L}(a-x)_++\sum_{b\in Q_R}(x-b)_+.$$

Với mỗi con $v$:

1. Áp dụng min cửa sổ bán kính $D_{uv}$: dịch mọi điểm heap trái đi $-D_{uv}$, heap phải đi $+D_{uv}$; giữ nguyên $M$.
2. Cộng hàm đã biến đổi vào hàm của $u$.

Sau khi gộp mọi con, cộng $|x-A_u|$ bằng hai hàm một phía.

## Gộp hai hàm

Muốn cộng $F$ và $G$, cộng hằng số cực tiểu của $G$, rồi lần lượt thêm các hàm một phía tương ứng với mọi điểm gãy của $G$ vào $F$. Mỗi lần thêm có thể làm tăng cực tiểu và chuyển điểm gãy giữa hai heap để giữ biểu diễn chuẩn.

Tọa độ dùng khi chuyển phải là tọa độ thật: giá trị lưu cộng với lazy riêng của heap nguồn. Không được chuyển trực tiếp giá trị đã trừ lazy của cây con khác. Hai hàm có thể đang mang các độ dịch rất khác nhau.

Luôn chọn hàm có nhiều điểm gãy hơn làm nơi nhận, chuyển hàm nhỏ vào hàm lớn. Mỗi đỉnh thêm đúng hai điểm gãy; mỗi lần một điểm thuộc hàm được chuyển, kích thước hàm chứa nó ít nhất tăng gấp đôi. Do đó mỗi điểm bị chuyển $O(\log N)$ lần. Mỗi lần chèn vào heap mất $O(\log N)$.

## Chứng minh đúng

Ở lá, cộng hai hàm một phía biểu diễn chính xác trị tuyệt đối. Giả sử các hàm của mọi con đều đúng. Phép dịch hai heap thực hiện đúng min trên cửa sổ của cạnh. Các cây con không có cạnh chéo, nên tổng các hàm sau biến đổi cộng với chi phí tại $u$ bằng đúng truy hồi DP. Phép gộp và thêm trị tuyệt đối bảo toàn hàm này. Theo quy nạp, hàm tại gốc đúng; lấy giá trị nhỏ nhất cho đáp án tối ưu toàn cây.

## Độ phức tạp và cài đặt

- Thời gian $O(N\log^2N)$, bộ nhớ $O(N)$.
- Duyệt cây bằng mảng thứ tự, xử lý ngược từ lá lên để tránh đệ quy theo chiều cao cây. Cây có thể là đường thẳng dài $10^5$ đỉnh.
- Sau khi gộp một hàm con, giải phóng đối tượng đó để không giữ bộ nhớ các heap cũ đã rút hết phần tử.
- Chọn mọi $X_u=0$ luôn hợp lệ, nên đáp án không vượt $N\cdot10^9\le10^{14}$. Dùng `long long` cho chi phí, điểm gãy và lazy cộng dồn.
- $D=0$ buộc hai đầu nhận cùng giá trị, không có nghĩa là bỏ qua cạnh.

## Phương án chậm và kiểm chứng

Chiếu mọi giá trị vào $[\min A_u,\max A_u]$ không tăng chi phí và giữ mọi giới hạn cạnh. Khi khoảng này nhỏ, có thể DP theo mọi tọa độ nguyên. Với mỗi con, deque tính min cửa sổ trong một lượt quét; tổng thời gian $O(NV)$ với $V$ là độ rộng miền.

Oracle sử dụng biểu diễn toàn bộ bước nhảy đạo hàm trong treap, tách theo tổng khối lượng để lấy min cửa sổ và hợp nhất các tập bước nhảy để cộng hàm. Nó không sử dụng hai heap, phép thêm hàm một phía hay quy tắc chuẩn hóa heap của lời giải mẫu. Khi miền nhỏ, cả oracle treap và lời giải mẫu được đối chiếu với DP tọa độ. Tổng trung gian trong oracle dùng số nguyên 128 bit.
