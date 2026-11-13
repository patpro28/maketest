# API nhập đề, testcase và editorial

Base URL: `/api/v3/problem-import`.
Tài liệu OpenAPI của các endpoint được tích hợp vào `/api/v3/docs`.

## Cấp và thu hồi khóa

1. Superuser mở **Admin → Judge → Problem import API keys → Add**
   (`/admin/judge/problemimportkey/add/`).
2. Nhập tên, chọn tài khoản staff đang hoạt động làm chủ khóa và thời điểm hết hạn.
   Bật **Allow approve** (`allow_approve`) nếu muốn tự duyệt bài khi nhập qua khóa này.
   Có thể bật/tắt tùy chọn này trên khóa đã cấp mà không cần tạo lại chuỗi khóa.
3. Lưu và sao chép khóa trên trang kết quả. Khóa chỉ được hiển thị trong phản hồi tạo mới;
   không được lưu dưới dạng chuỗi có thể dùng để gọi API trong database.
4. Gửi khóa qua header `Authorization: Bearer <key>` ở mỗi request.
5. Để thu hồi, chọn khóa ở danh sách và chạy **Revoke selected API keys**.
   Muốn gia hạn hoặc đổi chủ sở hữu, tạo khóa mới.

Khóa có chữ ký HMAC bằng Django `SECRET_KEY` với salt riêng, gắn với định danh khóa,
chủ sở hữu và hạn dùng. Cần giữ bí mật `SECRET_KEY` và sử dụng HTTPS ở môi trường thật.
Khóa hết hạn, bị thu hồi/xóa hoặc có chủ sở hữu bị vô hiệu hóa/bỏ quyền staff sẽ bị từ chối.
API dùng quyền hiện tại của chủ khóa, không kế thừa quyền của người cấp khóa.
JWT đăng nhập frontend không thay thế được khóa nhập đề và khóa nhập đề không dùng để đăng nhập frontend.

Quyền cần thiết:

| Thao tác | Quyền của chủ khóa |
| --- | --- |
| Tạo đề | `judge.add_problem` |
| Cập nhật đề / thay testcase / upload checker | `judge.change_problem` và được phép sửa đề qua `Problem.is_editable_by` |
| Tạo editorial | Được phép sửa đề và `judge.add_solution` |
| Cập nhật editorial | Được phép sửa đề và `judge.change_solution` |
| Đổi trạng thái công khai của đề | Thêm `judge.change_public_visibility` |
| Tự động duyệt đề | Khóa bật `allow_approve` và chủ khóa có `profile.super_admin`, như quyền duyệt trong admin |

Ví dụ staff sửa đề do mình tạo cần `judge.edit_own_problem` cùng các quyền ở bảng trên.
Nội dung đề/editorial đã bật full markup cần thêm `judge.problem_full_markup` để sửa qua API.
Đề mới tự thêm chủ khóa vào danh sách tác giả. Đề và editorial mặc định riêng tư;
`allow_approve` mặc định tắt, kể cả với khóa đã có. Khi bật và chủ khóa có quyền duyệt,
API tự đặt `approved = true` khi tạo/cập nhật đề, upload testcase/checker hoặc cập nhật editorial thành công.
Không cần và không được gửi `approved` trong payload; phản hồi trả trạng thái `approved` hiện tại.
Nếu khóa không bật tùy chọn hoặc chủ khóa không còn quyền duyệt, thao tác nhập vẫn thực hiện
theo quyền thông thường và giữ nguyên trạng thái duyệt của đề. Tự duyệt không tự công khai đề.
Mỗi thay đổi thành công ghi log kèm ID khóa và cập nhật
`last_used_at`. Không ghi chuỗi khóa vào log.

## Tạo đề

`POST /api/v3/problem-import/problems` — JSON, trả `201`.

