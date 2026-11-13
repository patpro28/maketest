"""Convert a statement's displayed hexadecimal sample into a real binary file."""
from pathlib import Path
import argparse
import re

parser = argparse.ArgumentParser()
parser.add_argument('problem', choices=[f'a109{k:06d}' for k in range(1, 11)])
parser.add_argument('sample', type=int, choices=[1, 2])
parser.add_argument('output', type=Path)
args = parser.parse_args()
root = Path(__file__).resolve().parents[2]
text = (root / 'custom' / args.problem / 'task.md').read_text()
dump = re.search(rf'### Sample Input {args.sample}\n\n```text\n(.*?)\n```', text, re.S)[1]
args.output.write_bytes(bytes.fromhex(dump))
print(f'Wrote {args.output.stat().st_size} binary bytes to {args.output}')
