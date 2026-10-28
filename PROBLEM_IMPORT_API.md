# API nhập đề, testcase và editorial

Base URL: `/api/v3/problem-import`.
Tài liệu OpenAPI của các endpoint được tích hợp vào `/api/v3/docs`.

## Cấp và thu hồi khóa

1. Superuser mở **Admin → Judge → Problem import API keys → Add**
   (`/admin/judge/problemimportkey/add/`).
2. Nhập tên, chọn tài khoản staff đang hoạt động làm chủ khóa và thời điểm hết hạn.
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
| Cập nhật đề / thay testcase | `judge.change_problem` và được phép sửa đề qua `Problem.is_editable_by` |
| Tạo editorial | Được phép sửa đề và `judge.add_solution` |
| Cập nhật editorial | Được phép sửa đề và `judge.change_solution` |
| Đổi trạng thái công khai của đề | Thêm `judge.change_public_visibility` |

Ví dụ staff sửa đề do mình tạo cần `judge.edit_own_problem` cùng các quyền ở bảng trên.
Nội dung đề/editorial đã bật full markup cần thêm `judge.problem_full_markup` để sửa qua API.
Đề mới tự thêm chủ khóa vào danh sách tác giả. Đề và editorial mặc định riêng tư;
API không tự duyệt đề (`approved`). Mỗi thay đổi thành công ghi log kèm ID khóa và cập nhật
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
  "partial": true
}
```

`group`, `classes`, `types` dùng trường `name` của danh mục đã có trong admin;
`allowed_languages` dùng `Language.key`. Không tự tạo các danh mục này.
Các trường bắt buộc: `code`, `name`, `description`, `group`, `classes`, `types`, `allowed_languages`.
Mã đề chỉ gồm chữ thường và chữ số, tối đa 20 ký tự; mã đề công khai phải đúng 10 ký tự
theo quy tắc hiện tại của hệ thống. Các giới hạn thời gian, bộ nhớ và điểm tuân theo cấu hình dự án.

Phản hồi:

```json
{"code":"sumdemo001","name":"Tổng hai số","is_public":false,"version_update":3}
```

## Cập nhật đề

`PATCH /api/v3/problem-import/problems/{code}` — JSON, trả `200`.

Chỉ gửi trường cần thay đổi. Các trường được hỗ trợ: `name`, `description`, `group`, `classes`,
`types`, `allowed_languages`, `time_limit`, `memory_limit`, `points`, `partial`, `short_circuit`,
`is_public`, `summary`. Không đổi mã đề qua API này. Trường lạ hoặc `null` bị từ chối.

```sh
curl -X PATCH "$BASE_URL/api/v3/problem-import/problems/sumdemo001" \
  -H "Authorization: Bearer $IMPORT_KEY" \
  -H 'Content-Type: application/json' \
  --data '{"description":"Nội dung đề mới","time_limit":2}'
```

## Nhập hoặc cập nhật testcase từ ZIP

`POST /api/v3/problem-import/problems/{code}/testcases` — multipart form, trả `200`.

Trường `upload` là ZIP. Mỗi lần gọi **thay toàn bộ testcase**, không nối thêm.
API tự ghép các cặp cùng đường dẫn/tên gốc, đuôi `.in` hoặc `.inp` và `.out` hoặc `.ans`.
Hỗ trợ thư mục con, phân biệt hoa/thường ở tên gốc; đuôi file không phân biệt hoa/thường.
Ví dụ `data/1.inp` + `data/1.out`, `data/2.in` + `data/2.ans`.
Thứ tự mặc định theo số trong tên: `1`, `2`, `10`; mỗi testcase mặc định 1 điểm, không phải pretest.

```sh
curl "$BASE_URL/api/v3/problem-import/problems/sumdemo001/testcases" \
  -H "Authorization: Bearer $IMPORT_KEY" \
  -F 'upload=@testcases.zip'
```

Để chỉ định thứ tự, điểm, pretest, checker hoặc subtask, gửi thêm trường `manifest`
chứa JSON. Có thể lưu JSON trong file và gửi bằng `-F 'manifest=<manifest.json'`.
Tên file trong manifest phải khớp chính xác đường dẫn trong ZIP.

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
Điểm của subtask được đặt ở dòng `S`. Pretest trong subtask theo dòng `S`.
Checker tích hợp hỗ trợ: `standard`, `floats`, `floatsabs`, `floatsrel`, `rstripped`, `sorted`,
`identical`, `linecount`. Từng testcase/subtask có thể đặt `checker`, `checker_args` riêng.
Custom checker được tải qua trường `custom_checker` hoặc endpoint `/checker` bên dưới.
Manifest cũng nhận `output_prefix`, `output_limit` là số nguyên không âm.

API dùng bộ biên dịch testcase hiện có để tạo `init.yml`, giữ cấu hình file I/O hiện tại,
thay generator bằng dữ liệu tĩnh. Không nhập mã generator/custom checker qua các file bên trong ZIP;
custom checker được gửi bằng một file multipart riêng. Nếu đã có custom checker và
manifest không ghi đè checker, lần nhập ZIP tiếp theo giữ cấu hình checker đó.
Đề `is_manually_managed=True` bị từ chối để tránh ghi đè dữ liệu quản lý thủ công.
File ZIP lỗi, thiếu cặp, đường dẫn không an toàn, tên trùng, symlink và file mã hóa đều bị từ chối.
Kiểm tra CRC bằng cách đọc theo từng khối, không giải nén ra thư mục.
Lỗi kiểm tra hoặc lỗi ghi file sẽ rollback SQL, giữ ZIP cũ và khôi phục `init.yml` cũ.

Giới hạn mặc định (có thể đổi trong `local_settings.py`):

| Cấu hình | Mặc định |
| --- | --- |
| `PROBLEM_IMPORT_MAX_ZIP_BYTES` | 64 MiB |
| `PROBLEM_IMPORT_MAX_UNCOMPRESSED_BYTES` | 512 MiB |
| `PROBLEM_IMPORT_MAX_ZIP_ENTRIES` | 10.000 |

Request multipart được dành thêm 1 MiB cho manifest và header; các API khác giữ giới hạn cũ.
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

Công cụ `generate.py -u` trong dự án dùng hai request: tải checker qua `/checker`
trước, rồi nhập ZIP với manifest không ghi đè checker. Cấu hình được hướng dẫn trong `README.md`.

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
- `422`: dữ liệu đề, thời gian, ZIP hoặc manifest không hợp lệ.

Trước khi dùng, chạy migration: `python manage.py migrate`.
Không cần migration dữ liệu đề/testcase hiện tại. Khóa API mới được lưu trong bảng riêng.
Các endpoint này quản lý nội dung và testcase; không thực hiện chạy thử/chấm lời giải.

Kiểm thử:

```sh
python manage.py test judge.views.api.v3.tests.test_problem_import_api \
  --keepdb --settings=tmath.problem_class_test_settings
```
