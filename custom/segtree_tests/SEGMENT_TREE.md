# Segment Tree — quy hoạch mở rộng để duyệt

Nguồn: nội dung quy hoạch 000–999 bạn gửi trong chat. Phương án A: phân loại theo kỹ thuật cài đặt. Đây là bản đề xuất, chưa áp dụng vào dữ liệu thật.

## Phạm vi thay đổi

- Đủ 10 nhóm chính và 100 phân nhóm tham khảo trong nhánh Data Structures › Segment Tree.
- Giữ toàn bộ mã Topic cũ, gồm cả Range Add, Range Assign và Range Affine; không tái sử dụng mã cũ cho khái niệm hẹp hơn.
- Range Add và Range Assign của Lazy giữ ở cấp trung gian, bên dưới mới phân biệt Sum và Min/Max. Vì vậy số Topic của nhánh lớn hơn 10 + 100.
- Giữ khả năng gán trực tiếp vào nhóm rộng cho bài tổng hợp khi phù hợp mục tiêu dạy học. Không tự gán vào con đầu tiên.
- Không đổi schema chỉ để mã hóa SEG0–SEG9: 10 nhóm là dữ liệu cây, không phải enum hay mười trường riêng.

## Quy hoạch 10 nhóm

| Khoảng tham khảo | Nhóm | Mã Topic ổn định |
|---|---|---|
| SEG000–SEG099 | Basic Segment Tree | TOP-GCN7EF2J53 |
| SEG100–SEG199 | Searching Segment Tree | TOP-YCJQX3ZWD2 |
| SEG200–SEG299 | Lazy Segment Tree | TOP-372AANQKG2 |
| SEG300–SEG399 | Advanced Node Segment Tree | TOP-TGBXA1KPHJ |
| SEG400–SEG499 | Persistent Segment Tree | TOP-H993NJR3EC |
| SEG500–SEG599 | Dynamic Segment Tree | TOP-2C0ERRW6Q6 |
| SEG600–SEG699 | Mergeable Segment Tree | TOP-KXEYN7ABMP |
| SEG700–SEG799 | Segment Tree Beats | TOP-F294YQ3CWC |
| SEG800–SEG899 | Hybrid Segment Tree | TOP-Q37SKRDDD4 |
| SEG900–SEG999 | Specialized Segment Tree | TOP-D8JWW34KWX |

## Cây Segment Tree

