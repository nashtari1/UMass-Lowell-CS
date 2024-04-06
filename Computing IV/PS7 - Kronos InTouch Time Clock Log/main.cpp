// Copyright 2023 Nika Ashtari
// This file is part of the Kronos Time Clock Program
// All rights reserved

// Header files and directives
#include <iostream>
#include <fstream>
#include <string>
#include <boost/regex.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int main(int argc, const char* argv[]) {
     std::ifstream file(argv[1]);
     if (file.fail()) {
          std::cout << "Could not open file" << std::endl;
          exit(1);
     }

     std::string outFile(argv[1]);
     outFile += ".rpt";
     std::ofstream output_file(outFile);

     // First pass: count total number of lines
     int totalLines = 0;
     std::string line;
     while (std::getline(file, line)) {
          totalLines += 1;
     }
     file.clear();
     file.seekg(0);

     // Header info
     output_file << "Device Boot Report\n\n";
     output_file << "InTouch log file: " << argv[1] << "\n";
     output_file << "Lines Scanned: " << totalLines << "\n\n";

     // Second pass: process lines and generate output
     boost::regex startup("([0-9]+)-([0-9]+)-([0-9]+) ([0-9]+):([0-9]+):([0-9]+): \\(log.c.166\\) server started.*");  //NOLINT
     boost::regex success("([0-9]+)-([0-9]+)-([0-9]+) ([0-9]+):([0-9]+):([0-9]+).([0-9]+):INFO:oejs.AbstractConnector:Started SelectChannelConnector@0.0.0.0:9080.*");  //NOLINT

     // Initializing variables
     int line_num = 1;
     boost::posix_time::ptime t;
     boost::posix_time::ptime bootEndTime;
     boost::gregorian::date date;
     boost::smatch sm;
     boost::gregorian::date tempD;
     bool repeat = false;

     while (std::getline(file, line)) {
          if (boost::regex_match(line, sm, startup)) {
               // checking for fail boot up
               if (repeat) {
                    output_file << "**** Incomplete boot ****\n" << std::endl;
               }
               output_file << "=== Device Boot ===" << std::endl;
               output_file << line_num << "(" << argv[1] << "): ";
               output_file << (sm[1]) << '-' << (sm[2]) << '-' << (sm[3])
               << ' ' << (sm[4]) << ':' << (sm[5]) << ':' << (sm[6])
               << ' ' << "Boot Start" << std::endl;
               tempD = boost::gregorian::
               from_undelimited_string(sm[1]+sm[2]+sm[3]);
               date = tempD;
               boost::posix_time::ptime tempT =
               boost::posix_time::from_iso_string
               (sm[1]+sm[2]+sm[3]+'T'+sm[4] + sm[5] + sm[6]);
               t = tempT;
               repeat = true;

            // checking for successful bootup
          } else if (boost::regex_match(line, sm, success)) {
               output_file << line_num << "(" << argv[1] << "): ";
               output_file << (sm[1]) << '-' << (sm[2]) << '-' << (sm[3])
               << ' ' << (sm[4]) << ':' << (sm[5]) << ':' << (sm[6])
               << ' ' << "Boot Completed" << std::endl;
               tempD = boost::gregorian::
               from_undelimited_string(sm[1]+sm[2]+sm[3]);
               date = tempD;
               boost::posix_time::ptime tempT =
               boost::posix_time::from_iso_string
               (sm[1]+sm[2]+sm[3]+'T'+sm[4] + sm[5] + sm[6]);
               bootEndTime = tempT;
               boost::posix_time::time_duration td = bootEndTime-t;
               output_file <<"\tBoot Time: " << td.total_milliseconds()
               << "ms" << std::endl << std::endl;
               repeat = false;
          }
          line_num += 1;
     }
     return 0;
}
