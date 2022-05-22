-- how to handle subtopics?
-- put index-headlines into buckets -> based on directory parts
-- 		for each level! -> store chapter_weights of index-headlines in
-- after that, sort the entries in each bucket only in the bucket (based on weight)
-- 		for each bucket level
-- after that, we have the order, but we need to collect the slides and sort all
-- accordingly -> could be done in same pass as bucketing -> if it is not a
-- topic or title, it is a slide -> put in table for last encountered chapter / topic

directory_buckets = {}
slide_container = {}
blocks = {}

pandoc.utils = require 'pandoc.utils'
pandoc.path = require 'pandoc.path'

function Header(header)
	local title = pandoc.utils.stringify(header.content)
	local level = pandoc.utils.stringify(header.level)
	print(title .. " " .. level)
end

function create_dir_buckets(split_dir, parent)
	local count = 0
	for _ in pairs(split_dir) do count = count + 1 end
	if count > 0 then
		local str = pandoc.utils.stringify(split_dir)
		local bucket_name = split_dir[1]
		table.remove(split_dir, 1)

		local bucket = parent ~= nil and parent or directory_buckets
		if (bucket[bucket_name] == nil) then
			bucket[bucket_name] = {}
		end
		create_dir_buckets(split_dir, bucket[bucket_name])
	end
end

function compare_buckets_by_index(a,b)
	return a.index.attributes.chapter_weight < b.index.attributes.chapter_weight
end

function compare_by_chapter_weight(a,b)
	return a.attributes.chapter_weight < b.attributes.chapter_weight
end

function emit_sorted_blocks(bucket)
	-- every bucket has potentially an index and chapters
	-- chapters are stored in one list
	-- topics (indices) are stored in multiple lists..
	-- TODO: to improve comparability, should store a "weight" field for all, that
	-- should be sorted..

	if (bucket.index ~= nil) then
		print("sorting")
		table.sort(bucket, compare_by_chapter_weight)
	end

	for i,el in pairs(bucket) do
		if (type(el)=="table" and el.index ~= nil) then
			emit_sorted_blocks(el)
		end
	end
end

function print_subbuckets(bucket, indentation)
	local prefix = ""
	for i=0, tonumber(indentation) do
		prefix = prefix.."  "
	end
	for i,el in pairs(bucket) do

		print(prefix.."bucket: "..i)
		if (el.index ~= nil) then
			local index_str = pandoc.utils.stringify(el.index)
			local index_weight = pandoc.utils.stringify(el.index.attributes.chapter_weight)
			print(prefix.."index: ".. index_str .. " " .. index_weight)
		end
		if (i=="chapters") then
			for n, c in pairs(bucket[i]) do
				local chapter_str = pandoc.utils.stringify(c)
				local weight = pandoc.utils.stringify(c.attributes.chapter_weight)
				print(prefix.."chapter: " .. chapter_str .. " " .. weight)
			end
		end
		if (i~= "chapters" and i~= "index" and  type(el) == "table") then
			print_subbuckets(el, indentation + 1)
		end
	end
end

function put_index(index)
	print("put index")

	local bucket = directory_buckets
	local split_dir = pandoc.path.split(index.attributes.dir)
	for i,el in pairs(split_dir) do
		print (el)
		bucket = bucket[el]
	end
	bucket["index"] = index
end

function put_chapter(chapter)
	print("put chapter")

	local bucket = directory_buckets
	local split_dir = pandoc.path.split(chapter.attributes.dir)
	for i,el in pairs(split_dir) do
		print (el)
		bucket = bucket[el]
	end
	if (bucket["chapters"] == nil) then
		bucket["chapters"] = {}
	end
	table.insert(bucket["chapters"], chapter)
end

function Pandoc(doc)
	local top_level_headings = {}
	local last_chapter_or_index_name = "none"

	for i,el in pairs(doc.blocks) do
		if el.t == "Header" and el.attributes.is_index == "true" then
			-- bucketing

			print("index")
			local split_dir =  pandoc.path.split(el.attributes.dir)
			create_dir_buckets(split_dir,nil)

			last_chapter_or_index_name = el.attributes.dir .. pandoc.utils.stringify(el.content)
			print(last_chapter_or_index_name)

			put_index(el)
			--table.insert(top_level_headings, el)
		elseif el.t == "Header" and el.level == 2 then
			last_chapter_or_index_name = el.attributes.dir .. pandoc.utils.stringify(el.content)

			local split_dir =  pandoc.path.split(el.attributes.dir)
			create_dir_buckets(split_dir,nil)

			print(last_chapter_or_index_name)

			put_chapter(el)
		elseif el.t == "Header" and el.level > 2 then
			if (slide_container[last_chapter_or_index_name] == nil) then
				slide_container[last_chapter_or_index_name] = {el}
			else
				table.insert(slide_container[last_chapter_or_index_name], el)
			end
		end
	end

	print_subbuckets(directory_buckets,0)

	emit_sorted_blocks(directory_buckets["markdown"])

	print("AFTER SORTING")
	print_subbuckets(directory_buckets,0)

	return doc
end

return {
  traverse = 'topdown',
  --{ Header = Header},
  { Pandoc = Pandoc},
}