```json
{
  "code": "sumdemo001",
  "name": "Tổng hai số",
  "description": "Cho hai số nguyên a và b. Hãy tính tổng a + b.",
  "group": "basic",
  "classes": "beginner",
  "types": ["implementation"],
  "allowed_languages": ["PY3", "CPP17"],
  "time_limit": 1,
  "memory_limit": 65536,
  "points": 100,
  "partial": true,
  "io_method": "standard"
}
```

`group`, `classes`, `types` dùng trường `name` của danh mục đã có trong admin;
`allowed_languages` dùng `Language.key`. Không tự tạo các danh mục này.
Các trường bắt buộc: `code`, `name`, `description`, `group`, `classes`, `types`, `allowed_languages`.
Mã đề chỉ gồm chữ thường và chữ số, tối đa 20 ký tự; mã đề công khai phải có từ 8 đến 10 ký tự
theo quy tắc hiện tại của hệ thống. Các giới hạn thời gian, bộ nhớ và điểm tuân theo cấu hình dự án.
Có thể cấu hình cách vào/ra ngay khi tạo bằng `io_method`, `io_input_file`, `io_output_file`
như phần bên dưới. Khi không gửi các trường này, giữ hành vi mặc định hiện tại;
chưa tạo cấu hình I/O riêng cho đề.

Phản hồi:

```json
{"code":"sumdemo001","name":"Tổng hai số","is_public":false,"approved":false,"version_update":3}
```

## Cập nhật đề

`PATCH /api/v3/problem-import/problems/{code}` — JSON, trả `200`.

Chỉ gửi trường cần thay đổi. Các trường được hỗ trợ: `name`, `description`, `group`, `classes`,
`types`, `allowed_languages`, `time_limit`, `memory_limit`, `points`, `partial`, `short_circuit`,
`is_public`, `summary`, `io_method`, `io_input_file`, `io_output_file`.
Không đổi mã đề qua API này. Trường lạ hoặc `null` bị từ chối.

```sh
curl -X PATCH "$BASE_URL/api/v3/problem-import/problems/sumdemo001" \
  -H "Authorization: Bearer $IMPORT_KEY" \
  -H 'Content-Type: application/json' \
  --data '{"description":"Nội dung đề mới","time_limit":2}'
```

### Cấu hình cách vào/ra (`io_method`)

Các trường sau dùng được cho cả `POST` tạo đề và `PATCH` cập nhật đề:

| Trường | Giá trị / ý nghĩa |
| --- | --- |
| `io_method` | `"standard"` để đọc `stdin`, ghi `stdout`; `"file"` để vào/ra bằng file. |
| `io_input_file` | Tên file chương trình đọc khi dùng `"file"`, ví dụ `"SUM.INP"`. |
| `io_output_file` | Tên file chương trình ghi khi dùng `"file"`, ví dụ `"SUM.OUT"`. |

Ví dụ chuyển đề sang vào/ra file và đặt tên file `.inp`, `.out`:

```sh
curl -X PATCH "$BASE_URL/api/v3/problem-import/problems/sumdemo001" \
  -H "Authorization: Bearer $IMPORT_KEY" \
  -H 'Content-Type: application/json' \
  --data '{"io_method":"file","io_input_file":"SUM.INP","io_output_file":"SUM.OUT"}'
```

- Khi bật `"file"`, phải có đủ hai tên file. Với `PATCH`, tên không gửi được giữ từ
  cấu hình cũ; nếu đề đã dùng file thì có thể chỉ gửi một tên để đổi riêng tên đó.
