make web_sources | xargs -n 1 bash -c 'pandoc "$0" --lua-filter=tools/extract-lecture-structure/filewise_pass.lua -o temp.md; cat temp.md >> temp_summary.md'
