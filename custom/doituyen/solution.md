# Lời giải DOITUYEN — Đổi tuyến

## Vì sao một khoảng cách cho mỗi thành phố chưa đủ?

Hai hành trình tới cùng thành phố nhưng dùng hai tuyến cuối khác nhau có thể dẫn tới chi phí tiếp tục khác nhau. Ví dụ 1 cho thấy tới thành phố $2$ lúc $1$ bằng tuyến $10$ kém hơn tới lúc $4$ bằng tuyến $20$ nếu muốn đi tiếp tới $4$.

Ta cần trạng thái $(u,c)$: đang tại thành phố $u$ và đang sử dụng tuyến $c$. Chỉ tạo trạng thái khi $c$ xuất hiện ở đầu vào hoặc đầu ra của ít nhất một chặng tại $u$. Mỗi chặng đóng góp nhiều nhất hai cặp, nên có không quá $2M$ trạng thái như vậy.

## Đồ thị mở rộng

Tạo một đỉnh trung gian $X_u$ cho mỗi thành phố. Với mỗi cặp $(u,c)$, thêm:

- Cung $(u,c)\to X_u$ trọng số $P_u$.
- Cung $X_u\to(u,c)$ trọng số $0$.

Với mỗi chặng $u\to v$, tuyến $c$, thời gian $w$, thêm cung

$$ (u,c)\to(v,c)\quad\text{trọng số }w.$$

Khi giữ nguyên tuyến ở một thành phố, đi thẳng qua trạng thái $(u,c)$, không qua $X_u$. Khi đổi tuyến, đi qua $X_u$ và trả đúng $P_u$. Cách này tránh việc tạo một cung cho mọi cặp tuyến ở cùng thành phố; một thành phố có nhiều tuyến vẫn chỉ cần số cung tuyến tính.

Chạy Dijkstra từ $X_S$, khoảng cách ban đầu bằng $0$. Các cung đi ra từ $X_S$ cho phép lên tuyến đầu tiên miễn phí. Đáp án là khoảng cách nhỏ nhất tới một trạng thái $(T,c)$, hoặc $0$ nếu $S=T$. Không lấy riêng khoảng cách tới $X_T$, vì như vậy có thể tính thừa phí đổi tuyến ở đích.

Cài đặt có thể dừng khi lần đầu chốt một trạng thái nằm tại $T$. Nếu hàng đợi hết mà chưa tới đích, trả $-1$.

## Chứng minh đúng

Mỗi hành trình hợp lệ chuyển thành một đường đi trong đồ thị mở rộng: mỗi chặng ứng với một cung di chuyển; mỗi lần đổi mã tuyến ứng với hai cung qua $X_u$. Lần lên tuyến đầu tiên dùng cung trọng số $0$ từ $X_S$. Tổng trọng số bằng đúng tổng thời gian hành trình. Do đó khoảng cách trong đồ thị mở rộng không lớn hơn đáp án thật.

Ngược lại, lấy các cung di chuyển trên một đường đi từ $X_S$ tới trạng thái tại $T$. Chúng tạo thành hành trình hợp lệ từ $S$ tới $T$. Mỗi lần hai chặng liên tiếp khác mã tuyến, đường đi bắt buộc đã qua đỉnh trung gian và trả phí. Nếu đường đi trả phí rồi chọn lại cùng mã tuyến, bỏ khoản đổi tuyến không cần thiết chỉ làm thời gian giảm hoặc giữ nguyên. Vì vậy đáp án thật không lớn hơn khoảng cách tối ưu trong đồ thị mở rộng. Kết hợp hai chiều, hai đáp án bằng nhau.

Mọi trọng số không âm, nên Dijkstra tính đúng khoảng cách nhỏ nhất.

## Độ phức tạp và lưu ý

- Sắp xếp rồi loại trùng các cặp $(u,c)$ để đánh số trạng thái; tra mã bằng tìm kiếm nhị phân.
- Có nhiều nhất $N+2M$ đỉnh và $5M$ cung.
- Tổng thời gian $O((N+M)\log(N+M))$; bộ nhớ $O(N+M)$.
- Dùng số nguyên có dấu $64$ bit. Một đường đi ngắn nhất có thể chọn không lặp đỉnh trong đồ thị mở rộng; tổng thời gian nhỏ hơn $6\cdot10^{14}$.
- Không nén chỉ theo mã tuyến toàn cục: hai thành phố dùng cùng mã vẫn là hai trạng thái khác nhau.
- Chặng có hướng, chặng trùng và chặng tự khép đều được giữ đúng như đầu vào.

## Hướng kiểm chứng chậm

Cho mỗi chặng một trạng thái tương ứng với chặng vừa đi. Từ trạng thái chặng $e$, thử từng chặng đi ra khỏi đích của $e$, cộng thời gian và phí nếu khác tuyến. Khởi tạo mọi chặng đi ra từ $S$ bằng thời gian chặng đó. Dijkstra trên mô hình này có thể mất $O(M^2\log M)$ nhưng phù hợp để đối chiếu dữ liệu nhỏ và vừa.
