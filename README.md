Simple C++ cmdline parser
=========================

## Ver 0.1
+ Command line arguments
+ Param default values
+ Param type => flags

## Ver 0.0

*No comment...*

**test.cpp**

	#include <iostream>
	#include "CmdLine.h"
	
	using cors::cmdline::CmdInfo;
	using cors::cmdline::CmdLine;
	using cors::cmdline::CmdParam;
	
	// Example:
	// ./proc -c "http://depositfiles.com/file/d2sF3gd" -s 12 --file "movi.avi"
	
	static CmdInfo commands[] = {
		{ 1, 	CmdInfo::FLAG_NULL,		"-h",	"--help",		NULL,	"Show help information" 	},
		{ 2,	CmdInfo::FLAG_NULL,		"-c",	"--continue",	NULL,	"Continue downloading"		},
		{ 3,	CmdInfo::FLAG_ARGUMENT,	"-f",	"--file",		NULL,	"Save to file"				},
		{ 4,	CmdInfo::FLAG_ARGUMENT,	"-s",	"--segments",	"5",	"Segments count"			},
		{ 0 },
	};
	
	int main (int argc, char *argv[])
	{
		std::cout	<< "CORS CMDLINE CPP LIB 2011, License MIT" << std::endl
					<< "Simple cmd line parser" << std::endl << std::endl;
	
		CmdLine cmd(argc,argv,commands);
	
		if( cmd.has_param("-h") ) {
			
			std::cout	<< "My help information" << std::endl
						<< "--------------------------" << std::endl;
			
			for( int i=0; commands[i].code>0 ; i++ ) {
				std::cout	<< commands[i].short_name << " or " << commands[i].name
							<< "\t\t" << commands[i].description << std::endl;
			}
			
			std::cout	<< std::endl << "Example:" << std::endl
						<< "./proc -c \"http://depositfiles.com/file/d2sF3gd\" -s 12 --file \"movi.avi\""
						<< std::endl << std::endl;
			
		}
		else {
	
			std::cout	<< "Params count: " << (int)cmd << std::endl
						<< "--------------------------" << std::endl;
		
			for( int i=0 ; i<cmd ; i++ ) {
				CmdParam p = cmd[i];
				std::cout << i << ") " << cmd[i].key(true) << " or " << cmd[i].key(false)
						  << " " << cmd[i].info->description
						  << "\r\n\t\tValue:" << (const char*)cmd[i]
						  << " int:" << (int)cmd[i] << " float:" << (float)cmd[i] << std::endl;
			}
			
			const char* file 		= cmd["-f"];
			bool is_continue 		= cmd["-c"];
			int segments_cnt 		= cmd["-s"];
			
			const char* input_file	= cmd.get_argument(0);
			
			if( input_file )
				std::cout	<< std::endl << (is_continue?"Continue load: \"":"Load:") << input_file << "\""
							<< (segments_cnt>0 ? " segments: " : "" ) << segments_cnt
							<< (file ? " >> " : "" ) << file << std::endl << std::endl;
			else
				std::cout	<< std::endl << "Try --help" << std::endl << std::endl;
		}
		
		return 0;
	}
