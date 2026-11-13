## Trạng thái và chuyển

Đặt $F[L][R]$ là số ký tự ít nhất phải chèn để đoạn $S[L\ldots R]$ thành đối xứng. Đoạn rỗng hoặc một ký tự có giá trị $0$.

- Nếu $S_L=S_R$: $F[L][R]=F[L+1][R-1]$.
- Nếu hai đầu khác nhau: $F[L][R]=1+\min(F[L+1][R],F[L][R-1])$.

Với hai đầu khác nhau, có thể chèn một bản sao của $S_L$ ở phía phải rồi giải phần còn lại, hoặc làm đối xứng cho $S_R$ ở phía trái.

## Tính đúng đắn

Xét một xâu đối xứng ngắn nhất chứa đoạn nguồn như dãy con. Có thể bỏ các cặp ngoài cùng mà cả hai ký tự đều được chèn, nên một ký tự ngoài cùng phải là đầu trái hoặc đầu phải của nguồn. Nếu hai đầu nguồn khác nhau, chúng không thể ghép với nhau; ký tự đối diện với đầu được giữ phải được chèn. Bỏ cặp đó cho một trong hai bài toán con trong công thức, và ngược lại mỗi chuyển tạo một cách chèn hợp lệ. Nếu hai đầu bằng nhau, luôn có thể ghép chúng với nhau trong một phương án ngắn nhất; phần giữa cần đúng số chèn tối ưu của đoạn trong. Quy nạp cho kết quả tối ưu.

## Độ phức tạp và cài đặt

Tính theo đoạn, nén một hàng với ô chéo cũ. Thời gian $O(N^2)$, bộ nhớ $O(N)$; tối đa $12502500$ ô chính. Giá trị cũng bằng $N$ trừ độ dài dãy con đối xứng dài nhất, nhưng công thức trên cho cách giải trực tiếp bằng DP trên đoạn.
