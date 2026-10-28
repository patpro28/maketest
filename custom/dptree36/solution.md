# Lời giải — Trang trí một nhánh liên thông

### Ba câu hỏi để xây dựng lời giải

**Cần tính gì tại đỉnh $u$?** Gọi $dp[u]$ là số tập đỉnh liên thông nằm hoàn toàn trong cây con của $u$, bắt buộc chứa $u$.

**Một lá trả về gì?** Chỉ có tập $\{u\}$, nên $dp[u]=1$.

**Cha dùng kết quả các con thế nào?** Với người con $v$, có hai lựa chọn rời nhau:

- Không chọn đỉnh nào trong nhánh của $v$: có $1$ cách.
- Chọn một phần của nhánh: để nối với $u$, phần được chọn phải liên thông và chứa $v$, nên có $dp[v]$ cách.

Mỗi nhánh vì thế có $1+dp[v]$ lựa chọn. Các nhánh độc lập nên nhân:

$$
dp[u]=\prod_{v\text{ là con của }u}(1+dp[v])\pmod{10^9+7}.
$$

Đáp án là $dp[1]$.

### Vì sao phải nhân?

Nếu nhánh thứ nhất có $a$ lựa chọn và nhánh thứ hai có $b$ lựa chọn, mỗi lựa chọn của nhánh thứ nhất kết hợp được với mọi lựa chọn của nhánh thứ hai, tạo ra $ab$ cách.

Trên cây sao có gốc và ba lá, mỗi lá cho hai lựa chọn, nên gốc có $2\cdot2\cdot2=8$ cách.

Trên đường $1\to2\to3\to4$, lần lượt có $dp[4]=1$, $dp[3]=2$, $dp[2]=3$, $dp[1]=4$.

Khởi tạo tích bằng $1$, không phải $0$. Lựa chọn bỏ tất cả các nhánh vẫn giữ đỉnh $u$, nên được tính là một tập hợp lệ. Tập rỗng không được tính.

### Chứng minh tính đúng đắn

Tại lá, chỉ tập chứa chính lá là hợp lệ. Giả sử kết quả ở các con đều đúng. Với mỗi nhánh, phần giao của một tập liên thông chứa $u$ với nhánh đó hoặc rỗng, hoặc liên thông và chứa người con trực tiếp. Hai trường hợp cho đúng $1+dp[v]$ cách.

Mỗi tập hợp lệ được tách duy nhất theo các nhánh. Ngược lại, kết hợp những lựa chọn hợp lệ ở các nhánh với đỉnh $u$ luôn tạo thành một tập liên thông. Vì vậy phép nhân đếm đủ và không lặp. Quy nạp đến gốc chứng minh công thức và đáp án.

### Độ phức tạp và lưu ý cài đặt

Thời gian $O(N)$, bộ nhớ $O(N)$. Lưu cha và thứ tự duyệt bằng vòng lặp, sau đó xử lý ngược thứ tự.

Dùng số nguyên 64 bit khi nhân hai số dư và lấy modulo sau mỗi phép nhân. Kết quả sau modulo có thể bằng $0$, điều này không có nghĩa là không có tập hợp lệ.

Bài chỉ hỏi các tập chứa gốc, nên không cộng $dp[u]$ của tất cả các đỉnh vào đáp án.
