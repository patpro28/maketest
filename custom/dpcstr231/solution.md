Gọi $E_t[i][j]$ là độ dài lớn nhất của hai đoạn kết thúc tại $(i,j)$ có không quá $t$ cặp khác nhau. Biên bằng $0$, với $0\le t\le K$.

- Nếu hai ký tự bằng nhau: $E_t[i][j]=E_t[i-1][j-1]+1$.
- Nếu chúng khác nhau và $t>0$: $E_t[i][j]=E_{t-1}[i-1][j-1]+1$.
- Nếu chúng khác nhau và $t=0$: giá trị bằng $0$.

Một cặp cuối bằng nhau không tiêu thụ lỗi; một cặp khác nhau tiêu thụ đúng một lỗi. Bỏ cặp cuối của mọi phương án hợp lệ đưa về đúng trạng thái được nêu trong công thức, và nối cặp cuối vào trạng thái ấy luôn hợp lệ. Vì vậy quy nạp cho thấy DP lưu đúng độ dài lớn nhất. Đáp án là giá trị lớn nhất của lớp $K$ trên mọi cặp vị trí.

Có thể nén chỉ số $i$ và duyệt $j$ giảm dần. Trạng thái là không quá $t$ lỗi nên tất cả các lớp ở biên đều bằng $0$.

Độ phức tạp thời gian $O(NM(K+1))$, bộ nhớ phụ của DP $O(M(K+1))$.
