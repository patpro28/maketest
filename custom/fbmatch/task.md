### Đề bài

Trong một trò chơi xếp chữ, người chơi nhận được một chuỗi ký tự $S$ gồm $N$ chữ cái thường tiếng Anh. Người chơi được phép **xáo trộn lại thứ tự các ký tự của chuỗi $S$ một cách tùy ý** để tạo thành một chuỗi mới.

Nhiệm vụ của người chơi là kiểm tra xem **có tồn tại cách sắp xếp nào sao cho ký tự ở vị trí đầu tiên và ký tự ở vị trí cuối cùng của chuỗi sau khi xáo trộn là giống nhau hay không**.

Với mỗi màn chơi (test case), hãy cho biết điều này có thể thực hiện được hay không.

### Dữ liệu vào

- Dòng đầu tiên chứa một số nguyên $T$ — số lượng test.
- Mỗi test gồm:
  - Một dòng chứa số nguyên $N$ — độ dài của chuỗi.
  - Một dòng chứa chuỗi $S$ gồm $N$ ký tự chữ thường.

### Dữ liệu ra

Với mỗi test, in ra trên một dòng:
- `Yes` nếu tồn tại cách xáo trộn thỏa mãn yêu cầu.
- `No` nếu không tồn tại cách nào.

(Không phân biệt chữ hoa hay chữ thường trong kết quả.)

### Ràng buộc

- $1 \le T \le 100$
- $2 \le N \le 100$
- $S_i \in \{\texttt{a}, \texttt{b}, \ldots, \texttt{z}\}$

### Sample Input 1
    4
    3
    aka
    4
    nope
    5
    pluto
    5
    foggy

### Sample Output 1
    Yes
    No
    No
    Yes

### Giải thích

- Test 1: Chuỗi `aka` đã có sẵn ký tự đầu và cuối giống nhau.
- Test 2: Chuỗi `nope` không thể xáo trộn để hai ký tự đầu–cuối trùng nhau.
- Test 3: Chuỗi `pluto` cũng không tồn tại cách sắp xếp phù hợp.
- Test 4: Chuỗi `foggy` có thể xáo trộn thành `gyfog`, khi đó ký tự đầu và cuối đều là `g`.