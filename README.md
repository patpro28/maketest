# Library Checker Problems

![CI](https://github.com/yosupo06/library-checker-problems/workflows/CI/badge.svg)
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://github.com/yosupo06/library-checker-problems/blob/master/LICENSE)

Source code of [https://judge.yosupo.jp](https://judge.yosupo.jp). You can get test cases of problems from this repository.

## Requirements

- Linux / OS X / Windows(MinGW-w64)
- python3.6+
- g++ / clang++ (Needs --std=c++14 and __int128_t)

## How to Use

```sh
cd /path/to/library-checker-problems

pip3 install -r requirements.txt
# or pip3 install colorlog markdown jinja2

ulimit -s unlimited # for linux (doesn't need for OS X and WSL)

./generate.py -p unionfind # generate testcases of unionfind
# or ./generate.py datastructure/unionfind/info.toml

ls datastructure/unionfind/in/ # testcases of unionfind
ls datastructure/unionfind/out/ # solutions of unionfind
file datastructure/unionfind/checker # binary of output checker
```

### For developer

```sh
./generate.py -p unionfind --dev # developer mode
./generate.py -p unionfind --test # test mode (for developer, exec this command before PR)
cat datastructure/unionfind/task.html # statement

./generate.py $(find . -name "info.toml" -not -path "./test/*") # generate all testcases
```

### Tải bài lên qua Problem Import API

Khai báo máy chủ và khóa API qua biến môi trường:

```sh
export HOST='https://judge.example.com'
export PROBLEM_IMPORT_API_KEY='<khóa nhập đề>'

./generate.py -u knapsack00 knapsack01
# Hoặc dùng danh sách bài / đường dẫn info.toml như khi sinh test:
./generate.py -p knapsack00 --upload
./generate.py custom/knapsack00/info.toml -u
```

`HOST` nhận URL máy chủ, có thể kèm `/api/v3/problem-import`. Nếu chỉ ghi tên
miền, công cụ dùng HTTPS. Khóa được gửi trong header `Authorization: Bearer`.

Thêm bảng sau vào `info.toml` của từng bài. Các giá trị phải khớp danh mục đã có
trên máy chủ; ví dụ dưới đây cần được thay bằng danh mục thực tế:

```toml
[upload]
group = 'basic'
classes = 'beginner'
types = ['implementation']
allowed_languages = ['PY3', 'CPP17']
# Các trường tùy chọn:
memory_limit = 65536  # KiB
points = 100
partial = true
checker = 'standard'
```

- Mã bài là tên thư mục chuyển sang chữ thường; chỉ nhận chữ cái và chữ số,
  tối đa 20 ký tự theo API.
- Tên bài lấy từ heading cấp một (`# ...`) đầu tiên trong `task.md`. Dòng này
  được bỏ khỏi nội dung đề gửi lên; các dòng còn lại giữ nguyên Markdown.
  Nếu không có heading cấp một, tên bài lấy từ `title` trong `info.toml`.
- Giới hạn thời gian lấy từ `timelimit`, có thể ghi đè bằng `[upload].time_limit`.
  Các trường tùy chọn khác gồm `short_circuit`, `is_public`, `summary`.
  Đề mới mặc định riêng tư theo API.
- Công cụ sinh hoặc dùng lại testcase, đối chiếu `hash.json`, rồi gửi ZIP chứa
  các cặp `.in`/`.out` theo thứ tự trong `[[tests]]`. Mỗi lần upload thay toàn bộ
  testcase trên máy chủ. Dữ liệu `in/`, `out/` cục bộ được giữ lại.
- Editorial lấy từ `editorial.md`, hoặc `solution.md` nếu không có `editorial.md`.
  Có thể đặt `[upload].editorial = 'đường/dẫn.md'` tính từ thư mục bài. Editorial
  được gửi với trạng thái riêng tư mặc định của API; không có file thì bỏ qua bước này.
- Nếu mã bài đã tồn tại (HTTP 409 khi tạo), công cụ cập nhật đề bằng `PATCH`.
  Nếu một bước lỗi, công cụ dừng và báo bước lỗi; các bước đã thành công trên
  máy chủ vẫn được giữ. Có thể chạy lại cùng lệnh sau khi sửa lỗi.
- Upload không xuất HTML và không dùng cùng `--dev`, `--test`, `--clean`,
  `--only-html`, `--htmldir`, `--new` hoặc `--zip`.

API chỉ nhận các checker tích hợp được liệt kê trong
[PROBLEM_IMPORT_API.md](PROBLEM_IMPORT_API.md), không tải custom checker C++ lên.
`checker` mặc định là `standard`; chọn checker phù hợp cho từng bài.
Để đặt điểm, pretest, subtask hoặc tùy chọn checker, đặt
`[upload].manifest = 'manifest.json'`. Nội dung JSON tuân theo tài liệu API,
ghi đè manifest mặc định. Đường dẫn testcase trong manifest là tên file phẳng
trong ZIP, ví dụ `example_00.in`, `example_00.out`, `random_00.in`.

Kiểm thử chức năng upload bằng máy chủ giả lập cục bộ:

```sh
python3 -m unittest problem_upload_test
```

## Test your solutions in local / CI

- If you want to test your solutions on your computer, [Online Judge Tools](https://github.com/online-judge-tools/oj) is useful.
- If you want to use Github Actions for testing your library by our problems, [Online Judge Verify Helper](https://github.com/online-judge-tools/verification-helper) is useful.

## If you have any trouble

- Create issue: we are very happy if you report any of our mistakes (e.g. test cases are weak, strange behavior of the site, English of statements is bad, ...). Anything others are also welcome.
- Codeforces: https://codeforces.com/blog/entry/76945
- Twitter: if you tweet your trouble with hashtag \#LibraryChecker, we are going to help you. The account of admin is [@yosupot](https://twitter.com/yosupot).

## 困ったときは(If you have any trouble - Japanese edition)

- issueを立てる: githubにはissueというTODOやバグなどをメモっておく機能があります。上の Issues → New issueから作成できます。
- Twitter で \#LibraryChecker というハッシュタグをつけて呟いてくれると、助けに行きます。[@yosupot](https://twitter.com/yosupot) へリプライ / DM でも大丈夫です。

## Contributing

We are welcome any issues and PRs! Except minor change (e.g. add test cases, fix statements), please create an issue first.

## Contributing - Japanese Edition

不具合(テストケースが弱い, ジャッジが異常な挙動をする, 問題文にtypoを発見, などなど)を発見したとき、報告していただけるととっても助かります。

基本的には上に書いたようにissueを立ててもらえると助かります。
熱意がある人は[CONTRIBUTING](docs/CONTRIBUTING.md) を参考にPull requestを送っていただけるととても助かります。

競プロerは必ずしもgithubに慣れているとは限らず、issue / pull request を送ったことがない人も少なくはないというのを理解しています。どれだけめちゃくちゃなものを送ってきても怒ったりこのリポジトリが壊れたりすることはないので、githubの練習がてら挑戦してみるというのもアリです(頑張ってサポートします)。

## File structure / How to create the problem

[guideline(en)](docs/guideline.en.md)

[guideline(日本語)](docs/guideline.md)

## library-checker-project

- problems: [library-checker-problems](https://github.com/yosupo06/library-checker-problems)
- judge: [library-checker-judge](https://github.com/yosupo06/library-checker-judge)
- frontend: [library-checker-frontend](https://github.com/yosupo06/library-checker-frontend)

## Thanks

We use [testlib](https://github.com/MikeMirzayanov/testlib) for verifier(input-checker) and output-checker.
We use [toml](https://github.com/uiri/toml) as toml paser.


docker run --rm \
  --network host \
  -v /opt/db-backups/laptrinhphothong:/backup \
  -v "$HOME/.config/mydumper/source.cnf:/run/db.cnf:ro" \
  --entrypoint mydumper \
  mydumper/mydumper:latest \
  --defaults-file=/run/db.cnf \
  --database=laptrinhphothong \
  --outputdir=/backup \
  --threads=4 \
  --compress=zstd \
  --verbose=3