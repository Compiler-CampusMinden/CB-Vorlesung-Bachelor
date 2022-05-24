mkdir .tmp_structure
make web_sources | xargs -n 1 bash -c 'pandoc "$0" --lua-filter=tools/extract-lecture-structure/filewise_pass.lua -o .tmp_structure/temp.md; cat .tmp_structure/temp.md >> .tmp_structure/temp_summary.md'
