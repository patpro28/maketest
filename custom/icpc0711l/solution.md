## Chu trình và đường đi trong khoảng cách cây

Với tập đỉnh đen được hỏi, gọi $W$ là tổng trọng số cây con nhỏ nhất nối tất cả chúng, và $D$ là khoảng cách lớn nhất giữa hai đỉnh đen.

- Chu trình ngắn nhất có độ dài $2W$.
- Đường đi ngắn nhất có độ dài $2W-D$.

Một chu trình phải đi qua mỗi cạnh của cây nối ít nhất hai lần. Duyệt cây nối rồi bỏ qua các đỉnh trung gian không cần thăm đạt đúng tổng $2W$ trong đồ thị khoảng cách.

Với đường đi có hai đầu $s,t$, các cạnh ngoài đường $s\leadsto t$ phải đi ít nhất hai lần; các cạnh trên đường đó ít nhất một lần. Cận dưới là $2W-d(s,t)\ge2W-D$. Chọn hai đầu của một đường kính, đi một lần theo đường kính và đi-về các nhánh còn lại đạt cận dưới. Khi chuyển hành trình thành thứ tự thăm các đỉnh đen, bất đẳng thức tam giác cho phép bỏ các lần lặp mà không tăng độ dài.

## Thứ tự DFS và đoạn liên tiếp

Đánh số các đỉnh theo thời điểm vào DFS. Cây con gốc $u$ là đoạn $[tin_u,tout_u)$. Với các đỉnh đen $v_1,\ldots,v_k$ theo thứ tự DFS,

$$2W=\sum_{i=1}^{k-1}d(v_i,v_{i+1})+d(v_k,v_1).$$

Mỗi cạnh trong cây nối chia tập đỉnh đen thành hai phía. Các đỉnh thuộc phía cây con tạo thành một đoạn trong thứ tự DFS, nên chu trình trên vượt qua lát cắt đó đúng hai lần. Cộng theo từng cạnh chứng minh đẳng thức.

## Thông tin trong segment tree

Mỗi nút lưu:

- đỉnh đen đầu và cuối theo thứ tự DFS;
- tổng khoảng cách giữa các đỉnh đen liên tiếp, chưa nối cuối về đầu;
- hai đầu một đường kính của tập đỉnh đen cùng độ dài đường kính.

Ghép hai đoạn kề nhau bằng cách nối đỉnh cuối của đoạn trái với đỉnh đầu của đoạn phải. Đường kính của hợp hai tập là lớn nhất trong hai đường kính cũ và bốn khoảng cách giữa các đầu mút của chúng.

Tính chất được dùng: trong khoảng cách cây, với hai đầu $a,b$ của một đường kính của tập $S$, một điểm xa nhất trong $S$ tính từ đỉnh bất kỳ luôn có thể chọn là $a$ hoặc $b$. Có thể thấy điều này bằng cách chiếu các điểm lên đường $a\leadsto b$: độ dài nhánh rẽ của mọi điểm bị chặn bởi việc nó không thể tạo khoảng cách lớn hơn đường kính tới $a$ hoặc $b$. Áp dụng tính chất này lần lượt cho hai tập chứng minh chỉ cần bốn cặp đầu mút khi ghép.

Nút rỗng là phần tử trung hòa. Đổi màu là cập nhật điểm. Truy vấn cây con là truy vấn đoạn, giữ đúng thứ tự trái-phải vì tổng đường nối không giao hoán. Sau khi ghép, nối đỉnh cuối về đầu để lấy $2W$; với loại $3$, trừ thêm đường kính.

## Tính khoảng cách và độ phức tạp

Tiền xử lý LCA bằng dãy Euler đầy đủ và sparse table truy vấn độ sâu nhỏ nhất. Khi đó

$$d(u,v)=distRoot_u+distRoot_v-2distRoot_{LCA(u,v)}$$

được tính trong $O(1)$. DFS dùng ngăn xếp tường minh để xử lý được cây dạng đường thẳng.

Tiền xử lý $O(N\log N)$ thời gian và bộ nhớ; mỗi thao tác $O(\log N)$. Tổng thời gian $O(N\log N+Q\log N)$. Trọng số và độ dài phải dùng số nguyên 64 bit.