- Tên file dài 1–100 ký tự, không rỗng/toàn khoảng trắng, không chứa đường dẫn,
  `/`, `\`, ký tự điều khiển và không được là `.` hoặc `..`. Giữ nguyên hoa/thường;
  không bắt buộc phần mở rộng `.inp`/`.out`.
- Tên này là tên file **chương trình dùng khi chạy**, độc lập với
  `cases[].input_file`/`cases[].output_file` là đường dẫn testcase trong ZIP.
- Gửi `{"io_method":"standard"}` để trở về `stdin`/`stdout` và xóa hai tên file cũ.
  Không gửi tên file cùng `"standard"`; chỉ gửi tên file khi cấu hình hiệu lực là `"file"`.
- Không gửi cả ba trường thì giữ nguyên cấu hình I/O. Gửi `null`, giá trị phương thức
  khác hoặc thiếu tên file khi bật `"file"` trả `422`. Đề quản lý thủ công từ chối
  thay đổi I/O bằng `409`.
- Thay đổi I/O cập nhật cấu hình chấm `init.yml`, giữ ZIP, testcase, generator và checker.
  Có thể cấu hình trước khi upload testcase; các lần upload testcase/checker sau giữ
  cấu hình này. Nếu kiểm tra hoặc ghi cấu hình thất bại, hoàn tác thay đổi đề và I/O.

## Nhập hoặc cập nhật testcase từ ZIP

`POST /api/v3/problem-import/problems/{code}/testcases` — multipart form, trả `200`.

Trường `upload` là ZIP. Mỗi lần gọi **thay toàn bộ testcase**, không nối thêm.
Có thể gửi thêm file `custom_checker` (`.cpp` hoặc `.py`) để nhập checker cùng lần upload.
API tự ghép các cặp cùng đường dẫn/tên gốc, đuôi `.in` hoặc `.inp` và `.out` hoặc `.ans`.
Hỗ trợ thư mục con, phân biệt hoa/thường ở tên gốc; đuôi file không phân biệt hoa/thường.
Ví dụ `data/1.inp` + `data/1.out`, `data/2.in` + `data/2.ans`.
Thứ tự mặc định theo số trong tên: `1`, `2`, `10`; mỗi testcase mặc định 1 điểm, không phải pretest.

```sh
curl "$BASE_URL/api/v3/problem-import/problems/sumdemo001/testcases" \
  -H "Authorization: Bearer $IMPORT_KEY" \
  -F 'upload=@testcases.zip'
```

`manifest` là trường form tùy chọn chứa **chuỗi JSON object**, mặc định `"{}"`.
API hiện chỉ nhận các trường cấp manifest sau; trường lạ bị từ chối bằng `422`:

| Trường | Giá trị và hành vi |
| --- | --- |
| `cases` | Danh sách testcase/subtask theo thứ tự muốn chấm, ít nhất một phần tử. Bỏ trường này hoặc gửi `null` để tự ghép file trong ZIP. Danh sách phải có ít nhất một dòng `C`. |
| `checker` | Loại checker chung. Nếu bỏ qua, giữ checker hiện tại; nếu chưa có cấu hình thì dùng `standard`. Khi upload `custom_checker` cùng request và bỏ `checker`, dùng `bridged`. |
| `checker_args` | JSON object. Bỏ qua để giữ args cũ khi không đổi checker và không upload checker mới; các trường hợp còn lại mặc định `{}`. Gửi `{}` để xóa args cũ. Không nhận `null`. |
| `output_prefix` | Số nguyên từ `0` đến `2147483647`, hoặc `null`. Ánh xạ sang `output_prefix_length` trong `init.yml`. Bỏ qua hoặc gửi `null` sẽ xóa giới hạn cũ. |
| `output_limit` | Số nguyên từ `0` đến `2147483647`, hoặc `null`. Ánh xạ sang `output_limit_length` trong `init.yml`. Bỏ qua hoặc gửi `null` sẽ xóa giới hạn cũ. |
| `binary_data` | Boolean JSON `true`/`false`. `true` ghi `binary_data: true` vào `init.yml` để giữ nguyên byte input/output khi judge đọc testcase. Bỏ qua để giữ cờ hiện tại; đề chưa có cờ mặc định `false`. Không nhận `null`, chuỗi hoặc số. |

Với testcase nhị phân, gửi rõ `binary_data: true`; API không tự nhận diện theo
nội dung hay phần mở rộng file:

```sh
curl "$BASE_URL/api/v3/problem-import/problems/sumdemo001/testcases" \
  -H "Authorization: Bearer $IMPORT_KEY" \
  -F 'upload=@binary-testcases.zip' \
  -F 'manifest={"binary_data":true}'