```text
Segment Tree [chọn] · TOP-SMAFERFWKJ
├── Basic Segment Tree [chọn] · TOP-GCN7EF2J53
│   ├── Static Range Query [chọn] · TOP-FB61J3EYJR
│   ├── Range Sum [chọn] · TOP-ZX6N9JZ9KY
│   ├── Range Min-Max [chọn] · TOP-F4DA53XX74
│   ├── Range GCD-LCM [chọn] · TOP-8GKH14W0VW
│   ├── Range Bitwise Operations [chọn] · TOP-E08D6J678N
│   ├── Conditional Counting [chọn] · TOP-H04T7B98ME
│   ├── Multi-Field Node [chọn] · TOP-ZHW1HQ0YJ2
│   ├── Multi-Aggregate Query [chọn] · TOP-BSQJMN7ST3
│   ├── Custom Associative Operation [chọn] · TOP-9QZWEP977C
│   └── Basic Mixed Problems [chọn] · TOP-HJSCY8W2S3
├── Searching Segment Tree [chọn] · TOP-YCJQX3ZWD2
│   ├── Basic Tree Search [chọn] · TOP-MMGEM1DRHE
│   ├── First Position [chọn] · TOP-A2ZNC92KAE
│   ├── K-th Element [chọn] · TOP-HVXB701KRY
│   ├── Prefix Sum Search [chọn] · TOP-M9VXK1G0PH
│   ├── First Value At Least X [chọn] · TOP-TNSF5CM70Q
│   ├── First Value At Most X [chọn] · TOP-QNVVMWMXG5
│   ├── Search within Range [chọn] · TOP-0Z6TK611NR
│   ├── Subarray Search [chọn] · TOP-B98YPQH48K
│   ├── Multi-Field Search [chọn] · TOP-MFMBYMQK2H
│   └── Searching Mixed Problems [chọn] · TOP-E5MM7G1JTV
├── Lazy Segment Tree [chọn] · TOP-372AANQKG2
│   ├── Basic Lazy Propagation [chọn] · TOP-001EY9JH9S
│   ├── Range Add [chọn] · TOP-N3XQ1DQMZ8
│   │   ├── Range Add - Range Sum [chọn] · TOP-KVAR7YJR6F
│   │   └── Range Add - Range Min-Max [chọn] · TOP-FD439S2HWB
│   ├── Range Assign [chọn] · TOP-31WZ5X801D
│   │   ├── Range Assign - Range Sum [chọn] · TOP-5B5YEHKMYE
│   │   └── Range Assign - Range Min-Max [chọn] · TOP-WM31MEXZWT
│   ├── Range Add and Assign [chọn] · TOP-C3M4B6QCMT
│   ├── Range Affine [chọn] · TOP-XNPY3G3TBQ
│   ├── Range Flip-XOR Update [chọn] · TOP-ANA9GB0CEA
│   ├── Lazy Tree Search [chọn] · TOP-7C4638FB4Z
│   └── Mixed Lazy Updates [chọn] · TOP-066JT1WB52
├── Advanced Node Segment Tree [chọn] · TOP-TGBXA1KPHJ
│   ├── Advanced Node Design [chọn] · TOP-2GXC8VEJ0M
│   ├── Maximum Subarray Sum [chọn] · TOP-8RN1DX07M4
│   ├── Minimum Subarray Sum [chọn] · TOP-KNZYFYN3MZ
│   ├── Prefix-Suffix-Best [chọn] · TOP-YEV72XSFZ5
│   ├── Longest Valid Run [chọn] · TOP-QEBJB2MENT
│   ├── Subarray Counting [chọn] · TOP-J0D8VFSQMD
│   ├── Transition Matrix [chọn] · TOP-X3J25Q15C5
│   ├── Segment Tree DP [chọn] · TOP-884A899GR0
│   ├── Finite-State Node [chọn] · TOP-93Q281A8DP
│   └── Advanced Node Mixed Problems [chọn] · TOP-CKXND5JVZQ
├── Persistent Segment Tree [chọn] · TOP-H993NJR3EC
│   ├── Basic Persistence [chọn] · TOP-XAXXG47112
│   ├── Point Update - Version Query [chọn] · TOP-JHGWYTXAPW
│   ├── Historical Version Query [chọn] · TOP-4RVD2N1EH9
│   ├── K-th Smallest in Range [chọn] · TOP-EXQJW5KY1J
│   ├── Count Values At Most X [chọn] · TOP-5RJ8X04XY4
│   ├── Range Frequency Query [chọn] · TOP-HSVMW0PG3K
│   ├── Version Difference Query [chọn] · TOP-Y619XQXFX8
│   ├── Persistent Tree Search [chọn] · TOP-E8ZNKYM3T1
│   ├── Persistence on Trees and Graphs [chọn] · TOP-D1H7Y5Z6NQ
│   └── Advanced Persistence [chọn] · TOP-MAMJ3XY9WQ
├── Dynamic Segment Tree [chọn] · TOP-2C0ERRW6Q6
│   ├── Basic Dynamic Segment Tree [chọn] · TOP-DYXYQCTB4F
│   ├── Large-Domain Point Update [chọn] · TOP-X1GK1QKHTK
│   ├── Large-Domain Range Query [chọn] · TOP-X4P5BGZF6X
│   ├── Dynamic Lazy Segment Tree [chọn] · TOP-82V0K1Y3D8
│   ├── Dynamic Tree Search [chọn] · TOP-JJMN4ZNBWZ
│   ├── Sparse-Domain Segment Tree [chọn] · TOP-VVN1KD54CE
│   ├── Multidimensional Dynamic Segment Tree [chọn] · TOP-AQP1W0YMJ2
│   ├── Persistent Dynamic Segment Tree [chọn] · TOP-QN8T12481P
│   ├── Memory Allocation and Optimization [chọn] · TOP-WDA03ZKTV2
│   └── Dynamic Mixed Problems [chọn] · TOP-V1C11PYKNV
├── Mergeable Segment Tree [chọn] · TOP-KXEYN7ABMP
│   ├── Basic Segment Tree Merge [chọn] · TOP-0E8YWYS6RH
│   ├── Merge Two Segment Trees [chọn] · TOP-383T7G4SNY
│   ├── Split Segment Tree [chọn] · TOP-2BPX2672CX
│   ├── Merge with K-th Query [chọn] · TOP-1E4S3MG7R9
│   ├── Segment Trees for Sets [chọn] · TOP-HJ1RTWD963
│   ├── Segment Tree Merge on Trees [chọn] · TOP-HQ83398JH0
│   ├── Merge with DSU [chọn] · TOP-H995QTTK16
│   ├── Persistent Segment Tree Merge [chọn] · TOP-1NKYCDD1K2
│   ├── Advanced Merge-Split [chọn] · TOP-HX7NK7CQYC
│   └── Merge-Split Mixed Problems [chọn] · TOP-3Z4ZPCJE6Z
├── Segment Tree Beats [chọn] · TOP-F294YQ3CWC
│   ├── Basic Segment Tree Beats [chọn] · TOP-SEX8SCX3ZJ
│   ├── Range Chmin [chọn] · TOP-Z6XNYF5XD8
│   ├── Range Chmax [chọn] · TOP-519TFY83WX
│   ├── Range Chmin and Chmax [chọn] · TOP-513VBJFBT7
│   ├── Range Add and Chmin [chọn] · TOP-ETAS8T48WC
│   ├── Range Add and Chmax [chọn] · TOP-40KDD6AD7R
│   ├── Range Add-Chmin-Chmax [chọn] · TOP-PDR5W8JEDQ
│   ├── Range Modulo and Pruned Updates [chọn] · TOP-0VYNGPA3GF
│   ├── Beats with Advanced Queries [chọn] · TOP-0XB95351AD
│   └── Beats Mixed Problems [chọn] · TOP-X2WGBW3D3Q
├── Hybrid Segment Tree [chọn] · TOP-Q37SKRDDD4
│   ├── Segment Tree with Binary Search [chọn] · TOP-A69BXWT45D
│   ├── Segment Tree with HLD [chọn] · TOP-M5MS3HZR60
│   ├── Segment Tree with Euler Tour [chọn] · TOP-40X0TYZ0JY
│   ├── Segment Tree of Vectors [chọn] · TOP-YRH9T95CMB
│   ├── Merge Sort Tree [chọn] · TOP-2VTCSZGN4Q
│   ├── Two-Dimensional Segment Tree [chọn] · TOP-YWGDK94GGG
│   ├── Segment Tree with Fenwick Tree [chọn] · TOP-WZ8ET97KW7
│   ├── Segment Tree with Li Chao Tree [chọn] · TOP-Y6T3R5DPDA
│   ├── Segment Tree with Offline Algorithms [chọn] · TOP-ZAGYN58C8Y
│   └── Other Hybrid Structures [chọn] · TOP-6Z83W3YZDK
└── Specialized Segment Tree [chọn] · TOP-D8JWW34KWX
    ├── Segment Tree over Time [chọn] · TOP-3K747Z2JEP
    ├── Segment Tree with Rollback [chọn] · TOP-KH1Y7V7C41
    ├── Offline Dynamic Connectivity [chọn] · TOP-2H7SWSSW8M
    ├── Active-Interval Segment Tree [chọn] · TOP-N3HW49BV66
    ├── Segment Tree in Geometry [chọn] · TOP-NN3D7DSVFQ
    ├── Sweep Line with Segment Tree [chọn] · TOP-85QVQZD286
    ├── Function-Aggregating Segment Tree [chọn] · TOP-E7SH2H0JMZ
    ├── Noncommutative Aggregation [chọn] · TOP-D691HSWR06
    ├── Other Specialized Variants [chọn] · TOP-49H1JEBR8R
    └── Specialized Mixed Problems [chọn] · TOP-97AGH6KF47
```

