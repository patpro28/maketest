Gọi $F[i]$ là số cách chia tiền tố dài $i$ và đặt $F[0]=1$. Khi tính $F[i]$, thử mỗi độ dài $d$ từ $1$ đến $\min(i,K)$. Nếu $S_{i-d+1}=S_i$ thì cộng $F[i-d]$ vào $F[i]$ theo modulo.

Mảnh cuối của mỗi cách chia xác định duy nhất $d$. Sau khi bỏ mảnh cuối, phần còn lại là một cách chia tiền tố dài $i-d$. Ngược lại có thể nối mảnh cuối vào mọi cách chia tiền tố đó, nên mỗi cách được tính đúng một lần.

Thời gian $O(NK)$ và bộ nhớ $O(N)$.
