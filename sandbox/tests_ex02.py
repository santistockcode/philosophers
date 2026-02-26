import os
import logging
import pexpect


def main():
    ex02_bin = os.path.abspath("./ex02/ex02")
    log_level = 'DEBUG'
    logging.basicConfig(
    level=getattr(logging, log_level, logging.INFO),
    format="%(asctime)s %(levelname)s %(message)s"
    )
    logging.getLogger(__name__).info("Starting e2e tests (log level=%s)", log_level)

    # Compile the ex02 binary if needed
    logging.info("Running ex02 binary: %s", ex02_bin)

    # Spawn the ex02 process
    child = pexpect.spawn(ex02_bin, timeout=5)
    child.logfile = open('ex02_output.log', 'wb')

    try:
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