## 100 phân nhóm và khoảng tham khảo

Mỗi dòng ánh xạ một khoảng trong quy hoạch sang Topic đề xuất. Đây không phải ánh xạ ProblemType hay danh sách bài hiện có. Khoảng giữ dạng chuỗi để bảo toàn số 0 ở đầu.

### SEG0 — Basic Segment Tree

| Khoảng | Dạng trong tài liệu nguồn | Topic đích | Mã Topic |
|---|---|---|---|
| 000–009 | Xây dựng cây, truy vấn cơ bản, không cập nhật | Static Range Query | TOP-FB61J3EYJR |
| 010–019 | Tổng đoạn – Range Sum | Range Sum | TOP-ZX6N9JZ9KY |
| 020–029 | Min / Max đoạn | Range Min-Max | TOP-F4DA53XX74 |
| 030–039 | GCD / LCM đoạn | Range GCD-LCM | TOP-8GKH14W0VW |
| 040–049 | AND / OR / XOR đoạn | Range Bitwise Operations | TOP-E08D6J678N |
| 050–059 | Đếm phần tử thỏa mãn điều kiện | Conditional Counting | TOP-H04T7B98ME |
| 060–069 | Lưu nhiều thông tin trên nút | Multi-Field Node | TOP-ZHW1HQ0YJ2 |
| 070–079 | Truy vấn kết hợp nhiều đại lượng | Multi-Aggregate Query | TOP-BSQJMN7ST3 |
| 080–089 | Segment Tree với phép toán kết hợp tùy chỉnh | Custom Associative Operation | TOP-9QZWEP977C |
| 090–099 | Bài toán tổng hợp cơ bản | Basic Mixed Problems | TOP-HJSCY8W2S3 |

