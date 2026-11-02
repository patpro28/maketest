"""Generate and verify SEGTREE005 without HTML."""
from pathlib import Path
import runpy
runpy.run_path(str(Path(__file__).resolve().parents[2] / 'segtree_tests' / 'check_static_max_count.py'), run_name='__main__')
