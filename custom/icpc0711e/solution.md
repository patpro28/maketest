## Phân loại thành phần của đồ thị gốc

Dùng BFS hoặc DFS để đếm:

- $z$: số đỉnh cô lập;
- $b$: số thành phần có cạnh và là đồ thị hai phía;
- $o$: số thành phần không hai phía.

Một đỉnh $(u,v)$ của $GG$ cô lập nếu ít nhất một tọa độ là đỉnh cô lập của $G$. Có $2Nz-z^2$ đỉnh như vậy.

Với hai thành phần có cạnh $C,D$ của $G$, tích $C\times D$ có hai thành phần liên thông nếu cả $C,D$ đều hai phía, và có một thành phần nếu ít nhất một thành phần không hai phía. Các cặp thành phần có thứ tự, vì hai tọa độ có vai trò riêng. Kết quả:

$$2Nz-z^2+2b^2+2bo+o^2.$$

## Vì sao tích có một hoặc hai thành phần?

Một bước trong đồ thị tích di chuyển đồng thời trên cả hai tọa độ. Do đó hai đỉnh trong tích nối được với nhau khi có hai hành trình cùng độ dài giữa các tọa độ tương ứng.

Trong thành phần hai phía, tính chẵn lẻ của độ dài hành trình giữa hai đỉnh được xác định bởi màu của chúng. Có thể thêm một lượt đi rồi quay lại trên cạnh để tăng độ dài thêm $2$. Khi cả hai thành phần hai phía, XOR của hai màu là bất biến, chia tích thành đúng hai nhóm liên thông.

Một thành phần không hai phía có chu trình lẻ, kể cả khuyên nếu đầu vào có khuyên. Có thể đi vòng qua chu trình lẻ để đổi tính chẵn lẻ của hành trình, rồi chèn các bước đi-về để đồng bộ hai độ dài. Vì thế tích liên thông khi ít nhất một tọa độ thuộc thành phần không hai phía.

Các tích của các cặp thành phần gốc khác nhau không nối được với nhau. Cộng đóng góp của chúng và các đỉnh cô lập chứng minh công thức.

## Độ phức tạp

$O(N+M)$ thời gian và bộ nhớ. Dùng số nguyên 64 bit vì đáp án có thể đạt $N^2$. Duyệt không đệ quy để tránh tràn ngăn xếp.