### SEG1 — Searching Segment Tree

| Khoảng | Dạng trong tài liệu nguồn | Topic đích | Mã Topic |
|---|---|---|---|
| 100–109 | Tìm kiếm trên cây Segment Tree cơ bản | Basic Tree Search | TOP-MMGEM1DRHE |
| 110–119 | Tìm vị trí đầu tiên / cuối cùng thỏa mãn điều kiện | First Position | TOP-A2ZNC92KAE |
| 120–129 | Tìm phần tử thứ \(k\) theo thứ tự | K-th Element | TOP-HVXB701KRY |
| 130–139 | Tìm vị trí theo tổng tiền tố | Prefix Sum Search | TOP-M9VXK1G0PH |
| 140–149 | Tìm phần tử đầu tiên có giá trị \(\ge x\) | First Value At Least X | TOP-TNSF5CM70Q |
| 150–159 | Tìm phần tử đầu tiên có giá trị \(\le x\) | First Value At Most X | TOP-QNVVMWMXG5 |
| 160–169 | Tìm kiếm trong đoạn \([L,R]\) | Search within Range | TOP-0Z6TK611NR |
| 170–179 | Tìm đoạn con thỏa mãn điều kiện | Subarray Search | TOP-B98YPQH48K |
| 180–189 | Tìm kiếm kết hợp nhiều thông tin | Multi-Field Search | TOP-MFMBYMQK2H |
| 190–199 | Bài toán tổng hợp về tìm kiếm | Searching Mixed Problems | TOP-E5MM7G1JTV |

### SEG2 — Lazy Segment Tree

| Khoảng | Dạng trong tài liệu nguồn | Topic đích | Mã Topic |
|---|---|---|---|
| 200–209 | Lazy Propagation cơ bản | Basic Lazy Propagation | TOP-001EY9JH9S |
| 210–219 | Range Add – Range Sum | Range Add - Range Sum | TOP-KVAR7YJR6F |
| 220–229 | Range Add – Range Min/Max | Range Add - Range Min-Max | TOP-FD439S2HWB |
| 230–239 | Range Assign – Range Sum | Range Assign - Range Sum | TOP-5B5YEHKMYE |
| 240–249 | Range Assign – Range Min/Max | Range Assign - Range Min-Max | TOP-WM31MEXZWT |
| 250–259 | Range Add + Range Assign | Range Add and Assign | TOP-C3M4B6QCMT |
| 260–269 | Range Multiply / Affine Update | Range Affine | TOP-XNPY3G3TBQ |
| 270–279 | Range Flip / XOR Update | Range Flip-XOR Update | TOP-ANA9GB0CEA |
| 280–289 | Lazy kết hợp tìm kiếm | Lazy Tree Search | TOP-7C4638FB4Z |
| 290–299 | Lazy tổng hợp, nhiều loại cập nhật | Mixed Lazy Updates | TOP-066JT1WB52 |