```

Có thể kết hợp `binary_data` với `cases`, checker và các trường khác trong bảng.
Cờ áp dụng cho toàn bộ bộ test, không đặt ở từng dòng `cases`.
Khi bật, judge không chuẩn hóa xuống dòng hoặc tự thêm newline vào dữ liệu test;
byte `0D` giữ nguyên giá trị `13`, không bị đổi thành `0A` (giá trị `10`).
Gửi `binary_data: false` để tắt và dùng lại xử lý văn bản mặc định của judge.

Cờ được lưu trong database và giữ qua các lần nhập lại ZIP không gửi trường này,
upload checker, đổi I/O hoặc tạo lại cấu hình pretest. Với cờ đã sửa tay trước đây,
API giữ `binary_data: true` nếu đọc được cờ đó trong `init.yml` hiện tại ở vùng
dữ liệu dùng chung; API không đọc được file chỉ tồn tại riêng trên máy chấm khác.
Phản hồi upload testcase có thêm `binary_data` là boolean cho biết cờ hiệu lực.

**API chưa hỗ trợ `points` ở cấp manifest**, kể cả dạng object ánh xạ tên file sang điểm;
gửi trường này trả `422`. Để đặt điểm riêng, phải khai báo `cases` với
`input_file`, `output_file`, `points` cho từng testcase:

```sh
curl "$BASE_URL/api/v3/problem-import/problems/sumdemo001/testcases" \
  -H "Authorization: Bearer $IMPORT_KEY" \
  -F 'upload=@testcases.zip' \
  -F 'manifest={"cases":[{"input_file":"data/1.inp","output_file":"data/1.out","points":10},{"input_file":"data/2.in","output_file":"data/2.ans","points":20}]}'
