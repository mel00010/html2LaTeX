#!/usr/bin/env python3
from collections import OrderedDict
from itertools import islice
import json
import sys

with open(sys.argv[1]) as json_file:
	json_data = json.load(json_file, strict=True,object_pairs_hook=OrderedDict)
	with open(sys.argv[2], 'w') as output_file:
#  	with sys.stdout as output_file:
		output_file.write('#include <utility>\n\n')
# 		output_file.write('using Item = ;\n\n')
		output_file.write('static constexpr std::pair<const char*, const char32_t*> characterReferences[] = {\n')
#  		for i in list(islice(json_data.items(), 10)):
		for i in list(json_data.items()):
			output_file.write('\t\t{ "')
			output_file.write(i[0])
			output_file.write('", U"')
			for j in i[1]["codepoints"]:
				output_file.write('\\U{:08X}'.format(j))
			output_file.write('" },\n')
		output_file.write('};\n')