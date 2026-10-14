# Lời giải

Từ phiên bản dễ, ta biết rằng trong một phương án tối ưu, mỗi đỉnh không phải lá có điểm số bằng $2$: các đỉnh kề với nó chứa đủ cả hai màu khác với màu của nó. Mỗi đỉnh lá có điểm số bằng $3$: đỉnh kề với nó có màu khác, và một đỉnh kề với đỉnh đó mang màu thứ ba.

Để đếm số cách tô màu, ta sử dụng quy hoạch động trên cây.

## Trạng thái quy hoạch động

Chọn một đỉnh làm gốc và xét các cây con theo cách thông thường. Giả sử ta đang tô màu đỉnh $u$ sau khi đã xử lý tất cả các đỉnh con của nó.

Gọi một đỉnh là **thỏa mãn** nếu cách tô màu hiện tại đã giúp đỉnh đó đạt điểm số nhỏ nhất có thể.

Lúc này, mọi đỉnh trong cây con của $u$, ngoại trừ chính $u$, đều đã được tô màu. Những đỉnh còn có thể chưa thỏa mãn chỉ là một số đỉnh con trực tiếp của $u$: việc tô màu $u$ không thể giúp một đỉnh ở sâu hơn trở nên thỏa mãn.

Có một ngoại lệ là các đỉnh lá nằm cách $u$ đúng $2$ cạnh. Tuy nhiên, một đỉnh lá như vậy thỏa mãn khi và chỉ khi cha của nó cũng thỏa mãn. Vì đỉnh cha đó là con trực tiếp của $u$, ta vẫn chỉ cần xét các đỉnh con trực tiếp của $u$.

Nếu một đỉnh con $v$ của $u$ chưa thỏa mãn, màu của $u$ sẽ được xác định duy nhất bởi yêu cầu của $v$, vì $u$ phải giúp $v$ trở nên thỏa mãn. Do đó, tất cả các đỉnh con chưa thỏa mãn của $u$ phải yêu cầu cùng một màu cho $u$.

Như vậy, ta cần lưu hai loại thông tin:

- Màu của đỉnh đang xét.
- Đỉnh đó đã thỏa mãn hay chưa; nếu chưa thì nó yêu cầu cha mang màu nào.

Đánh số ba màu là $1,2,3$. Ta có thể định nghĩa $\text{dp}[u][c_1][c_2]$ là số cách tô màu toàn bộ cây con của $u$ sao cho $u$ mang màu $c_1$ và cha của $u$ phải mang màu $c_2$. Nếu không có yêu cầu về màu của cha, đặt $c_2=0$.

Trạng thái này dùng được, nhưng có thể rút gọn đáng kể nhờ tính đối xứng giữa các màu. Với một đỉnh $u$ cố định:

- $\text{dp}[u][1][0]=\text{dp}[u][2][0]=\text{dp}[u][3][0]$. Dù chọn màu nào cho $u$, số cách tô cây con để mọi đỉnh đều thỏa mãn là như nhau.
- $\text{dp}[u][x][x]=0$. Nếu $u$ chưa thỏa mãn và mang màu $x$, cha của nó phải mang một màu khác $x$.
- Mọi giá trị $\text{dp}[u][x][y]$ với $x\ne y$ và $y>0$ đều bằng nhau. Chẳng hạn, tô $u$ màu đỏ và yêu cầu cha màu xanh lá không khác gì tô $u$ màu đỏ và yêu cầu cha màu xanh dương.

Vì vậy, ta chỉ cần lưu hai giá trị:

- $\text{dp}[u][0]$: số cách tô cây con của $u$ sao cho mọi đỉnh đều thỏa mãn.
- $\text{dp}[u][1]$: số cách tô cây con của $u$ sao cho $u$ chưa thỏa mãn và có một yêu cầu xác định về màu của cha.

Giá trị thứ nhất bằng $3$ lần $\text{dp}[u][1][0]$ của trạng thái ba chiều ở trên. Giá trị thứ hai bằng $6$ lần $\text{dp}[u][1][2]$ của trạng thái đó.

## Chuyển trạng thái

### Tính $\text{dp}[u][1]$

Giả sử $u$ mang màu đỏ và chưa thỏa mãn. Khi đó, màu xanh lá và xanh dương không thể đồng thời xuất hiện trong các đỉnh con của $u$.

Trước hết, xét trường hợp trong hai màu này chỉ có màu xanh lá xuất hiện ở các đỉnh con; màu đỏ vẫn có thể xuất hiện. Khi ấy, cha của $u$ phải mang màu xanh dương.

Với mỗi đỉnh con $v$ của $u$:

