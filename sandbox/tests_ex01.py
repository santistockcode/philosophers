import os
import logging
import pexpect


def main():
    ex01_bin = os.path.abspath("./ex01/ex01")
    log_level = 'DEBUG'
    logging.basicConfig(
    level=getattr(logging, log_level, logging.INFO),
    format="%(asctime)s %(levelname)s %(message)s"
    )
    logging.getLogger(__name__).info("Starting e2e tests (log level=%s)", log_level)

    # Compile the ex01 binary if needed
    logging.info("Running ex01 binary: %s", ex01_bin)

    # Spawn the ex01 process
    child = pexpect.spawn(ex01_bin, timeout=5)
    child.logfile = open('ex01_output.log', 'wb')

    try:
        # Expect start timestamp
        child.expect(r'start\s+(\d+)')
        start_time = int(child.match.group(1))
        logging.info("Start timestamp: %d ms", start_time)
        
        # Expect end timestamp and difference
        child.expect(r'end\s+(\d+)')
        end_time = int(child.match.group(1))
        logging.info("End timestamp: %d ms", end_time)
        
        # Expect the difference (end - start)
        child.expect(r'end\s*-\s*start\s+(\d+)')
        diff_time = int(child.match.group(1))
        logging.info("Difference: %d ms", diff_time)
        
        # Assert that start time should be close to 0 (program just started)
        assert start_time >= 0 and start_time < 100, f"Start time should be near 0, got {start_time}"
        
        # Assert that the sleep was approximately 1000ms (allow some tolerance)
        assert 950 <= diff_time <= 1100, f"Sleep should be ~1000ms, got {diff_time}ms"
        
        # Assert consistency: end - start should equal diff_time
        assert abs((end_time - start_time) - diff_time) < 10, f"Inconsistent timestamps"
        
        logging.info("✓ All assertions passed")
        
    except pexpect.TIMEOUT:
        logging.error("Timeout waiting for output")
        raise
    except pexpect.EOF:
        logging.error("Unexpected EOF")
        raise
    finally:
        child.close()
        if child.logfile:
            child.logfile.close()

if __name__ == "__main__":
    main()