### SEG3 — Advanced Node Segment Tree

| Khoảng | Dạng trong tài liệu nguồn | Topic đích | Mã Topic |
|---|---|---|---|
| 300–309 | Thiết kế Node và Merge nâng cao | Advanced Node Design | TOP-2GXC8VEJ0M |
| 310–319 | Maximum Subarray Sum | Maximum Subarray Sum | TOP-8RN1DX07M4 |
| 320–329 | Minimum Subarray Sum | Minimum Subarray Sum | TOP-KNZYFYN3MZ |
| 330–339 | Prefix / Suffix / Best | Prefix-Suffix-Best | TOP-YEV72XSFZ5 |
| 340–349 | Đoạn liên tiếp dài nhất thỏa mãn điều kiện | Longest Valid Run | TOP-QEBJB2MENT |
| 350–359 | Đếm đoạn con thỏa mãn điều kiện | Subarray Counting | TOP-J0D8VFSQMD |
| 360–369 | Ma trận chuyển trạng thái | Transition Matrix | TOP-X3J25Q15C5 |
| 370–379 | Dynamic Programming trên Segment Tree | Segment Tree DP | TOP-884A899GR0 |
| 380–389 | Segment Tree lưu trạng thái hữu hạn | Finite-State Node | TOP-93Q281A8DP |
| 390–399 | Tổng hợp các dạng Node phức tạp | Advanced Node Mixed Problems | TOP-CKXND5JVZQ |

### SEG4 — Persistent Segment Tree

| Khoảng | Dạng trong tài liệu nguồn | Topic đích | Mã Topic |
|---|---|---|---|
| 400–409 | Persistent Segment Tree cơ bản | Basic Persistence | TOP-XAXXG47112 |
| 410–419 | Point Update – Version Query | Point Update - Version Query | TOP-JHGWYTXAPW |
| 420–429 | Truy vấn phiên bản trong quá khứ | Historical Version Query | TOP-4RVD2N1EH9 |
| 430–439 | K-th Smallest Number | K-th Smallest in Range | TOP-EXQJW5KY1J |
| 440–449 | Đếm phần tử \(\le x\) trong đoạn | Count Values At Most X | TOP-5RJ8X04XY4 |
| 450–459 | Truy vấn tần suất trên đoạn | Range Frequency Query | TOP-HSVMW0PG3K |
| 460–469 | Truy vấn hiệu hai phiên bản | Version Difference Query | TOP-Y619XQXFX8 |
| 470–479 | Persistent kết hợp tìm kiếm | Persistent Tree Search | TOP-E8ZNKYM3T1 |
| 480–489 | Persistent trên cây / đồ thị | Persistence on Trees and Graphs | TOP-D1H7Y5Z6NQ |
| 490–499 | Persistent nâng cao | Advanced Persistence | TOP-MAMJ3XY9WQ |

### SEG5 — Dynamic Segment Tree

| Khoảng | Dạng trong tài liệu nguồn | Topic đích | Mã Topic |
|---|---|---|---|
| 500–509 | Dynamic Segment Tree cơ bản | Basic Dynamic Segment Tree | TOP-DYXYQCTB4F |
| 510–519 | Point Update trên miền tọa độ lớn | Large-Domain Point Update | TOP-X1GK1QKHTK |
| 520–529 | Range Query trên miền lớn | Large-Domain Range Query | TOP-X4P5BGZF6X |
| 530–539 | Dynamic Lazy Segment Tree | Dynamic Lazy Segment Tree | TOP-82V0K1Y3D8 |
| 540–549 | Dynamic Segment Tree kết hợp tìm kiếm | Dynamic Tree Search | TOP-JJMN4ZNBWZ |
| 550–559 | Dynamic Segment Tree trên miền thưa | Sparse-Domain Segment Tree | TOP-VVN1KD54CE |
| 560–569 | Dynamic Segment Tree nhiều chiều | Multidimensional Dynamic Segment Tree | TOP-AQP1W0YMJ2 |
| 570–579 | Dynamic Segment Tree kết hợp Persistent | Persistent Dynamic Segment Tree | TOP-QN8T12481P |
| 580–589 | Quản lý bộ nhớ và tối ưu cấp phát | Memory Allocation and Optimization | TOP-WDA03ZKTV2 |
| 590–599 | Bài toán tổng hợp | Dynamic Mixed Problems | TOP-V1C11PYKNV |

