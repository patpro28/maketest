"""Run the shared audit for dpstr600."""
from pathlib import Path
import runpy
import sys
sys.argv[1:1]=['--problem','dpstr600']
runpy.run_path(str(Path(__file__).resolve().parents[2]/'dpstr_palindrome_tests/check.py'),run_name='__main__')
