import sys
import pefile
import subprocess
from typing import List


COMMAND_LINE_TEST_PREFIX = 'T'
COMMAND_LINE_SETUP_PREFIX = 'U'
COMMAND_LINE_TEARDOWN_PREFIX = 'D'

TEST_NAME_PREFIX = b'test_'
SETUP_NAME_PREFIX = b'setup_'
TEARDOWN_NAME_PREFIX = b'teardown_'


def get_all_exports(tests_file: str):
    tests = []
    pe = pefile.PE(tests_file)
    for exp in pe.DIRECTORY_ENTRY_EXPORT.symbols:
        tests.append(exp.name)
    return tests


def get_sorted_setup_teardown(setups: List[bytes], teardowns: List[bytes]):
    sorted_setups_no_prefix = [setup.replace(SETUP_NAME_PREFIX, b'', 1) for setup in setups]
    sorted_teardowns_no_prefix = [teardown.replace(TEARDOWN_NAME_PREFIX, b'', 1) for teardown in teardowns]
    sorted_setups_no_prefix.sort()
    sorted_teardowns_no_prefix.sort()

    assert sorted_setups_no_prefix == sorted_teardowns_no_prefix, 'Mismatch in setups and teardowns'

    sorted_setups = [SETUP_NAME_PREFIX + setup for setup in sorted_setups_no_prefix]
    sorted_teardowns = [TEARDOWN_NAME_PREFIX + teardown for teardown in sorted_teardowns_no_prefix]
    return sorted_setups, sorted_teardowns


def main(tests_file: str):
    exports = get_all_exports(tests_file)
    tests = [export for export in exports if export.startswith(TEST_NAME_PREFIX)]
    setups = [export for export in exports if export.startswith(SETUP_NAME_PREFIX)]
    teardowns = [export for export in exports if export.startswith(TEARDOWN_NAME_PREFIX)]
    setups, teardowns = get_sorted_setup_teardown(setups, teardowns)

    args = [tests_file]
    args += [COMMAND_LINE_TEST_PREFIX + test.decode('utf8') for test in tests]
    args += [COMMAND_LINE_SETUP_PREFIX + setup.decode('utf8') for setup in setups]
    args += [COMMAND_LINE_TEARDOWN_PREFIX + teardown.decode('utf8') for teardown in teardowns]
    print(args)
    subprocess.check_call(args)


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print(f'Usage: {sys.argv[0]} <test_file>')
        exit(1)
    main(sys.argv[1])
