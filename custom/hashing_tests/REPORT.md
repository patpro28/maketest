# Kết quả kiểm thử bộ hashing

| Bài | Test chính thức | Ca đối chiếu thêm | Đầu vào sai bị từ chối | Kiểm tra checker | Thời gian chậm nhất |
| --- | ---: | ---: | ---: | ---: | ---: |
| hashing000 | 30 | 742 | 8 | 6 | 0.105 s |
| hashing001 | 30 | 1625 | 6 | 6 | 0.309 s |
| hashing002 | 30 | 226 | 5 | 6 | 0.118 s |
| hashing003 | 30 | 1000 | 6 | 6 | 0.037 s |
| hashing004 | 30 | 162 | 11 | 6 | 0.638 s |
| hashing005 | 30 | 314 | 6 | 6 | 0.073 s |
| hashing006 | 30 | 441 | 6 | 6 | 0.075 s |
| hashing007 | 30 | 361 | 13 | 6 | 0.669 s |
| hashing008 | 30 | 163 | 14 | 10 | 0.411 s |
| hashing009 | 30 | 162 | 9 | 6 | 1.028 s |

Mọi test chính thức đã qua verifier, lời giải, checker, đối chiếu lời giải độc lập và kiểm tra tái lập bộ sinh. Các test nhỏ được đối chiếu thêm bằng vét cạn trực tiếp. Thời gian đo trên máy chạy kiểm thử, đã bao gồm khởi động tiến trình.

Đề đã được kiểm tra thứ tự heading và đối chiếu cả hai ví dụ với đầu vào/đầu ra thực tế; không có Subtask và không xuất HTML. Hash SHA-256 của mọi đầu vào/đầu ra đã được đối chiếu với `hash.json`.
