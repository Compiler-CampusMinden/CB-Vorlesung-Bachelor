---@diagnostic disable: undefined-global
-- how to handle subtopics?
-- put index-headlines into buckets -> based on directory parts
-- 		for each level! -> store chapter_weights of index-headlines in
-- after that, sort the entries in each bucket only in the bucket (based on weight)
-- 		for each bucket level
-- after that, we have the order, but we need to collect the slides and sort all
-- accordingly -> could be done in same pass as bucketing -> if it is not a
-- topic or title, it is a slide -> put in table for last encountered chapter / topic



-- TODO: update
	-- aktuelle Struktur:
	-- bucket: markdown
	-- {
	--   bucket: semantics
	--   {
	--   	index = {..., chapater_weight = 4}
	--   	bucket: symboltables
	--   	{
	--			index = {..., chapter_weight = 4},
	--			chapters =
	--			{
	--				1 = {..., chapter_weight = 1},
	--				2 = {..., chapter_weight = 2}
	--			}
	--   	},
	--   	chapters =
	--   	{
	--   		1 = {..., chapter_weight = 1},
	--   		2 = {..., chapter_weight = 3}
	--   	}
	--   }
	-- }
	--
	-- Lösung:;
	-- - jeder chapters-eintrag bekommt ein weight-feld
	-- - jeder subbucket mit index wird auch als chapters-eintrag mit weight
	-- hinzugefügt
	--#
function rPrint(s, l, i) -- recursive Print (structure, limit, indent)
	l = (l) or 100; i = i or "";	-- default item limit, indent string
	if (l<1) then print "ERROR: Item limit reached."; return l-1 end;
	local ts = type(s);
	if (ts ~= "table") then print (i,ts,s); return l-1 end
	print (i,ts);           -- print "table"
	for k,v in pairs(s) do  -- print "[KEY] VALUE"
		l = rPrint(v, l, i.."\t["..tostring(k).."]");
		if (l < 0) then break end
	end
	return l
end


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

function subbucket_to_chapter(bucket)
	local indices_to_add = {}
	local add_count = 0

	for i,el in pairs(bucket) do
		print("visitting key-value: " .. tostring(i))
		if i ~= "index" and i ~= "chapters" then
			print("entering: " .. tostring(i))
			if (el.index ~= nil) then

				print("converting index of " .. tostring(i))
				local weight = el.index.attributes.chapter_weight

				table.insert(
				indices_to_add,
				{
					weight=weight,
					index=el.index
				})
				add_count = add_count + 1
			end
		end
	end

	for i,el in pairs(bucket) do
		if i ~= "index" and i ~= "chapters" then
			if (el.index ~= nil) then
				subbucket_to_chapter(el)
			end
		end
	end

	if add_count > 0 then
		if (bucket["chapters"] == nil) then
			bucket["chapters"] = {}
		end
		for i,el in pairs(indices_to_add) do
			table.insert(
			bucket["chapters"],
			el
			)
		end
	end
end

function compare_by_weight(a,b)
	return a.weight < b.weight
end

function sort_bucket(bucket)
	if bucket == nil or bucket.chapters == nil then
		return
	end
	table.sort(bucket["chapters"], compare_by_weight)

	for i,el in pairs(bucket) do
		if (type(el)=="table" and el.chapters ~= nil) then
			sort_bucket(el)
		end
	end
end

function get_bucket(split_dir, parent_bucket)
	local count = 0
	for _ in pairs(split_dir) do count = count + 1 end

	if count == 0 then
		return parent_bucket
	end

	if count > 0 then
		local bucket_name = split_dir[1]
		print("bucket_name: " .. bucket_name)
		local bucket = parent_bucket[bucket_name]
		-- TODO: handle missing bucket

		table.remove(split_dir, 1)
		return get_bucket(split_dir, bucket)
	end
end

function emit_blocks(bucket)
	-- if bucket has chapters
	-- 		iterate over chapters
	-- 		if chapter-entry is index
	-- 			emit index-block
	-- 			iterate over chapters of topic denoted by index
	-- 		if chapter-entry is chapter
	-- 			emit chapter-slides

	if (bucket["chapters"] ~= nil) then
		for i, el in pairs(bucket["chapters"]) do
			if el.index ~= nil then
				table.insert(blocks, el.index)
				local split_dir = pandoc.path.split(el.index.attributes.dir)
				print("getting bucket for " .. el.index.attributes.dir)
				index_bucket = get_bucket(split_dir, directory_buckets)
				rPrint(index_bucket)
				emit_blocks(index_bucket)
			elseif el.chapter ~= nil then
				table.insert(blocks, el.chapter)
				local slide_container_name = get_slide_container_name(el.chapter)
				print("container name: ".. slide_container_name)
				local slides = slide_container[slide_container_name]
				for i,slide in pairs(slides) do
					table.insert(blocks, slide)
				end
			end
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
				local chapter_str
				= c.chapter ~= nil
				and pandoc.utils.stringify(c.chapter)
				or pandoc.utils.stringify(c.index)

				local weight = pandoc.utils.stringify(c.weight)
				local msg = prefix.."chapter: " .. chapter_str .. " " .. weight
				if (c.index ~= nil) then
					msg = msg .. " (was index)"
				end
				print(msg)
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

	table.insert
	(bucket["chapters"],
	{
		weight=chapter.attributes.chapter_weight,
		chapter=chapter
	})
end

function get_slide_container_name(header)
	return header.attributes.dir .. pandoc.utils.stringify(header.content)
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

			last_chapter_or_index_name = get_slide_container_name(el)
			print(last_chapter_or_index_name)

			put_index(el)
			--table.insert(top_level_headings, el)
		elseif el.t == "Header" and el.level == 2 then
			last_chapter_or_index_name = get_slide_container_name(el)

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

	rPrint(directory_buckets)

	--print_subbuckets(directory_buckets,0)

	subbucket_to_chapter(directory_buckets["markdown"])

	print("----------------------AFTER TRANSFORMATION----------------------")
	rPrint(directory_buckets)

	sort_bucket(directory_buckets["markdown"])
	print("----------------------AFTER SORTING----------------------")

	rPrint(directory_buckets)
	--print("AFTER TRANSFORMATION")
	--print_subbuckets(directory_buckets,0)
	print("----------------------EMITTING BLOCKS----------------------")
	emit_blocks(directory_buckets["markdown"])

	return pandoc.Pandoc(blocks)
	--return doc
end

return {
  traverse = 'topdown',
  --{ Header = Header},
  { Pandoc = Pandoc},
}