- Nếu $v$ đã thỏa mãn, có $\text{dp}[v][0]\cdot\frac{2}{3}$ cách tô sao cho $v$ mang màu đỏ hoặc xanh lá.
- Nếu $v$ chưa thỏa mãn, có $\text{dp}[v][1]\cdot\frac{1}{6}$ cách tô sao cho $v$ mang màu xanh lá và yêu cầu cha của nó mang màu đỏ.

Ta còn phải bảo đảm có ít nhất một đỉnh con mang màu xanh lá. Do đó, cần trừ đi số cách mà tất cả các đỉnh con đều mang màu đỏ.

Số cách tô các đỉnh bên dưới $u$ sao cho $u$ mang màu đỏ và yêu cầu cha mang màu xanh dương là:

$$
\prod_v\left(\text{dp}[v][0]\cdot\frac{2}{3}
+\text{dp}[v][1]\cdot\frac{1}{6}\right)
-\prod_v\left(\text{dp}[v][0]\cdot\frac{1}{3}\right).
$$

Các tích ở đây được lấy trên tất cả các đỉnh con $v$ của $u$.

Có $3$ cách chọn màu cho $u$ và $2$ cách chọn màu mà $u$ yêu cầu cha phải mang. Vì vậy:

$$
\text{dp}[u][1]
=6\left[
\prod_v\left(\text{dp}[v][0]\cdot\frac{2}{3}
+\text{dp}[v][1]\cdot\frac{1}{6}\right)
-\prod_v\left(\text{dp}[v][0]\cdot\frac{1}{3}\right)
\right].
$$

### Tính $\text{dp}[u][0]$

Ta cũng cố định màu của $u$ là đỏ và xét từng đỉnh con $v$:

- Nếu $v$ đã thỏa mãn, nó có thể mang bất kỳ màu nào, nên có $\text{dp}[v][0]$ cách.
- Nếu $v$ chưa thỏa mãn, có $\text{dp}[v][1]\cdot\frac{1}{3}$ cách mà $v$ yêu cầu cha mang màu đỏ.

Như vậy, số cách tô thu được là:

$$
\prod_v\left(\text{dp}[v][0]
+\text{dp}[v][1]\cdot\frac{1}{3}\right).
$$

Nhân giá trị này với $3$ để tính cả trường hợp $u$ mang màu xanh lá hoặc xanh dương.

Tuy nhiên, không phải mọi cách tô vừa đếm đều hợp lệ, nên cần trừ đi các trường hợp mà $u$ chưa thỏa mãn:

- Tất cả các cách tô đã được đếm trong $\text{dp}[u][1]$ đều không hợp lệ đối với trạng thái này, nên ta trừ $\text{dp}[u][1]$.
- Các cách tô mà $u$ và tất cả các đỉnh con của nó cùng màu cũng không hợp lệ. Chúng chưa được đếm trong $\text{dp}[u][1]$, nên phải trừ riêng. Với mỗi đỉnh con $v$, có $\text{dp}[v][0]\cdot\frac{1}{3}$ cách để $v$ mang cùng màu với $u$. Lấy tích các giá trị này rồi nhân với $3$ để tính đủ ba màu của $u$.

Do đó:

$$
\text{dp}[u][0]
=3\prod_v\left(\text{dp}[v][0]
+\text{dp}[v][1]\cdot\frac{1}{3}\right)
-\text{dp}[u][1]
-3\prod_v\left(\text{dp}[v][0]\cdot\frac{1}{3}\right).
$$

Đáp án cuối cùng là $\text{dp}[\text{root}][0]$, vì sau khi tô xong toàn bộ cây, đỉnh gốc phải thỏa mãn.

## Lưu ý về các đỉnh lá

Trong quá trình xây dựng công thức ở trên, ta chưa xử lý riêng các đỉnh lá. Có hai chi tiết cần lưu ý:

1. Chọn gốc là một đỉnh không phải lá, tức là đỉnh có bậc lớn hơn $1$. Nếu gốc là lá, việc nó có thỏa mãn hay không sẽ phụ thuộc vào các đỉnh cách nó $2$ cạnh, trong khi trạng thái quy hoạch động hiện tại không xử lý trực tiếp tình huống này. Chọn gốc không phải lá giúp tránh vấn đề đó.
2. Nếu một đỉnh con $v$ của $u$ là lá, các giá trị lấy từ đỉnh đó có thể cần được điều chỉnh so với công thức chung. Phần xử lý cụ thể này được lời giải gốc để lại như một bài tập cho người đọc.

## Độ phức tạp

Độ phức tạp thời gian là $\mathcal{O}(N)$ cho mỗi bộ test.
