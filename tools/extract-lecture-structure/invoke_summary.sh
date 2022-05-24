pandoc .tmp_structure/temp_summary.md --lua-filter=tools/extract-lecture-structure/summary_pass.lua -o structure.md
rm -rf .tmp_structure
