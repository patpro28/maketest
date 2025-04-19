### Đề bài

Giáng sinh là khoảng thời gian đẹp nhất trong năm. Hai anh em Wiliam và Jacica là hai diễn viên múa chính của đoàn nghệ thuật đinh cao số một thế giới. Các vở diễn của họ góp phần hồi sinh các giá trị đạo đức, văn hóa truyền thống, đem lại cho người xem năng lượng tích cực, cảm nhận sâu sắc về các giá trị tốt đẹp và sự bình yên trong tâm hồn. Wiliam và Jacica vừa trở về nhà sau chuyến lưu diễn vòng quanh thế giới và bắt đầu trang trí cây thông Noel của họ bằng những món đồ xinh xắn đã mua trong quá trình lưu diễn.

Họ đã mua $n$ món đồ trang trí cây thông được xếp cạnh nhau trong một hộp dài, món đồ trang trí thứ $i$ có màu $A_i$. Hộp được mở ở cả hai dầu, vì vậy các món đồ có thể được lấy ra từ bên trái hoặc bên phải của hộp. Hộp này trong suốt, nên Wiliam và Jacica có thể nhìn thấy màu sắc của từng món đồ trang trí.

Jacica nghĩ ra một trò chơi để việc trang trí cây thông trở nên thú vị hơn. Trò chơi diễn ra như sau: Wiliam và Jacica thay phiên nhau chơi, Wiliam là người bắt dầu. Người chơi trong lượt của mình sẽ lấy một món đồ trang trí từ hộp (có thể từ bên trái hoặc bên phải) và đặt nó lên cây thông. Nếu món đồ được lấy có màu chưa từng dược người nào lấy trước đó, người chơi sẽ ghi được một điểm. Trò chơi kết thúc khi món đồ trang trí cuối cùng được lấy ra khỏi hộp.

Người chiến thắng là người ghi được nhiều điểm hơn. Vì cả Wiliam và Jacica đều là những người chơi xuất sắc, họ sẽ chơi một cách tối ưu.

**Yêu cầu**: Em hãy đưa ra kết quả cuối cùng của trò chơi.

### Dữ liệu vào

- Dòng đầu tiên chứa một số nguyên $n$ là số lượng món đồ trang trí trong hộp.
- Dòng thứ hai chứa $n$ số nguyên $A_1, A_2, ..., A_n$ với $A_i$  là màu sắc của món đồ thứ $i$.

### Dữ liệu ra

Một dòng duy nhất gồm hai số, được nối bằng một ký tự `:` (dầu hai chấm), lần lượt là điểm số của Wiliam và Jacica.

### Giới hạn

- $1 \le n \le 3000$
- $1 \le A_i \le n$

### Subtask

- Subtask 1 (25%): $1 \le A_i \le 2$
- Subtask 2 (20%): $1 \le n \le 20$
- Subtask 3 (10%): $1 \le A_i \le 20$
- Subtask 4 (20%): $1 \le n \le 300$
- Subtask 5 (25%): Không có giới hạn gì thêm

### Sample Input 1

```
5
1 1 2 1 1
```

### Sample Output 1

```
1:1
```

### Sample Input 2

```
6
5 3 4 5 3 4
```

### Sample Output 2

```
2:1
```

### Giải thích

**Test case 1**:

- Lượt đầu, Wiliam lấy món đồ bên trái (màu 1), ghi được một điểm.
- Lượt thứ hai, Jacica lấy món đồ bên phải (màu 1), không nhận được điểm nào vì màu này đã được lấy trước đó.
- Lượt thứ ba, Wiliam lấy món đồ bên trái (màu 1), không nhận được điểm nào vì màu này đã được lấy trước đó.
- Lượt thứ tư, Jacica lấy món đồ bên trái (màu 2), ghi được một điểm.
- Lượt cuối, Wiliam lấy món đồ bên phải (màu 1), không nhận được điểm nào vì màu này đã được lấy trước đó.

Tống kết, tỉ số là `1:1`.

**Test case 2**:

- Lượt đầu, Wiliam lấy món đồ bên trái (màu 5), ghi được một điểm.
- Lượt thứ hai, Jacica lấy món đồ bên phải (màu 4), ghi được một điểm.
- Lượt thứ ba, Wiliam lấy món đồ bên trái (màu 3), ghi được một điểm.
- Lượt thứ tư, Jacica lấy món đồ bên phải (màu 3), không nhận được điểm nào vì màu này đã được lấy trước đó.
- Lượt thứ năm, Wiliam lấy món đồ bên trái (màu 4), không nhận được điểm nào vì màu này đã được lấy trước đó.
- Lượt cuối, Jacica lấy món đồ bên phải (màu 5), không nhận được điểm nào vì màu này đã được lấy trước đó.

Tống kết, tỉ số là `2:1`.