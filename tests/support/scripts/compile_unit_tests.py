#!/usr/bin/env python3
"""
Compile and run C unit tests using minunit for the philosophers project.
Scans tests/unit/ for .c files, compiles each one linking against project
source files (excluding main.c), and runs the resulting binaries.
"""

import argparse
import glob
import os
import subprocess
import sys

# ── Paths ───────────────────────────────────────────────────────────────────
ROOT = os.environ.get("PHILOSOPHERS_ROOT", os.path.abspath(
    os.path.join(os.path.dirname(__file__), "..", "..", "..")))

SRC_DIR = os.path.join(ROOT, "src")
INCLUDE_DIR = os.path.join(ROOT, "include")
UNIT_DIR = os.path.join(ROOT, "tests", "unit")
THIRD_PARTY = os.path.join(ROOT, "tests", "support", "third_party")
BIN_DIR = os.path.join(UNIT_DIR, "bin")
VALGRIND_DIR = os.path.join(BIN_DIR, "valgrind-results")

CC = "cc"
BASE_CFLAGS = [ "-Wextra", "-Werror", "-g3", "-O0",
               f"-I{INCLUDE_DIR}", f"-I{THIRD_PARTY}", f"-I{SRC_DIR}"]
LDFLAGS = ["-lpthread"]


def get_project_sources():
    """Return all .c files in src/ except main.c"""
    srcs = glob.glob(os.path.join(SRC_DIR, "**", "*.c"), recursive=True)
    return [s for s in srcs if not s.endswith("main.c")]


def get_test_sources():
    """Return all .c files in tests/unit/"""
    return glob.glob(os.path.join(UNIT_DIR, "**", "test_*.c"), recursive=True)


def compile_test(test_src, project_srcs, extra_cflags=None):
    """Compile a single test file into an executable."""
    os.makedirs(BIN_DIR, exist_ok=True)
    test_name = os.path.splitext(os.path.basename(test_src))[0]
    out_path = os.path.join(BIN_DIR, test_name)

    cmd = [CC] + BASE_CFLAGS + (extra_cflags or []) + \
          [test_src] + project_srcs + LDFLAGS + ["-o", out_path]

    print(f"\033[36m[COMPILE]\033[0m {test_name}")
    print(f"  {' '.join(cmd)}")
    result = subprocess.run(cmd)
    if result.returncode != 0:
        print(f"\033[31m[FAIL]\033[0m Compilation failed for {test_name}")
        return None
    return out_path


def run_test(binary_path, use_valgrind=False):
    """Run a compiled test binary, optionally under valgrind --tool=helgrind."""
    test_name = os.path.basename(binary_path)
    print(f"\n\033[33m[RUN]\033[0m {test_name}")

    if use_valgrind:
        os.makedirs(VALGRIND_DIR, exist_ok=True)
        log_file = os.path.join(VALGRIND_DIR, f"{test_name}.log")
        cmd = ["valgrind", "--tool=helgrind", "--log-file=" + log_file,
               binary_path]
    else:
        cmd = [binary_path]

    result = subprocess.run(cmd)
    status = "\033[32m[PASS]\033[0m" if result.returncode == 0 \
        else "\033[31m[FAIL]\033[0m"
    print(f"{status} {test_name} (exit {result.returncode})")

    if use_valgrind:
        print(f"  Helgrind log: {log_file}")

    return result.returncode == 0


def clean_bin():
    """Remove compiled test binaries."""
    import shutil
    if os.path.isdir(BIN_DIR):
        shutil.rmtree(BIN_DIR)
        print("[CLEAN] Removed", BIN_DIR)


def main():
    parser = argparse.ArgumentParser(description="Compile & run philo unit tests")
    parser.add_argument("--run", action="store_true", help="Compile and run")
    parser.add_argument("--valgrind", action="store_true",
                        help="Run under valgrind --tool=helgrind")
    parser.add_argument("--keep_bin", action="store_true",
                        help="Keep binaries after running")
    parser.add_argument("--debug", action="store_true",
                        help="Add -O0 -DDEBUG flags")
    parser.add_argument("--fsanitize", choices=["thread", "address"],
                        help="Add -fsanitize flag")
    parser.add_argument("--clean", action="store_true",
                        help="Clean test binaries")
    args = parser.parse_args()

    if args.clean:
        clean_bin()
        return

    if not args.run:
        parser.print_help()
        return

    extra_cflags = []
    if args.debug:
        extra_cflags += ["-DDEBUG"]
    if args.fsanitize:
        extra_cflags += [f"-fsanitize={args.fsanitize}"]
        LDFLAGS.append(f"-fsanitize={args.fsanitize}")

    project_srcs = get_project_sources()
    test_srcs = get_test_sources()

    if not test_srcs:
        print("\033[33m[WARN]\033[0m No test files found in", UNIT_DIR)
        sys.exit(0)

    print(f"Found {len(test_srcs)} test file(s), "
          f"{len(project_srcs)} project source(s)\n")

    results = []
    for tsrc in test_srcs:
        binary = compile_test(tsrc, project_srcs, extra_cflags)
        if binary is None:
            results.append(False)
            continue
        passed = run_test(binary, use_valgrind=args.valgrind)
        results.append(passed)

    # if not args.keep_bin:
    #     clean_bin()

    # Summary
    total = len(results)
    passed = sum(results)
    failed = total - passed
    print(f"\n{'='*50}")
    print(f"Unit tests: {passed}/{total} passed, {failed} failed")
    print(f"{'='*50}")

    if failed > 0:
        sys.exit(1)


if __name__ == "__main__":
    main()