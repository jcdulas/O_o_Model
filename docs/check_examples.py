"""Check the order of public API examples in the Markdown guides and README."""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]
FENCE = re.compile(r"^ {0,3}(`{3,}|~{3,})(.*)$")
LANGUAGES = {"js": "JavaScript", "javascript": "JavaScript", "python": "Python", "cpp": "C++"}
EXPECTED = ("JavaScript", "Python", "C++")


def check(path):
    fence = None
    examples = 0
    for line_number, line in enumerate(path.read_text(encoding="utf-8").splitlines(), start=1):
        match = FENCE.match(line)
        if not match:
            continue
        marker, info = match.groups()
        if fence:
            if marker.startswith(fence) and not info.strip():
                fence = None
            continue
        fence = marker
        language = LANGUAGES.get(info.strip())
        if language:
            expected = EXPECTED[examples % 3]
            if language != expected:
                raise ValueError(f"{path}:{line_number}: expected {expected}, found {language}")
            examples += 1
    if examples % 3:
        raise ValueError(f"{path}: missing {EXPECTED[examples % 3]} example")
    return examples // 3


if __name__ == "__main__":
    paths = [ROOT / "README.md", *(ROOT / "docs").rglob("*.md")]
    print(f"Checked {sum(check(path) for path in paths)} JavaScript, Python and C++ example groups.")
