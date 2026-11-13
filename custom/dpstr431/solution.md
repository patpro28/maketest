Tính $P[i]$, phần dư tổng chữ số của tiền tố dài $i$ theo $D$. Đoạn sau tiền tố $j$ và kết thúc tại $i$ hợp lệ khi $P[j]=P[i]$. Gọi $F_t[i]$ là số cách chia tiền tố dài $i$ thành đúng $t$ đoạn. Khi duyệt $i$ tăng trong lớp $t$, duy trì $H[r]$ là tổng $F_{t-1}[j]$ của các vị trí $j<i$ có $P[j]=r$. Khi đó $F_t[i]=H[P[i]]$.

Điểm cắt trước đoạn cuối của một cách chia luôn có $j<i$. Điều kiện phần dư chọn đúng các điểm cắt cho đoạn cuối hợp lệ. Sau khi bỏ đoạn cuối, phần trước có đúng $t-1$ đoạn, nên cộng các trạng thái tương ứng sẽ đếm đúng các cách chia.

Khởi tạo $F_0[0]=1$ và các tiền tố khác bằng $0$. Trước khi tính ô $i$, thêm đúng ô $i-1$ của lớp trước vào bảng tổng. Độ phức tạp $O(K(N+D))$, bộ nhớ $O(N+D)$.
