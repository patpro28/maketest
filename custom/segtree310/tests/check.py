"""Generate and verify SEGTREE310 without HTML."""
from pathlib import Path
import runpy
runpy.run_path(str(Path(__file__).resolve().parents[2] / 'segtree_tests' / 'check_max_subarray.py'), run_name='__main__')
