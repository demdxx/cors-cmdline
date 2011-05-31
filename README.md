Simple C++ cmdline parser
=========================

## Ver 0.0

*No comment...*

**test.cpp**

	#include <iostream>
	#include "CmdLine.h"
	
	using cors::cmdline::CmdInfo;
	using cors::cmdline::CmdLine;
	using cors::cmdline::CmdParam;
	
	static CmdInfo commands[] = {
		{ 1, 	CmdInfo::TYPE_FLAG,		"-h",	"--help",		"Show help information" 	},
		{ 2,	CmdInfo::TYPE_FLAG,		"-c",	"--continue",	"Continue downloading"		},
		{ 3,	CmdInfo::TYPE_PARAM,	"-f",	"--file",		"Downloading file or url"	},
		{ 4,	CmdInfo::TYPE_PARAM,	"-s",	"--segments",	"Segments count"			},
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
			
			const char* file = cmd["-f"];
			bool is_continue = cmd["-c"];
			int segments_cnt = cmd["-s"];
			
			std::cout	<< std::endl << (is_continue?"Continue load: \"":"") << file << "\""
						<< (segments_cnt>0 ? " segments: " : "" ) << segments_cnt << std::endl << std::endl;
		
		}
		
		return 0;
	}