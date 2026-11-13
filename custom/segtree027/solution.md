## Xét hai hướng chênh lệch

Gọi $m_1,M_1$ là cực tiểu và cực đại của khu vực thứ nhất. Tương tự, gọi $m_2,M_2$ là hai cực trị của khu vực thứ hai.

Với $i$ thuộc khu vực thứ nhất và $j$ thuộc khu vực thứ hai, chênh lệch theo hướng $A_i-A_j$ lớn nhất là $M_1-m_2$. Cặp giá trị này luôn chọn được vì $M_1$ và $m_2$ xuất hiện trong hai khu vực tương ứng. Theo hướng còn lại, $A_j-A_i$ lớn nhất là $M_2-m_1$. Do $|A_i-A_j|=\max(A_i-A_j,A_j-A_i)$, kết quả là

$$\max(M_1-m_2,M_2-m_1).$$

## Cây đoạn

Dựng một cây đoạn trên $A$, lưu min và max tại mỗi nút. Nút cha lấy min của hai cực tiểu và max của hai cực đại. Khi gán tại một vị trí, sửa lá tương ứng rồi tính lại các nút trên đường lên gốc.

Khi truy vấn một khu vực, ghép các nút phủ đúng khu vực đó để lấy min và max. Hai lần truy vấn cung cấp đủ bốn cực trị. Áp dụng công thức trên cho đúng chênh lệch lớn nhất của một cặp vị trí thuộc hai khu vực.

## Độ phức tạp

Dựng cây trong $O(N)$. Mỗi lần gán và mỗi lần hỏi tốn $O(\log(N+1))$. Bộ nhớ là $O(N)$.
