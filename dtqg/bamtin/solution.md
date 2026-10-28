# Lời giải BAMTIN — Bám tín hiệu di động

## Quy hoạch động theo vị trí cuối

Đặt $F_i(x)$ là tổng chi phí nhỏ nhất tới thời điểm $i$ với vị trí cuối bằng $x$. Vị trí đầu được chọn tự do, nên trước thời điểm đầu ta có hàm chi phí bằng $0$ trên toàn trục.

Từ $-U_{i-1}\le x-y\le V_{i-1}$, vị trí trước đó phải nằm trong $[x-V_{i-1},x+U_{i-1}]$. Do đó:

$$F_i(x)=\max(L_i-x,0)+\max(x-R_i,0)+\min_{x-V_{i-1}\le y\le x+U_{i-1}}F_{i-1}(y).$$

Với $i=1$, chỉ cộng khoảng cách tới vùng tín hiệu đầu. Không cố định vị trí khởi đầu tại $0$.

## Biểu diễn bằng hai heap

Giữ hàm lồi dưới dạng

$$F(x)=M+\sum_{a\in Q_L}\max(a-x,0)+\sum_{b\in Q_R}\max(x-b,0),$$

với mọi điểm bên trái không lớn hơn mọi điểm bên phải. $Q_L$ là max-heap, $Q_R$ là min-heap, $M$ là giá trị nhỏ nhất. Khoảng giữa hai đỉnh heap là tập vị trí tối ưu; nếu một heap rỗng thì phía tương ứng không bị chặn.

Khi cộng $\max(a-x,0)$, nếu điểm nhỏ nhất bên phải $b<a$, chuyển điểm $b$ sang heap trái, đưa $a$ vào heap phải và tăng $M$ thêm $a-b$. Nếu không thì chỉ thêm $a$ vào heap trái. Phép cộng $\max(x-a,0)$ làm đối xứng qua hai heap.

Vì khoảng cách tới đoạn bằng tổng hai hàm một phía, mỗi vùng tín hiệu chỉ cần hai thao tác này.

## Lấy min trên cửa sổ bằng độ dịch lazy

Xét $G(x)=\min_{x-V\le y\le x+U}F(y)$. Ở nhánh giảm, giá trị tốt nhất được lấy xa hơn về bên phải tối đa $U$; ở nhánh tăng, lấy xa hơn về bên trái tối đa $V$. Khoảng cực tiểu vì vậy mở rộng, và các điểm gãy được biến đổi:

- Mọi điểm trong heap trái giảm $U$.
- Mọi điểm trong heap phải tăng $V$.
- Giá trị nhỏ nhất $M$ giữ nguyên.

Dùng hai biến lazy thay vì sửa từng phần tử. Khi chèn hoặc lấy đỉnh heap, quy đổi giữa tọa độ thật và tọa độ đã trừ lazy. Hai độ dịch khác nhau; đổi chỗ $U,V$ hoặc đổi dấu sẽ làm sai trường hợp chuyển động bất đối xứng.

## Chứng minh đúng

Truy hồi DP xét đủ mọi vị trí trước có thể tới $x$. Hàm khởi đầu bằng $0$, các hàm cộng thêm là hàm lồi tuyến tính từng đoạn. Phép min trên cửa sổ giữ tính lồi và có tác dụng dịch hai nhánh như trên. Quy tắc hai heap bảo toàn biểu diễn khi cộng các hàm một phía. Theo quy nạp, sau mỗi thời điểm hai heap biểu diễn chính xác $F_i$. Vị trí cuối không bị cố định nên đáp án là giá trị nhỏ nhất $M$.

## Độ phức tạp và phương án chậm

- Mỗi thời điểm có một lần dịch lazy và hai thao tác heap: $O(N\log N)$ thời gian, $O(N)$ bộ nhớ.
- Chọn robot đứng tại $0$ trong mọi thời điểm luôn hợp lệ và tốn không quá $N\cdot10^9\le2\cdot10^{14}$; dùng số nguyên 64 bit.
- Độ dịch cộng dồn có thể tới $2\cdot10^{14}$. Không dùng `int` cho tọa độ lưu trong heap.
- Khi miền tọa độ nhỏ, có thể DP theo từng tọa độ. Min cửa sổ của một lớp được tính bằng deque trong thời gian tuyến tính theo độ rộng miền.
- Có thể giới hạn nghiệm tối ưu vào $[\min L_i,\max R_i]$: phép chiếu mọi vị trí vào đoạn này không tăng chi phí và không làm tăng độ dịch theo bất kỳ hướng nào.

## Kiểm chứng độc lập

Oracle lưu toàn bộ các bước nhảy của đạo hàm trong một treap, lấy min cửa sổ bằng tách tổng khối lượng ở mức đạo hàm $0$ rồi dịch hai phần. Biểu diễn này khác hai heap của lời giải mẫu. Khi miền tọa độ đủ nhỏ, còn đối chiếu với DP theo tọa độ và deque. Các tổng trung gian trong biểu diễn đạo hàm có thể lớn dù đáp án nhỏ; oracle dùng số nguyên 128 bit cho các tổng này.
