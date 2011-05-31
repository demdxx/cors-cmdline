/**
 * 
 * CmdLine.cpp
 *  
 * Author:
 *       Dmitry Ponomarev (Aguacero) <demdxx@gmail.com>
 * 
 * Copyright (c) 2011 Dmitry Ponomarev V.
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

#include <stdlib.h>
#include <string.h>

#include "CmdLine.h"

using namespace cors::cmdline;

// Command Param ---

CmdParam::CmdParam( const char* value, const CmdInfo* info )
	: value( value ), info( info ) {}

CmdParam::operator CmdParam::ASCII_TYPE( void ) {
	return info && info->type==CmdInfo::TYPE_FLAG
			? "Y" : ( value>(const char*)0 ? value : "" );
}

CmdParam::operator int( void )
{
	return info && info->type==CmdInfo::TYPE_FLAG
			? 1 : ( value>(const char*)0 ? atoi(value) : 0 );
}

CmdParam::operator float( void )
{
	return info && info->type==CmdInfo::TYPE_FLAG
			? 1. : ( value>(const char*)0 ? atof(value) : 0. );
}

CmdParam::operator bool( void )
{
	return info!=NULL;
}

CmdParam::operator CmdParam::CmdInfoPtr( void )
{
	return info;
}

const char* CmdParam::key( bool sh )
{
	const char* n = info ? ( sh ? info->short_name : info->name ) : "";
	return n ? n : "";
}

int CmdParam::code( void )
{
	return info ? info->code : 0;
}

// Command Line ---

CmdLine::CmdLine( int argc, char** argv, CmdInfo* commands )
		: _argc(argc), _argv(argv), _commands(commands) {}

CmdInfo* CmdLine::get_command( const char* name )
{
	if( _commands ) {
		for( int i=0 ; ; i++ ) {
			if( _commands[i].code == 0 )
				return NULL;
			if( strcmp(_commands[i].short_name,name)==0 || strcmp(_commands[i].name,name)==0 )
				return _commands+i;
		}
	}
	return NULL;
}

bool CmdLine::has_param( const char* name )
{
	if( _argc>1 && _commands ) {
		CmdInfo* info 	= NULL;
		for( int subindex = 1 ; subindex<_argc ; subindex++ ) {
			info = get_command(_argv[subindex]);
			if( !info ) continue;

			if( info->type != CmdInfo::TYPE_FLAG )
				subindex++;

			if( !info->short_name || strcmp(info->short_name,name)!=0 )
				if( info->name && strcmp(info->name,name)!=0 ) continue;

			return true;
		}
	}
	return false;
}

CmdParam CmdLine::get_param( const char* name )
{
	if( _argc>1 && _commands ) {
		CmdInfo* info 	= NULL;
		for( int subindex = 1 ; subindex<_argc ; subindex++ ) {
			info = get_command(_argv[subindex]);
			if( !info ) continue;

			if( info->type != CmdInfo::TYPE_FLAG )
				subindex++;

			if( !info->short_name || strcmp(info->short_name,name)!=0 )
				if( info->name && strcmp(info->name,name)!=0 ) continue;

			return CmdParam( _argv[subindex], info );
		}
	}
	return CmdParam(NULL,NULL);
}

CmdParam CmdLine::get_param( int index )
{
	if( _argc>1 && _commands ) {
		CmdInfo* info 	= NULL;
		for( int subindex = 1 ; subindex<_argc ; subindex++ ) {
			info = get_command(_argv[subindex]);
			if( !info ) continue;

			if( info->type != CmdInfo::TYPE_FLAG )
				subindex++;

			if( --index<0 )
				return CmdParam( _argv[subindex], info );
		}
	}
	return CmdParam(NULL,NULL);
}

int CmdLine::count( void )
{
	int icount 	= 0;

	if( _argc>1 && _commands ) {
		CmdInfo* info 	= NULL;
		bool	b		= false;
		for( int subindex = 1 ; subindex<_argc ; subindex++ ) {
			if( b ) {
				icount++;
				b = false;
			}
			else {
				info = get_command(_argv[subindex]);
				if( !info ) continue;
				
				if( info->type == CmdInfo::TYPE_FLAG )
					icount++;
				else
					b	= true;
			}
		}
	}
	return icount;
}

CmdParam CmdLine::operator[]( const char* name )
{
	return get_param(name);
}

CmdParam CmdLine::operator[]( int index )
{
	return get_param(index);
}

CmdLine::operator int( void )
{
	return count();
}