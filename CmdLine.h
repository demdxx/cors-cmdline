/**
 * 
 * CmdLine.h
 *  
 * Author:
 *       Dmitry Ponomarev (Aguacero) <demdxx@gmail.com>
 * 
 * Copyright (c) 2011 Dmitry Ponomarev V.}
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#pragma once

namespace cors
{
	namespace cmdline
	{
		struct CmdInfo
		{
			enum {
				TYPE_FLAG	= 0,
				TYPE_PARAM,
			};
			
			int			code;
			char		type;
			const char*	short_name;
			const char*	name;
			const char*	description;
		};

		class CmdParam
		{
			public:
				typedef const char*		ASCII_TYPE;
				typedef const CmdInfo*	CmdInfoPtr;

				const char* 	value;
				const CmdInfo*  info;
				
			public:
				CmdParam( const char* value, const CmdInfo* info );
				
				operator ASCII_TYPE( void );
				operator int( void );
				operator float( void );
				operator bool( void );
				operator CmdInfoPtr( void );
				
				const char* key( bool sh = false );
				int code( void );
		};

		class CmdLine
		{
			protected:
				int			_argc;
				char**  	_argv;
				CmdInfo*	_commands;
			public:
				CmdLine( int argc, char** argv, CmdInfo* commands );
				CmdInfo* get_command( const char* name );

				bool has_param( const char* name );
				CmdParam get_param( const char* name );
				CmdParam get_param( int index );
				int count( void );
				
				CmdParam operator[]( const char* name );
				CmdParam operator[]( int index );
				operator int( void );
		};

	}
}