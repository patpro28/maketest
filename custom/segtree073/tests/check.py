"""Generate and verify SEGTREE073 without HTML."""
from pathlib import Path
import runpy
runpy.run_path(str(Path(__file__).resolve().parents[2] / 'segtree_tests' / 'check_equalize.py'), run_name='__main__')
