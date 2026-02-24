"""
Shared fixtures for philosophers e2e tests.
"""

import os
import subprocess
import time

import pexpect
import pytest

ROOT = os.environ.get("PHILOSOPHERS_ROOT",
                      os.path.abspath(os.path.join(os.path.dirname(__file__),
                                                   "..", "..")))
PHILO_BIN = os.path.join(ROOT, "philo")


@pytest.fixture(scope="session", autouse=True)
def build_philo():
    """Compile philo before the test session."""
    result = subprocess.run(["make", "-C", ROOT, "re"],
                            capture_output=True, text=True)
    if result.returncode != 0:
        pytest.fail(f"make failed:\n{result.stderr}")
    assert os.path.isfile(PHILO_BIN), f"Binary not found: {PHILO_BIN}"
    yield
    # Optional: clean after
    # subprocess.run(["make", "-C", ROOT, "fclean"])


@pytest.fixture
def run_philo():
    """
    Returns a helper function to spawn philo with given args.
    Usage:
        child = run_philo("5 800 200 200")
    """
    children = []

    def _run(args_str, timeout=10):
        cmd = f"{PHILO_BIN} {args_str}"
        child = pexpect.spawn(cmd, timeout=timeout, encoding="utf-8")
        children.append(child)
        return child

    yield _run

    for c in children:
        if c.isalive():
            c.terminate(force=True)


@pytest.fixture
def run_philo_valgrind():
    """
    Same as run_philo but under valgrind --tool=helgrind.
    """
    children = []

    def _run(args_str, timeout=30):
        cmd = (f"valgrind --tool=helgrind --error-exitcode=42 "
               f"{PHILO_BIN} {args_str}")
        child = pexpect.spawn(cmd, timeout=timeout, encoding="utf-8")
        children.append(child)
        return child

    yield _run

    for c in children:
        if c.isalive():
            c.terminate(force=True)