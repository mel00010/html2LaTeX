#!/usr/bin/env python3
import json
import sys

with open(sys.argv[1]) as json_file:
	json_data = json.load(json_file)
	with open(sys.argv[2], 'w') as output_file:
		output_file.write('#include <utility>\n\n')
		output_file.write('using Item = std::pair<char32_t, const char*>;\n\n')
		output_file.write('static constexpr Item unicodeToLaTeX[] = {\n')
		for i in json_data:
			output_file.write('\t\t{ '+i[0]+', "'+repr(i[1])[1:-1].replace('"', '\\"')+'" },\n')
		output_file.write('};\n')