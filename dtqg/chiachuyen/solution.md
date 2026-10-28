# Lời giải CHIACHUYEN — Chia chuyến hàng

## Quy hoạch động cơ bản

Đặt $D[i]$ là tổng chi phí nhỏ nhất để chở đúng $i$ kiện đầu tiên. Có $D[0]=0$; các tiền tố không thể chia có giá trị vô cùng.

Nếu chuyến cuối chở các kiện $j+1,\ldots,i$, thì

$$D[i]=C+\min_{\max(0,i-R)\le j\le i-L}
\left(D[j]+\max_{j<k\le i}H_k-\min_{j<k\le i}H_k\right).$$

Khi $i<L$, chưa có chuyến cuối hợp lệ. Công thức xét đủ mọi cách chọn chuyến cuối, nên cho đáp án đúng. Tính trực tiếp bằng cách kéo dài đoạn cuối và duy trì max/min mất $O(NR)$ thời gian, bộ nhớ $O(N)$.

## Giá trị cần duy trì

Khi đang xét đầu phải $i$, ở lá $j$ của segment tree lưu

$$V_j=D[j]+\max(H_{j+1},\ldots,H_i)-\min(H_{j+1},\ldots,H_i),\quad 0\le j<i.$$

Cần hỗ trợ gán một lá, cộng một giá trị không âm lên một đoạn lá và lấy min một đoạn lá. Dùng segment tree với lazy propagation.

Khi thêm $H_i$:

1. Thêm lá $j=i-1$ với giá trị $D[i-1]$, vì đoạn chỉ chứa kiện $i$ có max trừ min bằng $0$.
2. Cập nhật phần thay đổi của max cho các lá cũ bằng stack đơn điệu giảm.
3. Cập nhật phần thay đổi của min bằng stack đơn điệu tăng.
4. Lấy min trên cửa sổ $[\max(0,i-R),i-L]$, rồi cộng $C$ để tính $D[i]$.

## Cập nhật max bằng stack

Stack lưu các chỉ số $p_1<\cdots<p_k$ có giá trị $H_{p_1}>\cdots>H_{p_k}$. Trước khi thêm $i$, nếu $p$ là phần tử cuối và $q$ là chỉ số ngay trước nó trong stack (lấy $q=0$ nếu không còn), thì các lá

$$j\in[q,p-1]$$

đang có giá trị lớn nhất của đoạn $j+1,\ldots,i-1$ bằng $H_p$.

Khi $H_p\le H_i$, bỏ $p$ khỏi stack. Với nhóm lá trên, giá trị lớn nhất mới tăng từ $H_p$ lên $H_i$, nên cộng $H_i-H_p$ lên đoạn $[q,p-1]$. Lặp đến khi stack rỗng hoặc đỉnh stack có giá trị lớn hơn $H_i$, rồi đẩy $i$ vào.

Các nhóm bị bỏ rời nhau. Không cập nhật lá mới $i-1$, vốn đã có max bằng min bằng $H_i$.

## Cập nhật min bằng stack

Tương tự, dùng stack tăng nghiêm ngặt. Khi đỉnh $p$ có $H_p\ge H_i$, bỏ $p$ và cộng

$$H_p-H_i$$

lên các lá $[q,p-1]$, vì phần $-\min$ tăng một lượng như vậy. Sau đó đẩy $i$ vào stack.

Dùng dấu không nghiêm ngặt trong điều kiện bỏ đỉnh để gộp các nhóm bằng nhau; khi hai giá trị bằng nhau, lượng cộng bằng $0$.

## Chứng minh đúng

Bất biến ở mỗi bước là mỗi lá đã thêm lưu đúng $V_j$. Lá mới đúng vì đoạn một phần tử có độ chênh bằng $0$. Stack max phân hoạch chính xác những điểm bắt đầu mà cực đại thay đổi khi thêm $H_i$; các phép cộng cập nhật đúng lượng thay đổi. Stack min thực hiện điều tương tự cho cực tiểu. Vì vậy bất biến tiếp tục đúng sau hai nhóm cập nhật.

Truy vấn chỉ lấy các $j$ có $L\le i-j\le R$, tức mọi và chỉ những chuyến cuối hợp lệ. Theo công thức DP và quy nạp trên $i$, giá trị $D[i]$ nhận được là tối ưu. Nếu $D[N]$ không hữu hạn thì không có cách chia, nên trả $-1$.

## Độ phức tạp và lưu ý

- Mỗi chỉ số được đẩy vào và lấy khỏi mỗi stack nhiều nhất một lần. Tổng cộng $O(N)$ thao tác cộng đoạn.
- Mỗi thao tác trên segment tree mất $O(\log N)$, nên thời gian $O(N\log N)$; bộ nhớ $O(N)$.
- Dùng số nguyên có dấu $64$ bit. Chi phí một chuyến nhỏ hơn $2\cdot10^9$, nên mọi đáp án hữu hạn nhỏ hơn $4\cdot10^{14}$.
- Cài đặt chọn `INF = 4e18`. Các cập nhật max/min chỉ cộng số không âm; một lá không khả thi vẫn lớn hơn `INF/2`. Chỉ gán $D[i]$ nếu min truy vấn nhỏ hơn `INF/2`.
- Chỉ số trong stack là vị trí kiện hàng ($1$ đến $N$); chỉ số lá là số kiện đã chở ($0$ đến $N-1$). Phân biệt hai loại chỉ số để tránh lệch một đơn vị.
- Không tham lam tối thiểu số chuyến: ví dụ 1 có ba chuyến rẻ hơn hai chuyến.

## Các trường hợp kiểm tra nhanh

- $L=R=1$: đáp án $NC$.
- $L=R=K$: chỉ khả thi nếu $N$ chia hết cho $K$, khi đó cách chia là duy nhất.
- $L=1,C=0$: đáp án bằng $0$.
- Mọi $H_i$ bằng nhau: nếu tồn tại số chuyến $k$ với $kL\le N\le kR$, đáp án là $C\lceil N/R\rceil$; nếu không thì $-1$.
