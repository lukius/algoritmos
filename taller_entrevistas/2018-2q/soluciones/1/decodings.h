#ifndef _DECODINGS_H_
#define _DECODINGS_H_

#include <string>
#include <vector>


int num_decodings(const std::string&);

int num_decodings_2(
		const std::string &,
		size_t =0,
		std::vector<int> * =nullptr);

#endif