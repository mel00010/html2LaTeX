#!/usr/bin/env python3
from collections import OrderedDict
from itertools import islice
import json
import sys

with open(sys.argv[1]) as json_file:
	json_data = json.load(json_file, strict=True,object_pairs_hook=OrderedDict)
	with open(sys.argv[2], 'w') as output_file:
		output_file.write('#include <array>\n')
		output_file.write('#include <tuple>\n\n')
		output_file.write(
			'static constexpr std::array<std::tuple<const char32_t*, char32_t, char32_t>, '
			+str(len(json_data.items()))
			+'> characterReferences = {{\n')
		for i in sorted(list(json_data.items()), key=(lambda x: len(x[0])), reverse=True):
			output_file.write('\t\tstd::make_tuple( U"')
			output_file.write(i[0])
			output_file.write('", U\'\\U')
			output_file.write('{:08X}'.format(i[1]["codepoints"][0]))
			output_file.write('\', ')
			if len(i[1]["codepoints"]) is 1:
				output_file.write('(char32_t) EOF')
			else:
				output_file.write('U\'\\U')
				output_file.write('{:08X}'.format(i[1]["codepoints"][1]))
				output_file.write('\'')
			output_file.write('),\n')
		output_file.write('}};\n')