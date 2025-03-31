# 2025/3/31
# zhangzhong

from pathlib import Path

out_file = Path(
    "/Users/zhangzhong/src/aoapc-bac2nd/src/ch11/Example_11-4_CallingCircles/out.txt"
)
tmp_file = Path(
    "/Users/zhangzhong/src/aoapc-bac2nd/src/ch11/Example_11-4_CallingCircles/tmp.txt"
)


# 实现一个函数，读取一个文件，然后返回一个set
def parse_file(file: Path) -> list[list[set[str]]]:
    results: list[list[set[str]]] = []
    with file.open(mode="r") as f:
        text = f.read()
        cases = text.split("\n\n")

        for case in cases:
            sets: list[set[str]] = []
            lines = case.split("\n")
            for line in lines[1:]:
                sets.append(set(line.split(", ")))
            results.append(sets)
    return results


out_results = parse_file(out_file)
tmp_results = parse_file(tmp_file)
for i, out, tmp in zip(range(len(out_results)), out_results, tmp_results):
    # list[set[str]] 要如何比较呢？
    # Option 2: Compare as Unordered Collections of Sets
    # If the order of sets in the list doesn't matter (you just want to know if both lists contain the same sets), you can convert the lists to sets of frozensets:

    # set(frozenset(s) for s in out)
    # This works because:

    # frozenset is a hashable, immutable version of set that can be placed in other sets
    # This comparison only cares about which sets are present, not their order
    assert set(frozenset(s) for s in out) == set(frozenset(s) for s in tmp), (
        f"In case {i + 1}, Expected {out}, but got {tmp}"
    )
    # assert out == tmp, f"Expected {out}, but got {tmp}"
print("All tests passed.")