### SEG6 — Mergeable Segment Tree

| Khoảng | Dạng trong tài liệu nguồn | Topic đích | Mã Topic |
|---|---|---|---|
| 600–609 | Merge Segment Tree cơ bản | Basic Segment Tree Merge | TOP-0E8YWYS6RH |
| 610–619 | Gộp hai Segment Tree | Merge Two Segment Trees | TOP-383T7G4SNY |
| 620–629 | Tách Segment Tree | Split Segment Tree | TOP-2BPX2672CX |
| 630–639 | Merge kết hợp truy vấn K-th | Merge with K-th Query | TOP-1E4S3MG7R9 |
| 640–649 | Segment Tree trên các tập hợp | Segment Trees for Sets | TOP-HJ1RTWD963 |
| 650–659 | Segment Tree trên cây | Segment Tree Merge on Trees | TOP-HQ83398JH0 |
| 660–669 | Merge kết hợp DSU | Merge with DSU | TOP-H995QTTK16 |
| 670–679 | Merge kết hợp Persistent | Persistent Segment Tree Merge | TOP-1NKYCDD1K2 |
| 680–689 | Merge / Split nâng cao | Advanced Merge-Split | TOP-HX7NK7CQYC |
| 690–699 | Bài toán tổng hợp | Merge-Split Mixed Problems | TOP-3Z4ZPCJE6Z |

### SEG7 — Segment Tree Beats

| Khoảng | Dạng trong tài liệu nguồn | Topic đích | Mã Topic |
|---|---|---|---|
| 700–709 | Segment Tree Beats cơ bản | Basic Segment Tree Beats | TOP-SEX8SCX3ZJ |
| 710–719 | Range Chmin | Range Chmin | TOP-Z6XNYF5XD8 |
| 720–729 | Range Chmax | Range Chmax | TOP-519TFY83WX |
| 730–739 | Range Chmin + Chmax | Range Chmin and Chmax | TOP-513VBJFBT7 |
| 740–749 | Range Add + Chmin | Range Add and Chmin | TOP-ETAS8T48WC |
| 750–759 | Range Add + Chmax | Range Add and Chmax | TOP-40KDD6AD7R |
| 760–769 | Range Add + Chmin + Chmax | Range Add-Chmin-Chmax | TOP-PDR5W8JEDQ |
| 770–779 | Range Modulo / phép cập nhật giảm giá trị | Range Modulo and Pruned Updates | TOP-0VYNGPA3GF |
| 780–789 | Beats kết hợp truy vấn nâng cao | Beats with Advanced Queries | TOP-0XB95351AD |
| 790–799 | Segment Tree Beats tổng hợp | Beats Mixed Problems | TOP-X2WGBW3D3Q |

### SEG8 — Hybrid Segment Tree

| Khoảng | Dạng trong tài liệu nguồn | Topic đích | Mã Topic |
|---|---|---|---|
| 800–809 | Segment Tree kết hợp Binary Search | Segment Tree with Binary Search | TOP-A69BXWT45D |
| 810–819 | Segment Tree kết hợp HLD | Segment Tree with HLD | TOP-M5MS3HZR60 |
| 820–829 | Segment Tree kết hợp Euler Tour | Segment Tree with Euler Tour | TOP-40X0TYZ0JY |
| 830–839 | Segment Tree of Vectors | Segment Tree of Vectors | TOP-YRH9T95CMB |
| 840–849 | Merge Sort Tree | Merge Sort Tree | TOP-2VTCSZGN4Q |
| 850–859 | Segment Tree 2D | Two-Dimensional Segment Tree | TOP-YWGDK94GGG |
| 860–869 | Segment Tree kết hợp Fenwick Tree | Segment Tree with Fenwick Tree | TOP-WZ8ET97KW7 |
| 870–879 | Segment Tree kết hợp Li Chao Tree | Segment Tree with Li Chao Tree | TOP-Y6T3R5DPDA |
| 880–889 | Segment Tree kết hợp thuật toán Offline | Segment Tree with Offline Algorithms | TOP-ZAGYN58C8Y |
| 890–899 | Các cấu trúc kết hợp khác | Other Hybrid Structures | TOP-6Z83W3YZDK |

