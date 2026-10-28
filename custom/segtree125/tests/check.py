"""Generate and verify this SEG1 problem without HTML."""
from pathlib import Path
import runpy
import sys
HERE = Path(__file__).resolve()
sys.argv[1:1] = ["--problem", HERE.parents[1].name]
runpy.run_path(str(HERE.parents[2] / "segtree_tests" / "check_search_early.py"), run_name="__main__")
