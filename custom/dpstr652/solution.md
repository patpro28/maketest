## Trạng thái và ký hiệu

Đặt $F[L][R]$ là số **nội dung** dãy con đối xứng không rỗng phân biệt trong đoạn $S[L\ldots R]$. Đoạn rỗng có giá trị $0$, đoạn một ký tự có giá trị $1$. Mọi giá trị lấy modulo $10^9+7$.

Nếu $S_L\ne S_R$:

$$F[L][R]=F[L+1][R]+F[L][R-1]-F[L+1][R-1].$$

Nếu hai đầu cùng là chữ $c$, đặt $I=F[L+1][R-1]$. Gọi $p$ là vị trí xuất hiện đầu tiên của $c$ sau $L$, $q$ là vị trí xuất hiện cuối cùng của $c$ trước $R$.

- Không có chữ $c$ ở trong, tức $p>q$: $F[L][R]=2I+2$.
- Có đúng một chữ $c$ ở trong, tức $p=q$: $F[L][R]=2I+1$.
- Có ít nhất hai chữ $c$ ở trong, tức $p<q$: $F[L][R]=2I-F[p+1][q-1]$.

Tiền xử lý lần xuất hiện cùng chữ tiếp theo và trước đó cho mỗi vị trí bằng hai lượt quét. Khi tính một ô, lấy $p=next[L]$ và $q=prev[R]$ trong $O(1)$.

## Vì sao không đếm trùng

Nếu hai đầu khác nhau, mọi nội dung đối xứng phải xuất hiện trong ít nhất một đoạn bỏ một đầu. Một nội dung xuất hiện ở cả hai đoạn nhưng không xuất hiện trong đoạn trong sẽ phải có ký tự đầu là $S_L$ và ký tự cuối là $S_R$, mâu thuẫn với đối xứng. Vì vậy giao hai tập nội dung đúng bằng tập của đoạn trong, cho phép dùng công thức cộng–trừ.

Nếu hai đầu là $c$, từ các nội dung ở trong có thể giữ nguyên hoặc bọc thêm hai chữ $c$, rồi thêm riêng `c` và `cc`. Không có $c$ ở trong thì các nhóm nội dung này rời nhau, cho $2I+2$. Có đúng một $c$ thì chỉ `c` bị trùng, còn $2I+1$.

Nếu có ít nhất hai $c$, các nội dung đã có ở trong mà đồng thời thuộc nhóm mới bắt đầu và kết thúc bằng $c$ gồm `c`, `cc` và mọi xâu $cTc$ với $T$ là nội dung đối xứng trong đoạn giữa $p,q$. Chọn hai lần xuất hiện ngoài cùng $p,q$ biểu diễn được mọi nội dung loại này. Vì vậy phải trừ $2+F[p+1][q-1]$ khỏi $2I+2$, được công thức cuối. Quy nạp theo độ dài đoạn cho toàn bộ bảng đúng.

## Độ phức tạp và cài đặt

Thời gian $O(N^2)$, tối đa $12502500$ ô chính; bộ nhớ $O(N^2)$. Cần giữ cả bảng vì ô bị trừ có thể nằm ở đoạn bất kỳ bên trong. Với $N=5000$, dùng số nguyên 32 bit sau khi lấy dư cho bảng $100000000$ byte, phù hợp giới hạn $128$ MiB. Dùng 64 bit cho biểu thức trung gian và chuẩn hóa số dư sau phép trừ; đoạn trong rỗng có giá trị $0$.