```

Khi gửi `cases`, API dùng đúng thứ tự danh sách, không tự ghép hay tự thêm các
testcase khác trong ZIP. Tên file phải khớp chính xác đường dẫn trong ZIP, gồm
thư mục con và hoa/thường; không bắt buộc đuôi `.in`/`.inp`/`.out`/`.ans`.
Mỗi dòng chỉ nhận các trường sau:

| Trường | Giá trị / mặc định |
| --- | --- |
| `type` | `"C"` (testcase, mặc định), `"S"` (bắt đầu subtask), `"E"` (kết thúc subtask). |
| `input_file`, `output_file` | Chuỗi tối đa 100 ký tự. Với dòng `C`, cả hai phải trỏ đến file có trong ZIP. Không cần gửi ở dòng `S`/`E`. |
| `points` | Số nguyên từ `0` đến `2147483647`, mặc định `1`, không nhận `null`. Là điểm/trọng số testcase hoặc subtask, không thay tổng điểm `Problem.points` của đề. |
| `is_pretest` | Boolean, mặc định `false`. Trong subtask, lấy giá trị của dòng `S`. |
| `checker` | Loại checker riêng cho dòng `C`/`S`; bỏ qua hoặc gửi `""` để kế thừa checker của subtask/đề. |
| `checker_args` | JSON object, mặc định `{}`, không nhận `null`. Chỉ có tác dụng khi dòng đó đặt `checker` khác rỗng. |

Nên gửi các trường số nguyên bằng số nguyên JSON. Validator hiện có ép kiểu:
ví dụ `cases[].points` nhận cả `"10"`, `10.0` thành `10` và `true` thành `1`;
số thập phân có phần lẻ như `1.5` bị từ chối.
Không nhận `output_prefix`/`output_limit` ở từng dòng `cases`.
`io_method`, `io_input_file`, `io_output_file` cũng không thuộc manifest;
cấu hình chúng qua API tạo/cập nhật đề ở phần trên.

Ví dụ kết hợp testcase riêng với subtask. Có thể lưu JSON sau trong file và gửi
bằng `-F 'manifest=<manifest.json'`:

```json
{
  "checker": "standard",
  "checker_args": {},
  "cases": [
    {"input_file":"samples/1.in","output_file":"samples/1.out","points":10,"is_pretest":true},
    {"type":"S","points":90},
    {"input_file":"tests/2.in","output_file":"tests/2.out"},
    {"input_file":"tests/3.in","output_file":"tests/3.out"},
    {"type":"E"}
  ]
}
```

`S` bắt đầu subtask, `E` kết thúc; `C` là testcase thông thường (mặc định).
Điểm và trạng thái pretest của subtask được đặt ở dòng `S`; `points` và
`is_pretest` của các dòng `C` bên trong không quyết định điểm/pretest của nhóm.
Không có subtask lồng nhau: gặp `S` tiếp theo sẽ kết thúc nhóm trước và mở nhóm mới;
nhóm cuối cũng tự kết thúc khi hết danh sách, nên `E` có thể bỏ qua.
Nhóm rỗng hoặc `E` nằm ngoài nhóm bị từ chối bằng `422`.
Dòng `E` chỉ đóng nhóm; không dùng điểm, pretest hay checker đặt trên dòng này.
Checker hỗ trợ: `standard`, `floats`, `floatsabs`, `floatsrel`, `rstripped`, `sorted`,
`identical`, `linecount`. Từng testcase/subtask có thể đặt `checker`, `checker_args` riêng.
Chọn `bridged` để dùng file custom checker đã upload (C++ hoặc Python); dùng chung một file
checker cho các testcase/subtask chọn `bridged`.

API dùng bộ biên dịch testcase hiện có để tạo `init.yml`, giữ cấu hình file I/O hiện tại,
thay generator bằng dữ liệu tĩnh. Khi không gửi trường `checker` trong manifest, API giữ checker
hiện tại; nếu gửi file `custom_checker` thì mặc định kích hoạt `bridged`. `checker_args` hiện tại
được giữ khi không chỉ định args mới, không đổi loại checker và không thay file checker.
Gửi `"checker":"standard"` để chuyển về checker mặc định. Nếu gửi file custom checker cùng
một lựa chọn built-in rõ ràng, cần có ít nhất một testcase/subtask chọn `bridged`.
Không nhập mã generator; checker phải là file multipart riêng, không tự trích mã checker từ ZIP.
Đề `is_manually_managed=True` bị từ chối để tránh ghi đè dữ liệu quản lý thủ công.
File ZIP lỗi, đường dẫn không an toàn, tên trùng, symlink và file mã hóa đều bị từ chối.
Khi tự ghép testcase, thiếu cặp hoặc có nhiều input/output cho cùng tên gốc bị từ chối;
khi khai báo `cases`, API kiểm tra các file được tham chiếu trong danh sách đó.
Kiểm tra CRC bằng cách đọc theo từng khối, không giải nén ra thư mục.
Lỗi kiểm tra hoặc lỗi ghi file sẽ rollback SQL, giữ ZIP cũ và khôi phục `init.yml` cũ.

Giới hạn mặc định (có thể đổi trong `local_settings.py`):

| Cấu hình | Mặc định |
| --- | --- |
| `PROBLEM_IMPORT_MAX_ZIP_BYTES` | 64 MiB |
| `PROBLEM_IMPORT_MAX_CHECKER_BYTES` | 1 MiB |
| `PROBLEM_IMPORT_MAX_UNCOMPRESSED_BYTES` | 512 MiB |
| `PROBLEM_IMPORT_MAX_ZIP_ENTRIES` | 10.000 |

`PROBLEM_IMPORT_MAX_ZIP_ENTRIES` cũng giới hạn tổng số dòng `cases`, gồm cả `S` và `E`;
vượt giới hạn trả `413`.
Request multipart được dành thêm dung lượng checker và 1 MiB cho manifest/header;
các API khác giữ giới hạn cũ.
Cần đồng bộ giới hạn upload ở reverse proxy nếu triển khai qua proxy.

## Upload hoặc thay custom checker

`POST /api/v3/problem-import/problems/{code}/checker` — multipart form, trả `200`.

```sh
curl "$BASE_URL/api/v3/problem-import/problems/sumdemo001/checker" \
  -H "Authorization: Bearer $IMPORT_KEY" \
  -F 'upload=@checker.cpp' \
  -F 'checker_args={"time_limit":3}'
