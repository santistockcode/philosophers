"""
E2E tests: death detection and message rules.
"""

import pexpect
import pytest


class TestDeathDetection:
    """Verify a philosopher dies when they should."""

    def test_should_die(self, run_philo):
        """time_to_die < time_to_eat + time_to_sleep → must die."""
        child = run_philo("4 310 200 200", timeout=10)
        child.expect(r"\d+\s+\d+\s+died")
        child.close()

    def test_no_msg_after_death(self, run_philo):
        """No messages should appear after a death message."""
        child = run_philo("4 310 200 200", timeout=10)
        child.expect(r"\d+\s+\d+\s+died")
        # Read whatever remains
        try:
            child.expect(pexpect.EOF, timeout=3)
        except pexpect.TIMEOUT:
            pass
        remaining = child.before.strip() if child.before else ""
        # After "died", no additional action lines (allow empty or whitespace)
        lines_after = [l for l in remaining.split("\n") if l.strip()]
        assert len(lines_after) == 0, \
            f"Messages after death: {lines_after}"

    def test_death_timing(self, run_philo):
        """Death should be detected within 10ms of time_to_die."""
        import re
        child = run_philo("1 200 200 200", timeout=5)
        child.expect(r"(\d+)\s+1\s+died")
        death_ts = int(child.match.group(1))
        # 1 philo with 200ms die time → should die around 200ms
        assert death_ts <= 210, \
            f"Death detected too late: {death_ts}ms (expected ≤210ms)"


class TestNoDeathScenarios:
    """These should NOT produce a death."""
    
    @pytest.mark.skip(reason="This tests passes on empty main")
    @pytest.mark.parametrize("args", [
        "5 800 200 200 7",
        "4 410 200 200 10",
        "2 800 200 200 5",
    ])
    def test_no_death_with_enough_time(self, run_philo, args):
        child = run_philo(args, timeout=30)
        child.expect(pexpect.EOF)
        output = child.before
        assert "died" not in output