### SEG9 — Specialized Segment Tree

| Khoảng | Dạng trong tài liệu nguồn | Topic đích | Mã Topic |
|---|---|---|---|
| 900–909 | Segment Tree trên trục thời gian | Segment Tree over Time | TOP-3K747Z2JEP |
| 910–919 | Segment Tree kết hợp Rollback | Segment Tree with Rollback | TOP-KH1Y7V7C41 |
| 920–929 | Dynamic Connectivity Offline | Offline Dynamic Connectivity | TOP-2H7SWSSW8M |
| 930–939 | Segment Tree trên khoảng thời gian tồn tại | Active-Interval Segment Tree | TOP-N3HW49BV66 |
| 940–949 | Segment Tree trong hình học | Segment Tree in Geometry | TOP-NN3D7DSVFQ |
| 950–959 | Sweep Line + Segment Tree | Sweep Line with Segment Tree | TOP-85QVQZD286 |
| 960–969 | Segment Tree lưu hàm | Function-Aggregating Segment Tree | TOP-E7SH2H0JMZ |
| 970–979 | Segment Tree với phép toán không giao hoán | Noncommutative Aggregation | TOP-D691HSWR06 |
| 980–989 | Các biến thể chuyên sâu khác | Other Specialized Variants | TOP-49H1JEBR8R |
| 990–999 | Bài toán tổng hợp cấp độ cao | Specialized Mixed Problems | TOP-97AGH6KF47 |

## Các quy tắc giữ riêng

- Mã Topic vẫn là TOP-…, mã bài SEG… là quy hoạch độc lập. Chuyển Topic không đổi mã bài.
- Chưa tạo bài SEG, chưa thêm validator hay bộ cấp mã SEG, chưa ghép ProblemType và chưa thay đổi mã bài hiện có.
- Các khoảng 10 mã hiện được giữ để dễ đối chiếu nguồn; đây là đề xuất cần duyệt, chưa chốt cơ chế cấp mã lâu dài. Nếu một dạng cần hơn 10 bài, phải điều chỉnh quy hoạch hoặc hệ mã riêng; không nhân bản Topic để lấy thêm chỗ.
- Mỗi bài chọn một Topic chính theo kỹ thuật mới cần rèn luyện. Các kỹ thuật bổ sung được xem xét thành Tags khi triển khai.
- Nhóm Searching, Advanced Node, Hybrid và Specialized có thể giao nhau. Bảng này không tự quyết định Topic cho bài nhiều kỹ thuật.
- Theo lưu ý của tài liệu nguồn, Range Modulo được đặt gần Beats để tổ chức học; không khẳng định mọi bài Range Modulo dùng Beats.
- Thứ tự nhóm chỉ là sắp xếp trình bày. Độ khó và lộ trình học là thuộc tính/quan hệ riêng, chưa được suy ra từ mã.

## Điểm cần duyệt về tên và phạm vi

- First Position giữ nguyên tên/mã cũ, có thêm alias First or Last Position để bao quát nhóm 110–119.
- Range Affine giữ nguyên tên/mã cũ, có alias Range Multiply cho nhóm 260–269.
- Các nhóm tổng hợp và các nhóm có phạm vi gần nhau được giữ theo nguồn để bạn duyệt; có thể tinh giản sau mà không sửa mã Topic.

## Kiểm chứng

Đã kiểm tra đủ 10 nhóm, 100 Topic đích và 100 khoảng phủ liên tục 000–999. Fixture tổng sau lần cập nhật DP có 220 Topic, 222 alias, độ sâu lớn nhất 5. Toàn bộ mã Topic cũ và quy hoạch Segment Tree được giữ nguyên. Nạp fixture hai lần trong SQLite bộ nhớ tách biệt không phát sinh bản ghi trùng; model và dữ liệu đều qua kiểm tra Django 5.2.17. Chưa kiểm chứng migration trên MariaDB và chưa tác động database dự án.
