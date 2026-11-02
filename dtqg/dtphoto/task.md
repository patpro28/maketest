# DTPHOTO — Chụp ảnh

### Đề bài

Lễ khai mạc thế vận hội năm 2112 có $n$ vận động viên đánh số từ $1$ tới $n$ đứng xếp hàng ngang để chụp ảnh. Ban tổ chức đã sắp xếp họ theo một thứ tự mà họ cho là đẹp nhất, gọi là **thứ tự chuẩn**.

Tuy nhiên, khi người thợ chụp ảnh quay lại để bấm máy, một số vận động viên đã tự ý rời hàng để bắt tay khán giả. Trọng tài cảnh cáo những vận động viên tự ý rời hàng và yêu cầu quay lại hàng ngũ. Những vận động viên này có thể chèn vào các vị trí mới, làm mất đi thứ tự chuẩn. Các vận động viên không rời hàng vẫn giữ nguyên thứ tự tương đối với nhau.

Ban tổ chức sắp xếp lại các vận động viên theo thứ tự chuẩn trước lần chụp tiếp theo, nhưng mọi việc diễn ra tương tự. Sau $5$ lần và thu được $5$ tấm ảnh, ban tổ chức đành bỏ cuộc và gửi ảnh cho chuyên gia Photoshop cắt dán lại theo thứ tự chuẩn.

Vấn đề là ban tổ chức đã quên mất thứ tự chuẩn. Bạn cần dựa vào thứ tự trong $5$ bức ảnh để xác định thứ tự đó. Biết rằng **không có vận động viên nào bị cảnh cáo nhiều hơn một lần** trong cả năm lần chụp.

### Dữ liệu vào

Đọc từ tệp văn bản `PHOTO.INP`:

- Dòng đầu chứa số nguyên dương $n$.
- Trong $5$ dòng tiếp theo, dòng thứ $k$ chứa $n$ số nguyên là số hiệu các vận động viên trong bức ảnh thứ $k$, theo đúng thứ tự từ trái sang phải trong ảnh.

Các số trên một dòng được ngăn cách bởi ít nhất một dấu cách.

### Dữ liệu ra

Ghi ra tệp văn bản `PHOTO.OUT` $n$ số nguyên là số hiệu các vận động viên theo đúng thứ tự chuẩn muốn chụp, cách nhau ít nhất một dấu cách.

### Ràng buộc

- $1\le n\le10^5$.
- Mỗi bức ảnh chứa đúng một lần mỗi số hiệu từ $1$ tới $n$.
- Năm bức ảnh được tạo theo mô tả: trước mỗi lần chụp, hàng được đưa về cùng thứ tự chuẩn; mỗi vận động viên tự ý rời hàng trong nhiều nhất một lần chụp.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 30% | $n\le8$ |
| 2 | 70% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
9
1 5 7 8 9 2 4 3 6
2 4 6 1 3 5 7 9 8
3 5 7 9 2 4 6 8 1
1 3 7 5 9 2 4 6 8
1 7 3 5 9 2 4 6 8
```

### Sample Output 1

```text
1 3 5 7 9 2 4 6 8
```

### Giải thích

Ở ví dụ 1, thứ tự chuẩn là $(1,3,5,7,9,2,4,6,8)$. Các vận động viên rời hàng ở từng lần chụp lần lượt là:

- Lần $1$: vận động viên $3$ và $8$.
- Lần $2$: vận động viên $2,4,6$.
- Lần $3$: vận động viên $1$.
- Lần $4$: vận động viên $5$.
- Lần $5$: vận động viên $7$.

Không có vận động viên nào trong danh sách này rời hàng hai lần. Vận động viên $9$ không rời hàng trong cả năm lần.
