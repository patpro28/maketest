# DTPALINCUT — Cắt chuỗi đối xứng

### Đề bài

Một chuỗi hạt được biểu diễn bằng xâu $S$ gồm các chữ cái La tinh thường. Người ta muốn cắt chuỗi hạt để nhận được $k$ chuỗi con, trong đó mỗi chuỗi có độ dài xác định trước và là một xâu đối xứng. Một xâu đối xứng là xâu đọc từ trái sang phải giống như đọc từ phải sang trái.

Hãy xác định có tồn tại cách chọn $k$ đoạn của $S$, sao cho chúng đều đối xứng và có các độ dài $l_1,l_2,\ldots,l_k$ hay không.

Mỗi đoạn gồm các ký tự ở những vị trí liên tiếp trong $S$. Các đoạn được chọn đôi một không giao nhau và **không bắt buộc nằm sát nhau**: giữa hai đoạn có thể có các ký tự không được chọn. Có thể bỏ các phần hạt thừa ở đầu và cuối chuỗi. Thứ tự các đoạn trên chuỗi không bắt buộc trùng thứ tự liệt kê các độ dài. Nếu một độ dài xuất hiện nhiều lần, phải chọn đủ số đoạn tương ứng.

Ví dụ, có thể cắt xâu `asaaabbrcaacw` để nhận được ba xâu đối xứng có độ dài $2,3,4$ là `bb`, `aaa`, `caac`. Trên xâu ban đầu, các đoạn được giữ theo thứ tự `aaa`, `bb`, `caac`.

Có $T$ trường hợp yêu cầu trên cùng một xâu $S$. Các trường hợp độc lập, không thay đổi chuỗi hạt ban đầu.

### Dữ liệu vào

Đọc từ tệp văn bản `PALINCUT.INP`:

- Dòng đầu chứa xâu $S$.
- Dòng thứ hai chứa số nguyên $T$ là số trường hợp thử.
- Trong $T$ dòng tiếp theo, mỗi dòng chứa số nguyên $k$, tiếp theo là $k$ số nguyên dương $l_1,l_2,\ldots,l_k$.

### Dữ liệu ra

Ghi ra tệp văn bản `PALINCUT.OUT` $T$ dòng. Với mỗi trường hợp, in `YES` nếu có cách cắt thỏa mãn, ngược lại in `NO`.

### Ràng buộc

- $1\le |S|\le10000$.
- Mọi ký tự của $S$ thuộc tập `a`, `b`, ..., `z`.
- $1\le T\le200$.
- $1\le k\le13$ trong mỗi trường hợp.
- $l_i$ là số nguyên dương. Nếu một độ dài lớn hơn $|S|$, trường hợp đó không thể có lời giải.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 25% | $k=1$ trong mọi trường hợp thử; $T\le200$ |
| 2 | 25% | $k\le13$, $|S|\le200$, $T\le3$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
asaaabbrcaacw
2
3 2 3 4
4 2 2 2 2
```

### Sample Output 1

```text
YES
NO
```

### Sample Input 2

```text
bbbbccaa
4
2 4 4
3 4 2 2
4 1 2 2 3
4 2 2 2 2
```

### Sample Output 2

```text
NO
YES
YES
YES
```

### Giải thích

Ở ví dụ 1, trường hợp đầu có thể giữ các đoạn `aaa`, `bb`, `caac`, có các độ dài $3,2,4$ và đều đối xứng. Không thể chọn bốn đoạn độ dài $2$ không giao nhau, nên trường hợp thứ hai trả lời `NO`.

Ở ví dụ 2, không thể chọn hai đoạn đối xứng độ dài $4$. Ba trường hợp còn lại có thể cắt theo các cách sau:

- `bbbb | cc | aa`, có độ dài $4,2,2$.
- `bbb | b | cc | aa`, có các độ dài $3,1,2,2$, là một cách sắp lại các độ dài $1,2,2,3$.
- `bb | bb | cc | aa`, gồm bốn đoạn độ dài $2$.
