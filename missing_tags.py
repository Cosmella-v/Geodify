from pathlib import Path
import re

SRC_DIR = Path("src")
PREVIEWS_DIR = Path("previews")
SAPPHIRE_DIR = PREVIEWS_DIR / "sapphire"

COMMENT_PATTERN = re.compile(r'//\[\[omgrod\.geodify/TAG\]\]\s*([^\s:]+)')
MACRO_PATTERN = re.compile(r'ADD_TAG\(\s*"([^"]+)"\s*\)')

def get_source_tags():
    tags = set()

    for file in SRC_DIR.rglob("*"):
        if file.suffix not in [".cpp", ".hpp", ".h"]:
            continue

        text = file.read_text(errors="ignore")

        for match in COMMENT_PATTERN.finditer(text):
            tags.add(match.group(1))

        for match in MACRO_PATTERN.finditer(text):
            tags.add(match.group(1))

    return tags

def get_preview_tags(directory):
    tags = set()

    if not directory.exists():
        return tags

    for file in directory.glob("*.png"):
        name = file.stem

        if name.endswith("Preview"):
            name = name[:-7]

        tags.add(name)

    return tags

def main():
    source_tags = get_source_tags()

    swelvy_tags = get_preview_tags(PREVIEWS_DIR)
    sapphire_tags = get_preview_tags(SAPPHIRE_DIR)

    missing_swelvy = source_tags - swelvy_tags
    missing_sapphire = source_tags - sapphire_tags

    print("\n=== Missing SwelvyBG previews ===")

    if missing_swelvy:
        for tag in sorted(missing_swelvy):
            print(tag)
    else:
        print("None")

    print("\n=== Missing Sapphire previews ===")

    if missing_sapphire:
        for tag in sorted(missing_sapphire):
            print(tag)
    else:
        print("None")

    print("\n=== Preview summary ===")
    print(f"Source tags:   {len(source_tags)}")
    print(f"SwelvyBG:      {len(swelvy_tags)}")
    print(f"Sapphire:      {len(sapphire_tags)}")
    print(f"Missing BG:    {len(missing_swelvy)}")
    print(f"Missing SAP:   {len(missing_sapphire)}")

if __name__ == "__main__":
    main()