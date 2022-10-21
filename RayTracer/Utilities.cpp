#include "Utilities.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>

void SavePPMFile(int width, int height, unsigned char* image, std::string filename) {

	// If duplicate file exists, create new one with incremented version number.
	std::ifstream file(filename + std::string(".ppm"));
	int version = 0;
	while (file) {
		filename += std::string("_") + std::to_string(version);
		version++;
		file.open(filename + std::string(".ppm"));
	}
	file.close();

	// Save the ppm file.
	std::ofstream out(filename + std::string(".ppm"));
	out << "P3\n" << width << " " << height << "\n" << "255\n";
	for (int j = height - 1; j >= 0; j--) {
		for (int i = 0; i < width * 3; i += 3) {
			int r = image[j * width * 3 + i + 0];
			int g = image[j * width * 3 + i + 1];
			int b = image[j * width * 3 + i + 2];

			out << r << ' ' << g << ' ' << b << "\n";
		}
	}
	out.close();
}