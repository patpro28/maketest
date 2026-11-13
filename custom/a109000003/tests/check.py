from pathlib import Path
import runpy
import sys
sys.argv[1:1] = ['--problem', 'a109000003']
runpy.run_path(str(Path(__file__).resolve().parents[2] / 'a109_tests/check.py'), run_name='__main__')