```

- `upload`: mã nguồn `.cpp` (checker C++ theo chuẩn testlib) hoặc `.py` (hàm `check` của DMOJ).
- `checker_args`: JSON object tùy chọn, mặc định `{}`. Khi thay file, args cũ được thay bằng args này.
- Mã nguồn phải là UTF-8, không rỗng, không chứa byte NUL; dung lượng tối đa mặc định 1 MiB.
- API lưu file với tên riêng, kích hoạt `ProblemData.checker="bridged"` và tạo lại `init.yml`.
  Checker C++ mặc định có `lang="CPP17"`, `type="testlib"`; `files` luôn trỏ đến file vừa lưu.
  Checker Python được tham chiếu trực tiếp theo tên file trong `init.yml`, cùng args nếu có.
- Upload checker giữ nguyên ZIP, danh sách testcase và cấu hình file I/O hiện tại.
  Có thể upload checker trước testcase; lần nhập ZIP tiếp theo sẽ giữ checker đó.
- File checker cũ chỉ được dọn sau khi lưu thành công. Nếu có lỗi, SQL và cấu hình chấm được
  khôi phục; file checker mới được xóa. Đề quản lý thủ công bị từ chối bằng `409`.
- API chỉ lưu và cấu hình checker; không chạy/biên dịch mã nguồn trên web server.
  Judge thực hiện bước đó khi chấm bài; hệ thống judge cần hỗ trợ ngôn ngữ/thư viện tương ứng.

Upload ZIP và checker trong cùng request:

```sh
curl "$BASE_URL/api/v3/problem-import/problems/sumdemo001/testcases" \
  -H "Authorization: Bearer $IMPORT_KEY" \
  -F 'upload=@testcases.zip' \
  -F 'custom_checker=@checker.cpp' \
  -F 'manifest={"checker":"bridged","checker_args":{"time_limit":3}}'
```

## Tạo hoặc thay editorial

`PUT /api/v3/problem-import/problems/{code}/editorial` — JSON, trả `200`.

```json
{
  "content": "## Ý tưởng\nĐọc hai số, in tổng.\n\nĐộ phức tạp: O(1).",
  "is_public": false,
  "publish_on": "2026-10-20T08:00:00+07:00"
}
```

`content` là Markdown bắt buộc. Mặc định `is_public=false`, `publish_on` là thời điểm gọi API.
Thời gian chỉ định phải có múi giờ. Gọi lại cập nhật cùng editorial của đề và thêm chủ khóa vào tác giả.

## Mã lỗi và triển khai

- `401`: thiếu/sai khóa, chữ ký sai, hết hạn, thu hồi hoặc chủ khóa không còn hoạt động/staff.
- `403`: thiếu quyền thao tác hoặc không được sửa đề.
- `404`: mã đề không tồn tại.
- `409`: mã đề đã tồn tại hoặc testcase của đề được quản lý thủ công.
- `413`: vượt giới hạn kích thước/số lượng.
- `422`: dữ liệu đề, thời gian, ZIP, manifest hoặc mã nguồn/tham số checker không hợp lệ.

Trước khi dùng, chạy migration: `python manage.py migrate`.
Migration `0252_problemdata_binary_data` bổ sung cột lưu cờ nhị phân, mặc định `false`;
không thay nội dung ZIP/testcase hiện tại. Khóa API mới được lưu trong bảng riêng.
Các endpoint này quản lý nội dung và testcase; không thực hiện chạy thử/chấm lời giải.

Kiểm thử:

```sh
python manage.py test judge.views.api.v3.tests.test_problem_import_api \
  --keepdb --settings=tmath.problem_class_test_settings
```
