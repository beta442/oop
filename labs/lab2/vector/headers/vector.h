#pragma once

#include "std_lib.h"

bool CopyStreamOfDoubleIntoVector(std::istream& fIn, std::vector<double>& vec);
void ProcessVectorOfDoubleByTask(std::vector<double>& vec);
void PrintVectorOfDouble(const std::vector<double>& vec);
