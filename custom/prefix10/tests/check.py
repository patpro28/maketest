from pathlib import Path
import runpy
import sys
here = Path(__file__).resolve()
sys.argv[1:1] = ["--problem", here.parents[1].name]
runpy.run_path(str(here.parents[2] / "prefix_tests/check_sum.py"), run_name="__main__")
