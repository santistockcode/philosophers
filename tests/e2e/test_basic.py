"""
E2E tests: basic philosophers behavior.
"""

import re
import time

import pexpect
import pytest

import pdb


class TestArgValidation:
    """Test argument validation."""

    def test_no_args(self, run_philo):
        child = run_philo("", timeout=5)
        child.expect(pexpect.EOF)
        # Should exit quickly with an error
        child.close()
        assert child.exitstatus != 0 or child.signalstatus is not None

    def test_negative_args(self, run_philo):
        child = run_philo("-5 800 200 200", timeout=5)
        child.expect(pexpect.EOF)
        child.close()
        assert child.exitstatus != 0

    def test_invalid_args_1(self, run_philo):
        child = run_philo("abc 800 200 200", timeout=5)
        child.expect(pexpect.EOF)
        child.close()
        assert child.exitstatus != 0

    def test_invalid_args_last(self, run_philo):
        child = run_philo("15 800 200 200 xyz", timeout=5)
        child.expect(pexpect.EOF)
        child.close()
        assert child.exitstatus != 0

    def test_zero_philos(self, run_philo):
        child = run_philo("0 800 200 200", timeout=5)
        child.expect(pexpect.EOF)
        child.close()
        assert child.exitstatus != 0

    def test_non_numeric(self, run_philo):
        child = run_philo("five 800 200 200", timeout=5)
        child.expect(pexpect.EOF)
        child.close()
        assert child.exitstatus != 0


class TestBasicExecution:
    """Test that philos produce expected output format."""

    def test_one_philo_dies(self, run_philo):
        """One philosopher should die (can't take 2 forks)."""
        child = run_philo("1 800 200 200", timeout=5)
        child.expect(r"\d+\s+1\s+died")
        child.close()

    #1407 \t1 \tis sleeping\r\n
    def test_output_format(self, run_philo):
        """Every line should match: <timestamp> <id> <action>"""
        # pdb.set_trace()
        child = run_philo("4 800 200 200 3", timeout=10)
        child.expect(pexpect.EOF)
        output = child.before
        lines = [l.strip() for l in output.strip().split("\n") if l.strip()]
        # ['1 \t1 \tis thinking', '1 \t1 \tis sleeping', '1 \t2 \tis thinking', '1 \t2 \tis sleeping', '1 \t3 \tis thinking', '1 \t3 \tis sleeping', '1 \t4 \tis thinking', '1 \t4 \tis sleeping', '202 \t3 \tis thinking', '202 \t3 \tis sleeping', '202 \t1 \tis thinking', '202 \t1 \tis sleeping', '202 \t4 \tis thinking', '202 \t4 \tis sleeping', '202 \t2 \tis thinking', '202 \t2 \tis sleeping']
        pattern = re.compile(
            r"^\d+\s+\t+\d+\s+\t"
            r"(has taken a fork|is eating|is sleeping|is thinking|died)$"
        )
        for line in lines:
            assert pattern.match(line), f"Bad format: '{line}'"

    @pytest.mark.skip(reason="This tests passes on empty main")
    def test_stops_after_meals(self, run_philo):
        """With meal limit, simulation should end without death."""
        child = run_philo("5 800 200 200 3", timeout=20)
        child.expect(pexpect.EOF)
        output = child.before
        assert "died" not in output
    



class TestTimingConstraints:
    """Test that timestamps are monotonically increasing."""
        
    @pytest.mark.skip(reason="This tests passes on empty main")
    def test_timestamps_increasing(self, run_philo):
        child = run_philo("4 410 200 200 3", timeout=15)
        child.expect(pexpect.EOF)
        output = child.before
        lines = [l.strip() for l in output.strip().split("\n") if l.strip()]
        timestamps = []
        for line in lines:
            parts = line.split()
            if parts:
                try:
                    timestamps.append(int(parts[0]))
                except ValueError:
                    pass
        for i in range(1, len(timestamps)):
            assert timestamps[i] >= timestamps[i - 1], \
                f"Timestamp went backwards: {timestamps[i-1]} -> {timestamps[i]}"